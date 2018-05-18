// Targeter - target identification software for EUCALL workpackage 6
// Licensed under the GPL License. See LICENSE file in the project root for full license information.
// Copyright(C) 2017  David Watts 

#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include "opencv2/opencv.hpp"
#include "opencv/highgui.h"
#include "targeterimage.h"
#include "globals.h"
#include "Settings.h"
#include <memory>
#include <vector>

/**
* class to for image processing functionality shared by other classes
*/
class ImageProcessing : public QObject
{
	Q_OBJECT
public:
	ImageProcessing(){};
	~ImageProcessing(){};

	// from ELI barcode reading code
	QString scanForBarCodes(const cv::Mat& src, cv::Mat& dst, bool displayOK = true);
	QString getBarcode(cv::Mat& src, QRect roi);
	int* getRunLengthHistogram(cv::Mat& src, int& size, bool barLeftToRightBottomToTop = true);
	int* movingAverageVector(int* hist, int size);
	int* clusterMidPosition(int* hist, int size);
	int* thresholdOnMinimum(int* hist, int size, bool bAutoThreshold= false, int thresholdValue=15);

	int* fitPolynomial(int* y, int size, int order);

	cv::Mat fitBackgroundImage(cv::Mat im);

	void calibrateCamera(std::vector<targeterImage> imageList, SettingsValues* s);
	cv::Mat getLines(cv::Mat& src, QColor colour = QColor("red"));
// member functions
	cv::Mat CornerDetection(cv::Mat src, int noCorners = 10);
	cv::Mat CannyEdgeDetection(cv::Mat& im, bool bConverColor = true);

	cv::Mat Threshold(cv::Mat& im, int min, int max, thresholdType::thresholdType type = thresholdType::Range, bool bConvertToColor = true);
	int* histClusterRGBImage(cv::Mat hueHist, int histSize, int NoCluster = 2);

	cv::Mat getConnectedComponentImage(cv::Mat& bin, cv::Mat& labels, cv::Mat& stats, cv::Mat& centroids);
	cv::Mat HistogramClusteringGray(cv::Mat im, int NoClusters=2);

// static functions
	static void symmetricPadding(cv::Mat const & image, cv::Mat & paddedImage, int padding);

	static double PointPairToBearingDegrees(cv::Point startingPoint, cv::Point endingPoint);
	static double PointFromLine(cv::Point start, cv::Point end, cv::Point point);

	static cv::Mat localMaxima(cv::Mat image, bool remove_plateaus = true);
	static double imageMedian(cv::Mat channel);

	static void GaussianBlur(int* im, int w, int h, int repeat);

	static void modalFilter(int* im, int w, int h, int fSize, int NoFocusImages);
	static void modalFilter(cv::Mat& im, int w, int h, int fSize, int NoFocusImages);

	void thinning(const cv::Mat& src, cv::Mat& dst);
signals:
	void LOGCONSOLE(QString strText, CONSOLECOLOURS::colour col = CONSOLECOLOURS::colour::Information);
};

#endif