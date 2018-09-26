// Targeter - target identification software for EUCALL workpackage 6
// Licensed under the GPL License. See LICENSE file in the project root for full license information.
// Copyright(C) 2017  David Watts 

#ifndef HAAR_H
#define HAAR_H

#include "FocusStack.h"
#include <cmath>
#include <QObject>

#include "opencv2/opencv.hpp"
#include "opencv/highgui.h"

#define fname() (std:: cout << " " << __FUNCTION__ );

#define W0 0.5
#define W1 -0.5
#define S0 0.5
#define S1 0.5

class Haar {
public:
	static void HaarEnergy(cv::Mat data, cv::Mat &energyImage, int width, int height, int iterations, bool laplace = false, bool bSquare = true);
	static cv::Mat PyramidLevels(cv::Mat data, int width, int height, int iterations, const int NoFocusImages);
	static cv::Mat LaplacianPyramid(cv::Mat im, int levels, bool includeScale = true);
	static void Haar2(cv::Mat& data, int iterations);
	static float** getHaarCooc(cv::Mat data, cv::Mat coocImage, int width, int height, int iterations, float maxEnergy);

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
	static T* PyramidLevels(T* data, int width, int height, int iterations, int NoFocusImages)
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
	static T* PyramidRegionLevels(T* data, int width, int height, int iterations, int NoFocusImages)
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
	static void Haar1(T* data, int n)
    {
        T* temp = new T[n];

        int h = n >> 1;
        for (int i = 0; i < h; i++)
        {
            int k = (i << 1);
            temp[i] = data[k] * S0 + data[k + 1] * S1;
            temp[i + h] = data[k] * W0 + data[k + 1] * W1;
        }

        for (int i = 0; i < n; i++)
            data[i] = temp[i];

        delete [] temp;
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
	static void Haar2(T* data, int width, int height, int iterations, bool AbsImage = false)
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
	static void iHaar2(T* data, int width, int height, int iterations)
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
	static void iHaar1(T* data, int n)
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
    static void iHaar2(cv::Mat& data, int iterations)
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

};

#endif // HAAR_HPP



