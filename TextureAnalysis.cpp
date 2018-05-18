#include "TextureAnalysis.h"
#include "imageprocessing.h"
#include "opencv2/opencv.hpp"
#include <map>

using namespace cv;


TextureAnalysis::TextureAnalysis()
{
	
}


TextureAnalysis::~TextureAnalysis()
{
}

float TextureAnalysis::calculateEntropyOfRegion(Mat const & grayimage, int offset_x, int offset_y, int region)
{
	int x, y, r2 = region >> 1;
	float p, entropyVal = 0, count=0;
	uint hist[255] = {0};
	uint val, nMin = grayimage.cols*grayimage.rows, nMax = 0;

	// get hist
	for (x = offset_x - r2; x <= offset_x + r2; x++)
	{
		for (y = offset_y - r2; y <= offset_y + r2; y++)
		{
			if (x >= 0 && y >= 0 && x < grayimage.cols && y < grayimage.rows)
			{
				val = grayimage.at<uchar>(y, x);
				hist[val]++;

				nMin = MIN(val, nMin);
				nMax = MAX(val, nMax);

				count++;
			}
		}
	}

	// limit 0-255
	nMax = MAX(0, MIN(254, nMax));
	nMin = MAX(0, MIN(254, nMin));

	for (int i=nMin; i<=nMax; i++)
	{
		if(hist[i]>0)
		{
			p = (float(hist[i]) / count);
			entropyVal += p*log2(p);
		}
	}

	return -entropyVal;
}

/*
float TextureAnalysis::calculateEntropyOfRegion(Mat const & grayimage, int offset_x, int offset_y, int region)
{
	int x, y, r2 = region >> 1;
	float p, entropyVal = 0, count=0;
	MatConstIterator_<float> it;
	std::map<uchar, float> hist;

	uint val, nMin = grayimage.cols*grayimage.rows, nMax = 0;

	// get hist
	for(x=offset_x - r2; x <= offset_x + r2; x++)
		for (y = offset_y - r2; y <= offset_y + r2; y++)
		{
			if (x >= 0 && y >= 0 && x < grayimage.cols && y < grayimage.rows)
			{
				val = grayimage.at<uchar>(y, x);
				hist[val]++;
				count++;

				nMin = MIN(val, nMin);
				nMax = MAX(val, nMax);
			}
	}

	for (auto const &iterator : hist)
	{
		p = (iterator.second / count);
		entropyVal += p*log2(p);
	}
	return -entropyVal;
}
*/

void TextureAnalysis::entropyFilt(Mat const & image, Mat & entropy, int region)
{
	int x, y, r2 = region >> 1;
	cv::Mat pad;

	ImageProcessing::symmetricPadding(image, pad, r2);

	for (int i = 0; i < entropy.cols; i++)
	{
		for (int j = 0; j < entropy.rows; j++)
		{
			entropy.at<float>(j, i) = calculateEntropyOfRegion(pad, i+r2, j+r2, region);
		}
	}
}

