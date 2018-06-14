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

#include "globals.h"
#include "HelperFunctions.h"
#include "imageprocessing.h"
#include "mainwindow.h"
#include "findtargets.h"



// cuda gpu functions
#ifdef _CUDA_CODE_COMPILE_
#include "targetDetectionGPU.h"
#endif

using namespace cv;

typedef std::numeric_limits< float > dbl;

using namespace std;



template<typename T>
void FindTargets::printVector(const T& t) {
	std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::qDebug, ", "));
}

// functions follow ////////////////////////////////////////////////////////////////


/**
*
*  Prints to screen vector of cluster structures
*
* @author    David Watts
* @since     2017/03/07
*
* FullName   printClusterVector
* Qualifier
* @param     std::vector<T> cluster
* @return    void
* Access     public
*/

template<typename T>
void FindTargets::printClusterVector(std::vector<T> cluster)
{
	std::vector<T>::iterator iI;

	int i = 0;
	for (iI = cluster.begin(); iI != cluster.end(); iI++)
	{
		i++;
		std::string s = "cluster";
		(*iI).printMe(s + std::to_string(i));
	}
}


/**
*
*  Prints to screen values of Coocurance matrix
*
* @author    David Watts
* @since     2017/03/07
*
* FullName   printCoocuranceHistogram
* Qualifier
* @param     T * hist
* @param     int dim1
* @param     int dim2
* @param     int dim3
* @param     int nDim3
* @return    void
* Access     public
*/
template<typename T>
void FindTargets::printCoocuranceHistogram(T* hist, int dim1, int dim2, int dim3, int nDim3)
{
	int i, j, k, ind;

	if (dim3 <= 0)
	{
		for (i = 0; i<dim2; i++)
		{
			for (j = 0; j<dim1; j++)
				DBOUT(hist[i + j*dim1] << " ");
		}
		DBOUT(std::endl);
	}
	else
	{
		for (k = 0; k<dim3; k++)
		{
			DBOUT("d=" << k << endl);

			for (j = 0; j<dim2; j++)
			{
				for (i = 0; i<dim1; i++)
				{
					//ind =  i + dim2 * (j*dim1+k);
					//(z * dim1 * dim2) + (y * dim1) + x;

					ind = i + j*dim1 + k*dim1*dim2;
					DBOUT(hist[ind] << "\t"); //i + height* (j + width* k)
				}
				DBOUT(std::endl);
			}
			DBOUT(std::endl);
		}
		DBOUT(std::endl);
	}
}



// end of helper functions ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
*
*   Detects target image (trainingImage) in detectionImage using Laplacian method
*
* @author    David Watts
* @since     2017/04/25
*
* FullName   LaplacianFindObject
* Qualifier
* @param     std::vector<targeterImage> & trainingImages
* @param     targeterImage & detectionImage
* @return    cv::Mat
* Access     public
*/
cv::Mat FindTargets::LaplacianFindObject(std::vector<targeterImage>& trainingImages, targeterImage& detectionImage, int distance, int NoClusters)
{
	cv::Mat im;

	// padd target image to be multiple of 2^N - this is to be region size
	int maxDim = 0;

	for (int i = 0; i < trainingImages.size(); i++)
		maxDim = MIN(maxDim, MAX(trainingImages[0].Cols(), trainingImages[0].Rows()));

	int NextPow = round(pow(2, ceil(log2(maxDim))));

	return im;
}




