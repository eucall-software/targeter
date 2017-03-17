#ifndef TARGTERIMAGE_H
#define TARGTERIMAGE_H

//#include <vld.h>
#include <QPolygon>
#include <QRect>
#include <QDebug>
#include <qimage.h>


class ImagesContainer;

/**
* class to represent targeter image used to store associated image information and group images together
*/
class targeterImage {

public:
	targeterImage(ImagesContainer* pWin);
	targeterImage();
	~targeterImage();

	void addImageFromFile(std::string filename, imageType::imageType type = imageType::display);
	void addImageEx(cv::Mat im, imageType::imageType type, std::string descriptiveName = "", std::string tooltip = "", std::string filename = "");
	
	void addImage(cv::Mat im);

	cv::Mat& getImage();

	void createQTImage(bool bRGBSwap = true);
	
	QImage getQTImage();

	std::string setDefaultName();

	void setImageType(imageType::imageType type) { imageFunction = type; };	// name of function which created image

	imageType::imageType getImageFunction() { return imageFunction; };

	std::vector<int>& getDerivedImageArray() {return m_derivedImages;};

	void addDerivedIndex(int ind) { m_derivedImages.push_back(ind); };
	void addDerivedIndexes(const std::vector<int>& to_add) {m_derivedImages.insert(std::end(m_derivedImages), std::begin(to_add), std::end(to_add));};

	targeterImage& getImageOfType(imageType::imageType imageFunction);

	void removeDerivedIndex(int ind);
	void removeDerivedIndexes(const std::vector<int>& to_remove);
	
	std::string getName() { return name; };
	void setName(std::string s) { name = s; };

	int* get1DImage(imageType::imageType type);

	void set1DImage(int* im, imageType::imageType type = imageType::display);
	
	void free1DImages();

	int getImageRows();
	int getImageCols();

	cv::Size getImageSize();

	int getImageType();

	// functions for dealing with ccimages

	// getters
	cv::Mat& getLabelsImage() {	return labels;	};
	cv::Mat& getStatsImage() {	return stats;	};
	cv::Mat& getCentroidsImage() {	return centroids; };

	//setters
	void setLabelsImage(cv::Mat im) {labels = im;};
	void setStatsImage(cv::Mat im) {stats = im;};
	void setCentroidsImage(cv::Mat im) {centroids = im;};

	// functions for dealing with mask images	/////////////////////////////////////
	void setMaskType(drawingMode::drawingMode mode) { maskType = mode; };

	drawingMode::drawingMode getMaskType() { return maskType; };

private:
	ImagesContainer* m_ImagesContainer;

	std::vector<int> m_derivedImages;	    /// array index of images that are the result of processing this image (eg. mask images, target images, ccimages)
	

	QImage qt_im;				/// QT Image (shares data with opencv image)
	cv::Mat cv_im;				/// OpenCV image

	int* pImage;				/// int* image 1D array
	int* pMask;					/// int* mask image 1D array
	
	imageType::imageType imageFunction;		/// type of image

	drawingMode::drawingMode maskType;		/// type of mask

	std::string filepathname;	/// image path name
	std::string name;           /// image moniker

								// maybe not used much
	
	std::string tooltip;		/// tooltip describing image
	bool isDisplayed;			/// boolean to set if image is displayed


	// if the image is connected components image then add this associated information
	cv::Mat labels;			/// connected components labels
	cv::Mat stats;			/// connected components stats
	cv::Mat centroids;		/// connected components centroids
};
/*
class ccImage : public  targeterImage
{


public:
	ccImage(ImagesContainer* pC) : targeterImage(pC) { this->imageFunction = imageType::cclabels; };
	ccImage() {};

	
	void addImageEx(cv::Mat im,	std::string descriptiveName = "", std::string tooltip = "", std::string filename = "") 	{
		targeterImage::addImageEx(im, imageType::cclabels, descriptiveName, tooltip, filename);
	};
};

class maskImage : public targeterImage
{
private:
	// if the image is connected components image then add this associated information
	drawingMode::drawingMode maskType;		/// type of mask

public:
	maskImage(ImagesContainer* pC) : targeterImage(pC) { this->imageFunction = imageType::mask; }
	maskImage() {};



	void addImageEx(cv::Mat im,
		std::string descriptiveName = "",
		drawingMode::drawingMode masktype = drawingMode::none,
		std::string tooltip = "", std::string filename = "") 
	{
		this->maskType = masktype; 
		targeterImage::addImageEx(im, imageType::mask, descriptiveName, tooltip, filename);
	};
};

class targetImage : public  targeterImage
{
	QRect postionInParentImage;				/// position of image in overall 2D space
};
*/
#endif