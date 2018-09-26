// Targeter - target identification software for EUCALL workpackage 6
// Licensed under the GPL License. See LICENSE file in the project root for full license information.
// Copyright(C) 2017  David Watts 

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "globals.h"
#include "settingsdialog.h"

#include "opencv2/opencv.hpp"
#include "imagesContainer.h"
#include "targeterimage.h"

#include "Camera.h"
#include "BaslerCamera.h"
#include "imageprocessing.h"
#include "findtargets.h"
#include "TextureAnalysis.h"
#include "stageControlXY.h"
#include "stageControlZ.h"
#include "xmlWriter.h"
#include "shapeannotation.h"

#include <QMainWindow>
//#include <QFile>
#include <QMessageBox>
#include <QIcon>
#include <QMenu>
#include <QListWidgetItem>
#include <QThread>
#include <QTimer>

#ifdef _CUDA_CODE_COMPILE_
#include "focusingCUDA.h"
#endif

#ifdef _HAVE_IMAGEMAGICK
#include "ImageReadWrite.h"
#endif
	
#include <pylon/PylonIncludes.h>
using namespace Pylon;

namespace Ui {
	class MainWindow;
}

/**
* Main QTMainWindow derived class for managing window display
*/
class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	void shutDownInstruments();

	void setUpSlotsSignals();

	void refreshDisplayImages();

    // image reading
    void OpenImageOrXML();
    void SaveImageOrXML();

	void saveXMLProject(QString filename);
	void openXMLProject(QString filename);

    void addImage(const QString &fileName, imageType::imageType type = imageType::display);
    void loadFile(const QString &fileName);
	QString getSaveFilename(QExplicitlySharedDataPointer<targeterImage> im, int& number, bool bIsCompleteImage = true);

	void registerFiducialMarks();

	void getAvailablePorts();
	void assignPortZ(QVector<QString> AvailablePorts, QString excludePort);

    QImage::Format getFormat(int type);
	int getValidImageIndex();

	void addCVImage(QExplicitlySharedDataPointer<targeterImage> tim, QString imageName= "", bool bRGBSwap = true);
	QUuid addCVImage(cv::Mat im, QString imageName= "" , bool bRGBSwap = true, imageType::imageType type = imageType::display, bool bDisplay = true, QString filename = "", QString jsonData ="");
	QExplicitlySharedDataPointer<targeterImage> createTargeterImage(cv::Mat im, QVector3D fiducials, QVector3D stage, QString imageName = "", bool bRGBSwap = true,
		imageType::imageType type = imageType::display, bool bDisplay = true, QString filename = "", QString jsonData = "");

	void updateImageType(int ind, imageType::imageType type);
	
    void addQImageThumbnail(QExplicitlySharedDataPointer<targeterImage> tim, QString imageName = "");
	QString createTooltip(QExplicitlySharedDataPointer<targeterImage> tim, QString imageName = "");

    QImage copyImageToSquareRegion(QImage im, QColor col);

	QString limitString(const QString& aString, int maxLength);

    void resizeEvent(QResizeEvent* event);
    std::vector<int> getCheckedImages();
    void resizeImagePreserve(cv::Mat& in, cv::Mat& out, int newWidth, int newHeight);

    void DebugPrintMat(cv::Mat mat);

	void showMessage(imageType::imageType, QMessageBox::Icon icn = QMessageBox::Information);
	void showMessage(QString message, QMessageBox::Icon icn = QMessageBox::Information);
		
	void updateThumbs();

	void setHistogramImage();

	void detectLines();

	void writeCentroids(QExplicitlySharedDataPointer<targeterImage> tim, QFile& xmlFile);
	void drawCentroids(QExplicitlySharedDataPointer<targeterImage> tim, cv::Mat& drawimage, int imageIndex=-1, bool bDrawOnImage = false);
	cv::Mat drawCentroids(QExplicitlySharedDataPointer<targeterImage> tim, cv::Mat& drawimage, bool bWriteSubImages);

	cv::Mat getHistogram();
	QExplicitlySharedDataPointer<targeterImage> getConnectedComponents(cv::Mat& im);

	void FilterRegions(QExplicitlySharedDataPointer<targeterImage> ccim, cv::Mat& binImage, cv::Rect targetROI, double stdevMaxFactor, double stdevMinFactor, double aspectFactor);
	void FilterRegionsOnSize(QExplicitlySharedDataPointer<targeterImage> ccim, cv::Mat& binImage, double stdevMaxFactor, double stdevMinFactor, double aspectFactor);
	void FilterRegionsOnShape(QExplicitlySharedDataPointer<targeterImage> ccim, cv::Mat& binImage, cv::Rect targetROI);

	QExplicitlySharedDataPointer<targeterImage> createScoreImage(int& imageIndex);
	QExplicitlySharedDataPointer<targeterImage> createScoreImage(QVector<QExplicitlySharedDataPointer<targeterImage>> targetImages,
																QExplicitlySharedDataPointer<targeterImage> testImage);	

	void getTargetLocations(QVector<QExplicitlySharedDataPointer<targeterImage>> targetImages, 
							QExplicitlySharedDataPointer<targeterImage> detectImage);

	// thread functions
	void getScoreImage();
	void getTargetImage();
	void readProjectDataFromDOM();
	void writeProjectDataToDOM();

	//void writeImageTargetstoDOM(QString parentFilename, int imageIndex);
	//void writeTargetPositionsToDOM();

	// get image masked by drawn objects
	cv::Mat getDrawnImage(int index);

	QVector<QExplicitlySharedDataPointer<targeterImage>> findTargetImages(int& imageIndex);

	cv::Mat getTargetPositions(cv::Mat scoreImage, QExplicitlySharedDataPointer<targeterImage> detectImage, int imageIndex=-1);
	cv::Mat getTargetsFromLabelledImage(QExplicitlySharedDataPointer<targeterImage> tarCC, cv::Mat& binImage, QExplicitlySharedDataPointer<targeterImage> targetImage, cv::Mat displayImage, int imageIndex =-1, bool bFilter = true);
	void trainTargetImage(QVector<QExplicitlySharedDataPointer<targeterImage>> targetImages, QExplicitlySharedDataPointer<targeterImage> parent);

	void getHistograms(cv::Mat orginal_image, cv::Mat& histIntensity, cv::Mat& histHue, bool bProcessAsGrayscale = false, bool accumulate= false);

	void entropyFilterImage();

	void drawShape(cv::Mat& im, drawingShape shape, cv::Scalar col);

	QVector3D getRelativePosition(QVector3D position);
	QVector3D getAbsolutePosition(QVector3D position);

	void createFocusStackAndMove(double bestFocus, double focusRange, double step, ACTIONS::action act, bool bUpFirst=true);
	FocusResult getFocusValue(cv::Mat& im, double z, ACTIONS::action act);

	double getBestFocusPosition(double& bestFocusValue);
	double getBestFocusRange(double bestFocus);

	cv::Mat createMosaicImage(QVector<cv::Mat> images, QVector<QPoint> indexes);
	QVector3D getMosaicPositionFromName(QString str, bool relative = true);
	void rasterSortVectors(QVector<QPointF>& positions);
	static bool compareQPointF(const QPointF& first, const QPointF& second);
   
    // draw in window
    virtual void paintEvent(QPaintEvent* event);
    // virtual void wheelEvent(QWheelEvent * event );
	
	void createMaskImage(QExplicitlySharedDataPointer<targeterImage> orginal_image, QSharedPointer<drawingShape> shape);
    //cv::Mat maskImage(cv::Mat im, drawingShape shape);

	void deleteImage(int index, bool bDisplay = true);
	void addImageMosaic(cv::Mat& image, double focusDistance);

	void setImageDisplay(int ind);

	void consoleLog(QString strText, bool newline, bool moveToEnd, CONSOLECOLOURS::colour icn = CONSOLECOLOURS::colour::Information);
	void consoleLog(imageType::imageType type, CONSOLECOLOURS::colour icn = CONSOLECOLOURS::colour::Information);
	void consoleLog(QString strText, CONSOLECOLOURS::colour icn = CONSOLECOLOURS::colour::Information);