/**
*
*  Detects target image (trainingImage) in detectionImage using colour coocurrance matrix matching method
*
* @author    David Watts
* @since     2017/03/07
*
* FullName   ColourOccuranceHistogram
* Qualifier
* @param     std::vector<targeterImage> & trainingImages
* @param     targeterImage & detectionImage
* @param     int distance
* @param     int NoClusters
* @param     MainWindow * pMainWindow
* @return    void
* Access     public
*/
cv::Mat FindTargets::ColourOccuranceHistogram(std::vector<targeterImage>& trainingImages, targeterImage& detectionImage, int distance, int NoClusters, bool bCrossEntropy)
{
#ifdef DEBUGPRINT
	DBOUT("Function Name: " << Q_FUNC_INFO << std::endl);
#endif
	int w_t = trainingImages[0].getImage().cols;
	int h_t = trainingImages[0].getImage().rows;

	int w_d = detectionImage.getImage().cols;
	int h_d = detectionImage.getImage().rows;

	int regionWidth = w_t;
	int regionHeight = h_t;

	bool bSuccess = true;

#ifdef _CUDA_CODE_COMPILE_
	distance = MIN(32, distance);
	int optiDist = 16;
#endif

	regionWidth = MIN(distance, regionWidth);
	regionHeight = MIN(distance, regionHeight);

#ifdef _CUDA_CODE_COMPILE_
	int inc_W = 1;// regionWidth / 2;
	int inc_H = 1;// regionHeight / 2;
#else
	int regionWidth / 2;
	int regionHeight / 2;
#endif

	// distance should not be more than 32 as should sizes for CUDA
	distance = MAX(regionWidth, regionHeight);

	// make distance divisible by 2
	//distance = (distance >> 1) << 1;

	// allocate matrix
	float* coMatrix_TargetIntensity = nullptr;
	float* coMatrix_TargetHue = nullptr;
	float* scoreImage = nullptr;

	// clusters test and training images for RGB values

	int CoocSize = NoClusters*NoClusters*distance;

	coMatrix_TargetIntensity = new float[CoocSize];

	for (int i = 0; i < CoocSize; i++)
		coMatrix_TargetIntensity[i] = 0.0;

	// cluster intensity and hue of images
	if (HelperFunctions::isGrayImage(detectionImage.getImage()))
	{
		int* pClusterHistIntensity;

		// grayscale
		HistogramClusteringGray(detectionImage, NoClusters, &pClusterHistIntensity);

		// label training images using clustered image
		labelTrainingImagesGray(trainingImages, pClusterHistIntensity);

		delete[] pClusterHistIntensity;

		for (int i = 0; i < trainingImages.size(); i++)
		{
			// generate coocurrence matrices from training images
			getCoocuranceHistogram(trainingImages[i], coMatrix_TargetIntensity, nullptr, regionWidth, regionHeight, inc_W, inc_H, NoClusters, NoClusters, distance);
		}
	}
	else
	{
		// colour
		int *pClusterHistHue, *pClusterHistIntensity;

		HistogramClusteringHSV(detectionImage, NoClusters, &pClusterHistHue, &pClusterHistIntensity);

		// label training images using clustered image
		labelTrainingImagesHSV(trainingImages, pClusterHistHue, pClusterHistIntensity);

		delete[] pClusterHistHue;
		delete[] pClusterHistIntensity;

		coMatrix_TargetHue = new float[CoocSize];

		for (int i = 0; i < CoocSize; i++)
			coMatrix_TargetHue[i] = 0.0;
		
		for (int i = 0; i < trainingImages.size(); i++)
		{
			// generate concurrence matrices from training images
			getCoocuranceHistogram(trainingImages[i], coMatrix_TargetIntensity, coMatrix_TargetHue, regionWidth, regionHeight, inc_W, inc_H, NoClusters, NoClusters, distance);
		}
	}


#ifdef DEBUGIMAGES
	imshow("training", HelperFunctions::putImageScale(trainingImages[0].get1DImage(), trainingImages[0].Cols(), trainingImages[0].Rows()));                   // Show our image inside it.
	imshow("test", HelperFunctions::putImageScale(detectionImage.get1DImage(), detectionImage.Cols(), detectionImage.Rows()));                   // Show our image inside it.
#endif
	freopen("CONOUT$", "wb", stdout);
	
	//int* testing = kMeansRGB(detectionImage, NoClusters, 1000);

	// scan test image calculate intersection value save value to image
	//float* result = findTargets(detectionImage, coMatrixTrain, NoClusters, distance, bCrossEntropy);

#ifdef _CUDA_CODE_COMPILE_
	cudaScore cudaS(w_d, h_d, CoocSize);

	scoreImage = new float[w_d*h_d];

	for (int i = 0; i < w_d*h_d; i++)
		scoreImage[i] =0.0;

	cudaS.FindTargets(detectionImage.get1DImage(imageType::display), scoreImage, w_d, h_d, regionWidth, regionHeight, inc_W, inc_H, coMatrix_TargetIntensity, NoClusters, NoClusters, distance, false);

	if (!HelperFunctions::isGrayImage(detectionImage.getImage()))
	{
		bSuccess = cudaS.FindTargets(detectionImage.get1DImage(imageType::hue), scoreImage, w_d, h_d, regionWidth, regionHeight, inc_W, inc_H, coMatrix_TargetHue, NoClusters, NoClusters, distance, false);
	}
#else  
	scoreImage = FindTargets::findTargets(detectionImage, regionWidth, regionHeight, inc_W, inc_H, coMatrix_TargetIntensity, coMatrix_TargetHue, NoClusters, distance, bCrossEntropy);
#endif

	if (coMatrix_TargetHue != nullptr)
		delete[] coMatrix_TargetHue;

	if (coMatrix_TargetIntensity != nullptr)
		delete[] coMatrix_TargetIntensity;

	cv::Mat sim;

	if(bSuccess)
	{
		sim = HelperFunctions::putImageScale<float>(scoreImage, w_d, h_d);
	}
	else
	{
		sim = cv::Mat();
	}
	
	if (scoreImage != nullptr)
		delete[] scoreImage;

	return sim;
}

/**
*
*  Finds template image (trainingImages) in detectionImage using OpenCV matchTemplate method
*
* @author    David Watts
* @since     2017/03/07
*
* FullName   CVMatching
* Qualifier
* @param     std::vector<targeterImage> & trainingImages
* @param     targeterImage & detectionImage
* @param     algoType matchType
* @param     MainWindow * pMainWindow
* @return    void
* Access     public
*/
cv::Mat FindTargets::CVMatching(std::vector<targeterImage>& trainingImages, targeterImage& detectionImage, algoType::algoType matchType)
{
#ifdef DEBUGPRINT
	DBOUT("Function Name: " << Q_FUNC_INFO << std::endl);
#endif
	bool bExpandImageBoundaries = false;

	/// Create the result matrix
	cv::Mat result(detectionImage.Size(), CV_32FC1);

	int w = trainingImages[0].Cols();
	int h = trainingImages[0].Rows();

	cv::Size dstSize;
	cv::Mat dst;

	if (bExpandImageBoundaries)
	{
		detectionImage.Size() + trainingImages[0].Size() - cv::Size(1, 1);
		dst = cv::Mat(dstSize, detectionImage.Type(), cv::Scalar(0, 0, 0));

		detectionImage.getImage().copyTo(dst(cv::Rect(w >> 1, h >> 1, detectionImage.Cols(), detectionImage.Rows())));
	}
	else
	{
		dstSize = detectionImage.Size();
		dst = detectionImage.getImage();
	}

	/// Do the Matching and Normalize
	matchTemplate(dst, trainingImages[0].getImage(), result, matchType);

	cv::Mat out;

	normalize(result, result, 0, 255, NORM_MINMAX, -1, Mat());

	DBOUT(HelperFunctions::type2str(result.type()).data());

	result.convertTo(result, CV_8UC1);

	if (!bExpandImageBoundaries)
	{
		out = cv::Mat(detectionImage.Size(), CV_8UC1, cv::Scalar(0, 0, 0));

		result.copyTo(out(cv::Rect(w >> 1, h >> 1, result.cols, result.rows)));
	}
	else
	{
		out = result;
	}

	//cvtColor(result, dst, CV_GRAY2RGB);

	cv::Mat in[] = { out, out, out };
	cv::merge(in, 3, dst);

	return dst;

	// threshold values greater than threshold mask test image with crosshair centered on this image
}

