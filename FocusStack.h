// Targeter - target identification software for EUCALL workpackage 6
// Licensed under the GPL License. See LICENSE file in the project root for full license information.
// Copyright(C) 2017  David Watts 

#ifndef FOCUSSTACK_H
#define FOCUSSTACK_H

#include <QVector>

// for auto sorted list
#include <set>
#include <iterator>
#include <algorithm>

#include "opencv2/opencv.hpp"
#include "opencv/highgui.h"
#include "mainwindow.h"




/**
* class that manages performing focus stack, ie. takes image sequence and combines them into single in focus image
*/
class FocusStack {
public:
	static double getImageFocusLevel(targeterImage& image);
	static double getImageFocusLevel(cv::Mat& m);

	static int getBestFocusImage(QVector<cv::Mat> imageStack, QVector<double>& focusValues, FOCUSALGO::algo Algorithm = FOCUSALGO::DXDY);
	static double getFocusImage(cv::Mat& m, FOCUSALGO::algo Algorithm);
	
    static cv::Mat* processImageStack(std::vector<targeterImage>& imageStack, std::vector<int>& imageIndexes, MainWindow* pMainWindow);
	static cv::Mat* processImageStack2(std::vector<targeterImage>& imageStack, std::vector<int>& imageIndexes, MainWindow* pMainWindow);
	static cv::Mat* processImageStack3(std::vector<targeterImage>& imageStack, std::vector<int>& imageIndexes, MainWindow* pMainWindow);
	static cv::Mat processImageStack4(std::vector<targeterImage>& imageStack, std::vector<int>& imageIndexes, MainWindow* pMainWindow);

	static cv::Mat* mergeImageStack(std::vector<targeterImage>& imageStack, cv::Mat indexImage, int w, int h);

    // focussing algorithms /////////////////////////////////
	static void fillErrorRegions(int* im, int w, int h, int fSize, int NoFocusImages);
	static void fillErrorRegions(cv::Mat &im, int w, int h, int fSize, int NoFocusImages);


	static cv::Mat createLaplacianEnergyImage(cv::Mat im, int levels, bool bDisplay = true, bool bEnergy = false);
	static double** getEntropyImage(QMap<int, cv::Mat>& arrWE, int w, int h, std::vector<int>& imageIndexes, double& bestEntropyValue);
	static double*** getEnergyProbabilityImage(QMap<int, cv::Mat>& arrWE, double** energyEntropy, int w, int h, std::vector<int>& imageIndexes, double bestEntropyValue, double entropyFactor, double distanceFactor);

	// LAPM
	static double modifiedLaplacian(const cv::Mat& src);

    // OpenCV port of 'LAPV' algorithm (Pech2000)
	static double varianceOfLaplacian(const cv::Mat& src);

    // OpenCV port of 'TENG' algorithm (Krotkov86)
	static double tenengrad(const cv::Mat& src, int ksize);

    // OpenCV port of 'GLVN' algorithm (Santos97)
	static double normalizedGraylevelVariance(const cv::Mat& src);

	static double simpleDerivativeEnergy(const cv::Mat& data, bool horizontal);

    // helper pixel access functions
};

template<typename T>
T spiralIteration(cv::Mat& im, int i, int j, int w, int h, int n, bool bLessThanZero = true)
{
	int d = 1;
	int	m = 1;
	int x = 0;
	int y = 0;
	int count = 0;
	int noValues = 5;
	int sum = 0;

	std::multiset<int> sortedPixelList;

	//DBOUT(im.ptr<T>(j)[i]<<", ");

	if (im.ptr<T>(j)[i] > (bLessThanZero?-1:0))
		return im.ptr<T>(j)[i];

	for (int k = 0; k < n; k++)
	{
		while (2 * x * d < m)
		{
			x = x + d;

			if (i + x < w && i + x >= 0 && j + y < h && j + y >= 0)
			{
				// check x,y position here
				if (im.ptr<T>(j + y)[i + x] > (bLessThanZero ? -1 : 0))
				{
					//sum += im.ptr<T>(j + y)[i + x];
					
					sortedPixelList.insert(im.ptr<T>(j + y)[i + x]);
					count++;

					if (count >= noValues)
					{
						auto iter = sortedPixelList.cbegin();
						std::advance(iter, noValues / 2);	// median

						//return sum / count;
						return *iter; 
					}
				}
			}
		}

		while (2 * y * d < m)
		{
			y = y + d;

			if (i + x < w && i + x >= 0 && j + y < h && j + y >= 0)
			{
				// check x,y position here
				if (im.ptr<T>(j + y)[i + x] > (bLessThanZero ? -1 : 0))
				{
					//sum += im.ptr<T>(j + y)[i + x];

					sortedPixelList.insert(im.ptr<T>(j + y)[i + x]);
					count++;

					if (count >= noValues)
					{
						auto iter = sortedPixelList.cbegin();
						std::advance(iter, noValues / 2);	// median

						//return sum / count;
						return *iter;
					}
				}
			}
		}

		d = -1 * d;
		m = m + 1;
	}

	return im.ptr<T>(j)[i];
}


// pixels <0 are mask pixels, input image is integer image
template<typename T>
void FillMissingPixels(cv::Mat& in, cv::Mat& out,  bool bLessThanZero = true)
{
	int w = in.cols;
	int h = in.rows;

	for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
		{
			if (in.ptr<T>(j)[i] < (bLessThanZero ? 0 : 1))	// if pixel is masked then get best neighbour
			{
				out.ptr<T>(j)[i] = spiralIteration<T>(in, i, j, w, h, 80, bLessThanZero);
			}
			else
				out.ptr<T>(j)[i] = in.ptr<T>(j)[i];
		}
}


#endif // IMAGEPROCESSING_H
