/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[156];
    char stringdata0[2946];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 8), // "getVideo"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 18), // "cameraType::camera"
QT_MOC_LITERAL(4, 40, 11), // "assignPorts"
QT_MOC_LITERAL(5, 52, 14), // "reportCOMPORTS"
QT_MOC_LITERAL(6, 67, 16), // "QVector<QString>"
QT_MOC_LITERAL(7, 84, 3), // "str"
QT_MOC_LITERAL(8, 88, 14), // "MoveAbsoluteXY"
QT_MOC_LITERAL(9, 103, 1), // "x"
QT_MOC_LITERAL(10, 105, 1), // "y"
QT_MOC_LITERAL(11, 107, 15), // "ACTIONS::action"
QT_MOC_LITERAL(12, 123, 3), // "act"
QT_MOC_LITERAL(13, 127, 14), // "MoveRelativeXY"
QT_MOC_LITERAL(14, 142, 13), // "MoveAbsoluteZ"
QT_MOC_LITERAL(15, 156, 1), // "z"
QT_MOC_LITERAL(16, 158, 13), // "SendCommandXY"
QT_MOC_LITERAL(17, 172, 3), // "cmd"
QT_MOC_LITERAL(18, 176, 13), // "SetVelocityXY"
QT_MOC_LITERAL(19, 190, 4), // "velo"
QT_MOC_LITERAL(20, 195, 11), // "CalibrateXY"
QT_MOC_LITERAL(21, 207, 14), // "MeasureRangeXY"
QT_MOC_LITERAL(22, 222, 9), // "ConnectXY"
QT_MOC_LITERAL(23, 232, 12), // "DisconnectXY"
QT_MOC_LITERAL(24, 245, 7), // "AbortXY"
QT_MOC_LITERAL(25, 253, 11), // "getCOMPORTS"
QT_MOC_LITERAL(26, 265, 14), // "connectToPortZ"
QT_MOC_LITERAL(27, 280, 14), // "AvailablePorts"
QT_MOC_LITERAL(28, 295, 11), // "excludePort"
QT_MOC_LITERAL(29, 307, 15), // "connectToPortXY"
QT_MOC_LITERAL(30, 323, 13), // "getPositionXY"
QT_MOC_LITERAL(31, 337, 5), // "isFid"
QT_MOC_LITERAL(32, 343, 12), // "getPositionZ"
QT_MOC_LITERAL(33, 356, 12), // "DisplayImage"
QT_MOC_LITERAL(34, 369, 5), // "index"
QT_MOC_LITERAL(35, 375, 10), // "saveBackup"
QT_MOC_LITERAL(36, 386, 5), // "bLoad"
QT_MOC_LITERAL(37, 392, 15), // "addFiducialMark"
QT_MOC_LITERAL(38, 408, 18), // "FIDUCIAL::position"
QT_MOC_LITERAL(39, 427, 3), // "pos"
QT_MOC_LITERAL(40, 431, 1), // "p"
QT_MOC_LITERAL(41, 433, 16), // "updateVideoImage"
QT_MOC_LITERAL(42, 450, 7), // "cv::Mat"
QT_MOC_LITERAL(43, 458, 2), // "im"
QT_MOC_LITERAL(44, 461, 17), // "startFocusThreads"
QT_MOC_LITERAL(45, 479, 22), // "addFocusValueCompleted"
QT_MOC_LITERAL(46, 502, 23), // "allFocusValuesCompleted"
QT_MOC_LITERAL(47, 526, 26), // "createTransformationMatrix"
QT_MOC_LITERAL(48, 553, 7), // "topleft"
QT_MOC_LITERAL(49, 561, 8), // "topright"
QT_MOC_LITERAL(50, 570, 10), // "bottomleft"
QT_MOC_LITERAL(51, 581, 13), // "updateQTImage"
QT_MOC_LITERAL(52, 595, 3), // "img"
QT_MOC_LITERAL(53, 599, 4), // "name"
QT_MOC_LITERAL(54, 604, 8), // "QAction*"
QT_MOC_LITERAL(55, 613, 7), // "pAction"
QT_MOC_LITERAL(56, 621, 16), // "addTargeterImage"
QT_MOC_LITERAL(57, 638, 13), // "targeterImage"
QT_MOC_LITERAL(58, 652, 3), // "tim"
QT_MOC_LITERAL(59, 656, 11), // "addMatImage"
QT_MOC_LITERAL(60, 668, 9), // "imagename"
QT_MOC_LITERAL(61, 678, 20), // "imageType::imageType"
QT_MOC_LITERAL(62, 699, 4), // "type"
QT_MOC_LITERAL(63, 704, 10), // "LOGCONSOLE"
QT_MOC_LITERAL(64, 715, 7), // "strText"
QT_MOC_LITERAL(65, 723, 7), // "newline"
QT_MOC_LITERAL(66, 731, 9), // "moveToEnd"
QT_MOC_LITERAL(67, 741, 22), // "CONSOLECOLOURS::colour"
QT_MOC_LITERAL(68, 764, 3), // "icn"
QT_MOC_LITERAL(69, 768, 22), // "StageMovementCompleted"
QT_MOC_LITERAL(70, 791, 7), // "message"
QT_MOC_LITERAL(71, 799, 15), // "receiveSettings"
QT_MOC_LITERAL(72, 815, 16), // "StageConnectedXY"
QT_MOC_LITERAL(73, 832, 4), // "port"
QT_MOC_LITERAL(74, 837, 15), // "StageConnectedZ"
QT_MOC_LITERAL(75, 853, 14), // "enableFiducial"
QT_MOC_LITERAL(76, 868, 7), // "bEnable"
QT_MOC_LITERAL(77, 876, 16), // "updatePositionXY"
QT_MOC_LITERAL(78, 893, 4), // "bFid"
QT_MOC_LITERAL(79, 898, 15), // "updatePositionZ"
QT_MOC_LITERAL(80, 914, 18), // "ProvideContextMenu"
QT_MOC_LITERAL(81, 933, 11), // "logFeedback"
QT_MOC_LITERAL(82, 945, 5), // "score"
QT_MOC_LITERAL(83, 951, 5), // "email"
QT_MOC_LITERAL(84, 957, 9), // "institute"
QT_MOC_LITERAL(85, 967, 4), // "desc"
QT_MOC_LITERAL(86, 972, 16), // "disablePanButton"
QT_MOC_LITERAL(87, 989, 19), // "unsetDrawingButtons"
QT_MOC_LITERAL(88, 1009, 4), // "pAct"
QT_MOC_LITERAL(89, 1014, 13), // "setTargetArea"
QT_MOC_LITERAL(90, 1028, 12), // "drawingShape"
QT_MOC_LITERAL(91, 1041, 5), // "shape"
QT_MOC_LITERAL(92, 1047, 16), // "StatusBarMessage"
QT_MOC_LITERAL(93, 1064, 3), // "msg"
QT_MOC_LITERAL(94, 1068, 12), // "stageMovedXY"
QT_MOC_LITERAL(95, 1081, 11), // "stageMovedZ"
QT_MOC_LITERAL(96, 1093, 13), // "addFocusValue"
QT_MOC_LITERAL(97, 1107, 13), // "focusStrength"
QT_MOC_LITERAL(98, 1121, 13), // "moveObjective"
QT_MOC_LITERAL(99, 1135, 2), // "pt"
QT_MOC_LITERAL(100, 1138, 24), // "on_action_Open_triggered"
QT_MOC_LITERAL(101, 1163, 23), // "on_action_New_triggered"
QT_MOC_LITERAL(102, 1187, 35), // "on_actionCorner_Detection_tri..."
QT_MOC_LITERAL(103, 1223, 33), // "on_actionEdge_Detection_trigg..."
QT_MOC_LITERAL(104, 1257, 31), // "on_actionGrid_Spacing_triggered"
QT_MOC_LITERAL(105, 1289, 7), // "checked"
QT_MOC_LITERAL(106, 1297, 32), // "on_action_scan_regions_triggered"
QT_MOC_LITERAL(107, 1330, 38), // "on_actionCreate_Image_Mosaic_..."
QT_MOC_LITERAL(108, 1369, 41), // "on_actionClick_Center_Objecti..."
QT_MOC_LITERAL(109, 1411, 43), // "on_actionReference_fiducial_m..."
QT_MOC_LITERAL(110, 1455, 30), // "on_actionClickTarget_triggered"
QT_MOC_LITERAL(111, 1486, 40), // "on_actionSave_Target_Position..."
QT_MOC_LITERAL(112, 1527, 29), // "on_actionMask_Black_triggered"
QT_MOC_LITERAL(113, 1557, 29), // "on_actionMask_White_triggered"
QT_MOC_LITERAL(114, 1587, 31), // "on_actionEnergy_image_triggered"
QT_MOC_LITERAL(115, 1619, 36), // "on_actionCreate_Mask_Image_tr..."
QT_MOC_LITERAL(116, 1656, 17), // "onThumbImageClick"
QT_MOC_LITERAL(117, 1674, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(118, 1691, 4), // "item"
QT_MOC_LITERAL(119, 1696, 36), // "on_actionProcessFocusStack_tr..."
QT_MOC_LITERAL(120, 1733, 24), // "on_action_Save_triggered"
QT_MOC_LITERAL(121, 1758, 29), // "on_actionSelect_All_triggered"
QT_MOC_LITERAL(122, 1788, 31), // "on_actionDeselect_All_triggered"
QT_MOC_LITERAL(123, 1820, 41), // "on_actionGrab_Image_From_Came..."
QT_MOC_LITERAL(124, 1862, 41), // "on_actionGrab_Video_From_Came..."
QT_MOC_LITERAL(125, 1904, 27), // "on_actionZoom_Out_triggered"
QT_MOC_LITERAL(126, 1932, 26), // "on_actionZoom_In_triggered"
QT_MOC_LITERAL(127, 1959, 31), // "on_actionDetect_lines_triggered"
QT_MOC_LITERAL(128, 1991, 31), // "on_actionRead_Barcode_triggered"
QT_MOC_LITERAL(129, 2023, 46), // "on_actionSample_White_Binary_..."
QT_MOC_LITERAL(130, 2070, 36), // "on_actionRemoveBlackPixels_tr..."
QT_MOC_LITERAL(131, 2107, 32), // "on_actionEntropyFilter_triggered"
QT_MOC_LITERAL(132, 2140, 31), // "on_actionDraw_Polygon_triggered"
QT_MOC_LITERAL(133, 2172, 37), // "on_actionDraw_Circle_Region_t..."
QT_MOC_LITERAL(134, 2210, 42), // "on_actionDraw_Rectangular_Reg..."
QT_MOC_LITERAL(135, 2253, 32), // "on_actionSelect_Object_triggered"
QT_MOC_LITERAL(136, 2286, 30), // "on_action_Move_Image_triggered"
QT_MOC_LITERAL(137, 2317, 14), // "openRecentFile"
QT_MOC_LITERAL(138, 2332, 42), // "on_actionGet_Target_image_reg..."
QT_MOC_LITERAL(139, 2375, 44), // "on_actionSet_as_find_targets_..."
QT_MOC_LITERAL(140, 2420, 32), // "on_actionSet_as_Target_triggered"
QT_MOC_LITERAL(141, 2453, 31), // "on_actionDeleteObject_triggered"
QT_MOC_LITERAL(142, 2485, 31), // "on_actionFind_targets_triggered"
QT_MOC_LITERAL(143, 2517, 29), // "on_actionScoreImage_triggered"
QT_MOC_LITERAL(144, 2547, 30), // "on_actionDeleteImage_triggered"
QT_MOC_LITERAL(145, 2578, 27), // "on_actionSettings_triggered"
QT_MOC_LITERAL(146, 2606, 30), // "on_actionMergeImages_triggered"
QT_MOC_LITERAL(147, 2637, 33), // "on_actionThresholdImage_trigg..."
QT_MOC_LITERAL(148, 2671, 39), // "on_actionConnected_Components..."
QT_MOC_LITERAL(149, 2711, 40), // "on_actionFilter_Binary_Object..."
QT_MOC_LITERAL(150, 2752, 31), // "on_actionFind_Centers_triggered"
QT_MOC_LITERAL(151, 2784, 25), // "on_actionInvert_triggered"
QT_MOC_LITERAL(152, 2810, 35), // "on_actionCalibrate_Camera_tri..."
QT_MOC_LITERAL(153, 2846, 31), // "on_actionCorrectImage_triggered"
QT_MOC_LITERAL(154, 2878, 33), // "on_actionBackground_fit_trigg..."
QT_MOC_LITERAL(155, 2912, 33) // "on_actionEqualise_Image_trigg..."

    },
    "MainWindow\0getVideo\0\0cameraType::camera\0"
    "assignPorts\0reportCOMPORTS\0QVector<QString>\0"
    "str\0MoveAbsoluteXY\0x\0y\0ACTIONS::action\0"
    "act\0MoveRelativeXY\0MoveAbsoluteZ\0z\0"
    "SendCommandXY\0cmd\0SetVelocityXY\0velo\0"
    "CalibrateXY\0MeasureRangeXY\0ConnectXY\0"
    "DisconnectXY\0AbortXY\0getCOMPORTS\0"
    "connectToPortZ\0AvailablePorts\0excludePort\0"
    "connectToPortXY\0getPositionXY\0isFid\0"
    "getPositionZ\0DisplayImage\0index\0"
    "saveBackup\0bLoad\0addFiducialMark\0"
    "FIDUCIAL::position\0pos\0p\0updateVideoImage\0"
    "cv::Mat\0im\0startFocusThreads\0"
    "addFocusValueCompleted\0allFocusValuesCompleted\0"
    "createTransformationMatrix\0topleft\0"
    "topright\0bottomleft\0updateQTImage\0img\0"
    "name\0QAction*\0pAction\0addTargeterImage\0"
    "targeterImage\0tim\0addMatImage\0imagename\0"
    "imageType::imageType\0type\0LOGCONSOLE\0"
    "strText\0newline\0moveToEnd\0"
    "CONSOLECOLOURS::colour\0icn\0"
    "StageMovementCompleted\0message\0"
    "receiveSettings\0StageConnectedXY\0port\0"
    "StageConnectedZ\0enableFiducial\0bEnable\0"
    "updatePositionXY\0bFid\0updatePositionZ\0"
    "ProvideContextMenu\0logFeedback\0score\0"
    "email\0institute\0desc\0disablePanButton\0"
    "unsetDrawingButtons\0pAct\0setTargetArea\0"
    "drawingShape\0shape\0StatusBarMessage\0"
    "msg\0stageMovedXY\0stageMovedZ\0addFocusValue\0"
    "focusStrength\0moveObjective\0pt\0"
    "on_action_Open_triggered\0"
    "on_action_New_triggered\0"
    "on_actionCorner_Detection_triggered\0"
    "on_actionEdge_Detection_triggered\0"
    "on_actionGrid_Spacing_triggered\0checked\0"
    "on_action_scan_regions_triggered\0"
    "on_actionCreate_Image_Mosaic_triggered\0"
    "on_actionClick_Center_Objective_triggered\0"
    "on_actionReference_fiducial_marks_triggered\0"
    "on_actionClickTarget_triggered\0"
    "on_actionSave_Target_Positions_triggered\0"
    "on_actionMask_Black_triggered\0"
    "on_actionMask_White_triggered\0"
    "on_actionEnergy_image_triggered\0"
    "on_actionCreate_Mask_Image_triggered\0"
    "onThumbImageClick\0QListWidgetItem*\0"
    "item\0on_actionProcessFocusStack_triggered\0"
    "on_action_Save_triggered\0"
    "on_actionSelect_All_triggered\0"
    "on_actionDeselect_All_triggered\0"
    "on_actionGrab_Image_From_Camera_triggered\0"
    "on_actionGrab_Video_From_Camera_triggered\0"
    "on_actionZoom_Out_triggered\0"
    "on_actionZoom_In_triggered\0"
    "on_actionDetect_lines_triggered\0"
    "on_actionRead_Barcode_triggered\0"
    "on_actionSample_White_Binary_Regions_triggered\0"
    "on_actionRemoveBlackPixels_triggered\0"
    "on_actionEntropyFilter_triggered\0"
    "on_actionDraw_Polygon_triggered\0"
    "on_actionDraw_Circle_Region_triggered\0"
    "on_actionDraw_Rectangular_Region_triggered\0"
    "on_actionSelect_Object_triggered\0"
    "on_action_Move_Image_triggered\0"
    "openRecentFile\0"
    "on_actionGet_Target_image_region_triggered\0"
    "on_actionSet_as_find_targets_image_triggered\0"
    "on_actionSet_as_Target_triggered\0"
    "on_actionDeleteObject_triggered\0"
    "on_actionFind_targets_triggered\0"
    "on_actionScoreImage_triggered\0"
    "on_actionDeleteImage_triggered\0"
    "on_actionSettings_triggered\0"
    "on_actionMergeImages_triggered\0"
    "on_actionThresholdImage_triggered\0"
    "on_actionConnected_Components_triggered\0"
    "on_actionFilter_Binary_Objects_triggered\0"
    "on_actionFind_Centers_triggered\0"
    "on_actionInvert_triggered\0"
    "on_actionCalibrate_Camera_triggered\0"
    "on_actionCorrectImage_triggered\0"
    "on_actionBackground_fit_triggered\0"
    "on_actionEqualise_Image_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
     109,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      18,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  559,    2, 0x06 /* Public */,
       4,    0,  562,    2, 0x06 /* Public */,
       5,    1,  563,    2, 0x06 /* Public */,
       8,    3,  566,    2, 0x06 /* Public */,
      13,    3,  573,    2, 0x06 /* Public */,
      14,    2,  580,    2, 0x06 /* Public */,
      16,    1,  585,    2, 0x06 /* Public */,
      18,    1,  588,    2, 0x06 /* Public */,
      20,    0,  591,    2, 0x06 /* Public */,
      21,    0,  592,    2, 0x06 /* Public */,
      22,    0,  593,    2, 0x06 /* Public */,
      23,    0,  594,    2, 0x06 /* Public */,
      24,    0,  595,    2, 0x06 /* Public */,
      25,    0,  596,    2, 0x06 /* Public */,
      26,    2,  597,    2, 0x06 /* Public */,
      29,    2,  602,    2, 0x06 /* Public */,
      30,    1,  607,    2, 0x06 /* Public */,
      32,    1,  610,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      33,    0,  613,    2, 0x0a /* Public */,
      33,    1,  614,    2, 0x0a /* Public */,
      35,    1,  617,    2, 0x0a /* Public */,
      37,    2,  620,    2, 0x0a /* Public */,
      41,    1,  625,    2, 0x0a /* Public */,
      44,    3,  628,    2, 0x0a /* Public */,
      45,    0,  635,    2, 0x0a /* Public */,
      46,    0,  636,    2, 0x0a /* Public */,
      47,    3,  637,    2, 0x0a /* Public */,
      51,    3,  644,    2, 0x0a /* Public */,
      51,    2,  651,    2, 0x2a /* Public | MethodCloned */,
      51,    1,  656,    2, 0x2a /* Public | MethodCloned */,
      56,    2,  659,    2, 0x0a /* Public */,
      56,    1,  664,    2, 0x2a /* Public | MethodCloned */,
      59,    4,  667,    2, 0x0a /* Public */,
      63,    4,  676,    2, 0x0a /* Public */,
      63,    3,  685,    2, 0x2a /* Public | MethodCloned */,
      63,    2,  692,    2, 0x0a /* Public */,
      63,    1,  697,    2, 0x2a /* Public | MethodCloned */,
      63,    2,  700,    2, 0x0a /* Public */,
      63,    1,  705,    2, 0x2a /* Public | MethodCloned */,
      69,    1,  708,    2, 0x0a /* Public */,
      71,    0,  711,    2, 0x0a /* Public */,
      72,    1,  712,    2, 0x0a /* Public */,
      74,    1,  715,    2, 0x0a /* Public */,
      75,    1,  718,    2, 0x0a /* Public */,
      77,    3,  721,    2, 0x08 /* Private */,
      79,    2,  728,    2, 0x08 /* Private */,
      80,    1,  733,    2, 0x08 /* Private */,
      81,    5,  736,    2, 0x08 /* Private */,
      86,    0,  747,    2, 0x08 /* Private */,
      87,    1,  748,    2, 0x08 /* Private */,
      89,    1,  751,    2, 0x08 /* Private */,
      92,    1,  754,    2, 0x08 /* Private */,
      94,    3,  757,    2, 0x08 /* Private */,
      95,    2,  764,    2, 0x08 /* Private */,
      96,    4,  769,    2, 0x08 /* Private */,
      98,    1,  778,    2, 0x08 /* Private */,
     100,    0,  781,    2, 0x08 /* Private */,
     101,    0,  782,    2, 0x08 /* Private */,
     102,    0,  783,    2, 0x08 /* Private */,
     103,    0,  784,    2, 0x08 /* Private */,
     104,    1,  785,    2, 0x08 /* Private */,
     106,    0,  788,    2, 0x08 /* Private */,
     107,    0,  789,    2, 0x08 /* Private */,
     108,    1,  790,    2, 0x08 /* Private */,
     109,    1,  793,    2, 0x08 /* Private */,
     110,    1,  796,    2, 0x08 /* Private */,
     111,    0,  799,    2, 0x08 /* Private */,
     112,    0,  800,    2, 0x08 /* Private */,
     113,    0,  801,    2, 0x08 /* Private */,
     114,    0,  802,    2, 0x08 /* Private */,
     115,    0,  803,    2, 0x08 /* Private */,
     116,    1,  804,    2, 0x08 /* Private */,
     119,    0,  807,    2, 0x08 /* Private */,
     120,    0,  808,    2, 0x08 /* Private */,
     121,    0,  809,    2, 0x08 /* Private */,
     122,    0,  810,    2, 0x08 /* Private */,
     123,    0,  811,    2, 0x08 /* Private */,
     124,    1,  812,    2, 0x08 /* Private */,
     125,    0,  815,    2, 0x08 /* Private */,
     126,    0,  816,    2, 0x08 /* Private */,
     127,    0,  817,    2, 0x08 /* Private */,
     128,    0,  818,    2, 0x08 /* Private */,
     129,    0,  819,    2, 0x08 /* Private */,
     130,    0,  820,    2, 0x08 /* Private */,
     131,    0,  821,    2, 0x08 /* Private */,
     132,    0,  822,    2, 0x08 /* Private */,
     133,    0,  823,    2, 0x08 /* Private */,
     134,    0,  824,    2, 0x08 /* Private */,
     135,    0,  825,    2, 0x08 /* Private */,
     136,    0,  826,    2, 0x08 /* Private */,
     137,    0,  827,    2, 0x08 /* Private */,
     138,    0,  828,    2, 0x08 /* Private */,
     139,    0,  829,    2, 0x08 /* Private */,
     140,    0,  830,    2, 0x08 /* Private */,
     141,    0,  831,    2, 0x08 /* Private */,
     142,    0,  832,    2, 0x08 /* Private */,
     143,    0,  833,    2, 0x08 /* Private */,
     144,    0,  834,    2, 0x08 /* Private */,
     145,    0,  835,    2, 0x08 /* Private */,
     146,    0,  836,    2, 0x08 /* Private */,
     147,    0,  837,    2, 0x08 /* Private */,
     148,    0,  838,    2, 0x08 /* Private */,
     149,    0,  839,    2, 0x08 /* Private */,
     150,    0,  840,    2, 0x08 /* Private */,
     151,    0,  841,    2, 0x08 /* Private */,
     152,    0,  842,    2, 0x08 /* Private */,
     153,    0,  843,    2, 0x08 /* Private */,
     154,    0,  844,    2, 0x08 /* Private */,
     155,    0,  845,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, 0x80000000 | 11,    9,   10,   12,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, 0x80000000 | 11,    9,   10,   12,
    QMetaType::Void, QMetaType::Double, 0x80000000 | 11,   15,   12,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void, QMetaType::Double,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6, QMetaType::QString,   27,   28,
    QMetaType::Void, 0x80000000 | 6, QMetaType::QString,   27,   28,
    QMetaType::Void, QMetaType::Bool,   31,
    QMetaType::Void, QMetaType::Bool,   31,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   34,
    QMetaType::Void, QMetaType::Bool,   36,
    QMetaType::Void, 0x80000000 | 38, QMetaType::QPoint,   39,   40,
    QMetaType::Void, 0x80000000 | 42,   43,
    QMetaType::Void, 0x80000000 | 42, QMetaType::Double, 0x80000000 | 11,   43,   15,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QVector3D, QMetaType::QVector3D, QMetaType::QVector3D,   48,   49,   50,
    QMetaType::Bool, 0x80000000 | 42, QMetaType::QString, 0x80000000 | 54,   52,   53,   55,
    QMetaType::Bool, 0x80000000 | 42, QMetaType::QString,   52,   53,
    QMetaType::Bool, 0x80000000 | 42,   52,
    QMetaType::Void, 0x80000000 | 57, 0x80000000 | 54,   58,   55,
    QMetaType::Void, 0x80000000 | 57,   58,
    QMetaType::Void, 0x80000000 | 42, QMetaType::QString, 0x80000000 | 61, 0x80000000 | 54,   52,   60,   62,   55,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, 0x80000000 | 67,   64,   65,   66,   68,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool,   64,   65,   66,
    QMetaType::Void, 0x80000000 | 61, 0x80000000 | 67,   62,   68,
    QMetaType::Void, 0x80000000 | 61,   62,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 67,   64,   68,
    QMetaType::Void, QMetaType::QString,   64,
    QMetaType::Void, QMetaType::QString,   70,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   73,
    QMetaType::Void, QMetaType::QString,   73,
    QMetaType::Void, QMetaType::Bool,   76,
    QMetaType::Void, QMetaType::Bool, QMetaType::Double, QMetaType::Double,   78,    9,   10,
    QMetaType::Void, QMetaType::Bool, QMetaType::Double,   78,   15,
    QMetaType::Void, QMetaType::QPoint,   39,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   82,   53,   83,   84,   85,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 54,   88,
    QMetaType::Void, 0x80000000 | 90,   91,
    QMetaType::Void, QMetaType::QString,   93,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, 0x80000000 | 11,    9,   10,   12,
    QMetaType::Void, QMetaType::Double, 0x80000000 | 11,   15,   12,
    QMetaType::Void, 0x80000000 | 42, QMetaType::Double, QMetaType::Double, 0x80000000 | 11,   43,   15,   97,   12,
    QMetaType::Void, QMetaType::QPoint,   99,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,  105,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,  105,
    QMetaType::Void, QMetaType::Bool,  105,
    QMetaType::Void, QMetaType::Bool,  105,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 117,  118,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,  105,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->getVideo((*reinterpret_cast< cameraType::camera(*)>(_a[1]))); break;
        case 1: _t->assignPorts(); break;
        case 2: _t->reportCOMPORTS((*reinterpret_cast< QVector<QString>(*)>(_a[1]))); break;
        case 3: _t->MoveAbsoluteXY((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< ACTIONS::action(*)>(_a[3]))); break;
        case 4: _t->MoveRelativeXY((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< ACTIONS::action(*)>(_a[3]))); break;
        case 5: _t->MoveAbsoluteZ((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< ACTIONS::action(*)>(_a[2]))); break;
        case 6: _t->SendCommandXY((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->SetVelocityXY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->CalibrateXY(); break;
        case 9: _t->MeasureRangeXY(); break;
        case 10: _t->ConnectXY(); break;
        case 11: _t->DisconnectXY(); break;
        case 12: _t->AbortXY(); break;
        case 13: _t->getCOMPORTS(); break;
        case 14: _t->connectToPortZ((*reinterpret_cast< QVector<QString>(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 15: _t->connectToPortXY((*reinterpret_cast< QVector<QString>(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 16: _t->getPositionXY((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: _t->getPositionZ((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->DisplayImage(); break;
        case 19: _t->DisplayImage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->saveBackup((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: _t->addFiducialMark((*reinterpret_cast< FIDUCIAL::position(*)>(_a[1])),(*reinterpret_cast< QPoint(*)>(_a[2]))); break;
        case 22: _t->updateVideoImage((*reinterpret_cast< cv::Mat(*)>(_a[1]))); break;
        case 23: _t->startFocusThreads((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< ACTIONS::action(*)>(_a[3]))); break;
        case 24: _t->addFocusValueCompleted(); break;
        case 25: _t->allFocusValuesCompleted(); break;
        case 26: _t->createTransformationMatrix((*reinterpret_cast< QVector3D(*)>(_a[1])),(*reinterpret_cast< QVector3D(*)>(_a[2])),(*reinterpret_cast< QVector3D(*)>(_a[3]))); break;
        case 27: { bool _r = _t->updateQTImage((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QAction*(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 28: { bool _r = _t->updateQTImage((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 29: { bool _r = _t->updateQTImage((*reinterpret_cast< cv::Mat(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 30: _t->addTargeterImage((*reinterpret_cast< targeterImage(*)>(_a[1])),(*reinterpret_cast< QAction*(*)>(_a[2]))); break;
        case 31: _t->addTargeterImage((*reinterpret_cast< targeterImage(*)>(_a[1]))); break;
        case 32: _t->addMatImage((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< imageType::imageType(*)>(_a[3])),(*reinterpret_cast< QAction*(*)>(_a[4]))); break;
        case 33: _t->LOGCONSOLE((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< CONSOLECOLOURS::colour(*)>(_a[4]))); break;
        case 34: _t->LOGCONSOLE((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 35: _t->LOGCONSOLE((*reinterpret_cast< imageType::imageType(*)>(_a[1])),(*reinterpret_cast< CONSOLECOLOURS::colour(*)>(_a[2]))); break;
        case 36: _t->LOGCONSOLE((*reinterpret_cast< imageType::imageType(*)>(_a[1]))); break;
        case 37: _t->LOGCONSOLE((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< CONSOLECOLOURS::colour(*)>(_a[2]))); break;
        case 38: _t->LOGCONSOLE((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 39: _t->StageMovementCompleted((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 40: _t->receiveSettings(); break;
        case 41: _t->StageConnectedXY((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 42: _t->StageConnectedZ((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 43: _t->enableFiducial((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 44: _t->updatePositionXY((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 45: _t->updatePositionZ((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 46: _t->ProvideContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 47: _t->logFeedback((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 48: _t->disablePanButton(); break;
        case 49: _t->unsetDrawingButtons((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 50: _t->setTargetArea((*reinterpret_cast< drawingShape(*)>(_a[1]))); break;
        case 51: _t->StatusBarMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 52: _t->stageMovedXY((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< ACTIONS::action(*)>(_a[3]))); break;
        case 53: _t->stageMovedZ((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< ACTIONS::action(*)>(_a[2]))); break;
        case 54: _t->addFocusValue((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< ACTIONS::action(*)>(_a[4]))); break;
        case 55: _t->moveObjective((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 56: _t->on_action_Open_triggered(); break;
        case 57: _t->on_action_New_triggered(); break;
        case 58: _t->on_actionCorner_Detection_triggered(); break;
        case 59: _t->on_actionEdge_Detection_triggered(); break;
        case 60: _t->on_actionGrid_Spacing_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 61: _t->on_action_scan_regions_triggered(); break;
        case 62: _t->on_actionCreate_Image_Mosaic_triggered(); break;
        case 63: _t->on_actionClick_Center_Objective_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 64: _t->on_actionReference_fiducial_marks_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 65: _t->on_actionClickTarget_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 66: _t->on_actionSave_Target_Positions_triggered(); break;
        case 67: _t->on_actionMask_Black_triggered(); break;
        case 68: _t->on_actionMask_White_triggered(); break;
        case 69: _t->on_actionEnergy_image_triggered(); break;
        case 70: _t->on_actionCreate_Mask_Image_triggered(); break;
        case 71: _t->onThumbImageClick((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 72: _t->on_actionProcessFocusStack_triggered(); break;
        case 73: _t->on_action_Save_triggered(); break;
        case 74: _t->on_actionSelect_All_triggered(); break;
        case 75: _t->on_actionDeselect_All_triggered(); break;
        case 76: _t->on_actionGrab_Image_From_Camera_triggered(); break;
        case 77: _t->on_actionGrab_Video_From_Camera_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 78: _t->on_actionZoom_Out_triggered(); break;
        case 79: _t->on_actionZoom_In_triggered(); break;
        case 80: _t->on_actionDetect_lines_triggered(); break;
        case 81: _t->on_actionRead_Barcode_triggered(); break;
        case 82: _t->on_actionSample_White_Binary_Regions_triggered(); break;
        case 83: _t->on_actionRemoveBlackPixels_triggered(); break;
        case 84: _t->on_actionEntropyFilter_triggered(); break;
        case 85: _t->on_actionDraw_Polygon_triggered(); break;
        case 86: _t->on_actionDraw_Circle_Region_triggered(); break;
        case 87: _t->on_actionDraw_Rectangular_Region_triggered(); break;
        case 88: _t->on_actionSelect_Object_triggered(); break;
        case 89: _t->on_action_Move_Image_triggered(); break;
        case 90: _t->openRecentFile(); break;
        case 91: _t->on_actionGet_Target_image_region_triggered(); break;
        case 92: _t->on_actionSet_as_find_targets_image_triggered(); break;
        case 93: _t->on_actionSet_as_Target_triggered(); break;
        case 94: _t->on_actionDeleteObject_triggered(); break;
        case 95: _t->on_actionFind_targets_triggered(); break;
        case 96: _t->on_actionScoreImage_triggered(); break;
        case 97: _t->on_actionDeleteImage_triggered(); break;
        case 98: _t->on_actionSettings_triggered(); break;
        case 99: _t->on_actionMergeImages_triggered(); break;
        case 100: _t->on_actionThresholdImage_triggered(); break;
        case 101: _t->on_actionConnected_Components_triggered(); break;
        case 102: _t->on_actionFilter_Binary_Objects_triggered(); break;
        case 103: _t->on_actionFind_Centers_triggered(); break;
        case 104: _t->on_actionInvert_triggered(); break;
        case 105: _t->on_actionCalibrate_Camera_triggered(); break;
        case 106: _t->on_actionCorrectImage_triggered(); break;
        case 107: _t->on_actionBackground_fit_triggered(); break;
        case 108: _t->on_actionEqualise_Image_triggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QString> >(); break;
            }
            break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QString> >(); break;
            }
            break;
        case 15:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QString> >(); break;
            }
            break;
        case 27:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 30:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 32:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 3:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 49:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(cameraType::camera );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::getVideo)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::assignPorts)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(QVector<QString> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::reportCOMPORTS)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(double , double , ACTIONS::action );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::MoveAbsoluteXY)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(double , double , ACTIONS::action );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::MoveRelativeXY)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(double , ACTIONS::action );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::MoveAbsoluteZ)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::SendCommandXY)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::SetVelocityXY)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::CalibrateXY)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::MeasureRangeXY)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::ConnectXY)) {
                *result = 10;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::DisconnectXY)) {
                *result = 11;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::AbortXY)) {
                *result = 12;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::getCOMPORTS)) {
                *result = 13;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(QVector<QString> , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::connectToPortZ)) {
                *result = 14;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(QVector<QString> , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::connectToPortXY)) {
                *result = 15;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::getPositionXY)) {
                *result = 16;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::getPositionZ)) {
                *result = 17;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 109)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 109;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 109)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 109;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::getVideo(cameraType::camera _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::assignPorts()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void MainWindow::reportCOMPORTS(QVector<QString> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainWindow::MoveAbsoluteXY(double _t1, double _t2, ACTIONS::action _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MainWindow::MoveRelativeXY(double _t1, double _t2, ACTIONS::action _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MainWindow::MoveAbsoluteZ(double _t1, ACTIONS::action _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MainWindow::SendCommandXY(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MainWindow::SetVelocityXY(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void MainWindow::CalibrateXY()
{
    QMetaObject::activate(this, &staticMetaObject, 8, Q_NULLPTR);
}

// SIGNAL 9
void MainWindow::MeasureRangeXY()
{
    QMetaObject::activate(this, &staticMetaObject, 9, Q_NULLPTR);
}

// SIGNAL 10
void MainWindow::ConnectXY()
{
    QMetaObject::activate(this, &staticMetaObject, 10, Q_NULLPTR);
}

// SIGNAL 11
void MainWindow::DisconnectXY()
{
    QMetaObject::activate(this, &staticMetaObject, 11, Q_NULLPTR);
}

// SIGNAL 12
void MainWindow::AbortXY()
{
    QMetaObject::activate(this, &staticMetaObject, 12, Q_NULLPTR);
}

// SIGNAL 13
void MainWindow::getCOMPORTS()
{
    QMetaObject::activate(this, &staticMetaObject, 13, Q_NULLPTR);
}

// SIGNAL 14
void MainWindow::connectToPortZ(QVector<QString> _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void MainWindow::connectToPortXY(QVector<QString> _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void MainWindow::getPositionXY(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void MainWindow::getPositionZ(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}
QT_END_MOC_NAMESPACE
