#include <iomanip>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include "focusingCUDA.h"

#define checkCudaErrors(err) { __checkCudaErrors((err), __FILE__, __LINE__); }
inline void __checkCudaErrors(cudaError_t err, const char *file, int line)
{
	if (err != cudaSuccess)
	{
		const char* es = cudaGetErrorString(err);

		DBOUT("file=" << (int)file << " line= " << line << " CUDA Runtime API error (" << (int)err << ")" << es << std::endl);
	}
}

__global__
void cudaEnergy(int* image, int w, int h, int* dev_score)
{
	uint i = (blockIdx.x * blockDim.x) + threadIdx.x;
	uint j = (blockIdx.y * blockDim.y) + threadIdx.y;

	//printf("i=%d j=%d v=", i, j);

	// Test to see if we're testing a valid pixel
	if (i < w && j < h)
	{
		int diff1 = 0, diff2 = 0;

		int val1 = image[i + j*w];

		printf("%d\n", val1);

		if ((i + 1) < w)
			diff1 = val1 - image[(i + 1) + j*w];

		if ((j + 1) < h)
			diff2 = val1 - image[i + (j + 1)*w];

		int ssq = abs(diff1) + abs(diff2);	// rms

		atomicAdd(dev_score, ssq);
	}
}

int* getCImage(const cv::Mat& img) // returns true if the given 3 channel image is B = G = R
{
	int* im = new int[img.rows*img.cols];

	for (int j = 0; j < img.rows; j++)
	{
		for (int i = 0; i < img.cols; i++)
		{
			cv::Vec3b val = img.at<cv::Vec3b>(j, i);

			im[i + j*img.cols] = (int)val[0] * 0.114 + val[1] * 0.587 + val[2] * 0.299;
		}
	}
	return im;
}

void focusingCUDA::getFocusScore(FocusResult& res)
{
	int score = 0, *cuda_score;
	
	int w = res.focusImage.cols, int h = res.focusImage.rows;
	int N = w*h;

	dim3 threadsPerBlock(8, 8);
	dim3 numBlocks(w/threadsPerBlock.x, h/threadsPerBlock.y);

	int* image = getCImage(res.focusImage);
	int* cuda_image;

	cudaMalloc((void **)&cuda_score, sizeof(int));
	checkCudaErrors(cudaMemcpy(cuda_score, &score, sizeof(int), cudaMemcpyHostToDevice));

	// allocate image
	cudaMalloc(&cuda_image, w * h * sizeof(int));

	// copy image to cuda image
	checkCudaErrors(cudaMemcpy(cuda_image, image, w * h * sizeof(int), cudaMemcpyHostToDevice));

	printf("in cuda function\n");

	// call cuda function
	cudaEnergy << < numBlocks, threadsPerBlock >> > (cuda_image, w, h, cuda_score);

	checkCudaErrors(cudaMemcpy(&score, cuda_score, sizeof(int), cudaMemcpyDeviceToHost));

	cudaFree(cuda_image);
	cudaFree(cuda_score);

	if(image != nullptr)
		delete[] image;

	res.focusValue = score;

	//emit setFOCUS(res);
}

