// Targeter - target identification software for EUCALL workpackage 6
// Licensed under the GPL License. See LICENSE file in the project root for full license information.
// Copyright(C) 2017  David Watts 

#include <iostream>
#include <iomanip>
#include <limits>
#include <QDebug>
#include <vector>
#include "opencv2/opencv.hpp"
#include "opencv/highgui.h"
#include <zbar64/include/zbar.h>
#include "imageprocessing.h"
#include "HelperFunctions.h"
#include "globals.h"

using namespace cv;
using namespace std;
using namespace zbar;

QString ImageProcessing::scanForBarCodes(const cv::Mat& src, cv::Mat& dst, bool displayOK)
{
	QString tag;

	//scanner setup
	ImageScanner scanner;
	scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);

	int width = src.cols;
	int height = src.rows;

	/// Detector parameters
	uchar* raw = nullptr;
	cv::Mat gray = Mat::zeros(src.size(), CV_8UC1);

	dst = src.clone();

	if(src.channels() != 1)
	{
		cvtColor(src, gray, CV_BGR2GRAY);

		// wrap image data  
		raw = (uchar *)gray.data;
	}
	else
		raw = (uchar *)src.data;

	Image image(width, height, "Y800", raw, width * height);

	// scan the image for barcodes  
	scanner.scan(image);

	std::string TAG;

	// extract results  
	for (Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol)
	{
		TAG = symbol->get_data();
		if (TAG.size() != 14)
			continue;

		//print tag
		tag = QString(TAG.c_str());

		//define vector of points
		vector<Point> vp;

		if (displayOK)
		{
			int n = symbol->get_location_size();

			//get bar code location in image
			for (int i = 0; i < n; i++)
			{
				vp.push_back(Point(symbol->get_location_x(i), symbol->get_location_y(i)));
			}

			//build rectangle around the bar code
			RotatedRect r = minAreaRect(vp);
			Point2f pts[4];
			r.points(pts);

			//draw lines
			for (int i = 0; i < 4; i++)
			{
				line(dst, pts[i], pts[(i + 1) % 4], Scalar(255, 0, 0), 3);
			}
		}
	}

	return tag;
}
/*
void ImageProcessing::polyfit(const Mat& src_x, const Mat& src_y, Mat& dst, int order)
{
	CV_Assert((src_x.rows > 0) && (src_y.rows > 0) && (src_x.cols == 1) && (src_y.cols == 1) && (dst.cols == 1) && (dst.rows == (order + 1)) && (order >= 1));

	Mat copy, X_t, X_inv, temp2;

	Mat X = Mat::zeros(src_x.rows, order + 1, CV_32FC1);
	
	for (int i = 0; i <= order; i++)
	{
		copy = src_x.clone();
		pow(copy, i, copy);		// create vector of i^order

		Mat M1 = X.col(i);		// get reference of column i of Mat X

		copy.col(0).copyTo(M1); // copy power values to x(i) 
	}

	transpose(X, X_t);		// transpose matrix

	Mat temp = X_t * X;		// multiply transpose by itself

	invert(temp, temp2);	// invert and solve matrix

	Mat temp3 = temp2 * X_t;	// multiply result by the transpose
	Mat W = temp3 * src_y;		// multiply result by 

	W.copyTo(dst);
}
*/

int*  ImageProcessing::fitPolynomial(int* ydata, int size, int max_orders)
{
	int* newy = new int[size];

	Mat M = Mat_<double>(size, max_orders);
	Mat I = Mat_<double>(size, 1);

	for (int i = 0; i < size; i++)
	{
		double y = double(i - size / 2) / double(size);

		for (int order = 0; order < max_orders; order++)
		{
			double powy = pow(y, max_orders - order - 1);

			M.at<double>(i, order) = powy;
		}

		I.at<double>(i, 0) = (double)ydata[i];
	}

	SVD s(M);
	Mat q;

	// fit background
	s.backSubst(I, q);

	for (int i = 0; i < size; i++)
	{
		double y = double(i - size / 2) / double(size);
		
		double quad = 0;

		for (int order = 0; order<max_orders; order++)
		{
			double powy = pow(y, max_orders - order - 1);

			double qt = q.at<double>(order, 0);
			
			quad += qt * powy;
		}

		newy[i] = quad;
	}

	return newy;
}

cv::Mat ImageProcessing::subtractBackgroundChannel(cv::Mat inputImagePlane, cv::Mat& backgroundImagePlane)
{
	if(inputImagePlane.channels()>1)
		return cv::Mat();

	cv::Mat bim = fitBackgroundImage(inputImagePlane);

	cv::Mat gray_16S, dst_16S, bim_16S, dst;

	inputImagePlane.convertTo(gray_16S, CV_16SC1);
	bim.convertTo(bim_16S, CV_16SC1);

	cv::subtract(gray_16S, bim_16S, dst_16S);

	dst_16S = dst_16S + mean(bim_16S);

	dst_16S.convertTo(dst, CV_8UC1);
	bim_16S.convertTo(bim, CV_8UC1);

	backgroundImagePlane = bim;

	return dst;
}

cv::Mat ImageProcessing::subtractBackground(cv::Mat inputImage, cv::Mat& backgroundImage)
{
	cv::Mat dst;

	if (backgroundImage.empty())
		backgroundImage = cv::Mat(inputImage.rows, inputImage.cols, inputImage.type());

	if(inputImage.channels()==1)
	{
		dst = subtractBackgroundChannel(inputImage, backgroundImage);
	}
	else
	{
		std::vector<cv::Mat> rgb_planes;
		std::vector<cv::Mat> rgb_background;

		split(inputImage, rgb_planes);
		split(backgroundImage, rgb_background);

		rgb_planes[0] = subtractBackgroundChannel(rgb_planes[0], rgb_background[0]);
		rgb_planes[1] = subtractBackgroundChannel(rgb_planes[1], rgb_background[1]);
		rgb_planes[2] = subtractBackgroundChannel(rgb_planes[2], rgb_background[2]);

		cv::merge(rgb_planes, dst);
		cv::merge(rgb_background, backgroundImage);
	}

	return dst;
}