private:
	void deSerialiseSettings(bool fromBackup = false);
	void serialiseSettings(bool fromBackup = false);

	// save file history
	void fh_setCurrentFile(const QString &fileName);
	void fh_updateRecentFileActions();
	void fh_addFileListToMenu();
	QString fh_strippedName(const QString &fullFileName);

	//////////////////// member variables ////////////////////////

	// member classes to do various tasks
	QSharedPointer<SettingsValues> m_settings;
	//QSharedPointer<ExperimentalData> m_experimentalData;

	//TargetDetectionExperiments m_experimentalData;
	QVector<ImageData> m_processedImages;
	ImageData m_currentScanImageData;
	StagePosition<double> m_focus_position_Z;

	int m_current_parent_scan_image_index;
	int m_current_scan_image_index;
	int m_current_scan_region_index;

	ImagesContainer m_ImagesContainer;		/// class to manage all image access

	SettingsDialog m_settingsDlg;			/// main settings dialog
	ShapeAnnotation m_shapeAnnotationDlg;	/// dialog to get annotation information

	ImageProcessing m_ImageProcessing;		/// class to do image processing
	TextureAnalysis m_TextureAnalysis;		/// class to do texture based image processing
	FindTargets m_FindTargets;				/// class to detect targets

#ifdef _HAVE_IMAGEMAGICK
	ImageReadWrite m_imageReadWrite;		/// class to do reading/writing of images with imagemagick
