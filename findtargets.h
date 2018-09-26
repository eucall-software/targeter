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

	cv::Mat LaplacianFindObject(QVector<QExplicitlySharedDataPointer<targeterImage>> trainingImages, QExplicitlySharedDataPointer<targeterImage> detectionImage, int distance, int NoClusters);

	float* ProcessScoreImage(float* scoreImage, int w, int h, cv::Size targetSize, int maxD, int scoreAreaFactor, int ScoreThresholdPercent);

	cv::Mat CVMatching(QVector<QExplicitlySharedDataPointer<targeterImage>> trainingImages, QExplicitlySharedDataPointer<targeterImage> detectionImage, algoType::algoType matchType, bool bCorrectBackground = false);
	
	void findTargets(int* intensityImage, int* hueImage, float* scoreImage, int w_d, int h_d, COOCMatrix* coocTarget, bool bCrossEntropy = false, bool bProcessGrayscale = false);
	
	////////////////////////////// colour concurrence histograms /////////////////////////////////////////////////////////////////////

	cv::Mat ColourOccuranceHistogram(QVector<QExplicitlySharedDataPointer<targeterImage>>& trainingImages, 
									QExplicitlySharedDataPointer<targeterImage>& detectionImage, COOCMatrix* coocTraining, 
									int regionDistance, int distanceBins, int NoClusters, bool bCrossEntropy = false, 
									bool bProcessGrayscale = true, bool bFASTCOOC = false, bool bCorrectBackground = false);
	void trainColourOccuranceHistogram(QVector<QExplicitlySharedDataPointer<targeterImage>>& trainingImages,
									   QExplicitlySharedDataPointer<targeterImage>& detectionImage, COOCMatrix* coocTraining,
									   int regionDistance, int distanceBins, int NoClusters, bool bCrossEntropy = false, 
									   bool bProcessGrayscale = false, bool bFASTCOOC = false);
	
	cv::Mat detectCOOCHistogram(cv::Mat detectionImage, COOCMatrix* coocTraining, bool bCrossEntropy = false, 
								bool bProcessGrayscale = true, bool bFASTCOOC=false, bool bCorrectBackground = false);

	void labelTrainingImagesGray(const QVector<QExplicitlySharedDataPointer<targeterImage>>& TrainImages, int* pClusterHistIntensity);
	void labelTrainingImagesHSV(const QVector<QExplicitlySharedDataPointer<targeterImage>>& TrainImages, int* pClusterHistIntensity, int* pClusterHistHue);
	void initialiseCOOCMatrix(COOCMatrix* cooc, int w, int h, int regionDistance, int distanceBins, int NoClusters, bool bFASTCOOC = false);
	void getCoocuranceHistogram(int* pImage, int* pHue, int* mask, drawingMode::drawingMode maskType, int w, int h, COOCMatrix* cooc, 
								bool bProcessGrayscale = true, bool isGrayScale = false, bool bFASTCOOC = false);
	
	void HistogramClustering(cv::Mat im, COOCMatrix* cooc, int* clusterImageIntensity, int* clusterImageHue,
							int histSizeIntensity, int histSizeHue, int NoClusters, bool bProcessGrayscale, bool imageIsGray);

	int HistogramClusterImage(cv::Mat hist, const cv::Mat* pchannel, int* pClusterImage, int histSize, int NoCluster);

	float getCoocMatrixGray(int* im, int w, int h, int* pMask, drawingMode::drawingMode maskType, int startX, int startY, 
							COOCMatrix* cooc, bool bFASTCOOC = false);
	float getCoocMatrixHSV(int* pImage, int* pHue, int w, int h, int* pMask, drawingMode::drawingMode maskType, int startX, int startY, 
							COOCMatrix* cooc, bool bFASTCOOC = false);

	std::vector<int*> kMeansRGB(cv::Mat img, QVector<cv::Mat> testImgs, int NoClusters, int maxIterations);
	
	int* histClusterEqual(cv::Mat hueHist, int histSize, int NoClusters);

	//float getCoocMatrix(QExplicitlySharedDataPointer<targeterImage> m, int* pMask, drawingMode::drawingMode maskType, int startX, int startY, int regionWidth, int regionHeight, float* coMatrixF, int NoClusters, int maxD);
	//int* histEntropyClusterRGBImage(cv::Mat hueHist, int histSize, int NoClusters);
	//int* histClusterRGBImage(cv::Mat hueHist, int histSize);

	///////////////////////////// laws texture features /////////////////////////////////////////////////////////////////////////////////

	cv::Mat lawsTextureFeatures(QVector<QExplicitlySharedDataPointer<targeterImage>> trainingImages, QExplicitlySharedDataPointer<targeterImage> detectionImage, bool bCorrectBackground = false);
	void trainLawsTextureFeatures(QVector<QExplicitlySharedDataPointer<targeterImage>> trainingImages, QVector<cv::Mat>& lawsHistTarget, QVector<float>& lawsHistBiases);
	QMap<QString, cv::Mat> getLawFilteredImages(cv::Mat im);
	void getLawFilterHistograms(cv::Mat im, QVector<cv::Mat>& lawsHistTarget, int histSize=10, int histRange=128, bool bAccumulateHistograms = false);
	cv::Mat detectLawsTextureFeatures(cv::Mat detectionImage, QVector<cv::Mat> lawsHistTarget, QVector<float> biases, bool bCorrectBackground = false);
	double scoreLawsHistogram(QVector<cv::Mat> lawsMapDetect, QVector<cv::Mat> lawsHistTarget, QVector<float> biases);
	void addHistogram(cv::Mat& hist, cv::Mat aim, cv::Mat bim, cv::Mat cim, cv::Mat dim, int noBins, int histrange, bool append);
	void getHistogramWeights(QVector<cv::Mat> hists, QVector<float>& biases);
	void getHistogram(cv::Mat input, cv::Mat& histogram, int noBins, int histrange, bool append);
	void sepConvolve(const cv::Mat image, cv::Mat& spResult, const float Kernel[/* KernelLen */], int KernelLen, bool bRow);
	void getLawFilterHistograms(QVector<cv::Mat>& lawsHist, QMap<QString, cv::Mat> lawsMap, cv::Rect roi, int histSize, int histRange, bool bAccumulateHistograms);


	cv::Mat HaarHistogram(QVector<QExplicitlySharedDataPointer<targeterImage>> trainingImages, QExplicitlySharedDataPointer<targeterImage> detectionImage, int distance, int NoClusters, bool bProcessGrayscale = false);
	bool FindTargetsHaar(QVector<QExplicitlySharedDataPointer<targeterImage>> trainingImages,
						 QExplicitlySharedDataPointer<targeterImage> detectionImage, int levels);


	int getNextPower2(QVector<QExplicitlySharedDataPointer<targeterImage>> trainingImages);

	template<typename T>
	void printVector(const T& t);
	template<typename T>
	void printClusterVector(QVector<T> cluster);
	template<typename T> static
	void printCoocuranceHistogram(T* hist, int dim1, int dim2, int dim3, int nDim3 = 1);

signals:
	void LOGCONSOLE(QString strText, QString strIcon = "Information");
};

#endif // FINDTARGETS_H