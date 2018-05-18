// Targeter - target identification software for EUCALL workpackage 6
// Licensed under the GPL License. See LICENSE file in the project root for full license information.
// Copyright(C) 2017  David Watts 

#include "FocusStack.h"
#include "openCVtrilateralFilter.h"
#include "mainwindow.h"
#include "haar.h"
#include "HelperFunctions.h"
#include "imageprocessing.h"
#include "targeterimage.h"

#include <cmath>
#include <QVector>
#include <QMap>

#include "opencv2/opencv.hpp"
#include "opencv/highgui.h"

// cuda gpu functions
#ifdef _CUDA_CODE_COMPILE_
#include "targetDetectionGPU.h"
#endif

using namespace cv;

int FocusStack::getBestFocusImage(QVector<cv::Mat> imageStack, QVector<double>& focusValues, FOCUSALGO::algo Algorithm)
{
	int index = 0;
	double maxEnergy = 0;

	focusValues.empty();

	for(int i=0; i<imageStack.length(); i++)
	{
		double energy = getFocusImage(imageStack[i], Algorithm);

		focusValues.append(energy);

		if (energy > maxEnergy)
		{
			maxEnergy = energy;
			index = i;
		}
	}

	return index;
}

// should this be on the GPU? probably
double FocusStack::getFocusImage(cv::Mat& m, FOCUSALGO::algo Algorithm)
{
	double energy = 0;

	if (Algorithm == FOCUSALGO::DXDY)
	{

#ifdef _CUDA_CODE_COMPILE_
		energy = getFocusScore(HelperFunctions::getCImage(m), m.rows, m.cols);
#else  
		energy = simpleDerivativeEnergy(m, true);	// horizontal 
		energy += simpleDerivativeEnergy(m, false);			// vertical
#endif

	}
	else if (Algorithm == FOCUSALGO::GLVN)
		energy = normalizedGraylevelVariance(m);
	else if (Algorithm == FOCUSALGO::LAPM)
		energy = modifiedLaplacian(m);
	else if (Algorithm == FOCUSALGO::LAPV)
		energy = varianceOfLaplacian(m);
	else if (Algorithm == FOCUSALGO::TENG)
		energy = tenengrad(m, 5);
	else if (Algorithm == FOCUSALGO::HAARPY)
		energy = getImageFocusLevel(m);

	// emit addFocusValue(energy, act);

	return energy;
}

// should this be on the GPU? probably
double FocusStack::getImageFocusLevel(cv::Mat& m)
{
	fname();

	double esum;
	int i, j, w, h, maxI;
	cv::Mat im, em;
	int levels = 6;
	int regionSize = 11; // should be odd
	double probThreshold = 0.5, EnergyThreshold = 70;
	QMap<int, double> totalEnergy;

	cv::cvtColor(m, im, CV_BGR2GRAY, 1);
	im.convertTo(im, CV_64FC1);

	Mat laplace = Haar::LaplacianPyramid(im, levels, false);

	w = m.cols;
	h = m.rows;

	em = Mat::zeros(h, w, CV_64F);

	// calculate Haar Energy image
	Haar::HaarEnergy(laplace, em, w, h, levels, true);

	esum = 0;

	// sum of normalised energy
	for (i = 0; i < w; i++)
		for (j = 0; j < h; j++)
		{
			esum += em.ptr<double>(j)[i] / ((double)levels);
		}

	return esum;
}


double FocusStack::getImageFocusLevel(targeterImage& image)
{
	fname();

	cv::Mat& im = image.getImage();

	if (im.rows > 0 && im.cols > 0)
		return getImageFocusLevel(im);
	else
		return -1;
}


