#include <iostream>
#include <iomanip>
#include <limits>
#include <QDebug>
#include <vector>
#include "opencv2/opencv.hpp"
#include "opencv/highgui.h"
#include "imageprocessing.h"
#include "HelperFunctions.h"

#include "globals.h"


using namespace cv;
using namespace std;

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
cv::Mat ImageProcessing::Threshold(Mat& im, int min, int max)
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
	cv::cvtColor(im, gray, cv::COLOR_BGR2GRAY);

	int max_BINARY_value = 255;

	//If  src(x,y) is greater than thresh, the new pixel value will be set to 0.
	threshold(gray, dst, max, max_BINARY_value, 4);

	//If src(x, y) is lower than thresh, the new pixel value will be set to 0.
	threshold(dst, dst, min, max_BINARY_value, 3);

	// now make all non zero pixels max_BINARY_value
	threshold(dst, dst, 0, max_BINARY_value, 0);

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
	int* pClusterHist = NULL;
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

	cv::cvtColor(im, image1_gray, CV_BGR2GRAY);

	histImage = &image1_gray;
	
	b_hist.create(histSize, 1, CV_32SC1);

	// Compute the histogram:
	calcHist(histImage, 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);

	// here we cluster image based on its hue histogram /////////////////

	pClusterHist = histClusterRGBImage(b_hist, histSize, NoClusters);//histClusterEqual(b_hist, histSize, NoClusters); 

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
int* ImageProcessing::histClusterRGBImage(cv::Mat hueHist, int histSize, int NoClusters)
{

#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
	int sum, i, j;
	std::vector<histCluster>::iterator clusterToMerge1, clusterToMerge2, iI, jI, kI;
	float PCK_1, PCK_2, PCK_12, M_CK_1, M_CK_2, M_CK_12, E_CK_1, E_CK_2, SA_CK_12, SL_CK_12, DIST_CK_12;
	long n;
	int* pClusterHist = new int[histSize];
	float f, meanHue, varHue, totHueVar, bestMean, bestVar;
	std::vector<histogramBar> h1, h2;

	// create array of lists size NoClusters for clusters
	std::vector<histCluster> clusterList;

	// normalise histogram to sum to 1
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

	return pClusterHist;
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