/**
*
* posterize image based on the equal binning of image histogram
*
* @author    David Watts
* @since     2017/03/07
*
* FullName   histClusterEqual
* Qualifier
* @param     cv::Mat hueHist
* @param     int histSize
* @param     int NoClusters
* @return    int*
* Access     public
*/
int* FindTargets::histClusterEqual(cv::Mat hueHist, int histSize, int NoClusters)
{
	int sum, i;
	int* pClusterHist = new int[histSize];
	float Sum = 0;

	for (i = 0; i<histSize; i++)
	{
		Sum += hueHist.at<float>(i);
	}

	Sum /= ((float)NoClusters);

	// label histogram with cluster ID
	for (i = 0, sum = 0.0; i < histSize; i++)
		pClusterHist[i] = 0;

	float ct = 0;
	int cl = 0;

	// 3) now go through clusters and label image
	for (i = 0; i<histSize; i++)
	{
		pClusterHist[i] = cl;

		ct += hueHist.at<float>(i);;

		if (ct > Sum)
		{
			ct = 0;
			cl++;
		}
	}

	return pClusterHist;
}



/**
*
*  Uses histogram cluster merging method to posterise grayscale image into NoCluster number of levels
*
* @author    David Watts
* @since     2017/03/07
*
* FullName   HistogramClusteringGray
* Qualifier
* @param     targeterImage & detectionImage
* @param     std::vector<targeterImage> & TrainImages
* @param     int NoClusters
* @param     MainWindow * pMainWindow
* @return    void
* Access     public
*/
void FindTargets::HistogramClusteringGray(targeterImage& detectionImage, int NoClusters, int** clusterHist)
{
	std::vector<cv::Mat> hsv_planes;
	cv::Mat image1_gray;

	DBOUT("greyscale image" << std::endl);

	//cv::cvtColor(detectionImage.getImage(), image1_gray, CV_BGR2GRAY);
	split(detectionImage.getImage(), hsv_planes);

#ifdef DEBUGIMAGES
	cv::String s = "gray ";

	namedWindow(s, WINDOW_AUTOSIZE);// Create a window for display.
	imshow(s, hsv_planes[0]);                   // Show our image inside it.
#endif
	(*clusterHist) = HSVHist(detectionImage, &hsv_planes[0], NoClusters, imageType::display);
}


/**
*
*  Uses histogram cluster merging method to posterise RGB image into NoCluster number of levels (Hue and Value)
*
* @author    David Watts
* @since     2017/04/05
*
* FullName   HistogramClusteringHSV
* Qualifier
* @param     targeterImage & detectionImage
* @param     std::vector<targeterImage> & TrainImages
* @param     int NoClusters
* @param     MainWindow * pMainWindow
* @return    void
* Access     public
*/
void FindTargets::HistogramClusteringHSV(targeterImage& detectionImage, int NoClusters, int** clusterHistHue, int** clusterHistIntensity)
{
	cv::Mat hsvImage;
	std::vector<cv::Mat> hsv_planes;

	DBOUT("colour image" << std::endl);

	cv::cvtColor(detectionImage.getImage(), hsvImage, CV_BGR2HSV);

	split(hsvImage, hsv_planes);

#ifdef DEBUGIMAGES
	cv::String s = "hue ";

	namedWindow(s, WINDOW_AUTOSIZE);// Create a window for display.
	imshow(s, hsv_planes[0]);                   // Show our image inside it.
#endif

	(*clusterHistHue) = HSVHist(detectionImage, &hsv_planes[2], NoClusters, imageType::display);
	(*clusterHistIntensity) = HSVHist(detectionImage, &hsv_planes[0], NoClusters, imageType::hue);
}

int* FindTargets::HSVHist(targeterImage& detectionImage, const cv::Mat* pchannel, int NoClusters, imageType::imageType imType)
{
	// //////////////////////////////////////////////////////////////////
	int i, w1 = detectionImage.Cols(), h1 = detectionImage.Rows();
	int histSize = 256;

	if (imType == imageType::hue)
		histSize = 180;

	float range[] = { 0, histSize };

	bool uniform = true;
	bool accumulate = false;

	const float* histRange = { range };
	cv::Mat hist;

	cv::calcHist(pchannel, 1, 0, Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);

	// here we cluster image based on its hue histogram /////////////////
	ImageProcessing ip;
	int* pClusterHist = ip.histClusterRGBImage(hist, histSize, NoClusters);

	// assign clusters to test image
	int* pImage = new int[h1*w1];

	// label image with cluster
	for (i = 0; i < w1; i++)
		for (int j = 0; j < h1; j++)
			pImage[i + j*w1] = pClusterHist[cvFloor(pchannel->at<uchar>(j, i))];

#ifdef DEBUGIMAGES
	cv::Mat histimage = HelperFunctions::displayHistogram(hist, histSize, 500, 500);

	cv::String s = "histogram ";
	s += (imType == imageType::hue ? "hue" : "intensity");

	namedWindow(s, WINDOW_AUTOSIZE);		// Create a window for display.
	imshow(s, histimage);                   // Show our image inside it.
#endif // endif

	detectionImage.set1DImage(pImage, imType);

	return pClusterHist;
}

