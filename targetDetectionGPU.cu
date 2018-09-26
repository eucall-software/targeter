

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string.h>
#include <stdlib.h>
#include "math.h"
#include "targetDetectionGPU.h"
#include "globals.h"

/*
texture<int, cudaTextureType2D, cudaReadModeElementType> cuda_texture_image;
*/

using namespace std;

const double sqrt_2 = 1.4142135;

__global__ void haar_horizontal(float input[], float output[], int o_width, int w)
{
	int x_index = blockIdx.x*blockDim.x + threadIdx.x;
	int y_index = blockIdx.y*blockDim.y + threadIdx.y;

	if (x_index >= (w + 1) / 2 || y_index >= w) return;

	int i_thread_id = y_index*o_width + 2 * x_index;
	int o_thread_id = y_index*o_width + x_index;

	const double sqrt_2 = 1.4142135;
	output[o_thread_id] = (input[i_thread_id] + input[i_thread_id + 1]) / sqrt_2;
	output[o_thread_id + w / 2] = (input[i_thread_id] - input[i_thread_id + 1]) / sqrt_2;
}

__global__ void haar_vertical(float input[], float output[], int o_width, int w)
{
	int x_index = blockIdx.x*blockDim.x + threadIdx.x;
	int y_index = blockIdx.y*blockDim.y + threadIdx.y;

	if (y_index >= (w + 1) / 2 || x_index >= w) return;

	int p1 = 2 * y_index*o_width + x_index;
	int p2 = (2 * y_index + 1)*o_width + x_index;
	int p3 = y_index*o_width + x_index;

	const double sqrt_2 = 1.4142135;
	output[p3] = (input[p1] + input[p2]) / sqrt_2;
	output[p3 + o_width*w / 2] = (input[p1] - input[p2]) / sqrt_2;
}

void cudaScore::haar(float input[], float output[], int o_width, int o_height, int levels)
{
	float* d_input;
	float* d_output;

	int widthstep = o_width * sizeof(float);

	cudaMalloc(&d_input, widthstep*o_height);
	cudaMalloc(&d_output, widthstep*o_height);

	cudaMemcpy(d_input, input, widthstep*o_height, cudaMemcpyHostToDevice);

	dim3 blocksize(16, 16);
	dim3 gridsize;

	int w = o_width;
	gridsize.x = (w + blocksize.x - 1) / blocksize.x;
	gridsize.y = (w + blocksize.y - 1) / blocksize.y;

	for(int ct = 0; ct<levels; ct++)
	{
		haar_horizontal << <gridsize, blocksize >> >(d_input, d_output, o_width, w);
		haar_vertical << <gridsize, blocksize >> >(d_output, d_input, o_width, w);
		w /= 2;
	}

	cudaMemcpy(output, d_input, widthstep*o_height, cudaMemcpyDeviceToHost);

	cudaFree(d_input);
	cudaFree(d_output);
}

// compute Haar transform image is square of dimensions size (with power 2)
void cudaScore::haar2d_gpu(float* input, int size, int levels)
{
	int w = size;
	float* output = new float[size*size];

	haar(input, output, w, w, levels);
}


