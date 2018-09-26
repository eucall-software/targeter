// Targeter - target identification software for EUCALL workpackage 6
// Licensed under the GPL License. See LICENSE file in the project root for full license information.
// Copyright(C) 2017  David Watts 

#include <iostream>
#include <iomanip>
#include <limits>
#include <QDebug>
#include <vector>
#include <QSharedPointer>
#include "opencv2/opencv.hpp"
#include "opencv/highgui.h"

#include "globals.h"
#include "HelperFunctions.h"
#include "imageprocessing.h"
#include "mainwindow.h"
#include "findtargets.h"
#include "Haar.h"



// cuda gpu functions
#ifdef _CUDA_CODE_COMPILE_
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaarithm.hpp>
#include <opencv2/cudaimgproc.hpp>
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
void FindTargets::printClusterVector(QVector<T> cluster)
{
	QVector<T>::iterator iI;

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
cv::Mat FindTargets::LaplacianFindObject(QVector<QExplicitlySharedDataPointer<targeterImage>> trainingImages, QExplicitlySharedDataPointer<targeterImage> detectionImage, int distance, int NoClusters)
{
	cv::Mat im;

	// padd target image to be multiple of 2^N - this is to be region size
	int maxDim = 0;

	for (int i = 0; i < trainingImages.size(); i++)
		maxDim = MIN(maxDim, MAX(trainingImages[0]->Cols(), trainingImages[0]->Rows()));

	int NextPow = round(pow(2, ceil(log2(maxDim))));

	return im;
}

/*
Steerable filters wavelet or laplacian filter->N orientations at each freq,
joint pdf for each orientation pair -> n pdf's * frequency levels,
or difference in orientation,
detection is by cooc comparison.
Can also do shrinkage to make pdf sparse to a list can be used instead.
Can find shrinkage for target by increasing threshold and looking at reconstruction error function of threshold.
Then apply best threshold to entire transform.
*/

//************************************
// Method:    FindTargetsHaar
// FullName:  FindTargets::FindTargetsHaar
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: QVector<QExplicitlySharedDataPointer<targeterImage>> trainingImages
// Parameter: QExplicitlySharedDataPointer<targeterImage> detectionImage
// Parameter: int levels
//************************************
bool FindTargets::FindTargetsHaar(QVector<QExplicitlySharedDataPointer<targeterImage>> trainingImages, 
	QExplicitlySharedDataPointer<targeterImage> detectionImage, int levels)
{
	// perform transform of target images
	for(int i=0; i<trainingImages.size();i++)
	{
		cv::Mat im;

		cv::cvtColor(trainingImages[i]->getImage(), im, CV_BGR2GRAY, 1);
		im.convertTo(im, CV_64FC1);

		double minVal = 0, maxVal = 0;

		cv::minMaxLoc(im, &minVal, &maxVal);

		Haar::Haar2(im, levels);

		// shrinkage of target transforms by threshold -> store threshold
		cv::Mat coocImage;

		// collect statistics on target images - orientation vs magnitude cooc matrix
		Haar::getHaarCooc(im, coocImage, im.cols, im.rows, levels, (float)maxVal);

		return true;
	}

	// compare with regions of detect image

	return true;
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
* @return    void	* Access     public
*/
cv::Mat FindTargets::CVMatching(QVector<QExplicitlySharedDataPointer<targeterImage>> trainingImages, QExplicitlySharedDataPointer<targeterImage> detectionImage, algoType::algoType matchType, bool bCorrectBackground)
{
#ifdef DEBUGPRINT
	DBOUT("Function Name: " << Q_FUNC_INFO << std::endl);
#endif
	bool bExpandImageBoundaries = false;

	/// Create the result matrix
	int w = trainingImages[0]->Cols();
	int h = trainingImages[0]->Rows();

	cv::Size dstSize;
	cv::Mat dst, dst_border;
	
	dstSize = detectionImage->Size();
	dst = detectionImage->getImage();

	copyMakeBorder(dst, dst, h/2, h/2, w/2, w/2, BORDER_REPLICATE);

	if (bCorrectBackground)
	{
		cv::Mat out;
		ImageProcessing ip;
		dst = ip.subtractBackground(dst, out);
	}

	int dw = dst.cols;
	int dh = dst.rows;

	cv::Mat detect = trainingImages[0]->getImage();

	cv::Mat result((dw - w + 1), (dh - h + 1), CV_32FC1);

	DBOUT("dst type " << HelperFunctions::type2str(dst.type()).toLocal8Bit().data());
	DBOUT("detect type " << HelperFunctions::type2str(detect.type()).toLocal8Bit().data());

	/// Do the Matching and Normalize
	cv::matchTemplate(dst, detect, result, matchType);

	cv::Mat sim = HelperFunctions::convertFloatToGreyscaleMat(result);

	cv::Mat fullSizeImage(dstSize.height, dstSize.width, dst.type());

	sim.copyTo(fullSizeImage(cv::Rect(w/2, h/2, sim.cols, sim.rows)));

	return fullSizeImage;
}


////////////////////////////// laws method /////////////////////////////////////////////////////////

//************************************
// Method:    sepConvolve
// FullName:  FindTargets::sepConvolve
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: const cv::Mat spImage
// Parameter: cv::Mat & spResult
// Parameter: const float Kernel[]
// Parameter: int KernelLen
// Parameter: bool bRow
//************************************
void FindTargets::sepConvolve(const cv::Mat spImage, cv::Mat& spResult, const float Kernel[/* KernelLen */], int KernelLen, bool bRow)
{
	int r= spImage.rows, c= spImage.cols;
	
	if(bRow)
	{
		for (int j = 0; j < r; j++)
		{
			for (int i = 0; i < c; i++)
			{
				spResult.at<float>(j, i) = 0;

				for (int k = 0; k < KernelLen; k++)
				{
					int ind = i - k;

					//mirror
					if (ind > c - 1)
						ind = c - (ind - c);
					else if (ind < 0)
						ind = -ind;

					spResult.at<float>(j, i) = spResult.at<float>(j, i) + spImage.at<float>(j, ind) * Kernel[k];    // convolve: multiply and accumulate
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < c; i++)
		{
			for (int j = 0; j < r; j++)
			{
				spResult.at<float>(j, i) = 0;

				for (int k = 0; k < KernelLen; k++)
				{
					int ind = j - k;
					
					//mirror
					if (ind > r - 1)
						ind = r - (ind - r);
					else if (ind < 0)
						ind = -ind;
					
					spResult.at<float>(j, i) = spResult.at<float>(j, i) + spImage.at<float>(ind, i) * Kernel[k];    // convolve: multiply and accumulate
				}
			}
		}
	}
}

//************************************
// Method:    addHistogram
// FullName:  FindTargets::addHistogram
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: cv::Mat & hist
// Parameter: cv::Mat aim
// Parameter: cv::Mat bim
// Parameter: cv::Mat cim
// Parameter: cv::Mat dim
// Parameter: int noBins
// Parameter: int histrange
// Parameter: bool append
//************************************
void FindTargets::addHistogram(cv::Mat& hist, cv::Mat aim, cv::Mat bim, cv::Mat cim, cv::Mat dim, int noBins, int histrange, bool append)
{
	float range[] = { -histrange, histrange };
	const float* histRange = { range };
	bool uniform = true;

	if(!aim.empty())
		getHistogram(aim, hist, noBins, histrange, append);
	if(!bim.empty())
		getHistogram(bim, hist, noBins, histrange, true);
	if(!cim.empty())
		getHistogram(cim, hist, noBins, histrange, true);
	if(!dim.empty())
		getHistogram(dim, hist, noBins, histrange, true);

	hist.at<float>(noBins>>1, 0) = 0;
}

void FindTargets::getHistogram(cv::Mat input, cv::Mat& histogram, int noBins, int histrange, bool append)
{
	
	
	// cuda histogram on deals with uchar/short types!
	/*
#ifdef _CUDA_CODE_COMPILE_
	cv::cuda::GpuMat hist(1, noBins, CV_32S);
	cv::cuda::GpuMat  inImage;
	inImage.upload(input);
	cv::cuda::histEven(inImage, hist, noBins, -histrange, histrange);
	cv::Mat result_host;
	hist.download(histogram);
#else
*/
	float range[] = { -histrange, histrange };
	const float* histRange = { range };
	cv::calcHist(&input, 1, 0, cv::Mat(), histogram, 1, &noBins, &histRange, true, append);
	/*
#endif
*/
}

//************************************
// Method:    scoreLawsHistogram
// FullName:  FindTargets::scoreLawsHistogram
// Access:    public 
// Returns:   double
// Qualifier:
// Parameter: QVector<cv::Mat> lawsMapDetect
// Parameter: QVector<cv::Mat> lawsHistTarget
// Parameter: QVector<float> biases
//************************************
double FindTargets::scoreLawsHistogram(QVector<cv::Mat> lawsMapDetect, QVector<cv::Mat> lawsHistTarget, QVector<float> biases)
{
	float score = 0;

	for (int i = 0; i < lawsHistTarget.length(); i++)
	{
		float bias = 1.0/float(lawsHistTarget.length());

		if (biases.length() >= i && biases[i] >= 0 && biases[i] <= 1)
			bias = biases[i];

		// should bias the histogram with the strongest response in the test images
 		score += compareHist(lawsHistTarget[i], lawsMapDetect[i], cv::HISTCMP_CHISQR) * bias;
	}
	return score;
}


//************************************
// Method:    getLawFilteredImages
// FullName:  FindTargets::getLawFilteredImages
// Access:    public 
// Returns:   QT_NAMESPACE::QMap<QT_NAMESPACE::QString, cv::Mat>
// Qualifier:
// Parameter: cv::Mat im
//************************************
QMap<QString, cv::Mat> FindTargets::getLawFilteredImages(cv::Mat im)
{
	QMap<QString, cv::Mat> lawsMapTarget;

	float L[5] = { 1, 4, 6, 4, 1 };
	float E[5] = { -1, -2, 0, 2, 1 };
	float ER[5] = { 1, 2, 0, -2, -1 };
	float S[5] = { -1, 0, 2, 0, -1 };
	float R[5] = { 1, -4, 6, -4, 1 };
	//float W5[5] = { -1, 2, 0, -2, 1};

	int r = im.rows, c = im.cols, t = im.type();

	cv::Mat tempIm = cv::Mat(r, c, t);

	// first 1D filter on X
	sepConvolve(im, tempIm, L, 5, true);
	cv::Mat temp1 = tempIm.clone();
	lawsMapTarget["im_L"] = temp1;
	sepConvolve(im, tempIm, E, 5, true);
	lawsMapTarget["im_E"] = tempIm.clone();
	sepConvolve(im, tempIm, ER, 5, true);
	lawsMapTarget["im_ER"] = tempIm.clone();
	sepConvolve(im, tempIm, S, 5, true);
	lawsMapTarget["im_S"] = tempIm.clone();
	sepConvolve(im, tempIm, R, 5, true);
	lawsMapTarget["im_R"] = tempIm.clone();
	// other filtered images filtered in Y

	// filtered images

	// completely symmetric
	sepConvolve(lawsMapTarget["im_S"], tempIm, S, 5, false);
	lawsMapTarget["im_SS"] = tempIm.clone();
	sepConvolve(lawsMapTarget["im_R"], tempIm, R, 5, false);
	lawsMapTarget["im_RR"] = tempIm.clone();
	// 180 degree rotationally symmetric

	//cv::Mat LSSL = (sepConvolve(im_L, S, 5, false) + sepConvolve(im_S, L, 5, false)) / 2.0;
	 sepConvolve(lawsMapTarget["im_L"], tempIm, S, 5, false);
	lawsMapTarget["im_LS"] = tempIm.clone();

	sepConvolve(lawsMapTarget["im_S"], tempIm, L, 5, false);
	lawsMapTarget["im_SL"] = tempIm.clone();
	

	//cv::Mat SRRS = (sepConvolve(im_S, R, 5, false) + sepConvolve(im_R, S, 5, false)) / 2.0;
	sepConvolve(lawsMapTarget["im_S"], tempIm, R, 5, false);
	lawsMapTarget["im_SR"] = tempIm.clone();
	
	 sepConvolve(lawsMapTarget["im_R"], tempIm, S, 5, false);
	lawsMapTarget["im_RS"] = tempIm.clone();
	

	//cv::Mat LRRL = (sepConvolve(im_L, R, 5, false) + sepConvolve(im_R, L, 5, false)) / 2.0;
	 sepConvolve(lawsMapTarget["im_E"], tempIm, E, 5, false);
	lawsMapTarget["im_EE"] = tempIm.clone();
	
	sepConvolve(lawsMapTarget["im_E"], tempIm, ER, 5, false);
	lawsMapTarget["im_EER"] = tempIm.clone();

	// 90 Degree rotationally symmetric - Anything with E and another type of filter!

	// either average like below or add to same histogram for filter type

	/*
	//cv::Mat LEEL = (sepConvolve(im_L, E, 5, false) + sepConvolve(im_E, L, 5, false)) / 2.0;
	cv::Mat EL_LE_LER_ERL = (sepConvolve(im_E, L, 5, false) +
	sepConvolve(im_L, E, 5, false) +
	sepConvolve(im_L, ER, 5, false) +
	sepConvolve(im_ER, L, 5, false)) / 4.0;
	*/

	sepConvolve(lawsMapTarget["im_E"], tempIm, L, 5, false);
	lawsMapTarget["im_EL"] = tempIm.clone();
	sepConvolve(lawsMapTarget["im_L"], tempIm, E, 5, false);
	lawsMapTarget["im_LE"] = tempIm.clone();
	sepConvolve(lawsMapTarget["im_L"], tempIm, ER, 5, false);
	lawsMapTarget["im_LER"] = tempIm.clone();
	sepConvolve(lawsMapTarget["im_ER"], tempIm, L, 5, false);
	lawsMapTarget["im_ERL"] = tempIm.clone();

	/*
	//cv::Mat ESSE =	(sepConvolve(im_E, S, 5, false) + sepConvolve(im_S, E, 5, false)) / 2.0;
	cv::Mat ES_SE_SER_ERS = (sepConvolve(im_E, S, 5, false) +
	sepConvolve(im_S, E, 5, false) +
	sepConvolve(im_S, ER, 5, false) +
	sepConvolve(im_ER, S, 5, false)) / 4.0;
	*/
	 
	sepConvolve(lawsMapTarget["im_E"], tempIm, S, 5, false);
	lawsMapTarget["im_ES"] = tempIm.clone();
	sepConvolve(lawsMapTarget["im_S"], tempIm, E, 5, false);
	lawsMapTarget["im_SE"] = tempIm.clone();
	sepConvolve(lawsMapTarget["im_S"], tempIm, ER, 5, false);
	lawsMapTarget["im_SER"] = tempIm.clone();
	sepConvolve(lawsMapTarget["im_ER"], tempIm, S, 5, false);
	lawsMapTarget["im_ERS"] = tempIm.clone();

	/*
	//cv::Mat ERRE = (sepConvolve(im_E, R, 5, false) + sepConvolve(im_R, E, 5, false)) / 2.0;
	cv::Mat ER_RE_RER_ERR = (sepConvolve(im_E, R, 5, false) +
	sepConvolve(im_R, E, 5, false) +
	sepConvolve(im_R, ER, 5, false) +
	sepConvolve(im_ER, R, 5, false)) / 4.0;
	*/
	 
	sepConvolve(lawsMapTarget["im_E"], tempIm, R, 5, false);
	lawsMapTarget["im_ER"] = tempIm.clone();
	sepConvolve(lawsMapTarget["im_R"], tempIm, E, 5, false);
	lawsMapTarget["im_RE"] = tempIm.clone();
	sepConvolve(lawsMapTarget["im_R"], tempIm, ER, 5, false);
	lawsMapTarget["im_RER"] = tempIm.clone();
	sepConvolve(lawsMapTarget["im_ER"], tempIm, R, 5, false);
	lawsMapTarget["im_ERR"] = tempIm.clone();

	return lawsMapTarget;
}

//************************************
// Method:    getLawFilterHistograms
// FullName:  FindTargets::getLawFilterHistograms
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: cv::Mat im
// Parameter: QVector<cv::Mat> & lawsHistTarget
// Parameter: int histSize
// Parameter: int histRange
// Parameter: bool bAccumulateHistograms
//************************************
void FindTargets::getLawFilterHistograms(cv::Mat im, QVector<cv::Mat>& lawsHistTarget, int histSize, int histRange, bool bAccumulateHistograms)
{
	cv::cvtColor(im, im, CV_BGR2GRAY, 1);

	im.convertTo(im, CV_32FC1);

	QMap<QString, cv::Mat> lawsMapTarget = getLawFilteredImages(im);

	if(bAccumulateHistograms == false || lawsHistTarget.length() == 0 )
	{
		for (int c = 0; c < 8; c++)
			lawsHistTarget.append(cv::Mat());
	}

	getLawFilterHistograms(lawsHistTarget, lawsMapTarget, cv::Rect(), histSize, histRange, bAccumulateHistograms);
}

void FindTargets::getLawFilterHistograms(QVector<cv::Mat>& lawsHist, QMap<QString, cv::Mat> lawsMap, cv::Rect roi, int histSize, int histRange, bool bAccumulateHistograms)
{
	if(roi.x >= 0 && roi.y >= 0 && roi.width > 0 && roi.height > 0)
	{
		addHistogram(lawsHist[0], lawsMap["im_SS"](roi), cv::Mat(), cv::Mat(), cv::Mat(), histSize, histRange, bAccumulateHistograms);
		addHistogram(lawsHist[1], lawsMap["im_RR"](roi), cv::Mat(), cv::Mat(), cv::Mat(), histSize, histRange, bAccumulateHistograms);
		addHistogram(lawsHist[2], lawsMap["im_LS"](roi), lawsMap["im_SL"](roi), cv::Mat(), cv::Mat(), histSize, histRange, bAccumulateHistograms);
		addHistogram(lawsHist[3], lawsMap["im_SR"](roi), lawsMap["im_RS"](roi), cv::Mat(), cv::Mat(), histSize, histRange, bAccumulateHistograms);
		addHistogram(lawsHist[4], lawsMap["im_EE"](roi), lawsMap["im_EER"](roi), cv::Mat(), cv::Mat(), histSize, histRange, bAccumulateHistograms);
		addHistogram(lawsHist[5], lawsMap["im_EL"](roi), lawsMap["im_LE"](roi), lawsMap["im_LER"](roi), lawsMap["im_ERL"](roi), histSize, histRange, bAccumulateHistograms);
		addHistogram(lawsHist[6], lawsMap["im_ES"](roi), lawsMap["im_SE"](roi), lawsMap["im_SER"](roi), lawsMap["im_ERS"](roi), histSize, histRange, bAccumulateHistograms);
		addHistogram(lawsHist[7], lawsMap["im_ER"](roi), lawsMap["im_RE"](roi), lawsMap["im_RER"](roi), lawsMap["im_ERR"](roi), histSize, histRange, bAccumulateHistograms);
	}
	else
	{
		addHistogram(lawsHist[0], lawsMap["im_SS"], cv::Mat(), cv::Mat(), cv::Mat(), histSize, histRange, bAccumulateHistograms);
		addHistogram(lawsHist[1], lawsMap["im_RR"], cv::Mat(), cv::Mat(), cv::Mat(), histSize, histRange, bAccumulateHistograms);
		addHistogram(lawsHist[2], lawsMap["im_LS"], lawsMap["im_SL"], cv::Mat(), cv::Mat(), histSize, histRange, bAccumulateHistograms);
		addHistogram(lawsHist[3], lawsMap["im_SR"], lawsMap["im_RS"], cv::Mat(), cv::Mat(), histSize, histRange, bAccumulateHistograms);
		addHistogram(lawsHist[4], lawsMap["im_EE"], lawsMap["im_EER"], cv::Mat(), cv::Mat(), histSize, histRange, bAccumulateHistograms);
		addHistogram(lawsHist[5], lawsMap["im_EL"], lawsMap["im_LE"], lawsMap["im_LER"], lawsMap["im_ERL"], histSize, histRange, bAccumulateHistograms);
		addHistogram(lawsHist[6], lawsMap["im_ES"], lawsMap["im_SE"], lawsMap["im_SER"], lawsMap["im_ERS"], histSize, histRange, bAccumulateHistograms);
		addHistogram(lawsHist[7], lawsMap["im_ER"], lawsMap["im_RE"], lawsMap["im_RER"], lawsMap["im_ERR"], histSize, histRange, bAccumulateHistograms);
	}
}

//************************************
// Method:    getHistogramWeights
// FullName:  FindTargets::getHistogramWeights
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: QVector<cv::Mat> hists
// Parameter: QVector<float> & biases
//************************************
void FindTargets::getHistogramWeights(QVector<cv::Mat> hists, QVector<float>& biases)
{
	biases = QVector<float>(hists.length());
	double bsum = 0;

	// get sum of histogram to use in an importance measure
	for (int i = 0; i < hists.length(); i++)
	{
		biases[i] = cv::sum(hists[i])[0];	// or entropy?
		bsum += biases[i];
	}

	//normalise
	for (int i = 0; i < hists.length(); i++)
		biases[i] /= bsum;
}

//************************************
// Method:    detectLawsTextureFeatures
// FullName:  FindTargets::detectLawsTextureFeatures
// Access:    public 
// Returns:   cv::Mat
// Qualifier:
// Parameter: cv::Mat detectionImage
// Parameter: QVector<cv::Mat> lawsHistTarget
// Parameter: QVector<float> biases
//************************************
cv::Mat FindTargets::detectLawsTextureFeatures(cv::Mat detectionImage, QVector<cv::Mat> lawsHistTarget, QVector<float> biases, bool bCorrectBackground)
{
	#ifdef _CUDA_CODE_COMPILE_
		int inc = 1;
	#else
		int inc = 10;
	#endif
	int regionSize = 15;
	int histRange = 128;
	int histSize = 10;

	// now get detection 
	cv::Mat im, scoreImage(detectionImage.rows, detectionImage.cols, CV_32FC1);

	// now filter detect image and compare histograms of regions of the image
	cv::cvtColor(detectionImage, im, CV_BGR2GRAY, 1);

	if (bCorrectBackground)
	{
		cv::Mat out;
		ImageProcessing ip;
		im = ip.subtractBackground(im, out);
	}

	im.convertTo(im, CV_32FC1);

	QMap<QString, cv::Mat> lawsMapDetect = getLawFilteredImages(im);

	QVector<cv::Mat> lawsHistDetect;

	for (int c = 0; c < 8; c++)
		lawsHistDetect.append(cv::Mat());

	// but this has to be on regions of the detection image
	for (int i = 0; i < im.cols; i += inc)
		for (int j = 0; j < im.rows; j += inc)
		{
			int regionSizeI = regionSize;
			int regionSizeJ = regionSize;

			if (i + regionSize >= im.cols)
				regionSizeI = im.cols - i;
			if (j + regionSize >= im.rows)
				regionSizeJ = im.rows - j;

			// get histograms in this region of the image
			cv::Rect roi(i, j, regionSizeI, regionSizeJ);

			getLawFilterHistograms(lawsHistDetect, lawsMapDetect, roi, histSize, histRange, false);

			//score detect region using target histogram	
			float s = scoreLawsHistogram(lawsHistDetect, lawsHistTarget, biases);

			for (int k = i; k < i + inc; k++)
				for (int l = j; l < j + inc; l++)
					scoreImage.at<float>(l, k) = s;
		}

	// create greyscale image of score
	cv::Mat sim = HelperFunctions::convertFloatToGreyscaleMat(scoreImage);

	return sim;
}

//************************************
// Method:    lawsTextureFeatures
// FullName:  FindTargets::lawsTextureFeatures
// Access:    public 
// Returns:   cv::Mat
// Qualifier:
// Parameter: QVector<QExplicitlySharedDataPointer<targeterImage>> trainingImages
// Parameter: QExplicitlySharedDataPointer<targeterImage> detectionImage
//************************************
cv::Mat FindTargets::lawsTextureFeatures(QVector<QExplicitlySharedDataPointer<targeterImage>> trainingImages,
	QExplicitlySharedDataPointer<targeterImage> detectionImage, bool bCorrectBackground)
{
	int histRange = 128;
	int histSize = 10;
	
	QVector<cv::Mat> lawsHistTarget;

	for (int i = 0, hs = 0; i < trainingImages.size(); i++)
		getLawFilterHistograms(trainingImages[i]->getImage(), lawsHistTarget, histSize, histRange, true);

	//return HelperFunctions::displayHistogram(lawsHistTarget[7], histSize);

	// get vector of filter weights
	QVector<float> biases;
	getHistogramWeights(lawsHistTarget, biases);

	return detectLawsTextureFeatures(detectionImage->getImage(), lawsHistTarget, biases, bCorrectBackground);
}

void FindTargets::trainLawsTextureFeatures(QVector<QExplicitlySharedDataPointer<targeterImage>> trainingImages, QVector<cv::Mat>& lawsHistTarget, QVector<float>& lawsHistBiases)
{
	int histRange = 128;
	int histSize = 10;
	
	lawsHistTarget.clear();

	for (int i = 0, hs = 0; i < trainingImages.size(); i++)
		getLawFilterHistograms(trainingImages[i]->getImage(), lawsHistTarget, histSize, histRange, true);

	//return HelperFunctions::displayHistogram(lawsHistTarget[7], histSize);

	// get vector of filter weights
	getHistogramWeights(lawsHistTarget, lawsHistBiases);
}

cv::Mat FindTargets::HaarHistogram(QVector<QExplicitlySharedDataPointer<targeterImage>> trainingImages, QExplicitlySharedDataPointer<targeterImage> detectionImage, int distance, int NoClusters, bool bProcessGrayscale)
{
	cv::Mat sim = cv::Mat();

	return sim;
}


/////////////////////////// cooc target detection ////////////////////////////////////////////////////////////////
void FindTargets::trainColourOccuranceHistogram(QVector<QExplicitlySharedDataPointer<targeterImage>>& trainingImages,
											  QExplicitlySharedDataPointer<targeterImage>& detectionImage, COOCMatrix* coocTraining,
											  int regionDistance, int distanceBins, int NoClusters, bool bCrossEntropy, 
											  bool bProcessGrayscale, bool bFASTCOOC)
{
#ifdef DEBUGPRINT
	DBOUT("Function Name: " << Q_FUNC_INFO << std::endl);
#endif
	// training phase ////

	if(trainingImages.length()<=0)
		return;

	int histSizeIntensity = 256;
	int histSizeHue = 180;

	int* clusterHistIntensity = new int[histSizeIntensity];
	int* clusterHistHue = new int[histSizeHue];
	int* clusterImageIntensity = nullptr;
	int* clusterImageHue = nullptr;

	// should be taken out of here and produced when the target image is created

	// cluster intensity and hue of images
	bool isColour = HelperFunctions::isGrayImage(detectionImage->getImage());

	int maxw = trainingImages[0]->Rows();
	int maxh = trainingImages[0]->Cols();

	for (int i = 0; i < trainingImages.length(); i++)
	{
		maxw = MAX(maxw, trainingImages[i]->Cols());
		maxh = MAX(maxh, trainingImages[i]->Rows());
	}

	initialiseCOOCMatrix(coocTraining, maxw, maxh, regionDistance, distanceBins, NoClusters, bFASTCOOC);
		
	for(int i=0; i<trainingImages.length(); i++)
	{
		int w = trainingImages[i]->Cols();
		int h = trainingImages[i]->Rows();

		clusterImageIntensity = new int[w*h];
		clusterImageHue = new int[w*h];

		HistogramClustering(trainingImages[i]->getImage(), coocTraining, clusterImageIntensity, clusterImageHue,
							histSizeIntensity, histSizeHue, NoClusters, bProcessGrayscale, isColour);

		// generate concurrence matrices from training images
		getCoocuranceHistogram(clusterImageIntensity, clusterImageHue, trainingImages[i]->get1DImage(imageType::mask), trainingImages[i]->getMaskType(), 
								w, h, coocTraining, bProcessGrayscale, HelperFunctions::isGrayImage(trainingImages[i]->getImage()), bFASTCOOC);

		if (clusterImageIntensity != nullptr)
			delete[] clusterImageIntensity;
		if (clusterImageHue != nullptr)
			delete[] clusterImageHue;
	}

	if (clusterHistIntensity != nullptr)
		delete[] clusterHistIntensity;
	if (clusterHistHue != nullptr)
		delete[] clusterHistHue;
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
void FindTargets::HistogramClustering(cv::Mat im, COOCMatrix* cooc, int* clusterImageIntensity, int* clusterImageHue,
									  int histSizeIntensity, int histSizeHue, int NoClusters, bool bProcessGrayscale, bool imageIsGray)
{
	std::vector<cv::Mat> hsv_planes;
	cv::Mat image1_gray;
	cv::Scalar mean, stdev;

	if (imageIsGray)
	{
		DBOUT("greyscale image" << std::endl);

		if (bProcessGrayscale)
		{
			cv::cvtColor(im, image1_gray, CV_BGR2GRAY);
			cooc->averageIntensity = HistogramClusterImage(cooc->intensityHist, &image1_gray, clusterImageIntensity, histSizeIntensity, NoClusters);
		}
		else
		{
			split(im, hsv_planes);

#ifdef DEBUGIMAGES
			imshow("gray", hsv_planes[0]);                   // Show our image inside it.
#endif
			cooc->averageIntensity = HistogramClusterImage(cooc->intensityHist, &hsv_planes[1], clusterImageIntensity, histSizeIntensity, NoClusters);
		}
	}
	else
	{
		cv::Mat hsvImage;
		std::vector<cv::Mat> hsv_planes;

		DBOUT("colour image" << std::endl);

		cv::cvtColor(im, hsvImage, CV_BGR2HLS);

		split(hsvImage, hsv_planes);

#ifdef DEBUGIMAGES
		cv::String s = "hue ";

		namedWindow(s, WINDOW_AUTOSIZE);// Create a window for display.
		imshow(s, hsv_planes[0]);                   // Show our image inside it.
#endif
		cooc->averageIntensity = HistogramClusterImage(cooc->intensityHist, &hsv_planes[1], clusterImageIntensity, histSizeIntensity, NoClusters);
		cooc->averageHue = HistogramClusterImage(cooc->hueHist, &hsv_planes[0], clusterImageHue, histSizeHue, NoClusters);
	}
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
cv::Mat FindTargets::ColourOccuranceHistogram(QVector<QExplicitlySharedDataPointer<targeterImage>>& trainingImages,
											  QExplicitlySharedDataPointer<targeterImage>& detectionImage,
											  COOCMatrix* coocTraining, int regionDistance, int distanceBins, 
											  int NoClusters, bool bCrossEntropy, bool bProcessGrayscale, bool bFASTCOOC, 
											  bool bCorrectBackground)
{
#ifdef DEBUGPRINT
	DBOUT("Function Name: " << Q_FUNC_INFO << std::endl);
#endif
	// training phase ////

	trainColourOccuranceHistogram(trainingImages, detectionImage, coocTraining, regionDistance, distanceBins,  NoClusters,  
								bCrossEntropy, bProcessGrayscale, bFASTCOOC);

	// cluster detect image

	// testing phase
	cv::Mat score = detectCOOCHistogram(detectionImage->getImage(), coocTraining, bCrossEntropy, bProcessGrayscale, bFASTCOOC, bCorrectBackground);

	// clean up
	if (coocTraining->coMatrixHue != nullptr)
		delete[] coocTraining->coMatrixHue;
	if (coocTraining->coMatrixIntensity != nullptr)
		delete[] coocTraining->coMatrixIntensity;

	return score;
}

void FindTargets::initialiseCOOCMatrix(COOCMatrix* cooc, int w, int h, int regionDistance, int distanceBins, int NoClusters, bool bFASTCOOC)
{
	int regionWidth = w;
	int regionHeight = h;

	bool bSuccess = true;

#ifdef _CUDA_CODE_COMPILE_
	// limit it to warp size
	regionDistance = MIN(32, regionDistance);
	int optiDist = 16;
#endif
	// limit it to maximum size of region
	regionWidth = MIN(regionDistance, regionWidth);
	regionHeight = MIN(regionDistance, regionHeight);
#ifdef _CUDA_CODE_COMPILE_
	int inc_W = 1;
	int inc_H = 1;
#else
if(bFASTCOOC)
{
	int inc_W = 1;
	int inc_H = 1; 
}
else
{
	int inc_W = regionWidth / 2;
	int inc_H = regionHeight / 2;
}
#endif

	// distance should not be more than 32 as should sizes for CUDA
	regionDistance = MAX(regionWidth, regionHeight);

	// make distance divisible by 2
	//distance = (distance >> 1) << 1;

	int rw = regionWidth - 1;
	int rh = regionHeight - 1;
	float maxDist = ceil(sqrt(rw*rw + rh*rh));

	// clusters test and training images for RGB values
	cooc->coMatrixHue = nullptr;
	cooc->coMatrixIntensity = nullptr;
	
	if(bFASTCOOC)
	{
		cooc->coDIMX = NoClusters*2;
		cooc->coDIMY = distanceBins;
	}
	else
	{
		cooc->coDIMX = NoClusters;
		cooc->coDIMY = NoClusters;
	}

	cooc->coDIMZ = distanceBins;
	cooc->regionHeight = regionHeight;
	cooc->regionWidth = regionWidth;
	cooc->maxDist = maxDist;
	cooc->incrementWidth = inc_W;
	cooc->incrementHeight = inc_H;

	int CoocSize = cooc->coDIMX*cooc->coDIMY*cooc->coDIMZ;

	cooc->coMatrixIntensity = new float[CoocSize];
	cooc->coMatrixHue = new float[CoocSize];

	for (int i = 0; i < CoocSize; i++)
	{
		cooc->coMatrixIntensity[i] = 0.0;
		cooc->coMatrixHue[i] = 0.0;
	}	
}

cv::Mat FindTargets::detectCOOCHistogram( cv::Mat detectionImage, COOCMatrix* coocTraining, bool bCrossEntropy, 
										bool bProcessGrayscale, bool bFASTCOOC, bool bCorrectBackground)
{
	if(coocTraining->coDIMX == 0 || coocTraining->coDIMY == 0 || coocTraining->coDIMZ ==0)
		return cv::Mat();
	

	int w_d = detectionImage.cols;
	int h_d = detectionImage.rows;

	bool bSuccess = true;

	// allocate matrix
	float* scoreImage = nullptr;

	int CoocSize = coocTraining->coDIMX*coocTraining->coDIMY*coocTraining->coDIMZ;

#ifdef DEBUGIMAGES
	imshow("training", HelperFunctions::putImageScale(trainingImages[0]->get1DImage(), trainingImages[0].Cols(), trainingImages[0].Rows()));                   // Show our image inside it.
	imshow("test", HelperFunctions::putImageScale(detectionImage->get1DImage(), detectionImage.Cols(), detectionImage.Rows()));                   // Show our image inside it.
#endif
	freopen("CONOUT$", "wb", stdout);

	//int* testing = kMeansRGB(detectionImage, NoClusters, 1000);
	int histSizeIntensity = 256;
	int histSizeHue = 180;

	int* clusterImageIntensity = new int[w_d*h_d];
	int* clusterImageHue = new int[w_d*h_d];

	if(bCorrectBackground)
	{
		cv::Mat out;
		ImageProcessing ip;
		detectionImage = ip.subtractBackground(detectionImage, out);
	}

	HistogramClustering(detectionImage, coocTraining, clusterImageIntensity, clusterImageHue,
						histSizeIntensity, histSizeHue, coocTraining->coDIMX, bProcessGrayscale, 
						HelperFunctions::isGrayImage(detectionImage));

	// scan test image calculate intersection value save value to image
	//float* result = findTargets(detectionImage, coMatrixTrain, NoClusters, distance, bCrossEntropy);

	scoreImage = new float[w_d*h_d];

	for (int i = 0; i < w_d*h_d; i++)
		scoreImage[i] = 0.0;

#ifdef _CUDA_CODE_COMPILE_
	//printCoocuranceHistogram(coMatrix_TargetIntensity, CoocSize, CoocSize, 0, 2);

	// create the cuda class object
	cudaScore cudaS(w_d, h_d, CoocSize);

	bSuccess = cudaS.FindTargets(clusterImageIntensity, scoreImage, w_d, h_d, coocTraining, true, bCrossEntropy, bFASTCOOC);

	if (!HelperFunctions::isGrayImage(detectionImage) && !bProcessGrayscale)
	{
		bSuccess = cudaS.FindTargets(clusterImageHue, scoreImage, w_d, h_d, coocTraining, false, bCrossEntropy, bFASTCOOC);
	}
#else  
	FindTargets::findTargets(clusterImageIntensity, clusterImageHue, scoreImage, w_d, h_d, coocTraining, bCrossEntropy, 
										  HelperFunctions::isGrayImage(detectionImage->getImage()) || bProcessGrayscale);
#endif

	delete [] clusterImageIntensity;
	delete [] clusterImageHue;

	cv::Mat sim;

	if (bSuccess)
		sim = HelperFunctions::putImageScale<float>(scoreImage, w_d, h_d);
	else
		sim = cv::Mat();

	if (scoreImage != nullptr)
		delete[] scoreImage;

	return sim;
}



//************************************
// Method:    HSVHist
// FullName:  FindTargets::HSVHist
// Access:    public 
// Returns:   int*
// Qualifier:
// Parameter: QExplicitlySharedDataPointer<targeterImage> detectionImage
// Parameter: const cv::Mat * pchannel
// Parameter: int NoClusters
// Parameter: imageType::imageType imType
//************************************
int FindTargets::HistogramClusterImage(cv::Mat hist, const cv::Mat* pchannel, int* pClusterImage, int histSize, int NoClusters)
{
	int w = pchannel->cols;
	int h = pchannel->rows;
	int val, sum=0;

	int* pClusterIndexImage = new int[w*h];

	// //////////////////////////////////////////////////////////////////
	// here we cluster image based on its hue histogram /////////////////
	ImageProcessing ip;
	
	// takes an histogram and provides an index into a clusters for each greyscale
	ip.histClusterRGBImage(hist, pClusterIndexImage, histSize, NoClusters);

	// relabel image with cluster
	for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
		{
			int index = cvFloor(pchannel->at<uchar>(j, i));

			if(index<w*h)
			{
				val = pClusterIndexImage[index];
			}
			else
			{
				val = NoClusters-1;
				DBOUT("error index out of bounds " << Q_FUNC_INFO << index << " vs. " << w*h << std::endl);
			}

			sum += val;
			pClusterImage[i + j*w] = val;
		}

	delete [] pClusterIndexImage;

#ifdef DEBUGIMAGES
	cv::Mat histimage = HelperFunctions::displayHistogram(hist, histSize, 500, 500);

	cv::String s = "histogram ";
	s += (imType == imageType::hue ? "hue" : "intensity");

	namedWindow(s, WINDOW_AUTOSIZE);		// Create a window for display.
	imshow(s, histimage);                   // Show our image inside it.
#endif // endif

	return sum/(w*h);
}

//************************************
// Method:    labelTrainingImagesGray
// FullName:  FindTargets::labelTrainingImagesGray
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: QVector<QExplicitlySharedDataPointer<targeterImage>> TrainImages
// Parameter: int * pClusterHist
//************************************
void FindTargets::labelTrainingImagesGray(const QVector<QExplicitlySharedDataPointer<targeterImage>>& TrainImages, int* pClusterHist)
{
	int w, h, i;
	cv::Mat image1_gray;
	cv::Mat dst, hsvImage;
	std::vector<cv::Mat> hsv_planes;
	int* pImage = nullptr;

	// assign clusters to training images
	for (int k = 0; k < TrainImages.size(); k++)
	{
		w = TrainImages[k]->Cols(), h = TrainImages[k]->Rows();

		pImage = new int[w*h];

		if (TrainImages[k]->getImage().channels() > 1)
		{
			cv::cvtColor(TrainImages[k]->getImage(), image1_gray, cv::COLOR_BGR2GRAY);
		}
		else
		{
			image1_gray = TrainImages[k]->getImage();
		}

		// label image with cluster
		for (i = 0; i < w; i++)
			for (int j = 0; j < h; j++)
				pImage[i + j*w] = pClusterHist[cvFloor(image1_gray.at<uchar>(j, i))];

		TrainImages[k]->set1DImage(pImage);
	}
}

//************************************
// Method:    labelTrainingImagesHSV
// FullName:  FindTargets::labelTrainingImagesHSV
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: QVector<QExplicitlySharedDataPointer<targeterImage>> TrainImages
// Parameter: int * pClusterHistHue
// Parameter: int * pClusterHistIntensity
//************************************
void FindTargets::labelTrainingImagesHSV(const QVector<QExplicitlySharedDataPointer<targeterImage>>& TrainImages, int* pClusterHistHue, int* pClusterHistIntensity)
{
	int w, h, i;
	cv::Mat image1_gray;
	cv::Mat dst, hsvImage;
	std::vector<cv::Mat> hsv_planes;
	int* pImage = nullptr;

	// assign clusters to training images
	for (int k = 0; k < TrainImages.size(); k++)
	{
		w = TrainImages[k]->Cols(), h = TrainImages[k]->Rows();

		// get float image for 360 degrees
		cvtColor(TrainImages[k]->getImage(), hsvImage, CV_BGR2HLS);

		split(hsvImage, hsv_planes);

		pImage = new int[w*h];

		// label image with cluster
		for (i = 0; i < w; i++)
			for (int j = 0; j < h; j++)
			{
				pImage[i + j*w] = pClusterHistHue[cvFloor(hsv_planes[0].at<uchar>(j, i))];
			}

		TrainImages[k]->set1DImage(pImage, imageType::display);

		pImage = new int[w*h];

		// label image with cluster
		for (i = 0; i < w; i++)
			for (int j = 0; j < h; j++)
			{
				pImage[i + j*w] = pClusterHistIntensity[cvFloor(hsv_planes[1].at<uchar>(j, i))];
			}

		TrainImages[k]->set1DImage(pImage, imageType::hue);
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
float FindTargets::getCoocMatrixGray(int* pImage, int w, int h, int* pMask, drawingMode::drawingMode maskType, 
										int startX, int startY, COOCMatrix* cooc, bool bFASTCOOC)
{
	int i, j, c1, c2, x, y, ind, nextIndex, nextI, nextJ;
	float sum = 0;
	int regionWidth = cooc->regionWidth;
	int regionHeight = cooc->regionHeight;

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

					if(bFASTCOOC)
					{
						c1 = MAX(0, MIN(cooc->coDIMX-1, cooc->coDIMX/2 + (cooc->averageIntensity - c1)));
						float dxy = sqrt(i*i+j*j);
						int d = MIN(cooc->coDIMY-1, int(cooc->coDIMY*(dxy / cooc->maxDist)));

						if (c1 < cooc->coDIMX && d < cooc->coDIMY)
						{
							ind = c1 + d*cooc->coDIMX;

							cooc->coMatrixIntensity[ind] += 1.0;

							sum += 1.0;
						}
						else
							DBOUT("error index out of bounds " << Q_FUNC_INFO << c1 << " vs. " << cooc->coDIMX << "," << d << " vs. " << cooc->coDIMY << std::endl);
					}
					else
					{
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

										///	int d = max(x - i, y - j);	// maximum distance, city block
										float dx = (x - i);
										float dy = (y - j);
										float dxy = sqrt(dx*dx + dy*dy);
										int d = MIN(cooc->coDIMZ-1, int(cooc->coDIMZ*(dxy / cooc->maxDist)));

										if (c1 < cooc->coDIMX && c2 < cooc->coDIMY && d < cooc->coDIMZ)
										{
											ind = c1 + c2*cooc->coDIMX + d*cooc->coDIMX*cooc->coDIMY; //c1 + NoClusters * (c2 + NoClusters * d); //i + height* (j + width* k)

											cooc->coMatrixIntensity[ind] += 1.0;

											sum += 1.0;
										}
										else
											DBOUT("error index out of bounds " << Q_FUNC_INFO << c1 << " vs. " << cooc->coDIMX << "," << c2 << " vs. " << cooc->coDIMY << "," << d << " vs. " << cooc->coDIMZ << std::endl);
									}
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
float FindTargets::getCoocMatrixHSV(int* pImage, int* pHue, int w, int h, int* pMask, drawingMode::drawingMode maskType, 
									int startX, int startY, COOCMatrix* cooc, bool bFASTCOOC)
{
	int i, j, h1, h2, i1, i2, x, y, indImage, indHue;
	long ind;
	float sum = 0;
	int regionWidth = cooc->regionWidth; 
	int regionHeight = cooc->regionHeight;

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

					if (bFASTCOOC)
					{
						int c1 = MAX(0, MIN(cooc->coDIMX-1, cooc->coDIMX/2 + (cooc->averageIntensity - i1)));
						int c2 = MAX(0, MIN(cooc->coDIMX-1, cooc->coDIMX/2 + (cooc->averageHue - h1)));

						float dxy = sqrt(i*i + j*j);
						int d = MIN(cooc->coDIMY-1, int(cooc->coDIMY*(dxy / cooc->maxDist)));

						if (c1 < cooc->coDIMX && d < cooc->coDIMY)
						{
							indImage = c1 + d*cooc->coDIMX;
							indHue = c2 + d*cooc->coDIMX;

							cooc->coMatrixIntensity[indImage] += 1.0;
							cooc->coMatrixHue[indHue] += 1.0;

							sum += 1.0;
						}
						else
							DBOUT("error index out of bounds " << Q_FUNC_INFO << c1 << " vs. " << cooc->coDIMX << "," << d << " vs. " << cooc->coDIMY << std::endl);
					}
					else
					{
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

										//int d = max(x - i, y - j);	// maximum distance
										float dx = (x - i);
										float dy = (y - j);
										float dxy = sqrt(dx*dx + dy*dy);
										int d = MIN(cooc->coDIMZ-1, int(cooc->coDIMZ*(dxy/cooc->maxDist)));

										if (i1 < cooc->coDIMX && i2 < cooc->coDIMY && h1 < cooc->coDIMX && h2 < cooc->coDIMY &&	d < cooc->coDIMZ)
										{
											indImage = i1 + i2*cooc->coDIMX + d*cooc->coDIMX*cooc->coDIMY;
											indHue   = h1 + h2*cooc->coDIMX + d*cooc->coDIMX*cooc->coDIMY;	// hue indexes differently than intensity!

											cooc->coMatrixIntensity[indImage] += 1.0;
											cooc->coMatrixHue[indHue] += 1.0;

											sum += 1.0;
										}
										else
											DBOUT("error index out of bounds " << Q_FUNC_INFO << i1 << " vs. " << cooc->coDIMX << "," << i2 << " vs. " << cooc->coDIMY
												<< h1 << " vs. " << cooc->coDIMX << "," << h2 << " vs. " << cooc->coDIMY << "," << d << " vs. " << cooc->coDIMZ << std::endl);
									}
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
*  Gets cooccurrence matrix of image
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
void FindTargets::getCoocuranceHistogram(int* pImage, int* pHue, int* mask, drawingMode::drawingMode maskType, 
										int w, int h, COOCMatrix* cooc, bool bProcessGrayscale, bool isGrayScale, bool bFASTCOOC)
{
#ifdef DEBUGPRINT
	DBOUT("Function Name: " << Q_FUNC_INFO);
#endif
	int i, x, y, stepX = 1, stepY = 1;
	float sum = 0;

	int regionWidth = cooc->regionWidth;
	int regionHeight = cooc->regionHeight;
	int inc_W = cooc->incrementWidth;
	int inc_H = cooc->incrementHeight;

	// should not step through target - should get cooc from whole target region - but then larger distances
	if (isGrayScale || bProcessGrayscale)
	{
		for (y = 0; y < h; y += inc_H)
			for (x = 0; x < w; x += inc_W)
				sum += getCoocMatrixGray(pImage, w, h, mask, maskType, x, y, cooc, bFASTCOOC);
			
		// normalise histogram
		for (i = 0; i < cooc->coDIMX*cooc->coDIMY*cooc->coDIMZ; i++)
			cooc->coMatrixIntensity[i] /= sum;
	}
	else
	{
		for (y = 0; y < h; y += inc_H)
			for (x = 0; x < w; x += inc_W)
				sum += getCoocMatrixHSV(pImage, pHue, w, h,	mask, maskType, x, y, cooc, bFASTCOOC);

		// normalise histogram
		for (i = 0; i<cooc->coDIMX*cooc->coDIMY*cooc->coDIMZ; i++)
		{
			cooc->coMatrixIntensity[i] /= sum;
			cooc->coMatrixHue[i] /= sum;
		}
	}
	
	DBOUT("training image co-occurrance histogram" << std::endl);

	//printCoocuranceHistogram(cooc->coMatrixIntensity, cooc->coDIMX, cooc->coDIMX, cooc->coDIMZ);
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
void FindTargets::findTargets(int* intensityImage, int* hueImage, float* scoreImage, int w_d, int h_d, COOCMatrix* coocTarget, bool bCrossEntropy, bool bIsGray)
{

#ifdef DEBUGPRINT
	DBOUT("Function Name: " << Q_FUNC_INFO << std::endl);
#endif
	int i, j, x, y;
	float sum = 0, score = 0;
	COOCMatrix coocDetect;

	// copy settings
	coocDetect.coMatrixHue = nullptr;
	coocDetect.coMatrixIntensity = nullptr;
	coocDetect.coDIMX = coocTarget->coDIMX;
	coocDetect.coDIMY = coocTarget->coDIMY;
	coocDetect.coDIMZ = coocTarget->coDIMZ;
	coocDetect.regionHeight = coocTarget->regionHeight;
	coocDetect.regionWidth = coocTarget->regionWidth;
	coocDetect.maxDist = coocTarget->maxDist;
	coocDetect.incrementWidth = coocTarget->incrementWidth;
	coocDetect.incrementHeight = coocTarget->incrementHeight;

	long CoocSize = coocTarget->coDIMX* coocTarget->coDIMY* coocTarget->coDIMZ;

	//if (!bIsGray)
	//	CoocSize = NoClusters*NoClusters*NoClusters*NoClusters*maxD;

	coocDetect.coMatrixIntensity = new float[CoocSize];

	if(!bIsGray)
		coocDetect.coMatrixHue = new float[CoocSize];

	/*
	int maskIndex = detectionImage.getFriendArrayIndexOfType(imageType::target);

	targeterImage pMaskImage = NULL;
	int* pMask1D = NULL;
	drawingMode::drawingMode maskType;

	if (maskIndex >= 0 && maxD >= pMaskImage.Rows() && maxD >= pMaskImage.Cols())
	{
	pMaskImage = detectionImage.getGlobalImage(maskIndex);
	pMask1D = pMaskImage.get1DImage(imageType::mask);
	maskType = pMaskImage->getMaskType();
	}
	*/

	for (i = 0; i < w_d*h_d; i++)
		scoreImage[i] = 0.0;

	for (y = 0; y < h_d; y += coocTarget->incrementHeight)
		for (x = 0; x < w_d; x += coocTarget->incrementWidth)
		{
			// zero co-occurrence matrix
			for (i = 0, sum = 0; i<CoocSize; i++)
				coocDetect.coMatrixIntensity[i] = 0.0;

			//memset(coMatrixF, 0.0, NoClusters*NoClusters*maxD*sizeof(float));

			// no mask - I can't think how to use one properly
			// a) because of size being different to region 
			// b) in the case of multiple targets -> multiple masks?!
			if (bIsGray)
			{
				sum = getCoocMatrixGray(intensityImage, w_d, h_d, NULL, drawingMode::none, x, y, &coocDetect);
			}
			else
			{
				// zero co-occurrence matrix
				for (i = 0, sum = 0; i < CoocSize; i++)
					coocDetect.coMatrixHue[i] = 0.0;

				sum = getCoocMatrixHSV(intensityImage, hueImage, w_d, h_d, NULL, drawingMode::none, x, y, &coocDetect);
			}
			if (sum >0)
			{
				if(bCrossEntropy)
				{
					// get score by  Kullback–Leibler divergence of cooc matrices
					for (i = 0, score = 0.0; i < CoocSize; i++)
					{
						if(coocDetect.coMatrixIntensity[i]>0 && coocTarget->coMatrixIntensity[i]>0 && sum>0)
							score += coocTarget->coMatrixIntensity[i] * (log(coocTarget->coMatrixIntensity[i]) / log(coocDetect.coMatrixIntensity[i] / sum));		// Kullback–Leibler divergence P(coMatrixF | coMatrixTestF)
					}
				}
				else
				{
					// get score by minimum intersection of cooc matrices
					for (i = 0, score = 0.0; i < CoocSize; i++)
					{
						if (sum > 0)
						{
							score += fmin(coocDetect.coMatrixIntensity[i] / sum, coocTarget->coMatrixIntensity[i]);	//fabs(coMatrixF[i]- coMatrixTestF[i]);		// minimum intersection
							//score += sqrt((coMatrixIntensity[i] / sum) * coMatrixIntensity_Target[i]);		// Bhattacharyya distance

							if (!bIsGray)
							{
								//score += sqrt((coMatrixHue[i] / sum) * coMatrixHue_Target[i]);		// Bhattacharyya distance
								score += fmin(coocDetect.coMatrixHue[i] / sum, coocTarget->coMatrixHue[i]);				// minimum intersection of pdfs
							}
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
					for (j = y; j < y + coocTarget->regionHeight; j++)
						for (i = x; i < x + coocTarget->regionWidth; i++)
						{
							if (j < h_d && i < w_d)
								scoreImage[i + j*w_d] += score;
						}
				}
			}
			//DBOUT(score << ", ");
		}
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
				//	val = 255;	// this is target, 
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

	for (i = 0; i < histSize; i++)
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
	for (i = 0; i < histSize; i++)
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
std::vector<int*> FindTargets::kMeansRGB(cv::Mat img, QVector<cv::Mat> testImgs, int NoClusters, int maxIterations)
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