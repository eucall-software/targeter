#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include "opencv2/opencv.hpp"
#include "opencv/highgui.h"
#include <vector>

/**
* class to for image processing functionality shared by other classes
*/
class ImageProcessing 
{
public:
	static void GaussianBlur(int* im, int w, int h, int repeat);

	static void modalFilter(int* im, int w, int h, int fSize, int NoFocusImages);
	static void modalFilter(cv::Mat& im, int w, int h, int fSize, int NoFocusImages);

	static cv::Mat Threshold(cv::Mat& im, int min, int max);

	static int* histClusterRGBImage(cv::Mat hueHist, int histSize, int NoCluster = 2);
	static cv::Mat HistogramClusteringGray(cv::Mat im, int NoClusters=2);
};

#endif