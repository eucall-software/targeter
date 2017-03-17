#ifndef HAAR_HPP
#define HAAR_HPP

#include "FocusStack.h"
#include <cmath>
#include <QObject>

#include "opencv2/opencv.hpp"
#include "opencv/highgui.h"

#define fname() (std:: cout << " " << __FUNCTION__ );

class Haar {

    const double w0 = 0.5;
    const double w1 = -0.5;
    const double s0 = 0.5;
    const double s1 = 0.5;

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
    void Haar::HaarEnergy(cv::Mat data, cv::Mat &energyImage, int width, int height, int iterations, bool laplace=false, bool bSquare = true)
    {
        fname();

        int ii, ij, oi, oj;

        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                 for (int k = 0; k < iterations; k++)
                 {
                    ii = i >> (k+1);
                    ij = j >> (k+1);

                    oi = width >> (k+1);
                    oj = height >> (k+1);

                    if(bSquare)
                        energyImage.ptr<double>(j)[i] += ( (double)data.ptr<double>(oj+ij)[oi+ii]*data.ptr<double>(oj+ij)[oi+ii])/(double)(1<<k); // DXDY
                    else
                        energyImage.ptr<double>(j)[i] += fabs( (double)data.ptr<double>(oj+ij)[oi+ii] / (double)(1<<k) ); // DXDY

                    if(!laplace)
                    {
                        if(bSquare)
                            energyImage.ptr<double>(j)[i] += ((double)data.ptr<double>(oj+ij)[ii]*data.ptr<double>(oj+ij)[ii])/(double)(1<<k);    // SXDY
                        else
                            energyImage.ptr<double>(j)[i] += fabs( (double)data.ptr<double>(oj+ij)[ii]    / (double)(1<<k));    // SXDY
                        if(bSquare)
                            energyImage.ptr<double>(j)[i] += ((double)data.ptr<double>(ij)[oi+ii]*data.ptr<double>(ij)[oi+ii])/ (double)(1<<k);    // SYDX
                        else
                            energyImage.ptr<double>(j)[i] += fabs( (double)data.ptr<double>(ij)[oi+ii]    / (double)(1<<k) );    // SYDX
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
    cv::Mat Haar::LaplacianPyramid(cv::Mat im, int levels, bool includeScale = true)
    {
        int l;
        cv::Mat imOut = cv::Mat(im.rows*2, im.cols*2, im.type(), cv::Scalar(0));

        cv::Mat currentImg = im;

        for (l=0; l<levels; l++) {
            cv::Mat down,up;

            cv::pyrDown(currentImg, down);

            cv::pyrUp(down, up, currentImg.size());

            cv::Mat lap = currentImg - up;

            int y = imOut.rows>>(l+1);
            int x = imOut.cols>>(l+1);

            cv::Rect r =  cv::Rect(x, y, lap.cols, lap.rows);

            lap.copyTo(imOut(r));

            currentImg = down;
        }

        if(includeScale)
        {
            int y = imOut.rows>>(levels+1);
            int x = imOut.cols>>(levels+1);

            cv::Rect r =  cv::Rect(x, y, currentImg.cols, currentImg.rows);

            currentImg.copyTo(imOut(r) );
        }
        return imOut;
    }


    /**
    *
    * Get image of best (modal) values from Pyramid composition
    *
    * @author    David Watts
    * @since     2017/03/08
    * 
    * FullName   Haar::PyramidLevels
    * Qualifier 
    * @param     T * data 
    * @param     int width 
    * @param     int height 
    * @param     int iterations 
    * @param     int NoFocusImages 
    * @return    T*
    * Access     private 
    */
    template< class T >
    T* Haar::PyramidLevels(T* data, int width, int height, int iterations, int NoFocusImages)
    {
        fname();

        int ii, ij, oi, oj, c, x, y, lev;

        int* valueArray = new int[NoFocusImages];

        T* bestlevels = new T[width*height];

        memset(bestlevels, 0, sizeof(T)*width*height);

        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                 memset(valueArray, 0, sizeof(int)*NoFocusImages);

                 for (int k = 0; k < iterations; k++)
                 {
                    ii = i >> (k+1);
                    ij = j >> (k+1);

                    oi = width >> (k+1);
                    oj = height >> (k+1);

                    if(data[(oi+ii) + (oj+ij)*width]>=0)
                        valueArray[data[(oi+ii) + (oj+ij)*width]]++; // DXDY

                    if(data[(ii) + (oj+ij)*width]>=0)
                        valueArray[data[(ii) + (oj+ij)*width]]++;    // SXDY
                    if(data[(oi+ii) + (ij)*width]>=0)
                        valueArray[data[(oi+ii) + (ij)*width]]++;    // SYDX
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
                    bestlevels[i+j*width] = lev;
                 else
                    bestlevels[i+j*width] = -1;
            }
        }
        delete [] valueArray;
        return bestlevels;
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
        fname();

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
                    ii = i >> (k+1);
                    ij = j >> (k+1);

                    oi = width >> (k+1);
                    oj = height >> (k+1);

                    if( data.ptr<char>(oj+ij)[oi+ii] >= 0 && data.ptr<char>(oj+ij)[oi+ii] < NoFocusImages )
                        valueArray[data.ptr<char>(oj+ij)[oi+ii]]++; // DXDY

                    if( data.ptr<char>(oj+ij)[ii] >= 0 && data.ptr<char>(oj+ij)[ii] < NoFocusImages )
                        valueArray[data.ptr<char>(oj+ij)[ii]]++;    // SXDY

                    if( data.ptr<char>(ij)[oi+ii] >= 0 && data.ptr<char>(ij)[oi+ii] < NoFocusImages )
                        valueArray[data.ptr<char>(ij)[oi+ii]]++;    // SYDX

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

        delete [] valueArray;

        return bestlevels;
    }

    /**
    *
    * Get image of best (modal) values from local 8 connected neighbours of Pyramid composition
    *
    * @author    David Watts
    * @since     2017/03/08
    * 
    * FullName   Haar::PyramidRegionLevels
    * Qualifier 
    * @param     T * data 
    * @param     int width 
    * @param     int height 
    * @param     int iterations 
    * @param     int NoFocusImages 
    * @return    T*
    * Access     private 
    */
    template< class T >
    T* Haar::PyramidRegionLevels(T* data, int width, int height, int iterations, int NoFocusImages)
    {
        fname();

        int ii, ij, oi, oj, indi, indj, c, x, y, lev, fs1=1, startx, starty, endx, endy;

        int* valueArray = new int[NoFocusImages];

        T* bestlevels = new T[width*height];

        memset(bestlevels, 0, sizeof(T)*width*height);

        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                 memset(valueArray, 0, sizeof(int)*NoFocusImages);

                 for (int k = 0; k < iterations; k++)
                 {
                    ii = i >> (k+1);
                    ij = j >> (k+1);

                    oi = width >> (k+1);
                    oj = height >> (k+1);

                    // neighbours for first level only
                    if(k==0)
                    {
                        // bottom left SYDX
                        indi   = ii;           indj   = oj + ij;
                        startx = indi - fs1;   starty = indj - fs1;
                        endx   = indi + fs1;   endy   = indj+fs1;

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
                                    if(data[x + y*width]>=0)
                                        valueArray[data[x + y*width]]++;
                                }
                            }

                        // top right SXDY
                        indi   = oi + ii;      indj   = ij;
                        startx = indi - fs1;   starty = indj - fs1;
                        endx   = indi + fs1;   endy   = indj + fs1;

                        // fs1 area
                        for(x=startx; x<endx; x++)
                            for(y=starty; y<endy; y++)
                            {
                                if(x>=oi && y>=0 && x<oi+oi && y<oj)
                                {
                                    // surround
                                    if(data[x + y*width]>=0)
                                        valueArray[data[x + y*width]]++;
                                }
                            }

                        // bottom right DXDY
                        indi   = oi + ii;      indj   = oj + ij;
                        startx = indi - fs1;   starty = indj - fs1;
                        endx   = indi + fs1;   endy   = indj + fs1;

                        // fs1 area
                        for(x=startx; x<endx; x++)
                            for(y=starty; y<endy; y++)
                            {
                                if(x>=oi && y>=oj && x<oi+oi && y<oj+oj)
                                {
                                    // surround
                                    if(data[x + y*width]>=0)
                                        valueArray[data[x + y*width]]++;
                                }
                            }
                    }
                    else
                    {
                        if(data[(oi+ii) + (oj+ij)*width]>=0)
                            valueArray[data[(oi+ii) + (oj+ij)*width]]++; // DXDY
                        if(data[(ii) + (oj+ij)*width]>=0)
                            valueArray[data[(ii) + (oj+ij)*width]]++;    // SXDY
                        if(data[(oi+ii) + (ij)*width]>=0)
                            valueArray[data[(oi+ii) + (ij)*width]]++;    // SYDX
                    }
                 }

                 // get maximum value in values
                 int bestLevel = 0;
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
                    bestlevels[i+j*width] = lev;
                 else
                    bestlevels[i+j*width] = -1;
            }
        }

        delete [] valueArray;

        return bestlevels;
    }


    /**
    *
    * Perform 1D Haar wavelet transform
    *
    * @author    David Watts
    * @since     2017/03/08
    * 
    * FullName   Haar::Haar1
    * Qualifier 
    * @param     T * data 
    * @param     int n 
    * @return    void
    * Access     private 
    */
    template< class T >
    void Haar::Haar1(T* data, int n)
    {
        T* temp = new T[n];

        int h = n >> 1;
        for (int i = 0; i < h; i++)
        {
            int k = (i << 1);
            temp[i] = data[k] * s0 + data[k + 1] * s1;
            temp[i + h] = data[k] * w0 + data[k + 1] * w1;
        }

        for (int i = 0; i < n; i++)
            data[i] = temp[i];

        delete [] temp;
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

         fname();

         if(data.channels() == 1)
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

                    Haar1(row, levWidth);

                   for (int i = 0; i < levWidth; i++)
                        data.ptr<double>(j)[i] = row[i];
                }

                col = new double[levHeight];

                for (int i = 0; i < levWidth; i++)
                {
                    for (int j = 0; j < levHeight; j++)
                        col[j] = (double)data.ptr<double>(j)[i];

                    Haar1(col, levHeight);

                    for (int j = 0; j < levHeight; j++)
                        data.ptr<double>(j)[i] = col[j];
                }

                delete [] row;
                delete [] col;
            }

            if(zeroSmooth)
            {
                int levHeight = height >> (iterations);
                int levWidth = width >> (iterations);

                 for (int j = 0; j < levHeight+3; j++)
                     for (int i = 0; i < levWidth+3; i++)
                         data.ptr<double>(j)[i] = 0;

            }
         }
         else
         {
             std:: cout << " " << __FUNCTION__ << ": error processing image with more than one channel" << std::endl;
         }
    }

    /**
    *
    * Perform 1D Haar wavelet transform on 1D image 
    *
    * @author    David Watts
    * @since     2017/03/08
    * 
    * FullName   Haar::Haar2
    * Qualifier 
    * @param     T * data 
    * @param     int width 
    * @param     int height 
    * @param     int iterations 
    * @param     bool AbsImage 
    * @return    void
    * Access     private 
    */
    template< class T >
    void Haar::Haar2(T* data, int width, int height, int iterations, bool AbsImage = false)
    {
        fname();

        T* row;
        T* col;

        for (int k = 0; k < iterations; k++)
        {
            int lev = 1 << k;

            int levWidth = width / lev;
            int levHeight = height / lev;

            row = new T[levWidth];
            for (int j = 0; j < levHeight; j++)
            {
                for (int i = 0; i < levWidth; i++)
                    row[i] = data[i+j*width];

                Haar1(row, levWidth);

                for (int i = 0; i < levWidth; i++)
                    data[i+j*width] = row[i];
            }

            col = new T[levHeight];
            for (int i = 0; i < levWidth; i++)
            {
                for (int j = 0; j < levHeight; j++)
                    col[j] = data[i+j*width];

                Haar1(col, levHeight);

                for (int j = 0; j < levHeight; j++)
                    data[i+j*width] = col[j];
            }

            delete [] row;
            delete [] col;
        }

        if(AbsImage)
        {
            for(int i=0; i<width*height; i++)
                data[i] = fabs(data[i]);
        }
    }

    /**
    *
    *  Perform inverse Haar wavelet transform on 2D image 
    *
    * @author    David Watts
    * @since     2017/03/08
    * 
    * FullName   Haar::iHaar2
    * Qualifier 
    * @param     T * data 
    * @param     int width 
    * @param     int height 
    * @param     int iterations 
    * @return    void
    * Access     private 
    */
    template< class T >
    void Haar::iHaar2(T* data, int width, int height, int iterations)
    {
         fname();

        T* col;
        T* row;

        for (int k = iterations - 1; k >= 0; k--)
        {
            int lev = 1 << k;

            int levWidth = width / lev;
            int levHeight = height / lev;

            col = new T[levHeight];
            for (int i = 0; i < levWidth; i++)
            {
                for (int j = 0; j < levHeight; j++)
                     col[j] = data[i+j*width];

                iHaar1(col, levHeight);

                for (int j = 0; j < levHeight; j++)
                     data[i+j*width] = col[j];
            }

            row = new T[levWidth];
            for (int j = 0; j < levHeight; j++)
            {
                for (int i = 0; i < levWidth; i++)
                    row[i] = data[i+j*width];

                iHaar1(row, levWidth);

                for (int i = 0; i < levWidth; i++)
                    data[i+j*width] = row[i];
            }
            delete [] row;
            delete [] col;
        }

    }


    /**
    *
    *  Perform inverse Haar wavelet transform on 1D image  
    *
    * @author    David Watts
    * @since     2017/03/08
    * 
    * FullName   Haar::iHaar1
    * Qualifier 
    * @param     T * data 
    * @param     int n 
    * @return    void
    * Access     private 
    */
    template< class T >
    void Haar::iHaar1(T* data, int n)
    {
        T* temp = new T[n];

        int h = n >> 1;
        for (int i = 0; i < h; i++)
        {
            int k = (i << 1);
            temp[k] = (data[i] * s0 + data[i + h] * w0) / w0;
            temp[k + 1] = (data[i] * s1 + data[i + h] * w1) / s0;
        }

        for (int i = 0; i < n; i++)
            data[i] = temp[i];

        delete [] temp;
    }

    /**
    *
    *   Perform inverse Haar wavelet transform on 2D OpenCV image 
    *
    * @author    David Watts
    * @since     2017/03/08
    * 
    * FullName   Haar::iHaar2
    * Qualifier 
    * @param     cv::Mat & data 
    * @param     int iterations 
    * @return    void
    * Access     private 
    */
    template< class T >
    void Haar::iHaar2(cv::Mat& data, int iterations)
    {
        fname();

        if(data.channels() == 1)
        {
            int rows = data.rows;
            int cols = data.cols;

            T* col;
            T* row;

            for (int k = iterations - 1; k >= 0; k--)
            {
                int lev = 1 << k;

                int levCols = cols / lev;
                int levRows = rows / lev;

                col = new T[levRows];
                for (int i = 0; i < levCols; i++)
                {
                    for (int j = 0; j < levRows; j++)
                        col[j] = (double)data.ptr<uchar>(j)[i];;

                    iHaar1(col, levRows);

                    for (int j = 0; j < levRows; j++)
                        (double)data.ptr<uchar>(j)[i] = col[j];
                }

                row = new T[levCols];
                for (int j = 0; j < levRows; j++)
                {
                    for (int i = 0; i < levCols; i++)
                        row[i] = (double)data.ptr<uchar>(j)[i];;

                    iHaar1(row, levCols);

                    for (int i = 0; i < levCols; i++)
                        (double)data.ptr<uchar>(j)[i] = row[i];
                }
                delete [] row;
                delete [] col;
            }
        }
        else
        {
            std:: cout << " " << __FUNCTION__ <<  ": error processing image with more than one channel" <<std::endl;
        }
    }

}

#endif // HAAR_HPP



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