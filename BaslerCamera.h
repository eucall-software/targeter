#ifndef BASCAM_H
#define BASCAM_H

#include "opencv2/opencv.hpp"
#include "globals.h"

#include <QString>
#include <QImage>


#include <pylon/PylonIncludes.h>

using namespace Pylon;

class CVideoEventHandler;

class BaslerCamera : public QObject
{
	Q_OBJECT
private:
	int frameRate;
	
	std::unique_ptr<Pylon::CInstantCamera> pOverviewCamera = nullptr;
	std::unique_ptr<Pylon::CInstantCamera> pMicroscopeCamera = nullptr;

public:

	BaslerCamera();
	~BaslerCamera();

	void detachCameras();

	CVideoEventHandler* pEventHandler;

	bool isOverviewCameraEmpty() { return pOverviewCamera == nullptr; };
	bool isMicroscopeCameraEmpty() { return pOverviewCamera == nullptr; };

	bool openCamera(cameraType::camera cameraType);
	Pylon::CInstantCamera*  getCamera(cameraType::camera cameraType);

	cv::Mat grabImage(cameraType::camera cameraType = cameraType::overview, bool bCalledInLoop = false);
	void setCameras(QString overviewSerialNumber, QString microscopeSerialNumber);

	void grabVideo(cameraType::camera cameraType = cameraType::overview);
	void stopGrabbing();

	void sendImage(cv::Mat cv_im) {
		emit processedImage(cv_im);
	}

signals:
	//Signal to output frame to be displayed
	void processedImage(cv::Mat image);
	void LOGCONSOLE(QString strText, CONSOLECOLOURS::colour col = CONSOLECOLOURS::colour::Information);

};

class CVideoEventHandler : public CImageEventHandler
{
private:
	BaslerCamera* pParent;

public:
	void setParent(BaslerCamera* pCam) { pParent = pCam; };

	void CVideoEventHandler::OnImageGrabbed(CInstantCamera& camera, const CGrabResultPtr& ptrGrabResult)
	{
		CPylonImage image;
		CImageFormatConverter fc;
		fc.OutputPixelFormat = PixelType_RGB8packed;

		fc.Convert(image, ptrGrabResult);

		cv::Mat cv_img = cv::Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC3, (uint8_t*)image.GetBuffer());

		pParent->sendImage(cv_img.clone());
	}
};

#endif