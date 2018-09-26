/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "paintqlabel.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionFile;
    QAction *action_File;
    QAction *action_Exit;
    QAction *action_Open;
    QAction *actionProcessFocusStack;
    QAction *action_Save;
    QAction *actionSelect_All;
    QAction *actionDeselect_All;
    QAction *actionGrab_Image_From_Camera;
    QAction *actionZoom_Out;
    QAction *actionZoom_In;
    QAction *actionDraw_Polygon;
    QAction *actionDraw_Circle_Region;
    QAction *actionDraw_Rectangular_Region;
    QAction *action_Move_Image;
    QAction *actionGet_Target_image_region;
    QAction *actionSet_as_Target;
    QAction *actionSet_as_find_targets_image;
    QAction *actionFind_targets;
    QAction *actionDeleteObject;
    QAction *actionTarget_detection_settings;
    QAction *actionThresholdImage;
    QAction *actionMergeImages;
    QAction *actionSettings;
    QAction *actionReference_fiducial_marks;
    QAction *actionFind_Centers;
    QAction *actionInvert;
    QAction *actionConnected_Components;
    QAction *actionFilter_Binary_Objects;
    QAction *actionSave_Target_Positions;
    QAction *actionScoreImage;
    QAction *actionCalibrate_Camera;
    QAction *actionCorrectImage;
    QAction *actionGrab_Video_From_Camera;
    QAction *actionDetect_lines;
    QAction *actionCorner_Detection;
    QAction *actionEdge_Detection;
    QAction *actionEntropyFilter;
    QAction *actionEnergy_image;
    QAction *actionRemoveBlackPixels;
    QAction *action_New;
    QAction *actionHelp;
    QAction *actionDeleteImage;
    QAction *actionSample_White_Binary_Regions;
    QAction *actionMask_White;
    QAction *actionMask_Black;
    QAction *actionSelect_Object;
    QAction *actionClickTarget;
    QAction *actionRead_Barcode;
    QAction *action_scan_regions;
    QAction *actionCreate_Mask_Image;
    QAction *actionClick_Center_Objective;
    QAction *actionGrid_Spacing;
    QAction *actionBackground_fit;
    QAction *actionEqualise_Image;
    QAction *actionCreate_Image_Mosaic;
    QAction *actionDefine_Focus_Plane;
    QAction *actionAnnotate_Shape;
    QAction *actionTrainTarget;
    QAction *actionLaplacian;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    PaintQLabel *display_image;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QListWidget *ImageThumbList;
    QPlainTextEdit *consoleDisplay;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menuImages;
    QMenu *menuDetection;
    QMenu *menuCamera;
    QMenu *menuImage_Processing;
    QMenu *menuSettings;
    QMenu *menuAlignment;
    QMenu *menuView;
    QMenu *menuDrawing;
    QMenu *menuSegmentation;
    QToolBar *toolbarOpenSave;
    QStatusBar *statusBar;
    QToolBar *toolBarSettings;
    QToolBar *toolBarDrawing;
    QToolBar *toolBarZoomPann;
    QToolBar *toolBarImageAnalysis;
    QToolBar *toolBarMicroscope;
    QToolBar *toolBarCamera;
    QToolBar *toolBarBinaryOperations;
    QToolBar *toolBarTargets;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(939, 682);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/24/targeter.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionFile = new QAction(MainWindow);
        actionFile->setObjectName(QStringLiteral("actionFile"));
        action_File = new QAction(MainWindow);
        action_File->setObjectName(QStringLiteral("action_File"));
        action_Exit = new QAction(MainWindow);
        action_Exit->setObjectName(QStringLiteral("action_Exit"));
        action_Open = new QAction(MainWindow);
        action_Open->setObjectName(QStringLiteral("action_Open"));
        action_Open->setEnabled(true);
        action_Open->setVisible(true);
        actionProcessFocusStack = new QAction(MainWindow);
        actionProcessFocusStack->setObjectName(QStringLiteral("actionProcessFocusStack"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/24/focus.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionProcessFocusStack->setIcon(icon1);
        action_Save = new QAction(MainWindow);
        action_Save->setObjectName(QStringLiteral("action_Save"));
        actionSelect_All = new QAction(MainWindow);
        actionSelect_All->setObjectName(QStringLiteral("actionSelect_All"));
        actionDeselect_All = new QAction(MainWindow);
        actionDeselect_All->setObjectName(QStringLiteral("actionDeselect_All"));
        actionGrab_Image_From_Camera = new QAction(MainWindow);
        actionGrab_Image_From_Camera->setObjectName(QStringLiteral("actionGrab_Image_From_Camera"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/24/camera.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGrab_Image_From_Camera->setIcon(icon2);
        actionZoom_Out = new QAction(MainWindow);
        actionZoom_Out->setObjectName(QStringLiteral("actionZoom_Out"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/24/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_Out->setIcon(icon3);
        actionZoom_In = new QAction(MainWindow);
        actionZoom_In->setObjectName(QStringLiteral("actionZoom_In"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icons/24/plus.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_In->setIcon(icon4);
        actionDraw_Polygon = new QAction(MainWindow);
        actionDraw_Polygon->setObjectName(QStringLiteral("actionDraw_Polygon"));
        actionDraw_Polygon->setCheckable(true);
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/icons/24/polygon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDraw_Polygon->setIcon(icon5);
        actionDraw_Circle_Region = new QAction(MainWindow);
        actionDraw_Circle_Region->setObjectName(QStringLiteral("actionDraw_Circle_Region"));
        actionDraw_Circle_Region->setCheckable(true);
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/icons/24/circ.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDraw_Circle_Region->setIcon(icon6);
        actionDraw_Rectangular_Region = new QAction(MainWindow);
        actionDraw_Rectangular_Region->setObjectName(QStringLiteral("actionDraw_Rectangular_Region"));
        actionDraw_Rectangular_Region->setCheckable(true);
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/icons/24/rect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDraw_Rectangular_Region->setIcon(icon7);
        action_Move_Image = new QAction(MainWindow);
        action_Move_Image->setObjectName(QStringLiteral("action_Move_Image"));
        action_Move_Image->setCheckable(true);
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/icons/24/grabhand.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Move_Image->setIcon(icon8);
        actionGet_Target_image_region = new QAction(MainWindow);
        actionGet_Target_image_region->setObjectName(QStringLiteral("actionGet_Target_image_region"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/icons/24/polygonmask.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGet_Target_image_region->setIcon(icon9);
        actionSet_as_Target = new QAction(MainWindow);
        actionSet_as_Target->setObjectName(QStringLiteral("actionSet_as_Target"));
        actionSet_as_find_targets_image = new QAction(MainWindow);
        actionSet_as_find_targets_image->setObjectName(QStringLiteral("actionSet_as_find_targets_image"));
        actionFind_targets = new QAction(MainWindow);
        actionFind_targets->setObjectName(QStringLiteral("actionFind_targets"));
        actionFind_targets->setIcon(icon);
        actionDeleteObject = new QAction(MainWindow);
        actionDeleteObject->setObjectName(QStringLiteral("actionDeleteObject"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/icons/24/trashcan.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDeleteObject->setIcon(icon10);
        actionTarget_detection_settings = new QAction(MainWindow);
        actionTarget_detection_settings->setObjectName(QStringLiteral("actionTarget_detection_settings"));
        actionThresholdImage = new QAction(MainWindow);
        actionThresholdImage->setObjectName(QStringLiteral("actionThresholdImage"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/icons/24/threshold.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionThresholdImage->setIcon(icon11);
        actionMergeImages = new QAction(MainWindow);
        actionMergeImages->setObjectName(QStringLiteral("actionMergeImages"));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/icons/24/mergeimage.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMergeImages->setIcon(icon12);
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QStringLiteral("actionSettings"));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/icons/24/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSettings->setIcon(icon13);
        actionReference_fiducial_marks = new QAction(MainWindow);
        actionReference_fiducial_marks->setObjectName(QStringLiteral("actionReference_fiducial_marks"));
        actionReference_fiducial_marks->setCheckable(true);
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/icons/24/marks.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionReference_fiducial_marks->setIcon(icon14);
        actionFind_Centers = new QAction(MainWindow);
        actionFind_Centers->setObjectName(QStringLiteral("actionFind_Centers"));
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/icons/24/findcenters.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFind_Centers->setIcon(icon15);
        actionInvert = new QAction(MainWindow);
        actionInvert->setObjectName(QStringLiteral("actionInvert"));
        QIcon icon16;
        icon16.addFile(QStringLiteral(":/icons/24/invert.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionInvert->setIcon(icon16);
        actionConnected_Components = new QAction(MainWindow);
        actionConnected_Components->setObjectName(QStringLiteral("actionConnected_Components"));
        QIcon icon17;
        icon17.addFile(QStringLiteral(":/icons/24/connectedcomponents.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConnected_Components->setIcon(icon17);
        actionFilter_Binary_Objects = new QAction(MainWindow);
        actionFilter_Binary_Objects->setObjectName(QStringLiteral("actionFilter_Binary_Objects"));
        QIcon icon18;
        icon18.addFile(QStringLiteral(":/icons/24/filter.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFilter_Binary_Objects->setIcon(icon18);
        actionSave_Target_Positions = new QAction(MainWindow);
        actionSave_Target_Positions->setObjectName(QStringLiteral("actionSave_Target_Positions"));
        QIcon icon19;
        icon19.addFile(QStringLiteral(":/icons/24/saveTargets.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_Target_Positions->setIcon(icon19);
        actionScoreImage = new QAction(MainWindow);
        actionScoreImage->setObjectName(QStringLiteral("actionScoreImage"));
        QIcon icon20;
        icon20.addFile(QStringLiteral(":/icons/24/scoreimage.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionScoreImage->setIcon(icon20);
        actionCalibrate_Camera = new QAction(MainWindow);
        actionCalibrate_Camera->setObjectName(QStringLiteral("actionCalibrate_Camera"));
        QIcon icon21;
        icon21.addFile(QStringLiteral(":/icons/24/checkerboard.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCalibrate_Camera->setIcon(icon21);
        actionCorrectImage = new QAction(MainWindow);
        actionCorrectImage->setObjectName(QStringLiteral("actionCorrectImage"));
        QIcon icon22;
        icon22.addFile(QStringLiteral(":/icons/24/calibrate.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCorrectImage->setIcon(icon22);
        actionGrab_Video_From_Camera = new QAction(MainWindow);
        actionGrab_Video_From_Camera->setObjectName(QStringLiteral("actionGrab_Video_From_Camera"));
        actionGrab_Video_From_Camera->setCheckable(true);
        QIcon icon23;
        icon23.addFile(QStringLiteral(":/icons/24/movie.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGrab_Video_From_Camera->setIcon(icon23);
        actionDetect_lines = new QAction(MainWindow);
        actionDetect_lines->setObjectName(QStringLiteral("actionDetect_lines"));
        actionDetect_lines->setCheckable(true);
        QIcon icon24;
        icon24.addFile(QStringLiteral(":/icons/24/hough.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDetect_lines->setIcon(icon24);
        actionCorner_Detection = new QAction(MainWindow);
        actionCorner_Detection->setObjectName(QStringLiteral("actionCorner_Detection"));
        actionEdge_Detection = new QAction(MainWindow);
        actionEdge_Detection->setObjectName(QStringLiteral("actionEdge_Detection"));
        actionEntropyFilter = new QAction(MainWindow);
        actionEntropyFilter->setObjectName(QStringLiteral("actionEntropyFilter"));
        QIcon icon25;
        icon25.addFile(QStringLiteral(":/icons/24/entropy.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEntropyFilter->setIcon(icon25);
        actionEnergy_image = new QAction(MainWindow);
        actionEnergy_image->setObjectName(QStringLiteral("actionEnergy_image"));
        actionRemoveBlackPixels = new QAction(MainWindow);
        actionRemoveBlackPixels->setObjectName(QStringLiteral("actionRemoveBlackPixels"));
        action_New = new QAction(MainWindow);
        action_New->setObjectName(QStringLiteral("action_New"));
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QStringLiteral("actionHelp"));
        actionDeleteImage = new QAction(MainWindow);
        actionDeleteImage->setObjectName(QStringLiteral("actionDeleteImage"));
        actionDeleteImage->setIcon(icon10);
        actionSample_White_Binary_Regions = new QAction(MainWindow);
        actionSample_White_Binary_Regions->setObjectName(QStringLiteral("actionSample_White_Binary_Regions"));
        QIcon icon26;
        icon26.addFile(QStringLiteral(":/icons/24/sample.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSample_White_Binary_Regions->setIcon(icon26);
        actionMask_White = new QAction(MainWindow);
        actionMask_White->setObjectName(QStringLiteral("actionMask_White"));
        actionMask_White->setCheckable(true);
        QIcon icon27;
        icon27.addFile(QStringLiteral(":/icons/24/white.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMask_White->setIcon(icon27);
        actionMask_Black = new QAction(MainWindow);
        actionMask_Black->setObjectName(QStringLiteral("actionMask_Black"));
        actionMask_Black->setCheckable(true);
        QIcon icon28;
        icon28.addFile(QStringLiteral(":/icons/24/black.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMask_Black->setIcon(icon28);
        actionSelect_Object = new QAction(MainWindow);
        actionSelect_Object->setObjectName(QStringLiteral("actionSelect_Object"));
        QIcon icon29;
        icon29.addFile(QStringLiteral(":/icons/24/select.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSelect_Object->setIcon(icon29);
        actionClickTarget = new QAction(MainWindow);
        actionClickTarget->setObjectName(QStringLiteral("actionClickTarget"));
        actionClickTarget->setCheckable(true);
        QIcon icon30;
        icon30.addFile(QStringLiteral(":/icons/24/cross.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClickTarget->setIcon(icon30);
        actionRead_Barcode = new QAction(MainWindow);
        actionRead_Barcode->setObjectName(QStringLiteral("actionRead_Barcode"));
        QIcon icon31;
        icon31.addFile(QStringLiteral(":/icons/24/barcode.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRead_Barcode->setIcon(icon31);
        action_scan_regions = new QAction(MainWindow);
        action_scan_regions->setObjectName(QStringLiteral("action_scan_regions"));
        QIcon icon32;
        icon32.addFile(QStringLiteral(":/icons/24/scanareas.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_scan_regions->setIcon(icon32);
        actionCreate_Mask_Image = new QAction(MainWindow);
        actionCreate_Mask_Image->setObjectName(QStringLiteral("actionCreate_Mask_Image"));
        QIcon icon33;
        icon33.addFile(QStringLiteral(":/icons/24/binarymask.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCreate_Mask_Image->setIcon(icon33);
        actionClick_Center_Objective = new QAction(MainWindow);
        actionClick_Center_Objective->setObjectName(QStringLiteral("actionClick_Center_Objective"));
        actionClick_Center_Objective->setCheckable(true);
        QIcon icon34;
        icon34.addFile(QStringLiteral(":/icons/24/objectivePosition.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClick_Center_Objective->setIcon(icon34);
        actionGrid_Spacing = new QAction(MainWindow);
        actionGrid_Spacing->setObjectName(QStringLiteral("actionGrid_Spacing"));
        actionGrid_Spacing->setCheckable(true);
        QIcon icon35;
        icon35.addFile(QStringLiteral(":/icons/24/spacing.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGrid_Spacing->setIcon(icon35);
        actionBackground_fit = new QAction(MainWindow);
        actionBackground_fit->setObjectName(QStringLiteral("actionBackground_fit"));
        QIcon icon36;
        icon36.addFile(QStringLiteral(":/icons/24/background.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionBackground_fit->setIcon(icon36);
        actionEqualise_Image = new QAction(MainWindow);
        actionEqualise_Image->setObjectName(QStringLiteral("actionEqualise_Image"));
        QIcon icon37;
        icon37.addFile(QStringLiteral(":/icons/24/histogram_equalization.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEqualise_Image->setIcon(icon37);
        actionCreate_Image_Mosaic = new QAction(MainWindow);
        actionCreate_Image_Mosaic->setObjectName(QStringLiteral("actionCreate_Image_Mosaic"));
        QIcon icon38;
        icon38.addFile(QStringLiteral(":/icons/24/mosaic.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCreate_Image_Mosaic->setIcon(icon38);
        actionDefine_Focus_Plane = new QAction(MainWindow);
        actionDefine_Focus_Plane->setObjectName(QStringLiteral("actionDefine_Focus_Plane"));
        actionDefine_Focus_Plane->setCheckable(true);
        QIcon icon39;
        icon39.addFile(QStringLiteral(":/icons/24/focusPlane.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDefine_Focus_Plane->setIcon(icon39);
        actionAnnotate_Shape = new QAction(MainWindow);
        actionAnnotate_Shape->setObjectName(QStringLiteral("actionAnnotate_Shape"));
        QIcon icon40;
        icon40.addFile(QStringLiteral(":/icons/24/annotate.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAnnotate_Shape->setIcon(icon40);
        actionTrainTarget = new QAction(MainWindow);
        actionTrainTarget->setObjectName(QStringLiteral("actionTrainTarget"));
        QIcon icon41;
        icon41.addFile(QStringLiteral(":/icons/24/traintarget.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTrainTarget->setIcon(icon41);
        actionLaplacian = new QAction(MainWindow);
        actionLaplacian->setObjectName(QStringLiteral("actionLaplacian"));
        QIcon icon42;
        icon42.addFile(QStringLiteral(":/icons/24/laplacian.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLaplacian->setIcon(icon42);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, -1, 0);
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        display_image = new PaintQLabel(splitter);
        display_image->setObjectName(QStringLiteral("display_image"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(100);
        sizePolicy1.setHeightForWidth(display_image->sizePolicy().hasHeightForWidth());
        display_image->setSizePolicy(sizePolicy1);
        display_image->setMinimumSize(QSize(254, 254));
        display_image->setToolTipDuration(1);
        display_image->setFrameShape(QFrame::NoFrame);
        display_image->setAlignment(Qt::AlignCenter);
        splitter->addWidget(display_image);
        scrollArea = new QScrollArea(splitter);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy2);
        scrollArea->setFrameShape(QFrame::Box);
        scrollArea->setFrameShadow(QFrame::Plain);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 849, 87));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(1);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy3);
        scrollAreaWidgetContents->setAutoFillBackground(true);
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        ImageThumbList = new QListWidget(scrollAreaWidgetContents);
        ImageThumbList->setObjectName(QStringLiteral("ImageThumbList"));
        ImageThumbList->setEnabled(true);
        sizePolicy3.setHeightForWidth(ImageThumbList->sizePolicy().hasHeightForWidth());
        ImageThumbList->setSizePolicy(sizePolicy3);
        ImageThumbList->setLayoutDirection(Qt::LeftToRight);
        ImageThumbList->setAutoFillBackground(true);
        ImageThumbList->setFrameShape(QFrame::NoFrame);
        ImageThumbList->setFrameShadow(QFrame::Plain);
        ImageThumbList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ImageThumbList->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        ImageThumbList->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        ImageThumbList->setAutoScroll(true);
        ImageThumbList->setAlternatingRowColors(false);
        ImageThumbList->setIconSize(QSize(50, 50));
        ImageThumbList->setProperty("isWrapping", QVariant(false));
        ImageThumbList->setResizeMode(QListView::Adjust);
        ImageThumbList->setViewMode(QListView::IconMode);
        ImageThumbList->setModelColumn(0);
        ImageThumbList->setUniformItemSizes(false);

        gridLayout->addWidget(ImageThumbList, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);
        splitter->addWidget(scrollArea);
        consoleDisplay = new QPlainTextEdit(splitter);
        consoleDisplay->setObjectName(QStringLiteral("consoleDisplay"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(1);
        sizePolicy4.setVerticalStretch(1);
        sizePolicy4.setHeightForWidth(consoleDisplay->sizePolicy().hasHeightForWidth());
        consoleDisplay->setSizePolicy(sizePolicy4);
        splitter->addWidget(consoleDisplay);

        verticalLayout->addWidget(splitter);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 939, 21));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        menu_File->setToolTipsVisible(true);
        menuImages = new QMenu(menuBar);
        menuImages->setObjectName(QStringLiteral("menuImages"));
        menuImages->setToolTipsVisible(true);
        menuDetection = new QMenu(menuBar);
        menuDetection->setObjectName(QStringLiteral("menuDetection"));
        menuDetection->setToolTipsVisible(true);
        menuCamera = new QMenu(menuBar);
        menuCamera->setObjectName(QStringLiteral("menuCamera"));
        menuCamera->setToolTipsVisible(true);
        menuImage_Processing = new QMenu(menuBar);
        menuImage_Processing->setObjectName(QStringLiteral("menuImage_Processing"));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QStringLiteral("menuSettings"));
        menuAlignment = new QMenu(menuBar);
        menuAlignment->setObjectName(QStringLiteral("menuAlignment"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuDrawing = new QMenu(menuBar);
        menuDrawing->setObjectName(QStringLiteral("menuDrawing"));
        menuSegmentation = new QMenu(menuBar);
        menuSegmentation->setObjectName(QStringLiteral("menuSegmentation"));
        MainWindow->setMenuBar(menuBar);
        toolbarOpenSave = new QToolBar(MainWindow);
        toolbarOpenSave->setObjectName(QStringLiteral("toolbarOpenSave"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolbarOpenSave);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBarSettings = new QToolBar(MainWindow);
        toolBarSettings->setObjectName(QStringLiteral("toolBarSettings"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBarSettings);
        toolBarDrawing = new QToolBar(MainWindow);
        toolBarDrawing->setObjectName(QStringLiteral("toolBarDrawing"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBarDrawing);
        toolBarZoomPann = new QToolBar(MainWindow);
        toolBarZoomPann->setObjectName(QStringLiteral("toolBarZoomPann"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBarZoomPann);
        toolBarImageAnalysis = new QToolBar(MainWindow);
        toolBarImageAnalysis->setObjectName(QStringLiteral("toolBarImageAnalysis"));
        MainWindow->addToolBar(Qt::RightToolBarArea, toolBarImageAnalysis);
        toolBarMicroscope = new QToolBar(MainWindow);
        toolBarMicroscope->setObjectName(QStringLiteral("toolBarMicroscope"));
        MainWindow->addToolBar(Qt::LeftToolBarArea, toolBarMicroscope);
        toolBarCamera = new QToolBar(MainWindow);
        toolBarCamera->setObjectName(QStringLiteral("toolBarCamera"));
        MainWindow->addToolBar(Qt::LeftToolBarArea, toolBarCamera);
        toolBarBinaryOperations = new QToolBar(MainWindow);
        toolBarBinaryOperations->setObjectName(QStringLiteral("toolBarBinaryOperations"));
        MainWindow->addToolBar(Qt::RightToolBarArea, toolBarBinaryOperations);
        toolBarTargets = new QToolBar(MainWindow);
        toolBarTargets->setObjectName(QStringLiteral("toolBarTargets"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBarTargets);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menuImages->menuAction());
        menuBar->addAction(menuDrawing->menuAction());
        menuBar->addAction(menuCamera->menuAction());
        menuBar->addAction(menuAlignment->menuAction());
        menuBar->addAction(menuSegmentation->menuAction());
        menuBar->addAction(menuImage_Processing->menuAction());
        menuBar->addAction(menuDetection->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuSettings->menuAction());
        menu_File->addAction(action_New);
        menu_File->addAction(action_Open);
        menu_File->addAction(action_Save);
        menu_File->addSeparator();
        menu_File->addAction(actionGrab_Image_From_Camera);
        menu_File->addAction(actionProcessFocusStack);
        menu_File->addAction(action_Exit);
        menu_File->addSeparator();
        menuImages->addAction(actionSelect_All);
        menuImages->addAction(actionDeselect_All);
        menuImages->addSeparator();
        menuImages->addAction(actionSet_as_Target);
        menuImages->addAction(actionSet_as_find_targets_image);
        menuImages->addSeparator();
        menuImages->addAction(actionDeleteObject);
        menuDetection->addAction(actionTrainTarget);
        menuDetection->addAction(actionScoreImage);
        menuDetection->addAction(actionFind_targets);
        menuDetection->addAction(actionSave_Target_Positions);
        menuDetection->addAction(actionSample_White_Binary_Regions);
        menuCamera->addAction(actionProcessFocusStack);
        menuCamera->addAction(actionGrab_Video_From_Camera);
        menuCamera->addAction(actionGrab_Image_From_Camera);
        menuCamera->addAction(actionClick_Center_Objective);
        menuCamera->addAction(action_scan_regions);
        menuCamera->addAction(actionRead_Barcode);
        menuCamera->addAction(actionCreate_Image_Mosaic);
        menuImage_Processing->addAction(actionInvert);
        menuImage_Processing->addAction(actionConnected_Components);
        menuImage_Processing->addAction(actionFilter_Binary_Objects);
        menuImage_Processing->addAction(actionFind_Centers);
        menuImage_Processing->addAction(actionMergeImages);
        menuSettings->addAction(actionSettings);
        menuSettings->addAction(actionHelp);
        menuAlignment->addAction(actionBackground_fit);
        menuAlignment->addAction(actionDetect_lines);
        menuAlignment->addAction(actionCalibrate_Camera);
        menuAlignment->addAction(actionCorrectImage);
        menuAlignment->addAction(actionReference_fiducial_marks);
        menuView->addAction(actionZoom_Out);
        menuView->addAction(actionZoom_In);
        menuView->addAction(action_Move_Image);
        menuDrawing->addAction(actionDraw_Circle_Region);
        menuDrawing->addAction(actionDraw_Rectangular_Region);
        menuDrawing->addAction(actionDraw_Polygon);
        menuDrawing->addAction(actionCreate_Mask_Image);
        menuDrawing->addAction(actionGet_Target_image_region);
        menuDrawing->addAction(actionMask_White);
        menuDrawing->addAction(actionMask_Black);
        menuDrawing->addAction(actionSelect_Object);
        menuSegmentation->addAction(actionEntropyFilter);
        menuSegmentation->addAction(actionThresholdImage);
        menuSegmentation->addAction(actionEqualise_Image);
        menuSegmentation->addAction(actionEdge_Detection);
        menuSegmentation->addAction(actionCorner_Detection);
        toolbarOpenSave->addAction(action_New);
        toolbarOpenSave->addSeparator();
        toolbarOpenSave->addAction(action_Open);
        toolbarOpenSave->addAction(action_Save);
        toolBarSettings->addAction(actionDeleteObject);
        toolBarSettings->addAction(actionSettings);
        toolBarDrawing->addAction(actionDraw_Rectangular_Region);
        toolBarDrawing->addAction(actionDraw_Circle_Region);
        toolBarDrawing->addAction(actionDraw_Polygon);
        toolBarDrawing->addAction(actionAnnotate_Shape);
        toolBarDrawing->addAction(actionGrid_Spacing);
        toolBarDrawing->addSeparator();
        toolBarDrawing->addAction(actionClickTarget);
        toolBarDrawing->addAction(actionReference_fiducial_marks);
        toolBarDrawing->addAction(actionClick_Center_Objective);
        toolBarDrawing->addSeparator();
        toolBarDrawing->addAction(actionMask_White);
        toolBarDrawing->addAction(actionMask_Black);
        toolBarDrawing->addSeparator();
        toolBarDrawing->addAction(actionCreate_Mask_Image);
        toolBarDrawing->addAction(actionGet_Target_image_region);
        toolBarZoomPann->addAction(action_Move_Image);
        toolBarZoomPann->addAction(actionZoom_Out);
        toolBarZoomPann->addAction(actionZoom_In);
        toolBarImageAnalysis->addAction(actionThresholdImage);
        toolBarImageAnalysis->addAction(actionEqualise_Image);
        toolBarImageAnalysis->addAction(actionEntropyFilter);
        toolBarImageAnalysis->addAction(actionBackground_fit);
        toolBarImageAnalysis->addAction(actionLaplacian);
        toolBarMicroscope->addAction(action_scan_regions);
        toolBarMicroscope->addAction(actionCreate_Image_Mosaic);
        toolBarMicroscope->addAction(actionRead_Barcode);
        toolBarMicroscope->addAction(actionDetect_lines);
        toolBarMicroscope->addAction(actionCalibrate_Camera);
        toolBarMicroscope->addAction(actionCorrectImage);
        toolBarCamera->addAction(actionProcessFocusStack);
        toolBarCamera->addAction(actionGrab_Video_From_Camera);
        toolBarCamera->addAction(actionGrab_Image_From_Camera);
        toolBarBinaryOperations->addAction(actionInvert);
        toolBarBinaryOperations->addAction(actionConnected_Components);
        toolBarBinaryOperations->addAction(actionFilter_Binary_Objects);
        toolBarBinaryOperations->addAction(actionFind_Centers);
        toolBarBinaryOperations->addAction(actionMergeImages);
        toolBarTargets->addAction(actionTrainTarget);
        toolBarTargets->addAction(actionSample_White_Binary_Regions);
        toolBarTargets->addAction(actionScoreImage);
        toolBarTargets->addAction(actionFind_targets);
        toolBarTargets->addAction(actionSave_Target_Positions);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Targeter", Q_NULLPTR));
        actionFile->setText(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        action_File->setText(QApplication::translate("MainWindow", "&File", Q_NULLPTR));
        action_Exit->setText(QApplication::translate("MainWindow", "&Exit", Q_NULLPTR));
        action_Open->setText(QApplication::translate("MainWindow", "&Open", Q_NULLPTR));
        actionProcessFocusStack->setText(QApplication::translate("MainWindow", "&FocusStack", Q_NULLPTR));
        actionProcessFocusStack->setIconText(QApplication::translate("MainWindow", "FocusStack", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionProcessFocusStack->setToolTip(QApplication::translate("MainWindow", "Combine Focus Stack Images", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_Save->setText(QApplication::translate("MainWindow", "&Save", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_Save->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Save Image File</span></p><p>If file name ends with underscore number (eg. _10.png) then filenames numbered consequentially (11 etc)</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionSelect_All->setText(QApplication::translate("MainWindow", "Select All", Q_NULLPTR));
        actionDeselect_All->setText(QApplication::translate("MainWindow", "Deselect All", Q_NULLPTR));
        actionDeselect_All->setIconText(QApplication::translate("MainWindow", "Deselect All", Q_NULLPTR));
        actionGrab_Image_From_Camera->setText(QApplication::translate("MainWindow", "&Grab Image From Camera", Q_NULLPTR));
        actionZoom_Out->setText(QApplication::translate("MainWindow", "Zoom &Out", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionZoom_Out->setToolTip(QApplication::translate("MainWindow", "Zoom out of Image", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionZoom_In->setText(QApplication::translate("MainWindow", "Zoom &In", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionZoom_In->setToolTip(QApplication::translate("MainWindow", "Zoom in closer to image ", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionDraw_Polygon->setText(QApplication::translate("MainWindow", "Draw &Polygon Region", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionDraw_Polygon->setToolTip(QApplication::translate("MainWindow", "Draw polygon to select region", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionDraw_Circle_Region->setText(QApplication::translate("MainWindow", "Draw &Circle Region", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionDraw_Circle_Region->setToolTip(QApplication::translate("MainWindow", "Draw circle to select Region", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionDraw_Rectangular_Region->setText(QApplication::translate("MainWindow", "Draw &Rectangular Region", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionDraw_Rectangular_Region->setToolTip(QApplication::translate("MainWindow", "Draw rectangle to select region", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_Move_Image->setText(QApplication::translate("MainWindow", "&Move Image", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_Move_Image->setToolTip(QApplication::translate("MainWindow", "Move image or selected drawing object ", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionGet_Target_image_region->setText(QApplication::translate("MainWindow", "Make new image from region", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionGet_Target_image_region->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Create<span style=\" font-weight:600;\"> target image</span> from drawn boundary region and polygon/circular shape</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionSet_as_Target->setText(QApplication::translate("MainWindow", "Set/Unset as 'good target' image", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSet_as_Target->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>This will set/unset the selected image as a suitable <span style=\" font-weight:600;\">target image</span> to use for image analysis <span style=\" font-weight:600;\">training</span></p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionSet_as_find_targets_image->setText(QApplication::translate("MainWindow", "Set/unset as 'find targets' image", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSet_as_find_targets_image->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>This will set/unset the checked image as the <span style=\" font-weight:600;\">test image</span> in which image analysis will try to <span style=\" font-weight:600;\">find</span> targets</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionFind_targets->setText(QApplication::translate("MainWindow", "Detect Targets", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionFind_targets->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>By clicking this button image analysis algorithms trained on the example target images and<span style=\" font-weight:600;\"> best target regions within the 'test' image will be detected</span>. </p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionDeleteObject->setText(QApplication::translate("MainWindow", "&Delete object", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionDeleteObject->setToolTip(QApplication::translate("MainWindow", "Deletes current drawing object or selected image", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionTarget_detection_settings->setText(QApplication::translate("MainWindow", "target detection settings", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionTarget_detection_settings->setToolTip(QApplication::translate("MainWindow", "manage how targets are detected", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionThresholdImage->setText(QApplication::translate("MainWindow", "Threshold Image", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionThresholdImage->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>By clicking this button the current image will be &lt;b&gt;thresholded&lt;/b&gt; to a black/white image</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionMergeImages->setText(QApplication::translate("MainWindow", "Merge Images", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionMergeImages->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Combines a binary mask image with another image by multiplication. </p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionSettings->setText(QApplication::translate("MainWindow", "Targeter Settings", Q_NULLPTR));
        actionReference_fiducial_marks->setText(QApplication::translate("MainWindow", "Reference fiducial marks", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionReference_fiducial_marks->setToolTip(QApplication::translate("MainWindow", "Reference fiducial marks by clicking on the image", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionFind_Centers->setText(QApplication::translate("MainWindow", "Find Centers", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionFind_Centers->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Find center of regions in a connected component image</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionInvert->setText(QApplication::translate("MainWindow", "Invert Colours", Q_NULLPTR));
        actionConnected_Components->setText(QApplication::translate("MainWindow", "Connected Components", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionConnected_Components->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Finds connected components regions in a binary image. Non touching white regions are labelled with a region number. </p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionFilter_Binary_Objects->setText(QApplication::translate("MainWindow", "Filter Binary Objects", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionFilter_Binary_Objects->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Processes conneceted component image to find only those regions that meet size or shape criteria</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionSave_Target_Positions->setText(QApplication::translate("MainWindow", "Save Target Positions", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSave_Target_Positions->setToolTip(QApplication::translate("MainWindow", "Save Target Positions to XML file", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionScoreImage->setText(QApplication::translate("MainWindow", "ScoreImage", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionScoreImage->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>By clicking this button a 'good targets' score image is created, brighter pixels show best 'good target' positions.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionCalibrate_Camera->setText(QApplication::translate("MainWindow", "Calibrate Camera", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionCalibrate_Camera->setToolTip(QApplication::translate("MainWindow", "Calibrate Camera using alignment images (chessboard or circles)", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionCorrectImage->setText(QApplication::translate("MainWindow", "Correct Image Distortion", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionCorrectImage->setToolTip(QApplication::translate("MainWindow", "the image will be corrected if camera calibration has first been performed", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionGrab_Video_From_Camera->setText(QApplication::translate("MainWindow", "Grab Video From Camera", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionGrab_Video_From_Camera->setToolTip(QApplication::translate("MainWindow", "Get and show real time video from connected Basler camera", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionDetect_lines->setText(QApplication::translate("MainWindow", "Detect lines in Video", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionDetect_lines->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><span style=\" text-decoration: underline;\">Find lines in image</span><br>numbers on left = distance of line to image center<br>numbers on right = angle of lines</body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionCorner_Detection->setText(QApplication::translate("MainWindow", "Corner Detection", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionCorner_Detection->setToolTip(QApplication::translate("MainWindow", "Detect corners in image", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionEdge_Detection->setText(QApplication::translate("MainWindow", "Edge Detection", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionEdge_Detection->setToolTip(QApplication::translate("MainWindow", "Performs Canny edge detection on image", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionEntropyFilter->setText(QApplication::translate("MainWindow", "entropyFilter", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionEntropyFilter->setToolTip(QApplication::translate("MainWindow", "Perform entropy filtering on image", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionEnergy_image->setText(QApplication::translate("MainWindow", "Energy image", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionEnergy_image->setToolTip(QApplication::translate("MainWindow", "Create laplacian pyramid energy image", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionRemoveBlackPixels->setText(QApplication::translate("MainWindow", "RemoveBlackPixels", Q_NULLPTR));
        action_New->setText(QApplication::translate("MainWindow", "Create Project", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_New->setToolTip(QApplication::translate("MainWindow", "Go to project settings page", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionHelp->setText(QApplication::translate("MainWindow", "Help", Q_NULLPTR));
        actionDeleteImage->setText(QApplication::translate("MainWindow", "Delete Image", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionDeleteImage->setToolTip(QApplication::translate("MainWindow", "Delete this image", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionSample_White_Binary_Regions->setText(QApplication::translate("MainWindow", "Sample White Binary Regions", Q_NULLPTR));
        actionMask_White->setText(QApplication::translate("MainWindow", "Mask White", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionMask_White->setToolTip(QApplication::translate("MainWindow", "Mask image area white (ie. analyse this region)", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionMask_Black->setText(QApplication::translate("MainWindow", "Mask Black", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionMask_Black->setToolTip(QApplication::translate("MainWindow", "Mask image area black (ie. do not analyse this region)", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionSelect_Object->setText(QApplication::translate("MainWindow", "Select Object", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSelect_Object->setToolTip(QApplication::translate("MainWindow", "Select Drawing Object(s)", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionClickTarget->setText(QApplication::translate("MainWindow", "ClickTarget", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionClickTarget->setToolTip(QApplication::translate("MainWindow", "Click on image to define target", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionRead_Barcode->setText(QApplication::translate("MainWindow", "Read  Barcode", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionRead_Barcode->setToolTip(QApplication::translate("MainWindow", "Find and read Code39 linear barcode in image", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_scan_regions->setText(QApplication::translate("MainWindow", "Scan microscope regions", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_scan_regions->setToolTip(QApplication::translate("MainWindow", "Grab microscope images as a mosaic from masked regions of sample frame (use rectangle drawing shape to define regions of interest on the overview image first)", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionCreate_Mask_Image->setText(QApplication::translate("MainWindow", "Create Mask Image", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionCreate_Mask_Image->setToolTip(QApplication::translate("MainWindow", "Create mask image from black/white shapes", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionClick_Center_Objective->setText(QApplication::translate("MainWindow", "Click Center Objective", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionClick_Center_Objective->setToolTip(QApplication::translate("MainWindow", "Click overview image to center microscope objective at this place", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionGrid_Spacing->setText(QApplication::translate("MainWindow", "Sample Spacing", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionGrid_Spacing->setToolTip(QApplication::translate("MainWindow", "select then click twice on image to specify for sampling spacing", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionBackground_fit->setText(QApplication::translate("MainWindow", "Background fit", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionBackground_fit->setToolTip(QApplication::translate("MainWindow", "Fits image background (eg. to model illumination)", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionEqualise_Image->setText(QApplication::translate("MainWindow", "Equalise Image", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionEqualise_Image->setToolTip(QApplication::translate("MainWindow", "Contrast equalise image", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionCreate_Image_Mosaic->setText(QApplication::translate("MainWindow", "Create Image Mosaic", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionCreate_Image_Mosaic->setToolTip(QApplication::translate("MainWindow", "Stitch images together to produce an image mosaic", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionDefine_Focus_Plane->setText(QApplication::translate("MainWindow", "Define Focus Plane", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionDefine_Focus_Plane->setToolTip(QApplication::translate("MainWindow", "Move XY and Z stages until target  in focus, then click once on overview image to define focus Z centre, clicking three times or more in different regions will define focus plane.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionAnnotate_Shape->setText(QApplication::translate("MainWindow", "Annotate Shape", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionAnnotate_Shape->setToolTip(QApplication::translate("MainWindow", "Click to add annotation information to drawn region (eg. what this region represents)", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionTrainTarget->setText(QApplication::translate("MainWindow", "Train on Target", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionTrainTarget->setToolTip(QApplication::translate("MainWindow", "Train image analysis algorithm on selected example targets.  ", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionLaplacian->setText(QApplication::translate("MainWindow", "laplacian", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionLaplacian->setToolTip(QApplication::translate("MainWindow", "perform laplacian on image", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        display_image->setText(QString());
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", Q_NULLPTR));
        menuImages->setTitle(QApplication::translate("MainWindow", "Image List", Q_NULLPTR));
        menuDetection->setTitle(QApplication::translate("MainWindow", "Target Detection", Q_NULLPTR));
        menuCamera->setTitle(QApplication::translate("MainWindow", "Cameras", Q_NULLPTR));
        menuImage_Processing->setTitle(QApplication::translate("MainWindow", "Binary Objects", Q_NULLPTR));
        menuSettings->setTitle(QApplication::translate("MainWindow", "Settings", Q_NULLPTR));
        menuAlignment->setTitle(QApplication::translate("MainWindow", "Calibration", Q_NULLPTR));
        menuView->setTitle(QApplication::translate("MainWindow", "View", Q_NULLPTR));
        menuDrawing->setTitle(QApplication::translate("MainWindow", "Drawing", Q_NULLPTR));
        menuSegmentation->setTitle(QApplication::translate("MainWindow", "Segmentation", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        toolbarOpenSave->setToolTip(QApplication::translate("MainWindow", "Open/Save images and XML files", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        toolBarSettings->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        toolBarSettings->setToolTip(QApplication::translate("MainWindow", "Settings dialog", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        toolBarDrawing->setWindowTitle(QApplication::translate("MainWindow", "toolBar_2", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        toolBarDrawing->setToolTip(QApplication::translate("MainWindow", "Controls for drawing on image", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        toolBarZoomPann->setWindowTitle(QApplication::translate("MainWindow", "toolBar_3", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        toolBarZoomPann->setToolTip(QApplication::translate("MainWindow", "Zooming/Panning operations on image", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        toolBarImageAnalysis->setWindowTitle(QApplication::translate("MainWindow", "toolBar_4", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        toolBarImageAnalysis->setToolTip(QApplication::translate("MainWindow", "Image analysis operations", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        toolBarMicroscope->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        toolBarMicroscope->setToolTip(QApplication::translate("MainWindow", "Microscope related operations", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        toolBarCamera->setWindowTitle(QApplication::translate("MainWindow", "toolBar_2", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        toolBarCamera->setToolTip(QApplication::translate("MainWindow", "Camera related operations", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        toolBarBinaryOperations->setWindowTitle(QApplication::translate("MainWindow", "toolBar_3", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        toolBarBinaryOperations->setToolTip(QApplication::translate("MainWindow", "Binary image analysis operations", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        toolBarTargets->setWindowTitle(QApplication::translate("MainWindow", "toolBar_4", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        toolBarTargets->setToolTip(QApplication::translate("MainWindow", "Target detection operations", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