bool Check_CUDA_Device()
{
	int devID = 0;
	cudaError_t error;
	cudaDeviceProp deviceProp;
	error = cudaGetDevice(&devID);

	error = cudaGetDeviceProperties(&deviceProp, devID);

	int deviceCount = 0;
	if (cudaGetDeviceCount(&deviceCount) != cudaSuccess) {
		DBOUT("cudaGetDeviceCount FAILED CUDA Driver and Runtime version may be mismatched.\n");
		DBOUT("\nFAILED\n");
	}

	if (deviceProp.computeMode == cudaComputeModeProhibited)
	{
		DBOUT("Error: device is running in <Compute Mode Prohibited>, no threads can use ::cudaSetDevice().\n");
		return false;
	}
	else
	{
		DBOUT("GPU Device " << devID << " - " << deviceProp.name << " with compute capability major=" << deviceProp.major << " minor=" << deviceProp.minor << std::endl);

		const int kb = 1024;
		DBOUT("  Shared memory: " << (int)deviceProp.sharedMemPerBlock / kb << " MB" << std::endl);
		DBOUT("  Constant memory: " << (int)deviceProp.totalConstMem / kb << " MB" << std::endl);
		DBOUT("  Block registers: " << deviceProp.regsPerBlock << std::endl);
		DBOUT("  Warp size:        " << deviceProp.warpSize << std::endl);
		DBOUT("  Threads per block: " << deviceProp.maxThreadsPerBlock << std::endl);
		DBOUT("  Max block dimensions: " << deviceProp.maxThreadsDim[0] << ", " << deviceProp.maxThreadsDim[1] << ", " << deviceProp.maxThreadsDim[2] << std::endl);
		DBOUT("  Max grid dimensions:  " << deviceProp.maxGridSize[0] << ", " << deviceProp.maxGridSize[1] << ", " << deviceProp.maxGridSize[2] << std::endl);

		int driverVersion = 0, runtimeVersion = 0;

		if (devID == 0) {
			// This function call returns 9999 for both major & minor fields, if no CUDA capable devices are present
			if (deviceProp.major == 9999 && deviceProp.minor == 9999)
				printf("There is no device supporting CUDA.\n");
			else if (deviceCount == 1)
				printf("There is 1 device supporting CUDA\n");
			else
				printf("There are %d devices supporting CUDA\n", deviceCount);
		}

		printf("\nDevice %d: \"%s\"\n", devID, deviceProp.name);

		typedef struct
		{
			int SM; // 0xMm (hexidecimal notation), M = SM Major version, and m = SM minor version
			int Cores;
		} sSMtoCores;

		sSMtoCores nGpuArchCoresPerSM[] =
		{
			{ 0x10,  8 }, // Tesla Generation (SM 1.0) G80 class
			{ 0x11,  8 }, // Tesla Generation (SM 1.1) G8x class
			{ 0x12,  8 }, // Tesla Generation (SM 1.2) G9x class
			{ 0x13,  8 }, // Tesla Generation (SM 1.3) GT200 class
			{ 0x20, 32 }, // Fermi Generation (SM 2.0) GF100 class
			{ 0x21, 48 }, // Fermi Generation (SM 2.1) GF10x class
			{ 0x30, 192 }, // Kepler Generation (SM 3.0) GK10x class
			{ 0x35, 192 }, // Kepler Generation (SM 3.5) GK11x class
			{ -1, -1 }
		};


#if CUDART_VERSION >= 2020
		// Console log
		cudaDriverGetVersion(&driverVersion);
		printf("  CUDA Driver Version:                           %d.%d\n", driverVersion / 1000, driverVersion % 100);
		cudaRuntimeGetVersion(&runtimeVersion);
		printf("  CUDA Runtime Version:                          %d.%d\n", runtimeVersion / 1000, runtimeVersion % 100);
#endif
		printf("  CUDA Capability Major revision number:         %d\n", deviceProp.major);
		printf("  CUDA Capability Minor revision number:         %d\n", deviceProp.minor);

		printf("  Total amount of global memory:                 %u bytes\n", deviceProp.totalGlobalMem);
#if CUDART_VERSION >= 2000
		printf("  Number of multiprocessors:                     %d\n", deviceProp.multiProcessorCount);
		printf("  Number of cores:                               %d\n", nGpuArchCoresPerSM[deviceProp.major].SM * deviceProp.multiProcessorCount);
#endif
		printf("  Total amount of constant memory:               %u bytes\n", deviceProp.totalConstMem);
		printf("  Total amount of shared memory per block:       %u bytes\n", deviceProp.sharedMemPerBlock);
		printf("  Total number of registers available per block: %d\n", deviceProp.regsPerBlock);
		printf("  Warp size:                                     %d\n", deviceProp.warpSize);
		printf("  Maximum number of threads per block:           %d\n", deviceProp.maxThreadsPerBlock);
		printf("  Maximum sizes of each dimension of a block:    %d x %d x %d\n",
			deviceProp.maxThreadsDim[0],
			deviceProp.maxThreadsDim[1],
			deviceProp.maxThreadsDim[2]);
		printf("  Maximum sizes of each dimension of a grid:     %d x %d x %d\n",
			deviceProp.maxGridSize[0],
			deviceProp.maxGridSize[1],
			deviceProp.maxGridSize[2]);
		printf("  Maximum memory pitch:                          %u bytes\n", deviceProp.memPitch);
		printf("  Texture alignment:                             %u bytes\n", deviceProp.textureAlignment);
		printf("  Clock rate:                                    %.2f GHz\n", deviceProp.clockRate * 1e-6f);
#if CUDART_VERSION >= 2000
		printf("  Concurrent copy and execution:                 %s\n", deviceProp.deviceOverlap ? "Yes" : "No");
#endif
#if CUDART_VERSION >= 2020
		printf("  Run time limit on kernels:                     %s\n", deviceProp.kernelExecTimeoutEnabled ? "Yes" : "No");
		printf("  Integrated:                                    %s\n", deviceProp.integrated ? "Yes" : "No");
		printf("  Support host page-locked memory mapping:       %s\n", deviceProp.canMapHostMemory ? "Yes" : "No");
		printf("  Compute mode:                                  %s\n", deviceProp.computeMode == cudaComputeModeDefault ?
			"Default (multiple host threads can use this device simultaneously)" :
			deviceProp.computeMode == cudaComputeModeExclusive ?
			"Exclusive (only one host thread at a time can use this device)" :
			deviceProp.computeMode == cudaComputeModeProhibited ?
			"Prohibited (no host thread can use this device)" :
			"Unknown");
#endif
#if CUDART_VERSION >= 3000
		printf("  Concurrent kernel execution:                   %s\n", deviceProp.concurrentKernels ? "Yes" : "No");
#endif
#if CUDART_VERSION >= 3010
		printf("  Device has ECC support enabled:                %s\n", deviceProp.ECCEnabled ? "Yes" : "No");
#endif
		// csv masterlog info
		// *****************************
		// exe and CUDA driver name 
		printf("\n");
		std::string sProfileString = "deviceQuery, CUDA Driver = CUDART";
		char cTemp[10];

		// driver version
		sProfileString += ", CUDA Driver Version = ";

		sprintf(cTemp, "%d.%d", driverVersion / 1000, driverVersion % 100);

		sProfileString += cTemp;

		// Runtime version
		sProfileString += ", CUDA Runtime Version = ";

		sprintf(cTemp, "%d.%d", runtimeVersion / 1000, runtimeVersion % 100);

		sProfileString += cTemp;

		// Device count      
		sProfileString += ", NumDevs = ";

		sprintf(cTemp, "%d", deviceCount);

		sProfileString += cTemp;

		// First 2 device names, if any
		for (devID = 0; devID < ((deviceCount > 2) ? 2 : deviceCount); ++devID)
		{
			cudaDeviceProp deviceProp;
			cudaGetDeviceProperties(&deviceProp, devID);
			sProfileString += ", Device = ";
			sProfileString += deviceProp.name;
		}
		sProfileString += "\n";

		printf("%s", sProfileString.c_str());
	}
	return true;
}

