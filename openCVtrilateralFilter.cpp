#include "openCVtrilateralFilter.h"
#include <math.h>
#include "opencv2/opencv.hpp"
#include "opencv/highgui.h"
#include <vector>
using std::vector;

bool OpenCVtrilateralFilter::trilateralFilter(
    cv::Mat& inputImg,
    cv::Mat& outputImg,
	const float sigmaC, 
	const float epsilon,
	const int filterType
	)
{

	// Check sizes
    if (inputImg.cols != outputImg.cols
        || inputImg.rows != outputImg.rows
        || inputImg.depth() != outputImg.depth()
        || inputImg.channels() != outputImg.channels()
        || inputImg.channels() != 1)
	{
        return false;
	}

    if (inputImg.depth() != IPL_DEPTH_32F)
        return false;

	// Adaptive Neighbourhood pixelwise image
    cv::Mat adaptiveNeighbourhood = cv::Mat(inputImg.rows, inputImg.cols, inputImg.type(),cv::Scalar(1));
	
	// x and y gradients
    cv::Mat xGradient = cv::Mat(inputImg.rows, inputImg.cols, inputImg.type(),cv::Scalar(1));
    cv::Mat yGradient = cv::Mat(inputImg.rows, inputImg.cols, inputImg.type(),cv::Scalar(1));

	// Smoothed x and y gradients
    cv::Mat xGradientSmooth = cv::Mat(inputImg.rows, inputImg.cols, inputImg.type(),cv::Scalar(1));
    cv::Mat yGradientSmooth = cv::Mat(inputImg.rows, inputImg.cols, inputImg.type(),cv::Scalar(1));
	
	// Gradient magnitude
    cv::Mat gradientMagnitude = cv::Mat(inputImg.rows, inputImg.cols, inputImg.type(),cv::Scalar(1));

	// domain variance for the two filters: sigmaC
	// range variance of the two filters: sigmaR
	// beta = emperical value
	float sigmaR; 
	const float beta = 0.15f; //Always set between 0.1 and 0.2

	//Computes X and Y gradients of the input image
	computeGradients(inputImg, xGradient, yGradient ); 

	// Computes the gradient magnitude
	computeMagnitude(xGradient, yGradient, gradientMagnitude);

	// Get min and max gradient for sigmaR
	double minGrad, maxGrad;
    minMaxLoc(gradientMagnitude, &minGrad, &maxGrad);
	sigmaR = beta * ( (float) maxGrad - (float) minGrad );

	// Level Max and Maximum LUT values
	int levelMax, maxLUT;

	// If using LUT
	if (filterType == TYPE_LUT)
	{
		// maximum level = log2(xsize) or log2(ysize)
        levelMax = log2( __min( inputImg.cols, inputImg.rows ) );
		maxLUT = pow( 2.f, levelMax-1) + 1;
	}
	else
	{
		// Using fast-trilateral
		// Find threshold for truncation
		maxLUT = int( sigmaC * sqrt( fabs( log(epsilon) ) ) ) + 1;
		// Calculate maximum level
		levelMax = log2(2 * maxLUT + 1, true);
	}

	// Calculate Adaptive Neighbourhood
	setAdaptiveNeighbourHood(gradientMagnitude, sigmaR, levelMax, adaptiveNeighbourhood);

	// Bilaterally filter the X and Y gradients of the input image
	// to produce xGradientSmooth and yGradientSmooth.

	if (filterType == TYPE_LUT)
		BilateralGradientFilterLUT(
			xGradient,yGradient, gradientMagnitude, sigmaC, sigmaR,
			xGradientSmooth, yGradientSmooth);
	else
		BilateralGradientFilter(
		xGradient, yGradient, gradientMagnitude, sigmaC, sigmaR, epsilon, 
		xGradientSmooth, yGradientSmooth );
	
	// Performs bilateral filter on the detail signal 

	if (filterType == TYPE_LUT)
		DetailBilateralFilterLUT(
			inputImg, adaptiveNeighbourhood, xGradientSmooth, yGradientSmooth, 
			sigmaC, sigmaR, maxLUT, outputImg);
	else
		DetailBilateralFilter(
			inputImg, adaptiveNeighbourhood, xGradientSmooth, yGradientSmooth, 
			sigmaC, sigmaR, maxLUT, epsilon, outputImg);

    return true;
}

