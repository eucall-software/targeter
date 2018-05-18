// Targeter - target identification software for EUCALL workpackage 6
// Licensed under the GPL License. See LICENSE file in the project root for full license information.
// Copyright(C) 2017  David Watts 

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "settingsdialog.h"
#include "opencv2/opencv.hpp"
#include "opencv/highgui.h"
#include "imagesContainer.h"
#include "targeterimage.h"
#include "globals.h"
#include "Camera.h"
#include "BaslerCamera.h"
#include "imageprocessing.h"
#include "findtargets.h"
#include "TextureAnalysis.h"
#include "stageControlXY.h"
#include "stageControlZ.h"
#include "xmlWriter.h"

#include <QMainWindow>
#include <QFile>
#include <QMenu>
#include <QListWidgetItem>
#include <QThread>

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
    void OpenImage();
    void SaveImage();

    void addImage(const QString &fileName, imageType::imageType type = imageType::display);
    void loadFile(const QString &fileName);
	QString getSaveFilename(targeterImage im, int& number, bool bIsCompleteImage = true);

	void getAvailablePorts();

    QImage::Format getFormat(int type);
	int getValidImageIndex();

	void addCVImage(targeterImage& tim, QString imageName= "", bool bRGBSwap = true);
    void addCVImage(cv::Mat im, QUuid UID, QString imageName= "" , bool bRGBSwap = true, imageType::imageType type = imageType::display, bool bDisplay = true, QString filename = "");

	void updateImageType(int ind, imageType::imageType type);
	
    void addQImageThumbnail(targeterImage& tim, QString imageName = "");
	QString createTooltip(targeterImage& tim, QString imageName = "");

    QImage copyImageToSquareRegion(QImage im, QColor col);

    void resizeEvent(QResizeEvent* event);
    std::vector<int> getCheckedImages();
    void resizeImagePreserve(cv::Mat& in, cv::Mat& out, int newWidth, int newHeight);

    void DebugPrintMat(cv::Mat mat);

	void showMessage(imageType::imageType, QMessageBox::Icon icn = QMessageBox::Information);
	void showMessage(QString message, QMessageBox::Icon icn = QMessageBox::Information);
		
	void updateThumbs();

	void setHistogramImage();

	void detectLines();

	void writeCentroids(targeterImage& tim, QFile& xmlFile);
	void drawCentroids(targeterImage& tim, cv::Mat& drawimage, int imageIndex=-1);
	cv::Mat drawCentroids(targeterImage& tim, cv::Mat& drawimage, bool bWriteSubImages);

	cv::Mat getHistogram();
	targeterImage getConnectedComponents(cv::Mat& im);

	void FilterRegions(targeterImage& ccim, cv::Mat& binImage, cv::Rect targetROI, double stdevMaxFactor, double stdevMinFactor, double aspectFactor);
	void FilterRegionsOnSize(targeterImage& ccim, cv::Mat& binImage, double stdevMaxFactor, double stdevMinFactor, double aspectFactor);
	void FilterRegionsOnShape(targeterImage& ccim, cv::Mat& binImage, cv::Rect targetROI);

	targeterImage createScoreImage(int& imageIndex);

	// thread functions
	void getScoreImage();
	void getTargetImage();

	// get image masked by drawn objects
	cv::Mat getDrawnImage(int index);

	cv::Mat getTargetPositions(targeterImage scoreImage, targeterImage* targetImage = NULL, int imageIndex=-1);
	cv::Mat getTargetsFromLabelledImage(targeterImage& tarCC, cv::Mat& binImage, targeterImage* targetImage = NULL, targeterImage* displayImage = NULL, int imageIndex =-1, bool bFilter = true);

	void entropyFilterImage();

	void drawShape(cv::Mat& im, drawingShape shape, cv::Scalar col);

	void createFocusStackAndMove(double minPos, double maxPos, double step, ACTIONS::action act);
	void getFocusValue(cv::Mat im, double z, ACTIONS::action act);

	cv::Mat createMosaicImage(QVector<cv::Mat> images, QVector<QPoint> indexes);
	QVector3D getMosaicPositionFromName(QString str);
	void rasterSortVectors(QVector<QPointF>& positions);
	static bool compareQPointF(const QPointF& first, const QPointF& second);
   
    // draw in window
    virtual void paintEvent(QPaintEvent* event);
    // virtual void wheelEvent(QWheelEvent * event );
	
	void createMaskImage(targeterImage* orginal_image, drawingShape shape);
    //cv::Mat maskImage(cv::Mat im, drawingShape shape);

	void deleteImage(int index, bool bDisplay = true);
	void addImageMosaic(cv::Mat& image, double focusDistance);

	void setImageDisplay(int ind);

	void consoleLog(QString strText, bool newline, bool moveToEnd, CONSOLECOLOURS::colour icn = CONSOLECOLOURS::colour::Information);
	void consoleLog(imageType::imageType type, CONSOLECOLOURS::colour icn = CONSOLECOLOURS::colour::Information);
	void consoleLog(QString strText, CONSOLECOLOURS::colour icn = CONSOLECOLOURS::colour::Information);