#endif

	StageControlXY*  m_pStageXY;			/// class to manage XY stage
	StageControlZ* m_pStageZ;				/// class to manage Z stage

#ifdef _CUDA_CODE_COMPILE_
	focusingCUDA m_FocusCUDA;				/// class for focus algorithms on GPU
#endif

	QDomDocument m_projectXMLDOM;

	FocusParameters m_focusSettings;		/// member variable to store focusing parameters
	
	QMap<QString, cv::Mat> m_MosiacImageList;	/// list of images scanned in mosaic

	QVector<QExplicitlySharedDataPointer<targeterImage>> m_targetImages; /// store of target images

	/// variables for file history in GUI
	enum { MaxRecentFiles = 5 };
	QAction *recentFileActs[MaxRecentFiles];
	QString curFile;
	QAction *separatorAct;

	// class for basler camera image capture
	QSharedPointer<BaslerCamera> basCamera;	/// class to manage Basler camera

	int m_currentImageDisplayedIndex;			/// which image is currently being displayed

	/// window specific member variables
	QImage imdisplay;				/// The QImage which is shown in Qt label
	QTimer m_Timer;					/// The timer used for showing wait time

									/// variables for right click menu
	QMenu m_thumb_context_menu;
	bool m_bContextMenuAction;

	QVector<QString> m_AvailablePorts;	/// member variable to store port information for stages

	/// worker thread member variables
	QThread* m_pWorkerThreadXY;
	QThread* m_pWorkerThreadZ;
	QThread* m_pWorkerThreadCUDA;

	//////////////////////////////////////////////////////

public slots:
	void logDot();
	void DisplayImage();
	void DisplayImage(int index);
	void saveBackup(bool bLoad);
	void LogProcessing(bool bStart);
	void setSamplingDistance(QSharedPointer<QPolygon> poly);

	void addFiducialMark(FIDUCIAL::position pos, QPoint p);

	//Display video frame in player UI
	void updateVideoImage(cv::Mat im);

	void startFocusThreads(cv::Mat im, double z, ACTIONS::action act);
	void addFocusValueCompleted();
//	void allFocusValuesCompleted();
	QVector<QPoint> makeIndexes(QVector<QPointF> positions);

	void createTransformationMatrix(QVector3D topleft, QVector3D topright, QVector3D bottomleft);
	void getTargetPositionsFromImage(cv::Mat& centroidsImage, cv::Mat& stats, QVector<QPoint>& pts, QVector<QRect>& rects);

	bool updateQTImage(cv::Mat img, QString name = "camera image", QAction* pAction = nullptr);

	void addTargeterImage(QExplicitlySharedDataPointer<targeterImage> tim, QAction* pAction = nullptr);

	void addMatImage(cv::Mat img, QString imagename, imageType::imageType type, QAction* pAction);

	void LOGCONSOLE(QString strText, bool newline, bool moveToEnd, CONSOLECOLOURS::colour icn = CONSOLECOLOURS::colour::Information) { 
		consoleLog(strText, newline, moveToEnd, icn); 
	};
	void LOGCONSOLE(imageType::imageType type, CONSOLECOLOURS::colour icn = CONSOLECOLOURS::colour::Information) { 
		consoleLog(type, icn); 
	};

	void LOGCONSOLE(QString strText, CONSOLECOLOURS::colour icn = CONSOLECOLOURS::colour::Information) { consoleLog(strText, icn); };

	void StageMovementCompleted(QString message);

	void receiveSettings();

	void StageConnectedXY(QString port);
	void StageConnectedZ(QString port);

	void enableFiducial(bool bEnable);

	//double getBestFocus(double minPos, double step);