void FindTargets::labelTrainingImagesGray(std::vector<targeterImage>& TrainImages, int* pClusterHist)
{
	int w, h, i;
	cv::Mat image1_gray;
	cv::Mat dst, hsvImage;
	std::vector<cv::Mat> hsv_planes;
	int* pImage = nullptr;

	// assign clusters to training images
	for (int k = 0; k < TrainImages.size(); k++)
	{
		w = TrainImages[k].Cols(), h = TrainImages[k].Rows();

		pImage = new int[w*h];

		if (TrainImages[k].getImage().channels() > 1)
		{
			cv::cvtColor(TrainImages[k].getImage(), image1_gray, cv::COLOR_BGR2GRAY);
		}
		else
		{
			image1_gray = TrainImages[k].getImage();
		}

		// label image with cluster
		for (i = 0; i < w; i++)
			for (int j = 0; j < h; j++)
				pImage[i + j*w] = pClusterHist[cvFloor(image1_gray.at<uchar>(j, i))];

		TrainImages[k].set1DImage(pImage);
	}
}

void FindTargets::labelTrainingImagesHSV(std::vector<targeterImage>& TrainImages, int* pClusterHistHue, int* pClusterHistIntensity)
{
	int w, h, i;
	cv::Mat image1_gray;
	cv::Mat dst, hsvImage;
	std::vector<cv::Mat> hsv_planes;
	int* pImage = nullptr;

	// assign clusters to training images
	for (int k = 0; k < TrainImages.size(); k++)
	{
		w = TrainImages[k].Cols(), h = TrainImages[k].Rows();

		// get float image for 360 degrees
		cvtColor(TrainImages[k].getImage(), hsvImage, CV_BGR2HSV);

		split(hsvImage, hsv_planes);

		pImage = new int[w*h];

		// label image with cluster
		for (i = 0; i < w; i++)
			for (int j = 0; j < h; j++)
			{
				pImage[i + j*w] = pClusterHistHue[cvFloor(hsv_planes[2].at<uchar>(j, i))];
			}

		TrainImages[k].set1DImage(pImage, imageType::display);

		pImage = new int[w*h];

		// label image with cluster
		for (i = 0; i < w; i++)
			for (int j = 0; j < h; j++)
			{
				pImage[i + j*w] = pClusterHistIntensity[cvFloor(hsv_planes[0].at<uchar>(j, i))];
			}

		TrainImages[k].set1DImage(pImage, imageType::hue);
	}
}


/**
*
*  Gets coocurrance matrix for image region for grayscale image
*
* @author    David Watts
* @since     2017/03/07
*
* FullName   getCoocMatrixGray
* Qualifier
* @param     targeterImage & m
* @param     int * pMask
* @param     int startX
* @param     int startY
* @param     int regionWidth
* @param     int regionHeight
* @param     float * coMatrixF
* @param     int NoClusters
* @param     int maxD
* @return    float
* Access     public
*/
float FindTargets::getCoocMatrixGray(targeterImage& m, int* pMask, drawingMode::drawingMode maskType, int startX, int startY, int regionWidth, int regionHeight, 
	float* coMatrixF, int coDIMX, int coDIMY, int coDIMZ)
{
	int i, j, c1, c2, x, y, ind, nextIndex, nextI, nextJ;
	float sum = 0;

	int w = m.Cols(), h = m.Rows();
	int* pImage = m.get1DImage(imageType::display);

	bool bHasMask = (pMask != nullptr && (maskType == drawingMode::circle || maskType == drawingMode::poly));

	for (j = 0; j<regionHeight; j++)
		for (i = 0; i<regionWidth; i++)
		{
			// what to do about masked pixels

			if ((startX + i) < w && (startY + j) < h)	// check within image bounds
			{
				if (!bHasMask || pMask[(startX + i) + (startY + j)*regionHeight] > 0)	// only makes sense where mask is same size as region
				{
					c1 = pImage[(startX + i) + (startY + j)*w];

					nextIndex = 1 + i + j*regionHeight;

					nextJ = nextIndex / regionHeight;
					nextI = nextIndex%regionHeight;

					// check against all others
					for (y = nextJ; y < regionHeight; y++)
						for (x = nextI; x < regionWidth; x++)
						{
							if ((startX + x) < w && (startY + y) < h)// check within image bounds
							{
								if (!bHasMask || pMask[(startX + x) + (startY + y)*regionHeight] > 0)
								{
									c2 = pImage[(startX + x) + (startY + y)*w];

									int d = max(x - i, y - j);	// maximum distance

									if (c1 < coDIMX && c2 < coDIMY && d < coDIMZ)
									{
										ind = c1 + c2*coDIMX + d*coDIMX*coDIMY; //c1 + NoClusters * (c2 + NoClusters * d); //i + height* (j + width* k)

										coMatrixF[ind] += 1.0;

										sum += 1.0;
									}
									else
										DBOUT("error index out of bounds " << Q_FUNC_INFO << c1 << " vs. " << coDIMX << "," << c2 << " vs. " << coDIMY << "," << d << " vs. " << coDIMZ << std::endl);
								}
							}
						}
				}
			}
		}

	return sum;
}