#define checkCudaErrors(err) { __checkCudaErrors((err), __FILE__, __LINE__); }
inline void __checkCudaErrors(cudaError_t err, const char *file, int line)
{
	if (err != cudaSuccess)
	{
		const char* es = cudaGetErrorString(err);

		DBOUT("file=" << (int)file << " line= "  << line << " CUDA Runtime API error (" << (int)err << ")" <<  es << std::endl);
	}
}

cudaScore::cudaScore(int w_d, int h_d, int CoocSize)
{
	// allocate image
	cudaMalloc(&cuda_intensity_image, w_d * h_d * sizeof(int));

	// allocate target image
	cudaMalloc(&cuda_target_cooc, CoocSize * sizeof(float));

	// allocate score image
	cudaMalloc(&cuda_score_image, w_d * h_d * sizeof(float));

	cudaMalloc(&cuda_score_count_image, w_d * h_d * sizeof(int));
}

cudaScore::~cudaScore()
{
	cudaFree(cuda_intensity_image);
	cudaFree(cuda_target_cooc);
	cudaFree(cuda_score_image);
	cudaFree(cuda_score_count_image);
}


__global__
void mycudaMemsetInt(int* image, int n)
{
	int i = blockIdx.x*blockDim.x + threadIdx.x;

	if (i < n)
	{
		image[i] = 0;
	}
}

