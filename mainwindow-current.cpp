// Targeter - target identification software for EUCALL workpackage 6
// Licensed under the GPL License. See LICENSE file in the project root for full license information.
// Copyright(C) 2017  David Watts 
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FocusStack.h"
#include "opencvtoqt.h"
#include "globals.h"
#include "Settings.h"
#include "settingsdialog.h"
#include "findtargets.h"
#include "imageprocessing.h"
#include "HelperFunctions.h"
#include "imagesContainer.h"
#include "targeterimage.h"
#include "BaslerCamera.h"

//#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>

// end Qconcurent stuff
#include <QTimer>
#include <QFile>
#include <QFileDialog>
#include <QStringList>
#include <QDebug>
#include <QPainter>
#include <QWheelEvent>
#include <QSettings>
#include <QListWidgetItem>
#include <QBitmap>
#include <cmath>
#include <QScrollBar>
#include <QPlainTextEdit>

#include "opencv2/core.hpp"
#include "opencv/highgui.h"
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/video.hpp"


using namespace cv;
using namespace std;
using namespace QtConcurrent;

/*
    QIcon targeterIcon;
    try
    {
      targeterIcon.addFile(":icons/24/targeter.png", QSize(24, 24));
      QIcon deleteIcon = QIcon::fromTheme("edit-delete");

      ui->actionProcessFocusStack->setIcon(targeterIcon);
      ui->actionDelete_Selected_Images->setIcon(deleteIcon);

    }
    catch( cv::Exception& e )
    {
        const char* err_msg = e.what();
        std::cout << "exception caught: " << err_msg << std::endl;
    }
*/

/**
*
*  class constructor: sets up slots, initializes variables, gets serialised settings values
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::MainWindow
* Qualifier  : QMainWindow(parent), ui(new Ui::MainWindow)
* @param     QWidget * parent 
* @return    
* Access     public 
*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
    //m_CurrentQImage = NULL;
    this->m_scale = 1;

    ui->setupUi(this);

	// to send these data types over signals slots mechanism
	qRegisterMetaType<cv::Mat>("cv::Mat");
	qRegisterMetaType<QVector<QString> >("QVector<QString>");
	
    ui->action_Open->setIcon(this->style()->standardIcon(QStyle::SP_DialogOpenButton));
    ui->action_Save->setIcon(this->style()->standardIcon(QStyle::SP_DialogSaveButton));
	ui->action_New->setIcon(this->style()->standardIcon(QStyle::SP_FileDialogNewFolder));

    ui->ImageThumbList->setStyleSheet("QVectorWidget { background-color: "+QApplication::palette().color(QPalette::Window).name()+";}");
    //{background-color:red; border: 1px solid red }

    QPalette palette = ui->ImageThumbList->palette();

    palette.setColor(ui->ImageThumbList->backgroundRole(), ui->display_image->palette().color(QWidget::backgroundRole()));
    palette.setColor(ui->ImageThumbList->foregroundRole(), ui->display_image->palette().color(QWidget::backgroundRole()));

    ui->ImageThumbList->setAutoFillBackground(true);
    ui->ImageThumbList->setPalette(palette);

	qRegisterMetaType<CONSOLECOLOURS::colour>("CONSOLECOLOURS::colour");

	basCamera = make_unique<BaslerCamera>();

	m_settings = make_unique<SettingsValues>();

	basCamera->setCameras(QString("21799625"), QString("21799596"));

	connect(basCamera.get(), SIGNAL(processedImage(cv::Mat)), this, SLOT(updateQTImage(cv::Mat)));
	
	ui->ImageThumbList->setContextMenuPolicy(Qt::CustomContextMenu);

	// set up context menu
	m_thumb_context_menu.toolTipsVisible();

	m_thumb_context_menu.addAction(ui->actionSet_as_Target);
	m_thumb_context_menu.addAction(ui->actionSet_as_find_targets_image);
	m_thumb_context_menu.addAction(ui->actionDeleteImage);

	// set up scrolling text window with 2 lines 
	ui->consoleDisplay->ensureCursorVisible();
	ui->consoleDisplay->setReadOnly(true);

	//QFontMetrics m(m_textEdit->font());
	//int RowHeight = m.lineSpacing();

	//ui->consoleDisplay->setStyleSheet("QPlainTextEdit:focus{max-height: 400px}");
	
	QPalette p = ui->consoleDisplay->palette();
	p.setColor(QPalette::Base, QColor(80, 80, 80));
	p.setColor(QPalette::Text, Qt::white);
	ui->consoleDisplay->setPalette(p);
	//ui->consoleDisplay->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
	ui->consoleDisplay->setFocusPolicy(Qt::ClickFocus);

	//m_editScrollBar->setSingleStep(RowHeight);

	// add to toolbar
	//ui->toolBarEdit->addWidget(m_textEdit);

	//m_textEdit->resize(m_textEdit->width(), 3 * RowHeight);
	//ui->toolBarEdit->resize(m_textEdit->width(), 4 * RowHeight);

	//m_textEdit->setMaximumHeight(200 * RowHeight);

	consoleLog("Welcome to", CONSOLECOLOURS::colour::Information);
	consoleLog("Targeter", true, true, CONSOLECOLOURS::colour::Information);

	fh_addFileListToMenu();

	m_bContextMenuAction = false;

	// get settings from serialised file
	deSerialiseSettings();

	m_settingsDlg.create(m_settings.get());

	QString XMLfilename = m_settings->s_project_FilenamePrefix + m_settings->s_project_Barcode + ".xml";

	xmlWriter.openForWrite(XMLfilename);

	// set display to point to image container
	ui->display_image->setImageContainerPointer(&m_ImagesContainer);

	setUpSlotsSignals();

	// set up stages
	//emit m_pMicroscopeStages.getAvailablePorts();

	//emit m_pMicroscopeStages.assignPorts();
}

void MainWindow::logFeedback(int score, QString name, QString email, QString institute, QString desc)
{
	XMLWriter logWriter;

	connect(&logWriter, SIGNAL(LOGCONSOLE(QString, CONSOLECOLOURS::colour)), this, SLOT(LOGCONSOLE(QString, CONSOLECOLOURS::colour)));


	logWriter.openForAppend("feedback.xml");

	logWriter.appendFeedback(score, name, email, institute, desc);
}

void MainWindow::setUpSlotsSignals()
{
	m_pMicroscopeStages  = new StageManager;
	m_pWorkerThread = new QThread;

	// handle thumbnail clicks
	connect(ui->ImageThumbList, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(ProvideContextMenu(const QPoint &)));
	connect(ui->ImageThumbList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onThumbImageClick(QListWidgetItem*)));

	// slots for communication from printqlabel class
	connect(ui->display_image, SIGNAL(disablePanButton()), this, SLOT(disablePanButton()));
	connect(ui->display_image, SIGNAL(setTargetArea(drawingShape)), this, SLOT(setTargetArea(drawingShape)));
	connect(ui->display_image, SIGNAL(unsetDrawingButtons()), this, SLOT(unsetDrawingButtons()));
	connect(ui->display_image, SIGNAL(StatusBarMessage(QString)), this, SLOT(StatusBarMessage(QString)));
	connect(ui->display_image, SIGNAL(addFiducialMark(QPoint)), this, SLOT(addFiducialMark(QPoint)));
	connect(ui->display_image, SIGNAL(moveObjective(QPoint)), this, SLOT(moveObjective(QPoint)));

	// slot to get values back from modeless dialog
	connect(&m_settingsDlg, SIGNAL(sendSettings()), this, SLOT(receiveSettings()));
	connect(&m_settingsDlg, SIGNAL(logFeedback(int, QString, QString, QString, QString)), this, SLOT(logFeedback(int, QString, QString, QString, QString)));

	// logging from Image Processing functions run in separate thread
	connect(&m_ImageProcessing, SIGNAL(LOGCONSOLE(QString, CONSOLECOLOURS::colour)), this, SLOT(LOGCONSOLE(QString, CONSOLECOLOURS::colour)));

	// make stage control object a worker thread object
	m_pMicroscopeStages->moveToThread(m_pWorkerThread);

	// Marzhauser stage commands called from settings dialog
	connect(&m_settingsDlg, SIGNAL(MoveAbsoluteXY(double, double)), m_pMicroscopeStages, SLOT(MoveAbsoluteXY(double, double)));
	connect(&m_settingsDlg, SIGNAL(MoveRelativeXY(double, double)), m_pMicroscopeStages, SLOT(MoveRelativeXY(double, double)));
	connect(&m_settingsDlg, SIGNAL(SendCommandXY(QString)), m_pMicroscopeStages, SLOT(SendCommandXY(QString)));
	connect(&m_settingsDlg, SIGNAL(SetVelocityXY(double)), m_pMicroscopeStages, SLOT(SetVelocityXY(double)));
	connect(&m_settingsDlg, SIGNAL(CalibrateXY()), m_pMicroscopeStages, SLOT(CalibrateXY()));
	connect(&m_settingsDlg, SIGNAL(MeasureRangeXY()), m_pMicroscopeStages, SLOT(MeasureRangeXY()));
	connect(&m_settingsDlg, SIGNAL(ConnectXY()), m_pMicroscopeStages, SLOT(ConnectXY()));
	connect(&m_settingsDlg, SIGNAL(DisconnectXY()), m_pMicroscopeStages, SLOT(DisconnectXY()));
	connect(&m_settingsDlg, SIGNAL(AbortXY()), m_pMicroscopeStages, SLOT(AbortXY()));
	connect(&m_settingsDlg, SIGNAL(SetJoyStickXY(bool)), m_pMicroscopeStages, SLOT(SetJoystickXY(bool)));
	connect(&m_settingsDlg, SIGNAL(LOGCONSOLE(QString, CONSOLECOLOURS::colour)), this, SLOT(LOGCONSOLE(QString, CONSOLECOLOURS::colour)));

	connect(m_settingsDlg.getStagePanel(), SIGNAL(mouseDownPoint(double, double)), m_pMicroscopeStages, SLOT(goXY(double, double)));

	connect(&m_settingsDlg, SIGNAL(getCOMPORTS()), m_pMicroscopeStages, SLOT(getAvailablePorts()));
	connect(m_pMicroscopeStages, SIGNAL(reportCOMPORTS(QVector<QString>)), &m_settingsDlg, SLOT(updateCOMPORTS(QVector<QString>)));

	// Marzhauser stage commands called from main program
	connect(this, SIGNAL(MoveAbsoluteXY(double, double)), m_pMicroscopeStages, SLOT(MoveAbsoluteXY(double, double)));
	connect(this, SIGNAL(MoveRelativeXY(double, double)), m_pMicroscopeStages, SLOT(MoveRelativeXY(double, double)));
	connect(this, SIGNAL(SendCommandXY(QString)), m_pMicroscopeStages, SLOT(SendCommandXY(QString)));
	connect(this, SIGNAL(SetVelocityXY(double)), m_pMicroscopeStages, SLOT(SetVelocityXY(double)));
	connect(this, SIGNAL(CalibrateXY()), m_pMicroscopeStages, SLOT(CalibrateXY()));
	connect(this, SIGNAL(MeasureRangeXY()), m_pMicroscopeStages, SLOT(MeasureRangeXY()));
	connect(this, SIGNAL(ConnectXY()), m_pMicroscopeStages, SLOT(ConnectXY()));
	connect(this, SIGNAL(DisconnectXY()), m_pMicroscopeStages, SLOT(DisconnectXY()));
	connect(this, SIGNAL(AbortXY()), m_pMicroscopeStages, SLOT(AbortXY()));

	//	connect(&m_settingsDlg, SIGNAL(serialiseSettings(SettingsValues)), this, SLOT(serialiseSettings(SettingsValues)));
	connect(m_pMicroscopeStages, SIGNAL(LOGCONSOLE(QString, CONSOLECOLOURS::colour)), this, SLOT(LOGCONSOLE(QString, CONSOLECOLOURS::colour)));
	connect(m_pMicroscopeStages, SIGNAL(ACTIONCOMPLETED(QString)), this, SLOT(StageMovementCompleted(QString)));
	connect(m_pMicroscopeStages, SIGNAL(STAGECONNECTED(bool, QString)), this, SLOT(StageConnected(bool, QString)));
	connect(&xmlWriter, SIGNAL(LOGCONSOLE(QString, CONSOLECOLOURS::colour)), this, SLOT(LOGCONSOLE(QString, CONSOLECOLOURS::colour)));

	// clean up
	connect(m_pWorkerThread, SIGNAL(finished()), m_pMicroscopeStages, SLOT(deleteLater()));

	m_pWorkerThread->start();
}

void MainWindow::StageConnected(bool isXY, QString COMPORT)
{
	m_settingsDlg.updateCONNECTPORT(isXY, COMPORT);
}

void MainWindow::StageMovementCompleted(QString message)
{
	consoleLog(message, CONSOLECOLOURS::colour::Information);

	QApplication::restoreOverrideCursor();
}

/**
*
*  class destructor, serializes settings values
*
* @author    David Watts
* @since     2017/03/07
*
* FullName   MainWindow::~MainWindow
* Qualifier
* @return
* Access     public
*/
MainWindow::~MainWindow()
{
#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	serialiseSettings();

	delete ui;

	m_ImagesContainer.freeImages();

	m_pWorkerThread->quit();
	m_pWorkerThread->wait();
}

void MainWindow::addTargeterImage(targeterImage tim, QAction* pAction)
{
	addCVImage(tim, NULL, true);

	if (pAction != NULL)
		pAction->setChecked(false);
}

void MainWindow::addMatImage(cv::Mat img, QString imagename, imageType::imageType type, QAction* pAction)
{
	addCVImage(img, QUuid::QUuid(), imagename, true, type, true);

	if (pAction != NULL)
		pAction->setChecked(false);
}

bool MainWindow::updateQTImage(cv::Mat img, QString imagename, imageType::imageType type, QAction* pAction)
{
	// update last cv image trigger show image on paint control
	targeterImage* pTar = m_ImagesContainer.getLastImagePtr();
	
	if (pTar == NULL)
	{
		addCVImage(img.clone(), imagename);

		pTar = m_ImagesContainer.getLastImagePtr();
	}
	else
		pTar->addImage(img);

	// sets the last image as the one to be displayed
	ui->display_image->setImageIndex(m_ImagesContainer.getNumImages()-1);

	if (pAction != NULL)
		return pAction->isChecked();
	else
		return false;
}