// Computes X and Y gradients of the input image
void OpenCVtrilateralFilter::computeGradients(
    cv::Mat& inputImg, cv::Mat& xGradient, cv::Mat& yGradient )
{

	// Set up convolution kernels for forward differences
	float kernel[] = { -1, 1 };
    cv::Mat xKernel = cv::Mat(1,2,CV_32FC1,kernel);
    cv::Mat yKernel = cv::Mat(2,1,CV_32FC1,kernel);
    cv::Point anchorPt = cv::Point(0,0);

    cv::filter2D(inputImg,xGradient, CV_32FC1, xKernel, anchorPt);	// x gradient
    cv::filter2D(inputImg,yGradient,CV_32FC1, yKernel, anchorPt);	// y gradient
}

// Computes the magnitude of the gradients
void OpenCVtrilateralFilter::computeMagnitude(
        cv::Mat& xGradient, cv::Mat& yGradient,
        cv::Mat& gradientMagnitude)
{
    gradientMagnitude = cv::norm(xGradient-yGradient);
    /*
    float* xGrad = (float*) xGradient.data;
    float* yGrad = (float*) yGradient.data;
    float* gradMag = (float*) gradientMagnitude.data;

    for (int x = 0; x < xGradient.cols * xGradient.rows; x++)
        gradMag[x] = cv::norm(xGrad[x], yGrad[x]);
    */
}

// Find the adaptive neighbourhood for image
void OpenCVtrilateralFilter::setAdaptiveNeighbourHood(
    cv::Mat& gradientMagnitude, const float sigmaR, const int maxLevel,
    cv::Mat& adaptiveNeighbourhood	)
{
	// Image stacks for max and min neighbourhoods
    vector<cv::Mat> minGradientStack, maxGradientStack;
    cv::Size imgSize = gradientMagnitude.size();

	// Create image stack
	for(int i = 0 ; i < maxLevel ; i++)
        minGradientStack.push_back( cv::Mat(imgSize,gradientMagnitude.depth(),1) );
	for(int i = 0 ; i < maxLevel ; i++)
        maxGradientStack.push_back( cv::Mat(imgSize,gradientMagnitude.depth(),1) );

	// Build the min-max stack
    buildMinMaxImageStack(gradientMagnitude, minGradientStack, maxGradientStack );

	// Set up image data references
    cv::Mat minImg, maxImg;
    cv::Mat magImg = cv::Mat(gradientMagnitude);
    cv::Mat adpImg = cv::Mat(adaptiveNeighbourhood);

    for(int y = 0; y < imgSize.width; y++)
	{
        for(int x = 0; x < imgSize.height; x++)
		{
			int lev;
            const float upperThreshold = magImg.ptr(y)[x] + sigmaR;
            const float lowerThreshold = magImg.ptr(y)[x] - sigmaR;

			// Compute the adaptive neighbourhood based on the similarity of
			// the neighborhood gradients
			for(lev = 0; lev < maxLevel; lev++) 
			{
				minImg = minGradientStack[lev];
				maxImg = maxGradientStack[lev];
                if ( maxImg.ptr(y)[x] > upperThreshold || minImg.ptr(y)[x] < lowerThreshold )
					break;
			}

			// Sets the (half) size of the adaptive region
			// i.e., floor( ( pow(2.f, lev) + 1 ) / 2.f )
            adpImg.ptr(y)[x] = pow(2.f, lev-1);
		}
	}
}


