/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
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
#include <QtWidgets/QScrollArea>
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
    QAction *actionDeleteImage;
    QAction *actionThresholdImage;
    QAction *actionMergeImages;
    QAction *actionSettings;
    QAction *actionReference_fuducial_marks;
    QAction *actionFind_Centers;
    QAction *actionInvert;
    QAction *actionConnected_Components;
    QAction *actionFilter_Binary_Objects;
    QAction *actionSave_Target_Positions;
    QAction *actionScoreImage;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    PaintQLabel *display_image;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QListWidget *ImageThumbList;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menuImages;
    QMenu *menuWith_Selected;
    QMenu *menuMask_target_region;
    QMenu *menuType_Here;
    QMenu *menuImage_Zoom_Panning;
    QMenu *menuDetection;
    QMenu *menuCamera;
    QMenu *menuImage_Processing;
    QMenu *menuSettings;
    QMenu *menuAlignment;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;
    QToolBar *toolBar_2;
    QToolBar *toolBar_3;
    QToolBar *toolBar_4;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(822, 682);
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
        icon8.addFile(QStringLiteral(":/icons/24/grabhand.ico"), QSize(), QIcon::Normal, QIcon::Off);
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
        actionDeleteImage = new QAction(MainWindow);
        actionDeleteImage->setObjectName(QStringLiteral("actionDeleteImage"));
        actionDeleteImage->setIcon(icon10);
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
        actionReference_fuducial_marks = new QAction(MainWindow);
        actionReference_fuducial_marks->setObjectName(QStringLiteral("actionReference_fuducial_marks"));
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/icons/24/marks.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionReference_fuducial_marks->setIcon(icon14);
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
        actionScoreImage = new QAction(MainWindow);
        actionScoreImage->setObjectName(QStringLiteral("actionScoreImage"));
        QIcon icon19;
        icon19.addFile(QStringLiteral(":/icons/24/scoreimage.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionScoreImage->setIcon(icon19);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(20);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        display_image = new PaintQLabel(centralWidget);
        display_image->setObjectName(QStringLiteral("display_image"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(display_image->sizePolicy().hasHeightForWidth());
        display_image->setSizePolicy(sizePolicy1);
        display_image->setMinimumSize(QSize(254, 254));
        display_image->setToolTipDuration(1);
        display_image->setFrameShape(QFrame::NoFrame);
        display_image->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(display_image);

        scrollArea = new QScrollArea(centralWidget);
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
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 765, 87));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(1);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy3);
        scrollAreaWidgetContents->setAutoFillBackground(true);
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
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

        verticalLayout_2->addWidget(ImageThumbList);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 822, 21));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        menu_File->setToolTipsVisible(true);
        menuImages = new QMenu(menuBar);
        menuImages->setObjectName(QStringLiteral("menuImages"));
        menuImages->setToolTipsVisible(true);
        menuWith_Selected = new QMenu(menuImages);
        menuWith_Selected->setObjectName(QStringLiteral("menuWith_Selected"));
        menuWith_Selected->setToolTipsVisible(true);
        menuMask_target_region = new QMenu(menuImages);
        menuMask_target_region->setObjectName(QStringLiteral("menuMask_target_region"));
        menuMask_target_region->setToolTipsVisible(true);
        menuType_Here = new QMenu(menuImages);
        menuType_Here->setObjectName(QStringLiteral("menuType_Here"));
        menuImage_Zoom_Panning = new QMenu(menuImages);
        menuImage_Zoom_Panning->setObjectName(QStringLiteral("menuImage_Zoom_Panning"));
        menuImage_Zoom_Panning->setToolTipsVisible(true);
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
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::LeftToolBarArea, toolBar);
        toolBar_2 = new QToolBar(MainWindow);
        toolBar_2->setObjectName(QStringLiteral("toolBar_2"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar_2);
        toolBar_3 = new QToolBar(MainWindow);
        toolBar_3->setObjectName(QStringLiteral("toolBar_3"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar_3);
        toolBar_4 = new QToolBar(MainWindow);
        toolBar_4->setObjectName(QStringLiteral("toolBar_4"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar_4);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menuImages->menuAction());
        menuBar->addAction(menuCamera->menuAction());
        menuBar->addAction(menuAlignment->menuAction());
        menuBar->addAction(menuImage_Processing->menuAction());
        menuBar->addAction(menuDetection->menuAction());
        menuBar->addAction(menuSettings->menuAction());
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
        menuImages->addAction(menuImage_Zoom_Panning->menuAction());
        menuImages->addSeparator();
        menuImages->addAction(menuWith_Selected->menuAction());
        menuImages->addAction(menuMask_target_region->menuAction());
        menuImages->addSeparator();
        menuImages->addAction(actionDeleteObject);
        menuImages->addAction(menuType_Here->menuAction());
        menuWith_Selected->addAction(actionSet_as_Target);
        menuWith_Selected->addAction(actionSet_as_find_targets_image);
        menuMask_target_region->addAction(actionDraw_Circle_Region);
        menuMask_target_region->addAction(actionDraw_Rectangular_Region);
        menuMask_target_region->addAction(actionDraw_Polygon);
        menuMask_target_region->addAction(actionGet_Target_image_region);
        menuImage_Zoom_Panning->addAction(actionZoom_In);
        menuImage_Zoom_Panning->addAction(actionZoom_Out);
        menuImage_Zoom_Panning->addAction(action_Move_Image);
        menuDetection->addAction(actionScoreImage);
        menuDetection->addAction(actionFind_targets);
        menuDetection->addAction(actionSave_Target_Positions);
        menuCamera->addAction(actionGrab_Image_From_Camera);
        menuImage_Processing->addSeparator();
        menuImage_Processing->addAction(actionThresholdImage);
        menuImage_Processing->addAction(actionMergeImages);
        menuImage_Processing->addAction(actionConnected_Components);
        menuImage_Processing->addAction(actionFilter_Binary_Objects);
        menuImage_Processing->addAction(actionFind_Centers);
        menuImage_Processing->addSeparator();
        menuImage_Processing->addAction(actionInvert);
        menuImage_Processing->addSeparator();
        menuSettings->addAction(actionSettings);
        menuAlignment->addAction(actionReference_fuducial_marks);
        mainToolBar->addAction(action_Open);
        mainToolBar->addAction(action_Save);
        toolBar->addAction(actionGrab_Image_From_Camera);
        toolBar->addAction(actionReference_fuducial_marks);
        toolBar->addAction(actionDeleteObject);
        toolBar->addAction(actionSettings);
        toolBar_2->addAction(actionDraw_Rectangular_Region);
        toolBar_2->addAction(actionDraw_Circle_Region);
        toolBar_2->addAction(actionDraw_Polygon);
        toolBar_2->addSeparator();
        toolBar_2->addAction(actionGet_Target_image_region);
        toolBar_2->addAction(actionScoreImage);
        toolBar_2->addAction(actionFind_targets);
        toolBar_3->addAction(actionZoom_Out);
        toolBar_3->addAction(actionZoom_In);
        toolBar_3->addAction(action_Move_Image);
        toolBar_4->addAction(actionProcessFocusStack);
        toolBar_4->addSeparator();
        toolBar_4->addAction(actionThresholdImage);
        toolBar_4->addAction(actionMergeImages);
        toolBar_4->addAction(actionInvert);
        toolBar_4->addAction(actionConnected_Components);
        toolBar_4->addAction(actionFind_Centers);
        toolBar_4->addSeparator();
        toolBar_4->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Targeter", 0));
        actionFile->setText(QApplication::translate("MainWindow", "File", 0));
        action_File->setText(QApplication::translate("MainWindow", "&File", 0));
        action_Exit->setText(QApplication::translate("MainWindow", "&Exit", 0));
        action_Open->setText(QApplication::translate("MainWindow", "&Open", 0));
        actionProcessFocusStack->setText(QApplication::translate("MainWindow", "&FocusStack", 0));
        actionProcessFocusStack->setIconText(QApplication::translate("MainWindow", "FocusStack", 0));
#ifndef QT_NO_TOOLTIP
        actionProcessFocusStack->setToolTip(QApplication::translate("MainWindow", "Combine Focus Stack Images", 0));
#endif // QT_NO_TOOLTIP
        action_Save->setText(QApplication::translate("MainWindow", "&Save", 0));
        actionSelect_All->setText(QApplication::translate("MainWindow", "Select All", 0));
        actionDeselect_All->setText(QApplication::translate("MainWindow", "Deselect All", 0));
        actionDeselect_All->setIconText(QApplication::translate("MainWindow", "Deselect All", 0));
        actionGrab_Image_From_Camera->setText(QApplication::translate("MainWindow", "&Grab Image From Camera", 0));
        actionZoom_Out->setText(QApplication::translate("MainWindow", "Zoom &Out", 0));
#ifndef QT_NO_TOOLTIP
        actionZoom_Out->setToolTip(QApplication::translate("MainWindow", "Zoom out of Image", 0));
#endif // QT_NO_TOOLTIP
        actionZoom_In->setText(QApplication::translate("MainWindow", "Zoom &In", 0));
#ifndef QT_NO_TOOLTIP
        actionZoom_In->setToolTip(QApplication::translate("MainWindow", "Zoom in closer to image ", 0));
#endif // QT_NO_TOOLTIP
        actionDraw_Polygon->setText(QApplication::translate("MainWindow", "Draw &Polygon Region", 0));
#ifndef QT_NO_TOOLTIP
        actionDraw_Polygon->setToolTip(QApplication::translate("MainWindow", "Draw polygon to select region", 0));
#endif // QT_NO_TOOLTIP
        actionDraw_Circle_Region->setText(QApplication::translate("MainWindow", "Draw &Circle Region", 0));
#ifndef QT_NO_TOOLTIP
        actionDraw_Circle_Region->setToolTip(QApplication::translate("MainWindow", "Draw circle to select Region", 0));
#endif // QT_NO_TOOLTIP
        actionDraw_Rectangular_Region->setText(QApplication::translate("MainWindow", "Draw &Rectangular Region", 0));
#ifndef QT_NO_TOOLTIP
        actionDraw_Rectangular_Region->setToolTip(QApplication::translate("MainWindow", "Draw rectangle to select region", 0));
#endif // QT_NO_TOOLTIP
        action_Move_Image->setText(QApplication::translate("MainWindow", "&Move Image", 0));
#ifndef QT_NO_TOOLTIP
        action_Move_Image->setToolTip(QApplication::translate("MainWindow", "Move image or selected drawing object ", 0));
#endif // QT_NO_TOOLTIP
        actionGet_Target_image_region->setText(QApplication::translate("MainWindow", "Get &Target image region", 0));
#ifndef QT_NO_TOOLTIP
        actionGet_Target_image_region->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Create<span style=\" font-weight:600;\"> target image</span> from drawn boundary region and polygon/circular shape</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        actionSet_as_Target->setText(QApplication::translate("MainWindow", "Set/Unset as 'good target' image", 0));
#ifndef QT_NO_TOOLTIP
        actionSet_as_Target->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>This will set/unset the selected image as a suitable <span style=\" font-weight:600;\">target image</span> to use for image analysis <span style=\" font-weight:600;\">training</span></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        actionSet_as_find_targets_image->setText(QApplication::translate("MainWindow", "Set/unset as 'find targets' image", 0));
#ifndef QT_NO_TOOLTIP
        actionSet_as_find_targets_image->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>This will set/unset the checked image as the <span style=\" font-weight:600;\">test image</span> in which image analysis will try to <span style=\" font-weight:600;\">find</span> targets</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        actionFind_targets->setText(QApplication::translate("MainWindow", "Detect Targets", 0));
#ifndef QT_NO_TOOLTIP
        actionFind_targets->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>By clicking this button image analysis algorithms trained on the example target images and<span style=\" font-weight:600;\"> best target regions within the 'test' image will be detected</span>. </p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        actionDeleteObject->setText(QApplication::translate("MainWindow", "&Delete object", 0));
#ifndef QT_NO_TOOLTIP
        actionDeleteObject->setToolTip(QApplication::translate("MainWindow", "Deletes current drawing object or selected image", 0));
#endif // QT_NO_TOOLTIP
        actionTarget_detection_settings->setText(QApplication::translate("MainWindow", "target detection settings", 0));
#ifndef QT_NO_TOOLTIP
        actionTarget_detection_settings->setToolTip(QApplication::translate("MainWindow", "manage how targets are detected", 0));
#endif // QT_NO_TOOLTIP
        actionDeleteImage->setText(QApplication::translate("MainWindow", "DeleteImage", 0));
#ifndef QT_NO_TOOLTIP
        actionDeleteImage->setToolTip(QApplication::translate("MainWindow", "Deletes Image", 0));
#endif // QT_NO_TOOLTIP
        actionThresholdImage->setText(QApplication::translate("MainWindow", "Threshold Image", 0));
#ifndef QT_NO_TOOLTIP
        actionThresholdImage->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>By clicking this button the current image will be &lt;b&gt;thresholded&lt;/b&gt; to a black/white image</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        actionMergeImages->setText(QApplication::translate("MainWindow", "Merge Images", 0));
#ifndef QT_NO_TOOLTIP
        actionMergeImages->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Combines a binary mask image with another image by multiplication. </p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        actionSettings->setText(QApplication::translate("MainWindow", "Targeter Settings", 0));
        actionReference_fuducial_marks->setText(QApplication::translate("MainWindow", "Reference fuducial marks", 0));
        actionFind_Centers->setText(QApplication::translate("MainWindow", "Find Centers", 0));
#ifndef QT_NO_TOOLTIP
        actionFind_Centers->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Find center of regions in a connected component image</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        actionInvert->setText(QApplication::translate("MainWindow", "Invert Colours", 0));
        actionConnected_Components->setText(QApplication::translate("MainWindow", "Connected Components", 0));
#ifndef QT_NO_TOOLTIP
        actionConnected_Components->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Finds connected components regions in a binary image. Non touching white regions are labelled with a region number. </p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        actionFilter_Binary_Objects->setText(QApplication::translate("MainWindow", "Filter Binary Objects", 0));
#ifndef QT_NO_TOOLTIP
        actionFilter_Binary_Objects->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Processes conneceted component image to find only those regions that meet size or shape criteria</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        actionSave_Target_Positions->setText(QApplication::translate("MainWindow", "Save Target Positions", 0));
        actionScoreImage->setText(QApplication::translate("MainWindow", "ScoreImage", 0));
#ifndef QT_NO_TOOLTIP
        actionScoreImage->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>By clicking this button a 'good targets' score image is created, brighter pixels show best 'good target' positions.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        display_image->setText(QString());
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0));
        menuImages->setTitle(QApplication::translate("MainWindow", "Images", 0));
        menuWith_Selected->setTitle(QApplication::translate("MainWindow", "With Selected ...", 0));
        menuMask_target_region->setTitle(QApplication::translate("MainWindow", "Mask target region", 0));
        menuType_Here->setTitle(QApplication::translate("MainWindow", "Type Here", 0));
        menuImage_Zoom_Panning->setTitle(QApplication::translate("MainWindow", "Image Zoom/Panning", 0));
        menuDetection->setTitle(QApplication::translate("MainWindow", "Detection", 0));
        menuCamera->setTitle(QApplication::translate("MainWindow", "Camera", 0));
        menuImage_Processing->setTitle(QApplication::translate("MainWindow", "Image Processing", 0));
        menuSettings->setTitle(QApplication::translate("MainWindow", "Settings", 0));
        menuAlignment->setTitle(QApplication::translate("MainWindow", "Alignment", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
#ifndef QT_NO_TOOLTIP
        toolBar->setToolTip(QApplication::translate("MainWindow", "drawing tools", 0));
#endif // QT_NO_TOOLTIP
        toolBar_2->setWindowTitle(QApplication::translate("MainWindow", "toolBar_2", 0));
        toolBar_3->setWindowTitle(QApplication::translate("MainWindow", "toolBar_3", 0));
        toolBar_4->setWindowTitle(QApplication::translate("MainWindow", "toolBar_4", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
