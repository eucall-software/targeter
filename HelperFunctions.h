#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include "opencv2/opencv.hpp"
#include "opencv/highgui.h"
#include <QImage>

/**
* class for useful helper image manipulation functions
*/
class HelperFunctions {
public:

	static cv::Mat displayHistogram(int histSize, cv::Mat b_hist, int hist_w = 512, int hist_h = 400);
	
	static cv::Mat putMatScale(cv::Mat im, bool scale = true, bool bRed = true);

	static void resizeImagePreserve(cv::Mat &imageIn, cv::Mat &imageOut, int newWidth, int newHeight);

	static void DebugPrintMat(cv::Mat mat);

	static cv::Mat testReturn(cv::Mat& im);
	
	static int reflect(int M, int x);
	static std::string type2str(int type);

	static bool isGrayImage(cv::Mat img);

	static  QImage makeQImage(cv::Mat im, bool bRGBSwap = true);
	
	static  QImage::Format getFormat(int type);

	// template functions cannot be in cpp file!

	/**
	*
	* creates a scaled opencv image from int* 1D image array
	*
	* @author    David Watts
	* @since     2017/03/08
	*
	* FullName   putImageScale
	* Qualifier
	* @param     T * im
	* @param     int w
	* @param     int h
	* @return    cv::Mat
	* Access     public static
	*/
	template< typename T >
	static  cv::Mat putImageScale(T* im, int w, int h)
	{
		int i;
		uchar val;
		T tmin = 999999;
		T tmax = -999999;

		for (i = 0; i < w*h; i++)
		{
			if (im[i] < 0)
				im[i] = 0;
			if (im[i] < tmin)
				tmin = im[i];
			if (im[i] > tmax)
				tmax = im[i];
		}

		cv::Mat cMat(h, w, CV_8UC3);

		for (int j = 0; j < h; j++)
		{
			for (int i = 0; i < w; i++)
			{
				val = (uchar)(((double)(im[i + j*w] - tmin))*(255.0 / (double)(tmax - tmin)));

				// truncate to grayscale
				val = min(max(0, val), 255);

				cMat.ptr<uchar>(j)[(i * 3)] = val;
				cMat.ptr<uchar>(j)[(i * 3) + 1] = val;
				cMat.ptr<uchar>(j)[(i * 3) + 2] = val;
			}
		}

		return cMat;
	}

	/**
	*
	*  creates a opencv image from int* 1D image array
	*
	* @author    David Watts
	* @since     2017/03/08
	*
	* FullName   putImage
	* Qualifier
	* @param     T * im
	* @param     int width
	* @param     int height
	* @return    cv::Mat
	* Access     public static
	*/
	template<typename T>
	static  cv::Mat  putImage(T* im, int width, int height)
	{
		cv::Mat cMat(h, w, CV_8UC3);

		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width; i++)
			{
				cMat->ptr<uchar>(j)[(i * 3)] = im[i + j*width];
				cMat->ptr<uchar>(j)[(i * 3) + 1] = im[i + j*width];
				cMat->ptr<uchar>(j)[(i * 3) + 2] = im[i + j*width];
			}
		}

		return cMat;
	}

	/**
	*
	*  Returns a greyscale 1D int* image array from an OpenCV image
	*
	* @author    David Watts
	* @since     2017/03/07
	*
	* FullName   HelperFunctions::getImage
	* Qualifier
	* @param     cv::Mat & m
	* @return    T*
	* Access     public
	*/
	template< typename T >
	static  T*  getImage(cv::Mat& m)
	{
		fname();

		T* im = new T[m.cols*m.rows];

		if (m.channels() > 1)
		{
			cv::Mat greyMat;

			cv::cvtColor(m, greyMat, cv::COLOR_BGR2GRAY);

			for (int j = 0; j < m.rows; j++)
			{
				for (int i = 0; i < m.cols; i++)
					im[i + j*m.cols] = greyMat.ptr<uchar>(j)[i];
			}
		}
		else
		{
			for (int j = 0; j < m.rows; j++)
			{
				for (int i = 0; i < m.cols; i++)
					im[i + j * m.cols] = m.ptr<uchar>(j)[i];
			}
		}

		return im;
	}


	/**
	*
	*  rescales image pixel values
	*
	* @author    David Watts
	* @since     2017/03/07
	*
	* FullName   HelperFunctions::rescale
	* Qualifier
	* @param     T * im
	* @param     int w
	* @param     int h
	* @return    void
	* Access     public
	*/
	template< typename T >
	static void rescale(T* im, int w, int h)
	{
		fname();

		int i;
		T tmin = 999999;
		T tmax = -999999;

		for (i = 0; i < w*h; i++)
		{
			if (im[i] < 0)
				im[i] = 0;
			if (im[i] < tmin)
				tmin = im[i];
			if (im[i] > tmax)
				tmax = im[i];
		}

		for (i = 0; i < w*h; i++)
		{

			im[i] = (T)((double)(im[i] - tmin))*(255.0 / (double)(tmax - tmin));
			// std::cout << im[i] << " " ;
		}
	}
};

#endif