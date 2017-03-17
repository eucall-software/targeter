
//#include <vld.h>

#include "globals.h"
#include "targeterimage.h"
#include "imagesContainer.h"
#include "HelperFunctions.h"

#include <QRect>
#include <QDebug>
#include <QImage>

/**
*
*  Constructor for targeterImage class, has pointer to image array
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   targeterImage::targeterImage
* Qualifier 
* @param     ImagesContainer * pImages 
* @return    
* Access     public 
*/
targeterImage::targeterImage(ImagesContainer* pImages)
{ 
	this->m_ImagesContainer = pImages;
	pImage = NULL;
	pMask = NULL;
	imageFunction = imageType::display;
	filepathname = "";
	name = "";
	tooltip = "";
	isDisplayed = false;
}

/**
*
*   Constructor for targeterImage class
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   targeterImage::targeterImage
* Qualifier 
* @return    
* Access     public 
*/
targeterImage::targeterImage()
{
	pImage = NULL;
	pMask = NULL;
	imageFunction = imageType::display;
	filepathname = "";
	name = "";
	tooltip = "";
	isDisplayed = false;
}

/**
*
* targeterImage destructor 
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   targeterImage::~targeterImage
* Qualifier 
* @return    
* Access     public 
*/
targeterImage::~targeterImage() {
	//free1DImages(); 
}

/**
*
*  Returns int* image pointer depending on type of image
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   targeterImage::get1DImage
* Qualifier 
* @param     imageType::imageType type 
* @return    int*
* Access     public 
*/
int* targeterImage::get1DImage(imageType::imageType type) {
	if (type == imageType::mask)
		return pMask;
	else
		return pImage;
};

/**
*
*  sets int* image pointer, depending on type of image
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   targeterImage::set1DImage
* Qualifier 
* @param     int * im 
* @param     imageType::imageType type 
* @return    void
* Access     public 
*/
void targeterImage::set1DImage(int* im, imageType::imageType type) {
	if (type == imageType::mask)
		pMask = im;
	else
		pImage = im;
};

/**
*
* free's memory used by image pointers 
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   targeterImage::free1DImages
* Qualifier 
* @return    void
* Access     public 
*/
void targeterImage::free1DImages() {
	if (pImage)
	{
		delete[] pImage;
		pImage = NULL;
	}
	if (pMask)
	{
		delete[] pMask;
		pMask = NULL;
	}
};

/**
*
* gets associated image of a certain type  
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   targeterImage::getImageOfType
* Qualifier 
* @param     imageType::imageType imageFunction 
* @return    targeterImage::targeterImage&
* Access     public 
*/
targeterImage& targeterImage::getImageOfType(imageType::imageType imageFunction) {
	for (int i = 0; i < m_derivedImages.size(); i++)
	{
		if (m_ImagesContainer->getImageAt(m_derivedImages[i]).imageFunction == imageFunction)
		{ 
			return m_ImagesContainer->getImageAt(m_derivedImages[i]);
		}
	}
}

/**
*
*  gets QImage and if not exising creates one from valid cv::Mat image
*
* @author    David Watts
* @since     2017/03/15
*
* FullName   targeterImage::getQTImage
* Qualifier
* @return    QT_NAMESPACE::QImage
* Access     public
*/
QImage targeterImage::getQTImage()
{ 
	return qt_im; 
};

/**
*
* Creates a QImage for display purposes from an OpenCV image (shares memory)
*
* @author    David Watts
* @since     2017/03/13
*
* FullName   targeterImage::getQImage
* Qualifier
* @param     bool bRGBSwap
* @return    void
* Access     private
*/
void targeterImage::createQTImage(bool bRGBSwap)
{
	qt_im = QImage(cv_im.data, cv_im.cols, cv_im.rows, cv_im.step1(), HelperFunctions::getFormat(cv_im.type()));

	if (bRGBSwap)
		qt_im = qt_im.rgbSwapped();
}