/**
*
* Creates a single 'in focus' image from a vector of images partially in focus (focus stack)
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   FocusStack::processImageStack
* Qualifier 
* @param     QVector<targeterImage> & imageStack 
* @param     QVector<int> & imageIndexes 
* @param     MainWindow * pMainWindow 
* @return    cv::Mat*
* Access     public 
*/
Mat* FocusStack::processImageStack(std::vector<targeterImage>& imageStack, std::vector<int>& imageIndexes, MainWindow* pMainWindow)
{
    fname();

    double esum;
    int i, j, w, h, maxI;
    cv::Mat m, im, bm, em, iim, *pMat;
    int levels =6;
    int regionSize = 11; // should be odd
    double probThreshold = 0.5, EnergyThreshold  = 70;
    QMap<int, double> totalEnergy;

    foreach(int item, imageIndexes)
    {
        m = imageStack[item].getImage();

        cv::cvtColor(m, im, CV_BGR2GRAY,1);
        im.convertTo(im, CV_64FC1);

        Mat laplace = Haar::LaplacianPyramid(im, levels, false);

        if(bm.empty())
        {
            w = m.cols;
            h = m.rows;

            bm = cv::Mat(h, w, CV_64FC1, Scalar(0));
            iim = cv::Mat(h, w, CV_8UC1);
        }
        else
        {
            if(w != m.cols || h != m.rows)
            {
                std::cout << "cannot process images of different size, exiting" << std::endl;
                return NULL;
            }
        }

        em = Mat::zeros(h, w, CV_64F);

        // calculate Haar Energy image
        Haar::HaarEnergy(laplace, em, w, h, levels, true);

        QString s = "laplace image " + QString::number(item);

        //pMainWindow->addCVImage(HelperFunctions::putMatScale(em, true, false), s);

        esum = 0;

        for(i=0; i<w; i++)
            for(j=0; j<h; j++)
            {
                if(em.ptr<double>(j)[i] >= bm.ptr<double>(j)[i])
                {
                    iim.ptr(j)[i] = item+1;  //index
                    bm.ptr<double>(j)[i] = em.ptr<double>(j)[i]; // value
                }

                esum += em.ptr<double>(j)[i]/((double)(levels));
            }

        s = "laplace combined level image " + QString::number(item);

       // pMainWindow->addCVImage(HelperFunctions::putMatScale(iim, true), s);

        totalEnergy.insert(item, esum);

        std::cout << "Image Energy " << item << " : " << totalEnergy[item] << std::endl;
    }


    //pMainWindow->addCVImage(HelperFunctions::putMatScale(iim), "laplace best level image" );

    //energyImages.push_back(bm);

    // integer smooth iim
    //ImageProcessing::GaussianBlur(iim, m.cols, m.rows, 5);
   // ImageProcessing::modalFilter(iim, w, h, regionSize, imageIndexes.size());

    cv::Mat filteredImage = cv::Mat(h, w, CV_8UC1);

    //OpenCVtrilateralFilter tlf;
    //tlf.trilateralFilter(iim, filteredImage, 1.0, 1.0);
    int kernel_length =10;

    filteredImage = iim.clone();

    //cv::bilateralFilter(iim, filteredImage, kernel_length, kernel_length*2, kernel_length/2);

    //pMainWindow->addCVImage(HelperFunctions::putMatScale(filteredImage), "bilateral laplace filtered level image" );

    // better a polynomial fit

    pMat = new Mat(h, w, CV_8UC3);
    cv::Mat pScale = Mat(h, w, CV_8UC1);

    if(true)
    {
        cv::normalize(filteredImage, pScale, 0, 255, NORM_MINMAX, CV_8UC1);

        cv::cvtColor(pScale, *pMat, COLOR_GRAY2RGB, 3);
    }
    else
    {
        // cv::normalize(filteredImage, pScale, 0, imageStack.length()-1, NORM_MINMAX, CV_8UC1);
        pMat = FocusStack::mergeImageStack(imageStack, filteredImage, w, h);

    }
    // ImageProcessing::putMatScale(iim, *pMat);

   // pMainWindow->addCVImage(*pMat, "focus image" );

    return pMat;
}