// Building the Min-Max Stack of Image Gradients
void OpenCVtrilateralFilter::buildMinMaxImageStack(
    cv::Mat& gradientMagnitude,
    vector<cv::Mat> minStack, vector<cv::Mat> maxStack )
{
    const int imgWidth = gradientMagnitude.cols;
    const int imgHeight = gradientMagnitude.rows;

	// Set up image data references
    cv::Mat minImg1, maxImg1, minImg2, maxImg2;
    cv::Mat magImg = cv::Mat(gradientMagnitude);

	// Set up the bottom level of the pyramid
	minImg1 = minStack[0];
	maxImg1 = maxStack[0];
	
	// Loop through image setting up bottom stack
	for(int y = 0; y < imgHeight ; y++)
	{
		for (int x = 0; x < imgWidth; x++)
		{
			float outMin = 1e12;
			float outMax = -1e12;
			
			// Loop through local neighbourhood
			// To find maximum and minimum values
			for(int n = __max(y-1,0) ; n < __min(y+2, imgHeight); n++) 
			{
				for(int m=__max(x-1,0); m < __min(x+2, imgWidth) ; m++) 
				{
                    outMin = __min(magImg.ptr(n)[m], outMin);
                    outMax = __max(magImg.ptr(n)[m], outMax);
				}
			}
            minImg1.ptr(y)[x] = outMin;
            maxImg1.ptr(y)[x] = outMax;
		}
	}

	// Loop through image stack
	for (int i = 1 ; i < minStack.size(); i++)
	{
		// Lower level
		minImg1 = minStack[i-1];
		maxImg1 = maxStack[i-1];

		// Current level
		minImg2 = minStack[i];
		maxImg2 = maxStack[i];

		for(int y = 0; y < imgHeight ; y++)
		{
			for (int x = 0; x < imgWidth; x++)
			{
				float outMin = 1e12;
				float outMax = -1e12;

				// Loop through local neighbourhood
				// To find maximum and minimum values
				for(int n = __max(y-1,0) ; n < __min(y+2, imgHeight); n++) 
				{
					for(int m =__max(x-1,0); m < __min(x+2, imgWidth) ; m++) 
					{
                        outMin = __min(minImg1.ptr(n)[m], outMin);
                        outMax = __max(maxImg1.ptr(n)[m], outMax);
					}
				}
                minImg2.ptr(y)[x] = outMin;
                maxImg2.ptr(y)[x] = outMax;
			}
		}
	}
}

// =======================================================================
// Specific for fast version of Trilateral Fitler
// =======================================================================


//	Bilaterally filters the X and Y gradients of the input image.
//	To produce smoothed x and y gradients

void OpenCVtrilateralFilter::BilateralGradientFilter(
        cv::Mat& xGradient, cv::Mat& yGradient,
        cv::Mat& gradientMagnitude,
		const float sigmaC, const float sigmaR, const float epsilon,
        cv::Mat& xGradientSmooth, cv::Mat& yGradientSmooth	)
{
	// Get image size
    const int imgWidth  = xGradient.cols;
    const int imgHeight = xGradient.rows;

	// Constants used for domain / range calculations
	const float domainConst = -2.f * sigmaC * sigmaC;
	const float rangeConst =  -2.f * sigmaR * sigmaR;

	// Compute the weight for the domain filter (domainWeight). 
	// The domain filter is a Gaussian lowpass filter
	const int halfSize = int(sigmaC / 2.f);
    cv::Mat domainWeightLUT =
        cv::Mat(cvSize(halfSize+1,halfSize+1),xGradient.depth(),1);
	
	// Memory reference
    cv::Mat domainWeight = cv::Mat(domainWeightLUT);

    for (int y = 0; y < domainWeightLUT.rows ; y++)
	{
        for (int x = 0; x < domainWeightLUT.cols ; x++)
		{
			// weight for the domain filter (domainWeight)
			const float diff = (float) (x*x+y*y);
            domainWeight.ptr(y)[x] = (float) exp( diff / domainConst );
		}
	}

	// Memory referencing
    cv::Mat xImg = cv::Mat(xGradient);
    cv::Mat yImg= cv::Mat(yGradient);
    cv::Mat xSmoothImg = cv::Mat(xGradientSmooth);
    cv::Mat ySmoothImg= cv::Mat(yGradientSmooth);
    cv::Mat magImg= cv::Mat(gradientMagnitude);
	

	// Loop through image
	for(int y = 0; y < imgHeight ; y++) 
	{
		for(int x = 0; x < imgWidth ; x++)  
		{		
			double normFactor = 0.f;
			double tmpX = 0.f;
			double tmpY = 0.f;

			// Calculate Middle Pixel Normalised-gradient
            const float g2 = magImg.ptr(y)[x];

			// Loop through local neighbourhood
			for (int n = -halfSize; n <= halfSize; n++) 
			{ 
				for(int m = -halfSize; m <= halfSize; m++) 
				{ 	
					//Compute the weight for the domain filter (domainWeight). 
                    const float dWeight = domainWeight.ptr(abs(n))[abs(m)];

					// Only perform calculation if weight above zero
					if( dWeight < epsilon ) continue;
				
					// Only perform calculationg if within bounds
					const int localX = x + m;
					if (localX < 0) continue;
					if (localX >= imgWidth) continue;

					const int localY = y + n;
					if (localY < 0) continue;
					if (localY >= imgHeight) continue;

					// Calculate Local Normalised Gradient
                    const float g1 = magImg.ptr(localY)[localX];

					//Compute the gradient difference between a pixel and its neighborhood pixel 
					const float gradDiffSq =  (float) pow(g1 - g2, 2);
					
					// Compute the weight for the range filter (rangeWeight). The range filter
					// is a Gaussian filter defined by the difference in gradient magnitude.
					const float rangeWeight = (float) exp( gradDiffSq / rangeConst );	
					
					// Only compute if less than epsilon
					if (rangeWeight < epsilon) continue;

                    tmpX += xImg.ptr(localY)[localX] * dWeight * rangeWeight;
                    tmpY += yImg.ptr(localY)[localX] * dWeight * rangeWeight;

					// Bilateral filter normalized by normFactor
					normFactor += dWeight * rangeWeight;
				}
			}

			// Set smoothed image to normalised value
            xSmoothImg.ptr(y)[x] = tmpX / normFactor;
            ySmoothImg.ptr(y)[x] = tmpY / normFactor;
		}	
	}
}


