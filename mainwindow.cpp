﻿// Targeter - target identification software for EUCALL workpackage 6
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
#include "MultiWatcher.h"
#include "drawingObjects.h"
#include "haar.h"


//#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include <QFutureWatcher>
#include <QFuture>
#include <QMessageBox>

// end QConcurent stuff
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
#include <QTransform>
#include <QtGlobal>
#include <QMatrix4x4>

#include <regex>

#include "opencv2/core.hpp"
#include "opencv/highgui.h"
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/video.hpp"

using namespace cv;
using namespace std;
using namespace QtConcurrent;

Q_DECLARE_METATYPE(ACTIONS::action);

#define CONNECTCAST(class,fun,args) static_cast<void(class::*)args>(&class::fun)

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
MainWindow::MainWindow(QWidget *parent) : basCamera(new BaslerCamera()) ,
											m_settings(new SettingsValues()), 
										//	m_experimentalData(new ExperimentalData()),
											QMainWindow(parent),
											ui(new Ui::MainWindow)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
    //m_CurrentQImage = nullptr;

	m_pStageXY = nullptr;
	m_pStageZ = nullptr;
	//m_pFocusCUDA = nullptr;

    ui->setupUi(this);
	
	// to send these data types over signals slots mechanism
	qRegisterMetaType<cv::Mat>("cv::Mat");
	qRegisterMetaType<QVector<QString> >("QVector<QString>");
	qRegisterMetaType<ACTIONS::action>("ACTIONS::action");
	qRegisterMetaType<FIDUCIAL::position>("FIDUCIAL::position");
	qRegisterMetaType<QTextCursor>("QTextCursor");
	
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

	basCamera->setCameras(QString("21799625"), QString("21799596"));

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

	m_settingsDlg.create(m_settings.data());

	// get settings from serialised file
	deSerialiseSettings();

	// set display to point to image container
	ui->display_image->setImageContainerPointer(&m_ImagesContainer);

	ui->actionReference_fiducial_marks->setEnabled(!m_settings->bLockFiducial);

	ui->display_image->updatePaddTarget(m_settings->bPaddTargetImage, m_settings->numWaveletLevels);

	setUpSlotsSignals();

	// set up stages
	//emit m_pMicroscopeStages.getAvailablePorts();

	//emit m_pMicroscopeStages.assignPorts();
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

	m_pWorkerThreadXY->quit();
	m_pWorkerThreadXY->wait();

	m_pWorkerThreadZ->quit();
	m_pWorkerThreadZ->wait();
	/*
	m_pWorkerThreadCUDA->quit();
	m_pWorkerThreadCUDA->wait();
	*/
	if (m_pWorkerThreadXY != nullptr)
		delete m_pWorkerThreadXY;
	if (m_pWorkerThreadZ != nullptr)
		delete m_pWorkerThreadZ;
	/*
	if (m_pWorkerThreadCUDA != nullptr)
		delete m_pWorkerThreadCUDA;
	
	if (m_pStageXY != nullptr)
		delete m_pStageXY;
	if (m_pStageZ != nullptr)
		delete m_pStageZ;*/
	/*
	if (m_pFocusCUDA != nullptr)
		delete m_pFocusCUDA;
		*/
}

void MainWindow::serialiseSettings(bool fromBackup)
{
	QFile settingsFile;
	QString XMLfilename;

	if (fromBackup)		
		settingsFile.setFileName("targetter_settings_BACKUP.dat");
	else
		settingsFile.setFileName("targetter_settings.dat");
	
	if (settingsFile.open(QIODevice::WriteOnly))
	{
		QDataStream out(&settingsFile);   // we will serialize the data into the file

		m_settings->serialize(out);

		settingsFile.close();
	}
	/*
	if (fromBackup)
		XMLfilename = "targeter_project_BACKUP.xml";
	else
		XMLfilename = m_settings->s_project_FilenamePrefix + m_settings->s_project_Barcode + ".xml";

	XMLWriter projectWriter(this);

	projectWriter.OpenFile(m_settings->s_project_Directory, XMLfilename);

	// only add to settings node
	projectWriter.writeProjectSettings(m_settings.data());
	*/
}

void MainWindow::saveBackup(bool bLoad)
{
	if (bLoad)
		deSerialiseSettings(true);		
	else
		serialiseSettings(true);
}

void MainWindow::deSerialiseSettings(bool fromBackup)
{
	QFile settingsFile;
	QString XMLfilename;

	if (fromBackup)
		settingsFile.setFileName("targetter_settings_BACKUP.dat");
	else
		settingsFile.setFileName("targetter_settings.dat");
	
	if (settingsFile.open(QIODevice::ReadOnly))
	{
		QDataStream in(&settingsFile);   // we will serialize the data into the file
		m_settings->deserialize(in);

		registerFiducialMarks();

		settingsFile.close();
	}
	else
		m_settings->initialize();

	/*
	if (fromBackup || m_settings->s_project_FilenamePrefix == "" && m_settings->s_project_Barcode == "")
		XMLfilename = "targeter_project_BACKUP.xml";
	else
		XMLfilename = m_settings->s_project_FilenamePrefix + m_settings->s_project_Barcode + ".xml";

	// now get project properties
	QMap<QString, QVariant> map;

	XMLWriter projectWriter(this);

	projectWriter.OpenFile(m_settings->s_project_Directory, XMLfilename);

	projectWriter.readProjectInformation(XMLfilename, m_settings.data());
*/
	// update dialog
	m_settingsDlg.initControls();
	
}

/*
emit createTransformationMatrix(QVector3D(3,3,3), QVector3D(6,3,3), QVector3D(3, 6,6));	// test matrix
*/
void MainWindow::registerFiducialMarks()
{
	if (m_settingsDlg.checkFiducialsOrder(m_settings->fiducial_marks_stage, m_settings->fiducial_marks_image, false))
	{
		// create QRect of fiducial positions in image

		QVector3D stageTL = m_settings->fiducial_marks_stage[FIDUCIAL::position::topleft_microscope];
		QVector3D stageTR = m_settings->fiducial_marks_stage[FIDUCIAL::position::topright_microscope];
		QVector3D stageBL = m_settings->fiducial_marks_stage[FIDUCIAL::position::bottomleft_microscope];
		QVector3D stageBR = m_settings->fiducial_marks_stage[FIDUCIAL::position::bottomright_microscope];
		
		QPointF stageImageTL = m_settings->fiducial_marks_image[FIDUCIAL::position::topleft_microscope];
		QPointF stageImageTR = m_settings->fiducial_marks_image[FIDUCIAL::position::topright_microscope];
		QPointF stageImageBL = m_settings->fiducial_marks_image[FIDUCIAL::position::bottomleft_microscope];
		QPointF stageImageBR = m_settings->fiducial_marks_image[FIDUCIAL::position::bottomright_microscope];

		// adjust stage position by offsetting fiducial position in image in microns
		m_settings->fiducial_marks_stageAndImage[FIDUCIAL::position::topleft_microscope] = HelperFunctions::addPointToVector3D(stageTL, stageImageTL*m_settings->mmPerPixel);
		m_settings->fiducial_marks_stageAndImage[FIDUCIAL::position::topright_microscope] = HelperFunctions::addPointToVector3D(stageTR, stageImageTR*m_settings->mmPerPixel);
		m_settings->fiducial_marks_stageAndImage[FIDUCIAL::position::bottomleft_microscope] = HelperFunctions::addPointToVector3D(stageBL, stageImageBL*m_settings->mmPerPixel);
		m_settings->fiducial_marks_stageAndImage[FIDUCIAL::position::bottomright_microscope] = HelperFunctions::addPointToVector3D(stageBR, stageImageBR*m_settings->mmPerPixel);

		QTransform trans;
		QPolygonF imageFiducials;

		imageFiducials.append(m_settings->fiducial_marks_image[FIDUCIAL::position::topleft_overview]);
		imageFiducials.append(m_settings->fiducial_marks_image[FIDUCIAL::position::topright_overview]);
		imageFiducials.append(m_settings->fiducial_marks_image[FIDUCIAL::position::bottomleft_overview]);
		imageFiducials.append(m_settings->fiducial_marks_image[FIDUCIAL::position::bottomright_overview]);

		QPolygonF stageFiducials;

		stageFiducials.append(stageTL.toPointF());
		stageFiducials.append(stageTR.toPointF());
		stageFiducials.append(stageBL.toPointF());
		stageFiducials.append(stageBR.toPointF());

		// if possible to get transformation matrix
		if (QTransform::quadToQuad(imageFiducials, stageFiducials, m_settings->m_coordinateTransform))
			LOGCONSOLE("coordinate transform successfully registered", CONSOLECOLOURS::Information);
		else
			LOGCONSOLE("unable to calculate coordinate transform", CONSOLECOLOURS::Information);

		// now create Fiducials to Stage transformation matrix
		
		// position of fiducial mark in stage coordinates relative to microscope image
		// create transformation matrix that maps the position of objects in stage/image pixel space to fiducial marks (unit axes) space
		createTransformationMatrix(m_settings->fiducial_marks_stageAndImage[FIDUCIAL::position::topleft_microscope],
									m_settings->fiducial_marks_stageAndImage[FIDUCIAL::position::topright_microscope],
									m_settings->fiducial_marks_stageAndImage[FIDUCIAL::position::bottomleft_microscope]);
	}
	else
		LOGCONSOLE("please ensure that fiducial marks correctly registered", CONSOLECOLOURS::Information);
}

void MainWindow::logFeedback(int score, QString name, QString email, QString institute, QString desc)
{
	XMLWriter logWriter(this);

	logWriter.openXMLFile("feedback.xml", QIODevice::ReadWrite);

	logWriter.appendFeedback(score, name, email, institute, desc);
}

void MainWindow::setUpSlotsSignals()
{
	connect(basCamera.data(), &BaslerCamera::processedImage, this, &MainWindow::updateVideoImage);
	connect(basCamera.data(), &BaslerCamera::LOGCONSOLE, this, CONNECTCAST(MainWindow, LOGCONSOLE, (QString, CONSOLECOLOURS::colour)));

	connect(ui->ImageThumbList, &QListWidget::customContextMenuRequested, this, &MainWindow::ProvideContextMenu);
	connect(ui->ImageThumbList, &QListWidget::itemClicked, this, &MainWindow::onThumbImageClick);

	// slots for communication from printqlabel class
	connect(ui->display_image, &PaintQLabel::disablePanButton, this, &MainWindow::disablePanButton);
	connect(ui->display_image, &PaintQLabel::setTargetArea, this, &MainWindow::setTargetArea);
	connect(ui->display_image, &PaintQLabel::unsetDrawingButtons, this, &MainWindow::unsetDrawingButtons);
	connect(ui->display_image, &PaintQLabel::StatusBarMessage, this, &MainWindow::StatusBarMessage);
	connect(ui->display_image, &PaintQLabel::addFiducialMark, this, &MainWindow::addFiducialMark);
	connect(ui->display_image, &PaintQLabel::moveObjective, this, &MainWindow::moveObjective);

	connect(ui->display_image, &PaintQLabel::setSamplingDistance, this, &MainWindow::setSamplingDistance);

	// slot to get values back from modeless dialog
	connect(&m_settingsDlg, &SettingsDialog::sendSettings, this, &MainWindow::receiveSettings);
	connect(&m_settingsDlg, &SettingsDialog::logFeedback, this, &MainWindow::logFeedback);

	connect(&m_settingsDlg, &SettingsDialog::SETFIDUCIALPOSITION, ui->display_image, &PaintQLabel::setFiducialPosition);
	connect(&m_settingsDlg, &SettingsDialog::getCOMPORTS, this, &MainWindow::getAvailablePorts);

	// logging from Image Processing functions run in separate thread
	connect(&m_ImageProcessing, &ImageProcessing::LOGCONSOLE, this, CONNECTCAST(MainWindow, LOGCONSOLE, (QString, CONSOLECOLOURS::colour)));

	// XY STAGE SLOTS ///////////////////////////////
	m_pStageXY = new StageControlXY;
	m_pWorkerThreadXY = new QThread;

	// make stage control object a worker thread object
	m_pStageXY->moveToThread(m_pWorkerThreadXY);

	// Marzhauser stage commands called from settings dialog
	connect(&m_settingsDlg, &SettingsDialog::MoveAbsoluteXY, m_pStageXY, &StageControlXY::MoveAbsolute);
	connect(&m_settingsDlg, &SettingsDialog::MoveRelativeXY, m_pStageXY, &StageControlXY::MoveRelative);
	connect(&m_settingsDlg, &SettingsDialog::SendCommandXY, m_pStageXY, &StageControlXY::SendCommand);
	connect(&m_settingsDlg, &SettingsDialog::SetVelocityXY, m_pStageXY, &StageControlXY::SetVelocity);
	connect(&m_settingsDlg, &SettingsDialog::CalibrateXY, m_pStageXY, &StageControlXY::Calibrate);
	connect(&m_settingsDlg, &SettingsDialog::MeasureRangeXY, m_pStageXY, &StageControlXY::MeasureRange);

	connect(&m_settingsDlg, &SettingsDialog::ConnectXY, m_pStageXY, &StageControlXY::Connect);
	connect(&m_settingsDlg, &SettingsDialog::DisconnectXY, m_pStageXY, &StageControlXY::Disconnect);
	connect(&m_settingsDlg, &SettingsDialog::AbortXY, m_pStageXY, &StageControlXY::Abort);
	connect(&m_settingsDlg, &SettingsDialog::SetJoystickXY, m_pStageXY, &StageControlXY::SetJoystick);
	connect(&m_settingsDlg, &SettingsDialog::LOGCONSOLE, this, CONNECTCAST(MainWindow, LOGCONSOLE, (QString, CONSOLECOLOURS::colour)));
	
	connect(&m_settingsDlg, &SettingsDialog::LockFiducial, this, &MainWindow::enableFiducial);
	connect(&m_settingsDlg, &SettingsDialog::saveBackup, this, &MainWindow::saveBackup);
	connect(&m_settingsDlg, &SettingsDialog::moveToFiducialFromOverview, this, &MainWindow::moveObjective);
	connect(&m_settingsDlg, &SettingsDialog::createTransformationMatrix, this, &MainWindow::createTransformationMatrix);

	connect(&m_settingsDlg, &SettingsDialog::setGrid, ui->display_image, &PaintQLabel::setGrid);
	connect(&m_settingsDlg, &SettingsDialog::updatePaddTarget, ui->display_image, &PaintQLabel::updatePaddTarget);
	
	
	// Marzhauser stage commands called from main program
	connect(this, &MainWindow::MoveAbsoluteXY, m_pStageXY, &StageControlXY::MoveAbsolute);
	connect(this, &MainWindow::MoveRelativeXY, m_pStageXY, &StageControlXY::MoveRelative);
	connect(this, &MainWindow::SendCommandXY, m_pStageXY, &StageControlXY::SendCommand);
	connect(this, &MainWindow::SetVelocityXY, m_pStageXY, &StageControlXY::SetVelocity);
	connect(this, &MainWindow::CalibrateXY, m_pStageXY, &StageControlXY::Calibrate);
	connect(this, &MainWindow::MeasureRangeXY, m_pStageXY, &StageControlXY::MeasureRange);
	connect(this, &MainWindow::ConnectXY, m_pStageXY, &StageControlXY::Connect);
	connect(this, &MainWindow::DisconnectXY, m_pStageXY, &StageControlXY::Disconnect);
	connect(this, &MainWindow::AbortXY, m_pStageXY, &StageControlXY::Abort);
	connect(this, &MainWindow::connectToPortXY, m_pStageXY, &StageControlXY::assignPort);
	connect(this, &MainWindow::getPositionXY, m_pStageXY, CONNECTCAST(StageControlXY, updatePositions, (bool)));
	connect(this, &MainWindow::reportCOMPORTS, &m_settingsDlg, &SettingsDialog::updateCOMPORTS);

#ifdef _HAVE_IMAGEMAGICK
	connect(&m_imageReadWrite, &ImageReadWrite::LOGCONSOLE, this, CONNECTCAST(MainWindow, LOGCONSOLE, (QString, CONSOLECOLOURS::colour)));
#endif
	connect(&m_Timer, &QTimer::timeout, this, &MainWindow::logDot);

	connect(m_pStageXY, &StageControlXY::LOGCONSOLE, this, CONNECTCAST(MainWindow, LOGCONSOLE, (QString, CONSOLECOLOURS::colour)));
	connect(m_pStageXY, &StageControlXY::ACTIONCOMPLETED, this, &MainWindow::StageMovementCompleted);
	connect(m_pStageXY, &StageControlXY::UPDATEPOSITIONS, this, &MainWindow::updatePositionXY);
	connect(m_pStageXY, &StageControlXY::CONNECTEDTOPORT, this, &MainWindow::StageConnectedXY);
	connect(m_pStageXY, &StageControlXY::STAGEMOVED, this, &MainWindow::stageMovedXY);

	// clean up
	connect(m_pWorkerThreadXY, &QThread::finished, m_pStageXY, &StageControlXY::deleteLater);
	m_pWorkerThreadXY->start();

	// Z STAGE SLOTS ///////////////////////////////
	m_pStageZ = new StageControlZ;
	m_pWorkerThreadZ = new QThread;

	// make stage control object a worker thread object
	m_pStageZ->moveToThread(m_pWorkerThreadZ);

	// signal slots
	connect(&m_settingsDlg, &SettingsDialog::MoveAbsoluteZ, m_pStageZ, &StageControlZ::moveAbsolute);
	connect(&m_settingsDlg, &SettingsDialog::MoveRelativeZ, m_pStageZ, &StageControlZ::MoveRelative);
	connect(&m_settingsDlg, &SettingsDialog::SendCommandZ,  m_pStageZ, &StageControlZ::SendCommand);
	connect(&m_settingsDlg, &SettingsDialog::ConnectZ,      m_pStageZ, &StageControlZ::Connect);
	connect(&m_settingsDlg, &SettingsDialog::DisconnectZ,   m_pStageZ, &StageControlZ::Disconnect);
	connect(&m_settingsDlg, &SettingsDialog::SetKeypadZ, m_pStageZ, &StageControlZ::SetKeypad);
	connect(&m_settingsDlg, &SettingsDialog::stopMotionZ, m_pStageZ, &StageControlZ::stopMotion);

	connect(this, &MainWindow::MoveAbsoluteZ, m_pStageZ, &StageControlZ::moveAbsolute);

	connect(m_pStageZ, &StageControlZ::LOGCONSOLE, this, CONNECTCAST(MainWindow, LOGCONSOLE, (QString, CONSOLECOLOURS::colour)));
	connect(m_pStageZ, &StageControlZ::ACTIONCOMPLETED, this, &MainWindow::StageMovementCompleted);
	connect(m_pStageZ, &StageControlZ::UPDATEPOSITION, this, &MainWindow::updatePositionZ);
	connect(m_pStageZ, &StageControlZ::STAGEMOVED, this, &MainWindow::stageMovedZ);
	connect(this, &MainWindow::getPositionZ, m_pStageZ, CONNECTCAST(StageControlZ, updatePosition, (bool)));

	// clean up
	connect(m_pWorkerThreadZ, &QThread::finished, m_pStageZ, &StageControlZ::deleteLater);

	m_pWorkerThreadZ->start();

	// XY STAGE SLOTS ///////////////////////////////
	/*
	m_pFocusCUDA = new focusingCUDA;
	m_pWorkerThreadCUDA = new QThread;

	// make stage control object a worker thread object
	m_pFocusCUDA->moveToThread(m_pWorkerThreadCUDA);
	*/
	//connect(this, &MainWindow::getFocusCUDA, &m_FocusCUDA, &focusingCUDA::getFocusScore);
	//connect(&m_FocusCUDA, &focusingCUDA::setFOCUS, this, &MainWindow::addFocusValue);

	//m_pWorkerThreadCUDA->start();

	// detect com ports
	getAvailablePorts();
}

