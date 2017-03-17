#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "settingsdialog.h"

#include <QMainWindow>
#include <QListWidgetItem>
#include <QMenu>
#include "opencv2/opencv.hpp"
#include "opencv/highgui.h"
#include "imagesContainer.h"
#include "targeterimage.h"
#include "globals.h"
#include <QFile>

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

public slots:    // A slot or function is defined which will be intiated by timer
    void DisplayImage();


public:
#ifdef PYLON
    Pylon::PylonAutoInitTerm autoInitTerm;
#endif

    // image reading
    void OpenImage();
    void SaveImage();

    void addImage(const QString &fileName, imageType::imageType type = imageType::display);
    void loadFile(const QString &fileName);

    QImage::Format getFormat(int type);
	int getValidImageIndex();

	void addCVImage(targeterImage& tim, QString imageName, bool bRGBSwap);
    void addCVImage(cv::Mat im, QString imageName = "", bool bRGBSwap = true, imageType::imageType type = imageType::display, bool bDisplay = true);

	void updateImageType(int ind, imageType::imageType type);
	
    void addQImageThumbnail(QImage& qim, QString imageName = "", imageType::imageType type = imageType::display);

    QImage copyImageToSquareRegion(QImage im, QColor col);

    void resizeEvent(QResizeEvent* event);
    std::vector<int> getCheckedImages();
    void resizeImagePreserve(cv::Mat& in, cv::Mat& out, int newWidth, int newHeight);

    explicit MainWindow(QWidget *parent = 0);

	~MainWindow();

    void DebugPrintMat(cv::Mat mat);

	void showMessage(imageType::imageType, QMessageBox::Icon icn = QMessageBox::Warning);
	void showMessage(QString message, QMessageBox::Icon icn = QMessageBox::Warning);
		
	void updateThumbs(int index = -1);

	void setHistogramImage();

	void writeCentroids(targeterImage& tim, QFile& xmlFile);

	cv::Mat getHistogram();
	targeterImage MainWindow::getConnectedComponents(cv::Mat& im);
	void MainWindow::drawCentroids(targeterImage& tim, cv::Mat& drawimage);

	cv::Mat createScoreImage();
   
    // draw in window
    virtual void paintEvent(QPaintEvent* event);
    // virtual void wheelEvent(QWheelEvent * event );

	void createMaskImage(cv::Mat im, drawingShape shape);
    //cv::Mat maskImage(cv::Mat im, drawingShape shape);

	void deleteImage(int index, bool bDisplay = true);
private:
	QImage imdisplay;					//This will create QImage which is shown in Qt label
	QTimer* Timer;						// A timer is needed in GUI application
	ImagesContainer m_ImagesContainer;	/// collection of all images

	QMenu m_thumb_context_menu;
	bool m_bContextMenuAction;

	int m_currentImageDisplayedIndex;
	int m_scale;

	SettingsValues m_settings;			
	SettingsDialog m_settingsDlg;

	// save file history
	void fh_setCurrentFile(const QString &fileName);
	void fh_updateRecentFileActions();
	void fh_addFileListToMenu();
	QString fh_strippedName(const QString &fullFileName);

	enum { MaxRecentFiles = 5 };
	QAction *recentFileActs[MaxRecentFiles];

	QString curFile;
	QAction *separatorAct;

private slots:

	void ProvideContextMenu(const QPoint &pos);

    void disablePanButton();
    void unsetDrawingButtons();
    void setTargetArea(drawingShape shape);

    void on_action_Open_triggered();

    void onThumbImageClick(QListWidgetItem* item);

    void onImageChecked(QListWidgetItem* item);

    void on_actionProcessFocusStack_triggered();

    void on_action_Save_triggered();

    void on_actionSelect_All_triggered();

    void on_actionDeselect_All_triggered();

    void on_actionGrab_Image_From_Camera_triggered();

    void on_actionZoom_Out_triggered();

    void on_actionZoom_In_triggered();

    void on_actionDraw_Polygon_triggered();

    void on_actionDraw_Circle_Region_triggered();

    void on_actionDraw_Rectangular_Region_triggered();

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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