__global__
void mycudaMemsetFloat(float* image, int n)
{
	int i = blockIdx.x*blockDim.x + threadIdx.x;

	if (i < n)
	{
		image[i] = 0.0;
	}
}

/**
*
*  Gets coocurrance matrix for image region for grayscale image
*
* @author    David Watts
* @since     2017/03/07
*
* FullName   getCoocMatrixGrayGPU
* Qualifier
* @param     int* & m
* @param     int * pMask
* @param     int startX
* @param     int startY
* @param     int regionWidth
* @param     int regionHeight
* @param     float * coMatrixF
* @param     int NoClusters
* @param     int maxD
* @return    float
* Access     public
*/
__device__
void getCoocMatrixGrayGPU(int* pImage, int image_ind_x, int image_ind_y, int width, int height,
						int regionWidth, int regionHeight, float* coMatrixRegion, int averageCluster,
						int maxDist, int coDIMX, int coDIMY, int coDIMZ, bool bFASTCOOC)	
{
	int local_sum = 0;
	int pixel_index = image_ind_x + image_ind_y*width;
	
	if (threadIdx.x < regionWidth && threadIdx.y < regionHeight)
	{
		int c1 = pImage[image_ind_x + image_ind_y * width]; //tex2D(cuda_texture_image, image_ind_x, image_ind_y); 

		if (c1 >= 0)
		{
			if(bFASTCOOC)
			{
				float dx = (threadIdx.x);
				float dy = (threadIdx.y);

				float dxy = sqrtf(dx*dx+dy*dy);
				int d = MIN(coDIMY-1, int(coDIMY*(dxy/maxDist)));

				int dC = MIN(coDIMX-1, MAX(0, coDIMX/2 + (averageCluster - c1)));	// offset to handle negative numbers

				int ind = dC + coDIMX * d;	// 2D indexing

				if (ind < coDIMX*coDIMY)
				{
					atomicAdd(&coMatrixRegion[ind], 1.0);
					atomicAdd(&coMatrixRegion[0], 1.0);	
				}
			}
			else
			{
				int nextIndex = 1 + threadIdx.x + threadIdx.y*regionWidth;

				int nextJ = nextIndex / regionWidth;
				int nextI = nextIndex % regionWidth;

				//printf("rw=%d rh=%d\n", regionWidth, regionHeight);

				// check against all others - the slow part !!!
				for (int y = nextJ; y < regionHeight; y++)
					for (int x = nextI; x < regionWidth; x++)
					{
						if (image_ind_x + x < width && image_ind_y + y < height)
						{
							int c2 = pImage[(image_ind_x + x) + (image_ind_y + y)*width];  //tex2D(cuda_texture_image, image_ind_x + x, image_ind_y + y);

							if (c2 >= 0)
							{
								float dx = (x - threadIdx.x);
								float dy = (y - threadIdx.y);

								float dxy = sqrtf(dx*dx+dy*dy);
								int d = MIN(coDIMZ-1, int(coDIMZ*(dxy/maxDist)));

								int ind = c1 + coDIMX * (c2 + coDIMY * d);

								if (ind < coDIMX*coDIMY*coDIMZ)
								{
									atomicAdd(&coMatrixRegion[ind], 1.0);
									atomicAdd(&coMatrixRegion[0], 1.0);	
								}
							}
						}
					}
			}

			
		}
	}
}