/**
*
*  Gets coocurrance matrix for image region for H and V channels
*
* @author    David Watts
* @since     2017/03/07
*
* FullName   getCoocMatrixHSV
* Qualifier
* @param     targeterImage & m
* @param     int * pMask
* @param     int startX
* @param     int startY
* @param     int regionWidth
* @param     int regionHeight
* @param     float * coMatrixF
* @param     int NoClusters
* @param     int maxD
* @return    float
* Access     public
*/
float FindTargets::getCoocMatrixHSV2(int* pImage, int* pHue, int w, int h, int* pMask, drawingMode::drawingMode maskType, int startX, int startY, 
									int regionWidth, int regionHeight, float* coMatrixImage, float* coMatrixHue, int coDIMX, int coDIMY, int coDIMZ)
{
	int i, j, h1, h2, i1, i2, x, y, indImage, indHue;
	long ind;
	float sum = 0;

	bool bHasMask = (pMask != nullptr && (maskType == drawingMode::circle || maskType == drawingMode::poly));

	for (j = 0; j < regionHeight; j++)
		for (i = 0; i < regionWidth; i++)
		{
			// what to do about masked pixels

			if ((startX + i) < w && (startY + j) < h)	// check within image bounds
			{
				if (!bHasMask || pMask[(startX + i) + (startY + j)*w] > 0)
				{
					i1 = pImage[(startX + i) + (startY + j)*w];
					h1 = pHue[(startX + i) + (startY + j)*w];

					// check against all others
					for (y = 0; y < regionHeight; y++)
						for (x = 0; x < regionWidth; x++)
						{
							if (i + j*w >= x + y*w)	// should  not compare backwards direction or to itself
								continue;

							if ((startX + x) < w && (startY + y) < h)// check within image bounds
							{
								if (!bHasMask || pMask[(startX + x) + (startY + y)*w] > 0)
								{
									i2 = pImage[(startX + x) + (startY + y)*w];
									h2 = pHue[(startX + x) + (startY + y)*w];

									int d = max(x - i, y - j);	// maximum distance

									if (i1 < coDIMX && i2 < coDIMY && h1 < coDIMX && h2 < coDIMY &&	d < coDIMZ)
									{
										indImage = i1 + i2*coDIMX + d*coDIMX*coDIMY;
										indHue   = h1 + h2*coDIMX + d*coDIMX*coDIMY;	// hue indexes differently than intensity!

										coMatrixImage[indImage] += 1.0;
										coMatrixHue[indHue] += 1.0;

										sum += 1.0;
									}
									else
										DBOUT("error index out of bounds " << Q_FUNC_INFO << i1 << " vs. " << coDIMX << "," << i2 << " vs. " << coDIMY
											<< h1 << " vs. " << coDIMX << "," << h2 << " vs. " << coDIMY << "," << d << " vs. " << coDIMZ << std::endl);
								}
							}
						}
				}
			}
		}

	return sum;
}


/**
*
*  Gets cooccurrance matrix of image
*
* @author    David Watts
* @since     2017/03/07
*
* FullName   getCoocuranceHistogram
* Qualifier
* @param     targeterImage & m
* @param     float * coMatrixF
* @param     int NoClusters
* @param     int maxD
* @return    void
* Access     public
*/
void FindTargets::getCoocuranceHistogram(targeterImage& m, float* coMatrixIntensity, float* coMatrixHue, 
										int regionWidth, int regionHeight, int inc_W, int inc_H, int coDIMX, int coDIMY, int coDIMZ)
{
#ifdef DEBUGPRINT
	DBOUT("Function Name: " << Q_FUNC_INFO);
#endif
	int i, x, y, stepX = 1, stepY = 1;
	float sum = 0;
	int w = m.Cols(), h = m.Rows();

	// ind = x + width * (y + height * z)

	int* mask = m.get1DImage(imageType::mask);

	// should not step through target - should get cooc from whole target region - but then larger distances
	if (HelperFunctions::isGrayImage(m.getImage()))
	{
		for (y = 0; y < h; y += inc_H)
			for (x = 0; x < w; x += inc_W)
			{
				sum += getCoocMatrixGray(m, mask, m.getMaskType(), x, y, regionWidth, regionHeight, coMatrixIntensity, coDIMX, coDIMY, coDIMZ);
			}

		// normalise histogram
		for (i = 0; i < coDIMX*coDIMY*coDIMZ; i++)
			coMatrixIntensity[i] /= sum;
	}
	else
	{
		for (y = 0; y < h; y += inc_H)
			for (x = 0; x < w; x += inc_W)
			{
				sum += getCoocMatrixHSV2(m.get1DImage(imageType::display), m.get1DImage(imageType::hue), m.Cols(), m.Rows(), 
										mask, m.getMaskType(), x, y, regionWidth, regionHeight,
										coMatrixIntensity, coMatrixHue, coDIMX, coDIMY, coDIMZ);
			}

		// normalise histogram
		for (i = 0; i<coDIMX*coDIMY*coDIMZ; i++)
		{
			coMatrixIntensity[i] /= sum;
			coMatrixHue[i] /= sum;
		}
	}
	
	DBOUT("training image co-occurrance histogram" << std::endl);

	//printCoocuranceHistogram(coMatrixF, NoClusters, NoClusters, maxD);
}