void MainWindow::updatePositionXY(bool bFid, double x, double y)
{
	// update position
	m_settings->m_stage_position_XY_X = x;
	m_settings->m_stage_position_XY_Y = y;

	// updates position label 
	m_settingsDlg.updatePositions();

	if (bFid)
		emit getPositionZ(bFid);
}

void MainWindow::updatePositionZ(bool bFid, double z)
{
	// update position
	m_settings->m_stage_position_Z = z;

	// updates position label 
	m_settingsDlg.updatePosition();

	if(bFid)
	{
		// then this has to be called
		m_settingsDlg.setFiducial();

		consoleLog("Fiducial Mark added: " + QString::number(m_settings->m_image_position_XY_X) + "," + 
												QString::number(m_settings->m_image_position_XY_Y) + "," + 
												QString::number(m_settings->m_stage_position_XY_X) + "," +
												QString::number(m_settings->m_stage_position_XY_Y) + "," +
												QString::number(m_settings->m_stage_position_Z),
												CONSOLECOLOURS::colour::Information);
	}
}

// called from drawing label
void MainWindow::addFiducialMark(FIDUCIAL::position pos, QPoint p)
{
	m_settings->m_image_position_XY_X = p.x();
	m_settings->m_image_position_XY_Y = p.y();

	m_settings->fiducialPos = pos;

	m_settingsDlg.updateFiducialComboIndex();

	// get stage position from Stage manager then add fiducial (in case of manual movements)
	emit getPositionXY(true);
}

void MainWindow::assignPortZ(QVector<QString> AvailablePorts, QString excludePort)
{
	for (int i = 0; i < AvailablePorts.length(); i++)
	{
		if (AvailablePorts[i] == excludePort)
			continue;

		if (m_pStageZ->connectToPort(AvailablePorts[i]))
		{
			StageConnectedZ(AvailablePorts[i]);
			break;
		}
	}
}

void MainWindow::StageConnectedXY(QString port)
{
	// update dialog label
	m_settingsDlg.updateCONNECTPORT(true, port);

	// connect to available Z
	assignPortZ(m_AvailablePorts, port);
}

void MainWindow::StageConnectedZ(QString port)
{
	// update dialog label
	m_settingsDlg.updateCONNECTPORT(false, port);
}

void MainWindow::getAvailablePorts()
{
	TCHAR lpTargetPath[5000]; // buffer to store the path of the COMPORTS
	DWORD test;
	bool gotPort = 0; // in case the port is not found
	QVector<QString> ports;

	for (int i = 0; i < 255; i++) // checking ports from COM0 to COM255
	{
		QString ComName = "COM" + QString::number(i); // converting to COM0, COM1, COM2

		test = QueryDosDevice((LPWSTR)ComName.utf16(), (LPWSTR)lpTargetPath, 5000);

		// Test the return value and error if any
		if (test != 0) //QueryDosDevice returns zero if it didn't find an object
		{
			m_AvailablePorts.push_back(ComName); // add to the ComboBox
			ports.push_back(ComName);
			gotPort = 1; // found port
		}

		if (::GetLastError() == ERROR_INSUFFICIENT_BUFFER) //in case buffer got filled
		{
			lpTargetPath[10000]; // in case the buffer got filled, increase size of the buffer.
			continue;
		}
	}

	if (!gotPort) // if not port
		m_AvailablePorts.push_back(QString("No Active Ports Found")); // to display error message incase no ports found

	emit reportCOMPORTS(ports);
	emit connectToPortXY(ports, "");

	consoleLog("COM ports scanned");
}

void MainWindow::enableFiducial(bool bEnable)
{
	ui->actionReference_fiducial_marks->setEnabled(!bEnable);

	if (!bEnable)
		ui->display_image->setDrawingMode(drawingMode::none);
}

void MainWindow::StageMovementCompleted(QString message)
{
	consoleLog(message, CONSOLECOLOURS::colour::Information);

	QApplication::restoreOverrideCursor();
}

void MainWindow::shutDownInstruments()
{
	basCamera->detachCameras();
}

void MainWindow::addTargeterImage(QExplicitlySharedDataPointer<targeterImage> tim, QAction* pAction)
{
	addCVImage(tim, nullptr, true);

	LogProcessing(false);	// stop timer from showing dots in console

	if (pAction != nullptr)
		pAction->setChecked(false);
}

void MainWindow::addMatImage(cv::Mat img, QString imagename, imageType::imageType type, QAction* pAction)
{
	addCVImage(img, imagename, true, type, true);

	LogProcessing(false);	// stop timer from showing dots in console

	if (pAction != nullptr)
		pAction->setChecked(false);
}

