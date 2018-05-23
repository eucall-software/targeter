#include "BaslerCamera.h"
#include "globals.h"

#ifdef _BASLER_PYLON
#include <pylon/PylonIncludes.h>

#include <pylon/gige/BaslerGigECamera.h>

#include "opencv2/opencv.hpp"

using namespace cv;

using namespace Pylon;
using namespace Basler_GigECameraParams;
using namespace GenApi;
typedef CBaslerGigECamera Camera_t;

#endif

BaslerCamera::BaslerCamera() 
{
#ifdef _BASLER_PYLON
	// Before using any pylon methods, the pylon runtime must be initialized.
	PylonInitialize();

	pEventHandler = new CVideoEventHandler;

	pEventHandler->setParent(this);
#endif
}

BaslerCamera::~BaslerCamera()
{
	detachCameras();
}

void BaslerCamera::detachCameras()
{
#ifdef _BASLER_PYLON
	if (pOverviewCamera)
	{
		if (pOverviewCamera->IsOpen())
			pOverviewCamera->Close();

		pOverviewCamera->DestroyDevice();
	}

	if (pMicroscopeCamera)
	{
		if (pMicroscopeCamera->IsOpen())
			pMicroscopeCamera->Close();

		pMicroscopeCamera->DestroyDevice();
	}

	//pEventHandler->DestroyImageEventHandler();

	PylonTerminate();

#endif
}

bool BaslerCamera::openCamera(cameraType::camera cameraType)
{
	if (cameraType == cameraType::microscope)
	{
		try 
		{
			pMicroscopeCamera->Open();
			/*
			GenApi::CIntegerPtr pHeartbeat = pMicroscopeCamera->GetTLNodeMap().GetNode("HeartbeatTimeout");
			// set heartbeat to 600 seconds. (Note: Only GigE cameras have a "HeartbeatTimeout" node)
			if (pHeartbeat != nullptr) pHeartbeat->SetValue(1000);
			*/
			return true;
		}
		catch (GenICam::GenericException &e)
		{
			emit LOGCONSOLE("openCamera: An exception occurred opening microscope camera." + QString::fromUtf8(e.GetDescription()));
			pMicroscopeCamera->Close();
			return false;
		}
	}
	else
	{
		try
		{
			pOverviewCamera->Open();
			/*
			GenApi::CIntegerPtr pHeartbeat = pOverviewCamera->GetTLNodeMap().GetNode("HeartbeatTimeout");
			// set heartbeat to 600 seconds. (Note: Only GigE cameras have a "HeartbeatTimeout" node)
			if (pHeartbeat != nullptr) pHeartbeat->SetValue(1000);
			*/
			try
			{
				CFeaturePersistence::Load("acA2040-25gc_21799625.pfs", &(pOverviewCamera->GetNodeMap()), true);
			}
			catch (Pylon::GenericException &e)
			{
				// Error handling
				emit LOGCONSOLE("An exception occurred reading Basler settings file C:\\acA2040 - 25gc_21799625.pfs " + QString::fromUtf8(e.GetDescription()));
			}

			return true;
		}
		catch (GenICam::GenericException &e)
		{
			// Error handling.
			emit LOGCONSOLE("openCamera: An exception occurred opening overview camera." + QString::fromUtf8(e.GetDescription()));
			pOverviewCamera->Close();
			return false;
		}
	}
	return false;
}

void BaslerCamera::setCameras(QString overviewSerialNumber, QString microscopeSerialNumber)
{
#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
	
	if (pOverviewCamera== nullptr || !pOverviewCamera->IsOpen())
	{
		try
		{
			IPylonDevice* device = CTlFactory::GetInstance().CreateDevice(CDeviceInfo().SetDeviceClass(BaslerGigEDeviceClass).SetSerialNumber(overviewSerialNumber.toLocal8Bit().data()));
			pOverviewCamera = std::unique_ptr<Pylon::CInstantCamera>(new Pylon::CInstantCamera(device));
		}
		catch (GenICam::GenericException &e)
		{
			// Error handling.
			emit LOGCONSOLE("setCameras: An exception occurred creating overview camera." + QString::fromUtf8(e.GetDescription()));
		}
	}

	if (pMicroscopeCamera== nullptr || !pMicroscopeCamera->IsOpen())
	{
		try
		{
			IPylonDevice* device = CTlFactory::GetInstance().CreateDevice(CDeviceInfo().SetDeviceClass(BaslerGigEDeviceClass).SetSerialNumber(microscopeSerialNumber.toLocal8Bit().data()));
			pMicroscopeCamera = std::unique_ptr<Pylon::CInstantCamera>(new Pylon::CInstantCamera(device));
		}
		catch (GenICam::GenericException &e)
		{
			// Error handling.
			emit LOGCONSOLE("setCameras: An exception occurred creating microscope camera." + QString::fromUtf8(e.GetDescription()));
		}
	}
}
	