/**
*
*   Creates a single 'in focus' image from a vector of images partially in focus (focus stack) (alternative implementation)
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   FocusStack::processImageStack3
* Qualifier 
* @param     QVector<targeterImage> & imageStack 
* @param     QVector<int> & imageIndexes 
* @param     MainWindow * pMainWindow 
* @return    cv::Mat*
* Access     public 
*/
cv::Mat* FocusStack::processImageStack3(std::vector<targeterImage>& imageStack, std::vector<int>& imageIndexes, MainWindow* pMainWindow)
{
    fname();

    Mat bm, im;
    int i, j, w, h, maxI;
    cv::Mat m;
    cv::Mat* pMat;
    int levels =6;
    int regionSize = 11; // should be odd
    double probThreshold = 0.5, EnergyThreshold  = 70;
    double maxP, dSum, val, p;

    QMap<int,  Mat> arrWE;

    foreach(int item, imageIndexes)
    {
        m = imageStack[item].getImage();

        cv::cvtColor(m, im, CV_BGR2GRAY,1);
        im.convertTo(im, CV_64FC1);

        if(bm.empty())
        {
            w = m.cols;
            h = m.rows;
        }
        else
        {
            if(w != m.cols || h != m.rows)
            {
                std::cout << "cannot process images of different size, exiting" << std::endl;
                return NULL;
            }
        }

        Haar::Haar2(im, levels);

        // store wavelet images
        arrWE.insert(item, im);
    }

    cv::Mat levelImage = cv::Mat(h, w, CV_8SC1, cv::Scalar(0));

    std::cout << "image is " <<  HelperFunctions::type2str(levelImage.type()) << std::endl;

    // get best levels from images -  image still wavelet image here!
    for(i=0; i<w; i++)
    {
        for(j=0; j<h; j++)
        {
            dSum = 0;

            // get energies of wavelet images
            // get entropy from levels
            foreach(int item, imageIndexes)
                dSum += (arrWE[item].ptr<double>(j)[i])*(arrWE[item].ptr<double>(j)[i]);

            maxP = 0; maxI = 0;

            foreach(int item, imageIndexes)
            {
                val = (arrWE[item].ptr<double>(j)[i])*(arrWE[item].ptr<double>(j)[i]);

                p = val/dSum;   // value of maximum probablity value measure of peakedness of distribution

                if(p >= maxP)
                {
                    maxI = item;
                    maxP = p;
                }
            }

            if(maxP < probThreshold)
            {
                levelImage.ptr<char>(j)[i] = -1;     // flag pixel as being uninformative
                //std::cout << (int)levelImage.ptr<char>(j)[i] << " ";
            }
            else
                levelImage.ptr<char>(j)[i] = maxI;
        }
    }

    pMainWindow->addCVImage(HelperFunctions::putMatScale(levelImage), "level image" );

    // get modal level from wavelet levels - spatially and in resolution
    levelImage = Haar::PyramidLevels(levelImage, w, h, levels, imageIndexes.size());

    pMainWindow->addCVImage(HelperFunctions::putMatScale(levelImage), "after pyramid level image" );

    //GaussianBlur(levelImage, w, h, 5);
    FocusStack::fillErrorRegions(levelImage, w, h, regionSize, imageIndexes.size());

    //cv::Mat a = testReturn(levelImage);

    pMainWindow->addCVImage(HelperFunctions::putMatScale(levelImage), "after fill error regions" );

    // smooth regions
	ImageProcessing::modalFilter(levelImage, w, h, regionSize, imageIndexes.size());

    pMainWindow->addCVImage(HelperFunctions::putMatScale(levelImage), "after modal filter" );

    pMat = FocusStack::mergeImageStack(imageStack, levelImage, w, h);

    //pMat = (Mat*)ImageProcessing::putImageScale(levelImage, w, h);

    pMainWindow->addCVImage(*pMat, "focus image");

    return pMat;
}

cv::Mat FocusStack::createLaplacianEnergyImage(cv::Mat im, int levels, bool bDisplay, bool bEnergy)
{
	cv::Mat norm;
	double dVal, ldVal;

	cv::cvtColor(im, im, CV_BGR2GRAY, 1);
	im.convertTo(im, CV_64FC1);

	Mat laplace = Haar::LaplacianPyramid(im, levels, false);

	int w = im.cols;
	int h = im.rows;

	if (bEnergy)
	{
		cv::Mat energy = Mat::zeros(h, w, CV_64F);

		// calculate Haar Energy image
		Haar::HaarEnergy(laplace, energy, w, h, levels, true, false);

		if (bDisplay)
		{
			for (int i = 0; i < w; i++)
				for (int j = 0; j < h; j++)
				{
					dVal = energy.ptr<double>(j)[i];
					ldVal = log(dVal+1);
					//DBOUT(ldVal << " ");
					energy.ptr<double>(j)[i] = ldVal;
				}
			cv::normalize(energy, norm, 0, 255, NORM_MINMAX, CV_8UC1);
			norm.convertTo(norm, CV_8UC1);
			return norm;
		}
		else
			return energy;
	}
	else
	{
		if (bDisplay)
		{
			cv::normalize(laplace, norm, 0, 255, NORM_MINMAX, CV_8UC1);
			norm.convertTo(norm, CV_8UC1);

			return norm;
		}
		else
			return laplace;
	}

	
}