void MainWindow::serialiseSettings()
{
	QFile file("targetter_settings.dat");

	if (file.open(QIODevice::WriteOnly))
	{
		QDataStream out(&file);   // we will serialize the data into the file

		m_settings->serialize(out);

		file.close();
	}
}

void MainWindow::deSerialiseSettings()
{
	QFile file("targetter_settings.dat");

	if (file.open(QIODevice::ReadOnly)) {
		QDataStream in(&file);   // we will serialize the data into the file
		m_settings->deserialize(in);
	}
	else
	{
		m_settings->initialize(); 
	}

	file.close();
}

/**
*
* writes debug information into application console  
*
* @author    David Watts
* @since     2017/04/03
* 
* FullName   MainWindow::consoleLog
* Qualifier 
* @param     QString strText 
* @param     QMessageBox::Icon icn 
* @return    void
* Access     public 
*/
void MainWindow::consoleLog(QString strText, CONSOLECOLOURS::colour icn)
{
	consoleLog(strText, true, true, icn);
}

void MainWindow::consoleLog(QString strText, bool newline, bool moveToEnd, CONSOLECOLOURS::colour icn)
{
	QString msg = "<p>";

	//QPalette p = ui->consoleDisplay->palette();

	if (icn == CONSOLECOLOURS::Warning)
		msg = "<font color=\"yellow\">";
	if (icn == CONSOLECOLOURS::Data)
		msg = "<font color=\"yellow\">";
	else if (icn == CONSOLECOLOURS::Question)
		msg = "<font color=\"green\">";
	else if (icn == CONSOLECOLOURS::Critical)
		msg = "<font color=\"red\">";
	else if (icn == CONSOLECOLOURS::Information)
		msg = "<font color=\"white\">";
	else
		msg = "<font color=\"white\">";

	msg += strText;

	msg += "</font></p>";
	
	QMetaObject::invokeMethod(ui->consoleDisplay, "appendHtml", Qt::QueuedConnection, Q_ARG(QString, msg));

	//ui->consoleDisplay->appendHtml(msg);	// output string
	/*
	QTextCursor c = ui->consoleDisplay->textCursor();

	if (moveToEnd)
		c.movePosition(QTextCursor::End);
	else
		c.movePosition(QTextCursor::Start);
		

	ui->consoleDisplay->setTextCursor(c);
	*/
}


/**
*
*  writes debug information into application console  
*
* @author    David Watts
* @since     2017/04/03
* 
* FullName   MainWindow::consoleLog
* Qualifier 
* @param     imageType::imageType type 
* @param     QMessageBox::Icon icn 
* @return    void
* Access     public 
*/
void MainWindow::consoleLog(imageType::imageType type, CONSOLECOLOURS::colour icn)
{
	QString msg("A image of type");

	if (type == imageType::mask)
		msg += " mask ";
	else if (type == imageType::target)
		msg += " target ";
	else if (type == imageType::test)
		msg += " test ";
	else if (type == imageType::roi)
		msg += " region of interest ";
	else if (type == imageType::cclabels)
		msg += " connected components ";
	else if (type == imageType::any)
		msg += " valid image ";
	else
		msg += " different to this one ";

	msg += "is required for this function";

	consoleLog(msg, icn);
}

/**
*
* makes context menu for image thumbnails
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::ProvideContextMenu
* Qualifier 
* @param     const QPoint & pos 
* @return    void
* Access     private 
*/
void MainWindow::ProvideContextMenu(const QPoint &pos)
{
	QPoint item = ui->ImageThumbList->mapToGlobal(pos);

	//QWidget *widget = static_cast<QListWidgetItem*>(childAt(pos));

	m_bContextMenuAction = true;

	QAction* rightClickItem = m_thumb_context_menu.exec(item);

	m_bContextMenuAction = false;
}


/**
*
*  Manages recent file list
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::fh_addFileListToMenu
* Qualifier 
* @return    void
* Access     public 
*/
void MainWindow::fh_addFileListToMenu()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

    // create actions for recent files
    for (int i = 0; i < MaxRecentFiles; ++i) {
           recentFileActs[i] = new QAction(this);
           recentFileActs[i]->setVisible(false);
           connect(recentFileActs[i], SIGNAL(triggered()), this, SLOT(openRecentFile()));
    }

    QList<QMenu*> menus = menuBar()->findChildren<QMenu*>();

    separatorAct = menus[0]->addSeparator();

    //add action to menu bar
    for (int i = 0; i < MaxRecentFiles; ++i)
		menus[0]->addAction(recentFileActs[i]);

    menus[0]->addSeparator();

    fh_updateRecentFileActions();
}


/**
*
*  Sets current file for recent file list
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::fh_setCurrentFile
* Qualifier 
* @param     const QString & fileName 
* @return    void
* Access     public 
*/
void MainWindow::fh_setCurrentFile(const QString &fileName)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

    curFile = fileName;
    setWindowFilePath(curFile);

    QSettings settings;
    QStringList files = settings.value("recentFileList").toStringList();
    files.removeAll(fileName);
    files.prepend(fileName);
    while (files.size() > MaxRecentFiles)
        files.removeLast();

    settings.setValue("recentFileList", files);

    fh_updateRecentFileActions();
}


/**
*
*  Update actions for recent file list
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::fh_updateRecentFileActions
* Qualifier 
* @return    void
* Access     public 
*/
void MainWindow::fh_updateRecentFileActions()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

    QSettings settings;
    QStringList files = settings.value("recentFileList").toStringList();

    int numRecentFiles = qMin(files.size(), (int)MaxRecentFiles);

    for (int i = 0; i < numRecentFiles; ++i) {
        QString text = tr("&%1 %2").arg(i + 1).arg(fh_strippedName(files[i]));
        recentFileActs[i]->setText(text);
        recentFileActs[i]->setData(files[i]);
        recentFileActs[i]->setVisible(true);
    }
    for (int j = numRecentFiles; j < MaxRecentFiles; ++j)
        recentFileActs[j]->setVisible(false);

    separatorAct->setVisible(numRecentFiles > 0);
}

/**
*
*  gets just file name from full filenamepath
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::fh_strippedName
* Qualifier 
* @param     const QString & fullFileName 
* @return    QT_NAMESPACE::QString
* Access     public 
*/
QString MainWindow::fh_strippedName(const QString &fullFileName)
{   
    return QFileInfo(fullFileName).fileName();
}

void MainWindow::paintEvent(QPaintEvent* event)
{
#ifdef DEBUGPRINT
#ifdef ONMOUSEPAINTDEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
#endif
}

/*
void MainWindow::wheelEvent ( QWheelEvent * event )
{
    this->m_scale += (event->delta()/120); //or use any other step for zooming
    std::cout << "exception caught: " << this->m_scale << std::endl;


}
*/

QString MainWindow::getSaveFilename(targeterImage im, int& number, bool bIsCompleteImage)
{
	if (im.filepathname == "")									// create filename
		return m_settings->s_project_Directory + m_settings->s_project_FilenamePrefix + "_" + QString::number(number++) + "_" + im.getUID().toString() + ".png";
	else
	{
		QString filename = QString::fromStdString(im.filepathname);

		QFileInfo check_file(filename);

		// if it exists already and is not a subimage then number the filename
		if (check_file.exists() && check_file.isFile() && bIsCompleteImage)
			filename.insert(filename.lastIndexOf('.'), QString::number(number++));
		
		return filename;	// use existing filename
	}
}

cv::Mat MainWindow::getDrawnImage(int index)
{


	return cv::Mat();
}

/**
*
*  Saves current image to file
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::SaveImage
* Qualifier 
* @return    void
* Access     public 
*/
void MainWindow::SaveImage()
{
#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	std::vector<int> checked = getCheckedImages();

	if (ui->ImageThumbList->count() > 0 && checked.size() > 0)
	{
		QFileDialog dialog;
		QString filename, filepath = "";
		int fileNumber = 0;	
		int ct = 0;
		QVector<drawingShape> shapes;

		// get current active image check if it is checked to save then check for sub-images
		foreach(int i, checked)
		{
			targeterImage tim = m_ImagesContainer.getImageAt(i);

			cv::Mat im = tim.getImage();

			// does image already have a filename
			if (i == m_currentImageDisplayedIndex)	// current image
				shapes = ui->display_image->getTargetImage(false, true, i);

			// if first image
			
			filename = getSaveFilename(tim, fileNumber, shapes.length() == 0);

			// first file ask user if they want to modify file name (or path)
			if (ct == 0)
			{
				// ask user to modify filename
				filename = dialog.getSaveFileName(this, "Save Image File",
					filename, tr("Image Files [*.jpg, *.jpeg, *.bmp, *.png , *.pgm, *.pbm, *.ppm *.tiff *.tif]"),
					0, QFileDialog::DontUseNativeDialog);

				// get directory
				QFileInfo check_file(filename);

				filepath = check_file.absolutePath();
			}
			else
			{
				// save image to dialog chosen path
				if(filepath != "")
				{
					QFileInfo check_file(filename);
					filename = filepath + "/" + check_file.fileName();
				}	
			}

			if(i == m_currentImageDisplayedIndex && shapes.length() > 0)
			{
				for (int j = 0; j < shapes.length(); j++)
				{
					// or save sub-image
					QRect r = shapes[j].boundingBox;
					cv::Rect cvr = cv::Rect(r.x(), r.y(), r.width(), r.height());
					
					cv::Mat rectImage = im(cvr);

					if (ct <= 0)
					{
						// save the image
						imwrite(filename.toLocal8Bit().data(), rectImage);
					}
					else
					{
						QString file = filename;
						QString sRect = "_(" + QString::number(shapes[j].boundingBox.left()) + "," + QString::number(shapes[j].boundingBox.top()) + ":" +
							QString::number(shapes[j].boundingBox.right()) + "," + QString::number(shapes[j].boundingBox.bottom()) + ")";

						file.insert(file.lastIndexOf('.'), sRect);

						// save the image
						imwrite(file.toLocal8Bit().data(), rectImage);
					}
				}
			}
			else
			{
				// save the image
				imwrite(filename.toLocal8Bit().data(), im);
			}
		

			DBOUT("image written to file: " << filename.toLocal8Bit().data() << std::endl);

			ct++;
		}

		if(ct == 0)
			consoleLog("You must select the image(s) you wish to be written to file", CONSOLECOLOURS::Warning);
		
		//cv::imwrite(fileName.toLocal8Bit().data(), *m_pCurrentImage );
	}
}

/**
*
*  Opens recent file from list
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::openRecentFile
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::openRecentFile()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

    QAction *action = qobject_cast<QAction *>(sender());
    if (action)
        loadFile(action->data().toString());
}

/**
*
* loads image file  
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::loadFile
* Qualifier 
* @param     const QString & fileName 
* @return    void
* Access     public 
*/
void MainWindow::loadFile(const QString &fileName)
{

#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	 addImage(fileName, imageType::display);

	 int i = m_ImagesContainer.getNumImages();

     if(i>0)
     {
		 try
		 {
			 m_currentImageDisplayedIndex = i - 1;

             DisplayImage();
         }
         catch( cv::Exception& e )
         {
             const char* err_msg = e.what();
             std::cout << "exception caught: " << err_msg << std::endl;
         }
     }
}

/**
*
*  Displays message box depending on image type
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   MainWindow::showMessage
* Qualifier 
* @param     imageType::imageType type 
* @param     QMessageBox::Icon icn 
* @return    void
* Access     public 
*/
void MainWindow::showMessage(imageType::imageType type, QMessageBox::Icon icn)
{
	QString msg("A image of type");

	if (type == imageType::mask)
		msg += " mask ";
	else if (type == imageType::target)
		msg += " target ";
	else if (type == imageType::test)
		msg += " test ";
	else if (type == imageType::roi)
		msg += " region of interest ";
	else if (type == imageType::cclabels)
		msg += " connected components ";
	else
		msg += " different to this one ";

	msg += "is required for this function";

	showMessage(msg);
}

/**
*
*  Displays message box
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   MainWindow::showMessage
* Qualifier 
* @param     QString message 
* @param     QMessageBox::Icon icn 
* @return    void
* Access     public 
*/
void MainWindow::showMessage(QString message, QMessageBox::Icon icn)
{
	QMessageBox mb;
	QPixmap p(":icons/24/targeter.png");
	mb.setIcon(icn);
	mb.setWindowIcon(p);
	mb.setWindowTitle(QString("Targeter Message"));
	mb.setText(QString(message));
	mb.exec();
}

/**
*
*  Sets image histogram in settings dialog
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::setHistogramImage
* Qualifier 
* @return    void
* Access     public 
*/
void MainWindow::setHistogramImage()
{
	
	// get histogram image
	cv::Mat hIm = getHistogram();

	if (hIm.rows > 0)
	{
		// convert to qt image
		QImage qim = HelperFunctions::makeQImage(hIm);

		m_settingsDlg.setImageGridDisplaySize(ui->display_image->getDisplaySize());

		m_settingsDlg.setHistogramImage(qim);
	}
	
}

/**
*
* Gets image histogram 
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   MainWindow::getHistogram
* Qualifier 
* @return    cv::Mat
* Access     public 
*/
cv::Mat MainWindow::getHistogram()
{
	int histSize = 255;

	float range[] = { 0, histSize };
	const float* histRange = { range };
	bool uniform = true;
	bool accumulate = false;
	cv::Mat hIm;

	if (m_ImagesContainer.getNumImages() > 0)
	{
		cv::Mat& im = m_ImagesContainer.getImageAt(getValidImageIndex()).getImage();

		if (!im.empty())
		{
			cv::Mat b_hist, gim;

			if (im.channels() > 2)
			{
				cv::cvtColor(im, gim, cv::COLOR_BGR2GRAY);

				calcHist(&gim, 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
			}
			else
				calcHist(&im, 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);

			// get histogram image
			hIm = HelperFunctions::displayHistogram(b_hist, histSize);
		}
	}
	return hIm;
}


/**
*
*  Creates targeter image and QImage for display from OpenCV image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::addCVImage
* Qualifier 
* @param     cv::Mat im 
* @param     QString imageName 
* @param     bool bRGBSwap 
* @param     imageType type 
* @return    void
* Access     public 
*/
void MainWindow::addCVImage(cv::Mat im, QUuid UID, QString imageName, bool bRGBSwap, imageType::imageType type, bool bDisplay, QString fileName)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	targeterImage tim(&m_ImagesContainer);

	std::string name = imageName.toStdString();
	std::string fname = fileName.toStdString();

	if(fname == "")
		fname = (m_settings->s_project_Directory + m_settings->s_project_FilenamePrefix + "_" + tim.getUID().toString() + ".png").toStdString();

	if (imageName == "overview camera image")
		tim.setCameraType(cameraType::overview);
	else if (imageName == "microscope camera image")
		tim.setCameraType(cameraType::microscope);
	else
		tim.setCameraType(cameraType::none);

	tim.addImageEx(im, UID, type, name, name, fname);

	addCVImage(tim, imageName, bRGBSwap);
}