cv::Mat ImageProcessing::fitBackgroundImage(cv::Mat im)
{
	Mat M = Mat_<double>(im.rows * im.cols, 6);
	Mat I = Mat_<double>(im.rows * im.cols, 1);

	for (int i = 0; i < im.rows; i++)
	{
		for (int j = 0; j < im.cols; j++)
		{
			double x = (j - im.cols / 2) / double(im.cols);
			double y = (i - im.rows / 2) / double(im.rows);

			M.at<double>(i*im.cols + j, 0) = x*x;
			M.at<double>(i*im.cols + j, 1) = y*y;
			M.at<double>(i*im.cols + j, 2) = x*y;
			M.at<double>(i*im.cols + j, 3) = x;
			M.at<double>(i*im.cols + j, 4) = y;
			M.at<double>(i*im.cols + j, 5) = 1;

			I.at<double>(i*im.cols + j, 0) = im.at<uchar>(i, j);
		}
	}

	SVD s(M);
	Mat q;

	// fit background
	s.backSubst(I, q);

	cout << q;
	cout << q.at<double>(2, 0);

	Mat background(im.rows, im.cols, CV_8UC1);

	for (int i = 0; i < im.rows; i++)
	{
		for (int j = 0; j < im.cols; j++)
		{
			double x = (j - im.cols / 2) / double(im.cols);
			double y = (i - im.rows / 2) / double(im.rows);

			double quad =	q.at<double>(0, 0)*x*x + 
							q.at<double>(1, 0)*y*y + 
							q.at<double>(2, 0)*x*y + 
							q.at<double>(3, 0)*x + 
							q.at<double>(4, 0)*y + 
							q.at<double>(5, 0);

			background.at<uchar>(i, j) = saturate_cast<uchar>(quad);
		}
	}
	return background;
}

int* ImageProcessing::getRunLengthHistogram(cv::Mat& src, int& size, bool barLeftToRightBottomToTop)
{
	QString tag = "";

	int width = src.cols;
	int height = src.rows;

	/// Detector parameters
	cv::Mat gray = Mat::zeros(src.size(), CV_8UC1);

	if (src.channels() != 1)
		cvtColor(src, gray, CV_BGR2GRAY);
	else
		gray = src;

	double* hist = nullptr;

	if (src.cols > src.rows)
	{
		size = gray.cols;

		hist = new double[size];

		if (barLeftToRightBottomToTop)
		{
			// accumulate in columns
			for (int i = 0; i < size; i++)
			{
				hist[i] = 0;
				for (int j = 0; j < gray.rows; j++)
				{
					unsigned char g = gray.ptr<uchar>(j)[i];
					hist[i] += double(g) / double(gray.rows);
				}
			}
		}
		else
		{
			for (int i = size - 1; i >= 0; i--)
			{
				hist[i] = 0;
				for (int j = 0; j < gray.rows; j++)
				{
					unsigned char g = gray.ptr<uchar>(j)[i];
					hist[i] += double(g) / double(gray.rows);
				}
			}
		}
	}
	else
	{
		size = gray.rows;

		hist = new double[size];

		if (barLeftToRightBottomToTop)
		{
			// accumulate in rows
			for (int j = size - 1; j >= 0; j--)
			{
				hist[j] = 0;
				for (int i = 0; i < gray.cols; i++)
				{
					unsigned char g = gray.ptr<uchar>(j)[i];
					hist[j] += double(g) / double(gray.cols);
				}
			}
		}
		else
		{
			// accumulate in rows
			for (int j = 0; j < size; j++)
			{
				hist[j] = 0;
				for (int i = 0; i < gray.cols; i++)
				{
					unsigned char g = gray.ptr<uchar>(j)[i];
					hist[j] += double(g) / double(gray.cols);
				}
			}
		}
	}

	// copy over
	int* ihist = new int[size];

	for (int i = 0; i < size; i++)
		ihist[i] = (int)hist[i];

	delete [] hist;

	return ihist;
}

int* ImageProcessing::thresholdOnMinimum(int* hist, int size, bool bAutoThreshold, int thresholdValue)
{
	int* minimumValues = new int[size];

	// find moving minimum
	int windowSize = 31;
	int win = windowSize >> 1;
	int maxVal = 0;

	// get minimum lines
	for (int i = 0; i < size; i++)
	{
		int av = 0;
		int ct = 0;
		minimumValues[i] = MAXINT;

		maxVal = MAX(hist[i], maxVal);

		for (int j = i - win; j < i + win; j++)
		{
			if (j >= 0 && j < size)
				minimumValues[i] = MIN(minimumValues[i], hist[j]);
		}
	}

	// get stdev & mean
	double sum = 0;

	// get mean
	for (int i = 0; i < size; i++)
		sum += minimumValues[i];

	sum /= size;

	double stdev = 0;

	for (int i = 0; i < size; i++)
		stdev += pow((minimumValues[i] - sum), 2.0);

	stdev /= size;

	stdev = sqrt(stdev);

	double threshold;

	if(bAutoThreshold)
	{
		threshold = sum + 4.0*stdev;
	}
	else
	{
		threshold = (thresholdValue/100.0)*maxVal;
	}

	for (int i = 0; i < size; i++)
	{
		minimumValues[i] = threshold;
		/*
		if (hist[i] < threshold)
			minimumValues[i] = 0;
		else
			minimumValues[i] = 1;
		*/
	}
	// fit simple poly to values
	return minimumValues;
}

int* ImageProcessing::movingAverageVector(int* hist, int size)
{
	int* average = new int[size];

	for (int i = 0; i < size-10; i+=10)
	{
		ulong av = 0;

		for (int j = 0; j < 10; j++)
			av += hist[i + j];

		for (int j = 0; j < 10; j++)
			average[i + j] = av / 10.0;
	}

	int windowSize = 31;
	int win = windowSize >> 1;
	
	for (int i = 0; i < size; i++)
	{
		int av = 0;
		int ct = 0;

		for (int j = i - win; j < i + win; j++)
		{
			if (j >= 0 && j < size)
			{
				av += hist[i+j];
				ct++;
			}

			if (av > 0 && ct > 0)
				average[i] = av / ct;
			else
				average[i] = MAXINT;
		}
	}

	return average;
}

int* ImageProcessing::clusterMidPosition(int* hist, int size)
{
	int* average = new int[size];

	int lowerEstimate = MAXINT;
	int higherEstimate = 0;

	// limit to data range
	for (int i = 0; i < size; i++)
	{
		higherEstimate = MAX(higherEstimate, hist[i]);
		lowerEstimate = MIN(lowerEstimate, hist[i]);
	}

	int lowerCount = 1;
	int higherCount = 1;

	// get moving clusters
	for (int i = 0; i < size; i++)
	{
		if (abs(hist[i] - lowerEstimate/lowerCount) < abs(hist[i] - higherEstimate/higherCount))
		{
			lowerEstimate += hist[i];
			lowerCount++;
		}
		else
		{
			higherEstimate += hist[i];
			higherCount++;
		}
		//if the difference between lower and higher is large enough then threshold is valid otherwise it should be background

		average[i] = (higherEstimate / higherCount + lowerEstimate / lowerCount) / 2.0;
	}

	
	
	return average;
}

