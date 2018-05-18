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
    QByteArrayData data[160];
    char stringdata0[2966];
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
QT_MOC_LITERAL(44, 461, 26), // "createTransformationMatrix"
QT_MOC_LITERAL(45, 488, 7), // "topleft"
QT_MOC_LITERAL(46, 496, 8), // "topright"
QT_MOC_LITERAL(47, 505, 10), // "bottomleft"
QT_MOC_LITERAL(48, 516, 13), // "updateQTImage"
QT_MOC_LITERAL(49, 530, 3), // "img"
QT_MOC_LITERAL(50, 534, 4), // "name"
QT_MOC_LITERAL(51, 539, 8), // "QAction*"
QT_MOC_LITERAL(52, 548, 7), // "pAction"
QT_MOC_LITERAL(53, 556, 16), // "addTargeterImage"
QT_MOC_LITERAL(54, 573, 13), // "targeterImage"
QT_MOC_LITERAL(55, 587, 3), // "tim"
QT_MOC_LITERAL(56, 591, 11), // "addMatImage"
QT_MOC_LITERAL(57, 603, 9), // "imagename"
QT_MOC_LITERAL(58, 613, 20), // "imageType::imageType"
QT_MOC_LITERAL(59, 634, 4), // "type"
QT_MOC_LITERAL(60, 639, 10), // "LOGCONSOLE"
QT_MOC_LITERAL(61, 650, 7), // "strText"
QT_MOC_LITERAL(62, 658, 7), // "newline"
QT_MOC_LITERAL(63, 666, 9), // "moveToEnd"
QT_MOC_LITERAL(64, 676, 22), // "CONSOLECOLOURS::colour"
QT_MOC_LITERAL(65, 699, 3), // "icn"
QT_MOC_LITERAL(66, 703, 22), // "StageMovementCompleted"
QT_MOC_LITERAL(67, 726, 7), // "message"
QT_MOC_LITERAL(68, 734, 15), // "receiveSettings"
QT_MOC_LITERAL(69, 750, 16), // "StageConnectedXY"
QT_MOC_LITERAL(70, 767, 4), // "port"
QT_MOC_LITERAL(71, 772, 15), // "StageConnectedZ"
QT_MOC_LITERAL(72, 788, 14), // "enableFiducial"
QT_MOC_LITERAL(73, 803, 7), // "bEnable"
QT_MOC_LITERAL(74, 811, 12), // "getBestFocus"
QT_MOC_LITERAL(75, 824, 6), // "minPos"
QT_MOC_LITERAL(76, 831, 4), // "step"
QT_MOC_LITERAL(77, 836, 17), // "getBestFocusValue"
QT_MOC_LITERAL(78, 854, 19), // "QMap<double,double>"
QT_MOC_LITERAL(79, 874, 11), // "focusValues"
QT_MOC_LITERAL(80, 886, 9), // "arraySize"
QT_MOC_LITERAL(81, 896, 16), // "updatePositionXY"
QT_MOC_LITERAL(82, 913, 4), // "bFid"
QT_MOC_LITERAL(83, 918, 15), // "updatePositionZ"
QT_MOC_LITERAL(84, 934, 18), // "ProvideContextMenu"
QT_MOC_LITERAL(85, 953, 11), // "logFeedback"
QT_MOC_LITERAL(86, 965, 5), // "score"
QT_MOC_LITERAL(87, 971, 5), // "email"
QT_MOC_LITERAL(88, 977, 9), // "institute"
QT_MOC_LITERAL(89, 987, 4), // "desc"
QT_MOC_LITERAL(90, 992, 16), // "disablePanButton"
QT_MOC_LITERAL(91, 1009, 19), // "unsetDrawingButtons"
QT_MOC_LITERAL(92, 1029, 4), // "pAct"
QT_MOC_LITERAL(93, 1034, 13), // "setTargetArea"
QT_MOC_LITERAL(94, 1048, 12), // "drawingShape"
QT_MOC_LITERAL(95, 1061, 5), // "shape"
QT_MOC_LITERAL(96, 1067, 16), // "StatusBarMessage"
QT_MOC_LITERAL(97, 1084, 3), // "msg"
QT_MOC_LITERAL(98, 1088, 12), // "stageMovedXY"
QT_MOC_LITERAL(99, 1101, 11), // "stageMovedZ"
QT_MOC_LITERAL(100, 1113, 13), // "addFocusValue"
QT_MOC_LITERAL(101, 1127, 13), // "focusStrength"
QT_MOC_LITERAL(102, 1141, 13), // "moveObjective"
QT_MOC_LITERAL(103, 1155, 2), // "pt"
QT_MOC_LITERAL(104, 1158, 24), // "on_action_Open_triggered"
QT_MOC_LITERAL(105, 1183, 23), // "on_action_New_triggered"
QT_MOC_LITERAL(106, 1207, 35), // "on_actionCorner_Detection_tri..."
QT_MOC_LITERAL(107, 1243, 33), // "on_actionEdge_Detection_trigg..."
QT_MOC_LITERAL(108, 1277, 31), // "on_actionGrid_Spacing_triggered"
QT_MOC_LITERAL(109, 1309, 7), // "checked"
QT_MOC_LITERAL(110, 1317, 32), // "on_action_scan_regions_triggered"
QT_MOC_LITERAL(111, 1350, 38), // "on_actionCreate_Image_Mosaic_..."
QT_MOC_LITERAL(112, 1389, 41), // "on_actionClick_Center_Objecti..."
QT_MOC_LITERAL(113, 1431, 43), // "on_actionReference_fiducial_m..."
QT_MOC_LITERAL(114, 1475, 30), // "on_actionClickTarget_triggered"
QT_MOC_LITERAL(115, 1506, 40), // "on_actionSave_Target_Position..."
QT_MOC_LITERAL(116, 1547, 29), // "on_actionMask_Black_triggered"
QT_MOC_LITERAL(117, 1577, 29), // "on_actionMask_White_triggered"
QT_MOC_LITERAL(118, 1607, 31), // "on_actionEnergy_image_triggered"
QT_MOC_LITERAL(119, 1639, 36), // "on_actionCreate_Mask_Image_tr..."
QT_MOC_LITERAL(120, 1676, 17), // "onThumbImageClick"
QT_MOC_LITERAL(121, 1694, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(122, 1711, 4), // "item"
QT_MOC_LITERAL(123, 1716, 36), // "on_actionProcessFocusStack_tr..."
QT_MOC_LITERAL(124, 1753, 24), // "on_action_Save_triggered"
QT_MOC_LITERAL(125, 1778, 29), // "on_actionSelect_All_triggered"
QT_MOC_LITERAL(126, 1808, 31), // "on_actionDeselect_All_triggered"
QT_MOC_LITERAL(127, 1840, 41), // "on_actionGrab_Image_From_Came..."
QT_MOC_LITERAL(128, 1882, 41), // "on_actionGrab_Video_From_Came..."
QT_MOC_LITERAL(129, 1924, 27), // "on_actionZoom_Out_triggered"
QT_MOC_LITERAL(130, 1952, 26), // "on_actionZoom_In_triggered"
QT_MOC_LITERAL(131, 1979, 31), // "on_actionDetect_lines_triggered"
QT_MOC_LITERAL(132, 2011, 31), // "on_actionRead_Barcode_triggered"
QT_MOC_LITERAL(133, 2043, 46), // "on_actionSample_White_Binary_..."
QT_MOC_LITERAL(134, 2090, 36), // "on_actionRemoveBlackPixels_tr..."
QT_MOC_LITERAL(135, 2127, 32), // "on_actionEntropyFilter_triggered"
QT_MOC_LITERAL(136, 2160, 31), // "on_actionDraw_Polygon_triggered"
QT_MOC_LITERAL(137, 2192, 37), // "on_actionDraw_Circle_Region_t..."
QT_MOC_LITERAL(138, 2230, 42), // "on_actionDraw_Rectangular_Reg..."
QT_MOC_LITERAL(139, 2273, 32), // "on_actionSelect_Object_triggered"
QT_MOC_LITERAL(140, 2306, 30), // "on_action_Move_Image_triggered"
QT_MOC_LITERAL(141, 2337, 14), // "openRecentFile"
QT_MOC_LITERAL(142, 2352, 42), // "on_actionGet_Target_image_reg..."
QT_MOC_LITERAL(143, 2395, 44), // "on_actionSet_as_find_targets_..."
QT_MOC_LITERAL(144, 2440, 32), // "on_actionSet_as_Target_triggered"
QT_MOC_LITERAL(145, 2473, 31), // "on_actionDeleteObject_triggered"
QT_MOC_LITERAL(146, 2505, 31), // "on_actionFind_targets_triggered"
QT_MOC_LITERAL(147, 2537, 29), // "on_actionScoreImage_triggered"
QT_MOC_LITERAL(148, 2567, 30), // "on_actionDeleteImage_triggered"
QT_MOC_LITERAL(149, 2598, 27), // "on_actionSettings_triggered"
QT_MOC_LITERAL(150, 2626, 30), // "on_actionMergeImages_triggered"
QT_MOC_LITERAL(151, 2657, 33), // "on_actionThresholdImage_trigg..."
QT_MOC_LITERAL(152, 2691, 39), // "on_actionConnected_Components..."
QT_MOC_LITERAL(153, 2731, 40), // "on_actionFilter_Binary_Object..."
QT_MOC_LITERAL(154, 2772, 31), // "on_actionFind_Centers_triggered"
QT_MOC_LITERAL(155, 2804, 25), // "on_actionInvert_triggered"
QT_MOC_LITERAL(156, 2830, 35), // "on_actionCalibrate_Camera_tri..."
QT_MOC_LITERAL(157, 2866, 31), // "on_actionCorrectImage_triggered"
QT_MOC_LITERAL(158, 2898, 33), // "on_actionBackground_fit_trigg..."
QT_MOC_LITERAL(159, 2932, 33) // "on_actionEqualise_Image_trigg..."

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
    "cv::Mat\0im\0createTransformationMatrix\0"
    "topleft\0topright\0bottomleft\0updateQTImage\0"
    "img\0name\0QAction*\0pAction\0addTargeterImage\0"
    "targeterImage\0tim\0addMatImage\0imagename\0"
    "imageType::imageType\0type\0LOGCONSOLE\0"
    "strText\0newline\0moveToEnd\0"
    "CONSOLECOLOURS::colour\0icn\0"
    "StageMovementCompleted\0message\0"
    "receiveSettings\0StageConnectedXY\0port\0"
    "StageConnectedZ\0enableFiducial\0bEnable\0"
    "getBestFocus\0minPos\0step\0getBestFocusValue\0"
    "QMap<double,double>\0focusValues\0"
    "arraySize\0updatePositionXY\0bFid\0"
    "updatePositionZ\0ProvideContextMenu\0"
    "logFeedback\0score\0email\0institute\0"
    "desc\0disablePanButton\0unsetDrawingButtons\0"
    "pAct\0setTargetArea\0drawingShape\0shape\0"
    "StatusBarMessage\0msg\0stageMovedXY\0"
    "stageMovedZ\0addFocusValue\0focusStrength\0"
    "moveObjective\0pt\0on_action_Open_triggered\0"
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
     108,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      18,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  554,    2, 0x06 /* Public */,
       4,    0,  557,    2, 0x06 /* Public */,
       5,    1,  558,    2, 0x06 /* Public */,
       8,    3,  561,    2, 0x06 /* Public */,
      13,    3,  568,    2, 0x06 /* Public */,
      14,    2,  575,    2, 0x06 /* Public */,
      16,    1,  580,    2, 0x06 /* Public */,
      18,    1,  583,    2, 0x06 /* Public */,
      20,    0,  586,    2, 0x06 /* Public */,
      21,    0,  587,    2, 0x06 /* Public */,
      22,    0,  588,    2, 0x06 /* Public */,
      23,    0,  589,    2, 0x06 /* Public */,
      24,    0,  590,    2, 0x06 /* Public */,
      25,    0,  591,    2, 0x06 /* Public */,
      26,    2,  592,    2, 0x06 /* Public */,
      29,    2,  597,    2, 0x06 /* Public */,
      30,    1,  602,    2, 0x06 /* Public */,
      32,    1,  605,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      33,    0,  608,    2, 0x0a /* Public */,
      33,    1,  609,    2, 0x0a /* Public */,
      35,    1,  612,    2, 0x0a /* Public */,
      37,    2,  615,    2, 0x0a /* Public */,
      41,    1,  620,    2, 0x0a /* Public */,
      44,    3,  623,    2, 0x0a /* Public */,
      48,    3,  630,    2, 0x0a /* Public */,
      48,    2,  637,    2, 0x2a /* Public | MethodCloned */,
      48,    1,  642,    2, 0x2a /* Public | MethodCloned */,
      53,    2,  645,    2, 0x0a /* Public */,
      53,    1,  650,    2, 0x2a /* Public | MethodCloned */,
      56,    4,  653,    2, 0x0a /* Public */,
      60,    4,  662,    2, 0x0a /* Public */,
      60,    3,  671,    2, 0x2a /* Public | MethodCloned */,
      60,    2,  678,    2, 0x0a /* Public */,
      60,    1,  683,    2, 0x2a /* Public | MethodCloned */,
      60,    2,  686,    2, 0x0a /* Public */,
      60,    1,  691,    2, 0x2a /* Public | MethodCloned */,
      66,    1,  694,    2, 0x0a /* Public */,
      68,    0,  697,    2, 0x0a /* Public */,
      69,    1,  698,    2, 0x0a /* Public */,
      71,    1,  701,    2, 0x0a /* Public */,
      72,    1,  704,    2, 0x0a /* Public */,
      74,    2,  707,    2, 0x0a /* Public */,
      77,    4,  712,    2, 0x0a /* Public */,
      81,    3,  721,    2, 0x08 /* Private */,
      83,    2,  728,    2, 0x08 /* Private */,
      84,    1,  733,    2, 0x08 /* Private */,
      85,    5,  736,    2, 0x08 /* Private */,
      90,    0,  747,    2, 0x08 /* Private */,
      91,    1,  748,    2, 0x08 /* Private */,
      93,    1,  751,    2, 0x08 /* Private */,
      96,    1,  754,    2, 0x08 /* Private */,
      98,    3,  757,    2, 0x08 /* Private */,
      99,    2,  764,    2, 0x08 /* Private */,
     100,    3,  769,    2, 0x08 /* Private */,
     102,    1,  776,    2, 0x08 /* Private */,
     104,    0,  779,    2, 0x08 /* Private */,
     105,    0,  780,    2, 0x08 /* Private */,
     106,    0,  781,    2, 0x08 /* Private */,
     107,    0,  782,    2, 0x08 /* Private */,
     108,    1,  783,    2, 0x08 /* Private */,
     110,    0,  786,    2, 0x08 /* Private */,
     111,    0,  787,    2, 0x08 /* Private */,
     112,    1,  788,    2, 0x08 /* Private */,
     113,    1,  791,    2, 0x08 /* Private */,
     114,    1,  794,    2, 0x08 /* Private */,
     115,    0,  797,    2, 0x08 /* Private */,
     116,    0,  798,    2, 0x08 /* Private */,
     117,    0,  799,    2, 0x08 /* Private */,
     118,    0,  800,    2, 0x08 /* Private */,
     119,    0,  801,    2, 0x08 /* Private */,
     120,    1,  802,    2, 0x08 /* Private */,
     123,    0,  805,    2, 0x08 /* Private */,
     124,    0,  806,    2, 0x08 /* Private */,
     125,    0,  807,    2, 0x08 /* Private */,
     126,    0,  808,    2, 0x08 /* Private */,
     127,    0,  809,    2, 0x08 /* Private */,
     128,    1,  810,    2, 0x08 /* Private */,
     129,    0,  813,    2, 0x08 /* Private */,
     130,    0,  814,    2, 0x08 /* Private */,
     131,    0,  815,    2, 0x08 /* Private */,
     132,    0,  816,    2, 0x08 /* Private */,
     133,    0,  817,    2, 0x08 /* Private */,
     134,    0,  818,    2, 0x08 /* Private */,
     135,    0,  819,    2, 0x08 /* Private */,
     136,    0,  820,    2, 0x08 /* Private */,
     137,    0,  821,    2, 0x08 /* Private */,
     138,    0,  822,    2, 0x08 /* Private */,
     139,    0,  823,    2, 0x08 /* Private */,
     140,    0,  824,    2, 0x08 /* Private */,
     141,    0,  825,    2, 0x08 /* Private */,
     142,    0,  826,    2, 0x08 /* Private */,
     143,    0,  827,    2, 0x08 /* Private */,
     144,    0,  828,    2, 0x08 /* Private */,
     145,    0,  829,    2, 0x08 /* Private */,
     146,    0,  830,    2, 0x08 /* Private */,
     147,    0,  831,    2, 0x08 /* Private */,
     148,    0,  832,    2, 0x08 /* Private */,
     149,    0,  833,    2, 0x08 /* Private */,
     150,    0,  834,    2, 0x08 /* Private */,
     151,    0,  835,    2, 0x08 /* Private */,
     152,    0,  836,    2, 0x08 /* Private */,
     153,    0,  837,    2, 0x08 /* Private */,
     154,    0,  838,    2, 0x08 /* Private */,
     155,    0,  839,    2, 0x08 /* Private */,
     156,    0,  840,    2, 0x08 /* Private */,
     157,    0,  841,    2, 0x08 /* Private */,
     158,    0,  842,    2, 0x08 /* Private */,
     159,    0,  843,    2, 0x08 /* Private */,

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
    QMetaType::Void, QMetaType::QVector3D, QMetaType::QVector3D, QMetaType::QVector3D,   45,   46,   47,
    QMetaType::Bool, 0x80000000 | 42, QMetaType::QString, 0x80000000 | 51,   49,   50,   52,
    QMetaType::Bool, 0x80000000 | 42, QMetaType::QString,   49,   50,
    QMetaType::Bool, 0x80000000 | 42,   49,
    QMetaType::Void, 0x80000000 | 54, 0x80000000 | 51,   55,   52,
    QMetaType::Void, 0x80000000 | 54,   55,
    QMetaType::Void, 0x80000000 | 42, QMetaType::QString, 0x80000000 | 58, 0x80000000 | 51,   49,   57,   59,   52,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, 0x80000000 | 64,   61,   62,   63,   65,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool,   61,   62,   63,
    QMetaType::Void, 0x80000000 | 58, 0x80000000 | 64,   59,   65,
    QMetaType::Void, 0x80000000 | 58,   59,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 64,   61,   65,
    QMetaType::Void, QMetaType::QString,   61,
    QMetaType::Void, QMetaType::QString,   67,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   70,
    QMetaType::Void, QMetaType::QString,   70,
    QMetaType::Void, QMetaType::Bool,   73,
    QMetaType::Double, QMetaType::Double, QMetaType::Double,   75,   76,
    QMetaType::Bool, 0x80000000 | 78, QMetaType::Int, QMetaType::Double, 0x80000000 | 11,   79,   80,   15,   12,
    QMetaType::Void, QMetaType::Bool, QMetaType::Double, QMetaType::Double,   82,    9,   10,
    QMetaType::Void, QMetaType::Bool, QMetaType::Double,   82,   15,
    QMetaType::Void, QMetaType::QPoint,   39,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   86,   50,   87,   88,   89,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 51,   92,
    QMetaType::Void, 0x80000000 | 94,   95,
    QMetaType::Void, QMetaType::QString,   97,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, 0x80000000 | 11,    9,   10,   12,
    QMetaType::Void, QMetaType::Double, 0x80000000 | 11,   15,   12,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, 0x80000000 | 11,   15,  101,   12,
    QMetaType::Void, QMetaType::QPoint,  103,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,  109,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,  109,
    QMetaType::Void, QMetaType::Bool,  109,
    QMetaType::Void, QMetaType::Bool,  109,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 121,  122,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,  109,
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
        case 23: _t->createTransformationMatrix((*reinterpret_cast< QVector3D(*)>(_a[1])),(*reinterpret_cast< QVector3D(*)>(_a[2])),(*reinterpret_cast< QVector3D(*)>(_a[3]))); break;
        case 24: { bool _r = _t->updateQTImage((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QAction*(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 25: { bool _r = _t->updateQTImage((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 26: { bool _r = _t->updateQTImage((*reinterpret_cast< cv::Mat(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 27: _t->addTargeterImage((*reinterpret_cast< targeterImage(*)>(_a[1])),(*reinterpret_cast< QAction*(*)>(_a[2]))); break;
        case 28: _t->addTargeterImage((*reinterpret_cast< targeterImage(*)>(_a[1]))); break;
        case 29: _t->addMatImage((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< imageType::imageType(*)>(_a[3])),(*reinterpret_cast< QAction*(*)>(_a[4]))); break;
        case 30: _t->LOGCONSOLE((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< CONSOLECOLOURS::colour(*)>(_a[4]))); break;
        case 31: _t->LOGCONSOLE((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 32: _t->LOGCONSOLE((*reinterpret_cast< imageType::imageType(*)>(_a[1])),(*reinterpret_cast< CONSOLECOLOURS::colour(*)>(_a[2]))); break;
        case 33: _t->LOGCONSOLE((*reinterpret_cast< imageType::imageType(*)>(_a[1]))); break;
        case 34: _t->LOGCONSOLE((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< CONSOLECOLOURS::colour(*)>(_a[2]))); break;
        case 35: _t->LOGCONSOLE((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 36: _t->StageMovementCompleted((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 37: _t->receiveSettings(); break;
        case 38: _t->StageConnectedXY((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 39: _t->StageConnectedZ((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 40: _t->enableFiducial((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 41: { double _r = _t->getBestFocus((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 42: { bool _r = _t->getBestFocusValue((*reinterpret_cast< QMap<double,double>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< ACTIONS::action(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 43: _t->updatePositionXY((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 44: _t->updatePositionZ((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 45: _t->ProvideContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 46: _t->logFeedback((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 47: _t->disablePanButton(); break;
        case 48: _t->unsetDrawingButtons((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 49: _t->setTargetArea((*reinterpret_cast< drawingShape(*)>(_a[1]))); break;
        case 50: _t->StatusBarMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 51: _t->stageMovedXY((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< ACTIONS::action(*)>(_a[3]))); break;
        case 52: _t->stageMovedZ((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< ACTIONS::action(*)>(_a[2]))); break;
        case 53: _t->addFocusValue((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< ACTIONS::action(*)>(_a[3]))); break;
        case 54: _t->moveObjective((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 55: _t->on_action_Open_triggered(); break;
        case 56: _t->on_action_New_triggered(); break;
        case 57: _t->on_actionCorner_Detection_triggered(); break;
        case 58: _t->on_actionEdge_Detection_triggered(); break;
        case 59: _t->on_actionGrid_Spacing_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 60: _t->on_action_scan_regions_triggered(); break;
        case 61: _t->on_actionCreate_Image_Mosaic_triggered(); break;
        case 62: _t->on_actionClick_Center_Objective_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 63: _t->on_actionReference_fiducial_marks_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 64: _t->on_actionClickTarget_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 65: _t->on_actionSave_Target_Positions_triggered(); break;
        case 66: _t->on_actionMask_Black_triggered(); break;
        case 67: _t->on_actionMask_White_triggered(); break;
        case 68: _t->on_actionEnergy_image_triggered(); break;
        case 69: _t->on_actionCreate_Mask_Image_triggered(); break;
        case 70: _t->onThumbImageClick((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 71: _t->on_actionProcessFocusStack_triggered(); break;
        case 72: _t->on_action_Save_triggered(); break;
        case 73: _t->on_actionSelect_All_triggered(); break;
        case 74: _t->on_actionDeselect_All_triggered(); break;
        case 75: _t->on_actionGrab_Image_From_Camera_triggered(); break;
        case 76: _t->on_actionGrab_Video_From_Camera_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 77: _t->on_actionZoom_Out_triggered(); break;
        case 78: _t->on_actionZoom_In_triggered(); break;
        case 79: _t->on_actionDetect_lines_triggered(); break;
        case 80: _t->on_actionRead_Barcode_triggered(); break;
        case 81: _t->on_actionSample_White_Binary_Regions_triggered(); break;
        case 82: _t->on_actionRemoveBlackPixels_triggered(); break;
        case 83: _t->on_actionEntropyFilter_triggered(); break;
        case 84: _t->on_actionDraw_Polygon_triggered(); break;
        case 85: _t->on_actionDraw_Circle_Region_triggered(); break;
        case 86: _t->on_actionDraw_Rectangular_Region_triggered(); break;
        case 87: _t->on_actionSelect_Object_triggered(); break;
        case 88: _t->on_action_Move_Image_triggered(); break;
        case 89: _t->openRecentFile(); break;
        case 90: _t->on_actionGet_Target_image_region_triggered(); break;
        case 91: _t->on_actionSet_as_find_targets_image_triggered(); break;
        case 92: _t->on_actionSet_as_Target_triggered(); break;
        case 93: _t->on_actionDeleteObject_triggered(); break;
        case 94: _t->on_actionFind_targets_triggered(); break;
        case 95: _t->on_actionScoreImage_triggered(); break;
        case 96: _t->on_actionDeleteImage_triggered(); break;
        case 97: _t->on_actionSettings_triggered(); break;
        case 98: _t->on_actionMergeImages_triggered(); break;
        case 99: _t->on_actionThresholdImage_triggered(); break;
        case 100: _t->on_actionConnected_Components_triggered(); break;
        case 101: _t->on_actionFilter_Binary_Objects_triggered(); break;
        case 102: _t->on_actionFind_Centers_triggered(); break;
        case 103: _t->on_actionInvert_triggered(); break;
        case 104: _t->on_actionCalibrate_Camera_triggered(); break;
        case 105: _t->on_actionCorrectImage_triggered(); break;
        case 106: _t->on_actionBackground_fit_triggered(); break;
        case 107: _t->on_actionEqualise_Image_triggered(); break;
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
        case 24:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 27:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 29:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 3:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 48:
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
        if (_id < 108)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 108;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 108)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 108;
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