/**
*
*  Creates QImage for display from targeter image and displays image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::addCVImage
* Qualifier 
* @param     targeterImage & tim 
* @param     QString imageName 
* @param     bool bRGBSwap 
* @return    void
* Access     public 
*/
void MainWindow::addCVImage(targeterImage& tim, QString imageName, bool bRGBSwap)
{
#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	if (imageName == NULL)
		addQImageThumbnail(tim, QString::fromStdString(tim.name));
	else
		addQImageThumbnail(tim, imageName);

	m_ImagesContainer.addImage(tim);

	//m_currentImageDisplayedIndex = m_ImagesContainer.getNumImages() - 1;

	DisplayImage();
}



/**
*
*  Given a file name loads and reads image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::addImage
* Qualifier 
* @param     const QString & fileName 
* @param     imageType type 
* @return    void
* Access     public 
*/
void MainWindow::addImage(const QString &fileName, imageType::imageType type)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
    QString qs = fileName;
    String s = qs.toLocal8Bit().data();

	fh_setCurrentFile(qs);

	targeterImage tim(&m_ImagesContainer);

    cv::Mat im = imread(s);

	addCVImage(im, QUuid::QUuid(), qs, true, imageType::display, false, fileName);
}

/**
*
*  Makes sub image from rectangular region of image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::copyImageToSquareRegion
* Qualifier 
* @param     QImage qim 
* @param     QColor col 
* @return    QT_NAMESPACE::QImage
* Access     public 
*/
QImage MainWindow::copyImageToSquareRegion(QImage qim, QColor col)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

    QPoint pt;
    QImage destImage;

    if(qim.width()> qim.height())
    {
        destImage = QImage(qim.width(), qim.width(), qim.format());

        destImage.fill(col);

        pt = QPoint(0, (qim.width()-qim.height())>>1);
    }
    else
    {
        destImage = QImage(qim.height(), qim.height(), qim.format());

        destImage.fill(col);

        pt = QPoint((qim.height()-qim.width())>>1, 0);
    }

    QPainter painter(&destImage);

    painter.drawImage(pt, qim);
    painter.end();

    return destImage;
}

/**
*
*  update labels of thumbnail images
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::updateThumbs
* Qualifier 
* @param     int index 
* @return    void
* Access     public 
*/
void MainWindow::updateThumbs()
{
	QString s = "";

	for (int row = 0; row < ui->ImageThumbList->count(); row++)
	{
		targeterImage& t = m_ImagesContainer.getImageAt(row);

		imageType::imageType type = t.getImageFunction();

		s = QString::fromStdString(t.getName());

		if (type == imageType::target)
			s = "target image";
		else if (type == imageType::test)
			s = "detection image";

		ui->ImageThumbList->item(row)->setText(s.section("/", -1));
	}
}

QString MainWindow::createTooltip(targeterImage& tim, QString imageName)
{
	//QString type = IMAGETYPESTRINGS(tim.imageFunction);

	QString strTooltip = "<b>name:</b> " + imageName+ "<br><b>filename:</b> " 
		+ QString::fromStdString(tim.filepathname) + "<br><b>type:</b> " 
		+ IMAGETYPESTRINGS(tim.imageFunction) + "<br>";

	QString masktype = DRAWINGMODESTRINGS(tim.maskType);

	if (tim.maskType != drawingMode::drawingMode::none)
		strTooltip += "<b>mask type:</b> " + masktype + "<br>";

	QString tt = QString::fromStdString(tim.getTooltip());

	if (tt != "")
		strTooltip += "<b>info:</b> " + tt + "<br>";

	cameraType::camera cam = tim.getCameraType();
	QString s = CAMERATYPE(cam);

	if( cam != cameraType::none)
		strTooltip += "<b>from camera:</b> " + s + "<br>";

	return strTooltip;
}

/**
*
*  adds QImage to thumbnail list
*
* @author    David Watts
* @since     2017/03/07
*
* FullName   MainWindow::addQImage
* Qualifier
* @param     QImage & qim
* @param     QString imageName
* @param     imageType type
* @return    void
* Access     public
*/
void MainWindow::addQImageThumbnail(targeterImage& tim, QString imageName)
{
#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	QImage& qim = tim.getQTImage();
	imageType::imageType type = tim.getImageFunction();

	QImage iconImage = copyImageToSquareRegion(qim, ui->display_image->palette().color(QWidget::backgroundRole()));

	QListWidgetItem* pItem = new QListWidgetItem(QIcon(QPixmap::fromImage(iconImage)), NULL);//QFileInfo(qs).fileName());

	pItem->setData(Qt::UserRole, "thumb" + QString::number(ui->ImageThumbList->count()));

	QString strTooltip = createTooltip(tim, imageName);

	pItem->setToolTip(strTooltip);

	if (type == imageType::target)
		pItem->setText("target image");
	else if (type == imageType::test)
		pItem->setText("detection image");

	pItem->setFlags(pItem->flags() | Qt::ItemIsUserCheckable);
	pItem->setCheckState(Qt::Unchecked);

	ui->ImageThumbList->addItem(pItem);
}

/*
 * // code in function below
String s = qs.toLocal8Bit().data();

m_filenames.push_back(s);

Mat im = imread(s);

setCurrentFile(qs);

m_ImagesContainer.m_Images.push_back(im);

QImage::Format form = this->getFormat(im.type());

QImage qi = QImage(im.data, im.cols, im.rows, im.step, form);

QImage qim = qi.rgbSwapped();

m_QImages.push_back(qim);

QlistWidgetItem* pItem = new QlistWidgetItem(QIcon(QPixmap::fromImage(qim)), NULL);//QFileInfo(qs).fileName());

pItem->setToolTip(qs);

pItem->setFlags(pItem->flags() | Qt::ItemIsUserCheckable);
pItem->setCheckState(Qt::Unchecked);

ui->ImageThumbList->addItem(pItem);
*/

/**
*
*  Handles Opening of image from file open dialog
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::OpenImage
* Qualifier 
* @return    void
* Access     public 
*/
void MainWindow::OpenImage()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setViewMode(QFileDialog::Detail);

    QStringList fileNames;

	try 
	{
		QStringList s=QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);

		QString st = s[0];

		if (m_ImagesContainer.getNumImages() > 0)
			st = "";

		// unfortunately cannot use native file dialog as it crashes on network drive access
		fileNames = dialog.getOpenFileNames(this, tr("Open Image or XML file"), st, tr("Image Files [ *.jpg , *.jpeg , *.bmp , *.png , *.gif, *.tif, *.tiff *.xml]"), 0, QFileDialog::DontUseNativeDialog);
	}
	catch (...) {
		DBOUT("error opening file");
	}

    QMutableStringListIterator i(fileNames); // pass list as argument

    while (i.hasNext()) 
	{
        QString qs = i.next();

		if (qs.contains(".xml"))
			xmlWriter.readXMLFile(qs, m_settings.get(), m_experimentalData.get());
		else
			addImage(qs);	
    }

	int num = m_ImagesContainer.getNumImages();

    if(num>0)
    {
        try
        {
			m_currentImageDisplayedIndex = num - 1;
			
            DisplayImage();
        }
        catch( cv::Exception& e )
        {
            const char* err_msg = e.what();
            std::cout << "exception caught: " << err_msg << std::endl;
        }
    }
}


/**
*
*  Changes displayed image when thumbnail image clicked
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::onThumbImageClick
* Qualifier 
* @param     QListWidgetItem * item 
* @return    void
* Access     private 
*/
void MainWindow::onThumbImageClick(QListWidgetItem* item)
{

#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	if (item->checkState() == Qt::Checked)
	{
		QColor c("#b9fcb6");
		QBrush brush(c, Qt::SolidPattern);

		//QString s = "QListWidget::item[UserRole=" + item->data(Qt::UserRole).toString() + "]  { border: 1px solid red }";

		//item->listWidget()->setStyleSheet(s);

		item->setBackground(brush);

		// Set the main image to be the clicked thumbnail image.
		int i = -1;
		for (i = 0; i < ui->ImageThumbList->count(); i++)
		{
			if (ui->ImageThumbList->item(i) == item)
				break;
		}

		if (i >= 0)
			setImageDisplay(i);
	}
	else
	{
		QBrush brush(Qt::NoBrush);

		item->setBackground(brush);
		
		//// Set the main image to be the clicked thumbnail image.
		int ind = ui->ImageThumbList->currentRow();

		//if(ind != m_currentImageDisplayedIndex)
			setImageDisplay(ind);	
	}
}

/**
*
*  Sets image shown to be thumbnail clicked image
*
* @author    David Watts
* @since     2017/03/24
* 
* FullName   MainWindow::setImageDisplay
* Qualifier 
* @param     int ind 
* @return    void
* Access     public 
*/
void  MainWindow::setImageDisplay(int ind)
{
	if (ind < (int)m_ImagesContainer.getNumImages() && ind >= 0)
	{
		try
		{
			m_currentImageDisplayedIndex = ind;

			DisplayImage();
		}
		catch (cv::Exception& e)
		{
			const char* err_msg = e.what();
			std::cout << "exception caught: " << err_msg << std::endl;
		}
	}
}

/**
*
*  Get vector of checked images in list
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::getCheckedImages
* Qualifier 
* @return    QVector<int>
* Access     public 
*/
std::vector<int> MainWindow::getCheckedImages()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	std::vector<int> checkedItems;

    for(int row = 0; row <  ui->ImageThumbList->count(); row++)
    {
        if (ui->ImageThumbList->item(row)->checkState() == Qt::Checked)
        {
            checkedItems.push_back(row);
        }
    }
    return checkedItems;
}

/**
*
*  manage image redrawing when window resized
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::resizeEvent
* Qualifier 
* @param     QResizeEvent * event 
* @return    void
* Access     public 
*/
void MainWindow::resizeEvent(QResizeEvent* event)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

   QMainWindow::resizeEvent(event);
   // Your code here.

    this->DisplayImage();
}


/**
*
*  Gets valid image array index, if current image index is invalid then function returns last valid index
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::getValidImageIndex
* Qualifier 
* @return    int
* Access     public 
*/
int MainWindow::getValidImageIndex()
{
	if (m_currentImageDisplayedIndex >= 0 && m_ImagesContainer.getNumImages() > 0)
	{
		if (m_currentImageDisplayedIndex <m_ImagesContainer.getNumImages() && !m_ImagesContainer.getImageAt(m_currentImageDisplayedIndex).getQTImage().isNull())
		{
			return m_currentImageDisplayedIndex;
		}
		else    // handle case of invalid index, set to last image in list
		{
			for (int i = m_ImagesContainer.getNumImages() - 1; i >= 0; i--)
			{
				if (!m_ImagesContainer.getImageAt(i).getQTImage().isNull())
				{
					m_currentImageDisplayedIndex = i;
					return m_currentImageDisplayedIndex;
				}
			}
			
			m_currentImageDisplayedIndex = -1;
			return m_currentImageDisplayedIndex;
		}
	}
	return -1;
}

/**
*
*  Displays image in widget
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::DisplayImage
* Qualifier 
* @return    void
* Access     public 
*/
void MainWindow::DisplayImage()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	DisplayImage(getValidImageIndex());
}

void MainWindow::DisplayImage(int ind)
{
#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
	if (ind >= 0)
	{
		ui->display_image->setImageIndex(ind);
		
		updateThumbs();
	}
}

void MainWindow::refreshDisplayImages()
{
	for(int i=0;i<m_ImagesContainer.getNumImages();i++)
	{
		DisplayImage(i);
	}
}

/**
*
*  slot for Open file dialog
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_action_Open_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_action_Open_triggered()
{
    OpenImage();
}



/**
*
*  slot for performing focus stack
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionProcessFocusStack_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionProcessFocusStack_triggered()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	consoleLog("Focus stack function under development", CONSOLECOLOURS::colour::Information);

    if(ui->ImageThumbList->count()>0)
    {
		std::vector<int> check = getCheckedImages();

		// get all checked images

        cv::Mat pMat = FocusStack::processImageStack4(m_ImagesContainer.getImages(check), check, this);

		addCVImage(pMat, "focus image");
		
    }
}

void MainWindow::on_actionEnergy_image_triggered()
{
#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
	
	if (ui->ImageThumbList->count() > 0)
	{
		std::vector<int> check = getCheckedImages();

		// get all checked images
		std::vector<targeterImage> images = m_ImagesContainer.getImages(check);

		foreach(int item, check)
		{
			cv::Mat m = images[item].getImage();

			cv::Mat pMat = FocusStack::createLaplacianEnergyImage(m, 3, true, false);

			addCVImage(pMat, "laplacian image");

			pMat = FocusStack::createLaplacianEnergyImage(m, 3, true, true);

			addCVImage(pMat, "energy image");
		}

	}
}
/**
*
*  Slot to save image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_action_Save_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_action_Save_triggered()
{
    SaveImage();
}

/**
*
*  slot to select (check) all image thumbnails
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionSelect_All_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionSelect_All_triggered()
{
    for(int row = 0; row <  ui->ImageThumbList->count(); row++)
    {
        ui->ImageThumbList->item(row)->setCheckState(Qt::Checked);
    }
}

/**
*
*  slot to deselect (uncheck) all image thumbnails
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionDeselect_All_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionDeselect_All_triggered()
{
    for(int row = 0; row <  ui->ImageThumbList->count(); row++)
    {
        ui->ImageThumbList->item(row)->setCheckState(Qt::Unchecked);
    }
}

/**
*
*  Makes new image from ROI rect
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::setTargetArea
* Qualifier 
* @param     drawingShape shape 
* @return    void
* Access     private 
*/
void MainWindow::setTargetArea(drawingShape shape)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

    qDebug() <<m_ImagesContainer.getNumImages() << endl;

	if(m_currentImageDisplayedIndex >= 0)
	{
		createMaskImage(m_ImagesContainer.getImageAtPtr(m_currentImageDisplayedIndex), shape);
	}
	else
		consoleLog(imageType::any, CONSOLECOLOURS::colour::Warning);
}

