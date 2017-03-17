#include "FocusStack.h"
#include <cmath>
#include <QObject>

#include "opencv2/opencv.hpp"
#include "opencv/highgui.h"
#include "haar.h"


/**
*
* Get energy image (summed coefficient magnitude) from haar wavelet pyramid
*
* @author    David Watts
* @since     2017/03/08
*
* FullName   Haar::HaarEnergy
* Qualifier
* @param     cv::Mat data
* @param     cv::Mat & energyImage
* @param     int width
* @param     int height
* @param     int iterations
* @param     bool laplace
* @param     bool bSquare
* @return    void
* Access     private
*/
void Haar::HaarEnergy(cv::Mat data, cv::Mat &energyImage, int width, int height, int iterations, bool laplace, bool bSquare)
{
	int ii, ij, oi, oj;

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			for (int k = 0; k < iterations; k++)
			{
				ii = i >> (k + 1);
				ij = j >> (k + 1);

				oi = width >> (k + 1);
				oj = height >> (k + 1);

				if (bSquare)
					energyImage.ptr<double>(j)[i] += ((double)data.ptr<double>(oj + ij)[oi + ii] * data.ptr<double>(oj + ij)[oi + ii]) / (double)(1 << k); // DXDY
				else
					energyImage.ptr<double>(j)[i] += fabs((double)data.ptr<double>(oj + ij)[oi + ii] / (double)(1 << k)); // DXDY

				if (!laplace)
				{
					if (bSquare)
						energyImage.ptr<double>(j)[i] += ((double)data.ptr<double>(oj + ij)[ii] * data.ptr<double>(oj + ij)[ii]) / (double)(1 << k);    // SXDY
					else
						energyImage.ptr<double>(j)[i] += fabs((double)data.ptr<double>(oj + ij)[ii] / (double)(1 << k));    // SXDY
					if (bSquare)
						energyImage.ptr<double>(j)[i] += ((double)data.ptr<double>(ij)[oi + ii] * data.ptr<double>(ij)[oi + ii]) / (double)(1 << k);    // SYDX
					else
						energyImage.ptr<double>(j)[i] += fabs((double)data.ptr<double>(ij)[oi + ii] / (double)(1 << k));    // SYDX
				}
			}
		}
	}
}

/**
*
* perform Laplacian pyramid
*
* @author    David Watts
* @since     2017/03/08
*
* FullName   Haar::LaplacianPyramid
* Qualifier
* @param     cv::Mat im
* @param     int levels
* @param     bool includeScale
* @return    cv::Mat
* Access     private
*/
cv::Mat Haar::LaplacianPyramid(cv::Mat im, int levels, bool includeScale)
{
	int l;
	cv::Mat imOut = cv::Mat(im.rows * 2, im.cols * 2, im.type(), cv::Scalar(0));

	cv::Mat currentImg = im;

	for (l = 0; l<levels; l++) {
		cv::Mat down, up;

		cv::pyrDown(currentImg, down);

		cv::pyrUp(down, up, currentImg.size());

		cv::Mat lap = currentImg - up;

		int y = imOut.rows >> (l + 1);
		int x = imOut.cols >> (l + 1);

		cv::Rect r = cv::Rect(x, y, lap.cols, lap.rows);

		lap.copyTo(imOut(r));

		currentImg = down;
	}

	if (includeScale)
	{
		int y = imOut.rows >> (levels + 1);
		int x = imOut.cols >> (levels + 1);

		cv::Rect r = cv::Rect(x, y, currentImg.cols, currentImg.rows);

		currentImg.copyTo(imOut(r));
	}
	return imOut;
}


	