// Filters the detail signal and computes the output (2nd filtering pass for trilateral filter).
void OpenCVtrilateralFilter::DetailBilateralFilter(
        cv::Mat& inputImage, cv::Mat& adaptiveRegion,
        cv::Mat& xGradientSmooth, cv::Mat& yGradientSmooth,
		const float sigmaC, const float sigmaR,
		const int maxDomainSize, const float epsilon,
        cv::Mat& outputImg)
{

	// Get image size
    const int imgWidth  = inputImage.cols;
    const int imgHeight = inputImage.rows;

	// Create constants used throughout code
	const double domainConst = -2.f * sigmaC * sigmaC;
	const double rangeConst =  -2.f * sigmaR * sigmaR;

	// Memory referencing
    cv::Mat xImg = cv::Mat(xGradientSmooth);
    cv::Mat yImg = cv::Mat(yGradientSmooth);
    cv::Mat srcImg = cv::Mat(inputImage);
    cv::Mat outImg = cv::Mat(outputImg);
    cv::Mat adpImg = cv::Mat(adaptiveRegion);

	// Define Look Up Table for weightings
	
	// Compute the weight for the domain filter (domainWeight). The domain filter
	// is a Gaussian lowpass filter
    cv::Mat domainWeightLUT =
        cv::Mat( cvSize(maxDomainSize+1,maxDomainSize+1), inputImage.depth(), 1);
		
	// Memory reference
    cv::Mat domainWeight = cv::Mat(domainWeightLUT);

    for (int y = 0; y < domainWeightLUT.rows ; y++)
	{
        for (int x = 0; x < domainWeightLUT.cols ; x++)
		{
			// weight for the domain filter (domainWeight)
			const float diff = (float) (x*x+y*y);
            domainWeight.ptr(y)[x] = (float) exp( diff / domainConst );
		}
	}

	for(int y = 0; y < imgHeight; y++) 
	{	
		for(int x = 0; x < imgWidth; x++) 
		{ 
			double normFactor = 0.f;
			double tmp = 0.f;

			// filter window width is calculated from adaptive neighbourhood
			// halfsize is half of the filter window width (or maximum LUT value)
            const int halfSize = (int) __min( adpImg.ptr(y)[x], maxDomainSize );

			// Coefficients defining the centerplane is calculated
			// from the smoothed image gradients
			// Plane Equation is z = coeffA.x + coeffB.y + coeffC
			// coeffA = dI/dx, coeffB = dI/dy, coeffC = I at center pixel of the filter kernel
            const float coeffA = xImg.ptr(y)[x];
            const float coeffB = yImg.ptr(y)[x];
            const float coeffC = srcImg.ptr(y)[x];

			for (int n = -halfSize; n <= halfSize; n++) // y scan line
			{
				for(int m = -halfSize; m <= halfSize; m++) // x scan line
				{
					// Get domain weight from LUT
                    const float dWeight = domainWeight.ptr(abs(n))[abs(m)];

					// Only perform calculation if weight above zero
					if( dWeight < epsilon ) continue;
				
					// Only perform calculationg if within bounds
					const int localX = x + m;
					if (localX < 0) continue;
					if (localX >= imgWidth) continue;

					const int localY = y + n;
					if (localY < 0) continue;
					if (localY >= imgHeight) continue;

					// Compute the detail signal (detail) based on the difference between a 
					// neighborhood pixel and the centerplane passing through the center-pixel 
					// of the filter window. 
					const float detail = 
                        srcImg.ptr(localY)[localX] - coeffA * float(m) - coeffB * float(n) - coeffC;

					// Compute the weight for the range filter (rangeWeight). The range filter
					// is a Gaussian filter defined by the detail signal.
					const float rangeWeight = exp( pow(detail,2) / rangeConst );	

					if ( dWeight < epsilon ) continue;

					tmp += detail * dWeight * rangeWeight;

					//Detail Bilateral filter normalized by normFactor (eq. 9, Section 3.1)
					normFactor += dWeight * rangeWeight;
				}
			}

			// Write result to output image
            outImg.ptr(y)[x] = tmp / normFactor + coeffC;
		}	
	}	
}

