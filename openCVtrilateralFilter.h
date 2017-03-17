#ifndef FILE_openCVtrilateralFilter_h
#define FILE_openCVtrilateralFilter_h

#include <math.h>
#include <opencv/cxcore.h>
#include <vector>
using std::vector;


class OpenCVtrilateralFilter
{
public:
	OpenCVtrilateralFilter(){;};
	~OpenCVtrilateralFilter(){;};

	// Types for filter
	enum{TYPE_LUT, TYPE_FAST};

    bool trilateralFilter(cv::Mat& input, cv::Mat& output, const float sigmaC, const float epsilon,
		const int filterType = TYPE_FAST);
	
    cv::Mat trilateralFilter(cv::Mat& input, const float sigmaC, const float epsilon, const int filterType = TYPE_FAST)
	{
        cv::Mat output = cv::Mat( input.rows, input.cols, input.depth(), cv::Scalar(1));
        if ( trilateralFilter(input, output, sigmaC, epsilon, filterType) )
        {
            return output;
        }

	};

private:

	//Computes X and Y gradients of the input image
   	void computeGradients(
        cv::Mat& inputImg,							// inputs
        cv::Mat& xGradient, cv::Mat& yGradient);	// outputs

	// Compute image magnitude
	void computeMagnitude(
        cv::Mat& xGradient, cv::Mat& yGradient,		// inputs
        cv::Mat& gradientMagnitude);					// output

	//Finds the adaptive neighborhood size (stack level) 
	//from the min-max gradient stack
   	void setAdaptiveNeighbourHood(
        cv::Mat& gradientMagnitude,				// inputs
		const float sigmaR, const int maxLevel,				
        cv::Mat& adaptiveNeighbourhood	);		// output

	//Builds the stack of min-max image gradient magnitudes
	void buildMinMaxImageStack(
        cv::Mat& gradientMagnitude,								// input
        vector<cv::Mat> minStack, vector<cv::Mat> maxStack ); // outputs

	// Fast-Trilateral functions

	//Bilaterally filters  gradients pX and pY 
   	void BilateralGradientFilter(
        cv::Mat& xGradient, cv::Mat& yGradient,					// inputs
        cv::Mat& gradientMagnitude, const float sigmaC,
		const float sigmaR, const float epsilon,
        cv::Mat& xGradientSmooth, cv::Mat& yGradientSmooth	);	// outputs

	//Filters the detail signal and computes the final output image	
   	void DetailBilateralFilter(
        cv::Mat& inputImage, cv::Mat& adaptiveRegion,			//inputs
        cv::Mat& xGradientSmooth, cv::Mat& yGradientSmooth,
		const float sigmaC, const float sigmaR,
		const int maxDomainSize, const float epsilon,
        cv::Mat& outputImg);										// output


	// LUT-Trilateral functions

	void BilateralGradientFilterLUT(
        cv::Mat& xGradient, cv::Mat& yGradient,					// inputs
        cv::Mat& gradientMagnitude,
		const float sigmaC, const float sigmaR,
        cv::Mat& xGradientSmooth, cv::Mat& yGradientSmooth	);	// outputs

	void DetailBilateralFilterLUT(
        cv::Mat& inputImage, cv::Mat& adaptiveRegion,			// inputs
        cv::Mat& xGradientSmooth, cv::Mat& yGradientSmooth,
		const float sigmaC, const float sigmaR, const int maxDomainSize, 
        cv::Mat& outputImg);										// output


	inline float getNorm(float g1, float g2)
	{
		return (float) sqrt( (float) ( pow(g1,2) + pow(g2,2) ) );
	}

	inline int log2(int input, bool roundUp = false)
	{
		float temp = log10( float(input) ) / log10(2.f);
		if (roundUp)
			return int( ceil(temp) );
		else 
			return int( temp );
	}

};

#endif // FILE_openCVtrilateralFilter_h