/**
*
* Get OpenCV image of best (modal) values from Pyramid composition
*
* @author    David Watts
* @since     2017/03/08
*
* FullName   Haar::PyramidLevels
* Qualifier
* @param     cv::Mat data
* @param     int width
* @param     int height
* @param     int iterations
* @param     const int NoFocusImages
* @return    cv::Mat
* Access     private
*/
cv::Mat Haar::PyramidLevels(cv::Mat data, int width, int height, int iterations, const int NoFocusImages)
{
	
	int ii, ij, oi, oj, c, x, y, lev;

	int* valueArray = new int[NoFocusImages];

	cv::Mat bestlevels = cv::Mat(height, width, CV_8SC1, cv::Scalar(0));

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			memset(valueArray, 0, sizeof(int)*NoFocusImages);

			for (int k = 0; k < iterations; k++)   // index into wavelet image
			{
				ii = i >> (k + 1);
				ij = j >> (k + 1);

				oi = width >> (k + 1);
				oj = height >> (k + 1);

				if (data.ptr<char>(oj + ij)[oi + ii] >= 0 && data.ptr<char>(oj + ij)[oi + ii] < NoFocusImages)
					valueArray[data.ptr<char>(oj + ij)[oi + ii]]++; // DXDY

				if (data.ptr<char>(oj + ij)[ii] >= 0 && data.ptr<char>(oj + ij)[ii] < NoFocusImages)
					valueArray[data.ptr<char>(oj + ij)[ii]]++;    // SXDY

				if (data.ptr<char>(ij)[oi + ii] >= 0 && data.ptr<char>(ij)[oi + ii] < NoFocusImages)
					valueArray[data.ptr<char>(ij)[oi + ii]]++;    // SYDX

			}

			int bestLevel = 0;
			// get maximum value in value histogram (more frequent level value)
			for (int k = 0; k < NoFocusImages; k++)
			{
				c = valueArray[k];

				if (c > bestLevel)
				{
					bestLevel = c;
					lev = k;
				}
			}
			// should at least count one observation
			if (bestLevel>0)
				bestlevels.ptr<char>(j)[i] = lev;
			else
				bestlevels.ptr<char>(j)[i] = -1;
		}
	}

	delete[] valueArray;

	return bestlevels;
}

	

/**
*
*  Perform 2D Haar wavelet pyramid transform with OpenCV image
*
* @author    David Watts
* @since     2017/03/08
*
* FullName   Haar::Haar2
* Qualifier
* @param     cv::Mat & data
* @param     int iterations (no of levels)
* @return    void
* Access     private
*/
void Haar::Haar2(cv::Mat& data, int iterations)
{
	bool zeroSmooth = false;

	if (data.channels() == 1)
	{
		int width = data.cols;
		int height = data.rows;

		double* row;
		double* col;

		for (int k = 0; k < iterations; k++)
		{
			int levHeight = height >> k;
			int levWidth = width >> k;

			row = new double[levWidth];

			for (int j = 0; j < levHeight; j++)
			{
				for (int i = 0; i < levWidth; i++)
					row[i] = (double)data.ptr<double>(j)[i];

				Haar::Haar1(row, levWidth);

				for (int i = 0; i < levWidth; i++)
					data.ptr<double>(j)[i] = row[i];
			}

			col = new double[levHeight];

			for (int i = 0; i < levWidth; i++)
			{
				for (int j = 0; j < levHeight; j++)
					col[j] = (double)data.ptr<double>(j)[i];

				Haar::Haar1(col, levHeight);

				for (int j = 0; j < levHeight; j++)
					data.ptr<double>(j)[i] = col[j];
			}

			delete[] row;
			delete[] col;
		}

		if (zeroSmooth)
		{
			int levHeight = height >> (iterations);
			int levWidth = width >> (iterations);

			for (int j = 0; j < levHeight + 3; j++)
				for (int i = 0; i < levWidth + 3; i++)
					data.ptr<double>(j)[i] = 0;

		}
	}
	else
	{
		std::cout << " " << __FUNCTION__ << ": error processing image with more than one channel" << std::endl;
	}
}



/*
void LaplacianEnergy(QList<Mat>& arrIM, Mat& smallestLevel, int levels)
{
foreach(Mat im , arrIM) {
int valueArray[NoFocusImages];

Mat bestlevels = cv::Mat(height, width, CV_8SC1, cv::Scalar(0));

for (int i = 0; i < width; i++)
{
for (int j = 0; j < height; j++)
{
memset(valueArray, 0, sizeof(int)*NoFocusImages);

// bottom left SYDX
indi   = i;           indj   = j;
startx = indi - fs1;   starty = indj - fs1;
endx   = indi + fs1;   endy   = indj + fs1;

// center
if(data[indi+indj*width]>=0)
valueArray[data[indi+indj*width]]+=15; // center pixel add equal to surround

// fs1 area
for(x=startx; x<endx; x++)
for(y=starty; y<endy; y++)
{
if(x>=0 && y>=oj && x<oi && y<oj+oj)
{
// surround
if(im.ptr(y)[x]>=0)
valueArray[im.ptr(y)[x]]++;
}
}

int bestLevel = 0;
// get maximum value in value histogram (more frequent level value)
for (int k = 0; k < NoFocusImages; k++)
{
c = valueArray[k];

if(c > bestLevel)
{
bestLevel = c;
lev = k;
}
}
// should at least count one observation
if(bestLevel>0)
bestlevels.ptr<char>(j)[i] = lev;
else
bestlevels.ptr<char>(j)[i] = -1;
}
}

return bestlevels;

}
*/