double** FocusStack::getEntropyImage(QMap<int, Mat>& arrWE, int w, int h, std::vector<int>& imageIndexes, double& bestEntropyValue)
{
	int i, j;
	double** energyEntropy = new double*[w];
	int N = imageIndexes.size();
	double lN = log((double)N);
	double entropyValue, entropySum, dSum, val, pVal;
	bestEntropyValue = 0;

	// get probability distribution of each level having a particular energy
	for (i = 0; i < w; i++)
	{
		energyEntropy[i] = new double[h];

		for (j = 0; j < h; j++)
		{
			entropySum = 0;
			dSum = 0.0;

			// get entropy from levels
			foreach(int item, imageIndexes)
			{
				//DBOUT(arrWE[item].ptr<double>(j)[i] <<  ", ");
				dSum += arrWE[item].ptr<double>(j)[i];
			}

			//DBOUT(std::endl);
			// sum to 1 down the levels -> probabilities
			foreach(int item, imageIndexes)
			{
				val = arrWE[item].ptr<double>(j)[i];
				pVal = val / dSum;
				//DBOUT(val*log(val) << ", ");
				entropySum += pVal*log(pVal);
			}

			entropyValue = fabs(1.0 - (-entropySum / lN));

			energyEntropy[i][j] = entropyValue;
		

			if (entropyValue > bestEntropyValue)
			{
				//foreach(int item, imageIndexes)
				//	DBOUT(arrWE[item].ptr<double>(j)[i] <<  ", ");

				//DBOUT(entropyValue<<std::endl);
				bestEntropyValue = entropyValue;
			}
			//DBOUT(" = "<< (-entropySum) << std::endl);
		}
	}

	return energyEntropy;
}

double*** FocusStack::getEnergyProbabilityImage(QMap<int, Mat>& arrWE, double** energyEntropy, int w, int h, std::vector<int>& imageIndexes, double bestEntropyValue, double entropyFactor, double distanceFactor)
{
	int x, y, i, j, r = 2;
	int N = imageIndexes.size();
	double distance;
	double*** summedEnergy = new double**[w];

	// get scaled value of modified energy distribution
	for (i = 0; i < w; i++)
	{
		summedEnergy[i] = new double*[h];

		for (j = 0; j < h; j++)
		{
			summedEnergy[i][j] = new double[N];

			// collect probabilities in vector
			foreach(int item, imageIndexes)
			{
				if (i == 416 && j == 388)
					DBOUT(arrWE[item].ptr<double>(j)[i]);

				summedEnergy[i][j][item] = 0;

				for (x = i - r; x <= i + r; x++)
					for (y = j - r; y <= j + r; y++)
					{
						if (x >= 0 && y >= 0 && x < w && y < h)
						{
							// check neighbours, sum up level vectors for position weighted by entropy of distribution and distance from i,j
							distance = max(abs(i - x), abs(j - y));

							// multiply by inverse factor of entropy of sequence ((log(N)-E)/1) - (log(N) = maximum entropy for sequence N long)
							// and dividing by factor of distance from position
							if (arrWE[item].ptr<double>(y)[x] > 0.0)
							{
								summedEnergy[i][j][item] += (entropyFactor*((log(double(N)) - energyEntropy[x][y]) / 1.0)) * arrWE[item].ptr<double>(y)[x] / (distanceFactor*(1.0 / (1.0 + distance)));
								//summedEnergy[i][j][item] += (entropyFactor*(energyEntropy[x][y] / bestEntropyValue)) * arrWE[item].ptr<double>(y)[x] / (distanceFactor*(1.0 / (1.0 + distance)));
							}
						}
					}
			}
		}
	}
	return summedEnergy;
}