/**
*
*  Gets target score image based on matching image regions with training coccurrance mattrix (coMatrixTestF)
*
* @author    David Watts
* @since     2017/03/07
*
* FullName   findTargets
* Qualifier
* @param     targeterImage & detectionImage
* @param     float * coMatrixTestF
* @param     int NoClusters
* @param     int maxD
* @return    float*
* Access     public
*/
float* FindTargets::findTargets(targeterImage& detectionImage, int regionWidth, int regionHeight, int inc_W, int inc_H, float* coMatrixIntensity_Target, 
								float* coMatrixHue_Target, int coDIMX, int coDIMY, int coDIMZ, bool bCrossEntropy)
{

#ifdef DEBUGPRINT
	DBOUT("Function Name: " << Q_FUNC_INFO << std::endl);
#endif
	int i, j, x, y;
	float sum = 0, score = 0;

	int w = detectionImage.Cols(), h = detectionImage.Rows();

	long CoocSize =coDIMX*coDIMY*coDIMZ;

	bool bIsGray = HelperFunctions::isGrayImage(detectionImage.getImage());

	//if (!bIsGray)
	//	CoocSize = NoClusters*NoClusters*NoClusters*NoClusters*maxD;

	float* coMatrixIntensity = new float[CoocSize];
	float* coMatrixHue = nullptr;

	if(!bIsGray)
		coMatrixHue = new float[CoocSize];

	float* scoreImage = new float[w*h];
	/*
	int maskIndex = detectionImage.getFriendArrayIndexOfType(imageType::target);

	targeterImage pMaskImage = NULL;
	int* pMask1D = NULL;
	drawingMode::drawingMode maskType;

	if (maskIndex >= 0 && maxD >= pMaskImage.Rows() && maxD >= pMaskImage.Cols())
	{
	pMaskImage = detectionImage.getGlobalImage(maskIndex);
	pMask1D = pMaskImage.get1DImage(imageType::mask);
	maskType = pMaskImage.getMaskType();
	}
	*/

	int targetIndex = detectionImage.getFriendArrayIndexOfType(imageType::target);
	cv::Size targetSize;

	if (targetIndex >= 0)
	{
		targeterImage& t = detectionImage.getGlobalImage(targetIndex);
		targetSize = t.Size();
	}

	for (i = 0; i < w*h; i++)
		scoreImage[i] = 0.0;

	for (y = 0; y < h; y += inc_H)
		for (x = 0; x < w; x += inc_W)
		{
			// zero co-occurrence matrix
			for (i = 0, sum = 0; i<CoocSize; i++)
				coMatrixIntensity[i] = 0.0;

			//memset(coMatrixF, 0.0, NoClusters*NoClusters*maxD*sizeof(float));

			// no mask - I can't think how to use one properly
			// a) because of size being different to region 
			// b) in the case of multiple targets -> multiple masks?!
			if (HelperFunctions::isGrayImage(detectionImage.getImage()))
			{
				sum = getCoocMatrixGray(detectionImage, NULL, drawingMode::none, x, y, regionWidth, regionHeight, coMatrixIntensity, coDIMX, coDIMY, coDIMZ);
			}
			else
			{
				// zero co-occurrence matrix
				for (i = 0, sum = 0; i < CoocSize; i++)
					coMatrixHue[i] = 0.0;

				sum = getCoocMatrixHSV2(detectionImage.get1DImage(imageType::display), detectionImage.get1DImage(imageType::hue), detectionImage.Cols(), detectionImage.Rows(),
					NULL, detectionImage.getMaskType(), x, y, regionWidth, regionHeight,
					coMatrixIntensity, coMatrixHue, coDIMX, coDIMY, coDIMZ);
			}
			if (sum >0)
			{
				if(bCrossEntropy)
				{
					// get score by  Kullback–Leibler divergence of cooc matrices
					for (i = 0, score = 0.0; i < CoocSize; i++)
					{
						if(coMatrixIntensity[i]>0 && coMatrixIntensity[i]>0 && sum>0)
							score += coMatrixIntensity_Target[i] * (log(coMatrixIntensity_Target[i]) / log(coMatrixIntensity[i] / sum));		// Kullback–Leibler divergence P(coMatrixF | coMatrixTestF)
					}
				}
				else
				{
					// get score by minimum intersection of cooc matrices
					for (i = 0, score = 0.0; i < CoocSize; i++)
					{
						if (sum > 0)
						{
							//score += fmin(coMatrixIntensity[i] / sum, coMatrixIntensity_Target[i]);	//fabs(coMatrixF[i]- coMatrixTestF[i]);		// minimum intersection
							score += sqrt(float(coMatrixIntensity[i]) / float(sum)*coMatrixIntensity_Target[i]);		// Bhattacharyya distance

							if(!bIsGray)
								score += sqrt(float(coMatrixHue[i]) / float(sum)*coMatrixHue_Target[i]);		// Bhattacharyya distance
						}
					}
				}

																			//DBOUT("score=" << score << std::endl);

																			//DBOUT("testing image co-occurrance histogram" << std::endl);
																			//printCoocuranceHistogram<float>(coMatrixF, NoClusters, NoClusters, maxD);
																			//scoreImage[x + y*w] = score;

																			//DBOUT(score << " ");
				// label image region with score
				if (score > 0)
				{
					for (j = y; j < y + regionHeight; j++)
						for (i = x; i < x + regionWidth; i++)
						{
							if (j < h && i < w)
								scoreImage[i + j*w] += score;
						}
				}
			}
			//DBOUT(score << ", ");
		}

	return scoreImage;
}

float* FindTargets::ProcessScoreImage(float* scoreImage, int w, int h, cv::Size targetSize, int maxD, int scoreAreaFactor, int ScoreThresholdPercent)
{
	float count = 0, sum = 0, maxScore = 0, RegionScore = 0, regionMin, regionMax, val, countAboveThreshold;
	int i, j, x, y;

	// create score image that has regions similarly sized to target
	int tw = targetSize.width*scoreAreaFactor / 100.0;
	int th = targetSize.height*scoreAreaFactor / 100.0;

	// no point doing this if region size bigger than target size
	if (false && tw > maxD && th > maxD)
	{
		float* newScoreImage = new float[w*h];

		for (i = 0; i < w*h; i++)
			newScoreImage[i] = 0.0;

		int tw2 = tw >> 1, th2 = th >> 1;

		tw = tw2 << 1;
		th = th2 << 1;

		for (i = 0; i<w*h; i++)
			maxScore = max(scoreImage[i], maxScore);

		for (y = 0; y < h; y += th2)
			for (x = 0; x < w; x += tw2)
			{
				sum = 0;
				count = 0;
				regionMin = FLT_MAX;
				regionMax = 0;
				countAboveThreshold = 0;

				// get average score in region
				for (i = 0; i < tw; i++)
					for (j = 0; j < th; j++)
					{
						if (x + i < w && y + j < h)
						{
							sum += scoreImage[(x + i) + (y + j)*w];
							regionMin = MIN(regionMin, scoreImage[(x + i) + (y + j)*w]);
							regionMax = MAX(regionMax, scoreImage[(x + i) + (y + j)*w]);
							countAboveThreshold += (scoreImage[(x + i) + (y + j)*w] >= maxScore*(float(ScoreThresholdPercent) / 100.0)) ? 1 : 0;
							count++;
						}
					}

				RegionScore = (sum / count);// -regionMin;// (sum / count);// / (regionMax - regionMin);
				val = RegionScore;

				//// is region average score above score threshold
				//if (RegionScore > maxScore*(float(ScoreThresholdPercent) / 100.0))
				//	val = 255;	// this is target
				//else
				//	val = 0;	// this is not target

				// write to score image
				for (i = 0; i < tw; i++)
					for (j = 0; j < th; j++)
					{
						if (x + i < w && y + j < h)
						{
							newScoreImage[(x + i) + (y + j)*w] = countAboveThreshold>3 ? 1 : 0;//max(val, newScoreImage[(x + i) + (y + j)*w]);

																							   //if (sum/count > maxScore*(float(ScoreThresholdPercent)/100.0))
																							   //	newScoreImage[(x + i) + (y + j)*w] = 255; // max(sum, newScoreImage[(x + i) + (y + j)*w]);
																							   //else
																							   //	newScoreImage[(x + i) + (y + j)*w] = 0;

						}
					}
			}
		//DBOUT(std::endl);
		delete[] scoreImage;
		return newScoreImage;
	}
	return NULL;
}