// =======================================================================
// Specific for LUT version of Trilateral Fitler
// =======================================================================

//	Bilaterally filters the X and Y gradients of the input image.
//	To produce smoothed x and y gradients

void OpenCVtrilateralFilter::BilateralGradientFilterLUT(
        cv::Mat& xGradient, cv::Mat& yGradient,
        cv::Mat& gradientMagnitude,
		const float sigmaC, const float sigmaR,
        cv::Mat& xGradientSmooth, cv::Mat& yGradientSmooth	)
{
	// Get image size
    const int imgWidth  = xGradient.cols;
    const int imgHeight = xGradient.rows;

	// Constants used for domain / range calculations
	const float domainConst = -2.f * sigmaC * sigmaC;
	const float rangeConst =  -2.f * sigmaR * sigmaR;

	// Compute the weight for the domain filter (domainWeight). 
	// The domain filter is a Gaussian lowpass filter
	const int halfSize = int(sigmaC - 1.f / 2.f);
    cv::Mat domainWeightLUT = cv::Mat(cv::Size(halfSize+1,halfSize+1), xGradient.depth(),1);
	
	// Memory reference
    cv::Mat domainWeight = cv::Mat(domainWeightLUT);

    for (int y = 0; y < domainWeightLUT.rows ; y++)
	{
        for (int x = 0; x < domainWeightLUT.cols ; x++)
		{
			// weight for the domain filter (domainWeight)
			const float diff = (float) (x*x+y*y);
            domainWeight.ptr(y)[x] = (float) exp( diff / domainConst );
		}
	}

	// Memory referencing
    cv::Mat xImg = cv::Mat(xGradient);
    cv::Mat yImg = cv::Mat(yGradient);
    cv::Mat xSmoothImg = cv::Mat(xGradientSmooth);
    cv::Mat ySmoothImg = cv::Mat(yGradientSmooth);
    cv::Mat magImg = cv::Mat(gradientMagnitude);
	

	// Loop through image
	for(int y = 0; y < imgHeight ; y++) 
	{
		for(int x = 0; x < imgWidth ; x++)  
		{		
			double normFactor = 0.f;
			double tmpX = 0.f;
			double tmpY = 0.f;

			// Calculate Middle Pixel Normalised-gradient
            const float g2 = magImg.ptr(y)[x];

			// Loop through local neighbourhood
			for (int n = -halfSize; n <= halfSize; n++) 
			{ 
				for(int m = -halfSize; m <= halfSize; m++) 
				{ 	
					//Compute the weight for the domain filter (domainWeight). 
                    const float dWeight = domainWeight.ptr(abs(n))[abs(m)];
				
					// Only perform calculationg if within bounds
					const int localX = x + m;
					if (localX < 0) continue;
					if (localX >= imgWidth) continue;

					const int localY = y + n;
					if (localY < 0) continue;
					if (localY >= imgHeight) continue;

					// Calculate Local Normalised Gradient
                    const float g1 = magImg.ptr(localY)[localX];

					// Compute the gradient difference between a pixel and its neighborhood pixel 
					const float gradDiffSq =  (float) pow(g1 - g2, 2);
					
					// Compute the weight for the range filter (rangeWeight). The range filter
					// is a Gaussian filter defined by the difference in gradient magnitude.
					const float rangeWeight = (float) exp( gradDiffSq / rangeConst );	

                    tmpX += xImg.ptr(localY)[localX] * dWeight * rangeWeight;
                    tmpY += yImg.ptr(localY)[localX] * dWeight * rangeWeight;

					// Bilateral filter normalized by normFactor
					normFactor += dWeight * rangeWeight;
				}
			}

			// Set smoothed image to normalised value
            xSmoothImg.ptr(y)[x] = tmpX / normFactor;
            ySmoothImg.ptr(y)[x] = tmpY / normFactor;
		}	
	}
}