Pylon::CInstantCamera* BaslerCamera::getCamera(cameraType::camera cameraType)
{
	if (cameraType == cameraType::microscope)
	{
		if (openCamera(cameraType::microscope))
		{
			return pMicroscopeCamera.get();
		}
		else
		{
			emit LOGCONSOLE("getCamera: Error - Cannot open microscope camera");
			return nullptr;
		}
	}
	else
	{
		if (openCamera(cameraType::overview))
		{
			return pOverviewCamera.get();
		}
		else
		{
			emit LOGCONSOLE("getCamera: Error - Cannot open overview camera");
			return nullptr;
		}
	}
}


/**
*
*  slot to grab image using Basler pylon supported camera
*
* @author    David Watts
* @since     2017/03/07
*
* FullName   MainWindow::on_actionGrab_Image_From_Camera_triggered
* Qualifier
* @return    void
* Access     private
*/
cv::Mat BaslerCamera::grabImage(cameraType::camera cameraType, bool bCalledInLoop)
{
#ifdef _BASLER_PYLON

#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	Pylon::CInstantCamera* pCamera = nullptr;

	if(!bCalledInLoop)
		pCamera = getCamera(cameraType);
	else
	{
		if (cameraType == cameraType::microscope)
			pCamera = pMicroscopeCamera.get();
		else
			pCamera = pOverviewCamera.get();
	}

	if (pCamera == nullptr)
	{
		QString s = CAMERATYPE(cameraType);
		emit LOGCONSOLE("grabImage: Error - camera "+ s + " invalid");
		return cv::Mat();
	}

	try
	{
		CGrabResultPtr ptrGrabResult;

		pCamera->GrabOne(500, ptrGrabResult, TimeoutHandling_ThrowException);

		if (ptrGrabResult->GrabSucceeded())
		{
			CPylonImage target;

			CImageFormatConverter converter;
			converter.OutputPixelFormat = PixelType_BGR8packed;
			converter.OutputBitAlignment = OutputBitAlignment_MsbAligned;

			converter.Convert(target, ptrGrabResult);

			// target data is on stack therefore local copy, need to clone image object before storing
			cv::Mat image(target.GetWidth(), target.GetHeight(), CV_8UC3, target.GetBuffer(), cv::Mat::AUTO_STEP);

			if (image.empty())
			{
				emit LOGCONSOLE("grabImage: Unable to convert image to cv::mat");
				return cv::Mat();
			}

			emit LOGCONSOLE("grabImage: Image captured");

			if (!bCalledInLoop)
				pCamera->Close();

			return image.clone();
		}
		else
		{
			emit LOGCONSOLE("grabImage: Error - " + QString::number(ptrGrabResult->GetErrorCode()) + " " + ptrGrabResult->GetErrorDescription());
		}
	}
	catch (const GenericException &e)
	{
		// Error handling.
		emit LOGCONSOLE("grabImage: An exception occurred " + QString::fromUtf8(e.GetDescription()));
		emit LOGCONSOLE("grabImage: Camera not configured properly, is it on? maybe the IP address is wrong");
	}

	if (!bCalledInLoop)
		pCamera->Close();

	return cv::Mat();
#endif
}

/*
GenApi::CIntegerPtr width(pCamera->GetNodeMap().GetNode("Width"));
GenApi::CIntegerPtr height(pCamera->GetNodeMap().GetNode("Height"));
Mat cv_img(width->GetValue(), height->GetValue(), CV_8UC3);

pCamera->StartGrabbing();

CPylonImage image;
CImageFormatConverter fc;
fc.OutputPixelFormat = PixelType_RGB8packed;

while (pCamera->IsGrabbing()) 
{
	pCamera->RetrieveResult(5000, ptrGrabResult, TimeoutHandling_ThrowException);

	if (ptrGrabResult->GrabSucceeded()) 
	{

		fc.Convert(image, ptrGrabResult);

		//cv_img = cv::Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC3, (uint8_t*)image.GetBuffer());

		QImage QtImage((uint8_t*)image.GetBuffer(), ptrGrabResult->GetWidth(), ptrGrabResult->GetHeight(), QImage::Format_RGB888);

		//ui->display_image->setImage(QtImage);

		emit processedImage(QtImage);
	}
}

if (pCamera->IsOpen())
pCamera->Close();

pCamera->DestroyDevice();
*/

void BaslerCamera::grabVideo(cameraType::camera cameraType)
{
#ifdef _BASLER_PYLON

#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
	Pylon::CInstantCamera* pCamera = getCamera(cameraType);

	if (pCamera != nullptr)
	{
		int delay = (1000 / 60);

		// The parameter MaxNumBuffer can be used to control the count of buffers
		// allocated for grabbing. The default value of this parameter is 10.
		pCamera->MaxNumBuffer = 10;

		// Start the grabbing of c_countOfImagesToGrab images.
		// The camera device is parameterized with a default configuration which
		// sets up free-running continuous acquisition.

		// This smart pointer will receive the grab result data.
		CGrabResultPtr ptrGrabResult;

		//camera.GrabOne(5000,ptrGrabResult,TimeoutHandling_ThrowException);

		static const uint32_t c_countOfImagesToGrab = 0;

		//namedWindow("CV_Image", WINDOW_AUTOSIZE);

		pCamera->RegisterImageEventHandler(pEventHandler, RegistrationMode_ReplaceAll, Cleanup_None);

		try
		{
			pCamera->StartGrabbing(GrabStrategy_OneByOne, GrabLoop_ProvidedByInstantCamera);
		}
		catch (GenICam::GenericException &e)
		{
			// Error handling.
			emit LOGCONSOLE("grabVideo: An exception occurred - " + QString::fromUtf8(e.GetDescription()));

			stopGrabbing();
		}
	}
	else
	{
		QString s = CAMERATYPE(cameraType);
		emit LOGCONSOLE("grabVideo: " + s + " camera is NULL (not initialised)");
	}
#endif
}