QString ImageProcessing::getBarcode(cv::Mat& src, QRect roi)
{
	QString tag = "";

	int width = src.cols;
	int height = src.rows;

	/// Detector parameters
	cv::Mat gray = Mat::zeros(src.size(), CV_8UC1);

	cv::Mat roiIm = src(cv::Rect(roi.x(), roi.y(), roi.width(), roi.height()));

	if (src.channels() != 1)
		cvtColor(roiIm, gray, CV_BGR2GRAY);
	else
		gray = roiIm;

	ulong* hist = nullptr;
	int size = 0;
	
	if(roi.width()>roi.height())
	{
		size = gray.cols;

		hist = new ulong[size];

		// accumulate in columns
		for (int i = 0; i < size; i++)
		{
			hist[i] = 0;

			for (int j = 0; j < gray.rows; j++)
			{
				unsigned char g = gray.ptr<uchar>(j)[i];
				hist[j] += g;
			}
		}
	}
	else
	{
		size = gray.rows;

		hist = new ulong[size];

		// accumulate in rows
		for (int j = 0; j < size; j++)
		{
			hist[j] = 0;

			for (int i = 0; i < gray.cols; i++)
			{
				unsigned char g = gray.ptr<uchar>(j)[i];
			
				hist[j] += g;
			}
		}
	}

	QVector<ulong*> lines;

	lines.append(hist);

	cv::Mat im = HelperFunctions::linePlotImage<ulong>(lines, size, 1, 512, 512);

	ulong f_min = hist[0], f_max = hist[0];

	// find maximum/minimum
	for (int i = 0; i < size; i++)
	{
		f_min = min(f_min, hist[i]);
		f_max = max(f_max, hist[i]);
	}

	ulong mid = (f_max + f_min)>>1;

	// threshold
	for (int i = 0; i < size; i++)
	{
		QString s = QString::number(hist[i]);

		DBOUT(s.data() << ", ");

		tag += hist[i] > mid ? "1" : "0";
	}
	delete[] hist;

	return tag;
}


/**
*
*  Threshold image between min and max greyscale values
*
* Method:    calibrateCamera
* FullName:  ImageProcessing::calibrateCamera
* Access:    public static
* Returns:   void
* Qualifier:
* Parameter: std::vector<targeterImage> imageList
* Parameter: SettingsValues s
*/

void ImageProcessing::calibrateCamera(QVector<QExplicitlySharedDataPointer<targeterImage>> imageList, SettingsValues* s)
{
	unsigned char flags = 0;

	flags += s->bCV_CALIB_CB_ADAPTIVE_THRESH ? CALIB_CB_ADAPTIVE_THRESH : 0;
	flags += s->bCV_CALIB_CB_NORMALIZE_IMAGE ? CALIB_CB_NORMALIZE_IMAGE : 0;
	flags += s->bCV_CALIB_CB_FILTER_QUADS ? CALIB_CB_FILTER_QUADS : 0;
	flags += s->bCALIB_CB_FAST_CHECK ? CALIB_CB_FAST_CHECK : 0;

	unsigned char	cal_flags = s->ZeroDistortion ? CALIB_ZERO_TANGENT_DIST : 0;
	cal_flags += s->FixedAspect ? CALIB_FIX_ASPECT_RATIO : 0;
	cal_flags += s->FixPrincipalPointCenter ? CALIB_FIX_PRINCIPAL_POINT : 0;
	cal_flags += s->UseIntrinsicGuess ? CALIB_FIX_INTRINSIC : 0;
	cal_flags += s->FixFocalLength ? CALIB_FIX_FOCAL_LENGTH : 0;

	string str="";

	if (flags != 0)
	{
		str += "corner detection flags = ";
		str += ((flags & CALIB_CB_ADAPTIVE_THRESH) ? "adaptive threshold, " : "");
		str += ((flags & CALIB_CB_NORMALIZE_IMAGE) ? "normalise image, " : "");
		str += ((flags & CALIB_CB_FILTER_QUADS) ? "filter quads, " : "");
		str += ((flags & CALIB_CB_FAST_CHECK) ? "fast check, " : "");

		str += "\n";
	}

	if (cal_flags != 0)
	{
		str += "calibration flags = ";
		str += ((cal_flags & CALIB_ZERO_TANGENT_DIST) ? "zero tangental distortion, " : "");
		str += ((cal_flags & CALIB_FIX_ASPECT_RATIO) ? "fix aspect ratio, " : "");
		str += ((cal_flags & CALIB_FIX_PRINCIPAL_POINT) ? "fix principal point, " : "");
		str += ((cal_flags & CALIB_FIX_INTRINSIC) ? "fix intrinsics, " : "");
		str += ((cal_flags & CALIB_FIX_FOCAL_LENGTH) ? "fix focal length" : "");

		str += "\n";
	}

	DBOUT(str.data());

	vector<vector<cv::Point2f>> image_points;
	vector<vector<cv::Point3f>> object_points;

	cv::Mat image;

	cv::Size boardSize = cv::Size(s->calibrateNoRows, s->calibrateNoCols);
	int board_n = s->calibrateNoRows * s->calibrateNoCols;

	int n_boards = imageList.size();

	cv::Size image_size;

	float focalDist = s->activeCamera == cameraType::camera::microscope ? s->focalDistanceMicroscopeCamera : s->focalDistanceOverviewCamera;

	//overview camera has 35mm lens
	float FocalLengthInPixels = 1000.0*focalDist / s->mmPerPixel; // = 1000 * 35mm fl / 5.5um pixel size

	if (imageList.size() == 0)
	{
		emit LOGCONSOLE("no images selected - exiting function", CONSOLECOLOURS::colour::Critical);
		return;
	}

	foreach(targeterImage view, imageList)
	{
		cv::Mat& im = view.getImage();

		image_size = im.size();

		vector<cv::Point2f> corners; 

		bool bFound = false;
		Mat viewGray;

		switch (s->CalibrateAlgorithm) // Find feature points on the input format
		{
		case calibrateAlgoType::algoType::CHESSBOARD:
			// also use our corner detection algorithm instead here (after editing corners)
			bFound = cv::findChessboardCorners(im, boardSize, corners, flags);
			
			cvtColor(im, viewGray, COLOR_BGR2GRAY);

			if(bFound)
			{
				// extra accuracy on corner detection
				cornerSubPix(viewGray, corners, Size(11, 11), Size(-1, -1), TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 30, 0.1));
			}
			
			break;
		case calibrateAlgoType::algoType::CIRCLES_GRID:
			bFound = findCirclesGrid(im, boardSize, corners, CALIB_CB_SYMMETRIC_GRID);
			break;
		case calibrateAlgoType::algoType::ASYMMETRIC_CIRCLES_GRID:
			bFound = findCirclesGrid(im, boardSize, corners, CALIB_CB_ASYMMETRIC_GRID);
			break;
		default:
			bFound = false;
			break;
		}

		double squareSize = s->SizeOfSquare;

		if (bFound)
		{
			image ^= cv::Scalar::all(255);

			image_points.push_back(corners);
			object_points.push_back(vector<Point3f>());
			vector<cv::Point3f>& opts = object_points.back();
			opts.resize(board_n);
			switch (s->CalibrateAlgorithm) {
			case calibrateAlgoType::CHESSBOARD:
			case calibrateAlgoType::CIRCLES_GRID:
				for (int i = 0; i < s->calibrateNoCols; i++)
					for (int j = 0; j < s->calibrateNoRows; j++)
						opts[i + j*s->calibrateNoCols] = cv::Point3f((float)(j*squareSize), (float)(i*squareSize), 0.f);
				break;
			case calibrateAlgoType::ASYMMETRIC_CIRCLES_GRID:
				for (int i = 0; i < s->calibrateNoCols; i++)
					for (int j = 0; j < s->calibrateNoRows; j++)
						opts[i + j*s->calibrateNoCols] = cv::Point3f((float)((2 * j + i % 2)*squareSize), (float)(i*squareSize), 0.f);
				break;
			}
			emit LOGCONSOLE("collected our " + QString::number(image_points.size()) + " of " + QString::number(n_boards) + " needed images");
		}
		else
		{
			std::string s = "did find chessboard corners in image " + view.name;
			emit LOGCONSOLE(QString::fromStdString(s), CONSOLECOLOURS::colour::Warning);
		}
	}

	if (image_points.size() == 0)
	{
		emit LOGCONSOLE("couldn't find any reference points in any image (check settings for the number of rows/cols in pattern) - exiting", CONSOLECOLOURS::colour::Question);
		return;
	}

	emit LOGCONSOLE("calibrating the camera");

	s->SizeOfSquare = 99;

	FileStorage fs("temp", FileStorage::WRITE | FileStorage::MEMORY | FileStorage::FORMAT_YAML);

	if (s->activeCamera == cameraType::overview)
	{
		s->calibrationDataOverview.intrinsic_matrix.at<float>(0, 0) = FocalLengthInPixels;
		s->calibrationDataOverview.intrinsic_matrix.at<float>(1, 1) = FocalLengthInPixels;

		double err = cv::calibrateCamera(object_points, image_points, image_size, s->calibrationDataOverview.intrinsic_matrix, s->calibrationDataOverview.distortion_coeffs, cv::noArray(), cv::noArray(), cal_flags);
	
		fs << "overview camera reprojection_error" << err << "camera_matrix" << s->calibrationDataOverview.intrinsic_matrix << "distortion_coeffs" << s->calibrationDataOverview.distortion_coeffs;
	}
	else
	{
		s->calibrationDataMicroscope.intrinsic_matrix = cv::Mat(3, 3, CV_32F);
		s->calibrationDataMicroscope.intrinsic_matrix.at<float>(0, 0) = FocalLengthInPixels;
		s->calibrationDataMicroscope.intrinsic_matrix.at<float>(1, 1) = FocalLengthInPixels;

		double err = cv::calibrateCamera(object_points, image_points, image_size, s->calibrationDataMicroscope.intrinsic_matrix, s->calibrationDataMicroscope.distortion_coeffs, cv::noArray(), cv::noArray(), cal_flags);
	
		fs << "microscope camera reprojection_error" << err << "camera_matrix" << s->calibrationDataMicroscope.intrinsic_matrix << "distortion_coeffs" << s->calibrationDataMicroscope.distortion_coeffs;
	}

	std::string createdString = fs.releaseAndGetString();

	emit LOGCONSOLE(QString::fromStdString(createdString), CONSOLECOLOURS::colour::Data);
}