/**
*
*  Posterities image into NoCluster levels by performing K means clustering of intensity values
*
* @author    David Watts
* @since     2017/03/07
*
* FullName   kMeansRGB
* Qualifier
* @param     cv::Mat img
* @param     std::vector<cv::Mat> testImgs
* @param     int NoClusters
* @param     int maxIterations
* @return    std::vector<int*>
* Access     public
*/
std::vector<int*> FindTargets::kMeansRGB(cv::Mat img, std::vector<cv::Mat> testImgs, int NoClusters, int maxIterations)
{
#ifdef DEBUGPRINT
	DBOUT("Function Name: " << Q_FUNC_INFO << std::endl);
#endif
	int ind, ind2;

	std::vector<int*> retImages;

	cv::Mat m = img.clone().reshape(1, img.rows * img.cols);

	for (int i = 0; i<testImgs.size(); i++)
	{
		// add test image pixels to m
		cv::Mat m2 = testImgs[i].clone().reshape(1, testImgs[i].rows*testImgs[i].cols);

		// combine both images
		m.push_back(m2);
	}

	m.convertTo(m, CV_32F);

	cv::Mat bestLabels = cv::Mat(m.rows, 1, CV_8U);
	cv::Mat centroids = cv::Mat(NoClusters, 1, CV_32F);
	int attempts = 5;

	cv::kmeans(m, NoClusters, bestLabels,
		TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, maxIterations, 0.0001),
		attempts, KMEANS_RANDOM_CENTERS, centroids);
	/*
	#ifdef DEBUGPRINT
	Mat new_image( img.size(), img.type() );

	for( int y = 0; y < img.rows; y++ )
	for( int x = 0; x < img.cols; x++ )
	{
	int cluster_idx = bestLabels.at<int>(x + y*img.cols, 0);

	new_image.at<Vec3b>(y,x)[0] = centroids.at<float>(cluster_idx, 0);
	new_image.at<Vec3b>(y,x)[1] = centroids.at<float>(cluster_idx, 1);
	new_image.at<Vec3b>(y,x)[2] = centroids.at<float>(cluster_idx, 2);
	}

	imshow( "clustered image", new_image );
	waitKey( 0 );
	#endif
	*/
	int* clusters = new int[img.rows*img.cols];

	for (int y = 0; y < img.rows; y++)
		for (int x = 0; x < img.cols; x++)
		{
			ind = x + y*img.cols;
			clusters[ind] = bestLabels.at<int>(ind, 0);
		}

	retImages.push_back(clusters);

	for (int i = 0; i<testImgs.size(); i++)
	{
		int* pImage = new int[testImgs[i].rows*testImgs[i].cols];

		for (int y = 0; y < testImgs[i].rows; y++)
			for (int x = 0; x < testImgs[i].cols; x++)
			{
				ind2 = x + y*testImgs[i].cols;

				Vec3b c = testImgs[i].at<Vec3b>(y, x);

				if (c[0] >10 && c[1] >10 && c[2]>10)
					pImage[ind2] = bestLabels.at<int>(ind + ind2, 0);
				else
					pImage[ind2] = 0;

			}
		ind += ind2;

		retImages.push_back(pImage);
	}

	return retImages;
}


