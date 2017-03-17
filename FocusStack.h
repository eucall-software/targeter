#ifndef FOCUSSTACK_H
#define FOCUSSTACK_H

#include <QVector>
#include "opencv2/opencv.hpp"
#include "opencv/highgui.h"
#include "mainwindow.h"

/**
* class that manages performing focus stack, ie. takes image sequence and combines them into single in focus image
*/
class FocusStack {
public:
    static cv::Mat* processImageStack(std::vector<targeterImage>& imageStack, std::vector<int>& imageIndexes, MainWindow* pMainWindow);
	static cv::Mat* processImageStack2(std::vector<targeterImage>& imageStack, std::vector<int>& imageIndexes, MainWindow* pMainWindow);
	static cv::Mat* processImageStack3(std::vector<targeterImage>& imageStack, std::vector<int>& imageIndexes, MainWindow* pMainWindow);

	static cv::Mat* mergeImageStack(std::vector<targeterImage>& imageStack, cv::Mat indexImage, int w, int h);

    // focussing algorithms /////////////////////////////////
	static double modifiedLaplacian(const cv::Mat& src);

	static void fillErrorRegions(int* im, int w, int h, int fSize, int NoFocusImages);
	static void fillErrorRegions(cv::Mat &im, int w, int h, int fSize, int NoFocusImages);
    
    // OpenCV port of 'LAPV' algorithm (Pech2000)
	static double varianceOfLaplacian(const cv::Mat& src);

    // OpenCV port of 'TENG' algorithm (Krotkov86)
	static double tenengrad(const cv::Mat& src, int ksize);

    // OpenCV port of 'GLVN' algorithm (Santos97)
	static double normalizedGraylevelVariance(const cv::Mat& src);

    // helper pixel access functions
};

#endif // IMAGEPROCESSING_H