cv::Mat ImageProcessing::CornerDetection(cv::Mat src, int noCorners)
{
	Mat dst, dst_norm, dst_norm_scaled, src_gray;
	dst = Mat::zeros(src.size(), CV_32FC1);

	/// Detector parameters
	cvtColor(src, src_gray, CV_BGR2GRAY);

	/// Detecting corners
	std::vector< cv::Point2f > corners;

	double qualityLevel = 0.01;
	double minDistance = 20.;
	int blockSize = 3;
	bool useHarrisDetector = true;
	double k = 0.04;
	cv::Mat mask;

	//cornerHarris(src_gray, dst, blockSize, apertureSize, k, BORDER_DEFAULT);
	goodFeaturesToTrack(src_gray, corners, noCorners, qualityLevel, minDistance, mask, blockSize, useHarrisDetector, k);

	// refine corner detection
	cornerSubPix(src_gray, corners, Size(11, 11), Size(-1, -1), TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 30, 0.1));

	for (size_t i = 0; i < corners.size(); i++)
	{
		cv::circle(src, corners[i], 10, cv::Scalar(255.), 3);
	}

	return src;
}

void calculateSymetricPoint(Point const & inPoint, Point & outPoint, Size const & psize, int padding)
{
	if (inPoint.y < padding)
		outPoint.y = 2 * padding - inPoint.y - 1;
	else if (inPoint.y > (psize.width - padding - 1))
		outPoint.y = psize.width - 2 * padding + psize.width - inPoint.y - 1;
	else
		outPoint.y = inPoint.y;

	if (inPoint.x < padding)
		outPoint.x = 2 * padding - inPoint.x - 1;
	else if (inPoint.x > (psize.height - padding - 1))
		outPoint.x = psize.height - 2 * padding + psize.height - inPoint.x - 1;
	else
		outPoint.x = inPoint.x;
}


void ImageProcessing::symmetricPadding(Mat const & image, Mat & paddedImage, int padding)
{
	//Padd with zeros
	copyMakeBorder(image, paddedImage, padding, padding, padding, padding, 0);
	MatIterator_<uchar> its;
	MatIterator_<uchar> it;

	Size psize = paddedImage.size();
	for (unsigned int j = 0; j < psize.width; j++)
	{
		for (unsigned int i = 0; i < padding; i++)
		{
			Point sp;
			Point p(i, j);
			calculateSymetricPoint(p, sp, psize, padding);
			its = paddedImage.begin<uchar>() + sp.x*paddedImage.cols + sp.y;
			it = paddedImage.begin<uchar>() + p.x*paddedImage.cols + p.y;
			*it = *its;
		}

		for (unsigned int i = psize.height - padding; i < psize.height; i++)
		{
			Point sp;
			Point p(i, j);
			calculateSymetricPoint(p, sp, psize, padding);
			its = paddedImage.begin<uchar>() + sp.x*paddedImage.cols + sp.y;
			it = paddedImage.begin<uchar>() + p.x*paddedImage.cols + p.y;
			*it = *its;
		}
	}

	for (unsigned int i = padding; i < psize.height - padding; i++)
	{
		for (unsigned int j = 0; j < padding; j++)
		{
			Point sp;
			Point p(i, j);
			calculateSymetricPoint(p, sp, psize, padding);
			its = paddedImage.begin<uchar>() + sp.x*paddedImage.cols + sp.y;
			it = paddedImage.begin<uchar>() + p.x*paddedImage.cols + p.y;
			*it = *its;
		}

		for (unsigned int j = psize.width - padding; j < psize.width; j++)
		{
			Point sp;
			Point p(i, j);
			calculateSymetricPoint(p, sp, psize, padding);
			its = paddedImage.begin<uchar>() + sp.x*paddedImage.cols + sp.y;
			it = paddedImage.begin<uchar>() + p.x*paddedImage.cols + p.y;
			*it = *its;
		}
	}
}