void MainWindow::StatusBarMessage(QString msg)
{
	this->statusBar()->showMessage(msg);
}



/**
*
*  Gets binary mask image and sub image from region from drawing object shape
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::maskImage
* Qualifier 
* @param     Mat im 
* @param     drawingShape shape 
* @param     targeterImage & tim 
* @return    void
* Access     public 
*/
void MainWindow::createMaskImage(targeterImage* orginal_image, drawingShape shape)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
   
	cv::Mat mask, dst;
	cv::Mat& im = orginal_image->getImage();

	orginal_image->setImageType(imageType::test);
	orginal_image->setName(orginal_image->getDefaultName());
	
	int x = MAX(0, MIN(shape.boundingBox.left(), im.cols));
	int y = MAX(0, MIN(shape.boundingBox.top(), im.rows));
	int maxx = MAX(0, MIN(shape.boundingBox.right(), im.cols));
	int maxy = MAX(0, MIN(shape.boundingBox.bottom(), im.rows));

	int w = maxx - x;
	int h = maxy - y;

	cv::Rect roi(x, y, w, h);
	dst = im(roi);

    cv::Mat out = cv::Mat(roi.height, roi.width, im.type(), Scalar(0,0,0));

    // get mask image
    if(shape.type == drawingMode::poly)
    {
        // convert polygon to opencv polygon
        mask = cv::Mat(roi.height, roi.width, im.type(), Scalar(0, 0, 0));

        vector <cv::Point> triOut;

        // since poly must be in mask image
        foreach(QPoint p, shape.polygon)    
            triOut.push_back(cv::Point(p.x() - shape.boundingBox.left(), p.y() - shape.boundingBox.top()));

        cv::fillConvexPoly(mask, triOut, Scalar( 255, 255, 255));
    }
    else if(shape.type == drawingMode::circle)
    {
        mask = cv::Mat(roi.height, roi.width, im.type(), Scalar(0, 0, 0));
        cv::ellipse(mask, cv::Point(mask.cols>>1, mask.rows>>1), cv::Size(mask.cols>>1, mask.rows>>1), 0, 0, 360, Scalar( 255, 255, 255 ), -1);
    }
    else
    {
        //return dst;   // dst is with correct colour
        mask = cv::Mat(roi.height, roi.width, im.type(), Scalar(255, 255, 255));
    }

    //dst.copyTo(out, mask);

	targeterImage target_image(&m_ImagesContainer);

	target_image.setImageType(imageType::target);

	target_image.addImage(dst);

	target_image.setImagePosition(roi);

	target_image.addFriendID(orginal_image->getUID());

	QUuid target_image_ID = target_image.getUID();

	orginal_image->addFriendID(target_image_ID);
	
	targeterImage mask_image(&m_ImagesContainer);

	if (shape.type == drawingMode::circle || shape.type == drawingMode::poly)
	{
		int* pImage = new int[w*h];

		for (int i = 0; i < w; i++)
			for (int j = 0; j < h; j++)
				pImage[i + j*w] = (int)(mask.at<Vec3b>(j, i)[0] > 0 ? 1 : 0);

		target_image.set1DImage(pImage, imageType::mask);
		target_image.setMaskType(shape.type);

		// set 1D image for mask image as well
		int* pImageMask = new int[w*h];
		memcpy(pImageMask, pImage, w*h*sizeof(int));

		mask_image.set1DImage(pImageMask, imageType::mask);
		mask_image.setMaskType(shape.type);
	}

	orginal_image->addFriendID(mask_image.getUID());

	QUuid mask_image_ID = mask_image.getUID();
	orginal_image->addFriendID(mask_image_ID);		

	mask_image.setImageType(imageType::mask);

	mask_image.addFriendID(orginal_image->getUID());

	mask_image.addImage(mask);
	mask_image.setName("target mask image");
	mask_image.setImagePosition(roi);

	target_image.addFriendID(mask_image.getUID());

	addCVImage(mask_image, "target mask image", true);
	addCVImage(target_image, "target image", true);

	//tim.setName("target image");

	updateThumbs();
}

/**
*
*  slot to stop panning image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::disablePanButton
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::disablePanButton()
{
    ui->action_Move_Image->setChecked(false);
}

/**
*
*  slot for handling zoom out
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionZoom_Out_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionZoom_Out_triggered()
{
    ui->display_image->zoomToPoint(QPoint(ui->display_image->m_displayRect.width()>>1, ui->display_image->m_displayRect.height()>>1), 50);
    ui->display_image->repaint();
}

/**
*
*  slot for handling zoom in
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionZoom_In_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionZoom_In_triggered()
{
    ui->display_image->zoomToPoint(QPoint(ui->display_image->m_displayRect.width()>>1, ui->display_image->m_displayRect.height()>>1), -50);
    ui->display_image->repaint();
}

/**
*
*  slot for handling drawing polygon
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionDraw_Polygon_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionDraw_Polygon_triggered()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
    if(ui->actionDraw_Polygon->isChecked())
        ui->display_image->setDrawingMode(drawingMode::poly);
    else
        ui->display_image->setDrawingMode(drawingMode::none);

    // uncheck others
	unsetDrawingButtons(ui->actionDraw_Polygon);
}

void MainWindow::on_actionMask_Black_triggered()
{
	if (ui->actionMask_Black->isChecked())
		ui->display_image->setFillColour(drawingColour::mask_black);
	else
		ui->display_image->setFillColour(drawingColour::none);

	ui->actionMask_White->setChecked(false);
}

void MainWindow::on_actionMask_White_triggered()
{
	if (ui->actionMask_White->isChecked())
		ui->display_image->setFillColour(drawingColour::mask_white);
	else
		ui->display_image->setFillColour(drawingColour::none);

	ui->actionMask_Black->setChecked(false);
}

void MainWindow::on_actionCreate_Mask_Image_triggered()
{
	std::vector<int> checked = getCheckedImages();

	if (ui->ImageThumbList->count() > 0 && checked.size() > 0)
	{
		foreach(int i, checked)
		{
			targeterImage tim = m_ImagesContainer.getImageAt(i);

			if (tim.imageFunction != imageType::mask)
			{
				cv::Mat binImage = ui->display_image->getBinaryImageFromShapes(i);

				addCVImage(binImage, tim.getUID(), "binary mask image", true, imageType::mask);
			}
		}
	}
}

/**
*
*  slot for handling drawing circle
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionDraw_Circle_Region_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionDraw_Circle_Region_triggered()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
    if(ui->actionDraw_Circle_Region->isChecked())
        ui->display_image->setDrawingMode(drawingMode::circle);
    else
        ui->display_image->setDrawingMode(drawingMode::none);

    // uncheck others
	unsetDrawingButtons(ui->actionDraw_Circle_Region);
}

void MainWindow::on_actionSelect_Object_triggered()
{
#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
	if (ui->actionSelect_Object->isChecked())
		ui->display_image->setDrawingMode(drawingMode::select);
	else
		ui->display_image->setDrawingMode(drawingMode::none);

	// uncheck others
	unsetDrawingButtons(ui->actionSelect_Object);
}

/**
*
*  slot for handling drawing rectangle
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionDraw_Rectangular_Region_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionDraw_Rectangular_Region_triggered()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
    if(ui->actionDraw_Rectangular_Region->isChecked())
        ui->display_image->setDrawingMode(drawingMode::rect);
    else
        ui->display_image->setDrawingMode(drawingMode::none);

    // uncheck others
	unsetDrawingButtons(ui->actionDraw_Rectangular_Region);
}

/**
*
*  slot for handling panning image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_action_Move_Image_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_action_Move_Image_triggered()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
   if (ui->action_Move_Image->isChecked())
	   ui->display_image->setDrawingMode(drawingMode::shift);
   else
	   ui->display_image->setDrawingMode(drawingMode::none);

   unsetDrawingButtons(ui->action_Move_Image);
}

void MainWindow::receiveSettings()
{	
	if (m_settings->activeCamera != cameraType::none)
		basCamera->setCameras(QString::number(m_settings->overviewCameraSN), QString::number(m_settings->microscopeCameraSN));

	ui->display_image->setGrid(m_settings->displayGrid, m_settings->gridOffsetX, m_settings->gridOffsetY, m_settings->gridSpacingX, m_settings->gridSpacingY, m_settings->objectColours[drawingItems::grid]);
}

/**
*
*  slot for deselecting all drawing buttons
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::unsetDrawingButtons
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::unsetDrawingButtons(QAction* pAct)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
	if (pAct != ui->actionReference_fiducial_marks)
		ui->actionReference_fiducial_marks->setChecked(false);

	if (pAct != ui->actionClick_Center_Objective)
		ui->actionClick_Center_Objective->setChecked(false);

	if (pAct != ui->actionClickTarget)
		ui->actionClickTarget->setChecked(false);

	if (pAct != ui->actionGrid_Spacing)
		ui->actionGrid_Spacing->setChecked(false);

	// non cross cursor controls
	if (pAct != ui->actionDraw_Rectangular_Region)
		ui->actionDraw_Rectangular_Region->setChecked(false);

	if (pAct != ui->actionDraw_Circle_Region)
		ui->actionDraw_Circle_Region->setChecked(false);

	if (pAct != ui->actionDraw_Polygon)
		ui->actionDraw_Polygon->setChecked(false);

	if (pAct != ui->action_Move_Image)
		ui->action_Move_Image->setChecked(false);

	if (pAct != ui->actionSelect_Object)
		ui->actionSelect_Object->setChecked(false);

	if (pAct == ui->actionDraw_Rectangular_Region ||
		pAct == ui->actionDraw_Circle_Region || 
		pAct == ui->actionDraw_Polygon || 
		pAct == ui->action_Move_Image ||
		pAct == ui->actionClick_Center_Objective ||
		pAct == ui->actionGrid_Spacing ||
		pAct == ui->actionSelect_Object)
			QApplication::restoreOverrideCursor();
}

/**
*
*  slot to get target image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionGet_Target_image_region_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionGet_Target_image_region_triggered()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
	int ind = getValidImageIndex();

	if (ind >= 0)
	{
		if (ui->display_image->m_drawingObjects.size() == 0)
			consoleLog("You have to draw on the image (rectangle, circle, polygon) before producing a region of interest image", CONSOLECOLOURS::colour::Warning);
		else
			ui->display_image->getTargetImage();
	}
	else
		consoleLog(imageType::any, CONSOLECOLOURS::colour::Warning);
}

/**
*
*  sets type of image
*
* @author    David Watts
* @since     2017/03/14
* 
* FullName   MainWindow::updateImageType
* Qualifier 
* @param     int ind 
* @param     imageType::imageType type 
* @return    void
* Access     public 
*/
void MainWindow::updateImageType(int ind, imageType::imageType type)
{
	if (m_ImagesContainer.getImageAt(ind).getImageFunction() == type)
		m_ImagesContainer.getImageAt(ind).setImageType(imageType::display);
	else
		m_ImagesContainer.getImageAt(ind).setImageType(type);
}


/**
*
*  slot to flag image as target image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionSet_as_find_targets_image_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionSet_as_find_targets_image_triggered()
{
	std::vector<int> checked = getCheckedImages();

	if (m_bContextMenuAction)
	{
		int ind = ui->ImageThumbList->currentRow();

		updateImageType(ind, imageType::test);

		updateThumbs();
	}
	else if (ui->ImageThumbList->count() > 0 && checked.size() > 0)
	{
		// delete image in index check
		for (int i = checked.size() - 1; i >= 0; i--)
		{
			int ind = checked[i];

			updateImageType(ind, imageType::test);
		}

		updateThumbs();
	}
}

/**
*
*  removes image at array index
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::deleteImage
* Qualifier 
* @param     int index 
* @return    bool
* Access     public 
*/
void MainWindow::deleteImage(int index, bool bDisplay)
{
	if (index >= 0 && index < m_ImagesContainer.getNumImages())
	{
		// delete drawing object pointing to this image
		ui->display_image->deleteDrawingObjects(index);

		// remove image from list 
		m_ImagesContainer.removeImage(index);

		// and from gallery
		delete ui->ImageThumbList->item(index);

		// but now drawing objects point to wrong image

	}
	else
	{
		if (getValidImageIndex() < 0)
			ui->display_image->setImageIndex(m_ImagesContainer.getNumImages() - 1);
	}
	
	if (bDisplay)
		DisplayImage();
}

