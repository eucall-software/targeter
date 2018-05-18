// Targeter - target identification software for EUCALL workpackage 6
// Licensed under the GPL License. See LICENSE file in the project root for full license information.
// Copyright(C) 2017  David Watts 

#ifndef FINDTARGETS_H
#define FINDTARGETS_H

#include "opencv2/opencv.hpp"
#include "opencv/highgui.h"
#include "Settings.h"
#include "targeterimage.h"
#include <vector>

class MainWindow;

using namespace std;

class FindTargets : public QObject
{
	Q_OBJECT
public:
	cv::Mat ColourOccuranceHistogram(std::vector<targeterImage>& trainingImages, targeterImage& detectionImage, int distance, int NoClusters, bool bCrossEntropy = false);
	cv::Mat LaplacianFindObject(std::vector<targeterImage>& trainingImages, targeterImage& detectionImage, int distance, int NoClusters);

	float* ProcessScoreImage(float* scoreImage, int w, int h, cv::Size targetSize, int maxD, int scoreAreaFactor, int ScoreThresholdPercent);

	cv::Mat CVMatching(std::vector<targeterImage>& trainingImages, targeterImage& detectionImage, algoType::algoType matchType);
	int* HSVHist(targeterImage& detectionImage, const cv::Mat* pchannel, int NoClusters, imageType::imageType imType);

	//float getCoocMatrix(targeterImage& m, int* pMask, drawingMode::drawingMode maskType, int startX, int startY, int regionWidth, int regionHeight, float* coMatrixF, int NoClusters, int maxD);
	float getCoocMatrixGray(targeterImage& m, int* pMask, drawingMode::drawingMode maskType, int startX, int startY, int regionWidth, int regionHeight, 
		float* coMatrixF, int coDIMX, int coDIMY, int coDIMZ);
	float getCoocMatrixHSV2(int* pImage, int* pHue, int w, int h, int* pMask, drawingMode::drawingMode maskType, int startX, int startY, 
							int regionWidth, int regionHeight, float* coMatrixImage, float* coMatrixHue, int coDIMX, int coDIMY, int coDIMZ);

	void getCoocuranceHistogram(targeterImage& m, float* coMatrixIntensity, float* coMatrixHue, int regionWidth, int regionHeight, int inc_W, int inc_H, int coDIMX, int coDIMY, int coDIMZ);

	float* findTargets(targeterImage& detectionImage, int regionWidth, int regionHeight, int inc_W, int inc_H, 
						float* coMatrixIntensity_Target, float* coMatrixHue_Target, int coDIMX, int coDIMY, int coDIMZ, bool bCrossEntropy = false);

	void HistogramClusteringGray(targeterImage& detectionImage, int NoClusters, int** clusterHist);
	void HistogramClusteringHSV(targeterImage& detectionImage, int NoClusters, int** clusterHistHue, int** clusterHistIntensity);

	void labelTrainingImagesGray(std::vector<targeterImage>& TrainImages, int* pClusterHist);
	void labelTrainingImagesHSV(std::vector<targeterImage>& TrainImages, int* pClusterHistHue, int* pClusterHistIntensity);

	//int* histClusterRGBImage(cv::Mat hueHist, int histSize);
	std::vector<int*> kMeansRGB(cv::Mat img, std::vector<cv::Mat> testImgs, int NoClusters, int maxIterations);
	//int* histEntropyClusterRGBImage(cv::Mat hueHist, int histSize, int NoClusters);
	int* histClusterEqual(cv::Mat hueHist, int histSize, int NoClusters);

	template<typename T>
	void printVector(const T& t);
	template<typename T>
	void printClusterVector(std::vector<T> cluster);
	template<typename T>
	void printCoocuranceHistogram(T* hist, int dim1, int dim2, int dim3, int nDim3 = 1);

signals:
	void LOGCONSOLE(QString strText, QString strIcon = "Information");
};

#endif // FINDTARGETS_H