/**
*
*  Gets target score image based on matching image regions with training coccurrance mattrix (coMatrixTestF)
*
* @author    David Watts
* @since     2017/03/07
*
* FullName   findTargets
* Qualifier
* @param     int* & detectionImage
* @param     float * coMatrixTestF
* @param     int NoClusters
* @param     int maxD
* @return    float*
* Access     public
*/
__global__
void scoreTargetsGPU(int* cuda_intensity_image, int w, int h, int regionWidth, int regionHeight, int increment_W, int increment_H,
					float* coMatrixTarget, float* scoreImage, int* countImage, float maxDist, int coDIMX, int coDIMY, 
					int coDIMZ, int averageCluster, int* ct, bool bCrossEntropy, bool bFASTCOOC)
{
	__shared__ float shared_score;

	extern __shared__ float sh[];
	float* sharedCoocRegion = sh;
	//int* sharedCoocRegion = (int*)sh + regionWidth*regionHeight;

	// index into image and sub tile
	int image_ind_x = blockIdx.x*increment_W + threadIdx.x;
	int image_ind_y = blockIdx.y*increment_H + threadIdx.y;

	// zero shared memory
	int tid = threadIdx.y*blockDim.x + threadIdx.x;			// get linear thread index
	int cN = coDIMX*coDIMY*coDIMZ;

	if(bFASTCOOC)
		cN = coDIMX*coDIMY;
	
	int blockSize = blockDim.x * blockDim.y;

	// zero co-occurrence matrix using parallel threads, and loop to fill in rest up to cN
	for(int i=tid; i<cN; i += blockSize)
		sharedCoocRegion[i] = 0;
		
	__syncthreads();	// all threads in block synchronised
/*
	// copy image region into into shared tile memory
	if (image_ind_x < w && image_ind_y < h)
		sharedTile[threadIdx.x + threadIdx.y*regionWidth] = tex2D(cuda_texture_image, image_ind_x, image_ind_y);
	else
		sharedTile[threadIdx.x + threadIdx.y*regionWidth] = -1;
*/
	
	// create the coocurrence matrices

	// last data point has nothing to check against
	if (threadIdx.x != regionHeight - 1 && threadIdx.y != regionHeight - 1)
	{
		// takes pixel value compares with neighbours
		getCoocMatrixGrayGPU(cuda_intensity_image, image_ind_x, image_ind_y, w, h, regionWidth, regionHeight, sharedCoocRegion, 
							averageCluster, maxDist, coDIMX, coDIMY, coDIMZ, bFASTCOOC);
	}

	__syncthreads();

	// loop though coocurance matrices and get score
	float local_score = 0.0;
		
	// in the case of sharedCooc having bigger dimensions than the block size
	// zero remaining part of memory
	if (tid == 0)
		shared_score = 0.0;
	
	for (int i = tid; i < cN; i += blockSize)
	{
		if(i != 0)
			local_score += fmin(coMatrixTarget[i], sharedCoocRegion[i]/sharedCoocRegion[0]);	// minimum intersection
	}

	if (local_score>0)
		atomicAdd(&shared_score, local_score);

	__syncthreads();

	// label image region with score

	if (image_ind_x < w && image_ind_y < h)
	{
		atomicAdd(&scoreImage[image_ind_x + image_ind_y*w], shared_score);

		//scoreImage[image_ind_x + image_ind_y*w] = threadIdx.x;

		atomicAdd(&countImage[image_ind_x + image_ind_y*w], 1);

		//printf("%f ", scoreImage[image_ind_x + image_ind_y*w]);
	}
	
	//////////////////////////////// sum check /////////////////////////////////////
	atomicAdd(ct, 1);
}