/**
*
*  returns the current display image if existing or a valid image if not
*
* @author    David Watts
* @since     2017/03/15
* 
* FullName   targeterImage::getImage
* Qualifier 
* @return    cv::Mat&
* Access     public 
*/
cv::Mat& targeterImage::getImage()
{
	// always try to return a valid image
	return cv_im;
}

int targeterImage::getImageRows()
{
	return getImage().rows;
}

int targeterImage::getImageCols()
{
	return getImage().cols;
}

int targeterImage::getImageType()
{
	return getImage().type();
}


cv::Size targeterImage::getImageSize() {
	return getImage().size();
}

/**
*
*  loads image from file
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   targeterImage::addImageFromFile
* Qualifier 
* @param     std::string filename 
* @param     imageType::imageType type 
* @return    void
* Access     public 
*/
void targeterImage::addImageFromFile(std::string filename, imageType::imageType type)
{
	cv::Mat im = cv::imread(filename);

	this->filepathname = filename;

	this->addImageEx(im, type, filename);
}

/**
*
*  Extended method to create image
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   targeterImage::addImageEx
* Qualifier 
* @param     cv::Mat im 
* @param     imageType::imageType type 
* @param     std::string descriptiveName 
* @param     std::string tooltip 
* @param     std::string filename 
* @return    void
* Access     public 
*/
void targeterImage::addImageEx(cv::Mat im, imageType::imageType type, std::string descriptiveName, std::string tooltip, std::string filename)
{
	this->name = descriptiveName;
	this->imageFunction = type;

	this->filepathname = filename;

	addImage(im);

	if (descriptiveName == "")
		this->name = setDefaultName();

	if(tooltip == "")
		this->tooltip = this->name;
}

/**
*
*  sets a default name for image based on type
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   targeterImage::setDefaultName
* Qualifier 
* @return    std::string
* Access     public 
*/
std::string targeterImage::setDefaultName()
{
	if (this->imageFunction == imageType::display)
		return "an image";
	else if (this->imageFunction == imageType::mask)
		return "mask image";
	else if (this->imageFunction == imageType::cclabels)
		return "connected components image";
	else if (this->imageFunction == imageType::target)
		return "target image";
	else if (this->imageFunction == imageType::test)
		return "detection image";
	else if (this->imageFunction == imageType::score)
		return "score image";
	else if (this->imageFunction == imageType::score)
		return "centroids image";
	else if (this->imageFunction == imageType::roi)
		return "region of interest image";
	else
		return "an image";
}

/**
*
*  adds image and creates QT Image copy for display
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   targeterImage::addImage
* Qualifier 
* @param     cv::Mat im 
* @return    void
* Access     public 
*/
void targeterImage::addImage(cv::Mat im)
{
	this->cv_im = im;

	createQTImage(true);
}

/**
*
*  remove associated image given its ID
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   targeterImage::removeDerivedIndex
* Qualifier 
* @param     int ind 
* @return    void
* Access     public 
*/
void targeterImage::removeDerivedIndex(int ind) {
	std::vector<int>::iterator it = m_derivedImages.begin();
	std::advance(it, ind);
	m_derivedImages.erase(it);
}

/**
*
*  remove associated images given their ID's
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   targeterImage::removeDerivedIndexes
* Qualifier 
* @param     const std::vector<int> & to_remove 
* @return    void
* Access     public 
*/
void targeterImage::removeDerivedIndexes(const std::vector<int>& to_remove)
{
	auto vector_base = m_derivedImages.begin();
	std::vector<int>::size_type down_by = 0;

	for (auto iter = to_remove.cbegin();
		iter < to_remove.cend();
		iter++, down_by++)
	{
		std::vector<int>::size_type next = (iter + 1 == to_remove.cend()
			? m_derivedImages.size()
			: *(iter + 1));

		std::move(vector_base + *iter + 1,
			vector_base + next,
			vector_base + *iter - down_by);
	}
	m_derivedImages.resize(m_derivedImages.size() - to_remove.size());
}

