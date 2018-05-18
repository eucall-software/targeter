#ifndef TEXTUREANALYSIS_H
#define TEXTUREANALYSIS_H

#include "opencv2/core/core.hpp"

class TextureAnalysis
{
public:
	TextureAnalysis();
	~TextureAnalysis();
	
	float calculateEntropyOfRegion(cv::Mat const & grayimage, int offset_x, int offset_y, int region = 9);

	// requires energy image first
	void entropyFilt(cv::Mat const & image, cv::Mat & entropy, int region = 9);

private:

};

#endif