private:
	QThread* m_pWorkerThreadXY;
	QThread* m_pWorkerThreadZ;

	QVector<QString> m_AvailablePorts;

	QMap<QString, cv::Mat> m_MosiacImageList;

	QVector<cv::Mat> m_focusStackImages;	/// list of images used for focus stack focus finding or to make focus stack image
	QMap<double, double> m_focusStackCoarseFocusValues;	/// list of images used for focus stack focus finding or to make focus stack image
	QMap<double, double> m_focusStackFineFocusValues;	/// list of images used for focus stack focus finding or to make focus stack image
	int m_noFocusStackImages;
	double m_zdistance;
	QVector<double> m_focusValues;			// focus values to use for optimising focus routine.

	QImage imdisplay;					//This will create QImage which is shown in Qt label
	QTimer* Timer;						// A timer is needed in GUI application
	ImagesContainer m_ImagesContainer;	/// collection of all images
	StageControlXY*  m_pStageXY;
	StageControlZ* m_pStageZ;

	StageState<QPointF> m_stageStateXY;
	StageState<double> m_stageStateZ;

	QMenu m_thumb_context_menu;
	bool m_bContextMenuAction;

	int m_currentImageDisplayedIndex;
	int m_scale;

	std::unique_ptr<SettingsValues> m_settings;			
	std::unique_ptr<ExperimentalData> m_experimentalData;
	SettingsDialog m_settingsDlg;

	ImageProcessing m_ImageProcessing;
	TextureAnalysis m_TextureAnalysis;
	FindTargets m_FindTargets;
	XMLWriter xmlWriter;
	
	void deSerialiseSettings(bool fromBackup = false);
	void serialiseSettings(bool fromBackup = false);
	
	// save file history
	void fh_setCurrentFile(const QString &fileName);
	void fh_updateRecentFileActions();
	void fh_addFileListToMenu();
	QString fh_strippedName(const QString &fullFileName);

	enum { MaxRecentFiles = 5 };
	QAction *recentFileActs[MaxRecentFiles];

	QString curFile;
	QAction *separatorAct;

	// class for basler camera image capture
	std::unique_ptr<BaslerCamera> basCamera;

public slots:
	void DisplayImage();
	void DisplayImage(int index);
	void saveBackup(bool bLoad);

	void addFiducialMark(FIDUCIAL::position pos, QPoint p);

	//Display video frame in player UI
	void updateVideoImage(cv::Mat im) {
		updateQTImage(im);
	};

	void createTransformationMatrix(QVector3D topleft, QVector3D topright, QVector3D bottomleft);

	bool updateQTImage(cv::Mat img, QString name = "camera image", QAction* pAction = NULL);

	void addTargeterImage(targeterImage tim, QAction* pAction = NULL);

	void addMatImage(cv::Mat img, QString imagename, imageType::imageType type, QAction* pAction);

	void LOGCONSOLE(QString strText, bool newline, bool moveToEnd, CONSOLECOLOURS::colour icn = CONSOLECOLOURS::colour::Information) { consoleLog(strText, newline, moveToEnd, icn); };
	void LOGCONSOLE(imageType::imageType type, CONSOLECOLOURS::colour icn = CONSOLECOLOURS::colour::Information) { consoleLog(type, icn); };

	void LOGCONSOLE(QString strText, CONSOLECOLOURS::colour icn = CONSOLECOLOURS::colour::Information) { consoleLog(strText, icn); };

	void StageMovementCompleted(QString message);

	void receiveSettings();

	void StageConnectedXY(QString port);
	void StageConnectedZ(QString port);

	void enableFiducial(bool bEnable);

	double getBestFocus(double minPos, double step);
	bool getBestFocusValue(QMap<double, double> focusValues, int arraySize, double z, ACTIONS::action act);

private slots:
	void updatePositionXY(bool bFid, double x, double y);
	void updatePositionZ(bool bFid, double z);

	void ProvideContextMenu(const QPoint &pos);
	void logFeedback(int score, QString name, QString email, QString institute, QString desc);

    void disablePanButton();
    void unsetDrawingButtons(QAction* pAct);
    void setTargetArea(drawingShape shape);
	void StatusBarMessage(QString msg);

	void stageMovedXY(double x, double y, ACTIONS::action act);
	void stageMovedZ(double z, ACTIONS::action act);

	void addFocusValue(double z, double focusStrength, ACTIONS::action act);

	void moveObjective(QPoint pt);

    void on_action_Open_triggered();
	void on_action_New_triggered();
	void on_actionCorner_Detection_triggered();
	void on_actionEdge_Detection_triggered();
	void on_actionGrid_Spacing_triggered(bool checked);

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

signals:
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
