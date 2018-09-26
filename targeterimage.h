// Targeter - target identification software for EUCALL workpackage 6
// Licensed under the GPL License. See LICENSE file in the project root for full license information.
// Copyright(C) 2017  David Watts 

#ifndef TARGTERIMAGE_H
#define TARGTERIMAGE_H

//#include <vld.h>
#include <QPolygon>
#include <QRect>
#include <QDebug>
#include <qimage.h>
#include <QUuid>
#include <QVector3D>
#include "globals.h"

class ImagesContainer;

/**
* class to represent targeter image used to store associated image information and group images together
*/
class targeterImage : public QSharedData
{

public:
	targeterImage(ImagesContainer* pWin);
	targeterImage(bool dummy) { isNull = true; };
	targeterImage();
	~targeterImage();

	bool isNULL() { return isNull; };

	targeterImage(QExplicitlySharedDataPointer<targeterImage> tar);

	void addImageFromFile(std::string filename, imageType::imageType type = imageType::display);
	void addImageEx(cv::Mat im, QUuid UIDParent, imageType::imageType type, std::string descriptiveName = "", std::string tooltip = "", std::string filename = "");

	void addDrawingObject(QSharedPointer<drawingObject> dObj) {
		drawingObjects.append(dObj);
	};

	void addImage(cv::Mat im);
	void addJSONDATA(QJsonObject obj);

	cv::Mat& getImage();

	void createQTImage(bool bRGBSwap = true);

	QImage getQTImage();

	void setImageType(imageType::imageType type) { imageFunction = type; };	// name of function which created image

	imageType::imageType getImageFunction() { return imageFunction; };

	QString toString();

	std::string getName() { return name; };

	QString getFileName() { return QString::fromStdString(filepathname); }
	void setName(std::string s) { name = s; };
	std::string getDefaultName();

	int* get1DImage(imageType::imageType type = imageType::display);
	void set1DImage(int* im, imageType::imageType type = imageType::display);

	void free1DImages();

	int Rows();
	int Cols();
	cv::Size Size();
	int Type();

	QUuid& getUID() { return UID; };

	QString getUIDString() { return UID.toString(); };
	std::string getTooltip() { return tooltip; };

	bool isID(QUuid ID) { return ID == UID; };

	// functions for dealing with ccimages

	// getters
	cv::Mat& getLabelsImage() { return labels; };
	cv::Mat& getStatsImage() { return stats; };
	cv::Mat& getCentroidsImage() { return centroids; };
	cv::Rect& getImagePosition() { return imagePosition; };
	cameraType::camera getCameraType() { return cameraType; };

	QPoint getImageIndex() { return m_imageIndex; };
	QVector3D getPositionFiducial() { return m_positionFiducial; };
	QVector3D getPositionStage() { return m_positionStage; };

	void setStagePosition(QVector3D pos) { m_positionStage = pos; };
	void setFiducialPosition(QVector3D pos) { m_positionFiducial = pos; };

	QExplicitlySharedDataPointer<targeterImage> getGlobalImage(int index);

	//setters
	void setLabelsImage(cv::Mat im) { labels = im; };
	void setStatsImage(cv::Mat im) { stats = im; };
	void setCentroidsImage(cv::Mat im) { centroids = im; };
	void setImagePosition(cv::Rect r) { imagePosition = r; };
	void setCameraType(cameraType::camera cam) { cameraType = cam; };

	QString getFrameID() { return m_FrameID; };
	QString getSubFrameID() {return m_SubFrameID; };
	QString getSubRegionID(){return m_subRegionID;};
	QRect getPatternRegion() { return m_patternRegion; };

	void setFrameID(QString s) { m_FrameID = s; };
	void setSubFrameID(QString s) { m_SubFrameID = s; };
	void setSubRegionID(QString s) { m_subRegionID = s; };
	void setPatternRegion(QRect r) { m_patternRegion = r; };

	QVector<QSharedPointer<drawingObject>> getDrawingObjects() { return drawingObjects; };

	// functions for dealing with mask images	/////////////////////////////////////
	void setMaskType(drawingMode::drawingMode mode) { maskType = mode; };

	drawingMode::drawingMode getMaskType() { return maskType; };

public:		// public properties
	QVector<QSharedPointer<drawingObject>> drawingObjects;		/// list of drawing objects for this image

	imageType::imageType imageFunction;		/// type of image

	drawingMode::drawingMode maskType;		/// type of mask

	std::string filepathname;	/// image path name
	std::string name;           /// image moniker

	QPoint m_ImageOffset;		/// image X,Y offset in microns
	int m_ImageFocusPosition;	/// image Z focus position in microns (absolute stage position - relative to a focus on sample frame fiducial mark top left)
private:
	ImagesContainer* m_ImagesContainer;

	QPoint m_imageIndex;
	QVector3D m_positionFiducial;
	QVector3D m_positionStage;

	QString m_FrameID;		// barcode of frame
	QString m_SubFrameID;		// subframe identifier
	QString m_subRegionID;	// Parent region identifier 
	QRect m_patternRegion;	// Parent region location in image

	QImage qt_im;				/// QT Image (shares data with opencv image)
	cv::Mat cv_im;				/// OpenCV image

	int* pImage;				/// int* image 1D array (Grayscale intensity or HSV Value)
	int* pMask;					/// int* mask image 1D array
	int* pHue;					/// int* image 1D array (Hue image)

	std::string tooltip;		/// tooltip describing image
	bool isDisplayed;			/// boolean to set if image is displayed

	cameraType::camera cameraType;

	// if the image is connected components image then add this associated information
	cv::Mat labels;			/// connected components labels
	cv::Mat stats;			/// connected components stats
	cv::Mat centroids;		/// connected components centroids

	cv::Rect imagePosition; /// position of image in relation to other containing image

	QUuid UID;
	bool isNull;
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