/*

cudaChannelFormatDesc channelDesc = cudaCreateChannelDesc(8*sizeof(int), 0, 0, 0, cudaChannelFormatKindSigned);

cudaArray* cuArray;
cudaMallocArray(&cuArray, &channelDesc, w_d, h_d);

checkCudaErrors(cudaMemcpyToArray(cuArray, 0, 0, intensityImage,  N*sizeof(int), cudaMemcpyHostToDevice));

cuda_texture_image.addressMode[0] = cudaAddressModeClamp;
cuda_texture_image.addressMode[1] = cudaAddressModeClamp;
cuda_texture_image.filterMode = cudaFilterModePoint;
cuda_texture_image.normalized = false;

// bind texture to image
checkCudaErrors(cudaBindTextureToArray(cuda_texture_image, cuArray, channelDesc));
*/

bool cudaScore::setupCudaDevice(cudaDeviceProp* deviceProp, int &devID, dim3 gridSize, dim3 blockSize, size_t sharedMemBytes)
{
	cudaError_t error = cudaGetDevice(&devID);

	if (error != cudaSuccess)
	{
		DBOUT("cudaGetDevice returned error " << cudaGetErrorString(error) << " :" << error << " line=" << __LINE__ << std::endl);
		return false;
	}

	error = cudaGetDeviceProperties(deviceProp, devID);

	if (error != cudaSuccess)
	{
		DBOUT("cudaGetDeviceProperties returned error " << cudaGetErrorString(error) << " :" << error << " line=" << __LINE__ << std::endl);
		return false;
	}
	
	if (deviceProp->computeMode == cudaComputeModeProhibited)
	{
		DBOUT("Error: device is running in <Compute Mode Prohibited>, no threads can use ::cudaSetDevice().\n");
		return false;
	}

	DBOUT("GPU Device " << devID << " - " << deviceProp->name << " with compute capability major=" << deviceProp->major << " minor=" << deviceProp->minor << std::endl);

	const int kb = 1024;
	DBOUT("  Shared memory per block: " << (int)deviceProp->sharedMemPerBlock / kb << " MB , " << (int)deviceProp->sharedMemPerBlock << " bytes" << std::endl);
	DBOUT("  Constant memory: " << (int)deviceProp->totalConstMem / kb << " MB" << std::endl);
	DBOUT("  Registers per Block: " << deviceProp->regsPerBlock << std::endl);
	DBOUT("  Warp size:        " << deviceProp->warpSize << std::endl);
	DBOUT("  Maximum Threads per block: " << deviceProp->maxThreadsPerBlock << std::endl);
	DBOUT("  Max block dimensions: " << deviceProp->maxThreadsDim[0] << ", " << deviceProp->maxThreadsDim[1] << ", " << deviceProp->maxThreadsDim[2] << std::endl);
	DBOUT("  Max grid dimensions:  " << deviceProp->maxGridSize[0] << ", " << deviceProp->maxGridSize[1] << ", " << deviceProp->maxGridSize[2] << std::endl);

	DBOUT("Requested resources: " << "gridSize.x=" << gridSize.x << " gridSize.y=" << gridSize.y << " blockSize.x=" << blockSize.x << " blockSize.y=" << blockSize.y
		<< " sharedMemory=" << (int)sharedMemBytes / kb << " MB, " << (int)sharedMemBytes << " bytes" << std::endl);

	return true;
}