cv::Mat ImageProcessing::localMaxima(cv::Mat image,bool remove_plateaus)
{
	cv::Mat mask;

	// find pixels that are equal to the local neighborhood not maximum (including 'plateaus')
	cv::dilate(image, mask, cv::Mat());
	cv::compare(image, mask, mask, cv::CMP_GE);

	// optionally filter out pixels that are equal to the local minimum ('plateaus')
	if (remove_plateaus) {
		cv::Mat non_plateau_mask;
		cv::erode(image, non_plateau_mask, cv::Mat());
		cv::compare(image, non_plateau_mask, non_plateau_mask, cv::CMP_GT);
		cv::bitwise_and(mask, non_plateau_mask, mask);
	}

	return mask;
}

double ImageProcessing::PointPairToBearingDegrees(cv::Point startingPoint, cv::Point endingPoint)
{
	cv::Point originPoint = Point(endingPoint.x - startingPoint.x, endingPoint.y - startingPoint.y); // get origin point to origin by subtracting end from start
	double bearingRadians = atan2f(originPoint.y, originPoint.x); // get bearing in radians
	double bearingDegrees = bearingRadians * (180.0 / CV_PI); // convert to degrees
	bearingDegrees = (bearingDegrees > 0.0 ? bearingDegrees : (360.0 + bearingDegrees)); // correct discontinuity
	return bearingDegrees;
}

double ImageProcessing::imageMedian(cv::Mat channel)
{
	double m = (channel.rows*channel.cols) / 2;
	int bin = 0;
	double med = -1.0;

	int histSize = 256;
	float range[] = { 0, 256 };
	const float* histRange = { range };
	bool uniform = true;
	bool accumulate = false;
	cv::Mat hist;
	cv::calcHist(&channel, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);

	for (int i = 0; i < histSize && med < 0.0; ++i)
	{
		bin += cvRound(hist.at< float >(i));
		if (bin > m && med < 0.0)
			med = i;
	}

	return med;
}

double ImageProcessing::PointFromLine(cv::Point start, cv::Point end, cv::Point point)
{
	double x0 = point.x;
	double y0 = point.y;
	double x1 = start.x;
	double x2 = end.x;
	double y1 = start.y;
	double y2 = end.y;
	double dx2 = (x2 - x1)*(x2 - x1);
	double dy2 = (y2 - y1)*(y2 - y1);

	double dis = fabs((y2 - y1)*x0 - (x2 - x1)*y0 + x2*y1 - y2*x1) / sqrt(dy2 + dx2);
	return dis;
}

cv::Mat ImageProcessing::CannyEdgeDetection(cv::Mat& im, bool bConvertColor)
{

	cv::Mat src;
	Mat dst, cdst;

	bool bAutomatic = true;
	double goodFit = 0.1;

	if (im.channels() > 2)
		cv::cvtColor(im, src, cv::COLOR_BGR2GRAY);
	else
		src = im;

	/// Remove noise by blurring with a Gaussian filter
	cv::GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

	// detect histogram peak
	int v = imageMedian(src);

	int lower = 15;
	int upper = 50;

	// apply automatic Canny edge detection using the computed median
	if (bAutomatic) {
		double sigma = 0.33;

		lower = int(fmax(0, (1.0 - sigma) * v));
		upper = int(fmin(255, (1.0 + sigma) * v));
	}

	Canny(src, dst, lower, upper, 3);

	if (bConvertColor)
		cvtColor(dst, cdst, CV_GRAY2BGR);
	else
		return dst;

	return cdst;
}

cv::Mat ImageProcessing::getLines(cv::Mat& im, QColor colour)
{
	cv::Mat src;
	bool bAutomatic = true;
	double goodFit = 0.1;

	Mat dst, cdst = im.clone();

	dst = CannyEdgeDetection(im, false);

	vector<Vec4i> lines;
	// detect lines
	cv::HoughLinesP(dst, lines, 1, CV_PI / 180, 50, 50, 10);

	QVector<double> angles, averageAngles;
	double mindist = max(im.rows, im.cols);

	// draw lines
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(cdst, Point(l[0], l[1]), Point(l[2], l[3]), HelperFunctions::QC2S(colour), 3, CV_AA);

		double angle;
		/*
		double dx = l[0] - l[2];
		double dy = l[1] - l[3];

		if (dx == 0)
			angle = 180;
		else if (dy == 0)
			angle = 0;
		else
			angle = atan(dy / dx) * 180.0/CV_PI;
			*/
		angle = PointPairToBearingDegrees(Point(l[0], l[1]), Point(l[2], l[3]));
		angles.push_back(angle);

		mindist = fmin(mindist, PointFromLine(Point(l[0], l[1]), Point(l[2], l[3]), Point(im.cols/2.0, im.rows/2.0)));

		//DBOUT(" angle=" << to_string(angle).data() << std::endl);

		// only for lines within 2std of average length
	}

	double increment = 5.0;

	for(double a=increment; a<177; a+=(increment*2))
	{
		double average = 0, count = 0;
		double a1 = a;
		double a2 = a + (increment * 2);

		//wrap around
		if (a2 >= 180.0)
			a2 = 5.0;
		
		foreach(double angle, angles)
		{
			double an = fmod(angle, 180);

			if (a2 < a1)
			{
				if (an > a1 || an < a2)
				{
					average += an>a1?an:180.0+an;
					count++;
				}
			}
			else
			{
				if (an > a1 && an < a2)
				{
					average += an;
					count++;
				}
			}
		}

		if (count > 0)
		{
			averageAngles.push_back(fmod(average/count, 180.0));
		}
	}

	int fontFace = CV_FONT_HERSHEY_SIMPLEX;
	double scaleFactor = (double(im.rows)/2000.0);
	double fontScale = 5.0*scaleFactor;
	int baseline = 0;
	int offsetY = 0;
	int thickness = 5.0*scaleFactor;

	std::string text = to_string(mindist);
	Size textSize = getTextSize(text, fontFace, fontScale, 1, &baseline);

	offsetY += textSize.height + 20.0*scaleFactor;

	Point textOrg(0, offsetY);

	if(mindist <1)
		putText(cdst,text, textOrg, fontFace, fontScale, cv::Scalar(0, 255, 0), thickness, 8);
	else
		putText(cdst, text, textOrg, fontFace, fontScale, cv::Scalar(0, 0, 255), thickness, 8);

	offsetY = 0;

	// output text
	foreach(double angle, averageAngles)
	{
		std::string text = to_string(angle);
		Size textSize = getTextSize(text, fontFace, fontScale, 1, &baseline);

		offsetY += textSize.height+20.0*scaleFactor;

		Point textOrg((cdst.cols - textSize.width), offsetY);

		if(fabs(90.0-fmod(angle,90.0))<goodFit)
			putText(cdst, text, textOrg, fontFace, fontScale, cv::Scalar(0, 255, 0), thickness, 8);
		else
			putText(cdst, text, textOrg, fontFace, fontScale, cv::Scalar(0, 0, 255), thickness, 8);

		DBOUT("average angle=" << text.data() << std::endl);
	}
	
	return cdst;
}