cv::Mat FocusStack::processImageStack4(std::vector<targeterImage>& imageStack, std::vector<int>& imageIndexes, MainWindow* pMainWindow)
{
	fname();

	Mat bm, im, m, energy;
	int i, j, x, y, w, h, maxI, N= imageIndexes.size();
	int levels = 3;
	int regionSize = 11; // should be odd
	double probThreshold = 0.5, EnergyThreshold = 70;
	double entropySum, val, pVal, dSum, p, E, bestLevel, distance, entropyFactor =1, distanceFactor = 1;

	QMap<int, Mat> arrWE;

	foreach(int item, imageIndexes)
	{
		m = imageStack[item].getImage();

		if (arrWE.empty())
		{
			w = m.cols;
			h = m.rows;

			// resize image to be divisable by levels
		}
		else
		{
			if (w != m.cols || h != m.rows)
			{
				std::cout << "cannot process images of different size, exiting" << std::endl;
				return cv::Mat();
			}
		}

		energy = createLaplacianEnergyImage(m, levels, false, true);
		
		// store wavelet images														// seems that same image being stored all the time
		arrWE.insert(item, energy.clone());
	}

	double entropyValue, bestEntropyValue = 0;

	double** energyEntropy = getEntropyImage(arrWE, w, h, imageIndexes, bestEntropyValue);

	//double*** summedEnergy = getEnergyProbabilityImage(arrWE, energyEntropy, w, h, imageIndexes, bestEntropyValue, entropyFactor, distanceFactor);

	for (i = 0; i < w; i++)
		delete[]  energyEntropy[i];
		
	delete[]  energyEntropy;


	/*
	Mat en;
	cv::normalize(ee, en, 0, 255, NORM_MINMAX, CV_8UC1);
	en.convertTo(en, CV_8UC1);
	return en;
	*/

	cv::Mat levelImage = cv::Mat(h, w, CV_8UC3);
	cv::Mat inpaintMask  = cv::Mat(h, w, CV_32S);
	
	// get expected value of modified energy distribution
	for (j = 0; j < h; j++)
	{
		for (i = 0; i < w; i++)
		{
			
			dSum = 0.0;

			// collect probabilities in vector
			foreach(int item, imageIndexes)
			{
				dSum += arrWE[item].ptr<double>(j)[i];
				//dSum += summedEnergy[i][j][item];
			}

			double prob, expectedValue=0, maxProb = 0, entropy=0;
			int level = 0;
			
			if (dSum > 0)
			{
				// get expected value from probability
				foreach(int item, imageIndexes)
				{
				
				//	prob = summedEnergy[i][j][item] / dSum;
					prob =arrWE[item].ptr<double>(j)[i]/ dSum;
					entropy += prob*log(prob);
			
					//expectedValue += double(item)*prob; // E(L)
	
					if(prob>maxProb)
					{
						maxProb = prob;	// maximum likelihood - good choice, but sometimes distribution with 2 peaks.
						level = item;
					}
				}
				
				if ((-entropy / log(N)) > 0.95)	// entropy threshold
				{
					//levelImage.ptr<Vec3b>(j)[i] = Vec3b(0, 0, 0);
					inpaintMask.ptr<int>(j)[i] = -1;
				}
				else
				{
					inpaintMask.ptr<int>(j)[i] = level;
				}
			}
			else
				inpaintMask.ptr<int>(j)[i] = -1;
		}
	}

	// for each pixel position calculate level as 
	// add to 3d vector

	//cv::inpaint(levelImage, inpaintMask, levelImage, 3, INPAINT_NS);

	cv::Mat out = cv::Mat(h, w, CV_32S);

	//FillMissingPixels<int>(inpaintMask, out);

	out = inpaintMask.clone();

	// rescale original image back 
	
	for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
		{
			int level = out.ptr<int>(j)[i];

			if (level >= 0)
				levelImage.ptr<Vec3b>(j)[i] = imageStack[level].getImage().ptr<Vec3b>(j)[i];//Vec3b(255 * level / N, 255 * level / N, 255 * level / N); // 
			else
				levelImage.ptr<Vec3b>(j)[i] = Vec3b(0, 0, 0);
		}

	// L = sum(E(L)*((1-Entropy)/1)/(dist+1)
	
	// where dist is distance to neighbour pixel, entropy is ntropy of the energy distribution over the laplacian levels & E(L) is the expected value sum(L*P(L))
	/*
	for (i = 0; i < w; i++)
	{
		for (j = 0; j < h; j++)
			delete[] summedEnergy[i][j];
		delete[]  summedEnergy[i];
	}
	delete[]  summedEnergy;
	*/
	return levelImage;
}