bool cudaScore::FindTargets(int* detectionImage, float* scoreImage, int width, int height, COOCMatrix* coocTraining,
							bool bIntensityImage, bool bCrossEntropy, bool bFASTCOOC)
{
	// scan test image calculate intersection value save value to image
	size_t CoocSize = coocTraining->coDIMX*coocTraining->coDIMY*coocTraining->coDIMZ;

	if(bFASTCOOC)
		CoocSize = coocTraining->coDIMX*coocTraining->coDIMY;	// 2D matrix

	dim3 gridSize(((width + coocTraining->incrementWidth - 1) / coocTraining->incrementWidth), (height + coocTraining->incrementHeight - 1) / coocTraining->incrementHeight);
	dim3 blockSize(coocTraining->regionWidth, coocTraining->regionHeight);
	//size_t regionSizeBytes = regionWidth*regionHeight * sizeof(int);
	size_t CoocSizeBytes = CoocSize * sizeof(float);
	size_t sharedMemBytes = CoocSizeBytes;

	int devID =0;
	int count=0, *dev_count;
	cudaMalloc((void **)&dev_count, sizeof(int));
	cudaMemcpy(dev_count, &count, sizeof(int), cudaMemcpyHostToDevice);

	cudaError_t error;
	cudaDeviceProp deviceProp;
	int N = width*height;

	if (!setupCudaDevice(&deviceProp, devID, gridSize, blockSize, sharedMemBytes))
		return false;

	//checkCudaErrors(cudaMemcpy(cuda_intensity_image, intensityImage, w_d * h_d * sizeof(int), cudaMemcpyHostToDevice));
	if(bIntensityImage) {
		checkCudaErrors(cudaMemcpy(cuda_target_cooc, coocTraining->coMatrixIntensity, CoocSize * sizeof(float), cudaMemcpyHostToDevice));
	}
	else {
		checkCudaErrors(cudaMemcpy(cuda_target_cooc, coocTraining->coMatrixHue, CoocSize * sizeof(float), cudaMemcpyHostToDevice));
	}

	mycudaMemsetFloat << < (N + 255) / 256, 256 >> > (cuda_score_image, N);
	mycudaMemsetInt << < (N + 255) / 256, 256 >> > (cuda_score_count_image, N);

	checkCudaErrors(cudaMemcpy(cuda_intensity_image, detectionImage, width * height * sizeof(int), cudaMemcpyHostToDevice));

	float maxDist = sqrtf(coocTraining->regionWidth*coocTraining->regionWidth + coocTraining->regionHeight*coocTraining->regionHeight);

	scoreTargetsGPU <<< gridSize, blockSize, sharedMemBytes >>>(cuda_intensity_image, width, height, 
																coocTraining->regionWidth, coocTraining->regionHeight, 
																coocTraining->incrementWidth, coocTraining->incrementHeight,
																cuda_target_cooc, cuda_score_image, cuda_score_count_image, maxDist, 
																coocTraining->coDIMX, coocTraining->coDIMY, coocTraining->coDIMZ, 
																coocTraining->averageIntensity, dev_count, bCrossEntropy, bFASTCOOC); // gpu

	//cudaDestroyTextureObject(cuda_texture_image);
	//cudaFreeArray(cuArray);

	cudaMemcpy(&count, dev_count, sizeof(int), cudaMemcpyDeviceToHost);

	cudaFree(dev_count);

	if (count != gridSize.x*gridSize.y*blockSize.x*blockSize.y)
	{
		DBOUT("ERROR: total number of threads executed: " << count << " != " << gridSize.x*gridSize.y*blockSize.x*blockSize.y << std::endl);
		return false;
	}
	else
	{
		DBOUT("Score image created sucessfully"<< std::endl);

		checkCudaErrors(cudaPeekAtLastError());

		float* scoreImageTemp = new float[width*height];
		int* scoreCountImage = new int[width*height];

		checkCudaErrors(cudaMemcpy(scoreImageTemp, cuda_score_image, width*height*sizeof(float), cudaMemcpyDeviceToHost));
		checkCudaErrors(cudaMemcpy(scoreCountImage, cuda_score_count_image, width*height*sizeof(int), cudaMemcpyDeviceToHost));

		for (int i = 0; i < width*height; i++)
			scoreImage[i] = scoreImageTemp[i] / ((float)scoreCountImage[i]);

		delete[] scoreImageTemp;
	}
	
	return true;
}