/**
*
*  Threshold image between min and max greyscale values
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   ImageProcessing::Threshold
* Qualifier 
* @param     Mat & im 
* @param     int min 
* @param     int max 
* @return    cv::Mat
* Access     public 
*/
cv::Mat ImageProcessing::Threshold(Mat& im, int min, int max, thresholdType::thresholdType type, bool bConvertToColor)
{

#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
	/* 0: Binary
	1: Binary Inverted
	2: Threshold Truncated
	3: Threshold to Zero
	4: Threshold to Zero Inverted
	*/

	cv::Mat dst;

	cv::Mat gray;

	if (im.channels() > 2)
		cv::cvtColor(im, gray, cv::COLOR_BGR2GRAY);
	else
		gray = im;

	int max_BINARY_value = 255;

	if (type == thresholdType::Otzu)
	{
		threshold(gray, dst, 0, 255, cv::THRESH_BINARY + cv::THRESH_OTSU);
	}
	else if (type == thresholdType::adaptive)
	{
		cv::adaptiveThreshold(gray, dst, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 15, 10);
	}
	else
	{
		//If  src(x,y) is greater than thresh, the new pixel value will be set to 0.
		threshold(gray, dst, max, max_BINARY_value, cv::THRESH_TOZERO_INV);

		//If src(x, y) is lower than thresh, the new pixel value will be set to 0.
		threshold(dst, dst, min, max_BINARY_value, cv::THRESH_TOZERO);

		// now make all non zero pixels max_BINARY_value
		threshold(dst, dst, 0, max_BINARY_value, cv::THRESH_BINARY);
	}

	if(bConvertToColor)
		cv::cvtColor(dst, dst, cv::COLOR_GRAY2BGR);

	return dst;
}

/**
*
*  Returns posterized opencv image which has NoClusters numbers of levels
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   ImageProcessing::HistogramClusteringGray
* Qualifier 
* @param     cv::Mat im 
* @param     int NoClusters 
* @return    cv::Mat
* Access     public 
*/
cv::Mat ImageProcessing::HistogramClusteringGray(cv::Mat im, int NoClusters)
{

#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
	int i = 0;
	cv::Mat dst, hsvImage;
	// get histogram of hue 0-360
	int histSize;

	float range[] = { 0,0 };
	const float* histRange;

	bool uniform = true;
	bool accumulate = false;

	// pClusterHist has the cluster for each hue value
	std::vector<int*> cImages;
	int* pClusterHist = nullptr;
	cv::Mat* histImage;
	cv::Mat b_hist;
	std::vector<cv::Mat> hsv_planes;

	int w, h, w1 = im.cols, h1 = im.rows;

	cv::Mat image1_gray;

	DBOUT("greyscale image" << std::endl);

	// get histogram of hue 0-360
	histSize = 256;

	range[1] = (float)histSize;

	histRange = { range };

	if (im.channels() > 2)
		cv::cvtColor(im, image1_gray, CV_BGR2GRAY);
	else
		image1_gray = im;

	histImage = &image1_gray;
	
	b_hist.create(histSize, 1, CV_32SC1);

	// Compute the histogram:
	calcHist(histImage, 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);

	// here we cluster image based on its hue histogram /////////////////
	pClusterHist = new int[histSize];

	histClusterRGBImage(b_hist, pClusterHist, histSize, NoClusters);//histClusterEqual(b_hist, histSize, NoClusters); 

	// //////////////////////////////////////////////////////////////////

	// assign clusters to test image
	cv::Mat cMat(im.size(), CV_8UC3);

	// label image with cluster
	for (int j = 0; j < h1; j++)
		for (i = 0; i < w1; i++)
		{
			// gets cluster number up to max NoClusters 
			float val = (float)pClusterHist[cvFloor(histImage->at<uchar>(j, i))];

			val = val * (255.0 / double(NoClusters - 1));

			cMat.ptr<uchar>(j)[(i * 3)] = static_cast<unsigned char>(val);
			cMat.ptr<uchar>(j)[(i * 3) + 1] = static_cast<unsigned char>(val);
			cMat.ptr<uchar>(j)[(i * 3) + 2] = static_cast<unsigned char>(val);
		}
		
	delete[] pClusterHist;

	return cMat;
}