// Filters the detail signal and computes the output (2nd filtering pass for trilateral filter).
void OpenCVtrilateralFilter::DetailBilateralFilterLUT(
        cv::Mat& inputImage, cv::Mat& adaptiveRegion,
        cv::Mat& xGradientSmooth, cv::Mat& yGradientSmooth,
		const float sigmaC, const float sigmaR,
        const int maxDomainSize, cv::Mat& outputImg)
{

	// Get image size
    const int imgWidth  = inputImage.cols;
    const int imgHeight = inputImage.rows;

	// Create constants used throughout code
	const double domainConst = -2.f * sigmaC * sigmaC;
	const double rangeConst =  -2.f * sigmaR * sigmaR;

	// Memory referencing
    cv::Mat xImg = cv::Mat(xGradientSmooth);
    cv::Mat yImg = cv::Mat(yGradientSmooth);
    cv::Mat srcImg = cv::Mat(inputImage);
    cv::Mat outImg = cv::Mat(outputImg);
    cv::Mat adpImg = cv::Mat(adaptiveRegion);

	// Define Look Up Table for weightings
	
	// Compute the weight for the domain filter (domainWeight). The domain filter
	// is a Gaussian lowpass filter
    cv::Mat domainWeightLUT = cv::Mat( cv::Size(maxDomainSize,maxDomainSize), inputImage.depth(), 1);
		
	// Memory reference
    cv::Mat domainWeight = cv::Mat(domainWeightLUT);

    for (int y = 0; y < domainWeightLUT.rows ; y++)
	{
        for (int x = 0; x < domainWeightLUT.cols ; x++)
		{
			// weight for the domain filter (domainWeight)
			const float diff = (float) (x*x+y*y);
            domainWeight.ptr(y)[x] = (float) exp( diff / domainConst );
		}
	}


	for(int y = 0; y < imgHeight; y++) 
	{	
		for(int x = 0; x < imgWidth; x++) 
		{ 
			double normFactor = 0.f;
			double tmp = 0.f;

			// filter window width is calculated from adaptive neighbourhood
			// halfsize is half of the filter window width (or maximum LUT value)
            const int halfSize = (int) adpImg.ptr(y)[x];

			// Coefficients defining the centerplane is calculated
			// from the smoothed image gradients
			// Plane Equation is z = coeffA.x + coeffB.y + coeffC
			// coeffA = dI/dx, coeffB = dI/dy, coeffC = I at center pixel of the filter kernel
            const float coeffA = xImg.ptr(y)[x];
            const float coeffB = yImg.ptr(y)[x];
            const float coeffC = srcImg.ptr(y)[x];

			for (int n = -halfSize; n <= halfSize; n++) // y scan line
			{
				for(int m = -halfSize; m <= halfSize; m++) // x scan line
				{
					// Get domain weight from LUT
                    const float dWeight = domainWeight.ptr(abs(n))[abs(m)];
				
					// Only perform calculationg if within bounds
					const int localX = x + m;
					if (localX < 0) continue;
					if (localX >= imgWidth) continue;

					const int localY = y + n;
					if (localY < 0) continue;
					if (localY >= imgHeight) continue;

					// Compute the detail signal (detail) based on the difference between a 
					// neighborhood pixel and the centerplane passing through the center-pixel 
					// of the filter window. 
					const float detail = 
                        srcImg.ptr(localY)[localX] - coeffA * float(m) - coeffB * float(n) - coeffC;

					// Compute the weight for the range filter (rangeWeight). The range filter
					// is a Gaussian filter defined by the detail signal.
					const float rangeWeight = exp( pow(detail,2) / rangeConst );	

					// Add to function
					tmp += detail * dWeight * rangeWeight;

					//Detail Bilateral filter normalized by normFactor 
					normFactor += dWeight * rangeWeight;
				}
			}

			// Normalise according to weight
            outImg.ptr(y)[x] = tmp / normFactor + coeffC;
		}	
	}	


}

