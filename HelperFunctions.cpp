#include <iostream>
#include <iomanip>
#include <limits>
#include <QDebug>
#include <vector>
#include <QImage>

#include "opencv2/opencv.hpp"
#include "opencv/highgui.h"
#include "mainwindow.h"

#include "globals.h"
#include "HelperFunctions.h"

using namespace std;


/**
*
*  Returns a string representation of the opencv image type
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   HelperFunctions::type2str
* Qualifier 
* @param     int type 
* @return    std::string
* Access     public 
*/
string HelperFunctions::type2str(int type)
{
	string r;

	uchar depth = type & CV_MAT_DEPTH_MASK;
	uchar chans = 1 + (type >> CV_CN_SHIFT);

	switch (depth) {
	case CV_8U:  r = "8U"; break;
	case CV_8S:  r = "8S"; break;
	case CV_16U: r = "16U"; break;
	case CV_16S: r = "16S"; break;
	case CV_32S: r = "32S"; break;
	case CV_32F: r = "32F"; break;
	case CV_64F: r = "64F"; break;
	default:     r = "User"; break;
	}

	r += "C";
	r += (chans + '0');

	return r;
}

/**
*
*  Returns an OpenCV image from a histogram (b_hist)
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   HelperFunctions::displayHistogram
* Qualifier 
* @param     int histSize 
* @param     cv::Mat b_hist 
* @param     int hist_w 
* @param     int hist_h 
* @return    cv::Mat
* Access     public 
*/
cv::Mat HelperFunctions::displayHistogram(int histSize, cv::Mat b_hist, int hist_w, int hist_h)
{
	// Draw the histograms for B, G and R
		
	int fontFace = cv::FONT_HERSHEY_SCRIPT_SIMPLEX;
	int fontScale = 1, thickness=1;
	cv::Scalar red(255, 0, 0);
	cv::Scalar green(0, 255, 0);
	cv::Scalar blue(0, 0, 255);
	int maxheight = 0;
	cv::String text;
	cv::Size textSize;
	int baseline = 0;

	// create image for histogram
	cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));
	// bin size in image
	double bin_w = (((double)hist_w) / ((double)histSize));

	std::vector<cv::Point> lines;

	try
	{
		/// Draw for each channel
		for (int i = 0; i < histSize; i+=50)
		{
			text = cv::format("%d", i);

			textSize = cv::getTextSize(text, fontFace, fontScale, 1, &baseline);

			maxheight = max(maxheight, textSize.height);

			putText(histImage, text, cv::Point((int)(bin_w*i), hist_h), fontFace, fontScale, red, 8, true);
		}

		maxheight *= 1.5;

		// Normalize the result to [ 0, histImage.rows ] - i.e. fit in screen
		normalize(b_hist, b_hist, 0, histImage.rows - maxheight, cv::NORM_MINMAX);
			
		/// Draw for each channel
		for (int i = 0; i < histSize; i++)
		{
			lines.push_back(cv::Point((int)(bin_w*i), hist_h - maxheight - cvRound(b_hist.at<float>(i))));
		}

		const cv::Point *pts = (const cv::Point*) cv::Mat(lines).data;
		int npts = cv::Mat(lines).rows;

		polylines(histImage, &pts, &npts, 1,
			false,                  // draw closed contour (i.e. joint end to start)
			cv::Scalar(0, 255, 0),		// colour RGB ordering (here = green)
			1, 					// line thickness
			CV_AA, 0);
	}
	catch (cv::Exception& e)
	{
		const char* err_msg = e.what();
		DBOUT("exception caught: " << err_msg << std::endl);
	}

	return histImage;
}

/**
*
*  Resizes image while preserving aspect ratio
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   HelperFunctions::resizeImagePreserve
* Qualifier 
* @param     cv::Mat & imageIn 
* @param     cv::Mat & imageOut 
* @param     int newWidth 
* @param     int newHeight 
* @return    void
* Access     public 
*/
void HelperFunctions::resizeImagePreserve(cv::Mat &imageIn, cv::Mat &imageOut, int newWidth, int newHeight)
{
	int w = newWidth;
	int h = newHeight;

	double ratio = ((double)imageIn.cols) / ((double)imageIn.rows); // width/height

	int scaledH = (int)round(((double)w) / ratio);
	int scaledW = (int)round(((double)h)*ratio);

	if (scaledH > h) { w = scaledW; }
	else { h = scaledH; }

	cv::resize(imageIn, imageOut, cv::Size(w, h), 0, 0, cv::INTER_LINEAR);
}

