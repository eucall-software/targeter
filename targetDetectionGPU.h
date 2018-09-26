/* 
 * File:   targetDetectionGPU.h
 * Author: dave
 *
 * Created on August 31, 2017, 1:08 PM
 */

#ifndef TARGETDETECTIONGPU_H
#define	TARGETDETECTIONGPU_H

#include "device_launch_parameters.h"
#include "globals.h"

#ifdef	__cplusplus
extern "C" {
#endif

class cudaScore {
public:

    cudaScore(int w_d, int h_d, int CoocSize);
    ~cudaScore();

   // int getCoocMatrixGrayGPU(int* pImage, int w, int h, int startX, int startY, int regionWidth, int regionHeight, int* coMatrix, int NoClusters, int maxD);
   bool FindTargets(int* detectionImage, float* scoreImage, int width, int height, COOCMatrix* coocTraining, 
					bool bIntensityImage= true, bool bCrossEntropy = false, bool bFASTCOOC = false);
   // float* scoreTargetsGPU(int* detectionImage, int w, int h, int regionWidth, int regionHeight, float* coMatrixTestF, int NoClusters, int maxD, bool bCrossEntropy);
   
   void haar(float input[], float output[], int o_width, int o_height, int levels);
   void haar2d_gpu(float* input, int size, int levels);

   bool setupCudaDevice(cudaDeviceProp* deviceProp, int &devID, dim3 gridSize, dim3 blockSize, size_t sharedMemBytes);
//variables
    int* cuda_intensity_image;
    float* cuda_target_cooc;
    float* cuda_score_image;
	int* cuda_score_count_image;
};

#ifdef	__cplusplus
}
#endif

#endif	/* TARGETDETECTIONGPU_H */