/**
*
*   Creates a single 'in focus' image from a vector of images partially in focus (focus stack) (alternative implementation)
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   FocusStack::processImageStack2
* Qualifier 
* @param     QVector<targeterImage> & imageStack 
* @param     QVector<int> & imageIndexes 
* @param     MainWindow * pMainWindow 
* @return    cv::Mat*
* Access     public 
*/
cv::Mat* FocusStack::processImageStack2(std::vector<targeterImage>& imageStack, std::vector<int>& imageIndexes, MainWindow* pMainWindow)
{
    fname();

    double esum;
    int i, j, w, h;
    cv::Mat m, im, bm, em, iim;
    cv::Mat* pMat;
    int levels =3;
    int regionSize = 31; // should be odd
    bool bHaar = true;

    // QVector<Mat*> energyImages;

    QMap<int, double> totalEnergy;

    foreach(int item, imageIndexes)
    {
        m = imageStack[item].getImage();

        if(bHaar)
        {
            // im = (double*)ImageProcessing::getImage<double>(m);

            cv::cvtColor(m, im,CV_BGR2GRAY,1);
            im.convertTo(im, CV_64FC1);

            if(bm.empty())
            {
                w = m.cols;
                h = m.rows;

                bm = cv::Mat(h, w, CV_64FC1, Scalar(0));
                iim = cv::Mat(h, w, CV_8UC1);
            }

            Haar::Haar2(im, levels);

            em = Mat::zeros(h, w, CV_64F);

            // calculate Haar Energy image
            Haar::HaarEnergy(im, em, w, h, levels);

            esum = 0;

            for(i=0; i<w; i++)
                for(j=0; j<h; j++)
                {
                    if(em.ptr<double>(j)[i] > bm.ptr<double>(j)[i])
                    {
                        iim.ptr(j)[i] = item;  //index
                        bm.ptr<double>(j)[i] = em.ptr<double>(j)[i]; // value
                    }

                    esum += em.ptr<double>(j)[i]/((double)(w*h));
                }

            totalEnergy.insert(item, esum);

            std::cout << "Image Energy " << item << " : " << totalEnergy[item] << std::endl;
        }

        //energyImages.push_back(bm);
    }

    // integer smooth iim
    //ImageProcessing::GaussianBlur(iim, m.cols, m.rows, 5);
    //ImageProcessing::modalFilter(iim, w, h, regionSize, imageIndexes.size());

    cv::Mat filteredImage = cv::Mat(h, w, CV_8UC1);

    OpenCVtrilateralFilter tlf;

    //tlf.trilateralFilter(iim, filteredImage, 1.0, 1.0);
    int kernel_length =10;

    cv::bilateralFilter(iim, filteredImage, kernel_length, kernel_length*2, kernel_length/2);

    // better a polynomial fit

    pMat = new Mat(h, w, CV_8UC3);
    cv::Mat pScale = Mat(h, w, CV_8UC1);

    if(false)
    {
        cv::normalize(filteredImage, pScale, 0, 255, NORM_MINMAX, CV_8UC1);

        cv::cvtColor(pScale, *pMat, COLOR_GRAY2RGB, 3);
    }
    else
    {
        cv::normalize(filteredImage, pScale, 0, imageStack.size()-1, NORM_MINMAX, CV_8UC1);
        pMat = FocusStack::mergeImageStack(imageStack, pScale, w, h);

    }
    // ImageProcessing::putMatScale(iim, *pMat);

    pMainWindow->addCVImage(*pMat, "focus image" );

    return pMat;
}

/**
*
*  Merges images based on indexing the vector using the values in indexImage
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   FocusStack::mergeImageStack
* Qualifier 
* @param     QVector<targeterImage> & imageStack 
* @param     Mat indexImage 
* @param     int w 
* @param     int h 
* @return    cv::Mat*
* Access     public 
*/
Mat* FocusStack::mergeImageStack(std::vector<targeterImage>& imageStack, Mat indexImage, int w, int h)
{
    fname();

    int i, j, s = imageStack.size();
    cv::Mat *pIm, *pMat = new Mat(h, w, CV_8UC3);

    for(i=0; i<w; i++)
        for(j=0; j<h; j++)
        {
            char val = indexImage.ptr<char>(j)[i];

            if(val>=0 && val<s)
            {
                pIm = &imageStack[val].getImage();

                pMat->ptr<Vec3b>(j)[i] = pIm->ptr<Vec3b>(j)[i];
            }
            else
            {
                pMat->ptr<Vec3b>(j)[i] = cv::Vec3b(0,0,255);
            }
        }

    return pMat;
}