/**
*
*  make QImage from OpenCV image
*
* @author    David Watts
* @since     2017/03/07
*
* FullName   HelperFunctions::makeQImage
* Qualifier
* @param     cv::Mat im
* @param     bool bRGBSwap
* @return    QT_NAMESPACE::QImage
* Access     public
*/
QImage HelperFunctions::makeQImage(cv::Mat im, bool bRGBSwap)
{
	QImage::Format form = getFormat(im.type());

	QImage pImage = QImage(im.data, im.cols, im.rows, (int)im.step, form);

	if (bRGBSwap)
		pImage.rgbSwapped();

	return pImage;
}


/**
*
*  Returns QT Image type for OpenCV type
*
* @author    David Watts
* @since     2017/03/07
*
* FullName   HelperFunctions::getFormat
* Qualifier
* @param     int type
* @return    QT_NAMESPACE::QImage::Format
* Access     public
*/
QImage::Format HelperFunctions::getFormat(int type)
{

#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	switch (type) {
	case CV_8UC3: {
		return QImage::Format_RGB888;
	}
	case CV_8U: {
		return QImage::Format_Indexed8;
	}
	case CV_8UC4: {
		return  QImage::Format_ARGB32;
	}
				  return QImage::Format_Invalid;
	}
	return QImage::Format_Invalid;
}

/**
*
*  determines if image is greyscale
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   HelperFunctions::isGrayImage
* Qualifier  // returns true if the given 3 channel image is B = G = R
* @param     cv::Mat img 
* @return    bool
* Access     public 
*/
bool HelperFunctions::isGrayImage(cv::Mat img) // returns true if the given 3 channel image is B = G = R
{
	for (int j = 0; j < img.rows; j++)
	{
		for (int i = 0; i < img.cols; i++)
		{
			if (img.ptr<uchar>(j)[(i * 3)] != img.ptr<uchar>(j)[(i * 3) + 1] ||
				(img.ptr<uchar>(j)[(i * 3)] != img.ptr<uchar>(j)[(i * 3) + 2]))
				return false;
		}
	}
	return true;
}


/**
*
*  Handles vector boundaries by reflecting values
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   HelperFunctions::reflect
* Qualifier 
* @param     int M 
* @param     int x 
* @return    int
* Access     public 
*/
int HelperFunctions::reflect(int M, int x)
{
	if (x < 0)
	{
		return -x - 1;
	}

	if (x >= M)
	{
		return 2 * M - x - 1;
	}

	return x;
}

/**
*
*  returns a 0-255 scaled opencv image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   HelperFunctions::putMatScale
* Qualifier 
* @param     cv::Mat im 
* @param     bool scale 
* @param     bool bRed 
* @return    cv::Mat
* Access     public 
*/
cv::Mat HelperFunctions::putMatScale(cv::Mat im, bool scale, bool bRed)
{
	cv::Mat cMat;

	cv::normalize(im, cMat, 255, 0);

	return cMat;
}


cv::Mat HelperFunctions::testReturn(cv::Mat& im)
{
	cv::Mat cMat = cv::Mat(im.rows, im.cols, CV_8UC3, cv::Scalar(0));

	for (int j = 0; j < im.rows; j++)
	{
		for (int i = 0; i < im.cols; i++)
		{
			cMat.ptr<uchar>(j)[(i * 3)] = 0;
			cMat.ptr<uchar>(j)[(i * 3) + 1] = j % 255;
			cMat.ptr<uchar>(j)[(i * 3) + 2] = i % 255;
		}
	}

	return cMat;
}


/**
*
*  prints 2D matrix to screen
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   HelperFunctions::DebugPrintMat
* Qualifier 
* @param     cv::Mat mat 
* @return    void
* Access     public 
*/
void HelperFunctions::DebugPrintMat(cv::Mat mat)
{
	for (int i = 0; i < mat.cols; i++)
	{
		for (int j = 0; j < mat.rows; j++)
		{
			std::cout << (int)mat.at<uchar>(j, i) << " ";
		}
	}
}

