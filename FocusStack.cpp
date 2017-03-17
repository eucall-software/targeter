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

using namespace cv;



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

                esum += em.ptr<double>(j)[i]/((double)(w*h));
            }

        s = "laplace combined level image " + QString::number(item);

       // pMainWindow->addCVImage(HelperFunctions::putMatScale(iim, true), s);

        totalEnergy.insert(item, esum);

        std::cout << "Image Energy " << item << " : " << totalEnergy[item] << std::endl;
    }

       // pMainWindow->addCVImage(HelperFunctions::putMatScale(iim), "laplace best level image" );

    //energyImages.push_back(bm);

    // integer smooth iim
    //ImageProcessing::GaussianBlur(iim, m.cols, m.rows, 5);
    ImageProcessing::modalFilter(iim, w, h, regionSize, imageIndexes.size());

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

    if(false)
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
                pIm = &imageStack[val-1].getImage();

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
            if(im.ptr(y)[x]<0)
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


