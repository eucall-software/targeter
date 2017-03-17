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

using namespace cv;
typedef std::numeric_limits< double > dbl;
using namespace std;



namespace FindTargets {
	
    template<typename T>
    void printVector(const T& t) {
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
    * FullName   FindTargets::printClusterVector
    * Qualifier 
    * @param     std::vector<T> cluster 
    * @return    void
    * Access     public 
    */
    template<typename T>  void printClusterVector(std::vector<T> cluster)
    {
        std::vector<T>::iterator iI;

        int i=0;
        for (iI = cluster.begin(); iI != cluster.end(); iI++)
        {
            i++;
            std::string s= "cluster";
            (*iI).printMe(s+std::to_string(i));
        }
    }


    /**
    *
    *  Prints to screen values of Coocurance matrix
    *
    * @author    David Watts
    * @since     2017/03/07
    * 
    * FullName   FindTargets::printCoocuranceHistogram
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
    void printCoocuranceHistogram(T* hist, int dim1, int dim2, int dim3, int nDim3=1)
    {
        int i, j, k, ind;

        if(dim3<=0)
        {
            for(i=0;i<dim2;i++)
            {
                for(j=0;j<dim1;j++)
                    DBOUT( hist[i + j*dim1] << " ");
            }
			DBOUT(std::endl);
        }
        else
        {
            for(k=0;k<dim3; k++)
            {
                DBOUT("d=" << k <<endl);

                for(j=0;j<dim2;j++)
                {
                    for(i=0;i<dim1;i++)
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
    *  Detects target image (trainingImage) in detectionImage using colour coocurrance matrix matching method
    *
    * @author    David Watts
    * @since     2017/03/07
    * 
    * FullName   FindTargets::ColourOccuranceHistogram
    * Qualifier 
    * @param     std::vector<targeterImage> & trainingImages 
    * @param     targeterImage & detectionImage 
    * @param     int distance 
    * @param     int NoClusters 
    * @param     MainWindow * pMainWindow 
    * @return    void
    * Access     public 
    */
    cv::Mat ColourOccuranceHistogram(std::vector<targeterImage>& trainingImages, targeterImage& detectionImage, int distance, int NoClusters, MainWindow* pMainWindow)
    {
#ifdef DEBUGPRINT
    DBOUT("Function Name: " << Q_FUNC_INFO << std::endl);
#endif
		// clusters test and training images for RGB values
		FindTargets::hueHistogramClustering(detectionImage, trainingImages, NoClusters, pMainWindow);

		int w = trainingImages[0].getImage().cols;
		int h = trainingImages[0].getImage().rows;

		// there's no point having a coocurrance size bigger than the target window size
		for (int i = 0; i < trainingImages.size(); i++)
			distance = min(distance, max(trainingImages[0].getImageCols(), trainingImages[0].getImageRows()));

		// allocate matrix
        double* coMatrixTrain =new double[NoClusters*NoClusters*distance];

        for(int i=0;i<NoClusters*NoClusters*distance;i++)
            coMatrixTrain[i] = 0.0;

         for(int i=0;i<trainingImages.size();i++)
         {
            // generate coocurrance matrices from training images
            FindTargets::getCoocuranceHistogram(trainingImages[i], coMatrixTrain, NoClusters, distance);
        }

       //int* testing = FindTargets::kMeansRGB(detectionImage, NoClusters, 1000);


        // scan test image calculate intersection value save value to image
       double* result = FindTargets::findTargets(detectionImage, coMatrixTrain, NoClusters, distance);

	   return HelperFunctions::putImageScale<double>(result, detectionImage.getImageCols(), detectionImage.getImageRows());

       // threshold values greater than threshold mask test image with crosshair centered on this image

        delete [] result;
        delete [] coMatrixTrain;
    }

	/**
	*
	*  Finds template image (trainingImages) in detectionImage using OpenCV matchTemplate method
	*
	* @author    David Watts
	* @since     2017/03/07
	* 
	* FullName   FindTargets::CVMatching
	* Qualifier 
	* @param     std::vector<targeterImage> & trainingImages 
	* @param     targeterImage & detectionImage 
	* @param     algoType matchType 
	* @param     MainWindow * pMainWindow 
	* @return    void
	* Access     public 
	*/
	cv::Mat CVMatching(std::vector<targeterImage>& trainingImages, targeterImage& detectionImage, algoType::algoType matchType)
	{
#ifdef DEBUGPRINT
		DBOUT("Function Name: " << Q_FUNC_INFO << std::endl);
#endif
		bool bExpandImageBoundaries = false;

		/// Create the result matrix
		cv::Mat result(detectionImage.getImageSize(), CV_32FC1);

		int w = trainingImages[0].getImageCols();
		int h = trainingImages[0].getImageRows();

		cv::Size dstSize;
		cv::Mat dst;

		if (bExpandImageBoundaries)
		{
			detectionImage.getImageSize() + trainingImages[0].getImageSize() - cv::Size(1, 1);
			dst = cv::Mat(dstSize, detectionImage.getImageType(), cv::Scalar(0, 0, 0));

			detectionImage.getImage().copyTo(dst(cv::Rect(w>>1, h>>1, detectionImage.getImageCols(), detectionImage.getImageRows())));
		}
		else
		{
			dstSize = detectionImage.getImageSize();
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
			out = cv::Mat(detectionImage.getImageSize(), CV_8UC1, cv::Scalar(0, 0, 0));

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
	* FullName   FindTargets::histClusterEqual
	* Qualifier 
	* @param     cv::Mat hueHist 
	* @param     int histSize 
	* @param     int NoClusters 
	* @return    int*
	* Access     public 
	*/
	int* histClusterEqual(cv::Mat hueHist, int histSize, int NoClusters)
	{
		int sum, i, j;
		int* pClusterHist = new int[histSize];
		float Sum = 0;

		for(i = 0; i<histSize; i++)
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
    *  Uses histogram cluster merging method to posterise image into NoCluster number of levels
    *
    * @author    David Watts
    * @since     2017/03/07
    * 
    * FullName   FindTargets::hueHistogramClustering
    * Qualifier 
    * @param     targeterImage & detectionImage 
    * @param     std::vector<targeterImage> & TrainImages 
    * @param     int NoClusters 
    * @param     MainWindow * pMainWindow 
    * @return    void
    * Access     public 
    */
    void hueHistogramClustering(targeterImage& detectionImage, std::vector<targeterImage>& TrainImages, int NoClusters, MainWindow* pMainWindow)
    {
        int i=0;
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

		int w, h, w1 = detectionImage.getImageCols(), h1= detectionImage.getImageRows();

		cv::Mat image1_gray;

		bool bGrayImage = HelperFunctions::isGrayImage(detectionImage.getImage());

		if (bGrayImage)	// grayscale
		{
			DBOUT("greyscale image"<<std::endl);

			// get histogram of hue 0-360
			histSize = 256;

			range[1] = (float)histSize;

			histRange = { range };

			cv::cvtColor(detectionImage.getImage(), image1_gray, CV_BGR2GRAY);

			histImage = &image1_gray;
		}
		else
		{
			DBOUT("colour image" << std::endl);

			// get float image for 360 degrees
			detectionImage.getImage().convertTo(dst, CV_32F);

			cv::cvtColor(dst, hsvImage, CV_BGR2HSV);

			// get histogram of hue 0-360
			histSize = 360;

			range[1] = (float)histSize;

			histRange = { range };

			split(hsvImage, hsv_planes);

			histImage = &hsv_planes[0];	
		}

		b_hist.create(histSize, 1, CV_32SC1);

		// Compute the histogram:
		calcHist(histImage, 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);

        // here we cluster image based on its hue histogram /////////////////

        pClusterHist = ImageProcessing::histClusterRGBImage(b_hist, histSize, NoClusters);

        // //////////////////////////////////////////////////////////////////

        // assign clusters to test image
		int* pImage = new int[h1*w1];

		if (bGrayImage)
		{
			// label image with cluster
			for (i = 0; i < w1; i++)
				for (int j = 0; j < h1; j++)
					pImage[i + j*w1] = pClusterHist[cvFloor(histImage->at<uchar>(j, i))];
		}
		else
		{
			// label image with cluster
			for (i = 0; i < w1; i++)
				for (int j = 0; j < h1; j++)
					pImage[i + j*w1] = pClusterHist[cvFloor(histImage->at<float>(j, i))];
		}

		detectionImage.set1DImage(pImage);

        // assign clusters to training images
		for(int k=0; k<TrainImages.size(); k++)
        {
			w = TrainImages[k].getImageCols(), h = TrainImages[k].getImageRows();

			pImage = new int[w*h];

			if(HelperFunctions::isGrayImage(TrainImages[k].getImage()))	// grayscale
			{
				cv::cvtColor(TrainImages[k].getImage(), image1_gray, cv::COLOR_BGR2GRAY);

				histImage = &image1_gray;

				// label image with cluster
				for (i = 0; i<w; i++)
					for (int j = 0; j<h; j++)
						pImage[i + j*w] = pClusterHist[cvFloor(histImage->at<uchar>(j, i))];
			}
			else
			{
				// get float image for 360 degrees
				TrainImages[k].getImage().convertTo(dst, CV_32F);

				cvtColor(dst, hsvImage, CV_BGR2HSV);

				split(hsvImage, hsv_planes);

				histImage = &hsv_planes[0];

				// label image with cluster
				for (i = 0; i<w; i++)
					for (int j = 0; j < h; j++)
					{
						pImage[i + j*w] = pClusterHist[cvFloor(histImage->at<float>(j, i))];
					}
			}

			TrainImages[k].set1DImage(pImage);
        }

        delete [] pClusterHist;
    }


	/**
	*
	*  Gets coocurrance matrix for image region
	*
	* @author    David Watts
	* @since     2017/03/07
	* 
	* FullName   FindTargets::getCoocMatrix
	* Qualifier 
	* @param     targeterImage & m 
	* @param     int * pMask 
	* @param     int startX 
	* @param     int startY 
	* @param     int regionWidth 
	* @param     int regionHeight 
	* @param     double * coMatrixF 
	* @param     int NoClusters 
	* @param     int maxD 
	* @return    double
	* Access     public 
	*/
	double getCoocMatrix(targeterImage& m, int* pMask, drawingMode::drawingMode maskType, int startX, int startY, int regionWidth, int regionHeight, double* coMatrixF, int NoClusters, int maxD)
	{
		int i, j, c1, c2, x, y, ind;
		double sum = 0;

		int w = m.getImageCols(), h = m.getImageRows();
		int* pImage = m.get1DImage(imageType::display);

		bool bHasMask = (pMask != NULL && (maskType == drawingMode::circle || maskType == drawingMode::poly));

		for (j = 0; j<regionHeight; j++)
			for (i = 0; i<regionWidth; i++)
			{
				// what to do about masked pixels
				
				if ((startX + i) < w && (startY + j) < h)	// check within image bounds
				{
					if (!bHasMask || pMask[(startX + i) + (startY + j)*w] > 0)
					{
						c1 = pImage[(startX + i) + (startY + j)*w];

						// check against all others
						for (y = 0; y < regionHeight; y++)
							for (x = 0; x < regionWidth; x++)
							{
								if (i+j*w >= x+y*w)	// should  not compare backwards direction or to itself
									continue;

								if ((startX + x) < w && (startY + y) < h)// check within image bounds
								{
									if (!bHasMask || pMask[(startX + x) + (startY + y)*w] > 0)
									{
										c2 = pImage[(startX + x) + (startY + y)*w];

										int d = max(x-i, y-j);	// maximum distance

										if (c1 < NoClusters && c2 < NoClusters && d < maxD)
										{
											ind = c1 + c2*NoClusters + d*NoClusters*NoClusters; //c1 + NoClusters * (c2 + NoClusters * d); //i + height* (j + width* k)

											coMatrixF[ind] += 1.0;

											sum += 1.0;
										}
										else
											DBOUT("error index out of bounds " << Q_FUNC_INFO << c1 << " vs. " << w << "," << c2 << " vs. " << h << "," << d << " vs. " << maxD << std::endl);
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
	* FullName   FindTargets::getCoocuranceHistogram
	* Qualifier 
	* @param     targeterImage & m 
	* @param     double * coMatrixF 
	* @param     int NoClusters 
	* @param     int maxD 
	* @return    void
	* Access     public 
	*/
	void getCoocuranceHistogram(targeterImage& m, double* coMatrixF, int NoClusters, int maxD)
	{
#ifdef DEBUGPRINT
		DBOUT("Function Name: " << Q_FUNC_INFO);
#endif
		int i, x, y, stepX=1, stepY=1;
		double sum = 0;
		int w = m.getImageCols(), h = m.getImageRows();
		
		stepX = maxD>>1;	// so overlapping regions
		stepY = maxD>>1;

		// ind = x + width * (y + height * z)

		int* mask = m.get1DImage(imageType::mask);

		for (y = 0; y < h; y += stepY)
			for (x = 0; x < w; x += stepX)
			{
				sum += getCoocMatrix(m, mask, m.getMaskType(), x, y, maxD, maxD, coMatrixF, NoClusters, maxD);
			}

        // normalise histogram
        for(i=0; i<NoClusters*NoClusters*maxD; i++)
            coMatrixF[i] /= sum;

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
    * FullName   FindTargets::findTargets
    * Qualifier 
    * @param     targeterImage & detectionImage 
    * @param     double * coMatrixTestF 
    * @param     int NoClusters 
    * @param     int maxD 
    * @return    double*
    * Access     public 
    */
    double* findTargets(targeterImage& detectionImage, double* coMatrixTestF, int NoClusters, int maxD)
    {

#ifdef DEBUGPRINT
    DBOUT("Function Name: " << Q_FUNC_INFO << std::endl);
#endif
        int i, j, x, y, k;
        bool bFound = false;
        double sum=0, score=0;
        int increment = maxD>>1;
		int w = detectionImage.getImageCols(), h = detectionImage.getImageRows();

        double* coMatrixF =new double[NoClusters*NoClusters*maxD];

        double* scoreImage = new double[w*h];

		for (i = 0; i < w*h; i++)
			scoreImage[i] = 0;

        for( y = 0; y < h; y += increment)
            for( x = 0; x < w; x += increment)
            {
                // zero coocurrance martix
                for(i=0, sum=0;i<NoClusters*NoClusters*maxD;i++)
                    coMatrixF[i] = 0.0;

                //memset(coMatrixF, 0.0, NoClusters*NoClusters*maxD*sizeof(double));
				sum = getCoocMatrix(detectionImage, NULL, drawingMode::rect, x, y, maxD, maxD, coMatrixF, NoClusters, maxD);

                // compare cooccurance matrix to that of test
				// display cooc matrix as image

				//DBOUT("sum=" << sum << std::endl);

                if(sum >0)
                {
                    // get score
					for (i = 0, score = 0.0; i < NoClusters*NoClusters*maxD; i++)
						score += fmin(coMatrixF[i] / sum, coMatrixTestF[i]);//fabs(coMatrixF[i]- coMatrixTestF[i]);//
					
					//DBOUT("score=" << score << std::endl);

					//DBOUT("testing image co-occurrance histogram" << std::endl);
					//printCoocuranceHistogram<double>(coMatrixF, NoClusters, NoClusters, maxD);
					//scoreImage[x + y*w] = score;

					
                    //DBOUT(score << " ");
					if (score > 0)
					{
						for (j = y; j < y + increment; j++)
							for (i = x; i < x + increment; i++)
							{
								if (j < h && i < w)
									scoreImage[i + j*w] = score;
							}
					}
					
                }
				
				//DBOUT(score << ", ");
            }

		//DBOUT(std::endl);

        return scoreImage;
    }

    /**
    *
    *  Posterities image into NoCluster levels by performing K means clustering of intensity values
    *
    * @author    David Watts
    * @since     2017/03/07
    * 
    * FullName   FindTargets::kMeansRGB
    * Qualifier 
    * @param     cv::Mat img 
    * @param     std::vector<cv::Mat> testImgs 
    * @param     int NoClusters 
    * @param     int maxIterations 
    * @return    std::vector<int*>
    * Access     public 
    */
    std::vector<int*> kMeansRGB(cv::Mat img, std::vector<cv::Mat> testImgs, int NoClusters, int maxIterations)
    {
#ifdef DEBUGPRINT
    DBOUT("Function Name: " << Q_FUNC_INFO << std::endl);
#endif
        int ind, ind2;

        std::vector<int*> retImages;

        cv::Mat m = img.clone().reshape(1, img.rows * img.cols);

        for(int i=0;i<testImgs.size();i++)
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
                   TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, maxIterations, 0.0001),
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

        for( int y = 0; y < img.rows; y++ )
            for( int x = 0; x < img.cols; x++ )
            {
                ind = x+y*img.cols;
                clusters[ind] = bestLabels.at<int>(ind, 0);
            }

        retImages.push_back(clusters);

        for(int i=0;i<testImgs.size();i++)
        {
            int* pImage = new int[testImgs[i].rows*testImgs[i].cols];

            for( int y = 0; y < testImgs[i].rows; y++ )
                for( int x = 0; x < testImgs[i].cols; x++ )
                {
                    ind2 =  x+y*testImgs[i].cols;

                    Vec3b c = testImgs[i].at<Vec3b>(y, x);

                    if(c[0] >10 && c[1] >10 && c[2]>10 )
                        pImage[ind2] = bestLabels.at<int>(ind+ind2, 0);
                    else
                        pImage[ind2] = 0;

                }
            ind += ind2;

            retImages.push_back(pImage);
        }

        return retImages;
    }
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