/**
*
*  Returns image that has been posterized based on method of histogram variances
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   ImageProcessing::histClusterRGBImage
* Qualifier 
* @param     cv::Mat hueHist 
* @param     int histSize 
* @param     int NoClusters 
* @return    int*
* Access     public 
*/
void ImageProcessing::histClusterRGBImage(cv::Mat hueHist, int* pClusterHist, int histSize, int NoClusters)
{

#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
	int sum, i, j;
	std::vector<histCluster>::iterator clusterToMerge1, clusterToMerge2, iI, jI, kI;
	float PCK_1, PCK_2, PCK_12, M_CK_1, M_CK_2, M_CK_12, E_CK_1, E_CK_2, SA_CK_12, SL_CK_12, DIST_CK_12;
	long n;
	float f, meanHue, varHue, totHueVar, bestMean, bestVar;
	std::vector<histogramBar> h1, h2;

	// create array of lists size NoClusters for clusters
	std::vector<histCluster> clusterList;

	// normalize histogram to sum to 1
	normalize(hueHist, hueHist, 1, 0, NORM_L1);

	for (i = 0; i<histSize; i++)
	{
		f = hueHist.at<float>(i);

		if (f > 0)
		{
			// object representing histogram bar
			histogramBar c;
			c.freq = f;
			c.hue = i;

			std::vector<histogramBar> hb;     // list for all histogram bars in cluster

			hb.push_back(c);

			// object representing cluster of histogram bars
			histCluster h;

			h.varHue = 0;              // average hue of cluster
			h.meanHue = i;
			h.hueList.push_back(i);     // list of hues in clusters
			h.column = hb;              // list of histogram bars in cluster

			clusterList.push_back(h);   // add to cluster list
		}
	}

	// 1) check all clusters against each other find best cluster merger (min dist) (if NoMergedClusters == NoClusters then end)
	while (clusterList.size() > NoClusters)
	{
		bestVar = FLT_MAX;

		// compare all clusters
		for (iI = clusterList.begin(); iI != clusterList.end(); iI++)
		{
			jI = std::next(iI);

			// wrap cluster to start
			if (clusterList.end() == jI)
				jI = clusterList.begin();

			n = 0;
			meanHue = 0;
			PCK_1 = 0; PCK_2 = 0; PCK_12 = 0; E_CK_1 = 0; E_CK_2 = 0; M_CK_1 = 0; M_CK_2 = 0; M_CK_12 = 0; SA_CK_12 = 0; SL_CK_12 = 0;

			// need probability of pixels in each cluster P(Ck1) & P(Ck2)

			// for each bar get sum
			foreach(histogramBar l, (*iI).column)
			{
				PCK_1 += l.freq;
				E_CK_1 += l.hue*l.freq;
			}
			foreach(histogramBar l, (*jI).column)
			{
				PCK_2 += l.freq;
				E_CK_2 += l.hue*l.freq;
			}

			// need probability of pixels in merged cluster P(Ck1) + P(Ck2)
			PCK_12 = PCK_1 + PCK_2;

			// need expected value of pixels in clusters  1/P(Ck)*sum(i*p(i)), i = subset of k
			if (PCK_1 <= 0 || PCK_2 <= 0)
				continue;

			M_CK_1 = (1.0 / PCK_1)*E_CK_1;
			M_CK_2 = (1.0 / PCK_2)*E_CK_2;

			float PCK_1_2 = PCK_1 + PCK_2;

			// need mean value of pixels in merged cluster M(Ck1 U Ck2)
			M_CK_12 = ((PCK_1*M_CK_1) + (PCK_2*M_CK_2)) / PCK_1_2;

			float M_CK_1_2 = M_CK_1 - M_CK_2;

			// need interclass variance of merged cluster
			SL_CK_12 = ((PCK_1*PCK_2) / PCK_1_2) * (M_CK_1_2*M_CK_1_2);

			float sum_var = 0;

			foreach(histogramBar l, (*iI).column)
			{
				float s = (l.hue - M_CK_12);
				sum_var += (s*s) * l.freq;
			}
			foreach(histogramBar l, (*jI).column)
			{
				float s = (l.hue - M_CK_12);
				sum_var += (s*s) * l.freq;
			}

			// need global intra-class variance sigmaA of merged cluster
			SA_CK_12 = (1.0 / PCK_1_2)*sum_var;

			// cluster distance score
			DIST_CK_12 = SL_CK_12*SA_CK_12;

			// store best score / best clusters to merge
			if (DIST_CK_12 < bestVar)
			{
				clusterToMerge1 = iI;
				clusterToMerge2 = jI;
				bestMean = M_CK_12;
				bestVar = DIST_CK_12;
			}
		}

		if (bestVar < FLT_MAX)
		{
			(*clusterToMerge2).hueList.insert(std::end((*clusterToMerge2).hueList), std::begin((*clusterToMerge1).hueList), std::end((*clusterToMerge1).hueList));
			(*clusterToMerge2).column.insert(std::end((*clusterToMerge2).column), std::begin((*clusterToMerge1).column), std::end((*clusterToMerge1).column));

			(*clusterToMerge2).varHue = bestVar;
			(*clusterToMerge2).meanHue = bestMean;

			// remove cluster using iterators
			clusterList.erase(clusterToMerge1);
		}
		else
		{
			DBOUT("no best clusters choosen!" << std::endl);
		}
	}

	// sort clusters according to mean
	std::sort(clusterList.begin(), clusterList.end(), [](histCluster const& a, histCluster const& b) { return a.meanHue < b.meanHue; });

	// label histogram with cluster ID
	for (i = 0, sum = 0.0; i < histSize; i++)
		pClusterHist[i] = 0;

	int cl = 0;

	DBOUT("hue cluster list, size=" << NoClusters << std::endl);

	// 3) now go through clusters and label image
	foreach(histCluster c, clusterList)
	{
		foreach(int c, c.hueList)
			DBOUT(c << ", ");
		DBOUT(std::endl);

		foreach(int i, c.hueList)
		{
			pClusterHist[i] = cl;
		}
		cl++;
	}
}


/**
*
*  Performs modal filter on opencv image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   ImageProcessing::modalFilter
* Qualifier 
* @param     Mat & im 
* @param     int w 
* @param     int h 
* @param     int fSize 
* @param     int NoFocusImages 
* @return    void
* Access     public 
*/
void ImageProcessing::modalFilter(Mat& im, int w, int h, int fSize, int NoFocusImages)
{
#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	int i, j, x, y, c, k, lev, bestLevel, startx, starty, endx, endy;
	int* valueArray = new int[NoFocusImages];
	Mat bestLevels = cv::Mat(h, w, CV_8SC1, Scalar(0));
	int fs1 = fSize >> 1;

	for (i = 0; i < w; i++)
	{
		for (j = 0; j < h; j++)
		{
			memset(valueArray, 0, sizeof(int)*NoFocusImages);

			startx = i - fs1;
			endx = i + fs1;
			starty = j - fs1;
			endy = j + fs1;

			// fs1 area
			for (x = startx; x<endx; x++)
				for (y = starty; y<endy; y++)
				{
					if (x >= 0 && y >= 0 && x<w && y<h)
					{
						if (im.ptr<char>(y)[x] < NoFocusImages && im.ptr<char>(y)[x] >= 0)
							valueArray[im.ptr<char>(y)[x]]++;     // SXDY
					}
				}

			// get maximum value in values
			for (k = 0, bestLevel = 0; k < NoFocusImages; k++)
			{
				c = valueArray[k];

				if (c > bestLevel)
				{
					bestLevel = c;
					lev = k;
				}
			}

			bestLevels.ptr<char>(j)[i] = lev;
		}
	}

	bestLevels.copyTo(im);
	delete[] valueArray;
}


/**
*
*  performs modal filter on 1D int* image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   ImageProcessing::modalFilter
* Qualifier 
* @param     int * im 
* @param     int w 
* @param     int h 
* @param     int fSize 
* @param     int NoFocusImages 
* @return    void
* Access     public 
*/
void ImageProcessing::modalFilter(int* im, int w, int h, int fSize, int NoFocusImages)
{
#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	int i, j, x, y, c, k, lev, bestLevel, startx, starty, endx, endy;
	int* valueArray = new int[NoFocusImages];
	int* bestLevels = new int[w*h];
	int fs1 = fSize >> 1;

	memset(bestLevels, 0, sizeof(int)*w*h);

	for (i = 0; i < w; i++)
	{
		for (j = 0; j < h; j++)
		{
			memset(valueArray, 0, sizeof(int)*NoFocusImages);

			startx = i - fs1;
			endx = i + fs1;
			starty = j - fs1;
			endy = j + fs1;

			// fs1 area
			for (x = startx; x<endx; x++)
				for (y = starty; y<endy; y++)
				{
					if (x >= 0 && y >= 0 && x<w && y<h)
					{
						if (im[x + y*w] < NoFocusImages && im[x + y*w] >= 0)
							valueArray[im[x + y*w]]++;     // SXDY
					}
				}

			// get maximum value in values
			for (k = 0, bestLevel = 0; k < NoFocusImages; k++)
			{
				c = valueArray[k];

				if (c > bestLevel)
				{
					bestLevel = c;
					lev = k;
				}
			}

			bestLevels[i + j*w] = lev;
		}
	}

	memcpy(im, bestLevels, sizeof(int)*w*h);

	delete[] bestLevels;
	delete[] valueArray;
}