/*
int* histEntropyClusterRGBImage(cv::Mat hueHist, int histSize, int NoClusters)
{
int sum, i;
std::vector<entropyCluster>::iterator clusterToMerge1, clusterToMerge2, iI, jI, kI;
int* pClusterHist = new int[histSize];
float f, entropy, bestEntropy, totEntropy;
entropyCluster h1, h2;

// create array of lists size NoClusters for clusters
std::vector<entropyCluster> clusterList;

for(i=0; i<histSize; i++)
{
f = hueHist.at<float>(i);

if(f>0)
{
// object representing cluster of histogram bars
entropyCluster c;

c.freq = f;
c.hueList.push_back(i);     // list of hues in clusters

clusterList.push_back(c);   // add to cluster list
}
}

// 1) check all clusters against each other find best cluster merger (min dist) (if NoMergedClusters == NoClusters then end)
while(clusterList.size() > NoClusters)
{
bestEntropy=FLT_MAX;
entropy=0;
totEntropy=0;

// get entropy of all clusters
for (kI = clusterList.begin(); kI != clusterList.end(); kI++)
totEntropy += (*kI).freq*log((*kI).freq);

// compare all clusters
for (iI = clusterList.begin(); iI != clusterList.end(); iI++)
{
jI = std::next(iI);

// dont compare cluster with itself
if(clusterList.end() == jI)
break;

h1 = (*iI);
h2 = (*jI);

// subtract values of clusters to be merged
entropy = totEntropy - (h1.freq)*log(h1.freq) - (h2.freq)*log(h2.freq);

// add entropy of merged column
entropy += (h1.freq + h2.freq)*log(h1.freq + h2.freq);

//DBOUT(entropy;

entropy = -entropy;

// store best score / best clusters to merge
if(entropy < bestEntropy)
{
clusterToMerge1 = iI;
clusterToMerge2 = jI;
//bestMean = meanHue;
bestEntropy = entropy;
}
}

// merge clusters with minumum varianc

// deep copy lists
(*clusterToMerge1).printMe("cluster 1");
(*clusterToMerge2).printMe("cluster 2");


if( (*clusterToMerge1).hueList.size() > (*clusterToMerge2).hueList.size())
{
(*clusterToMerge1).hueList.insert(std::end((*clusterToMerge1).hueList), std::begin((*clusterToMerge2).hueList), std::end((*clusterToMerge2).hueList));

(*clusterToMerge1).freq = (*clusterToMerge1).freq + (*clusterToMerge2).freq;

// remove cluster using iterators
clusterList.erase(clusterToMerge2);

//DBOUT((*clusterToMerge1).hueList.size();
}
else
{
(*clusterToMerge2).hueList.insert(std::end((*clusterToMerge2).hueList), std::begin((*clusterToMerge1).hueList), std::end((*clusterToMerge1).hueList));

(*clusterToMerge2).freq = (*clusterToMerge1).freq + (*clusterToMerge2).freq;

// remove cluster using iterators
clusterList.erase(clusterToMerge1);

// DBOUT((*clusterToMerge2).hueList.size();
}

// printClusterVector(clusterList);

DBOUT("iteration "<< clusterList.size()<< endl;

// merge best cluster and repeat
}

// label histogram with cluster ID
for(i = 0, sum=0.0; i < histSize; i++ )
pClusterHist[i] = 0;

int cl=1;
// 3) now go through clusters and label image
foreach(entropyCluster c, clusterList)
{
c.printMe("final cluster of 15");

foreach(int i, c.hueList)
{
pClusterHist[i] = cl;
}
cl++;
}

return pClusterHist;

}
*/

/*
// function to cluster RGB data based on histogram variances
int* histClusterRGBImage1(cv::Mat hueHist, int histSize, int NoClusters)
{
int sum, i, j;
std::vector<histCluster>::iterator clusterToMerge1, clusterToMerge2, iI, jI, kI;
long n;
int* pClusterHist = new int[histSize];
float f, meanHue, varHue, totHueVar, bestMean, bestVar;
std::vector<histogramBar> h1, h2;

// create array of lists size NoClusters for clusters
std::vector<histCluster> clusterList;

for(i=0; i<histSize; i++)
{
f = hueHist.at<float>(i);

if(f>0)
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
while(clusterList.size() > NoClusters)
{
bestVar=FLT_MAX;

// compare all clusters
for (iI = clusterList.begin(); iI != clusterList.end(); iI++)
{
jI = std::next(iI);

// dont compare cluster with itself
if(clusterList.end() == jI)
break;

n = 0;
meanHue = 0;

// for each bar get sum
foreach(histogramBar l, (*iI).column)
{
meanHue += l.freq * l.hue;
n += l.freq;
}
foreach(histogramBar l, (*jI).column)
{
meanHue += l.freq * l.hue;
n += l.freq;
}

// divide sum to get average hue
meanHue /= ((float)n);

//midHue /= len;
varHue = 0;

// get variance in cluster
foreach(histogramBar l, (*iI).column)
{
float v = (l.hue - meanHue);
varHue += l.freq*v*v;
}
foreach(histogramBar l, (*jI).column)
{
float v = (l.hue - meanHue);
varHue += l.freq*v*v;
}

varHue /= ((float)n-1);

totHueVar = varHue;

// add to variance of other clusters (excluding iI and iJ)
// for the sum or difference of independent random variables, variances add
for (kI = clusterList.begin(); kI != clusterList.end(); kI++)
{
if(kI != iI && kI != jI)
totHueVar += (*kI).varHue;
}

// store best score / best clusters to merge
if(totHueVar < bestVar)
{
clusterToMerge1 = iI;
clusterToMerge2 = jI;
bestMean = meanHue;
bestVar = totHueVar;
}
}

// merge best cluster and repeat
if( (*clusterToMerge1).hueList.size() > (*clusterToMerge2).hueList.size())
{
(*clusterToMerge1).hueList.insert(std::end((*clusterToMerge1).hueList), std::begin((*clusterToMerge2).hueList), std::end((*clusterToMerge2).hueList));
(*clusterToMerge1).column.insert(std::end((*clusterToMerge1).column), std::begin((*clusterToMerge2).column), std::end((*clusterToMerge2).column));

(*clusterToMerge1).varHue = bestVar;
(*clusterToMerge1).meanHue = bestMean;

// remove cluster using iterators
clusterList.erase(clusterToMerge2);

//DBOUT((*clusterToMerge1).hueList.size();
}
else
{
(*clusterToMerge2).hueList.insert(std::end((*clusterToMerge2).hueList), std::begin((*clusterToMerge1).hueList), std::end((*clusterToMerge1).hueList));
(*clusterToMerge2).column.insert(std::end((*clusterToMerge2).column), std::begin((*clusterToMerge1).column), std::end((*clusterToMerge1).column));

(*clusterToMerge2).varHue = bestVar;
(*clusterToMerge2).meanHue = bestMean;

// remove cluster using iterators
clusterList.erase(clusterToMerge1);

//DBOUT((*clusterToMerge2).hueList.size();
}
}

// label histogram with cluster ID
for(i = 0, sum=0.0; i < histSize; i++ )
pClusterHist[i] = 0;

int cl=0;
// 3) now go through clusters and label image
foreach(histCluster c, clusterList)
{
DBOUT(c.hueList;

foreach(int i, c.hueList)
{
pClusterHist[i] = cl;
}
cl++;
}

return pClusterHist;

}
*/