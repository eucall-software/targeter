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
#include "globals.h"

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
	void addImageEx(cv::Mat im, QUuid UIDParent, imageType::imageType type, std::string descriptiveName = "", std::string tooltip = "", std::string filename = "");
	
	void addImage(cv::Mat im);

	cv::Mat& getImage();

	void createQTImage(bool bRGBSwap = true);
	
	QImage& getQTImage();

	void setImageType(imageType::imageType type) { imageFunction = type; };	// name of function which created image

	imageType::imageType getImageFunction() { return imageFunction; };

	std::vector<QUuid>& getFriendImageArray() {return m_FriendIDs;};

	// derived images - index to other 
	void addFriendID(QUuid uid) { m_FriendIDs.push_back(uid); };
	void addFriendID(const std::vector<QUuid>& to_add) { m_FriendIDs.insert(std::end(m_FriendIDs), std::begin(to_add), std::end(to_add)); };

	int getFriendArrayIndexOfType(imageType::imageType imageFunction);

	bool removeFriendID(QUuid ID);
	void removeFriendIDs(const std::vector<QUuid>& to_remove);
	bool hasFriendID(QUuid ID);
	std::vector<QUuid>::iterator getFriend(QUuid ID);

	std::string getName() {	return name; };
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
	cv::Mat& getLabelsImage() {	return labels;	};
	cv::Mat& getStatsImage() {	return stats;	};
	cv::Mat& getCentroidsImage() {	return centroids; };
	cv::Rect& getImagePosition() { return imagePosition; };
	cameraType::camera getCameraType() { return cameraType; };
	
	targeterImage& getGlobalImage(int index);

	//setters
	void setLabelsImage(cv::Mat im) {labels = im;};
	void setStatsImage(cv::Mat im) {stats = im;};
	void setCentroidsImage(cv::Mat im) {centroids = im;};
	void setImagePosition(cv::Rect r) { imagePosition = r; };
	void setCameraType(cameraType::camera cam) { cameraType = cam; };

	// functions for dealing with mask images	/////////////////////////////////////
	void setMaskType(drawingMode::drawingMode mode) { maskType = mode; };

	drawingMode::drawingMode getMaskType() { return maskType; };

public:		// public properties
	bool IsGray;

	imageType::imageType imageFunction;		/// type of image

	drawingMode::drawingMode maskType;		/// type of mask

	std::string filepathname;	/// image path name
	std::string name;           /// image moniker

	QPoint m_ImageOffset;		/// image X,Y offset in microns
	int m_ImageFocusPosition;	/// image Z focus position in microns (absolute stage position - relative to a focus on sample frame fiducial mark top left)

private:
	ImagesContainer* m_ImagesContainer;

	std::vector<QUuid> m_FriendIDs;	    /// array index of images that are the result of processing this image (eg. mask images, target images, ccimages)
	
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