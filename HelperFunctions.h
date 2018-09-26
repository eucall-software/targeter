// Targeter - target identification software for EUCALL workpackage 6
// Licensed under the GPL License. See LICENSE file in the project root for full license information.
// Copyright(C) 2017  David Watts 

#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include "opencv2/opencv.hpp"
#include "opencv/highgui.h"
#include <QVector>
#include <QImage>
#include <QJsonObject>


/**
* class for useful helper image manipulation functions
*/
class HelperFunctions {
public:

	static cv::Mat displayHistogram(cv::Mat b_hist, int histSize, int hist_w = 512, int hist_h = 400);

	static cv::Mat convertFloatToGreyscaleMat(cv::Mat im);

	static QVector3D addPointToVector3D(QVector3D vect, QPointF pt);

	static bool pointInPoly(QPolygonF poly, QPointF pt);
	static bool pointInEllipse(QRectF ellipseRect, QPointF pt);

	static int padd(int n, int levels = 3) 
	{ 
		int power = pow(2, levels);
		return (1 + n/power) * power; 
	};

	static QSharedPointer<QRect> getPaddRect(QPoint ptStart, QPoint ptEnd, int levels);

	static QJsonObject ObjectFromString(const QString& in);

	static cv::Mat putMatScale(cv::Mat im, bool scale = true, bool bRed = true);

	static void resizeImagePreserve(cv::Mat &imageIn, cv::Mat &imageOut, int newWidth, int newHeight);

	static void DebugPrintMat(cv::Mat mat);

	static bool checkMatCompatibility(cv::Mat& in, cv::Mat& out, const int expectedType, bool checkType = true);

	static cv::Mat testReturn(cv::Mat& im);
	
	static int reflect(int M, int x);
	static QString type2str(int type);

	static bool isGrayImage(const cv::Mat& img);

	static int* getCImage(const cv::Mat& img);

	static QString toDataURL(cv::Mat image);

	static  QImage makeQImage(cv::Mat im, bool bRGBSwap = true);
	
	static  QImage::Format getFormat(int type);

	static cv::Scalar QC2S(QColor color);
	static QColor S2QC(cv::Scalar color);

	static QString getBarcodeStringfromVector(int* vect, int& size);

	static void rotate90(cv::Mat &matImage, RotateFlags::RotateFlags rotflag);
	
	template< typename T >
	static cv::Mat expandRunLengthImage(T* Image, int length, int width, int height, int type, int channels, bool makeBorder = true, bool bBinary = false)
	{
		cv::Mat out(height, width, type);

		T tmax = 0;

		for(int i=0;i<width;i++)
			tmax = MAX(Image[i], tmax);
		
		// scale
		for (int i = 0; i < width; i++)
			Image[i] *= 255 * Image[i] / tmax;

		if(length == height)
		{
			for (int j = 0; j < height; j++)
			{
				T val = bBinary ? (Image[j]>0 ? 255 : 0) : Image[j];

				if(channels ==3)
				{
					Vec3b color = Vec3b(val, val, val);

					for (int i = 0; i < width; i++)
						out.at<Vec3b>(j, i) = color;
				}
				else
				{
					for (int i = 0; i < width; i++)
						out.at<uchar>(j, i) = saturate_cast<uchar>(val);
				}
			}
		}
		else if(length == width)
		{
			for (int i = 0; i < width; i++)
			{
				T val = bBinary?(Image[i]>0?255:0): Image[i];

				if(channels ==3)
				{
					Vec3b color = Vec3b(val, val, val);

					for (int j = 0; j < height; j++)
						out.at<Vec3b>(j, i) = color;
				}
				else
				{
					for (int j = 0; j < height; j++)
						out.at<uchar>(j, i) = saturate_cast<uchar>(val);
				}
				
			}
		}

		if(makeBorder)
		{
			int border_size = 50;

			cv::Mat big_image(height+ border_size*2, width+ border_size*2, type, cvScalar(255));
			out.copyTo(big_image(cv::Rect(border_size, border_size, out.cols, out.rows)));

			return big_image;
		}
		else
			return out;
	}