/**
*
*  slot to delete current image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionDeleteImage_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionDeleteImage_triggered()
{
	int item;

	QObject* obj = sender();

	int ind = ui->ImageThumbList->currentRow();

	deleteImage(ind);
}

/**
*
*  slot to delete checked image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionDeleteObject_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionDeleteObject_triggered()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	QObject* obj = sender();

	if (obj == ui->actionDeleteObject)
	{
		int item;
		std::vector<int> checked = getCheckedImages();

		if (ui->ImageThumbList->count() > 0 && checked.size() > 0)
		{
			bool changeCurrent = false;

			if (checked.size() > 1)
				qSort(checked.begin(), checked.end());

			// delete image in index check
			for (int i = checked.size() - 1; i >= 0; i--)
				deleteImage(checked[i], i==0);	// display when list finally processed
		}
		else
		{
			ui->display_image->deleteSelectedDrawingObject();
		}
		ui->display_image->repaint();
	}
	else
	{
		DBOUT("called from menu");
	}
}

void MainWindow::on_actionClickTarget_triggered(bool checked)
{
	// change state to click target state
	if (ui->actionClickTarget->isChecked())
		ui->display_image->setDrawingMode(drawingMode::cross);
	else
		ui->display_image->setDrawingMode(drawingMode::none);

	unsetDrawingButtons(ui->actionClickTarget);
}


void MainWindow::on_actionGrid_Spacing_triggered(bool checked)
{
	// change state to click target state
	if (ui->actionGrid_Spacing->isChecked())
		ui->display_image->setDrawingMode(drawingMode::cross);
	else
		ui->display_image->setDrawingMode(drawingMode::none);

	unsetDrawingButtons(ui->actionGrid_Spacing);
}

void MainWindow::on_actionReference_fiducial_marks_triggered(bool checked)
{

	if (ui->actionReference_fiducial_marks->isChecked())
		ui->display_image->setDrawingMode(drawingMode::fiducial);
	else
		ui->display_image->setDrawingMode(drawingMode::none);

	unsetDrawingButtons(ui->actionReference_fiducial_marks);
}

void MainWindow::on_actionClick_Center_Objective_triggered(bool checked)
{
	// get click position
	if (ui->actionClick_Center_Objective->isChecked())
		ui->display_image->setDrawingMode(drawingMode::centerObjective);
	else
		ui->display_image->setDrawingMode(drawingMode::none);

	unsetDrawingButtons(ui->actionClick_Center_Objective);
}

void MainWindow::addFiducialMark(QPoint p)
{
	m_settingsDlg.setFiducial(p.x(), p.y(), true);

	consoleLog("Fiducial Mark added: "+ QString::number(p.x()) + "," + QString::number(p.y()), CONSOLECOLOURS::colour::Information);
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
void MainWindow::on_actionGrab_Image_From_Camera_triggered()
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
	if (m_settings->activeCamera == cameraType::overview)
	{
		if (!basCamera->isOverviewCameraEmpty())
		{
			cv::Mat image = basCamera->grabImage(cameraType::overview);

			QUuid id = QUuid::createUuid();

			if (!image.empty())
				addCVImage(image, id, "overview camera image");

			QString filename = m_settings->s_project_Directory + m_settings->s_project_FilenamePrefix + "_" + id.toString() + ".png";
			
			imwrite(filename.toLocal8Bit().data(), image);

			DBOUT("camera image written to file: " << filename.toLocal8Bit().data() << std::endl);

		}
		else
			DBOUT("problem connecting to overview camera");
	}
	else
	{
		if (!basCamera->isMicroscopeCameraEmpty())
		{
			cv::Mat image = basCamera->grabImage(cameraType::microscope);

			if(!image.empty())
				addCVImage(image, QUuid::createUuid(), "microscope camera image");
		}
		else
			DBOUT("problem connecting to microscope camera");
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
void MainWindow::on_actionGrab_Video_From_Camera_triggered(bool checked)
{
#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
	
	if(checked)
	{
		if (m_settings->activeCamera == cameraType::overview)
		{
			if (!basCamera->isOverviewCameraEmpty())
			{
				basCamera->grabVideo(cameraType::overview);
			}
			else
				DBOUT("problem connecting to overview camera");
		}
		else
		{
			if (!basCamera->isMicroscopeCameraEmpty())
			{
				basCamera->grabVideo(cameraType::microscope);
			}
			else
				DBOUT("problem connecting to microscope camera");
		}
	}
	else
	{
		basCamera->stopGrabbing();
	}
}


/**
*
*  slot to merge checked binary and normal images
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionMergeImages_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionMergeImages_triggered()
{
	std::vector<int> checked = getCheckedImages();
	cv::Mat dst, pIm;
	bool bOK = false;
	int maskIndex = -1;

	// find which of the images is mask image
	for (int i = 0; i < checked.size(); i++)
	{
		if (m_ImagesContainer.getImageAt(checked[i]).getImageFunction() == imageType::mask)
		{
			maskIndex = checked[i];
			break;
		}
	}

	if (maskIndex >= 0)
	{
		cv::Mat& mask = m_ImagesContainer.getImageAt(maskIndex).getImage();

		if (ui->ImageThumbList->count() > 0 && checked.size() > 1)
		{
			// delete image in index check
			for (int i = 0; i < checked.size(); i++)
			{
				if (checked[i] == maskIndex)
					continue;

				int c = m_ImagesContainer.getImageAt(checked[i]).Cols();
				int r = m_ImagesContainer.getImageAt(checked[i]).Rows();

				if (mask.rows != r || mask.cols != c)
				{
					// enlarge mask image by copying to larger image
					cv::Mat newMask;

					cv::resize(mask, newMask, m_ImagesContainer.getImageAt(checked[i]).Size());

					m_ImagesContainer.getImageAt(checked[i]).getImage().copyTo(dst, newMask);
				}
				else
					m_ImagesContainer.getImageAt(checked[i]).getImage().copyTo(dst, mask);

				bOK = true;
			}
			if (bOK)
				addCVImage(dst, "masked image");
		}
	}
	else
	{
		consoleLog("One of the images needs to be a binary mask image for the merging", CONSOLECOLOURS::colour::Warning);
	}
}

/**
*
*  slot to display settings dialog
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionSettings_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionSettings_triggered()
{
	m_settingsDlg.create(m_settings.get());

	setHistogramImage();

	m_settingsDlg.show();
}

void MainWindow::on_action_New_triggered()
{
	m_settingsDlg.create(m_settings.get());

	setHistogramImage();

	m_settingsDlg.setActiveTab("ProjectSettingsTab");
	m_settingsDlg.show();
}

/**
*
*  slot to threshold selected image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionThresholdImage_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionThresholdImage_triggered()
{
	int ind = getValidImageIndex();

	if (ind >= 0)
	{
		cv::Mat& im = m_ImagesContainer.getImageAt(ind).getImage();
		cv::Mat out;

		if (m_settings->ThresholdType == thresholdType::cluster2 || m_settings->ThresholdType == thresholdType::posterize)
			out = m_ImageProcessing.HistogramClusteringGray(im, m_settings->NoClustersThreshold);
		else
			out = m_ImageProcessing.Threshold(im, m_settings->threshold_min, m_settings->threshold_max, m_settings->ThresholdType);

		addCVImage(out, m_ImagesContainer.getImageAt(ind).getUID(), "threshold image", true, imageType::mask, true);
	}
	else
		consoleLog(imageType::any, CONSOLECOLOURS::colour::Warning);
}

void MainWindow::on_actionRemoveBlackPixels_triggered()
{
	int ind = getValidImageIndex();

	if (ind >= 0)
	{
		cv::Mat& im = m_ImagesContainer.getImageAt(ind).getImage();

		Mat bin, pbin = cv::Mat(im.rows, im.cols, CV_8UC1);
	
		cv::cvtColor(im, bin, cv::COLOR_BGR2GRAY, 1);

		FillMissingPixels<uchar>(bin, pbin, false);

		addCVImage(pbin, m_ImagesContainer.getImageAt(ind).getUID(), "remove black pixels image", true, imageType::display, true);
	}
	else
		consoleLog(imageType::any, CONSOLECOLOURS::colour::Warning);
}

void MainWindow::on_actionBackground_fit_triggered()
{
	int ind = getValidImageIndex();

	if (ind >= 0)
	{
		cv::Mat im = m_ImagesContainer.getImageAt(ind).getImage();

		cv::Mat gray;

		if (im.channels() != 1)
			cvtColor(im, gray, CV_BGR2GRAY);
		else
			gray = im;

		cv::Mat bim = m_ImageProcessing.fitBackgroundImage(gray);

		cv::Mat corr = gray - bim;

		addCVImage(bim, m_ImagesContainer.getImageAt(ind).getUID(), "background image", true, imageType::background, true);
		addCVImage(corr, m_ImagesContainer.getImageAt(ind).getUID(), "corrected image", true, imageType::display, true);
	}
	else
		consoleLog(imageType::any, CONSOLECOLOURS::colour::Warning);
}



void MainWindow::on_actionEntropyFilter_triggered()
{
	QFuture<void> t1 = QtConcurrent::run(this, &MainWindow::entropyFilterImage);
}

void MainWindow::entropyFilterImage()
{
	int ind = getValidImageIndex();

	if (ind >= 0)
	{
		cv::Mat& im = m_ImagesContainer.getImageAt(ind).getImage();
		Mat bin, pbin;
		cv::cvtColor(im, bin, cv::COLOR_BGR2GRAY, 1);

		cv::Mat entropyMat = Mat::zeros(im.rows, im.cols, CV_32FC1);

		m_TextureAnalysis.entropyFilt(bin, entropyMat);

		normalize(entropyMat, entropyMat, 0, 255, NORM_MINMAX, -1, Mat());

		entropyMat.convertTo(entropyMat, CV_8UC1);

		QMetaObject::invokeMethod(this, // obj
			"addMatImage", // member
			Qt::BlockingQueuedConnection,
			Q_ARG(cv::Mat, entropyMat),
			Q_ARG(QString, "entropy image"),
			Q_ARG(imageType::imageType, imageType::display),
			Q_ARG(QAction*, ui->actionEntropyFilter)); // val1
	}
	else
		QMetaObject::invokeMethod(this, "LOGCONSOLE", Qt::QueuedConnection, Q_ARG(imageType::imageType, imageType::any), Q_ARG(CONSOLECOLOURS::colour, CONSOLECOLOURS::colour::Warning));
}

/**
*
*  slot to perform connected component analysis on selected image
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   MainWindow::on_actionConnected_Components_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionConnected_Components_triggered()
{
	int ind = getValidImageIndex();

	if (ind >= 0)
	{
		targeterImage& tim = m_ImagesContainer.getImageAt(ind);

		if (tim.getImageFunction() == imageType::mask)
		{
			targeterImage ccim = getConnectedComponents(tim.getImage());

			ccim.addFriendID(tim.getUID());

			addCVImage(ccim, "connected components image", true);
		}
		else
			consoleLog(imageType::mask, CONSOLECOLOURS::colour::Warning);
	}
	else
	{
		consoleLog(imageType::any, CONSOLECOLOURS::colour::Warning);
	}
}

/**
*
*  Sets connected component image structure from binary image
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   MainWindow::getConnectedComponents
* Qualifier 
* @param     cv::Mat & im 
* @return    targeterImage&
* Access     public 
*/
targeterImage MainWindow::getConnectedComponents(cv::Mat& im)
{
	cv::Mat bin, out, stats, centroids;
	cv::Mat labels;

	if(im.channels()>1)
		cv::cvtColor(im, bin, cv::COLOR_BGR2GRAY, 1);
	else
		bin = im;

	// create new ccimage
	targeterImage ccim(&m_ImagesContainer);

	out = m_ImageProcessing.getConnectedComponentImage(bin, labels, stats, centroids);

	ccim.setLabelsImage(labels);

	ccim.setCentroidsImage(centroids);
	ccim.setStatsImage(stats);
	ccim.setLabelsImage(labels);

	ccim.setImageType(imageType::cclabels);
	ccim.setName("labeled image");

	//cv::cvtColor(labels, bin, cv::COLOR_GRAY2BGR, 3);

	ccim.addImage(out);

	return ccim;
}

/**
*
*  slot to flag images as target (training) images
*
* @author    David Watts
* @since     2017/03/07
*
* FullName   MainWindow::on_actionSet_as_Target_triggered
* Qualifier
* @return    void
* Access     private
*/
void MainWindow::on_actionSet_as_Target_triggered()
{
	std::vector<int> checked = getCheckedImages();

	if (m_bContextMenuAction)
	{
		int ind = ui->ImageThumbList->currentRow();

		updateImageType(ind, imageType::target);

		updateThumbs();
	}
	else if (ui->ImageThumbList->count() > 0 && checked.size() > 0)
	{
		int ind = checked[0];

		updateImageType(ind, imageType::target);

		updateThumbs();
	}
}

/**
*
*  Slot to score image of possible targets found in the detection image
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   MainWindow::on_actionScoreImage_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionScoreImage_triggered()
{
	QFuture<void> t1 = QtConcurrent::run(this, &MainWindow::getScoreImage);
}

void MainWindow::getScoreImage()
{
	int imageIndex = -1;

	targeterImage tim = createScoreImage(imageIndex);

	if (tim.Rows() > 0 && tim.Cols()>0)
	{
		QString s("score image ");

		s.append(ALGOSTRINGS(m_settings->algorithmType));

		QMetaObject::invokeMethod(this, // obj
			"addTargeterImage", // member
			Qt::BlockingQueuedConnection,
			Q_ARG(targeterImage, tim),
			Q_ARG(QAction*, ui->actionDetect_lines)); // val1
	}
	else
	{
		consoleLog(imageType::any, CONSOLECOLOURS::colour::Warning);
	}

}

/**
*
*   Slot to score image of possible targets found in the detection image
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   MainWindow::createScoreImage
* Qualifier 
* @return    cv::Mat
* Access     public 
*/
targeterImage MainWindow::createScoreImage(int& imageIndex)
{
	std::vector<targeterImage> targetImages;
	targeterImage testImage(&m_ImagesContainer);
	targeterImage tim(&m_ImagesContainer);
	cv::Mat scoreImage;
	
	bool bFoundTest = false;

	// get vector list of training images from targeterImages
	for (int i = m_ImagesContainer.getNumImages()-1; i >=0; i--)
	{
		targeterImage& m = m_ImagesContainer.getImageAt(i);

		if (m.getImageFunction() == imageType::target)
		{
			targetImages.push_back(m);
			tim.addFriendID(m.getUID());
		}
		else if (!bFoundTest && m.getImageFunction() == imageType::test)
		{
			bFoundTest = true;
			imageIndex = i;
			testImage = m;
		}
	}

	if (targetImages.size() > 0 && bFoundTest)
	{
		tim.addFriendID(testImage.getUID());

		foreach(targeterImage t, targetImages)
			tim.addFriendID(t.getUID());

		tim.setImageType(imageType::score);
		
		if (m_settings->algorithmType<0 || m_settings->algorithmType>algoType::LASTALGO)
			m_settings->algorithmType = algoType::COOC;

		// get score image
		if (m_settings->algorithmType == algoType::COOC)
		{
			scoreImage = m_FindTargets.ColourOccuranceHistogram(targetImages, testImage, m_settings->distance, m_settings->cluster, false);
		}
		else if (m_settings->algorithmType == algoType::LAPLACIAN)
		{
			QMetaObject::invokeMethod(this, "LOGCONSOLE", Qt::BlockingQueuedConnection, Q_ARG(QString, "function not yet implemented"),	Q_ARG(CONSOLECOLOURS::colour, CONSOLECOLOURS::colour::Information));
			scoreImage = m_FindTargets.LaplacianFindObject(targetImages, testImage, m_settings->distance, m_settings->cluster);
		}
		else if (m_settings->algorithmType == algoType::CROSSENTROPY)
		{
			scoreImage = m_FindTargets.ColourOccuranceHistogram(targetImages, testImage, m_settings->distance, m_settings->cluster, true);
		}
		else
		{
			scoreImage = m_FindTargets.CVMatching(targetImages, testImage, m_settings->algorithmType);
		}

		if (scoreImage.rows > 0)
			tim.addImage(scoreImage);
		else
			QMetaObject::invokeMethod(this, "LOGCONSOLE", Qt::BlockingQueuedConnection, Q_ARG(QString, "something went wrong - score image not created"), Q_ARG(CONSOLECOLOURS::colour, CONSOLECOLOURS::colour::Warning));
	}
	else
	{
		QString msg;
		if (targetImages.size() == 0)
			msg = "You need to set a target ";
		if (testImage.getImage().empty())
			msg += "and a test ";

		msg += "image first";

		QMetaObject::invokeMethod(this, "LOGCONSOLE", Qt::BlockingQueuedConnection, Q_ARG(QString, msg), Q_ARG(CONSOLECOLOURS::colour, CONSOLECOLOURS::colour::Warning));
	}

	return tim;
}

