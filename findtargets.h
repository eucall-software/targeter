#ifndef FINDTARGETS_H
#define FINDTARGETS_H

#include "opencv2/opencv.hpp"
#include "opencv/highgui.h"
#include "targeterimage.h"
#include <vector>

class MainWindow;

using namespace std;

namespace FindTargets {
	cv::Mat ColourOccuranceHistogram(std::vector<targeterImage>& trainingImages, targeterImage& detectionImage, int distance, int NoClusters, MainWindow* pMainWindow);
	cv::Mat CVMatching(std::vector<targeterImage>& trainingImages, targeterImage& detectionImage, algoType::algoType matchType);

	double getCoocMatrix(targeterImage& m, int* pMask, drawingMode::drawingMode maskType, int startX, int startY, int regionWidth, int regionHeight, double* coMatrixF, int NoClusters, int maxD);
    void getCoocuranceHistogram(targeterImage& m, double* coMatrixF, int NoClusters, int maxD);

    double* findTargets(targeterImage& detectionImage, double* coMatrixTestF, int NoClusters, int maxD);
	void hueHistogramClustering(targeterImage& detectionImage, std::vector<targeterImage>& TrainImages, int NoClusters, MainWindow* pMainWindow);

    //int* histClusterRGBImage(cv::Mat hueHist, int histSize);
	std::vector<int*> kMeansRGB(cv::Mat img, std::vector<cv::Mat> testImgs, int NoClusters, int maxIterations);
    int* histEntropyClusterRGBImage(cv::Mat hueHist, int histSize, int NoClusters);
	int* histClusterEqual(cv::Mat hueHist, int histSize, int NoClusters);

   
    template<typename T> void printVector(const T& t);
    template<typename T>  void printClusterVector(std::vector<T> cluster);
}


#endif // FINDTARGETS_H
