// Targeter - target identification software for EUCALL workpackage 6
// Licensed under the GPL License. See LICENSE file in the project root for full license information.
// Copyright(C) 2017  David Watts 


//#include <vld.h>

#include "globals.h"
#include "targeterimage.h"
#include "imagesContainer.h"
#include "HelperFunctions.h"

#include <QRect>
#include <QDebug>
#include <QImage>
#include <QUuid>


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
targeterImage::targeterImage(ImagesContainer* pImages) : targeterImage()
{ 
	this->m_ImagesContainer = pImages;
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
	pHue = NULL;
	imageFunction = imageType::display;
	filepathname = "";
	name = "";
	tooltip = "";
	cameraType = cameraType::none;
	maskType = drawingMode::none;
	isDisplayed = false;
	UID = QUuid::createUuid();
	m_FriendIDs.push_back(UID);
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
	else if (type == imageType::hue)
		return pHue;
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
	else if (type == imageType::hue)
		pHue = im;
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
*  returns QImage copy
*
* @author    David Watts
* @since     2017/03/15
*
* FullName   targeterImage::getQTImage
* Qualifier
* @return    QT_NAMESPACE::QImage
* Access     public
*/
QImage& targeterImage::getQTImage()
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
	// make sure cv image of the correct type
	if (cv_im.channels() < 3)
	{
		DBOUT("image doesnt have enough channels, making 3 channel image");

		cv::Mat in[] = { cv_im, cv_im, cv_im };
		cv::merge(in, 3, cv_im);
	}

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

int targeterImage::Rows()
{
	return getImage().rows;
}

int targeterImage::Cols()
{
	return getImage().cols;
}

int targeterImage::Type()
{
	return getImage().type();
}

cv::Size targeterImage::Size() {
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

	this->addImageEx(im, QUuid::QUuid(), type, filename);
}

/**
*
*  Extended method to create image
*
* @author    David Watts
* @since     2017/03/23
* 
* FullName   targeterImage::addImageEx
* Qualifier 
* @param     cv::Mat im 
* @param     QUuid UIDParent 
* @param     imageType::imageType type 
* @param     std::string descriptiveName 
* @param     std::string tooltip 
* @param     std::string filename 
* @return    void
* Access     public 
*/
void targeterImage::addImageEx(cv::Mat im, QUuid UIDParent, imageType::imageType type, std::string descriptiveName, std::string tooltip, std::string filename)
{
	this->name = descriptiveName;
	this->imageFunction = type;
	this->filepathname = filename;

	// stores image
	addImage(im);

	if (descriptiveName == "")
		this->name = getDefaultName();

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
std::string targeterImage::getDefaultName()
{
	if (this->imageFunction == imageType::display)
		return std::string("an image");
	else if (this->imageFunction == imageType::mask)
		return std::string("mask image");
	else if (this->imageFunction == imageType::cclabels)
		return std::string("labeled image");
	else if (this->imageFunction == imageType::target)
		return std::string("target image");
	else if (this->imageFunction == imageType::test)
		return std::string("detection image");
	else if (this->imageFunction == imageType::score)
		return std::string("score image");
	else if (this->imageFunction == imageType::score)
		return std::string("centroids image");
	else if (this->imageFunction == imageType::roi)
		return std::string("region of interest image");
	else if (this->imageFunction == imageType::any)
		return std::string("a valid image");
	else
		return std::string("an image");
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

	this->IsGray = HelperFunctions::isGrayImage(im);

	createQTImage(true);
}

/**
*
*  remove associated image given its ID
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   targeterImage::removeFriendIndex
* Qualifier 
* @param     QUuid ID 
* @return    void
* Access     public 
*/
bool targeterImage::removeFriendID(QUuid ID) 
{
	bool bFound = false;
	
	std::vector<QUuid>::iterator iter = std::find(m_FriendIDs.begin(), m_FriendIDs.end(), ID);

	if (iter == m_FriendIDs.end())
	{
		bFound = true;
		m_FriendIDs.erase(iter);
	}
	return bFound;
}

/**
*
*  remove associated images given their ID's
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   targeterImage::removeFriendIndexes
* Qualifier 
* @param     const std::vector<QUuid> & to_remove 
* @return    void
* Access     public 
*/
void targeterImage::removeFriendIDs(const std::vector<QUuid>& to_remove)
{
	for (std::vector<QUuid>::iterator iter = m_FriendIDs.begin(); iter < m_FriendIDs.end(); iter++)
		removeFriendID(*iter);
}

/**
*
*  check if object has friend image of a given ID
*
* @author    David Watts
* @since     2017/03/23
* 
* FullName   targeterImage::hasFriendID
* Qualifier 
* @param     QUuid ID 
* @return    bool
* Access     public 
*/
bool targeterImage::hasFriendID(QUuid ID)
{
	return std::find(m_FriendIDs.begin(), m_FriendIDs.end(), ID) == m_FriendIDs.end();
}

targeterImage& targeterImage::getGlobalImage(int index) {
	if (index >= 0 && index < m_ImagesContainer->getNumImages())
		return m_ImagesContainer->getImageAt(index);
};

std::vector<QUuid>::iterator targeterImage::getFriend(QUuid ID){ return std::find(m_FriendIDs.begin(), m_FriendIDs.end(), ID); }


/**
*
*  gets global image array (m_ImagesContainer) index of friend image of a certain imageType
*
* @author    David Watts
* @since     2017/03/23
* 
* FullName   targeterImage::getFriendIndexOfType
* Qualifier 
* @param     imageType::imageType imageFunction 
* @return    int
* Access     public 
*/
int targeterImage::getFriendArrayIndexOfType(imageType::imageType imageFunction)
{
	int ret = -1;

	for (std::vector<QUuid>::iterator iter = m_FriendIDs.begin(); iter < m_FriendIDs.end(); iter++)
	{
		for (int i = 0; i < m_ImagesContainer->getImages().size(); i++)
		{
			targeterImage& t = m_ImagesContainer->getImageAt(i);

			if (t.getUID() == *iter &&  t.getImageFunction() == imageFunction)
			{	
				ret =  i;
				break;
			}
		}
	}
	return ret;
}