/*
cv::Mat cudaScore::FindTargets::detectLawsTextureFeatures(cv::Mat detectionImage, QVector<cv::Mat> lawsHistTarget, QVector<float> biases)
{
	int regionSize = 10;
	int histRange = 128;
	int histSize = 10;

	// now get detection 
	cv::Mat im, scoreImage(detectionImage.rows, detectionImage.cols, CV_32FC1);

	// now filter detect image and compare histograms of regions of the image
	cv::cvtColor(detectionImage, im, CV_BGR2GRAY, 1);

	cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE(2.0);
	clahe->apply(im, im);

	im.convertTo(im, CV_32FC1);

	QMap<QString, cv::Mat> lawsMapDetect = getLawFilteredImages(im);

	QVector<cv::Mat> lawsHistDetect;

	for (int c = 0; c < 8; c++)
		lawsHistDetect.append(cv::Mat());

	// but this has to be on regions of the detection image
	for (int i = 0; i < im.cols; i += regionSize)
		for (int j = 0; j < im.rows; j += regionSize)
		{
			int regionSizeI = regionSize;
			int regionSizeJ = regionSize;

			if (i + regionSize >= im.cols)
				regionSizeI = im.cols - i;
			if (j + regionSize >= im.rows)
				regionSizeJ = im.rows - j;

			// get histograms in this region of the image
			cv::Rect roi(i, j, regionSizeI, regionSizeJ);

			addHistogram(lawsHistDetect[0], lawsMapDetect["im_SS"](roi), cv::Mat(), cv::Mat(), cv::Mat(), histSize, histRange, false);
			addHistogram(lawsHistDetect[1], lawsMapDetect["im_RR"](roi), cv::Mat(), cv::Mat(), cv::Mat(), histSize, histRange, false);
			addHistogram(lawsHistDetect[2], lawsMapDetect["im_LS"](roi), lawsMapDetect["im_SL"](roi), cv::Mat(), cv::Mat(), histSize, histRange, false);
			addHistogram(lawsHistDetect[3], lawsMapDetect["im_SR"](roi), lawsMapDetect["im_RS"](roi), cv::Mat(), cv::Mat(), histSize, histRange, false);
			addHistogram(lawsHistDetect[4], lawsMapDetect["im_EE"](roi), lawsMapDetect["im_EER"](roi), cv::Mat(), cv::Mat(), histSize, histRange, false);
			addHistogram(lawsHistDetect[5], lawsMapDetect["im_EL"](roi), lawsMapDetect["im_LE"](roi), lawsMapDetect["im_LER"](roi), lawsMapDetect["im_ERL"](roi), histSize, histRange, false);
			addHistogram(lawsHistDetect[6], lawsMapDetect["im_ES"](roi), lawsMapDetect["im_SE"](roi), lawsMapDetect["im_SER"](roi), lawsMapDetect["im_ERS"](roi), histSize, histRange, false);
			addHistogram(lawsHistDetect[7], lawsMapDetect["im_ER"](roi), lawsMapDetect["im_RE"](roi), lawsMapDetect["im_RER"](roi), lawsMapDetect["im_ERR"](roi), histSize, histRange, false);

			//score detect region using target histogram	
			float s = scoreLawsHistogram(lawsHistDetect, lawsHistTarget, biases);

			for (int k = i; k < i + regionSizeI; k++)
				for (int l = j; l < j + regionSizeJ; l++)
				{
					scoreImage.at<float>(l, k) = s;
				}
		}

	// create greyscale image of score
	cv::Mat sim = HelperFunctions::convertFloatToGreyscaleMat(scoreImage);

	return sim;
}
*/