private slots:
	void updatePositionXY(bool bFid, double x, double y);
	void updatePositionZ(bool bFid, double z);

	void ProvideContextMenu(const QPoint &pos);
	void logFeedback(int score, QString name, QString email, QString institute, QString desc);

    void disablePanButton();
    void unsetDrawingButtons(QAction* pAct);
    void setTargetArea(QSharedPointer<drawingShape> shape);
	void StatusBarMessage(QString msg);

	void stageMovedXY(double x, double y, ACTIONS::action act);
	void stageMovedZ(double z, ACTIONS::action act);

	void addFocusValue(FocusResult result);

	void moveObjective(QPoint pt);

    void on_action_Open_triggered();
	void on_action_New_triggered();
	void on_actionCorner_Detection_triggered();
	void on_actionEdge_Detection_triggered();
	void on_actionLaplacian_triggered();
	void on_actionGrid_Spacing_triggered(bool checked);

	void on_actionAnnotate_Shape_triggered();

	void on_action_scan_regions_triggered();

	void on_actionCreate_Image_Mosaic_triggered();

	void on_actionClick_Center_Objective_triggered(bool checked);
	void on_actionReference_fiducial_marks_triggered(bool checked);
	void on_actionClickTarget_triggered(bool checked);

	void on_actionSave_Target_Positions_triggered();

	void on_actionMask_Black_triggered();
	void on_actionMask_White_triggered();

	void on_actionEnergy_image_triggered();

	void on_actionCreate_Mask_Image_triggered();

    void onThumbImageClick(QListWidgetItem* item);

    void on_actionProcessFocusStack_triggered();

    void on_action_Save_triggered();

    void on_actionSelect_All_triggered();

    void on_actionDeselect_All_triggered();

    void on_actionGrab_Image_From_Camera_triggered();

	void on_actionGrab_Video_From_Camera_triggered(bool checked);

    void on_actionZoom_Out_triggered();

    void on_actionZoom_In_triggered();

	void on_actionDetect_lines_triggered();

	void on_actionRead_Barcode_triggered();

	void on_actionSample_White_Binary_Regions_triggered();

	void on_actionRemoveBlackPixels_triggered();

	void on_actionEntropyFilter_triggered();

    void on_actionDraw_Polygon_triggered();

    void on_actionDraw_Circle_Region_triggered();
	
    void on_actionDraw_Rectangular_Region_triggered();

	void on_actionSelect_Object_triggered();

    void on_action_Move_Image_triggered();

    void openRecentFile();

    void on_actionGet_Target_image_region_triggered();

    void on_actionSet_as_find_targets_image_triggered();

    void on_actionSet_as_Target_triggered();

    void on_actionDeleteObject_triggered();

    void on_actionFind_targets_triggered();

	void on_actionScoreImage_triggered();

	void on_actionDeleteImage_triggered();

    void on_actionSettings_triggered();

    void on_actionMergeImages_triggered();

    void on_actionThresholdImage_triggered();

	void on_actionConnected_Components_triggered();

	void on_actionFilter_Binary_Objects_triggered();

	void on_actionFind_Centers_triggered();

	void on_actionInvert_triggered();

	void on_actionCalibrate_Camera_triggered();

	void on_actionCorrectImage_triggered();

	void on_actionBackground_fit_triggered();

	void on_actionEqualise_Image_triggered();

	void on_actionTrainTarget_triggered();

signals:
	void getFocusCUDA(FocusResult res);

	void getVideo(cameraType::camera);
	void assignPorts();
	void reportCOMPORTS(QVector<QString> str);
	// call XT stage from code
	void MoveAbsoluteXY(double x, double y, ACTIONS::action act);
	void MoveRelativeXY(double x, double y, ACTIONS::action act);
	void MoveAbsoluteZ(double z, ACTIONS::action act);
	void SendCommandXY(QString cmd);
	void SetVelocityXY(double velo);
	void CalibrateXY();
	void MeasureRangeXY();
	void ConnectXY();
	void DisconnectXY();
	void AbortXY();
	void getCOMPORTS();
	void connectToPortZ(QVector<QString> AvailablePorts, QString excludePort);
	void connectToPortXY(QVector<QString> AvailablePorts, QString excludePort);

	void getPositionXY(bool isFid);
	void getPositionZ(bool isFid);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