/**
*
*  Compares neighbouring pixels to determine best value for focusing
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   FocusStack::fillErrorRegions
* Qualifier 
* @param     int * im 
* @param     int w 
* @param     int h 
* @param     int fSize 
* @param     int NoFocusImages 
* @return    void
* Access     public 
*/
void FocusStack::fillErrorRegions(int* im, int w, int h, int fSize, int NoFocusImages)
{
    fname();

    int i, j, x, y, c, k, lev, bestLevel, startx, starty, endx, endy;
    int* valueArray = new int[NoFocusImages];
    int* bestLevels = new int[w*h];
    int fs1 = fSize>>1;

    memset(bestLevels, 0, sizeof(int)*w*h);

    for (i = 0; i < w; i++)
    {
        for (j = 0; j < h; j++)
        {
            if(im[i+j*w]<0)
            {
                memset(valueArray, 0, sizeof(int)*NoFocusImages);

                startx = i-fs1;
                endx = i+fs1;
                starty = j-fs1;
                endy = j+fs1;

                // fs1 area
                for(x=startx; x<endx; x++)
                    for(y=starty; y<endy; y++)
                    {
                        if(x>=0 && y>=0 && x<w && y<h)
                        {
                            if(im[x + y*w] < NoFocusImages && im[x + y*w] >=0 )
                                valueArray[im[x + y*w]]++;     // SXDY
                        }
                    }

                // get maximum value in values
                for (k = 0, bestLevel = 0; k < NoFocusImages; k++)
                {
                    c = valueArray[k];

                    if(c > bestLevel)
                    {
                        bestLevel = c;
                        lev = k;
                    }
                }

                bestLevels[i+j*w] = lev;
            }
            else
            {
                bestLevels[i+j*w] = im[i+j*w];
            }
        }
    }

    memcpy(im, bestLevels, sizeof(int)*w*h);

    delete [] bestLevels;
    delete [] valueArray;

}

/**
*
*  Compares neighbouring pixels to determine best value for focusing (alternative implementation)
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   FocusStack::fillErrorRegions
* Qualifier 
* @param     Mat & im 
* @param     int w 
* @param     int h 
* @param     int fSize 
* @param     int NoFocusImages 
* @return    void
* Access     public 
*/
void FocusStack::fillErrorRegions(Mat& im, int w, int h, int fSize, int NoFocusImages)
{
    fname();

    int i, j, x, y, c, k, lev, bestLevel, startx, starty, endx, endy;
    int* valueArray = new int[NoFocusImages];
    int fs1 = fSize>>1;

    Mat bestLevels = cv::Mat(h, w, CV_8UC1, cv::Scalar(0));

    for (i = 0; i < w; i++)
    {
        for (j = 0; j < h; j++)
        {
            if(im.ptr(j)[i]>0)
            {
                memset(valueArray, 0, sizeof(int)*NoFocusImages);

                startx = i-fs1;
                endx = i+fs1;
                starty = j-fs1;
                endy = j+fs1;

                // fs1 area
                for(x=startx; x<endx; x++)
                    for(y=starty; y<endy; y++)
                    {
                        if(x>=0 && y>=0 && x<w && y<h)
                        {
                            if(im.ptr<char>(y)[x] < NoFocusImages && im.ptr<char>(y)[x] >=0 )
                                valueArray[im.ptr<char>(y)[x]]++;     // SXDY
                        }
                    }

                // get maximum value in values
                for (k = 0, bestLevel = 0; k < NoFocusImages; k++)
                {
                    c = valueArray[k];

                    if(c > bestLevel)
                    {
                        bestLevel = c;
                        lev = k;
                    }
                }


                bestLevels.ptr(j)[i] = lev;
            }
            else
            {
                bestLevels.ptr(j)[i] = im.ptr<char>(j)[i];
            }
        }
    }

    bestLevels.copyTo(im);
    delete [] valueArray;
}

    
/**
*
*  OpenCV port of 'LAPM' algorithm (Nayar89)
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   FocusStack::modifiedLaplacian
* Qualifier 
* @param     const cv::Mat & src 
* @return    double
* Access     public 
*/
double FocusStack::modifiedLaplacian(const cv::Mat& src)
{
    fname();

    cv::Mat M = (Mat_<double>(3, 1) << -1, 2, -1);
    cv::Mat G = cv::getGaussianKernel(3, -1, CV_64F);

    cv::Mat Lx;
    cv::sepFilter2D(src, Lx, CV_64F, M, G);

    cv::Mat Ly;
    cv::sepFilter2D(src, Ly, CV_64F, G, M);

    cv::Mat FM = cv::abs(Lx) + cv::abs(Ly);

    double focusMeasure = cv::mean(FM).val[0];
    return focusMeasure;
}

 
/**
*
*  OpenCV port of 'LAPV' algorithm (Pech2000)
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   FocusStack::varianceOfLaplacian
* Qualifier 
* @param     const cv::Mat & src 
* @return    double
* Access     public 
*/
double FocusStack::varianceOfLaplacian(const cv::Mat& src)
{
    fname();

    cv::Mat lap;
    cv::Laplacian(src, lap, CV_64F);

    cv::Scalar mu, sigma;
    cv::meanStdDev(lap, mu, sigma);

    double focusMeasure = sigma.val[0]*sigma.val[0];
    return focusMeasure;
}

