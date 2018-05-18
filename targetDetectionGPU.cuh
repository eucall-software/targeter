/* 
 * File:   targetDetectionGPU.h
 * Author: dave
 *
 * Created on August 31, 2017, 1:08 PM
 */
#ifndef TARGETDETECTIONGPU_H
#define	TARGETDETECTIONGPU_H

#include <cuda_runtime.h>

#ifdef	__cplusplus
extern "C" {
#endif

double getFocusScore(int* image, int w, int h);

class cudaScore {
public:

    cudaScore(int w_d, int h_d, int CoocSize);
    ~cudaScore();

	// int getCoocMatrixGrayGPU(int* pImage, int w, int h, int startX, int startY, int regionWidth, int regionHeight, int* coMatrix, int NoClusters, int maxD);
	bool FindTargets(int* detectionImage, float* scoreImage, int w_d, int h_d, int regionWidth, int regionHeight, int increment_W, int increment_H, 
	float* coMatrixTarget, int coDIMX, int coDIMY, int coDIMZ, bool bCrossEntropy);
	// float* scoreTargetsGPU(int* detectionImage, int w, int h, int regionWidth, int regionHeight, float* coMatrixTestF, int NoClusters, int maxD, bool bCrossEntropy);
	 
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