/**
*
*  Performs Guassian blur filter on 1D int* image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   ImageProcessing::GaussianBlur
* Qualifier 
* @param     int * im 
* @param     int w 
* @param     int h 
* @param     int repeat 
* @return    void
* Access     public 
*/
void ImageProcessing::GaussianBlur(int* im, int w, int h, int repeat)
{
#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	int i, i1, j1, j, k;
	double sum;
	int coeffLength = 13;
	int hfw = coeffLength >> 1;

	double coeff[] = { 0, 0.000003, 0.000229, 0.005977, 0.060598, 0.24173, 0.382925, 0.24173,
		0.060598, 0.005977, 0.000229, 0.000003, 0 };

	double*  dim = new double[w*h];

	for (i = 0; i<w*h; i++)
		dim[i] = (double)im[i];

	for (int r = 0; r<repeat; r++)
	{
		// along i - direction
		for (j = 0; j<h; j++)
		{
			for (i = 0; i<w; i++)
			{
				for (sum = 0.0, k = -hfw; k <= hfw; k++)
				{
					i1 = HelperFunctions::reflect(w, i - k);
					sum = sum + coeff[k + hfw] * (double)dim[i1 + j*w];
				}
				dim[i + j*w] = sum;
			}
		}

		for (j = 0; j<h; j++)
		{
			for (i = 0; i<w; i++)
			{
				for (sum = 0.0, k = -hfw; k <= hfw; k++)
				{
					j1 = HelperFunctions::reflect(h, j - k);
					sum = sum + coeff[k + hfw] * (double)dim[i + j1*w];
				}
				dim[i + j*w] = sum;
			}
		}
	}
	for (i = 0; i<w*h; i++)
		im[i] = (int)round(dim[i]);

	delete[] dim;
}


/**
* Code for thinning a binary image using Zhang-Suen algorithm.
*
* Author:  Nash (nash [at] opencv-code [dot] com)
* Website: http://opencv-code.com

* Perform one thinning iteration.
* Normally you wouldn't call this function directly from your code.
*
* Parameters:
* 		im    Binary image with range = [0,1]
* 		iter  0=even, 1=odd
*/
void thinningIteration(cv::Mat& img, int iter)
{
	CV_Assert(img.channels() == 1);
	CV_Assert(img.depth() != sizeof(uchar));
	CV_Assert(img.rows > 3 && img.cols > 3);

	cv::Mat marker = cv::Mat::zeros(img.size(), CV_8UC1);

	int nRows = img.rows;
	int nCols = img.cols;

	if (img.isContinuous()) {
		nCols *= nRows;
		nRows = 1;
	}

	int x, y;
	uchar *pAbove;
	uchar *pCurr;
	uchar *pBelow;
	uchar *nw, *no, *ne;    // north (pAbove)
	uchar *we, *me, *ea;
	uchar *sw, *so, *se;    // south (pBelow)

	uchar *pDst;

	// initialize row pointers
	pAbove = nullptr;
	pCurr = img.ptr<uchar>(0);
	pBelow = img.ptr<uchar>(1);

	for (y = 1; y < img.rows - 1; ++y) {
		// shift the rows up by one
		pAbove = pCurr;
		pCurr = pBelow;
		pBelow = img.ptr<uchar>(y + 1);

		pDst = marker.ptr<uchar>(y);

		// initialize col pointers
		no = &(pAbove[0]);
		ne = &(pAbove[1]);
		me = &(pCurr[0]);
		ea = &(pCurr[1]);
		so = &(pBelow[0]);
		se = &(pBelow[1]);

		for (x = 1; x < img.cols - 1; ++x) {
			// shift col pointers left by one (scan left to right)
			nw = no;
			no = ne;
			ne = &(pAbove[x + 1]);
			we = me;
			me = ea;
			ea = &(pCurr[x + 1]);
			sw = so;
			so = se;
			se = &(pBelow[x + 1]);

			int A = (*no == 0 && *ne == 1) + (*ne == 0 && *ea == 1) +
				(*ea == 0 && *se == 1) + (*se == 0 && *so == 1) +
				(*so == 0 && *sw == 1) + (*sw == 0 && *we == 1) +
				(*we == 0 && *nw == 1) + (*nw == 0 && *no == 1);
			int B = *no + *ne + *ea + *se + *so + *sw + *we + *nw;
			int m1 = iter == 0 ? (*no * *ea * *so) : (*no * *ea * *we);
			int m2 = iter == 0 ? (*ea * *so * *we) : (*no * *so * *we);

			if (A == 1 && (B >= 2 && B <= 6) && m1 == 0 && m2 == 0)
				pDst[x] = 1;
		}
	}

	img &= ~marker;
}

/**
* Function for thinning the given binary image
*
* Parameters:
* 		src  The source image, binary with range = [0,255]
* 		dst  The destination image
*/
void ImageProcessing::thinning(const cv::Mat& src, cv::Mat& dst)
{
	dst = src.clone();
	dst /= 255;         // convert to binary image

	cv::Mat prev = cv::Mat::zeros(dst.size(), CV_8UC1);
	cv::Mat diff;

	do {
		thinningIteration(dst, 0);
		thinningIteration(dst, 1);
		cv::absdiff(dst, prev, diff);
		dst.copyTo(prev);
	} while (cv::countNonZero(diff) > 0);

	dst *= 255;
}

cv::Mat ImageProcessing::getConnectedComponentImage(cv::Mat& bin, cv::Mat& labels, cv::Mat& stats, cv::Mat& centroids)
{
	cv::Mat out = cv::Mat(bin.rows, bin.cols, CV_8UC3, cvScalar(0.));
	const int connectivity_8 = 8;

	int nLabels = connectedComponentsWithStats(bin, labels, stats, centroids, connectivity_8, CV_32S);
	int inc = 255 / nLabels;
	int rgb = 0, r = 0, g = 0, b = 0;

	// colorise
	inc = (255 * 255 * 255) / nLabels;

	for (int i = 1; i<nLabels; i++)
	{
		cv::Mat mask = labels == i;

		rgb += inc;

		r = rgb % 255;
		g = (rgb / 255) % 255;
		b = (rgb / (255 * 255)) % 255;

		out.setTo(cv::Scalar(r, g, b), mask);
	}

	/*
	applyColorMap(labels, out, COLORMAP_JET);

	labels.convertTo(labels, CV_8U);

	normalize(labels, labels, 0, 255, NORM_MINMAX, -1, Mat());
	*/
	return out;

}