/**
*
* Slot to find targets in detection image
*
* @author    David Watts
* @since     2017/03/07
*
* FullName   MainWindow::on_actionCreate_target_image_triggered
* Qualifier
* @return    void
* Access     private
*/
void MainWindow::on_actionFind_targets_triggered()
{
	QFuture<void> t1 = QtConcurrent::run(this, &MainWindow::getTargetImage);
}

void MainWindow::getTargetImage()
{
	int imageIndex=-1;

	// get score image
	targeterImage tim = createScoreImage(imageIndex);

	if (tim.Rows() > 0 && tim.Cols() > 0)
	{
		cv::Mat im = getTargetPositions(tim, NULL, imageIndex);

		QMetaObject::invokeMethod(this, // obj
			"addMatImage", // member
			Qt::BlockingQueuedConnection,
			Q_ARG(cv::Mat, im),
			Q_ARG(QString, "detected targets image"),
			Q_ARG(imageType::imageType, imageType::centroids),
			Q_ARG(QAction*, ui->actionDetect_lines)); // val1
	}
	else
	{
		consoleLog(imageType::any, CONSOLECOLOURS::colour::Warning);
	}
}

void  MainWindow::on_actionSave_Target_Positions_triggered()
{
	// get all target positions from image
	QVector<QPoint> targets = ui->display_image->targetPoints();
	QVector<QRect> r;

	// write to xml file
	xmlWriter.writeCentroids(targets, r);
}

cv::Mat MainWindow::getTargetPositions(targeterImage scoreImage, targeterImage* targetImage, int imageIndex)
{
	int index = -1;

	if (scoreImage.Rows() > 0)
	{
		cv::Mat binImage, targets;

		// use standard threshold method
		if (m_settings->ThresholdType == thresholdType::cluster2 || m_settings->ThresholdType == thresholdType::posterize)
			binImage = m_ImageProcessing.HistogramClusteringGray(scoreImage.getImage(), m_settings->NoClustersThreshold);
		else
			binImage = m_ImageProcessing.Threshold(scoreImage.getImage(), m_settings->threshold_min, m_settings->threshold_max, m_settings->ThresholdType);

		cv::Mat labels, stats, centroids;
		int connectivity_8 = 8;

		targeterImage tarCC = getConnectedComponents(binImage);

		return getTargetsFromLabelledImage(tarCC, binImage, targetImage, &scoreImage, imageIndex);
	}
	else
		return cv::Mat();
}

cv::Mat MainWindow::getTargetsFromLabelledImage(targeterImage& tarCC, cv::Mat& binImage, targeterImage* targetImage, targeterImage* displayImage, int imageIndex, bool bFilter)
{
	cv::Mat targets;

	targeterImage *tarBin = NULL, *tar = NULL;

	if(bFilter && targetImage != NULL && binImage.rows > 0)
	{
		cv::Rect r = targetImage->getImagePosition();

		if(r.width>0 && r.height>0)
		{
			// filter binary regions based on similarity to target image size
			FilterRegions(tarCC, binImage, r, m_settings->StdevLarger, m_settings->StdevSmaller, m_settings->AspectTolerance);
		}
	}

	if (displayImage != NULL)
	{
		cv::Mat& originalImage = displayImage->getImage();

		targets = originalImage.clone();

		drawCentroids(tarCC, targets, imageIndex);

		if (tarCC.getImageFunction() == imageType::cclabels)
		{
			xmlWriter.writeCentroids(tarCC.getCentroidsImage(), tarCC.getStatsImage());
		}
	}
	else
	{
		QMetaObject::invokeMethod(this, "LOGCONSOLE", Qt::QueuedConnection, Q_ARG(imageType::imageType, imageType::test), Q_ARG(CONSOLECOLOURS::colour, CONSOLECOLOURS::colour::Warning));
	}

	return targets;
}

/**
*
*  Draws crosses at centroid positions of connected component regions on supplied cv::Mat image
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   MainWindow::drawCentroids
* Qualifier 
* @param     targeterImage & tim 
* @param     cv::Mat & drawimage 
* @return    void
* Access     public 
*/
void MainWindow::drawCentroids(targeterImage& tim, cv::Mat& drawimage, int imageIndex)
{
	if (tim.getImageFunction() == imageType::cclabels)
	{
		cv::Mat& centroidsImage = tim.getCentroidsImage();
		cv::Mat& stats = tim.getStatsImage();
		cv::Mat& display = tim.getImage();
		cv::Mat sub_image;
		cv::Rect rect;
		bool bWriteSubImages = true;
		QString filename = m_settings->s_project_Directory + m_settings->s_project_FilenamePrefix;
		QString imagename = QString::fromStdString(tim.filepathname);

		filename += imagename.mid(imagename.lastIndexOf('/'), imagename.lastIndexOf('.'));
		QString file;
	
		for (int i = 1; i < centroidsImage.rows; i++)	// first region is invalid
		{
			double x = centroidsImage.at<double>(i, 0);
			double y = centroidsImage.at<double>(i, 1);
			int *row = &stats.at<int>(i, 0);
			
			if(row[CC_STAT_WIDTH]>1 && row[CC_STAT_HEIGHT]>1)
			{
				rect = cv::Rect(row[CC_STAT_LEFT], row[CC_STAT_TOP], row[CC_STAT_WIDTH], row[CC_STAT_HEIGHT]);

				// save sub image
				drawimage(rect).copyTo(sub_image);

				file = filename + QString::number(x) + "-" + QString::number(x) + ".png";
				cv::imwrite(file.toLocal8Bit().data(), sub_image);

				DBOUT("target image written: " << file.toLocal8Bit().data() <<std::endl);
			}
			else
			{
				bWriteSubImages = false;
			}
		}

		for (int i = 1; i < centroidsImage.rows; i++)	// first region is invalid
		{
			double x = centroidsImage.at<double>(i, 0);
			double y = centroidsImage.at<double>(i, 1);
			int *row = &stats.at<int>(i, 0);

			if (row[CC_STAT_WIDTH] > 1 && row[CC_STAT_HEIGHT] > 1)
			{
				rect = cv::Rect(row[CC_STAT_LEFT], row[CC_STAT_TOP], row[CC_STAT_WIDTH], row[CC_STAT_HEIGHT]);
				cv::rectangle(drawimage, rect, cv::Scalar(0, 255, 0));
			}
			cv::drawMarker(drawimage, cv::Point(x, y), cv::Scalar(0, 0, 255), MARKER_CROSS, 3, 1);

			ui->display_image->setTargetPosition(QPoint(x, y), imageIndex);
		}

		if(bWriteSubImages)
			consoleLog("some sub images not written to file as too small", CONSOLECOLOURS::colour::Warning);
	}
	else
	{
		consoleLog(imageType::cclabels, CONSOLECOLOURS::colour::Warning);
	}
}


/**
*
*  Draws crosses at centroid positions of connected component regions on supplied cv::Mat image
*
* @author    David Watts
* @since     2017/03/17
*
* FullName   MainWindow::drawCentroids
* Qualifier
* @param     targeterImage & tim
* @param     cv::Mat & drawimage
* @return    void
* Access     public
*/
cv::Mat MainWindow::drawCentroids(targeterImage& tim, cv::Mat& display, bool bWriteSubImages)
{
	if (tim.getImageFunction() == imageType::cclabels)
	{
		cv::Mat& centroidsImage = tim.getCentroidsImage();
		cv::Mat& stats = tim.getStatsImage();

		cv::Mat sub_image;
		cv::Rect rect;

		QString filename = m_settings->s_project_Directory + m_settings->s_project_FilenamePrefix;
		QString imagename = QString::fromStdString(tim.filepathname);

		filename += imagename.mid(imagename.lastIndexOf('/'), imagename.lastIndexOf('.'));
		QString file;

		if (bWriteSubImages && !display.empty())
		{
			for (int i = 1; i < centroidsImage.rows; i++)	// first region is invalid
			{
				double x = centroidsImage.at<double>(i, 0);
				double y = centroidsImage.at<double>(i, 1);
				int *row = &stats.at<int>(i, 0);
				rect = cv::Rect(row[CC_STAT_LEFT], row[CC_STAT_TOP], row[CC_STAT_WIDTH], row[CC_STAT_HEIGHT]);

				// save sub image
				display(rect).copyTo(sub_image);

				file = filename + QString::number(x) + "-" + QString::number(x) + ".png";
				imwrite(file.toLocal8Bit().data(), sub_image);

				DBOUT("target image written: " << file.toLocal8Bit().data() << std::endl);
			}
		}

		if (display.empty())
		{
			// create new image
			cv::Mat displayImage(tim.Size(), tim.Type(), cv::Scalar(0, 0, 0));

			// overwrite display image
			for (int i = 1; i < centroidsImage.rows; i++)	// first region is invalid
			{
				double x = centroidsImage.at<double>(i, 0);
				double y = centroidsImage.at<double>(i, 1);
				int *row = &stats.at<int>(i, 0);
				rect = cv::Rect(row[CC_STAT_LEFT], row[CC_STAT_TOP], row[CC_STAT_WIDTH], row[CC_STAT_HEIGHT]);

				cv::rectangle(displayImage, rect, cv::Scalar(255, 255, 255), CV_FILLED);
			}
			return displayImage;
		}
		else
		{
			cv::Mat displayImage = tim.getImage().clone();

			// overwrite display image
			for (int i = 1; i < centroidsImage.rows; i++)	// first region is invalid
			{
				double x = centroidsImage.at<double>(i, 0);
				double y = centroidsImage.at<double>(i, 1);
				int *row = &stats.at<int>(i, 0);
				rect = cv::Rect(row[CC_STAT_LEFT], row[CC_STAT_TOP], row[CC_STAT_WIDTH], row[CC_STAT_HEIGHT]);

				cv::rectangle(displayImage, rect, cv::Scalar(0, 255, 0));
				cv::drawMarker(displayImage, cv::Point(x, y), cv::Scalar(0, 0, 255), MARKER_CROSS, 10, 1);
			}

			return displayImage;
		}

	}
	else
	{
		consoleLog(imageType::cclabels, CONSOLECOLOURS::colour::Warning);
	}

	return cv::Mat();
}