bool MainWindow::updateQTImage(cv::Mat img, QString imagename, QAction* pAction)
{
	// update last cv image trigger show image on paint control
	QExplicitlySharedDataPointer<targeterImage> pTar = m_ImagesContainer.getLastImagePtr();
	
	if (pTar == nullptr)
	{
		addCVImage(img, imagename);

		pTar = m_ImagesContainer.getLastImagePtr();
	}
	else
		pTar->addImage(img);

	// sets the last image as the one to be displayed
	ui->display_image->setImageIndex(m_ImagesContainer.getNumImages()-1);

	if (pAction != nullptr)
		return pAction->isChecked();
	else
		return false;
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
void MainWindow::logDot() {
	/*
	//QString msg = "<font color=\"green\"><span>. </span></font>";
	QTextCursor c = ui->consoleDisplay->textCursor();
	c.movePosition(QTextCursor::End);
	ui->consoleDisplay->appendPlainText(". ");

	//QMetaObject::invokeMethod(ui->consoleDisplay, "appendHtml", Qt::QueuedConnection, Q_ARG(QString, msg));
	*/
	ui->consoleDisplay->moveCursor(QTextCursor::End);
	ui->consoleDisplay->textCursor().insertHtml(". ");
	ui->consoleDisplay->moveCursor(QTextCursor::End);
};

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

QString MainWindow::getSaveFilename(QExplicitlySharedDataPointer<targeterImage> im, int& number, bool bIsCompleteImage)
{
	if (im->filepathname == "")									// create filename
		return m_settings->s_project_Directory + m_settings->s_project_FilenamePrefix + "_" + QString::number(number++) + "_" + im->getUID().toString() + ".png";
	else
	{
		QString filename = QString::fromStdString(im->filepathname);

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
void MainWindow::SaveImageOrXML()
{
#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	std::vector<int> checked = getCheckedImages();

	QFileDialog dialog;
	QString filename, filepath = "";
	int ct = 0;

	if (ui->ImageThumbList->count() > 0 && checked.size() > 0)
	{
		
		int fileNumber = 0;	
		
		QVector<QSharedPointer<drawingShape>> shapes;

		// get current active image check if it is checked to save then check for sub-images
		foreach(int i, checked)
		{
			QExplicitlySharedDataPointer<targeterImage> tim = m_ImagesContainer.getImageAt(i);

			// does image already have a filename
			if (i == m_currentImageDisplayedIndex)	// current image
				shapes = ui->display_image->getImageShapes(false, true, i);

			// if first image
			
			filename = getSaveFilename(tim, fileNumber, shapes.length() == 0);

			cv::Mat im = tim->getImage();

			// first file ask user if they want to modify file name (or path)
			if (ct == 0)
			{
				// ask user to modify filename
				filename = dialog.getSaveFileName(this, "Save Image File",
					filename, tr("Image Files [*.jpg, *.jpeg, *.jp2, *.bmp, *.png , *.pgm, *.pbm, *.ppm *.tiff *.tif]"),
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
					QRect r = shapes[j]->boundingBox;
					cv::Rect cvr = cv::Rect(r.x(), r.y(), r.width(), r.height());
					
					cv::Mat rectImage = im(cvr);

					if (ct <= 0)
					{
						// save the image
#ifdef _HAVE_IMAGEMAGICK
						m_imageReadWrite.writeImage(filename, rectImage);
#else
						imwrite(filename.toLocal8Bit().data(), rectImage);
#endif
					}
					else
					{
						QString file = filename;
						QString sRect = "_(" + QString::number(shapes[j]->boundingBox.left()) + "," + QString::number(shapes[j]->boundingBox.top()) + ":" +
							QString::number(shapes[j]->boundingBox.right()) + "," + QString::number(shapes[j]->boundingBox.bottom()) + ")";

						file.insert(file.lastIndexOf('.'), sRect);

						// save the image
#ifdef _HAVE_IMAGEMAGICK
						m_imageReadWrite.writeImage(file, rectImage);
#else
						imwrite(file.toLocal8Bit().data(), rectImage);
#endif
					}
				}
			}
			else
			{
				// save the image
#ifdef _HAVE_IMAGEMAGICK
					m_imageReadWrite.writeImage(filename, im); 
#else
					imwrite(filename.toLocal8Bit().data(), im);
#endif
			}
		

			DBOUT("image written to file: " << filename.toLocal8Bit().data() << std::endl);

			ct++;
		}
		//cv::imwrite(fileName.toLocal8Bit().data(), *m_pCurrentImage );
	}

	if (ct == 0)
	{
		QString XMLfilename = m_settings->s_project_FilenamePrefix + m_settings->s_project_Barcode + ".xml";

		filename = dialog.getSaveFileName(this, "Save XML project File", XMLfilename, tr("XML project Files [*.xml]"),
										  0, QFileDialog::DontUseNativeDialog);

		saveXMLProject(filename);

	}
}

void MainWindow::openXMLProject(QString filename)
{
	consoleLog("Saving XML file: " + filename, CONSOLECOLOURS::Information);

	QFile file(filename);

	if (!file.open(QIODevice::ReadOnly) || !m_projectXMLDOM.setContent(&file))
		consoleLog("Failed to parse XML file: " + filename, CONSOLECOLOURS::Information);
	else
		readProjectDataFromDOM();
}

void MainWindow::saveXMLProject(QString filename)
{
	consoleLog("Saving XML file: " + filename, CONSOLECOLOURS::Information);

	writeProjectDataToDOM();	// ensure DOM is up to date

	QFile XMLFile(filename);

	XMLFile.open(QIODevice::WriteOnly);

	QTextStream stream(&XMLFile);
	stream.seek(0);
	stream.setCodec("UTF-8");
	stream.setDevice(&XMLFile);
	stream << m_projectXMLDOM.toString();
	stream.flush();

	XMLFile.close();
}

void MainWindow::readProjectDataFromDOM()
{
	// read settings from m_projectXMLDOM
}

void MainWindow::writeProjectDataToDOM()
{
	// write settings to m_projectXMLDOM

	m_projectXMLDOM.clear();

	XMLWriter writer;

	QDomElement containerTag = m_projectXMLDOM.createElement("targeter");

	// now add all settings
	writer.writeProjectInfoToDOM(m_projectXMLDOM, containerTag, m_settings.data());

	// now add all the targets
	writer.writeTargetsToDOM(m_projectXMLDOM, containerTag, m_processedImages);

}

/*
void MainWindow::writeImageTargetstoDOM(QString parentFilename, int imageIndex)
{
	QVector<QSharedPointer<drawingShape>> shapes = ui->display_image->getImageShapes(false, true, imageIndex);

	XMLWriter writer(this);
	writer.OpenFile(m_settings->s_project_Directory, m_settings->s_project_FilenamePrefix + m_settings->s_project_Barcode + ".xml");

	writer.appendImageInformationXML(parentFilename, "auto detection image", shapes, QSharedPointer<StageMovement>(new StageMovement()));

	// write to xml file
	writer.writePositions(m_processedImages);
}


void MainWindow::writeTargetPositionsToDOM()
{
		if(m_experimentalData->m_detected_targets.size()>0)
		{
			int ind = getValidImageIndex();


			//// no bounding box for clicked points
			//QVector<QRect> r;

			//XMLWriter targetWriter(this);

			//QString XMLfilename = m_settings->s_project_FilenamePrefix + m_settings->s_project_Barcode + ".xml";

			//targetWriter.openXMLFile(XMLfilename, QIODevice::ReadWrite);

		
			// check to see if there is any region annotation

			// get targets - should be added to global list of targets in experimental data
			QVector<QSharedPointer<drawingShape>> shapes = ui->display_image->getImageShapes(false, true, ind);

			XMLWriter writer(this);

			writer.OpenFile(m_settings->s_project_Directory, m_settings->s_project_FilenamePrefix + m_settings->s_project_Barcode + ".xml");

			writer.appendImageInformationXML(tim->getFileName(), "single image", shapes, QSharedPointer<StageMovement>(new StageMovement()));

			// write to xml file
			writer.writePositions(m_experimentalData->m_detected_targets);
		}
}
*/


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
		cv::Mat& im = m_ImagesContainer.getImageAt(getValidImageIndex())->getImage();

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
	QString jsonData = "";
	fh_setCurrentFile(qs);

#ifdef _HAVE_IMAGEMAGICK
	cv::Mat im = m_imageReadWrite.readImage(qs, jsonData);

	// add json data to targeter image 
#else
	cv::Mat im = imread(qs.toLocal8Bit().data());
#endif
	if (im.rows <= 0 || im.cols <= 0)
	{
		consoleLog("Invalid image - " + qs, CONSOLECOLOURS::colour::Warning);
		return;
	}

	addCVImage(im, qs, true, imageType::display, false, fileName, jsonData);
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
QUuid MainWindow::addCVImage(cv::Mat im, QString imageName, bool bRGBSwap, imageType::imageType type, bool bDisplay, QString fileName, QString jsonData)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	QVector3D ptFid = getMosaicPositionFromName(imageName, true);
	QVector3D ptStage = getMosaicPositionFromName(imageName, false);

	QExplicitlySharedDataPointer<targeterImage> tim =  createTargeterImage(im, ptFid, ptStage, imageName, bRGBSwap, type, bDisplay, fileName, jsonData);

	addCVImage(tim, imageName, bRGBSwap);

	return tim->getUID();
}

void MainWindow::updateVideoImage(cv::Mat im) 
{
	// if no targeter image existing, create one to hold the video image
	if(m_ImagesContainer.getNumImages() > 0 && m_ImagesContainer.getLastImagePtr()->getImageFunction() == imageType::imageType::video)
		updateQTImage(im);
	else
		addCVImage(im, "captured image", true, imageType::video);
}

QExplicitlySharedDataPointer<targeterImage> MainWindow::createTargeterImage(cv::Mat im, QVector3D fiducials, QVector3D stage, QString imageName,
																			bool bRGBSwap, imageType::imageType type, bool bDisplay, QString fileName, QString jsonData)
{
#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
	QExplicitlySharedDataPointer<targeterImage> tim = QExplicitlySharedDataPointer<targeterImage>(new targeterImage(&m_ImagesContainer));

	std::string name = imageName.toStdString();
	std::string fname = fileName.toStdString();

	QUuid uid = QUuid::createUuid();

	if (fname == "")
		fname = (m_settings->s_project_Directory + m_settings->s_project_FilenamePrefix + "_" + uid.toString() + ".png").toStdString();

	if (imageName == "overview camera image")
		tim->setCameraType(cameraType::overview);
	else if (imageName == "microscope camera image")
		tim->setCameraType(cameraType::microscope);
	else
		tim->setCameraType(cameraType::none);

	if (jsonData != "")
	{
		QJsonObject jsonObj = HelperFunctions::ObjectFromString(jsonData);

		if (!jsonObj.isEmpty())
		{
			// add json settings to targeter Image
			tim->addJSONDATA(jsonObj);
		}
	}

	tim->addImageEx(im, uid, type, name, name, fname);

	tim->setFiducialPosition(fiducials);
	tim->setStagePosition(stage);

	return tim;
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
* @param     QExplicitlySharedDataPointer<targeterImage> & tim 
* @param     QString imageName 
* @param     bool bRGBSwap 
* @return    void
* Access     public 
*/
void MainWindow::addCVImage(QExplicitlySharedDataPointer<targeterImage> tim, QString imageName, bool bRGBSwap)
{
#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	if (imageName == "")
		addQImageThumbnail(tim, QString::fromStdString(tim->name));
	else
		addQImageThumbnail(tim, imageName);

	m_ImagesContainer.addImage(tim);

	//m_currentImageDisplayedIndex = m_ImagesContainer.getNumImages() - 1;

	DisplayImage();
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

QString MainWindow::limitString(const QString& aString, int maxLength) {
	
	if (aString.length() <= maxLength)
		return aString;

	QString ELLIPSIS = "...";

	float spacePerPart = (maxLength - ELLIPSIS.length()) / 2.0;
	QString beforeEllipsis = aString.left(std::ceil(spacePerPart));
	QString afterEllipsis = aString.right(std::floor(spacePerPart));

	return beforeEllipsis + ELLIPSIS + afterEllipsis;
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
		QExplicitlySharedDataPointer<targeterImage> t = m_ImagesContainer.getImageAt(row);

		imageType::imageType type = t->getImageFunction();

		s = QString::fromStdString(t->getName());

		if (type == imageType::target)
			s = "target image";
		else if (type == imageType::test)
			s = "detection image";

		QString filename = s.section("/", -1);

		ui->ImageThumbList->item(row)->setText(limitString(filename, 15));
	}
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
void MainWindow::addQImageThumbnail(QExplicitlySharedDataPointer<targeterImage> tim, QString imageName)
{
#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	QImage& qim = tim->getQTImage();
	imageType::imageType type = tim->getImageFunction();

	QImage iconImage = copyImageToSquareRegion(qim, ui->display_image->palette().color(QWidget::backgroundRole()));

	QListWidgetItem* pItem = new QListWidgetItem(QIcon(QPixmap::fromImage(iconImage)), nullptr);//QFileInfo(qs).fileName());

	pItem->setData(Qt::UserRole, "thumb" + QString::number(ui->ImageThumbList->count()));

	QString strTooltip = tim->toString();

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

QlistWidgetItem* pItem = new QlistWidgetItem(QIcon(QPixmap::fromImage(qim)), nullptr);//QFileInfo(qs).fileName());

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
void MainWindow::OpenImageOrXML()
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
		fileNames = dialog.getOpenFileNames(this, tr("Open Image or XML file"), st, tr("Image Files (*.jpg *.jpeg *.jp2 *.bmp *.png *.gif *.tif *.tiff);;XML files (*.xml)"), nullptr, QFileDialog::DontUseNativeDialog);
	}
	catch (...) {
		DBOUT("error opening file");
	}

    QMutableStringListIterator i(fileNames); // pass list as argument

    while (i.hasNext()) 
	{
        QString qs = i.next();

		if (qs.contains(".xml"))
		{
			openXMLProject(qs);

			// read target information from file
			//xmlWriter.readXMLFile(qs, m_settings.data(), m_experimentalData.get());
		}
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
		if (m_currentImageDisplayedIndex <m_ImagesContainer.getNumImages() && !m_ImagesContainer.getImageAt(m_currentImageDisplayedIndex)->getQTImage().isNull())
		{
			return m_currentImageDisplayedIndex;
		}
		else    // handle case of invalid index, set to last image in list
		{
			for (int i = m_ImagesContainer.getNumImages() - 1; i >= 0; i--)
			{
				if (!m_ImagesContainer.getImageAt(i)->getQTImage().isNull())
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
    OpenImageOrXML();
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

		QVector<QExplicitlySharedDataPointer<targeterImage>> images = m_ImagesContainer.getImages(check);

        cv::Mat pMat = FocusStack::processImageStack4(images, check, this);

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
		QVector<QExplicitlySharedDataPointer<targeterImage>> images = m_ImagesContainer.getImages(check);

		foreach(int item, check)
		{
			cv::Mat m = images[item]->getImage();

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
   SaveImageOrXML();
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
void MainWindow::setTargetArea(QSharedPointer<drawingShape> shape)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

    qDebug() <<m_ImagesContainer.getNumImages() << endl;

	if(m_currentImageDisplayedIndex >= 0)
	{
		createMaskImage(m_ImagesContainer.getImageAt(m_currentImageDisplayedIndex), shape);
	}
	else
		consoleLog(imageType::any, CONSOLECOLOURS::colour::Warning);
}

void MainWindow::StatusBarMessage(QString msg)
{
	this->statusBar()->showMessage(msg);
}

void MainWindow::getHistograms(cv::Mat orginal_image, cv::Mat& intensityHist, cv::Mat& hueHist, bool bProcessGrayscale, bool accumulate)
{
	cv::Mat hsvImage, image1_gray;
	int histSize = 256;
	float range[] = { 0, histSize };
	const float* histRange = { range };
	bool uniform = true;
	
	int i, w1 = orginal_image.cols, h1 = orginal_image.rows;

	if (orginal_image.channels()==1)
	{
		cv::calcHist(&orginal_image, 1, 0, Mat(), intensityHist, 1, &histSize, &histRange, uniform, accumulate);
	}
	else if (HelperFunctions::isGrayImage(orginal_image) || bProcessGrayscale)
	{
		cv::cvtColor(orginal_image, image1_gray, CV_BGR2GRAY);
		cv::calcHist(&image1_gray, 1, 0, Mat(), intensityHist, 1, &histSize, &histRange, uniform, accumulate);
	}
	else
	{
		cv::cvtColor(orginal_image, hsvImage, CV_BGR2HLS);

		std::vector<cv::Mat> hsv_planes;
		split(hsvImage, hsv_planes);

		cv::calcHist(&hsv_planes[1], 1, 0, Mat(), intensityHist, 1, &histSize, &histRange, uniform, accumulate);
		histSize = 180;
		range[1] = histSize;
		const float* histRangeHue = { range };
		cv::calcHist(&hsv_planes[0], 1, 0, Mat(), hueHist, 1, &histSize, &histRangeHue, uniform, accumulate);
	}
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
* @param     QExplicitlySharedDataPointer<targeterImage> & tim 
* @return    void
* Access     public 
*/
void MainWindow::createMaskImage(QExplicitlySharedDataPointer<targeterImage> orginal_image, QSharedPointer<drawingShape> shape)
{
#ifdef DEBUGPRINT
    qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
	cv::Mat mask, dst;
	cv::Mat& im = orginal_image->getImage();

	orginal_image->setImageType(imageType::test);
	orginal_image->setName(orginal_image->getDefaultName());

	QRect intersected = shape->boundingBox.intersected(QRect(QPoint(0, 0), QSize(im.rows, im.cols)));
	
	int w = shape->boundingBox.width();
	int h = shape->boundingBox.height();

	cv::Rect roi(shape->boundingBox.left(), shape->boundingBox.top(), w, h);

	// check for valid shape
	if(roi.x<0 || roi.y<0 || roi.width==0 || roi.height ==0 || roi.width > im.cols || roi.height > im.rows)
		return;

	if(m_settings->bCorrectBackGround)
	{
		cv::Mat out, im2;
		im2 = m_ImageProcessing.subtractBackground(im, out);

		// get HLS histograms of parent image save them in target object
		// get histogram from parent image	
		// save to settings for finding targets
		getHistograms(im2, m_settings->coocMatrix->intensityHist, m_settings->coocMatrix->hueHist, false);
	}
	else
	{	
		// get HLS histograms of parent image save them in target object
		// get histogram from parent image	
		// save to settings for finding targets
		getHistograms(im, m_settings->coocMatrix->intensityHist, m_settings->coocMatrix->hueHist, false);

	}


	// copy data to new image - deep copy!
	im(roi).copyTo(dst);

    cv::Mat out = cv::Mat(roi.height, roi.width, im.type(), Scalar(0,0,0));

    // get mask image
    if(shape->type == drawingMode::poly)
    {
        // convert polygon to opencv polygon
        mask = cv::Mat(roi.height, roi.width, im.type(), Scalar(0, 0, 0));

        vector <cv::Point> triOut;

        // since poly must be in mask image
        foreach(QPoint p, shape->polygon)    
            triOut.push_back(cv::Point(p.x() - shape->boundingBox.left(), p.y() - shape->boundingBox.top()));

        cv::fillConvexPoly(mask, triOut, Scalar( 255, 255, 255));
    }
    else if(shape->type == drawingMode::circle)
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

	QExplicitlySharedDataPointer<targeterImage> target_image = QExplicitlySharedDataPointer<targeterImage>(new targeterImage(&m_ImagesContainer));

	/// end get histogram

	target_image->setImageType(imageType::target);

	target_image->addImage(dst);

	target_image->setImagePosition(roi);

	QExplicitlySharedDataPointer<targeterImage> mask_image = QExplicitlySharedDataPointer<targeterImage>(new targeterImage(&m_ImagesContainer));

	if (shape->type == drawingMode::circle || shape->type == drawingMode::poly)
	{
		int* pImage = new int[w*h];

		for (int i = 0; i < w; i++)
			for (int j = 0; j < h; j++)
				pImage[i + j*w] = (int)(mask.at<Vec3b>(j, i)[0] > 0 ? 1 : 0);

		target_image->set1DImage(pImage, imageType::mask);
		target_image->setMaskType(shape->type);

		// set 1D image for mask image as well
		int* pImageMask = new int[w*h];
		memcpy(pImageMask, pImage, w*h*sizeof(int));

		mask_image->set1DImage(pImageMask, imageType::mask);
		mask_image->setMaskType(shape->type);
	}

	mask_image->setImageType(imageType::mask);

	mask_image->addImage(mask);
	mask_image->setName("target mask image");
	mask_image->setImagePosition(roi);

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
			QExplicitlySharedDataPointer<targeterImage> tim = m_ImagesContainer.getImageAt(i);

			if (tim->imageFunction != imageType::mask)
			{
				cv::Mat binImage = ui->display_image->getBinaryImageFromShapes(i);

				addCVImage(binImage, "binary mask image", true, imageType::mask);
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

void MainWindow::on_actionAnnotate_Shape_triggered()
{
	int ind = getValidImageIndex();
	bool showImage = true;
	bool bFoundRect = false;

	if (ind >= 0)
	{
		QExplicitlySharedDataPointer<targeterImage> tim = m_ImagesContainer.getImageAt(ind);
		cv::Mat& im = tim->getImage();

		// only used temp cannot store anything
	//	QVector<drawingShape> shapes = ui->display_image->getTargetImage(false, true, ind);

		bool bSelectedOnly = false;

		QVector<QSharedPointer<drawingObject>> drawingObjectList = tim->getDrawingObjects();

		// if any of the shapes are selected only process those
		for (int i = 0; i < drawingObjectList.length(); i++)
		{
			QSharedPointer<drawingObject> pObj = drawingObjectList.at(i);

			if (pObj->m_bSelected)
				bSelectedOnly = true;
		}

		for (int i = 0; i < drawingObjectList.length(); i++)
		{
			QSharedPointer<drawingObject> pObj = drawingObjectList.at(i);
		
			// if no shapes are selected then process all otherwise just the selected ones
			if (pObj->m_type == drawingMode::rect && (!bSelectedOnly || (bSelectedOnly && pObj->m_bSelected)))
			{
				// 
				ui->display_image->highLightShape(pObj, true);

				m_shapeAnnotationDlg.setValues(pObj->ID, pObj->name, pObj->desc, pObj->regionType);

				if (m_shapeAnnotationDlg.exec())
					m_shapeAnnotationDlg.GetValues(pObj->ID, pObj->name, pObj->desc, pObj->regionType);
				
				ui->display_image->highLightShape(pObj, false);
			}
		}
	}
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
		if (m_ImagesContainer.getImageAt(ind)->drawingObjects.size() == 0)
			consoleLog("You have to draw on the image (rectangle, circle, polygon) before producing a region of interest image", CONSOLECOLOURS::colour::Warning);
		else
			ui->display_image->getImageShapes(true);
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
	if (m_ImagesContainer.getImageAt(ind)->getImageFunction() == type)
		m_ImagesContainer.getImageAt(ind)->setImageType(imageType::display);
	else
		m_ImagesContainer.getImageAt(ind)->setImageType(type);
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

	if (getValidImageIndex() < 0)
		ui->display_image->setImageIndex(m_ImagesContainer.getNumImages() - 1);
	
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
		ui->display_image->setDrawingMode(drawingMode::sampleSpacing);
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
			{
				addCVImage(image, "overview camera image");

				QString filename = m_settings->s_project_Directory + m_settings->s_project_FilenamePrefix + "_" + id.toString() + ".png";
#ifdef _HAVE_IMAGEMAGICK
				m_imageReadWrite.writeImage(filename, image);
#else
				imwrite(filename.toLocal8Bit().data(), image);
#endif

				DBOUT("camera image written to file: " << filename.toLocal8Bit().data() << std::endl);
			}
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
				addCVImage(image, "microscope camera image");
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
		if (m_ImagesContainer.getImageAt(checked[i])->getImageFunction() == imageType::mask)
		{
			maskIndex = checked[i];
			break;
		}
	}

	if (maskIndex >= 0)
	{
		cv::Mat& mask = m_ImagesContainer.getImageAt(maskIndex)->getImage();

		if (ui->ImageThumbList->count() > 0 && checked.size() > 1)
		{
			// delete image in index check
			for (int i = 0; i < checked.size(); i++)
			{
				if (checked[i] == maskIndex)
					continue;

				int c = m_ImagesContainer.getImageAt(checked[i])->Cols();
				int r = m_ImagesContainer.getImageAt(checked[i])->Rows();

				if (mask.rows != r || mask.cols != c)
				{
					// enlarge mask image by copying to larger image
					cv::Mat newMask;

					cv::resize(mask, newMask, m_ImagesContainer.getImageAt(checked[i])->Size());

					m_ImagesContainer.getImageAt(checked[i])->getImage().copyTo(dst, newMask);
				}
				else
					m_ImagesContainer.getImageAt(checked[i])->getImage().copyTo(dst, mask);

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
	m_settingsDlg.create(m_settings.data());

	setHistogramImage();

	m_settingsDlg.show();
}

void MainWindow::on_action_New_triggered()
{
	m_settingsDlg.create(m_settings.data());

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
		cv::Mat& im = m_ImagesContainer.getImageAt(ind)->getImage();
		cv::Mat out;

		if (m_settings->ThresholdType == thresholdType::cluster2 || m_settings->ThresholdType == thresholdType::posterize)
			out = m_ImageProcessing.HistogramClusteringGray(im, m_settings->NoClustersThreshold);
		else
			out = m_ImageProcessing.Threshold(im, m_settings->threshold_min, m_settings->threshold_max, m_settings->ThresholdType);

		addCVImage(out, "threshold image", true, imageType::mask, true);
	}
	else
		consoleLog(imageType::any, CONSOLECOLOURS::colour::Warning);
}

void MainWindow::on_actionRemoveBlackPixels_triggered()
{
	int ind = getValidImageIndex();

	if (ind >= 0)
	{
		cv::Mat& im = m_ImagesContainer.getImageAt(ind)->getImage();

		Mat bin, pbin = cv::Mat(im.rows, im.cols, CV_8UC1);
	
		cv::cvtColor(im, bin, cv::COLOR_BGR2GRAY, 1);

		FocusStack::FillMissingPixels<uchar>(bin, pbin, false);

		addCVImage(pbin, "remove black pixels image", true, imageType::display, true);
	}
	else
		consoleLog(imageType::any, CONSOLECOLOURS::colour::Warning);
}

void MainWindow::on_actionBackground_fit_triggered()
{
	int ind = getValidImageIndex();

	if (ind >= 0)
	{
		cv::Mat im = m_ImagesContainer.getImageAt(ind)->getImage();

		cv::Mat bim, dst;
		dst = m_ImageProcessing.subtractBackground(im, bim);

		addCVImage(bim, "background image", true, imageType::background, true);
		addCVImage(dst, "corrected image", true, imageType::display, true);
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
		cv::Mat& im = m_ImagesContainer.getImageAt(ind)->getImage();
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
		QExplicitlySharedDataPointer<targeterImage> tim = m_ImagesContainer.getImageAt(ind);

		if (tim->getImageFunction() == imageType::mask)
		{
			QExplicitlySharedDataPointer<targeterImage> ccim = getConnectedComponents(tim->getImage());

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
* @return    targeterImage
* Access     public 
*/
QExplicitlySharedDataPointer<targeterImage> MainWindow::getConnectedComponents(cv::Mat& im)
{
	cv::Mat bin, out, stats, centroids;
	cv::Mat labels;

	if(im.channels()>1)
		cv::cvtColor(im, bin, cv::COLOR_BGR2GRAY, 1);
	else
		bin = im;

	// create new ccimage
	QExplicitlySharedDataPointer<targeterImage> ccim = QExplicitlySharedDataPointer<targeterImage> (new targeterImage(&m_ImagesContainer));

	out = m_ImageProcessing.getConnectedComponentImage(bin, labels, stats, centroids);

	ccim->setLabelsImage(labels);

	ccim->setCentroidsImage(centroids);
	ccim->setStatsImage(stats);
	ccim->setLabelsImage(labels);

	ccim->setImageType(imageType::cclabels);
	ccim->setName("labeled image");

	//cv::cvtColor(labels, bin, cv::COLOR_GRAY2BGR, 3);

	ccim->addImage(out);

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
	LogProcessing(true);
	QFuture<void> t1 = QtConcurrent::run(this, &MainWindow::getScoreImage);
}

void MainWindow::getScoreImage()
{
	int imageIndex = -1;

	QExplicitlySharedDataPointer<targeterImage> tim = createScoreImage(imageIndex);

	if (tim->Rows() > 0 && tim->Cols()>0)
	{
		QString s("score image ");

		s.append(ALGOSTRINGS(m_settings->algorithmType));

		QMetaObject::invokeMethod(this, // obj
			"addTargeterImage", // member
			Qt::BlockingQueuedConnection,
			Q_ARG(QExplicitlySharedDataPointer<targeterImage>, tim),
			Q_ARG(QAction*, ui->actionDetect_lines)); // val1
	}
	else
	{
		consoleLog(imageType::any, CONSOLECOLOURS::colour::Warning);
	}
}

void MainWindow::LogProcessing(bool bStart)
{
	if (bStart)
	{
		ui->consoleDisplay->textCursor().insertHtml("<br>");
		m_Timer.start(1000);
	}
	else
	{
		m_Timer.stop();
		ui->consoleDisplay->textCursor().insertHtml("<br>");
	}
}

QVector<QExplicitlySharedDataPointer<targeterImage>> MainWindow::findTargetImages(int& imageIndex)
{
	QVector<QExplicitlySharedDataPointer<targeterImage>> targetImages;
	bool bFoundTest = false;

	// get vector list of training images from targeterImages
	for (int i = m_ImagesContainer.getNumImages() - 1; i >= 0; i--)
	{
		QExplicitlySharedDataPointer<targeterImage> m = m_ImagesContainer.getImageAt(i);

		if (m->getImageFunction() == imageType::target)
		{
			targetImages.push_back(m);
		}
		else if (!bFoundTest && m->getImageFunction() == imageType::test)
		{
			bFoundTest = true;
			imageIndex = i;
		}
	}

	return targetImages;
}

QExplicitlySharedDataPointer<targeterImage> MainWindow::createScoreImage(QVector<QExplicitlySharedDataPointer<targeterImage>> targetImages, 
																		 QExplicitlySharedDataPointer<targeterImage> testImage)
{
	QExplicitlySharedDataPointer<targeterImage> tim = QExplicitlySharedDataPointer<targeterImage>(new targeterImage(&m_ImagesContainer));
	cv::Mat scoreImage;

	if (targetImages.size() > 0 && (testImage != nullptr && !testImage->isNULL()))
	{
		tim->setImageType(imageType::score);

		if (m_settings->algorithmType<0 || m_settings->algorithmType>algoType::LASTALGO)
			m_settings->algorithmType = algoType::COOC;

		// get score image
		if (m_settings->algorithmType == algoType::COOC || m_settings->algorithmType == algoType::FASTCOOC)
		{
			scoreImage = m_FindTargets.ColourOccuranceHistogram(targetImages, testImage, (m_settings->coocMatrix).data(), 
											m_settings->distance, m_settings->distanceBins, m_settings->cluster, false, 
											m_settings->bProcessGrayscale, m_settings->algorithmType == algoType::FASTCOOC, 
											m_settings->bCorrectBackGround);
		}
		else if (m_settings->algorithmType == algoType::LAPLACIAN)
		{
			QMetaObject::invokeMethod(this, "LOGCONSOLE", Qt::BlockingQueuedConnection, Q_ARG(QString, "function not yet implemented"), Q_ARG(CONSOLECOLOURS::colour, CONSOLECOLOURS::colour::Information));
			scoreImage = m_FindTargets.LaplacianFindObject(targetImages, testImage, m_settings->distance, m_settings->cluster);
		}
		else if (m_settings->algorithmType == algoType::HAAR)
		{
			scoreImage = m_FindTargets.FindTargetsHaar(targetImages, testImage, m_settings->numWaveletLevels);
		}
		else if (m_settings->algorithmType == algoType::LAWS)
		{
			scoreImage = m_FindTargets.lawsTextureFeatures(targetImages, testImage, m_settings->bCorrectBackGround);
		}
		else if(CV_TM_SQDIFF <= m_settings->algorithmType && m_settings->algorithmType <= CV_TM_CCOEFF_NORMED)
		{
			scoreImage = m_FindTargets.CVMatching(targetImages, testImage, m_settings->algorithmType, m_settings->bCorrectBackGround);
		}
		else
		{
			QMetaObject::invokeMethod(this, "LOGCONSOLE", Qt::BlockingQueuedConnection, Q_ARG(QString, "incorrect algorithm specified"), Q_ARG(CONSOLECOLOURS::colour, CONSOLECOLOURS::colour::Warning));
		}

		if (scoreImage.rows > 0)
			tim->addImage(scoreImage);
		else
			QMetaObject::invokeMethod(this, "LOGCONSOLE", Qt::BlockingQueuedConnection, Q_ARG(QString, "something went wrong - score image not created"), Q_ARG(CONSOLECOLOURS::colour, CONSOLECOLOURS::colour::Warning));
	}
	else
	{
		QString msg;
		if (targetImages.size() == 0)
			msg = "You need to set a target ";
		if (testImage == nullptr || testImage->isNULL())
			msg += "and a test ";

		msg += "image first";

		QMetaObject::invokeMethod(this, "LOGCONSOLE", Qt::BlockingQueuedConnection, Q_ARG(QString, msg), Q_ARG(CONSOLECOLOURS::colour, CONSOLECOLOURS::colour::Warning));
	}

	QMetaObject::invokeMethod(this, "LogProcessing", Qt::BlockingQueuedConnection, Q_ARG(bool, false));

	return tim;
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
QExplicitlySharedDataPointer<targeterImage> MainWindow::createScoreImage(int& imageIndex)
{
	QVector<QExplicitlySharedDataPointer<targeterImage>> targetImages;

	QExplicitlySharedDataPointer<targeterImage> testImage = QExplicitlySharedDataPointer<targeterImage> (new targeterImage(&m_ImagesContainer));

	imageIndex = -1;

	// get test/target images from image list
	targetImages = findTargetImages(imageIndex);

	testImage = m_ImagesContainer.getImageAt(imageIndex);

	return createScoreImage(targetImages, testImage);
}

void MainWindow::on_actionTrainTarget_triggered()
{
	QVector<QExplicitlySharedDataPointer<targeterImage>> targetImages;

	int imageIndex = -1;

	// get test/target images from image list
	targetImages = findTargetImages(imageIndex);

	QExplicitlySharedDataPointer<targeterImage> testImage = m_ImagesContainer.getImageAt(imageIndex);

	if(targetImages.length()>0)
		trainTargetImage(targetImages, testImage);	// when target extracted from image image needs to be clustered
	else
		consoleLog("no target images found");
}

void MainWindow::trainTargetImage(QVector<QExplicitlySharedDataPointer<targeterImage>> targetImages, QExplicitlySharedDataPointer<targeterImage> parentImage)
{
	QExplicitlySharedDataPointer<targeterImage> tim = QExplicitlySharedDataPointer<targeterImage>(new targeterImage(&m_ImagesContainer));
	cv::Mat scoreImage;

	if (targetImages.size() > 0)
	{
		tim->setImageType(imageType::score);

		if (m_settings->algorithmType<0 || m_settings->algorithmType>algoType::LASTALGO)
			m_settings->algorithmType = algoType::COOC;

		// get score image
		if (m_settings->algorithmType == algoType::COOC || m_settings->algorithmType == algoType::FASTCOOC)
		{
			m_FindTargets.trainColourOccuranceHistogram(targetImages, parentImage, (m_settings->coocMatrix).data(), 
														m_settings->distance, m_settings->distanceBins, m_settings->cluster, false,
														m_settings->bProcessGrayscale, m_settings->algorithmType == algoType::FASTCOOC);
			
			for (int j = 0; j < MIN(5, m_settings->coocMatrix->coDIMY); j++){
				QString s="";
				for (int i = 0; i < MIN(5, m_settings->coocMatrix->coDIMZ); i++){
					QString t;
					t.sprintf("%.3e", m_settings->coocMatrix->coMatrixIntensity[i + j*m_settings->coocMatrix->coDIMX + m_settings->coocMatrix->coDIMX*m_settings->coocMatrix->coDIMY]);
					s+=t + "\t";
				}
				LOGCONSOLE(s + " ... ");
			}
			LOGCONSOLE(" ... ");
		}
		else if (m_settings->algorithmType == algoType::LAWS)
		{
			m_FindTargets.trainLawsTextureFeatures(targetImages, m_settings->lawsHistTarget, m_settings->lawsHistBiases);
			for (int j = 0; j < m_settings->lawsHistTarget.length(); j++) {
				QString s = "";
				for (int i = 0; i < MIN(5, m_settings->lawsHistTarget[j].rows); i++) {
					QString t;
					t.sprintf("%.3e", m_settings->lawsHistTarget[j].at<float>(i));
					s += t + "\t";
				}
				LOGCONSOLE(s + " ... ");
			}
			LOGCONSOLE(" ... ");

		}
		else
		{
			QMetaObject::invokeMethod(this, "LOGCONSOLE", Qt::BlockingQueuedConnection, Q_ARG(QString, "incorrect algorithm specified"), Q_ARG(CONSOLECOLOURS::colour, CONSOLECOLOURS::colour::Warning));
		}

	}
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
	LogProcessing(true);
	QFuture<void> t1 = QtConcurrent::run(this, &MainWindow::getTargetImage);
}

void MainWindow::getTargetImage()
{
	int imageIndex = -1;

	QVector<QExplicitlySharedDataPointer<targeterImage>> targetImages;

	QExplicitlySharedDataPointer<targeterImage> testImage = QExplicitlySharedDataPointer<targeterImage>(new targeterImage(&m_ImagesContainer));

	// get test/target images from image list
	targetImages = findTargetImages(imageIndex);

	testImage = m_ImagesContainer.getImageAt(imageIndex);

	QExplicitlySharedDataPointer<targeterImage> tim = createScoreImage(targetImages, testImage);

	if (tim->Rows() > 0 && tim->Cols() > 0)
	{
		cv::Mat im = getTargetPositions(tim->getImage(), testImage, imageIndex);

		//writeImageTargetstoXML(tim->getFileName(), imageIndex);

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


void MainWindow::getTargetLocations(QVector<QExplicitlySharedDataPointer<targeterImage>> targetImages, 
									QExplicitlySharedDataPointer<targeterImage> detectImage)
{
	int imageIndex = -1;
	/*
	XMLWriter writer(this);

	writer.OpenFile(m_settings->s_project_Directory, m_settings->s_project_FilenamePrefix + m_settings->s_project_Barcode + ".xml");
	*/
	// get score image
	QExplicitlySharedDataPointer<targeterImage> tim = createScoreImage(targetImages, detectImage);

	if (tim->Rows() > 0 && tim->Cols() > 0)
	{
		cv::Mat im = getTargetPositions(tim->getImage(), detectImage, imageIndex);

		// write to xml file
		//writer.writePositions(m_experimentalData->m_detected_targets);
	}
	else
	{
		consoleLog(imageType::any, CONSOLECOLOURS::colour::Warning);
	}
}

/*
double x = targetPoints[i].x();
double y = targetPoints[i].y();

x *= micronsToPixels;
y *= micronsToPixels;

x += imageOffsetToFiducials.x();
y += imageOffsetToFiducials.y();

double z = imageOffsetToFiducials.z()>=0?imageOffsetToFiducials.z():0;

output += "x:" + QString::number(x) + " y:" + QString::number(y) + " z:" + QString::number(imageOffsetToFiducials.z()) + "\n";
*/

void MainWindow::getTargetPositionsFromImage(cv::Mat& centroidsImage, cv::Mat& stats, QVector<QPoint>& pts, QVector<QRect>& rects)
{
	// empty lists
	pts.clear();
	rects.clear();

	for (int i = 1; i < centroidsImage.rows; i++)
	{
		double x = centroidsImage.at<double>(i, 0);
		double y = centroidsImage.at<double>(i, 1);

		int *row = &stats.at<int>(i, 0);

		// convert to fiducial coordinates
		pts.append(QPoint(x, y));
		
		rects.append(QRect(row[cv::CC_STAT_LEFT], row[cv::CC_STAT_TOP], row[cv::CC_STAT_WIDTH], row[cv::CC_STAT_HEIGHT]));
	}
}

//************************************
//
//	Gets all target positions from images writes to experimental data structure
//
// Method:    on_actionSave_Target_Positions_triggered
// FullName:  MainWindow::on_actionSave_Target_Positions_triggered
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void  MainWindow::on_actionSave_Target_Positions_triggered()
{
	QVector3D vect = QVector3D(0, 0, 0);

	for(int ind=0; ind<m_ImagesContainer.getNumImages(); ind++)
	{
		QExplicitlySharedDataPointer<targeterImage> tim = m_ImagesContainer.getImageAt(ind);

		vect = tim->getPositionStage();

		if (vect.x() < 0 || vect.y() < 0)
		{
			vect = QVector3D();
			consoleLog("image offset not found, positions relative to image not fiducials origin", CONSOLECOLOURS::Warning);
		}

		// get all target positions from image
		QVector<QPoint> targetPoints = ui->display_image->targetPoints();
		QVector<Target> targetList;
		
		for (int i = 0; i < targetPoints.size(); i++)
		{
			if (!targetPoints[i].isNull())
			{
				QPoint ptTarget = targetPoints[i];

				double x = targetPoints[i].x();
				double y = targetPoints[i].y();

				// convert from pixels to mm's
				x *= m_settings->mmPerPixel;
				y *= m_settings->mmPerPixel;

				// add image offset in mm
				x += vect.x();
				y += vect.y();

				double z = vect.z() >= 0 ? vect.z() : 0;

				// relative to fiducials
				Target target;
				target.position = getRelativePosition(QVector3D(x, y, z));
				target.ID = i;
				target.image = tim->getFileName();
				target.imagePosition = QPoint(x, y);
				target.region = QRect(x,y, 1, 1);

				targetList.append(target);
			}
		}

		ImageData imdata;

		imdata.filename = tim->getFileName();
		imdata.FrameID = tim->getFrameID();
		imdata.patternRegion = tim->getPatternRegion();
		imdata.shapeType = drawingMode::cross;	
		imdata.scanRegionIndex = 0;
		imdata.SubFrameID = tim->getSubFrameID();
		imdata.subRegionID = tim->getSubRegionID();

		imdata.targetList.append(targetList);

		m_processedImages.append(imdata);

		//writeTargetPositionsToXML();
	}
}



QVector<QPoint> MainWindow::makeIndexes(QVector<QPointF> positions)
{
	QVector<QPoint> indexes;

	// need to tell the orientation of area before organizing
	if (positions.length() > 0)
	{
		// sort images based on positions
		rasterSortVectors(positions);

		int x = 0, y = 0;

		indexes.append(QPoint(x, y));

		for (int i = 1; i < positions.length(); i++)
		{
			if (positions[i].y() > positions[i - 1].y())
				y++;
			else if (positions[i].y() < positions[i - 1].y())
				y = 0;

			if (positions[i].x() > positions[i - 1].x())
				x++;
			else if (positions[i].x() < positions[i - 1].x())
				x = 0;

			indexes.append(QPoint(x, y));
		}
	}

	return indexes;
}

void MainWindow::on_actionCreate_Image_Mosaic_triggered()
{
	QVector<cv::Mat> images;
	QVector<QPointF> positions;
	QVector<QPoint> indexPositions;

	std::vector<int> checked = getCheckedImages();
	cv::Mat dst, pIm;
	bool bOK = false;
	int maskIndex = -1;
	int len = checked.size();
	int width = sqrt(len);

	// get selected images
	for (int i = 0; i < len; i++)
	{
		QExplicitlySharedDataPointer<targeterImage>tar = m_ImagesContainer.getImageAt(checked[i]);

		QString filename = QString::fromStdString(tar->filepathname);

		QVector3D pt = getMosaicPositionFromName(filename);

		if(tar->getImageIndex().x() >= 0 && tar->getImageIndex().y())
		{
			indexPositions.append(tar->getImageIndex());
		}
		else
		{
			// if no position in file exif then check name
			if (pt.x() < 0 && pt.y() < 0)
				pt = getMosaicPositionFromName(QString::fromStdString(tar->getName()));

			if (pt.x() >= 0 && pt.y() >= 0)
				positions.append(pt.toPointF());
			else
				positions.append(QPoint(i%width, i / width));	// no info in filename then use count;
		}
	
		images.append(tar->getImage());
	}

	if(images.size()>0)
	{
		// default number of images in row
		int noOfImagesInRow = m_settings->mosaicImageCols;

		cv::Mat mosaicImage;

		if (indexPositions.size() >= images.size())
		{
			mosaicImage = createMosaicImage(images, indexPositions);
		}
		else if(positions.size() >= images.size())
		{
			QVector<QPoint> indexes = makeIndexes(positions);
			mosaicImage = createMosaicImage(images, indexes);
		}
		else
			consoleLog("Some or all of selected images have no indexing information, mosaic will be square and may be unordered!", CONSOLECOLOURS::colour::Warning);

		if (mosaicImage.rows>0 && mosaicImage.cols>0)
		{
			// pass in positions here? except sizes are different from image
			addCVImage(mosaicImage, "mosaic image", true, imageType::mosaic, true);
		}
	}
}

// extract out image position from file name

// QString filename = pathname + "_stageXYZ[" + QString::number(absolutePosition.x()) + "," + QString::number(absolutePosition.y()) + "," + QString::number(absolutePosition.z()) + "]" +
// +"_fidXYZ[" + QString::number(relativePosition.x()) + "," + QString::number(relativePosition.y()) + "," + QString::number(relativePosition.z()) + "]" + ".png";

QVector3D MainWindow::getMosaicPositionFromName(QString str, bool relative)
{
	bool ok = true;
	QString pos;

	if (relative)
		pos = "_fid";
	else
		pos = "_stage";

	int startX = str.lastIndexOf(pos);
	
	startX = str.indexOf("[", startX);
	int endX = str.indexOf("]", startX);

	float x = -1, y = -1, z = -1;

	if(startX != -1 & endX != -1 && startX<endX)
	{
		QString nums = str.mid(startX + 1, endX - startX-1);

		QStringList lstr = nums.split(",");

		if(lstr.length() == 3)
		{
			QString s = lstr.at(0);
			float val = s.toFloat(&ok);
			if (ok)	x = val;

			s = lstr.at(1);
			val = s.toFloat(&ok);
			if (ok)	y = val;

			s = lstr.at(2);
			val = s.toFloat(&ok);
			if (ok)	z = val;
		}
	}

	return QVector3D(x, y, z);
}



bool MainWindow::compareQPointF(const QPointF& first, const QPointF& second)
{
	if (first.x() < second.x())
		return true;
	else if (first.x() > second.x())
		return false;
	else
	{
		if (first.y() < second.y())
			return true;
		else
			return false;
	}
}

void MainWindow::rasterSortVectors(QVector<QPointF>& positions)
{
	// do K-means in loop up to number of points 
	qSort(positions.begin(), positions.end(), compareQPointF);
}

void MainWindow::setSamplingDistance(QSharedPointer<QPolygon> poly)
{
	m_settings->samplingOffset = poly->at(1) - poly->at(0);
	m_settings->samplingSpacing = poly->at(2) - poly->at(1);

	m_settings->samplingOffset = QPoint(abs(m_settings->samplingOffset.x()), abs(m_settings->samplingOffset.y()));
	m_settings->samplingSpacing = QPoint(abs(m_settings->samplingSpacing.x()), abs(m_settings->samplingSpacing.y()));

	m_settingsDlg.updateSamplingSpacing();
}

// look at imags positions and organise 
cv::Mat MainWindow::createMosaicImage(QVector<cv::Mat> images, QVector<QPoint> indexes)
{
	int w = images[0].cols, h = images[0].rows;
	bool bSameSize = true;

	for (int i = 0; i < images.size(); i++)
	{
		cv::Mat im = images[i];

		if (w != images[i].cols || h != images[i].rows)
		{
			bSameSize = false;
			break;
		}
	}

	cv::Mat mosaicImage;

	if(bSameSize)
	{
		int w = images[0].cols;
		int h = images[0].rows;

		if(indexes.length()>0)
		{
			int maxx = -1, maxy = -1;

			for(int i=0;i<indexes.length();i++)
			{
				maxx = max(indexes[i].x(), maxx);
				maxy = max(indexes[i].y(), maxy);
			}

			int nw = (maxx+1)*w;
			int nh = (maxy+1)*h;
		
			mosaicImage = cv::Mat(nh, nw, images[0].type());

			mosaicImage.setTo(0);

			for (int i = 0; i<images.length(); i++)
				images[i].copyTo(mosaicImage(Rect(w*indexes[i].x(), h*indexes[i].y(), images[i].cols, images[i].rows)));
		}
		else
		{
			int imRow = min(images.size(), m_settings->mosaicImageCols);
			int no_rows = ceil(double(images.size()) / double(imRow));

			int nh = (int)(h * no_rows);
			int nw = (int)(w* imRow);

			mosaicImage = cv::Mat(nh, nw, images[0].type());

			mosaicImage.setTo(0);
		
			for (int j = 0, posY = 0, ct=0; j < no_rows; j++, posY += h)
			{
				for (int i = 0, posX=0; i < imRow && ct < images.size(); i++, posX += w)
				{
					images[ct].copyTo(mosaicImage(Rect(posX, posY, images[ct].cols, images[ct].rows)));

					ct++;
				}
			}
		}
	}
	else
		consoleLog("Images not the same size!", CONSOLECOLOURS::colour::Warning);

	return mosaicImage;
}

cv::Mat MainWindow::getTargetPositions(cv::Mat scoreImage, QExplicitlySharedDataPointer<targeterImage> detectImage, int imageIndex)
{
	int index = -1;

	if (!scoreImage.empty())
	{
		cv::Mat binImage, targets;

		// use standard threshold method
		if (m_settings->ThresholdType == thresholdType::cluster2 || m_settings->ThresholdType == thresholdType::posterize)
			binImage = m_ImageProcessing.HistogramClusteringGray(scoreImage, m_settings->NoClustersThreshold);
		else
			binImage = m_ImageProcessing.Threshold(scoreImage, m_settings->threshold_min, m_settings->threshold_max, m_settings->ThresholdType);

		cv::Mat labels, stats, centroids;
		int connectivity_8 = 8;

		QExplicitlySharedDataPointer<targeterImage> tarCC = getConnectedComponents(binImage);

		return getTargetsFromLabelledImage(tarCC, binImage, detectImage, detectImage->getImage(), imageIndex);
	}
	else
		return cv::Mat();
}

cv::Mat MainWindow::getTargetsFromLabelledImage(QExplicitlySharedDataPointer<targeterImage> tarCC, cv::Mat& binImage, 
												QExplicitlySharedDataPointer<targeterImage> detectImage, 
												cv::Mat displayImage, int imageIndex, bool bFilter)
{
	cv::Mat targets;

	QExplicitlySharedDataPointer<targeterImage> tarBin, tar;

	if(bFilter && detectImage != nullptr && binImage.rows > 0)
	{
		cv::Rect r = detectImage->getImagePosition();

		if(r.width>0 && r.height>0)
		{
			// filter binary regions based on similarity to target image size
			FilterRegions(tarCC, binImage, r, m_settings->StdevLarger, m_settings->StdevSmaller, m_settings->AspectTolerance);
		}
	}

	if (!displayImage.empty())
	{
		targets = displayImage.clone();

		drawCentroids(tarCC, targets, imageIndex, true);

		if (tarCC->getImageFunction() == imageType::cclabels)
		{
			QVector<QPoint> targetPoints;
			QVector<QRect> rects;
			QVector<Target> targetList;

			getTargetPositionsFromImage(tarCC->getCentroidsImage(), tarCC->getStatsImage(), targetPoints, rects);
			QVector3D vect = detectImage->getPositionStage();

			if (vect.x() < 0 || vect.y() < 0)
			{
				vect = QVector3D();
				consoleLog("image offset not found, positions relative to image not fiducials origin", CONSOLECOLOURS::Warning);
			}

			for (int i = 0; i < targetPoints.size(); i++)
			{
				if (!targetPoints[i].isNull())
				{
					QPoint ptTarget = targetPoints[i];

					double x = targetPoints[i].x();
					double y = targetPoints[i].y();

					x *= m_settings->mmPerPixel;
					y *= m_settings->mmPerPixel;

					x += vect.x();
					y += vect.y();

					double z = vect.z() >= 0 ? vect.z() : 0;

					// now translate relative to fiducial marks

					QVector3D rel = getRelativePosition(QVector3D(x, y, z));

					Target target;
					target.position = rel;
					target.imagePosition = targetPoints[i];
					target.region = rects[i];
					target.image = detectImage->getFileName();
					target.ID = i;

					targetList.append(target);
				}
			}

			ImageData imdata;

			imdata.FrameID = detectImage->getFrameID();
			imdata.patternRegion = detectImage->getPatternRegion();
			imdata.SubFrameID = detectImage->getSubFrameID();
			imdata.subRegionID = detectImage->getSubRegionID();

			imdata.targetList.append(targetList);

			m_processedImages.append(imdata);
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
* @param     QExplicitlySharedDataPointer<targeterImage> & tim 
* @param     cv::Mat & drawimage 
* @return    void
* Access     public 
*/
void MainWindow::drawCentroids(QExplicitlySharedDataPointer<targeterImage> tim, cv::Mat& drawimage, int imageIndex, bool bDrawOnImage)
{
	if (tim->getImageFunction() == imageType::cclabels)
	{
		cv::Mat& centroidsImage = tim->getCentroidsImage();
		cv::Mat& stats = tim->getStatsImage();
		cv::Mat& display = tim->getImage();
		cv::Mat sub_image;
		cv::Rect rect;
		bool bWriteSubImages = true;
		QString filename = m_settings->s_project_Directory + m_settings->s_project_FilenamePrefix;
		QString imagename = QString::fromStdString(tim->filepathname);

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
#ifdef _HAVE_IMAGEMAGICK
				m_imageReadWrite.writeImage(file, sub_image); 
#else
				cv::imwrite(file.toLocal8Bit().data(), sub_image);
#endif
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
				if(bDrawOnImage)
					cv::rectangle(drawimage, rect, cv::Scalar(0, 255, 0));
			}
			if(bDrawOnImage)
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
* @param     QExplicitlySharedDataPointer<targeterImage> & tim
* @param     cv::Mat & drawimage
* @return    void
* Access     public
*/
cv::Mat MainWindow::drawCentroids(QExplicitlySharedDataPointer<targeterImage> tim, cv::Mat& display, bool bWriteSubImages)
{
	if (tim->getImageFunction() == imageType::cclabels)
	{
		cv::Mat& centroidsImage = tim->getCentroidsImage();
		cv::Mat& stats = tim->getStatsImage();

		cv::Mat sub_image;
		cv::Rect rect;

		QString filename = m_settings->s_project_Directory + m_settings->s_project_FilenamePrefix;
		QString imagename = QString::fromStdString(tim->filepathname);

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

#ifdef _HAVE_IMAGEMAGICK
				m_imageReadWrite.writeImage(file, sub_image); 
#else
				imwrite(file.toLocal8Bit().data(), sub_image);
#endif

				DBOUT("target image written: " << file.toLocal8Bit().data() << std::endl);
			}
		}

		if (display.empty())
		{
			// create new image
			cv::Mat displayImage(tim->Size(), tim->Type(), cv::Scalar(0, 0, 0));

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
			cv::Mat displayImage = tim->getImage().clone();

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

void MainWindow::FilterRegionsOnSize(QExplicitlySharedDataPointer<targeterImage> ccim, cv::Mat& binImage, double stdevMaxFactor, double stdevMinFactor, double aspectFactor)
{
	cv::Mat newCentroidsImage, newStats;
	double aspect, objectsLength, area, sum = 0.0, sumsq = 0.0;

	// get the ccimage image
	cv::Mat& centroidsImage = ccim->getCentroidsImage();

	cv::Mat& stats = ccim->getStatsImage();

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

		ccim->setCentroidsImage(newCentroidsImage);
		ccim->setStatsImage(newStats);
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
* @param     QExplicitlySharedDataPointer<targeterImage> & tim
* @param     double stdevMaxFactor
* @param     double stdevMinFactor
* @param     double aspectFactor
* @return    void
* Access     public
*/
void MainWindow::FilterRegionsOnShape(QExplicitlySharedDataPointer<targeterImage> ccim, cv::Mat& binImage, cv::Rect targetROI)
{
	cv::Mat newCentroidsImage, newStats;
	vector<Point> tcontour;
	vector<vector<Point> > tcontours;
	double aspect, objectsLength, area, sum = 0.0, sumsq = 0.0;

	// get the ccimage image
	cv::Mat& centroidsImage = ccim->getCentroidsImage();

	cv::Mat& stats = ccim->getStatsImage();

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

	ccim->setCentroidsImage(newCentroidsImage);
	ccim->setStatsImage(newStats);
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
* @param     QExplicitlySharedDataPointer<targeterImage> & tim 
* @param     double stdevMaxFactor 
* @param     double stdevMinFactor 
* @param     double aspectFactor 
* @return    void
* Access     public 
*/
void MainWindow::FilterRegions(QExplicitlySharedDataPointer<targeterImage> ccim, cv::Mat& binImage, cv::Rect targetROI, double stdevMaxFactor, double stdevMinFactor, double aspectFactor)
{
	cv::Mat newCentroidsImage, newStats;
	vector<Point> tcontour;
	vector<vector<Point> > tcontours;
	double aspect, objectsLength, area, sum = 0.0, sumsq = 0.0;

	// get the ccimage image
	cv::Mat& centroidsImage = ccim->getCentroidsImage();

	cv::Mat& stats = ccim->getStatsImage();
	
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

		ccim->setCentroidsImage(newCentroidsImage);
		ccim->setStatsImage(newStats);
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
* @param     QExplicitlySharedDataPointer<targeterImage> & tim 
* @param     QFile & xmlFile 
* @return    void
* Access     public 
*/
/*
void MainWindow::writeCentroids(QExplicitlySharedDataPointer<targeterImage> tim, QFile& xmlFile)
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
		QExplicitlySharedDataPointer<targeterImage> tim = m_ImagesContainer.getImageAt(ind);

		pIm = drawCentroids(tim, cv::Mat(), false);

		if(pIm.rows>0)
		{
			addCVImage(pIm,  "detected targets mask image", true, imageType::mask, true);

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

	int ccindex = -1, mindex = -1, tindex = -1;

	foreach(int i, checked)
	{
		if (m_ImagesContainer.getImageAt(i).data()->Type() == imageType::cclabels)
			ccindex = i;
		else if (m_ImagesContainer.getImageAt(i).data()->Type() == imageType::mask)
			mindex = i;
		else if (m_ImagesContainer.getImageAt(i).data()->Type() == imageType::target)
			tindex = i;
	}

	int ind = getValidImageIndex();

	if (ind >= 0)
	{
		QExplicitlySharedDataPointer<targeterImage> tim = m_ImagesContainer.getImageAt(ind);

		QExplicitlySharedDataPointer<targeterImage> tarBin, tar;

		if(ccindex >= 0)
		{
			QExplicitlySharedDataPointer<targeterImage> ccim = m_ImagesContainer.getImageAt(ccindex);

			if(mindex >= 0)
				tarBin = m_ImagesContainer.getImageAt(mindex);
			else
				consoleLog(imageType::mask, CONSOLECOLOURS::colour::Warning);
			
			if(tindex >= 0)
				tar = m_ImagesContainer.getImageAt(tindex);
			else
				consoleLog(imageType::target, CONSOLECOLOURS::colour::Warning);

			if(tarBin != nullptr)
			{
				cv::Rect r;

				if (tar != nullptr)
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
		QExplicitlySharedDataPointer<targeterImage> tim= m_ImagesContainer.getImageAt(ind);
		cv::Mat& im = tim->getImage();
		cv::Mat out;

		bitwise_not(im, out);

		addCVImage(out, "inverted image", true, m_ImagesContainer.getImageAt(ind)->getImageFunction());
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
		QExplicitlySharedDataPointer<targeterImage> tim= m_ImagesContainer.getImageAt(ind);
		cv::Mat& im = tim->getImage();
		
		QVector<QSharedPointer<drawingShape>> shapes = ui->display_image->getImageShapes(false, true, ind);
		
		foreach(QSharedPointer<drawingShape> s, shapes)
		{
			if (s->type == drawingMode::rect)
			{
				m_settings->s_BarCodeImageRect = s->boundingBox;
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

			addCVImage(plot_image, "run length histogram (threshold line in blue)", true, m_ImagesContainer.getImageAt(ind)->getImageFunction());

	/*
			int* newaverage = m_ImageProcessing.fitPolynomial(average, size, 2);

			cv::Mat out2 = HelperFunctions::linePlotImage<int>(size, 1, 512, 512, newaverage);
			addCVImage(out2, tim->getUID(), "moving average fit", true, m_ImagesContainer.getImageAt(ind).getImageFunction());
	*/				

			// threshold histogram
			for (int i = 0; i < size; i++)
				run_length_hist[i] = run_length_hist[i] > threshold_hist[i] ? 1 : 0;
			delete[] threshold_hist;

			corr = HelperFunctions::expandRunLengthImage<int>(run_length_hist, size, corr.cols, corr.rows, gray.type(), gray.channels(), true, true);

			addCVImage(corr, "Cleaned bar code image", true, m_ImagesContainer.getImageAt(ind)->getImageFunction());

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
				addCVImage(detect_image, "is barcode detected", true, m_ImagesContainer.getImageAt(ind)->getImageFunction());

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
		QExplicitlySharedDataPointer<targeterImage> tim = m_ImagesContainer.getImageAt(ind);
		cv::Mat& im = tim->getImage();

		cv::Mat out, gray;

		if (im.channels() != 1)
			cvtColor(im, gray, CV_BGR2GRAY);

		cv::normalize(gray, out, 255, 0, NORM_MINMAX);
		cv::equalizeHist(gray, out);

	//	cv::Ptr<cv::CLAHE> clahe = createCLAHE();
	//	clahe->setClipLimit(4);

	//	clahe->apply(gray, out);

		addCVImage(out, "histogram equalized image", true, m_ImagesContainer.getImageAt(ind)->getImageFunction());
	}
}

void MainWindow::on_actionLaplacian_triggered()
{
	int ind = getValidImageIndex();

	if (ind >= 0)
	{
		QExplicitlySharedDataPointer<targeterImage> tim = m_ImagesContainer.getImageAt(ind);
		cv::Mat& im = tim->getImage();

		cv::Mat out, gray;

		Haar harr;
		cv::Mat lapla = harr.LaplacianPyramid(im, m_settings->numWaveletLevels, true);

		addCVImage(lapla, "laplacian image", true, m_ImagesContainer.getImageAt(ind)->getImageFunction());
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
			QExplicitlySharedDataPointer<targeterImage> tim= m_ImagesContainer.getImageAt(i);
			
			if (tim->imageFunction != imageType::mask)
			{
				cv::Mat binImage = ui->display_image->getBinaryImageFromShapes(i);

				//addCVImage(binImage, tim.getUID(), "binary image", true, tim.getImageFunction());

				ui->display_image->getTargetsFromBinaryImage(binImage, m_settings->samplingSpacing, m_settings->samplingOffset, threshold, m_settings->samplingType,  i);
			}
			else
				ui->display_image->getTargetsFromBinaryImage(tim->getImage(), m_settings->samplingSpacing, m_settings->samplingOffset, threshold, m_settings->samplingType, i);
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
			QExplicitlySharedDataPointer<targeterImage> tim = m_ImagesContainer.getImageAt(i);
			cv::Mat& im = tim->getImage();
				
			cv::Mat out = m_ImageProcessing.getLines(im, m_settings->objectColours[drawingItems::hough]);

			if(out.rows>0 && out.cols>0)
				addCVImage(out, "hough lines image", true, tim->getImageFunction());
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
			QFuture<void> t1 = QtConcurrent::run(&m_ImageProcessing, &ImageProcessing::calibrateCamera, m_ImagesContainer.getImages(checked), m_settings.data());
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
			QExplicitlySharedDataPointer<targeterImage> t = m_ImagesContainer.getImageAt(i);

			cv::Mat& im = t->getImage();

			cv::Mat m = m_ImageProcessing.CannyEdgeDetection(im);

			addCVImage(m, "canny edge image", true, t->getImageFunction());
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
			QExplicitlySharedDataPointer<targeterImage> t = m_ImagesContainer.getImageAt(i);

			cv::Mat& im = t->getImage();

			cv::Mat im2 = m_ImageProcessing.CornerDetection(im, m_settings->calibrateNoCols*m_settings->calibrateNoRows);

			addCVImage(im2, "corrected image", true, t->getImageFunction());
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
			QExplicitlySharedDataPointer<targeterImage> t = m_ImagesContainer.getImageAt(i);

			cv::Mat& im = t->getImage();
			cv::Mat im2;

			cv::Mat map1, map2;

			if(m_settings->activeCamera == cameraType::overview)
				cv::initUndistortRectifyMap(m_settings->calibrationDataOverview.intrinsic_matrix, m_settings->calibrationDataOverview.distortion_coeffs, cv::Mat(), m_settings->calibrationDataOverview.intrinsic_matrix, cv::Size(im.rows, im.cols), CV_16SC2, map1, map2);
			else
				cv::initUndistortRectifyMap(m_settings->calibrationDataMicroscope.intrinsic_matrix, m_settings->calibrationDataMicroscope.distortion_coeffs, cv::Mat(), m_settings->calibrationDataMicroscope.intrinsic_matrix, cv::Size(im.rows, im.cols), CV_16SC2, map1, map2);

			// must be new and empty image
			cv::remap(im, im2, map1, map2, cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());

			std::string pathname = t->name;

			int pos = -1;

			pos = pathname.find_last_of('.');

			if(pos>=0)
				pathname.insert(pos-1, "cal");
			else
				pathname.append(".png");
#ifdef _HAVE_IMAGEMAGICK
			m_imageReadWrite.writeImage(QString::fromStdString(pathname), im2);
#else
			cv::imwrite(pathname, im2);
#endif
			addCVImage(im2, "corrected image", true, t->getImageFunction());
		}
	}
}

void MainWindow::moveObjective(QPoint pt)
{
	#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
	// transform image coordinates to stage coordinates
	// if not explicitly set then QT initializes to identity matrix (ie no transform)

	QPointF stagePosition = m_settings->m_coordinateTransform.map(pt);

	// move to stage position
	emit MoveAbsoluteXY(stagePosition.x(), stagePosition.y(), ACTIONS::action::nothing);
}

void MainWindow::createTransformationMatrix(QVector3D topleft, QVector3D topright, QVector3D bottomleft)
{
#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	float M11, M12, M13, M14, M21, M22, M23, M24, M31, M32, M33, M34, M44;

	// this is the translation offset from the stage to the fiducial marks
	M14 = topleft.x();
	M24 = topleft.y();
	M34 = topleft.z();

	// translate of fiducial coordinate system so that origin is the same as stage

	// take topleft point as vector origin
	// vector centered on fiducial top left
	QVector3D XAxisFiducial = topright - topleft;
	QVector3D YAxisFiducial = bottomleft - topleft;

	// Z axis is vector orthogonal to XY plane
	QVector3D ZAxisFiducial = QVector3D::crossProduct(XAxisFiducial, YAxisFiducial);

	// normalise vectors to unit length, stage scale space will be the same as fiducial scale space
	// only the rotation angles will differ between the vector frames.

	// what we are doing here is finding unit vectors all microns information lost!
	XAxisFiducial.normalize();
	YAxisFiducial.normalize();
	ZAxisFiducial.normalize();

	// unit Cartesian vectors, frame of reference for stage
	// direction same & scale same as fiducial frame of reference
	// as fiducial vectors have been normalised to length of 1

	// would be better in microns, so subtract topright.x from topleft.x and bottomleft.y from topleft.y 
	// or create a vector from fiducial marks, making relative to top left
	
	QVector3D XAxisStage = QVector3D(1, 0, 0);
	QVector3D YAxisStage = QVector3D(0, 1, 0);
	QVector3D ZAxisStage = QVector3D(0, 0, 1);

	// rotational transformation coefficients relative to stage

	// This matrix will transform points from the fiducial axis to the stage coordinates
	// these are the rotation, skew and reflection coefficients

	// destination=stage, source=fiducial
	M11 = (float)QVector3D::dotProduct(XAxisStage, XAxisFiducial);
	M12 = (float)QVector3D::dotProduct(XAxisStage, YAxisFiducial);
	M13 = (float)QVector3D::dotProduct(XAxisStage, ZAxisFiducial);
	M21 = (float)QVector3D::dotProduct(YAxisStage, XAxisFiducial);
	M22 = (float)QVector3D::dotProduct(YAxisStage, YAxisFiducial);
	M23 = (float)QVector3D::dotProduct(YAxisStage, ZAxisFiducial);
	M31 = (float)QVector3D::dotProduct(ZAxisStage, XAxisFiducial);
	M32 = (float)QVector3D::dotProduct(ZAxisStage, YAxisFiducial);
	M33 = (float)QVector3D::dotProduct(ZAxisStage, ZAxisFiducial);

	// the inverse of the transform matrix reverses the operation

	// create and return transformation matrix M=RT, where T = [M14, M24, M34]', RT are combined into M
	m_settings->m_transformationMatrix = QMatrix4x4(M11, M12, M13, M14, M21, M22, M23, M24, M31, M32, M33, M34, 0, 0, 0, 1);

	m_settings->m_invTransformationMatrix = m_settings->m_transformationMatrix.inverted();
}

// translates coordinates from absolute stage coordinates to coordinates relative to fiducial marks
QVector3D MainWindow::getRelativePosition(QVector3D absolutePosition)
{
	return m_settings->m_transformationMatrix*absolutePosition;
}

// translates coordinates from coordinates relative to fiducial marks to absolute stage coordinates
QVector3D MainWindow::getAbsolutePosition(QVector3D relativePosition)
{
	return m_settings->m_invTransformationMatrix*relativePosition;
}

// stage scanning functions ///////////////////////////////////////////////////////////////////

void MainWindow::on_action_scan_regions_triggered()
{
#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	// get masked regions
	int ind = getValidImageIndex();
	bool showImage = true;
	bool bFoundRect = false;

	// reset all values, the first focus scan will be full range
	m_focusSettings.BestFocusRange = 999;
	m_focusSettings.BestFocusPosition = 999;
	m_focusSettings.bestFocusValue = -1;

	if (ind >= 0)
	{
		// make sure microscope camera selected
		if (m_settings->activeCamera != cameraType::microscope)
			m_settings->activeCamera = cameraType::microscope;

		QExplicitlySharedDataPointer<targeterImage> tim = m_ImagesContainer.getImageAt(ind);
		cv::Mat& im = tim->getImage();

		m_MosiacImageList.clear();

		QVector<QSharedPointer<drawingShape>> shapes = ui->display_image->getImageShapes(false, false, ind);
		XMLWriter writer(this);
		writer.OpenFile(m_settings->s_project_Directory, m_settings->s_project_FilenamePrefix + m_settings->s_project_Barcode + ".xml");
		writer.appendImageInformationXML(tim->getFileName(), "Overview image", shapes);

		StagePosition<double> stagePositionsZ;
	
		ImageData imdata;

		int shapeCount = 0;
		
		// transform coordinates
		foreach(QSharedPointer<drawingShape> s, shapes)
		{
			shapeCount++;
			s->ID = shapeCount;

			// rectangles used for masking stage ROI's
			if (s->type == drawingMode::rect || s->type == drawingMode::circle || s->type == drawingMode::poly)
			{
				QPointF tl = m_settings->m_coordinateTransform.map(QPointF(s->boundingBox.topLeft()));
				QPointF br = m_settings->m_coordinateTransform.map(QPointF(s->boundingBox.bottomRight()));

				QPolygonF imagePoly;
				imagePoly.clear();

				if (s->type == drawingMode::poly)
				{
					foreach(QPoint pt, s->polygon)
						imagePoly.append(m_settings->m_coordinateTransform.map(pt));
				}

				// transform image rect to stage position
				QRectF frect = QRectF(fmin(tl.x(), br.x()), fmin(tl.y(), br.y()), fabs(tl.x() - br.x()), fabs(tl.y() - br.y()));

				double imageWidthInMM = m_settings->mmPerPixel*double(m_settings->imageWidth);
				double imageHeightInMM = m_settings->mmPerPixel*double(m_settings->imageHeight);

				double x1 = frect.left();
				double x2 = frect.right();
				double y1 = frect.top();
				double y2 = frect.bottom();

				int x = 0, y = 0;

				ScanRegion scanRegion;

				scanRegion.regionShape = s->type;
				scanRegion.scanRegion = frect;
				scanRegion.scanRegionIndex = shapeCount;

				// have to save state of movements in QPoint array and iterate array using global counter, maybe in a stage movement class 
				for (double i = x1; i < x2; i += imageWidthInMM, x++)
					for (double j = y1; j < y2; j += imageHeightInMM, y++)
					{
						QRectF tile = QRect(i, j, imageWidthInMM, imageWidthInMM);

						// check if point in polygon or ellipse if these shapes used
						if(s->type == drawingMode::rect || 
							(s->type == drawingMode::circle &&
							HelperFunctions::pointInEllipse(frect, tile.topLeft()) ||
							HelperFunctions::pointInEllipse(frect, tile.topRight()) ||
							HelperFunctions::pointInEllipse(frect, tile.bottomLeft()) ||
							HelperFunctions::pointInEllipse(frect, tile.bottomRight())) ||
							(s->type == drawingMode::poly &&
							HelperFunctions::pointInPoly(s->polygon, tile.topLeft()) ||
							HelperFunctions::pointInPoly(s->polygon, tile.topRight()) ||
							HelperFunctions::pointInPoly(s->polygon, tile.bottomLeft()) ||
							HelperFunctions::pointInPoly(s->polygon, tile.bottomRight())) )
						{
							// also store i,j index position, necessary for recreating the image.
							QPoint posIndex(x, y);

							// move to stage position
							StageCoordinates sc;
							sc.stagePosition3D.setX(tile.left());
							sc.stagePosition3D.setY(tile.top());
							sc.index = posIndex;
							sc.tileSize = QSize(imageWidthInMM, imageHeightInMM);
							
							scanRegion.stagePositions.append(sc);
						}
					}

				m_currentScanImageData.scanRegion.append(scanRegion);

				bFoundRect = true;
			}
		}

		if(!bFoundRect)
			consoleLog("No rect, ellipse or poly drawing shapes found for defining scanning area", CONSOLECOLOURS::colour::Warning);

		// will call a lot of events but should wait for process to complete before next stage movement.
		if(!m_currentScanImageData.scanRegion.first().stagePositions.isEmpty())
		{
			const QPointF pt = m_currentScanImageData.scanRegion.first().stagePositions.first().stagePosition3D.toPointF();
			
			m_focusSettings.BestFocusPosition = m_settings->m_DefaultFocusPosition;
			
			emit MoveAbsoluteXY(pt.x(), pt.y(), ACTIONS::action::coarseFocus);
		}
	}
}

// called when stage moved to new XY position - focusing starts
void MainWindow::stageMovedXY(double x, double y, ACTIONS::action act)
{
#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
	double focusRange = m_settings->m_FocusRange;
	double bestFocusPosition = m_settings->m_DefaultFocusPosition;

	// use best range as range
	if (m_settings->m_bOptimiseFocusRange && m_focusSettings.BestFocusRange != 999)
		focusRange = m_focusSettings.BestFocusRange;
	
	// use last found best focus position to center next focus range
	if ((m_settings->m_bCenterFocus || m_settings->m_bInterpolateFocusPosition) && m_focusSettings.BestFocusPosition != 999)	// don't do on first iteration
	{
		bestFocusPosition = m_focusSettings.BestFocusPosition;

		if (m_settings->m_bInterpolateFocusPosition)
			bestFocusPosition = m_focusSettings.BestFocusPosition + m_focusSettings.dBestFocusPosition;			// interpolate
	}

	// if only fine focusing selected do only a fine focusing
	if(m_settings->m_bUseFineFocusRange && !m_settings->m_bUseCoarseFocusRange)		
	{
		// stage moved now start fine focusing
		m_focusSettings.FOCUS_STATE = ACTIONS::fineFocus;

		// do a fine focusing
		createFocusStackAndMove(bestFocusPosition, focusRange, m_settings->m_FineFocusStep, act);
	}
	else  // normal case: start with coarse focusing
	{	
		// stage moved now start coarse focusing
		m_focusSettings.FOCUS_STATE = ACTIONS::coarseFocus;

		// do a coarse focusing
		createFocusStackAndMove(bestFocusPosition, focusRange, m_settings->m_CoarseFocusStep, act);
	}
}

void MainWindow::createFocusStackAndMove(double bestFocus, double focusRange, double step, ACTIONS::action act, bool bUpFirst)
{
#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
	m_focusSettings.noFocusStackImages = 0;
	// clear position array and image array

	m_focus_position_Z.removeAll();
	
	if(bUpFirst)
	{
		// add focus positions to array
		// go upwards from center
		for (double z = bestFocus; z <= bestFocus + focusRange; z += step)
			m_focus_position_Z.append(z);

		// then downwards from center
		for (double z = bestFocus-step; z >= bestFocus - focusRange; z -= step)
			m_focus_position_Z.append(z);
	}
	else
	{
		// add focus positions to array
		// go downwards from center
		for (double z = bestFocus; z >= bestFocus - focusRange; z -= step)
			m_focus_position_Z.append(z);
	
		// then upwards from center
		for (double z = bestFocus+step; z <= bestFocus + focusRange; z += step)
			m_focus_position_Z.append(z);
	}

	// move to first position
	if(m_focus_position_Z.checkIfValid())
	{
		m_focus_position_Z.setPosition(0);

		m_focusSettings.noFocusStackImages = m_focus_position_Z.getSize();

		// calls Z axis stage move
		emit MoveAbsoluteZ(m_focus_position_Z.getCurentPosition(), act);
	}
}

// fullRange, centered, bestRange, centeredBestRange, coarse, fine, bestRangeCoarse, bestRangeFine, interpolate
// called after Z axis stage has moved
void MainWindow::stageMovedZ(double stageZ, ACTIONS::action act)
{
#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif
	if (!(act == ACTIONS::addToMosaic))
	{
		cv::Mat image = basCamera->grabImage(cameraType::microscope);

		if (!image.empty())
		{
			updateVideoImage(image);// add image to gallery

			if (act == ACTIONS::coarseFocus || act == ACTIONS::fineFocus)
			{
				// get focus position
				if(m_focus_position_Z.checkIfValidPosition())
				{
					double z = m_focus_position_Z.getCurentPosition();

					// increment to next position
					m_focus_position_Z.moveIterator();

					// get focus value from image
					startFocusThreads(image, z, act);		
					
					// move stage to next focus position
					emit MoveAbsoluteZ(z, act);
				}
			}
		}
		else
		{
			consoleLog("stageMovedZ - no image grabbed - aborting!", CONSOLECOLOURS::colour::Warning);
			return;
		}
	}
	else if (act == ACTIONS::MosaicFinished)
	{
		// write all other scan information here.

		// process mosaic etc
		QMessageBox::information(this, tr("Targeter"),
			tr("Finished obtaining images from frame"),
			QMessageBox::Ok);
	}
	else if(act == ACTIONS::addToMosaic)
	{
		// get next XY position

	}
}


void MainWindow::startFocusThreads(cv::Mat image, double z, ACTIONS::action act)
{
#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

#ifdef _CUDA_CODE_COMPILE_not_implemented_
	FocusResult res;

	res.z = z;
	res.act = act;
	res.focusImage = image;

	m_FocusCUDA.getFocusScore(res);

	addFocusValue(res);

#else
	QFutureWatcher<FocusResult>* watcher = new QFutureWatcher<FocusResult>();

	connect(watcher, &QFutureWatcher<FocusResult>::finished, this, &MainWindow::addFocusValueCompleted);

	QFuture<FocusResult> future = QtConcurrent::run(this, &MainWindow::getFocusValue, image, z, act);

	watcher->setFuture(future);
#endif

	// future watcher stuff
	//MultiWatcher* mWatcher = new MultiWatcher;

	//mWatcher->_sync.addFuture(future);

	//connect(mWatcher, &MultiWatcher::MultiWatchDone, this, &MainWindow::allFocusValuesCompleted);

	//mWatcher->start();
}

// called in separate thread, gets focus value for image
FocusResult MainWindow::getFocusValue(cv::Mat& im, double z, ACTIONS::action act)
{
#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	FocusResult res;

	res.z = z;
	res.act = act;
	res.focusImage = im;

	res.focusValue = FocusStack::getFocusImage(im, m_settings->FocusAlgorithm);

	return res;
}

void MainWindow::addFocusValueCompleted()
{
#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	QFutureWatcher<FocusResult>* pWatcher = dynamic_cast<QFutureWatcher<FocusResult>*>(sender());

	if (pWatcher)
	{
		QFuture<FocusResult> future = pWatcher->future();

		FocusResult result = pWatcher->future().result();

		addFocusValue(result);

		delete pWatcher;
	}
}

/*
void MainWindow::allFocusValuesCompleted()
{
	sender()->deleteLater();

}


bool m_bOptimiseFocusRange;
bool m_bInterpolateFocusPosition;
bool m_bUseFocusThreshold;
bool m_bUseCoarseFocusRange;
bool m_bUseFineFocusRange;
bool m_bCenterFocus;
bool m_bUseRegisteredFocusPoints;
*/
//fullRange, centered, bestRange, centeredBestRange, coarse, fine, bestRangeCoarse, bestRangeFine, interpolate
void MainWindow::addFocusValue(FocusResult result)
{

#ifdef DEBUGPRINT
	qDebug() << "Function Name: " << Q_FUNC_INFO;
#endif

	FocusImage fi;
	fi.focusValue = result.focusValue;
	fi.focusImage = result.focusImage;

	QString actstr = ACTION_STRINGS(result.act);

	consoleLog("action:" + actstr + " z:" + QString::number(result.z) + " focus value:" + QString::number(result.focusValue));

	// if good enough focus value then quit coarse focus & do next step
	if(	m_settings->m_bUseFocusThreshold && 
		m_focusSettings.bestFocusValue>0 &&
		fi.focusValue > m_focusSettings.bestFocusValue*(1.0 - m_settings->m_FocusThresholdFraction))
	{
		// use this position as best focus and move on
		double bestFocusValue = fi.focusValue;

		// get focus position and best focused image as this image & position
		double bestPosition = result.z;

		// just do fine focus range at this position
		if (m_settings->m_bUseFineFocusRange)		
		{
			// do fine search at this position

			// change focus state
			m_focusSettings.FOCUS_STATE = ACTIONS::fineFocus;

			// 	now do fine focusing
			createFocusStackAndMove(result.z, m_settings->m_CoarseFocusStep, m_settings->m_FineFocusStep, ACTIONS::fineFocus);
		}
		else	// quit and use best focus value
		{
			// save for later comparisons
			m_focusSettings.bestFocusValue = bestFocusValue;

			m_focusSettings.dBestFocusPosition = bestPosition - m_focusSettings.BestFocusPosition;
			m_focusSettings.BestFocusPosition = bestPosition;

			cv::Mat bestImage = result.focusImage;

			// add image and do next XY position
			addImageMosaic(bestImage, bestPosition);
		}
	}
	else		// for all other types of focusing complete focus stack
	{
		// add focus information to array
		m_focusSettings.focusStackData.insert(result.z, fi);

		// if focus stack completed
		if (m_focusSettings.focusStackData.size() >= m_focusSettings.noFocusStackImages)
		{
			double bestFocusValue = 0;

			// get focus position and best focused image
			double bestPosition = getBestFocusPosition(bestFocusValue);
			m_focusSettings.dBestFocusPosition = bestPosition - m_focusSettings.BestFocusPosition;

			m_focusSettings.BestFocusPosition = bestPosition;

			cv::Mat bestImage = m_focusSettings.focusStackData[bestPosition].focusImage;

			// save for later comparisons
			m_focusSettings.bestFocusValue = bestFocusValue;

			// calculate optimised focus range
			if (m_settings->m_bOptimiseFocusRange)
			{
				// range calculated from min max position of focus values that were greater then focus threshold min(x:f(x)>T)
				if (m_focusSettings.FOCUS_STATE == ACTIONS::coarseFocus)
				{
					double range = getBestFocusRange(bestFocusValue);

					if (range > 0)
						m_focusSettings.BestFocusRange = range;
				}
			}

			// clear the data array now we have the best focus position and image
			m_focusSettings.focusStackData.clear();

			// if just coarse selected then focusing finished, move on to next position
			if (m_settings->m_bUseCoarseFocusRange && !m_settings->m_bUseFineFocusRange)
			{
				// add best focused image from fine image stack & save image
				addImageMosaic(bestImage, bestPosition);
			}
			else
			{
				// do next operation
				if (m_focusSettings.FOCUS_STATE == ACTIONS::coarseFocus)
				{
					// get best focus position - fine increments about +/- one coarse step
					// should be improved, it could be that the coarse step is not big enough

					// change focus state
					m_focusSettings.FOCUS_STATE = ACTIONS::fineFocus;

					// 	now do fine focusing
					createFocusStackAndMove(bestPosition, m_settings->m_CoarseFocusStep, m_settings->m_FineFocusStep, ACTIONS::fineFocus);
				}
				else if (m_focusSettings.FOCUS_STATE == ACTIONS::fineFocus)
				{
					// add best focused image from fine image stack & save image, in separate thread
					QFuture<void> t1 = QtConcurrent::run(this, &MainWindow::addImageMosaic, bestImage, bestPosition);
				}
			}
		}
	}
}

double MainWindow::getBestFocusRange(double bestFocus)
{
	QMapIterator<double, FocusImage> i = QMapIterator<double, FocusImage>(m_focusSettings.focusStackData);

	double start = 0, end = 0, mult = 1.0;

	// get best focus value
	while (i.hasNext())
	{
		i.next();

		if (i.value().focusValue >= bestFocus*m_settings->m_FocusThresholdFraction)
		{
			start = i.key();
			break;
		}
	}

	i.toBack();

	while (i.hasPrevious())
	{
		i.previous();

		if (i.value().focusValue >= bestFocus*m_settings->m_FocusThresholdFraction || i.key() == start)
		{
			end = i.key();
			break;
		}
	}

	// if value lies at ends of range then double range
	if (start == m_focusSettings.focusStackData.first().focusValue || end == m_focusSettings.focusStackData.last().focusValue)
		mult = 2.0;

	return mult*(end - start);
}

double MainWindow::getBestFocusPosition(double& bestFocusValue)
{
	QMapIterator<double, FocusImage> i = QMapIterator<double, FocusImage>(m_focusSettings.focusStackData);

	double bestPosition = 0, maxVal = 0;

	// get first element
	if(i.hasNext())
	{
		i.next();
		maxVal = i.value().focusValue;
		bestPosition = i.key();
	}

	// get best focus value
	while (i.hasNext())
	{
		i.next();

		if (i.value().focusValue >= maxVal)
		{
			maxVal = i.value().focusValue;
			bestPosition = i.key();
		}
	}

	bestFocusValue = maxVal;

	return bestPosition;
}

void MainWindow::addImageMosaic(cv::Mat& image, double focusDistance)
{
	// check here if position valid 
	if (focusDistance > -990)
	{
		QString pathname = m_settings->s_project_Directory + m_settings->s_project_FilenamePrefix + "_";

		bool bFound;

		ScanRegion sr = m_currentScanImageData.getScanRegion(bFound);

		if(bFound)
		{
			StageCoordinates sc = sr.getStagePosition(bFound);

			if(bFound)
			{
				QSharedPointer<ImageData> id = sc.childImage;

				QPoint ind = sc.index;

				QVector3D absolutePosition = sc.stagePosition3D;
				absolutePosition.setZ(focusDistance);

				QVector3D relativePosition = getRelativePosition(sc.stagePosition3D);

				// add image to mosaic and save to file.
				QString filename = pathname + "_ind[" + QString::number((int)ind.x()) + "," + QString::number((int)ind.y()) + "]" +
					+"_stage[" + QString::number(absolutePosition.x()) + "," + QString::number(absolutePosition.y()) + "," + QString::number(absolutePosition.z()) + "]" +
					+"_fid[" + QString::number(relativePosition.x()) + "," + QString::number(relativePosition.y()) + "," + QString::number(relativePosition.z()) + "]" +
					".png";

				id->filename = filename;

				// save file name in list
				m_MosiacImageList[filename] = image;

				QString jsonData = "{name: " + filename + ", pattern:" + QString::number(id->scanRegionIndex) +
					", shapeType:" + DRAWINGMODESTRINGS(sr.regionShape) +
					", frameBarcode:" + m_settings->s_project_Barcode + "}," +
					", tileSize:{width:" + QString::number(sc.tileSize.width()) + ", height:" + QString::number(sc.tileSize.height()) + "}," +
					", index:{x:" + QString::number((int)ind.x()) + ", y:" + QString::number((int)ind.y()) + "}," +
					", stage:{x:" + QString::number(absolutePosition.x()) + ", y:" + QString::number(absolutePosition.y()) + ", z:" + QString::number(absolutePosition.z()) + "}," +
					" fiducial:[x:" + QString::number(relativePosition.x()) + ",y:" + QString::number(relativePosition.y()) + ", z:" + QString::number(relativePosition.z()) + "}}";

				if (m_settings->m_bShowBestFocusImage)
					updateVideoImage(image);// add image to gallery

				// add to list of processed images
				m_processedImages.append(m_currentScanImageData);

				if (m_settings->m_bDetectTargetsWhileScanning)
				{
					// get score image
					LogProcessing(true);

					cv::Mat scoreImage;

					if (m_settings->algorithmType == algoType::COOC || m_settings->algorithmType == algoType::FASTCOOC)
					{
						scoreImage = m_FindTargets.detectCOOCHistogram(image, (m_settings->coocMatrix).data(), false, m_settings->bProcessGrayscale,
																	   m_settings->algorithmType == algoType::FASTCOOC, m_settings->bCorrectBackGround);
					}
					else if (m_settings->algorithmType == algoType::LAWS)
					{
						scoreImage = m_FindTargets.detectLawsTextureFeatures(image, m_settings->lawsHistTarget, m_settings->lawsHistBiases, m_settings->bCorrectBackGround);
					}

					if (!scoreImage.empty())
					{
						cv::Mat im = getTargetPositions(scoreImage, QExplicitlySharedDataPointer<targeterImage>(false), m_ImagesContainer.getNumImages() - 1);
					}
					else
					{
						QMetaObject::invokeMethod(this, "LOGCONSOLE", Qt::QueuedConnection, Q_ARG(QString, "error - score image not created - did you forget to train?"), Q_ARG(CONSOLECOLOURS::colour, CONSOLECOLOURS::colour::Warning));
					}
				}

#ifdef _HAVE_IMAGEMAGICK
				// write image file including exif information
				m_imageReadWrite.writeImage(filename, image, jsonData);
#else
				imwrite(filename.toLocal8Bit().data(), image);
#endif
				// increment to next position
				StageCoordinates nsc = sr.incrementStagePosition(bFound);

				if(!bFound)
				{
					// move to next scan region
					m_currentScanImageData.incrementScanRegion(bFound);

					if(bFound)
					{
						nsc = sr.getStagePosition(bFound);

						// no more places to move to
						if(!bFound)
						{
							// move to beginning position
							QPointF pt = m_currentScanImageData.scanRegion.first().stagePositions.first().stagePosition3D.toPointF();
							emit MoveAbsoluteXY(pt.x(), pt.y(), ACTIONS::action::MosaicFinished);
						}
					}
					else
					{
						// move to beginning position
						QPointF pt = m_currentScanImageData.scanRegion.first().stagePositions.first().stagePosition3D.toPointF();
						emit MoveAbsoluteXY(pt.x(), pt.y(), ACTIONS::action::MosaicFinished);
					}
				}
				else
				{
					// move to beginning position
					QPointF pt = m_currentScanImageData.scanRegion.first().stagePositions.first().stagePosition3D.toPointF();
					emit MoveAbsoluteXY(pt.x(), pt.y(), ACTIONS::action::MosaicFinished);
				}
			}
			else
			{
				// move to beginning position
				QPointF pt = m_currentScanImageData.scanRegion.first().stagePositions.first().stagePosition3D.toPointF();
				emit MoveAbsoluteXY(pt.x(), pt.y(), ACTIONS::action::MosaicFinished);
			}
		}
		else
		{
			// move to beginning position
			QPointF pt = m_currentScanImageData.scanRegion.first().stagePositions.first().stagePosition3D.toPointF();
			emit MoveAbsoluteXY(pt.x(), pt.y(), ACTIONS::action::MosaicFinished);
		}
	}
	else
		QMetaObject::invokeMethod(this, "LOGCONSOLE", Qt::QueuedConnection, Q_ARG(QString, "error - addImageMosaic - bad focus image!"), Q_ARG(CONSOLECOLOURS::colour, CONSOLECOLOURS::colour::Warning));
	
}

/*
double MainWindow::getBestFocus(double minPos, double step)
{
// process focus stack, get best focus position
int bestImageIndex = FocusStack::getBestFocusImage(m_focusStackImages, m_focusValues, m_settings->FocusAlgorithm);

// move Z axis position to that of best focus image
return minPos + step*((double)bestImageIndex);
}
*/