void BaslerCamera::stopGrabbing()
{
	emit LOGCONSOLE("stopGrabbing called");

	if(pMicroscopeCamera != nullptr)
		pMicroscopeCamera->StopGrabbing();
	if(pOverviewCamera != nullptr)
		pOverviewCamera->StopGrabbing();

	if(pMicroscopeCamera != nullptr)
		pMicroscopeCamera->Close();
	if(pOverviewCamera != nullptr)
		pOverviewCamera->Close();
}

/**
*
*  slot to grab image using Basler pylon supported camera
*
* @author    David Watts
* @since     2017/03/07
*
* FullName   BaslerCamera::on_actionGrab_Image_From_Camera_triggered
* Qualifier
* @return    void
* Access     private
*/
//void BaslerCamera::grabVideo2()
//{
//#ifdef _BASLER_PYLON
//
//#ifdef DEBUGPRINT
//	qDebug() << "Function Name: " << Q_FUNC_INFO;
//#endif
//	
//	try
//	{
//		int delay = (1000 / 60);
//
//		// The parameter MaxNumBuffer can be used to control the count of buffers
//		// allocated for grabbing. The default value of this parameter is 10.
//		pCamera->MaxNumBuffer = 5;
//
//		// Start the grabbing of c_countOfImagesToGrab images.
//		// The camera device is parameterized with a default configuration which
//		// sets up free-running continuous acquisition.
//
//		// This smart pointer will receive the grab result data.
//		CGrabResultPtr ptrGrabResult;
//
//		//camera.GrabOne(5000,ptrGrabResult,TimeoutHandling_ThrowException);
//
//		static const uint32_t c_countOfImagesToGrab = 30;
//
//		pCamera->StartGrabbing(c_countOfImagesToGrab);
//
//		// Camera.StopGrabbing() is called automatically by the RetrieveResult() method
//		// when c_countOfImagesToGrab images have been retrieved.
//		while (pCamera->IsGrabbing())
//		{
//			pCamera->RetrieveResult(5000, ptrGrabResult, TimeoutHandling_ThrowException);
//
//			// Image grabbed successfully?
//			if (ptrGrabResult->GrabSucceeded())
//			{
//				CPylonImage target;
//
//				CImageFormatConverter converter;
//				converter.OutputPixelFormat = PixelType_BGR8packed;
//				converter.OutputBitAlignment = OutputBitAlignment_MsbAligned;
//
//				converter.Convert(target, ptrGrabResult);
//
//				//there are 2 way to create a Qimage.
//				// QImage* QtImage= new QImage((uchar*)frame.data, frame.cols, frame.rows,QImage::Format_RGB888);
//
//				int w = target.GetWidth();
//				int h = target.GetHeight();
//
//				DBOUT("Image size: " << w << " " << h << std::endl);
//
//				// target data is on stack therefore local copy, need to clone image object before storing
//				cv::Mat image(w, h, CV_8UC3, target.GetBuffer(), cv::Mat::AUTO_STEP);
//
//				if (image.empty())
//				{
//					DBOUT("Unable to convert image to cv::mat");
//					return;
//				}
//				else
//				{
//					DBOUT("Image captured" << std::endl);
//
//					//return image.clone();
//
//					//m_ImagesContainer.m_Images.push_back(tim);
//
//					QImage QtImage((uint8_t*)target.GetBuffer(), ptrGrabResult->GetWidth(), ptrGrabResult->GetHeight(), QImage::Format_RGB888);
//
//					//ui->display_image->setImage(QtImage);
//
//					emit processedImage(QtImage);
//
//					//emit processedImage(QtImage);
//					this->msleep(delay);
//
//					
//				}
//			}
//
//			if (pCamera->IsOpen())
//				pCamera->Close();
//
//			pCamera->DestroyDevice();
//		}
//
//	}  //while
//	catch (GenICam::GenericException &e)
//	{
//		// Error handling.
//		DBOUT("An exception occurred." << std::endl
//			<< e.GetDescription() << std::endl);
//	}
//	
//	
//	VideoCapture cap(2); // open the default camera
//	if (!cap.isOpened())  // check if we succeeded
//		return;
//
//	//Mat edges;
//	//namedWindow("edges", 1);
//	//for (int i=0;i<10;i++)
//	//{
//	//	Mat frame;
//	//	cap >> frame; // get a new frame from camera
//	//
//	//	imshow("edges", frame);
//
//	//	if (waitKey(30) >= 0) 
//	//		break;
//	//}
//	
//#endif
//}
