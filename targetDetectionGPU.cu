#include "device_launch_parameters.h"

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string.h>
#include <stdlib.h>
#include "math.h"
#include "targetDetectionGPU.cuh"
#include "globals.h"

texture<int, cudaTextureType2D, cudaReadModeElementType> cuda_texture_image;

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

template<class T>
__global__
void mycudaMemset(T* image, int n)
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
void getCoocMatrixGrayGPU(int image_ind_x, int image_ind_y, int width, int height, 
						int regionWidth, int regionHeight, int* coMatrixRegion, int coDIMX, int coDIMY, int coDIMZ)	
{
	int local_sum = 0;
	int pixel_index = image_ind_x + image_ind_y*width;

	if (threadIdx.x < regionWidth && threadIdx.y < regionHeight)
	{
		int c1 = tex2D(cuda_texture_image, image_ind_x, image_ind_y); // pImage[threadIdx.x + threadIdx.y * regionWidth];

		if (c1 >= 0)
		{
			int nextIndex = 1 + threadIdx.x + threadIdx.y*regionWidth;

			int nextJ = nextIndex / regionWidth;
			int nextI = nextIndex % regionWidth;

			//printf("rw=%d rh=%d\n", regionWidth, regionHeight);

			// check against all others
			for (int y = nextJ; y < regionHeight; y++)
				for (int x = nextI; x < regionWidth; x++)
				{
					if (image_ind_x + x < width && image_ind_y + y < height)
					{
						int c2 = tex2D(cuda_texture_image, image_ind_x + x, image_ind_y + y);  //pImage[x + y*regionWidth];

						if (c2 >= 0)
						{
							int ind = c1 + coDIMX * (c2 + coDIMY * MAX(x, y));

							if (ind < coDIMX*coDIMY*coDIMZ)
							{
								atomicAdd(&coMatrixRegion[ind], 1);
								atomicAdd(&coMatrixRegion[0], 1);	// not needed, can be precomputed as n*(n-1)/2
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
void scoreTargetsGPU(int w, int h, int regionWidth, int regionHeight, int increment_W, int increment_H,
					float* coMatrixTarget, float* scoreImage, int* countImage, int coDIMX, int coDIMY, 
					int coDIMZ, int* ct, bool bCrossEntropy)
{
	__shared__ int shared_count;
	__shared__ float shared_score;

	extern __shared__ int sh[];
	int* sharedCoocRegion = sh;
	//int* sharedCoocRegion = (int*)sh + regionWidth*regionHeight;

	// index into image and sub tile
	int image_ind_x = blockIdx.x*increment_W + threadIdx.x;
	int image_ind_y = blockIdx.y*increment_H + threadIdx.y;

	// zero shared memory
	int tid = threadIdx.y*blockDim.x + threadIdx.x;			// get linear thread index
	int cN = coDIMX*coDIMY*coDIMZ;
	int blockSize = blockDim.x * blockDim.y;

	// in the case of sharedCooc having bigger dimensions than the block size
	// zero remaining part of memory
	if (tid == 0)
	{
		shared_count = 0;
		shared_score = 0.0;
	}

	// zero co-occurrence matrix using parralel threads
	for(int i=tid; i<cN; i += blockSize)
		sharedCoocRegion[i] = 0;
/*
	// copy image region into into shared tile memory
	if (image_ind_x < w && image_ind_y < h)
		sharedTile[threadIdx.x + threadIdx.y*regionWidth] = tex2D(cuda_texture_image, image_ind_x, image_ind_y);
	else
		sharedTile[threadIdx.x + threadIdx.y*regionWidth] = -1;
*/
	__syncthreads();

	// create the coocurrence matrices

	// last data point has nothing to check against
	if (threadIdx.x != regionHeight - 1 && threadIdx.y != regionHeight - 1)
	{
		// takes pixel value compares with neighbours
		getCoocMatrixGrayGPU(image_ind_x, image_ind_y, w, h, regionWidth, regionHeight, sharedCoocRegion, coDIMX, coDIMY, coDIMZ);
	}

	__syncthreads();

	// loop though coocurance matrices and get score
	float local_score = 0.0;

	for (int i = tid; i < cN; i += blockSize)
	{
		float score_test = coMatrixTarget[i];
		float score_train = float(sharedCoocRegion[i]) / float(sharedCoocRegion[0]);
		local_score += sqrt(score_test*score_train);
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

template<class T>
__global__
void cudaEnergy(T* image, int w, int h, double* dev_score)
{
	int i = (blockIdx.y * blockDim.y + threadIdx.y);
	int j = (blockIdx.x * blockDim.x + threadIdx.x);

	// Test to see if we're testing a valid pixel
	if (i < w && j < h)
	{
		int diff1 = 0, diff2 = 0;

		int val1 = image[i + j*w];

		if ((i + 1) < w)
			diff1 = val1 - image[(i + 1) + j*w];

		if ((j + 1) < h)
			diff2 = val1 - image[i + (j + 1)*w];
		
		atomicAdd(dev_score, (double)diff1*diff1 + diff2*diff2);
	}
}


double getFocusScore(int* image, int w, int h)
{
	double score = 0, *cuda_score;
	int N = w*h;
	int n2 = ceil(w / 2.0) * ceil(h / 2.0);
	dim3 gridSize(32, 16);
	dim3 blockSize(32, n2/32*32*16);

	int* cuda_image;

	cudaMalloc((void **)&cuda_score, sizeof(double));
	cudaMemcpy(cuda_score, &score, sizeof(double), cudaMemcpyHostToDevice);

	// allocate image
	cudaMalloc(&cuda_image, w * h * sizeof(int));

	// copy image to cuda image
	checkCudaErrors(cudaMemcpy(cuda_image, image, w*h*sizeof(int), cudaMemcpyDeviceToHost));
	
	cudaEnergy <<< blockSize, gridSize >>> (cuda_image, w, h, cuda_score);

	cudaMemcpy(&score, cuda_score, sizeof(double), cudaMemcpyDeviceToHost);

	cudaFree(cuda_image);
	cudaFree(cuda_score);

	return score;
}

bool cudaScore::FindTargets(int* intensityImage, float* scoreImage, int w_d, int h_d, int regionWidth, int regionHeight, int increment_W, int increment_H, 
							float* coMatrixTarget, int coDIMX, int coDIMY, int coDIMZ, bool bCrossEntropy)
{
	// scan test image calculate intersection value save value to image
	size_t CoocSize = coDIMX*coDIMY*coDIMZ;

	dim3 gridSize(((w_d + increment_W - 1) / increment_W), (h_d + increment_H - 1) / increment_H);
	dim3 blockSize(regionWidth, regionHeight);
	//size_t regionSizeBytes = regionWidth*regionHeight * sizeof(int);
	size_t CoocSizeBytes = CoocSize * sizeof(float);
	size_t sharedMemBytes = CoocSizeBytes;

	int devID =0;
	int count=0, *dev_count;
	cudaMalloc((void **)&dev_count, sizeof(int));
	cudaMemcpy(dev_count, &count, sizeof(int), cudaMemcpyHostToDevice);

	cudaError_t error;
	cudaDeviceProp deviceProp;
	int N = w_d*h_d;

	error = cudaGetDevice(&devID);

	if (error != cudaSuccess)
	{
		DBOUT("cudaGetDevice returned error " << cudaGetErrorString(error) << " :" << error << " line=" << __LINE__ << std::endl);
		return false;
	}

	error = cudaGetDeviceProperties(&deviceProp, devID);

	if (deviceProp.computeMode == cudaComputeModeProhibited)
	{
		DBOUT("Error: device is running in <Compute Mode Prohibited>, no threads can use ::cudaSetDevice().\n");
		return false;
	}

	if (error != cudaSuccess)
	{
		DBOUT("cudaGetDeviceProperties returned error " << cudaGetErrorString(error) << ", code=" << error << " line=" << __LINE__ << std::endl);
		return false;
	}
	else
	{
		DBOUT("GPU Device " << devID << " - " << deviceProp.name << " with compute capability major=" << deviceProp.major << " minor=" << deviceProp.minor << std::endl);

		const int kb = 1024;
		DBOUT("  Shared memory: "<< (int)deviceProp.sharedMemPerBlock / kb << " MB" << std::endl);
		DBOUT("  Constant memory: "<< (int)deviceProp.totalConstMem / kb << " MB" << std::endl);
		DBOUT("  Block registers: "<< deviceProp.regsPerBlock << std::endl);
		DBOUT("  Warp size:        "<< deviceProp.warpSize << std::endl);
		DBOUT("  Threads per block: "<< deviceProp.maxThreadsPerBlock << std::endl);
		DBOUT("  Max block dimensions: "<< deviceProp.maxThreadsDim[0] << ", " << deviceProp.maxThreadsDim[1] << ", " << deviceProp.maxThreadsDim[2] << std::endl);
		DBOUT("  Max grid dimensions:  "<< deviceProp.maxGridSize[0] << ", " << deviceProp.maxGridSize[1] << ", " << deviceProp.maxGridSize[2] << std::endl);

		DBOUT("Requested resources: " << "gridSize.x=" << gridSize.x << " gridSize.y=" << gridSize.y << " blockSize.x="<< blockSize.x <<" blockSize.y="<<blockSize.y << " sharedMemory="<< (int)sharedMemBytes / kb << " MB" << std::endl);
	}

	//checkCudaErrors(cudaMemcpy(cuda_intensity_image, intensityImage, w_d * h_d * sizeof(int), cudaMemcpyHostToDevice));
	checkCudaErrors(cudaMemcpy(cuda_target_cooc, coMatrixTarget, CoocSize * sizeof(float), cudaMemcpyHostToDevice));

	mycudaMemset << < (N + 255) / 256, 256 >> > (cuda_score_image, N);
	mycudaMemset << < (N + 255) / 256, 256 >> > (cuda_score_count_image, N);

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

	scoreTargetsGPU << < gridSize, blockSize, sharedMemBytes >> > (w_d, h_d, regionWidth, regionHeight, increment_W, increment_H,
		cuda_target_cooc, cuda_score_image, cuda_score_count_image, coDIMX, coDIMY, coDIMZ, dev_count, bCrossEntropy); // gpu

	//cudaDestroyTextureObject(cuda_texture_image);
	//cudaFreeArray(cuArray);

	cudaMemcpy(&count, dev_count, sizeof(int), cudaMemcpyDeviceToHost);

	cudaFreeArray(cuArray);
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

		float* scoreImageTemp = new float[w_d*h_d];
		int* scoreCountImage = new int[w_d*h_d];

		checkCudaErrors(cudaMemcpy(scoreImageTemp, cuda_score_image, w_d*h_d * sizeof(float), cudaMemcpyDeviceToHost));
		checkCudaErrors(cudaMemcpy(scoreCountImage, cuda_score_count_image, w_d*h_d * sizeof(int), cudaMemcpyDeviceToHost));

		for (int i = 0; i < w_d*h_d; i++)
			scoreImage[i] = scoreImageTemp[i] / ((float)scoreCountImage[i]);

		delete[] scoreImageTemp;
	}
	
	return true;
}