	// template functions cannot be in cpp file!

	/**
	*
	* creates a line plot of data
	*
	* @author    David Watts
	* @since     2017/03/08
	*
	* FullName   linePlotImage
	* Qualifier
	* @param     T * data	// Y values
	* @param     int datasize  
	* @param     int binX	// interval between data points
	* @param     int size_w	// image width
	* @param     int size_h // image height
	* @return    cv::Mat	// plot image
	* Access     public static
	*/
	template< typename T >
	static cv::Mat linePlotImage(QVector<T*> const& data, int datasize, int binX, int size_w=512, int size_h=512)
	{
		// Draw the histograms for B, G and 
		int cols[15][3] = {
			{ 255, 255, 255 },{ 255, 0, 0 },{ 0, 255, 0 },{ 0, 0, 255 },
			{ 255, 255, 0 },{ 0, 255, 255 },{ 255, 0, 255 },{ 192, 192, 192 },
			{ 128, 128, 128 },{ 128, 0, 0 },{ 128, 128, 0 },{ 0, 128, 0 },
			{ 128, 0, 128 },{ 0, 128, 128 },{ 0, 0, 128 } };

		int fontFace = cv::FONT_HERSHEY_TRIPLEX;
		int fontScale = 1;
		cv::Scalar red(255, 0, 0);
		cv::Scalar green(0, 255, 0);
		cv::Scalar blue(0, 0, 255);
		int maxheight = 0;
		cv::String text;
		cv::Size textSize;
		int baseline = 0;

		// create image for histogram
		cv::Mat histImage(size_h, size_w, CV_8UC3, cv::Scalar(0, 0, 0));

		// bin size in image
		double bin_w = (((double)size_w) / ((double)datasize));

		// get the x axis tick labels
		// 5 ticks
		int ticks = 5;
		// assume data starts at zero
		int maximum = binX*datasize;

		int interval = maximum / ticks;

		// round to decimal intervals
		if (interval > 1000)
			interval = interval - interval % 1000;
		else if (interval > 100)
			interval = interval - interval % 100;
		else if (interval > 10)
			interval = interval - interval % 10;

		double ratioW = double(size_w) / double(maximum);

		try
		{
			/// Draw for each channel
			for (int i = 0; i < datasize*binX; i += interval)
			{
				text = cv::format("%d", i);

				textSize = cv::getTextSize(text, fontFace, fontScale, 1, &baseline);

				maxheight = max(maxheight, textSize.height);

				putText(histImage, text, cv::Point((int)(i*ratioW), size_h), fontFace, fontScale, red, 8, true);
			}

			maxheight *= 1.5;

			// scale data
			T tmax= data[0][0], tmin = data[0][0];
			
			for (int j = 0; j < data.length(); j++)
			{
				// Normalize the result to [ 0, histImage.rows ] - i.e. fit in screen
				for (int i = 0; i < datasize; i++)
				{
					tmax = MAX(tmax, data[j][i]);
					tmin = MIN(tmin, data[j][i]);
				}
			}

			for (int j = 0; j < data.length(); j++)
			{
				double r = cols[j % 15][0];
				double g = cols[j % 15][1];
				double b = cols[j % 15][2];

				cv::Scalar colour = cv::Scalar(r, g, b);
				
				if(datasize>1)
				{
					/// Draw for each channel
					for (int i = 1; i < datasize; i++)
					{
						T val1 = (T)((double)(data[j][i-1] - tmin))*(size_h / (double)(tmax - tmin));
						T val2 = (T)((double)(data[j][i] - tmin))*(size_h / (double)(tmax - tmin));

						cv::Point p1 = cv::Point((int)(bin_w*i-1), size_h - maxheight - val1);
						cv::Point p2 = cv::Point((int)(bin_w*i), size_h - maxheight - val2);

						cv::line(histImage, p1, p2, colour,	1, CV_AA);
					}
				}
			}
				
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
				val = MIN(MAX(0, val), 255);

				Vec3b color = Vec3b(val, val, val);

				cMat.at<Vec3b>(j, i) = color;
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