/**
*
* OpenCV port of 'TENG' algorithm (Krotkov86)
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   FocusStack::tenengrad
* Qualifier 
* @param     const cv::Mat & src 
* @param     int ksize 
* @return    double
* Access     public 
*/
double FocusStack::tenengrad(const cv::Mat& src, int ksize)
{
    fname();

    cv::Mat Gx, Gy;
    cv::Sobel(src, Gx, CV_64F, 1, 0, ksize);
    cv::Sobel(src, Gy, CV_64F, 0, 1, ksize);

    cv::Mat FM = Gx.mul(Gx) + Gy.mul(Gy);

    double focusMeasure = cv::mean(FM).val[0];
    return focusMeasure;
}

/**
*
*  OpenCV port of 'GLVN' algorithm (Santos97)
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   FocusStack::normalizedGraylevelVariance
* Qualifier 
* @param     const cv::Mat & src 
* @return    double
* Access     public 
*/
double FocusStack::normalizedGraylevelVariance(const cv::Mat& src)
{
    fname();

    cv::Scalar mu, sigma;
    cv::meanStdDev(src, mu, sigma);

    double focusMeasure = (sigma.val[0]*sigma.val[0]) / mu.val[0];
    return focusMeasure;
}

/**
*
*  Simple Haar detail image energy
*
* @author    David Watts
* @since     2017/03/07
*
* FullName   FocusStack::normalizedGraylevelVariance
* Qualifier
* @param     const cv::Mat & src
* @return    double
* Access     public
*/

double FocusStack::simpleDerivativeEnergy(const cv::Mat& data, bool horizontal)
{
	fname();

	bool zeroSmooth = false;
	double focusMeasure = 0;
	int val2, val1;

	if (data.channels() != 1)
	{
		int width = data.cols;
		int height = data.rows;

		double* row;
		double* col;

		if (horizontal)
		{
			for (int i = 0; i < width - 1; i++)
			{
				for (int j = 0; j < height; j++)
				{
					if (data.channels() == 1)
					{
						val1 = (int)data.at<Vec3b>(j, i)[0];
						val2 = (int)data.at<Vec3b>(j, i + 1)[0];
					}
					else
					{
						val1 = (int)data.at<Vec3b>(j, i)[0] * 0.114 + data.at<Vec3b>(j, i)[1] * 0.587 + data.at<Vec3b>(j, i)[2] * 0.299;
						val2 = (int)data.at<Vec3b>(j, i+1)[0] * 0.114 + data.at<Vec3b>(j, i+1)[1] * 0.587 + data.at<Vec3b>(j, i+1)[2] * 0.299;
					}
					
					double diff = (double)(val2 - val1);
					focusMeasure += (diff*diff);
				}
			}

		}
		else
		{
			for (int j = 0; j < height - 1; j++)
			{
				for (int i = 0; i < width; i++)
				{

					if(data.channels() == 1)
					{
						val1 = (int)data.at<Vec3b>(j, i)[0];
						val2 = (int)data.at<Vec3b>(j + 1, i)[0];
					}
					else
					{
						val1 = (int)data.at<Vec3b>(j, i)[0] * 0.114 + data.at<Vec3b>(j, i)[1] * 0.587 + data.at<Vec3b>(j, i)[2] * 0.299;
						val2 = (int)data.at<Vec3b>(j + 1, i)[0] * 0.114 + data.at<Vec3b>(j + 1, i)[1] * 0.587 + data.at<Vec3b>(j + 1, i)[2] * 0.299;
					}
					
					double diff = (double)(val2 - val1);
					focusMeasure += (diff*diff);
				}
			}

		}

		return focusMeasure/((double)(width*height));	// scale to image size
	}
	else
		return -1;


}