void MainWindow::FilterRegionsOnSize(targeterImage& ccim, cv::Mat& binImage, double stdevMaxFactor, double stdevMinFactor, double aspectFactor)
{
	cv::Mat newCentroidsImage, newStats;
	double aspect, objectsLength, area, sum = 0.0, sumsq = 0.0;

	// get the ccimage image
	cv::Mat& centroidsImage = ccim.getCentroidsImage();

	cv::Mat& stats = ccim.getStatsImage();

	if (centroidsImage.rows > 0 && stats.rows >= centroidsImage.rows)
	{
		for (int i = 1; i < centroidsImage.rows; i++)
		{
			int *row = &stats.at<int>(i, 0);
			area = (double)row[CC_STAT_AREA];

			sumsq += area*area;
			sum += area;
		}

		objectsLength = ((double)centroidsImage.rows);

		double mean_val = sum / objectsLength;
		double sample_variance = (sumsq - objectsLength * mean_val * mean_val) / (objectsLength - 1.0);
		double sample_std_deviation = sqrt(sample_variance);

		for (int i = 1; i < centroidsImage.rows; i++)
		{
			int *row = &stats.at<int>(i, 0);

			area = (double)row[CC_STAT_AREA];

			// only append cc regions within shape constraints
			if (area < mean_val + sample_std_deviation*stdevMaxFactor &&
				area > mean_val - sample_std_deviation*stdevMinFactor)
			{
				vector<vector<Point> > contours;

				cv::Mat roi = binImage(cv::Rect(row[CC_STAT_LEFT], row[CC_STAT_TOP], row[CC_STAT_WIDTH], row[CC_STAT_HEIGHT]));
				cv::Mat thr;

				if (roi.channels() > 1)
					cvtColor(roi, thr, CV_BGR2GRAY);
				else
					thr = roi;

				// must be UCHAR 1 channel image
				findContours(thr, contours, cv::noArray(), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

				vector<Point> contour = contours[0];

				if (contour.size() > 4)
				{
					cv::RotatedRect r = cv::fitEllipse(contour);	// seems to always label the shorter side width

																	//	cv::Moments M = cv::moments(contour);
																	//	cv::Point centerT = cv::Point(int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]));

					aspect = ((double)r.boundingRect().width) / ((double)r.boundingRect().height);

					if (((double)r.boundingRect().width) / ((double)r.boundingRect().height) < aspectFactor &&
						((double)r.boundingRect().height) / ((double)r.boundingRect().width) < aspectFactor)
					{
						newStats.push_back(stats.row(i));
						newCentroidsImage.push_back(centroidsImage.row(i));
					}
					else
					{
						consoleLog("target rejected because aspect ratio to large. ratio = " + QString::number(aspect) + " (aspect factor=" + QString::number(aspectFactor) + ")");
					}
				}
				else
				{
					consoleLog("target rejected because contour doesn't have enough points (>4) = " + QString::number(contours.size()));
				}
			}
			else
				consoleLog("target rejected because out of size range, size = " + QString::number(area) + " (size range= " + QString::number(mean_val - sample_std_deviation*stdevMinFactor) + " to " + QString::number(mean_val + sample_std_deviation*stdevMaxFactor) + ")");
		}

		ccim.setCentroidsImage(newCentroidsImage);
		ccim.setStatsImage(newStats);
	}
}


/**
*
*  Filters connected component objects based on shape and size
*
* @author    David Watts
* @since     2017/03/29
*
* FullName   MainWindow::FilterRegions
* Qualifier
* @param     targeterImage & tim
* @param     double stdevMaxFactor
* @param     double stdevMinFactor
* @param     double aspectFactor
* @return    void
* Access     public
*/
void MainWindow::FilterRegionsOnShape(targeterImage& ccim, cv::Mat& binImage, cv::Rect targetROI)
{
	cv::Mat newCentroidsImage, newStats;
	vector<Point> tcontour;
	vector<vector<Point> > tcontours;
	double aspect, objectsLength, area, sum = 0.0, sumsq = 0.0;

	// get the ccimage image
	cv::Mat& centroidsImage = ccim.getCentroidsImage();

	cv::Mat& stats = ccim.getStatsImage();

	if (centroidsImage.rows > 0 && stats.rows >= centroidsImage.rows)
	{
		objectsLength = ((double)centroidsImage.rows);

		// get moments for target image
		if (targetROI.width > 0)
		{
			// get its location in original image
			cv::Mat thr;

			// for all targets /////
			if (binImage.rows > 0)
			{
				cvtColor(binImage(targetROI), thr, CV_BGR2GRAY);

				// must be UCHAR 1 channel image
				findContours(thr, tcontours, cv::noArray(), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

				tcontour = tcontours[0];	// get first region
			}
			//	cv::Moments M = cv::moments(contour);
			//	cv::Point centerT = cv::Point(int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]));
		}

		for (int i = 1; i < centroidsImage.rows; i++)
		{
			int *row = &stats.at<int>(i, 0);

			vector<vector<Point> > contours;

			cv::Mat roi = binImage(cv::Rect(row[CC_STAT_LEFT], row[CC_STAT_TOP], row[CC_STAT_WIDTH], row[CC_STAT_HEIGHT]));
			cv::Mat thr;

			if (roi.channels() > 1)
				cvtColor(roi, thr, CV_BGR2GRAY);
			else
				thr = roi;

			// must be UCHAR 1 channel image
			findContours(thr, contours, cv::noArray(), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

			vector<Point> contour = contours[0];

			if (contour.size() > 4)
			{
				double match_score = 100;

				if (tcontour.size() > 0)
				{
					match_score = cv::matchShapes(tcontour, contour, 2, 0);
				}

				if (tcontour.size() == 0 || match_score < m_settings->ScoreThreshold)	// anyway this keeps care of any ambiguities
				{
					newStats.push_back(stats.row(i));
					newCentroidsImage.push_back(centroidsImage.row(i));
				}
				else
				{
					consoleLog("target rejected on basis of shape. score = " + QString::number(match_score) + " (score threshold=" + QString::number(m_settings->ScoreThreshold) + ")");
				}
				
			}
			else
			{
				consoleLog("target rejected because contour doesn't have enough points (>4) = " + QString::number(contours.size()));
			}
		}
	}

	ccim.setCentroidsImage(newCentroidsImage);
	ccim.setStatsImage(newStats);
}

/**
*
*  Filters connected component objects based on shape and size
*
* @author    David Watts
* @since     2017/03/29
* 
* FullName   MainWindow::FilterRegions
* Qualifier 
* @param     targeterImage & tim 
* @param     double stdevMaxFactor 
* @param     double stdevMinFactor 
* @param     double aspectFactor 
* @return    void
* Access     public 
*/
void MainWindow::FilterRegions(targeterImage& ccim, cv::Mat& binImage, cv::Rect targetROI, double stdevMaxFactor, double stdevMinFactor, double aspectFactor)
{
	cv::Mat newCentroidsImage, newStats;
	vector<Point> tcontour;
	vector<vector<Point> > tcontours;
	double aspect, objectsLength, area, sum = 0.0, sumsq = 0.0;

	// get the ccimage image
	cv::Mat& centroidsImage = ccim.getCentroidsImage();

	cv::Mat& stats = ccim.getStatsImage();
	
	if (centroidsImage.rows > 0 && stats.rows >= centroidsImage.rows)
	{
		for (int i = 1; i < centroidsImage.rows; i++)
		{
			int *row = &stats.at<int>(i, 0);
			area = (double)row[CC_STAT_AREA];

			sumsq += area*area;
			sum += area;
		}

		objectsLength = ((double)centroidsImage.rows);

		double mean_val = sum / objectsLength;
		double sample_variance = (sumsq - objectsLength * mean_val * mean_val) / (objectsLength - 1.0);
		double sample_std_deviation = sqrt(sample_variance);

		// get moments for target image
		if (targetROI.width>0)
		{
			// get its location in original image
			cv::Mat thr;
				
			if (binImage.rows>0)
			{
				cvtColor(binImage(targetROI), thr, CV_BGR2GRAY);

				// must be UCHAR 1 channel image
				findContours(thr, tcontours, cv::noArray(), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

				tcontour = tcontours[0];	// get first region
			}
			//	cv::Moments M = cv::moments(contour);
			//	cv::Point centerT = cv::Point(int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]));
		}
		
		for (int i = 1; i < centroidsImage.rows; i++)
		{
			int *row = &stats.at<int>(i, 0);

			area = (double)row[CC_STAT_AREA];

			// only append cc regions within shape constraints
			if (area < mean_val + sample_std_deviation*stdevMaxFactor &&
				area > mean_val - sample_std_deviation*stdevMinFactor)
			{
				vector<vector<Point> > contours;

				cv::Mat roi = binImage(cv::Rect(row[CC_STAT_LEFT], row[CC_STAT_TOP], row[CC_STAT_WIDTH], row[CC_STAT_HEIGHT]));
				cv::Mat thr;

				if (roi.channels() > 1)
					cvtColor(roi, thr, CV_BGR2GRAY);
				else
					thr = roi;

				// must be UCHAR 1 channel image
				findContours(thr, contours, cv::noArray(), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

				vector<Point> contour = contours[0];

				if (contour.size() > 4)
				{
					cv::RotatedRect r = cv::fitEllipse(contour);	// seems to always label the shorter side width

					//	cv::Moments M = cv::moments(contour);
					//	cv::Point centerT = cv::Point(int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]));

					double match_score = 100;

					if (tcontour.size() > 0)
					{
						match_score = cv::matchShapes(tcontour, contour, 2, 0);
					}

					aspect =  ((double)r.boundingRect().width) / ((double)r.boundingRect().height);	

					if (((double)r.boundingRect().width) / ((double)r.boundingRect().height) < aspectFactor &&
						((double)r.boundingRect().height) / ((double)r.boundingRect().width) < aspectFactor)
					{
						if (tcontour.size() == 0 || match_score < m_settings->ScoreThreshold)	// anyway this keeps care of any ambiguities
						{
							newStats.push_back(stats.row(i));
							newCentroidsImage.push_back(centroidsImage.row(i));
						}
						else
						{
							consoleLog("target rejected on basis of shape. score = " + QString::number(match_score) + " (score threshold="+ QString::number(m_settings->ScoreThreshold) +")");
						}
					}
					else
					{
						consoleLog("target rejected because aspect ratio to large. ratio = " + QString::number(aspect) + " (aspect factor="+ QString::number(aspectFactor) +")");
					}
				}
				else
				{
					consoleLog("target rejected because contour doesn't have enough points (>4) = " + QString::number(contours.size()));
				}
			}
			else
				consoleLog("target rejected because out of size range, size = " + QString::number(area) + " (size range= " + QString::number(mean_val - sample_std_deviation*stdevMinFactor) + " to " + QString::number(mean_val + sample_std_deviation*stdevMaxFactor) + ")");
		}

		ccim.setCentroidsImage(newCentroidsImage);
		ccim.setStatsImage(newStats);
	}
}

void MainWindow::drawShape(cv::Mat& im, drawingShape shape, cv::Scalar col)
{
	int x = MAX(0, MIN(shape.boundingBox.left(), im.cols));
	int y = MAX(0, MIN(shape.boundingBox.top(), im.rows));
	int w = MAX(0, MIN(shape.boundingBox.width(), im.cols));
	int h = MAX(0, MIN(shape.boundingBox.height(), im.rows));

	cv::Rect roi(x, y, w, h);

	// get mask image
	if (shape.type == drawingMode::poly)
	{
		vector <cv::Point> triOut;

		// since poly must be in mask image
		foreach(QPoint p, shape.polygon)
			triOut.push_back(cv::Point(p.x() - shape.boundingBox.left(), p.y() - shape.boundingBox.top()));

		cv::fillConvexPoly(im, triOut, col);
	}
	else if (shape.type == drawingMode::circle)
	{
	
		cv::ellipse(im, cv::Point(im.cols >> 1, im.rows >> 1), cv::Size(im.cols >> 1, im.rows >> 1), 0, 0, 360, col, -1);
	}
	else
	{
		//return dst;   // dst is with correct colour
		cv::rectangle(im, roi, col, -1);
	}
}



/**
*
*  Writes XML of target locations in image
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   MainWindow::writeCentroids
* Qualifier 
* @param     targeterImage & tim 
* @param     QFile & xmlFile 
* @return    void
* Access     public 
*/
/*
void MainWindow::writeCentroids(targeterImage& tim, QFile& xmlFile)
{
	if (tim.getImageFunction() == imageType::cclabels)
	{
		cv::Mat& centroidsImage = tim.getCentroidsImage();
		cv::Mat& stats = tim.getStatsImage();

		QDomDocument doc("MyML");
		QDomElement root = doc.createElement("MyML");
		doc.appendChild(root);

		QDomElement tag = doc.createElement("Greeting");
		root.appendChild(tag);

		QDomText t = doc.createTextNode("Hello World");
		tag.appendChild(t);

		QXmlStreamWriter stream;

		stream.setDevice(&xmlFile);
		stream.writeStartDocument();

		stream.writeStartElement("target_coordinates");

		for (int i = 1; i < centroidsImage.rows; i++)
		{
			double x = centroidsImage.at<double>(i, 0);
			double y = centroidsImage.at<double>(i, 1);
			int *row = &stats.at<int>(i, 0);
			double left = row[CC_STAT_LEFT];
			double top = row[CC_STAT_TOP];
			double width = row[CC_STAT_WIDTH];
			double height = row[CC_STAT_HEIGHT];

			stream.writeStartElement("target");

			stream.writeStartElement("centroid");
			stream.writeAttribute("x", QString::number(x));
			stream.writeAttribute("y", QString::number(y));
			stream.writeEndElement();

			stream.writeStartElement("bounding_rectangle");
			stream.writeAttribute("top", QString::number(top));
			stream.writeAttribute("left", QString::number(left));
			stream.writeAttribute("width", QString::number(width));
			stream.writeAttribute("height", QString::number(height));
			stream.writeEndElement();

			stream.writeEndElement();

			xmlFile.flush();
		}

		stream.writeEndElement();

		stream.writeEndDocument();

		xmlFile.close();
	}
	else
	{
		consoleLog(imageType::cclabels);
	}
}*/



/**
*
*  Finds center coordinates of connected  component regions
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   MainWindow::on_actionFind_Centers_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionFind_Centers_triggered()
{
	std::vector<int> checked = getCheckedImages();
	cv::Mat dst, pIm;

	int ind = getValidImageIndex();

	if (ind >= 0)
	{
		targeterImage& tim = m_ImagesContainer.getImageAt(ind);

		pIm = drawCentroids(tim, cv::Mat(), false);

		if(pIm.rows>0)
		{
			addCVImage(pIm, tim.getUID(), "detected targets mask image", true, imageType::mask, true);

			consoleLog("Now you can use the mask function to combine mask with detection image", CONSOLECOLOURS::colour::Information);
		}
		else
			consoleLog("Unable to detect targets", CONSOLECOLOURS::colour::Information);

	}
}


void MainWindow::on_actionFilter_Binary_Objects_triggered()
{
	// get size distribution 

	// find stdev
	std::vector<int> checked = getCheckedImages();
	cv::Mat dst, pIm;

	int ind = getValidImageIndex();

	if (ind >= 0)
	{
		targeterImage& tim = m_ImagesContainer.getImageAt(ind);

		targeterImage *tarBin = NULL, *tar = NULL;

		int index = tim.getFriendArrayIndexOfType(imageType::cclabels);

		if(index >= 0)
		{
			targeterImage& ccim = m_ImagesContainer.getImageAt(index);

			index = tim.getFriendArrayIndexOfType(imageType::mask);

			if(index >= 0)
				tarBin = m_ImagesContainer.getImageAtPtr(index);
			else
				consoleLog(imageType::mask, CONSOLECOLOURS::colour::Warning);
			
			index = tim.getFriendArrayIndexOfType(imageType::target);
			
			if(index >= 0)
				tar = m_ImagesContainer.getImageAtPtr(index);
			else
				consoleLog(imageType::target, CONSOLECOLOURS::colour::Warning);

			
			if(tarBin != NULL)
			{
				cv::Rect r;

				if (tar != NULL)
					r = tar->getImagePosition();

				// exclude those % > or < than stdev etc
				FilterRegions(ccim, tarBin->getImage(), r , m_settings->StdevLarger, m_settings->StdevSmaller, m_settings->AspectTolerance);
			}
		}
		else
		{
			consoleLog(imageType::cclabels, CONSOLECOLOURS::colour::Warning);
		}
	}
}

/**
*
*  Inverts image black->white etc.
*
* @author    David Watts
* @since     2017/03/17
* 
* FullName   MainWindow::on_actionInvert_triggered
* Qualifier 
* @return    void
* Access     private 
*/
void MainWindow::on_actionInvert_triggered()
{
	int ind = getValidImageIndex();

	if (ind >= 0)
	{
		targeterImage tim = m_ImagesContainer.getImageAt(ind);
		cv::Mat& im = tim.getImage();
		cv::Mat out;

		bitwise_not(im, out);

		addCVImage(out, tim.getUID(), "inverted image", true, m_ImagesContainer.getImageAt(ind).getImageFunction());
	}
	else
	{
		consoleLog(imageType::any, CONSOLECOLOURS::colour::Warning);
	}
}

void MainWindow::on_actionRead_Barcode_triggered()
{
	int ind = getValidImageIndex();
	bool showImage = true;
	bool bFoundRect = false;

	if (ind >= 0)
	{
		targeterImage tim = m_ImagesContainer.getImageAt(ind);
		cv::Mat& im = tim.getImage();
		
		QVector<drawingShape> shapes = ui->display_image->getTargetImage(false, true, ind);
		
		foreach(drawingShape s, shapes)
		{
			if (s.type == drawingMode::rect)
			{
				m_settings->s_BarCodeImageRect = s.boundingBox;
			}
		}

		cv::Mat barcodeImage, gray;

		// must be sufficient image resolution
		if (m_settings->s_BarCodeImageRect.width() > 50 && m_settings->s_BarCodeImageRect.height() > 50)
		{
			bFoundRect = true;
			
			QRect roi = m_settings->s_BarCodeImageRect;

			barcodeImage = im(cv::Rect(roi.x(), roi.y(), roi.width(), roi.height()));
		}
		else
			barcodeImage = im;

		if (barcodeImage.channels() != 1)
			cvtColor(barcodeImage, gray, CV_BGR2GRAY);
		else
			gray = barcodeImage;

		// normalise for illumination
		cv::Mat bim = m_ImageProcessing.fitBackgroundImage(gray);

		cv::Mat corr = gray - bim;

		//QString tag = m_ImageProcessing.scanForBarCodes(im, out, showImage);
		//	QString tag = m_ImageProcessing.getBarcode(im, s.boundingBox);

		QVector<int*> plotlines;
		int size = 0;

		// if true: reads left to right or top to bottom
		if(bFoundRect)
		{
			int* run_length_hist = m_ImageProcessing.getRunLengthHistogram(corr, size);
			plotlines.append(run_length_hist);
			int* threshold_hist = m_ImageProcessing.thresholdOnMinimum(run_length_hist, size, m_settings->BarcodeAutoThreshold, m_settings->BarcodeThreshold);
			plotlines.append(threshold_hist);

			cv::Mat plot_image = HelperFunctions::linePlotImage<int>(plotlines, size, 1, 1024, 512);

			addCVImage(plot_image, tim.getUID(), "run length histogram (threshold line in blue)", true, m_ImagesContainer.getImageAt(ind).getImageFunction());

	/*
			int* newaverage = m_ImageProcessing.fitPolynomial(average, size, 2);

			cv::Mat out2 = HelperFunctions::linePlotImage<int>(size, 1, 512, 512, newaverage);
			addCVImage(out2, tim.getUID(), "moving average fit", true, m_ImagesContainer.getImageAt(ind).getImageFunction());
	*/				

			// threshold histogram
			for (int i = 0; i < size; i++)
				run_length_hist[i] = run_length_hist[i] > threshold_hist[i] ? 1 : 0;
			delete[] threshold_hist;

			corr = HelperFunctions::expandRunLengthImage<int>(run_length_hist, size, corr.cols, corr.rows, gray.type(), gray.channels(), true, true);

			addCVImage(corr, tim.getUID(), "Cleaned bar code image", true, m_ImagesContainer.getImageAt(ind).getImageFunction());

			delete[] run_length_hist;
		}

/*				
		cv::Mat dst;

		if(corr.cols > corr.rows)
			cv::vconcat(gray, out, dst);
		else
			cv::hconcat(gray, out, dst);

		//cv::Mat out = HelperFunctions::linePlotImage<int>(hist, size, 1);
				
*/
		cv::Mat detect_image;

		QString tag = m_ImageProcessing.scanForBarCodes(corr, detect_image, !bFoundRect);

		//QString bar = HelperFunctions::getBarcodeStringfromVector(hist, size);

	//	consoleLog(bar, CONSOLECOLOURS::colour::Information);


		if (tag != "")
		{
			if(!bFoundRect)
				addCVImage(detect_image, tim.getUID(), "is barcode detected", true, m_ImagesContainer.getImageAt(ind).getImageFunction());

			consoleLog("Detected barcode = " + tag, CONSOLECOLOURS::colour::Information);
			m_settings->s_project_ID = tag;
		}
		else
			consoleLog("No barcodes detected in image", CONSOLECOLOURS::colour::Information);
	}
	else
	{
		consoleLog(imageType::any, CONSOLECOLOURS::colour::Warning);
	}

}

void MainWindow::on_actionEqualise_Image_triggered()
{
	int ind = getValidImageIndex();

	if (ind >= 0)
	{
		targeterImage tim = m_ImagesContainer.getImageAt(ind);
		cv::Mat& im = tim.getImage();

		cv::Mat out, gray;

		if (im.channels() != 1)
			cvtColor(im, gray, CV_BGR2GRAY);

		//cv::normalize(gray, out, 255, 0, NORM_MINMAX);
		//cv::equalizeHist(gray, out);

		cv::Ptr<cv::CLAHE> clahe = createCLAHE();
		clahe->setClipLimit(4);

		clahe->apply(gray, out);

		addCVImage(out, tim.getUID(), "histogram equalised image", true, m_ImagesContainer.getImageAt(ind).getImageFunction());
	}


}

// in white regions of binary image sample for targets
void MainWindow::on_actionSample_White_Binary_Regions_triggered()
{
	int threshold = 10;
	int gridSpacing = 10;

	std::vector<int> checked = getCheckedImages();

	if (ui->ImageThumbList->count() > 0 && checked.size() > 0)
	{
		cv::Mat sampleRegionsImage;

		foreach(int i, checked)
		{
			targeterImage tim = m_ImagesContainer.getImageAt(i);
			
			if (tim.imageFunction != imageType::mask)
			{
				cv::Mat binImage = ui->display_image->getBinaryImageFromShapes(i);

				//addCVImage(binImage, tim.getUID(), "binary image", true, tim.getImageFunction());

				ui->display_image->getTargetsFromBinaryImage(binImage, threshold, m_settings->samplingType, m_settings->samplingSpacing, i);
			}
			else
				ui->display_image->getTargetsFromBinaryImage(tim.getImage(), threshold, m_settings->samplingType, m_settings->samplingSpacing, i);
		}
	}
}

void MainWindow::on_actionDetect_lines_triggered()
{
	std::vector<int> checked = getCheckedImages();

	if (ui->ImageThumbList->count() > 0 && checked.size() > 0)
	{
		foreach(int i, checked)
		{
			targeterImage tim = m_ImagesContainer.getImageAt(i);
			cv::Mat& im = tim.getImage();
				
			cv::Mat out = m_ImageProcessing.getLines(im, m_settings->objectColours[drawingItems::hough]);

			if(out.rows>0 && out.cols>0)
				addCVImage(out, tim.getUID(), "hough lines image", true, tim.getImageFunction());
		}

		ui->actionDetect_lines->setChecked(false);
	}
	else
	{
		if(ui->actionDetect_lines->isChecked())
			QFuture<void> t1 = QtConcurrent::run(this, &MainWindow::detectLines);
	}
}
	

void MainWindow::detectLines()
{
	bool isChecked = true;

	if (m_settings->activeCamera == cameraType::none ||
		m_settings->activeCamera == cameraType::overview && basCamera->isOverviewCameraEmpty() ||
		m_settings->activeCamera == cameraType::microscope && basCamera->isMicroscopeCameraEmpty())
	{
		QString s = CAMERATYPE(m_settings->activeCamera);
		consoleLog("detectLines: Error - camera " + s + " not available", CONSOLECOLOURS::colour::Warning);
		return;
	}

	basCamera->openCamera(m_settings->activeCamera);

	while(isChecked)
	{
		cv::Mat im = basCamera->grabImage(m_settings->activeCamera, true);

		if (im.rows > 0 && im.cols > 0)
		{
			cv::Mat out = m_ImageProcessing.getLines(im, m_settings->objectColours[drawingItems::hough]);

			// update view image
			QMetaObject::invokeMethod(this, // obj
				"updateQTImage", // member
				Qt::BlockingQueuedConnection,
				Q_RETURN_ARG(bool, isChecked),
				Q_ARG(cv::Mat, out),
				Q_ARG(QString, "detect lines image"),
				Q_ARG(imageType::imageType, imageType::display),
				Q_ARG(QAction*, ui->actionDetect_lines)); // val1
		}
		else
			consoleLog("detectLines: Error - empty image returned from camera", CONSOLECOLOURS::colour::Warning);
	}

	basCamera->stopGrabbing();
}

void MainWindow::on_actionCalibrate_Camera_triggered()
{
#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	if (ui->ImageThumbList->count() > 0)
	{

		std::vector<int> checked = getCheckedImages();

		if (ui->ImageThumbList->count() > 0 && checked.size() > 0)
		{
			// get all checked images .get
			QFuture<void> t1 = QtConcurrent::run(&m_ImageProcessing, &ImageProcessing::calibrateCamera, m_ImagesContainer.getImages(checked), m_settings.get());
		}
	}
}

void MainWindow::on_actionEdge_Detection_triggered()
{
	std::vector<int> checked = getCheckedImages();

	if (ui->ImageThumbList->count() > 0 && checked.size() > 0)
	{
		foreach(int i, checked)
		{
			targeterImage t = m_ImagesContainer.getImageAt(i);

			cv::Mat& im = t.getImage();

			cv::Mat m = m_ImageProcessing.CannyEdgeDetection(im);

			addCVImage(m, t.getUID(), "canny edge image", true, t.getImageFunction());
		}
	}
}

void MainWindow::on_actionCorner_Detection_triggered()
{
	std::vector<int> checked = getCheckedImages();

	if (ui->ImageThumbList->count() > 0 && checked.size() > 0)
	{
		foreach(int i, checked)
		{
			targeterImage t = m_ImagesContainer.getImageAt(i);

			cv::Mat& im = t.getImage();

			cv::Mat im2 = m_ImageProcessing.CornerDetection(im, m_settings->calibrateNoCols*m_settings->calibrateNoRows);

			addCVImage(im2, t.getUID(), "corrected image", true, t.getImageFunction());
		}
	}
}

void MainWindow::on_actionCorrectImage_triggered()
{
	std::vector<int> checked = getCheckedImages();

	if (ui->ImageThumbList->count() > 0 && checked.size() > 0)
	{
		foreach(int i, checked)
		{
			targeterImage t = m_ImagesContainer.getImageAt(i);

			cv::Mat& im = t.getImage();
			cv::Mat im2;

			cv::Mat map1, map2;

			if(m_settings->activeCamera == cameraType::overview)
				cv::initUndistortRectifyMap(m_settings->calibrationDataOverview.intrinsic_matrix, m_settings->calibrationDataOverview.distortion_coeffs, cv::Mat(), m_settings->calibrationDataOverview.intrinsic_matrix, cv::Size(im.rows, im.cols), CV_16SC2, map1, map2);
			else
				cv::initUndistortRectifyMap(m_settings->calibrationDataMicroscope.intrinsic_matrix, m_settings->calibrationDataMicroscope.distortion_coeffs, cv::Mat(), m_settings->calibrationDataMicroscope.intrinsic_matrix, cv::Size(im.rows, im.cols), CV_16SC2, map1, map2);

			// must be new and empty image
			cv::remap(im, im2, map1, map2, cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());

			std::string pathname = t.name;

			int pos = -1;

			pos = pathname.find_last_of('.');

			if(pos>=0)
				pathname.insert(pos-1, "cal");
			else
				pathname.append(".png");
		
			cv::imwrite(pathname, im2);

			addCVImage(im2, t.getUID(), "corrected image", true, t.getImageFunction());
		}
	}
}

void MainWindow::moveObjective(QPoint pt)
{
	// change image coordinates to stage coordinates

	emit MoveAbsoluteXY(pt.x(), pt.y());
}


/*
void MainWindow::MoveAbsoluteXY(double x, double y)
{
	//m_MicroscopeStages
	//m_MicroscopeStages.MoveAbsoluteXY(x, y);

	QFuture<void> t1 = QtConcurrent::run(&m_MicroscopeStages, &StageManager::MoveAbsoluteXY, x, y);
}
void MainWindow::MoveRelativeXY(double x, double y)
{
	//m_MicroscopeStages.MoveRelativeXY(x, y);
	QFuture<void> t1 = QtConcurrent::run(&m_MicroscopeStages, &StageManager::MoveRelativeXY, x, y);
}
void MainWindow::SendCommandXY(QString cmd)
{
	//m_MicroscopeStages.SendCommandXY(cmd);

	QFuture<void> t1 = QtConcurrent::run(&m_MicroscopeStages, &StageManager::SendCommandXY, cmd);
}
void MainWindow::SetVelocityXY(double velo)
{
	//m_MicroscopeStages.SetVelocityXY(velo);

	QFuture<void> t1 = QtConcurrent::run(&m_MicroscopeStages, &StageManager::SetVelocityXY, velo);
}
void MainWindow::CalibrateXY()
{
	//m_MicroscopeStages.CalibrateXY();

	QFuture<void> t1 = QtConcurrent::run(&m_MicroscopeStages, &StageManager::CalibrateXY);
}
void MainWindow::MeasureRangeXY()
{
	//m_MicroscopeStages.MeasureRangeXY();

	QFuture<void> t1 = QtConcurrent::run(&m_MicroscopeStages, &StageManager::MeasureRangeXY);
}
void MainWindow::ConnectXY()
{
	//m_MicroscopeStages.ConnectXY();

	QFuture<void> t1 = QtConcurrent::run(&m_MicroscopeStages, &StageManager::ConnectXY);
}
void MainWindow::DisconnectXY()
{
	//m_MicroscopeStages.DisconnectXY();

	QFuture<void> t1 = QtConcurrent::run(&m_MicroscopeStages, &StageManager::DisconnectXY);
}

void MainWindow::AbortXY()
{
//	QMetaObject::invokeMethod(&m_MicroscopeStages, "AbortXY", Qt::QueuedConnection);
	
	//m_MicroscopeStages.AbortXY();

	QFuture<void> t1 = QtConcurrent::run(&m_MicroscopeStages, &StageManager::AbortXY);
}


void MainWindow::maskImage(QImage& im, drawingShape shape)
{
#ifdef DEBUGPRINT
qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
QPainterPath path;

if(shape.type == drawingMode::poly)
path.addPolygon(shape.polygon);
else
path.addEllipse(shape.boundingBox);

QImage cutout(im.size(), QImage::Format_ARGB32_Premultiplied);

Q_ASSERT(!cutout.isNull());

if(!cutout.isNull())
{
cutout.fill(Qt::black);

QPainter p(&cutout);
p.setClipPath(path);
p.drawImage(0, 0, im);
p.end();

im = cutout.copy();
}

}
*/

/*
void MainWindow::maskImage(QImage& im, drawingShape shape)
{

QImage cutout(im.size(), im.format());
QPainter painter(&cutout);
QPainterPath path;

qDebug() << "mask image circle" << shape.type <<endl;

if(shape.type == drawingMode::poly)
{
path.addPolygon(shape.polygon);
}
else
{
qDebug() << "mask image circle" << shape.boundingBox <<endl;

QRegion r(shape.boundingBox, QRegion::Ellipse);
painter.setClipRegion(r);
}

painter.drawImage(0, 0, im);

painter.end();
}

// goes in function below
//Mat im;

//HelperFunctions::resizeImagePreserve(*m_pCurrentImage, im, ui->display_image->width(), ui->display_image->height());

//QImage imdisplay = mat_to_qimage_ref(im);

//QImage imdisplay = m_CurrentQImage.scaled(ui->display_image->width(), ui->display_image->height(), Qt::KeepAspectRatio);

//ui->display_image->setPixmap(QPixmap::fromImage(imdisplay));

*/



