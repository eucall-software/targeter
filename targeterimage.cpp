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
	cv_im = cv::Mat();
	isNull = false;
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
	pImage = nullptr;
	pMask = nullptr;
	pHue = nullptr;
	isNull = false;
	m_imageIndex = QPoint(-1, -1);
	imageFunction = imageType::display;
	filepathname = "";
	name = "";
	tooltip = "";
	cameraType = cameraType::none;
	maskType = drawingMode::none;
	isDisplayed = false;
	cv_im = cv::Mat();
	UID = QUuid::createUuid();
}

targeterImage::targeterImage(QExplicitlySharedDataPointer<targeterImage> tar) 
{
	drawingObjects = tar->drawingObjects;		
	imageFunction = tar->imageFunction;		
	maskType = tar->maskType;		
	filepathname = tar->filepathname;	
	name = tar->name;          
	m_ImageOffset = tar->m_ImageOffset;		
	m_ImageFocusPosition = tar->m_ImageFocusPosition;	
	m_ImagesContainer = tar->m_ImagesContainer;
	m_imageIndex = tar->m_imageIndex;
	m_positionFiducial = tar->m_positionFiducial;
	m_positionStage = tar->m_positionStage;
	m_FrameID = tar->m_FrameID;		
	m_SubFrameID = tar->m_SubFrameID;		
	m_subRegionID = tar->m_subRegionID;	
	m_patternRegion = tar->m_patternRegion;	    
	qt_im = tar->qt_im;				
	cv_im = tar->cv_im;			
	pImage = tar->pImage;			
	pMask = tar->pMask;		
	pHue = tar->pHue;
	tooltip = tar->tooltip;
	isDisplayed = tar->isDisplayed;
	cameraType = tar->cameraType;
	labels = tar->labels;			
	stats = tar->stats;	
	centroids = tar->centroids;
	imagePosition = tar->imagePosition; 
	UID = tar->UID;
	isNull = tar->isNULL();
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
targeterImage::~targeterImage() 
{
	free1DImages();
}

void targeterImage::addJSONDATA(QJsonObject obj)
{
	if(!obj.isEmpty())
	{
		if(obj.contains("index"))
		{
			QJsonObject pos = obj["index"].toObject();
			int x=0, y=0;

			if (pos.contains("x"))
				x = pos["x"].toInt();
			if (pos.contains("y"))
				y = pos["y"].toInt();
		
			m_imageIndex = QPoint(x, y);
		}

		if (obj.contains("stage"))
		{
			QJsonObject pos = obj["stage"].toObject();

			double x = 0, y = 0, z = 0;

			if (pos.contains("x"))
				x = pos["x"].toDouble();
			if (pos.contains("y"))
				y = pos["y"].toDouble();
			if (pos.contains("z"))
				z = pos["z"].toDouble();

			m_positionStage = QVector3D(x, y, z);
		}
		if (obj.contains("fiducial"))
		{
			QJsonObject pos = obj["fiducial"].toObject();

			double x=0, y=0, z=0;

			if (pos.contains("x"))
				x = pos["x"].toDouble();
			if (pos.contains("y"))
				y = pos["y"].toDouble();
			if (pos.contains("z"))
				z = pos["z"].toDouble();

			m_positionFiducial= QVector3D(x, y, z);
		}
	}
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
void targeterImage::free1DImages() 
{
	if (pImage)
	{
		delete[] pImage;
		pImage = nullptr;
	}
	if (pMask)
	{
		delete[] pMask;
		pMask = nullptr;
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
	// check valid image
	if(im.rows>0 && im.cols>0)
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

		// set image valid
		isNull = false;
	}
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

	createQTImage(true);
}

QString targeterImage::toString()
{
	//QString type = IMAGETYPESTRINGS(tim.imageFunction);

	QString strTooltip = "<b>name:</b> " + QString::fromStdString(this->name) + "<br><b>filename:</b> "
		+ QString::fromStdString(filepathname) + "<br><b>type:</b> "
		+ "<b>width:</b> " + QString::number(Cols()) + ", <b>height:</b> " + QString::number(Rows()) + "<br>"
		+ IMAGETYPESTRINGS(imageFunction) + "<br>";

	QString masktype = DRAWINGMODESTRINGS(maskType);

	if (maskType != drawingMode::drawingMode::none)
		strTooltip += "<b>mask type:</b> " + masktype + "<br>";

	QString tt = QString::fromStdString(getTooltip());

	if (tt != "")
		strTooltip += "<b>info:</b> " + tt + "<br>";

	cameraType::camera cam = getCameraType();
	QString s = CAMERATYPE(cam);

	if (cam != cameraType::none)
		strTooltip += "<b>from camera:</b> " + s + "<br>";

	if (m_imageIndex.x() >= 0 && m_imageIndex.y() >= 0)
		strTooltip += "<b>image index position:</b> x:" + QString::number(m_imageIndex.x()) +
		" y:" + QString::number(m_imageIndex.y()) + "<br>";

	if(m_positionFiducial.x() >= 0 && m_positionFiducial.y() >= 0 && m_positionFiducial.z() >= 0)
		strTooltip += "<b>fiducial position:</b> x:" + QString::number(m_positionFiducial.x()) + 
		" y:"+  QString::number(m_positionFiducial.y()) + 
		" z:" + QString::number(m_positionFiducial.z()) + "<br>";

	if (m_positionStage.x() >= 0 && m_positionStage.y() >= 0 && m_positionStage.z() >= 0)
		strTooltip += "<b>stage position:</b> x:" + QString::number(m_positionStage.x()) +
		" y:" + QString::number(m_positionStage.y()) +
		" z:" + QString::number(m_positionStage.z()) + "<br>";

	
	return strTooltip;
}

QExplicitlySharedDataPointer<targeterImage> targeterImage::getGlobalImage(int index) {
	if (index >= 0 && index < m_ImagesContainer->getNumImages())
		return m_ImagesContainer->getImageAt(index);
};


