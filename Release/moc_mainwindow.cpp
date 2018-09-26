/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QSharedPointer>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[179];
    char stringdata0[3318];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 12), // "getFocusCUDA"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 11), // "FocusResult"
QT_MOC_LITERAL(4, 37, 3), // "res"
QT_MOC_LITERAL(5, 41, 8), // "getVideo"
QT_MOC_LITERAL(6, 50, 18), // "cameraType::camera"
QT_MOC_LITERAL(7, 69, 11), // "assignPorts"
QT_MOC_LITERAL(8, 81, 14), // "reportCOMPORTS"
QT_MOC_LITERAL(9, 96, 16), // "QVector<QString>"
QT_MOC_LITERAL(10, 113, 3), // "str"
QT_MOC_LITERAL(11, 117, 14), // "MoveAbsoluteXY"
QT_MOC_LITERAL(12, 132, 1), // "x"
QT_MOC_LITERAL(13, 134, 1), // "y"
QT_MOC_LITERAL(14, 136, 15), // "ACTIONS::action"
QT_MOC_LITERAL(15, 152, 3), // "act"
QT_MOC_LITERAL(16, 156, 14), // "MoveRelativeXY"
QT_MOC_LITERAL(17, 171, 13), // "MoveAbsoluteZ"
QT_MOC_LITERAL(18, 185, 1), // "z"
QT_MOC_LITERAL(19, 187, 13), // "SendCommandXY"
QT_MOC_LITERAL(20, 201, 3), // "cmd"
QT_MOC_LITERAL(21, 205, 13), // "SetVelocityXY"
QT_MOC_LITERAL(22, 219, 4), // "velo"
QT_MOC_LITERAL(23, 224, 11), // "CalibrateXY"
QT_MOC_LITERAL(24, 236, 14), // "MeasureRangeXY"
QT_MOC_LITERAL(25, 251, 9), // "ConnectXY"
QT_MOC_LITERAL(26, 261, 12), // "DisconnectXY"
QT_MOC_LITERAL(27, 274, 7), // "AbortXY"
QT_MOC_LITERAL(28, 282, 11), // "getCOMPORTS"
QT_MOC_LITERAL(29, 294, 14), // "connectToPortZ"
QT_MOC_LITERAL(30, 309, 14), // "AvailablePorts"
QT_MOC_LITERAL(31, 324, 11), // "excludePort"
QT_MOC_LITERAL(32, 336, 15), // "connectToPortXY"
QT_MOC_LITERAL(33, 352, 13), // "getPositionXY"
QT_MOC_LITERAL(34, 366, 5), // "isFid"
QT_MOC_LITERAL(35, 372, 12), // "getPositionZ"
QT_MOC_LITERAL(36, 385, 6), // "logDot"
QT_MOC_LITERAL(37, 392, 12), // "DisplayImage"
QT_MOC_LITERAL(38, 405, 5), // "index"
QT_MOC_LITERAL(39, 411, 10), // "saveBackup"
QT_MOC_LITERAL(40, 422, 5), // "bLoad"
QT_MOC_LITERAL(41, 428, 13), // "LogProcessing"
QT_MOC_LITERAL(42, 442, 6), // "bStart"
QT_MOC_LITERAL(43, 449, 19), // "setSamplingDistance"
QT_MOC_LITERAL(44, 469, 24), // "QSharedPointer<QPolygon>"
QT_MOC_LITERAL(45, 494, 4), // "poly"
QT_MOC_LITERAL(46, 499, 15), // "addFiducialMark"
QT_MOC_LITERAL(47, 515, 18), // "FIDUCIAL::position"
QT_MOC_LITERAL(48, 534, 3), // "pos"
QT_MOC_LITERAL(49, 538, 1), // "p"
QT_MOC_LITERAL(50, 540, 16), // "updateVideoImage"
QT_MOC_LITERAL(51, 557, 7), // "cv::Mat"
QT_MOC_LITERAL(52, 565, 2), // "im"
QT_MOC_LITERAL(53, 568, 17), // "startFocusThreads"
QT_MOC_LITERAL(54, 586, 22), // "addFocusValueCompleted"
QT_MOC_LITERAL(55, 609, 11), // "makeIndexes"
QT_MOC_LITERAL(56, 621, 15), // "QVector<QPoint>"
QT_MOC_LITERAL(57, 637, 16), // "QVector<QPointF>"
QT_MOC_LITERAL(58, 654, 9), // "positions"
QT_MOC_LITERAL(59, 664, 26), // "createTransformationMatrix"
QT_MOC_LITERAL(60, 691, 7), // "topleft"
QT_MOC_LITERAL(61, 699, 8), // "topright"
QT_MOC_LITERAL(62, 708, 10), // "bottomleft"
QT_MOC_LITERAL(63, 719, 27), // "getTargetPositionsFromImage"
QT_MOC_LITERAL(64, 747, 8), // "cv::Mat&"
QT_MOC_LITERAL(65, 756, 14), // "centroidsImage"
QT_MOC_LITERAL(66, 771, 5), // "stats"
QT_MOC_LITERAL(67, 777, 16), // "QVector<QPoint>&"
QT_MOC_LITERAL(68, 794, 3), // "pts"
QT_MOC_LITERAL(69, 798, 15), // "QVector<QRect>&"
QT_MOC_LITERAL(70, 814, 5), // "rects"
QT_MOC_LITERAL(71, 820, 13), // "updateQTImage"
QT_MOC_LITERAL(72, 834, 3), // "img"
QT_MOC_LITERAL(73, 838, 4), // "name"
QT_MOC_LITERAL(74, 843, 8), // "QAction*"
QT_MOC_LITERAL(75, 852, 7), // "pAction"
QT_MOC_LITERAL(76, 860, 16), // "addTargeterImage"
QT_MOC_LITERAL(77, 877, 43), // "QExplicitlySharedDataPointer<..."
QT_MOC_LITERAL(78, 921, 3), // "tim"
QT_MOC_LITERAL(79, 925, 11), // "addMatImage"
QT_MOC_LITERAL(80, 937, 9), // "imagename"
QT_MOC_LITERAL(81, 947, 20), // "imageType::imageType"
QT_MOC_LITERAL(82, 968, 4), // "type"
QT_MOC_LITERAL(83, 973, 10), // "LOGCONSOLE"
QT_MOC_LITERAL(84, 984, 7), // "strText"
QT_MOC_LITERAL(85, 992, 7), // "newline"
QT_MOC_LITERAL(86, 1000, 9), // "moveToEnd"
QT_MOC_LITERAL(87, 1010, 22), // "CONSOLECOLOURS::colour"
QT_MOC_LITERAL(88, 1033, 3), // "icn"
QT_MOC_LITERAL(89, 1037, 22), // "StageMovementCompleted"
QT_MOC_LITERAL(90, 1060, 7), // "message"
QT_MOC_LITERAL(91, 1068, 15), // "receiveSettings"
QT_MOC_LITERAL(92, 1084, 16), // "StageConnectedXY"
QT_MOC_LITERAL(93, 1101, 4), // "port"
QT_MOC_LITERAL(94, 1106, 15), // "StageConnectedZ"
QT_MOC_LITERAL(95, 1122, 14), // "enableFiducial"
QT_MOC_LITERAL(96, 1137, 7), // "bEnable"
QT_MOC_LITERAL(97, 1145, 16), // "updatePositionXY"
QT_MOC_LITERAL(98, 1162, 4), // "bFid"
QT_MOC_LITERAL(99, 1167, 15), // "updatePositionZ"
QT_MOC_LITERAL(100, 1183, 18), // "ProvideContextMenu"
QT_MOC_LITERAL(101, 1202, 11), // "logFeedback"
QT_MOC_LITERAL(102, 1214, 5), // "score"
QT_MOC_LITERAL(103, 1220, 5), // "email"
QT_MOC_LITERAL(104, 1226, 9), // "institute"
QT_MOC_LITERAL(105, 1236, 4), // "desc"
QT_MOC_LITERAL(106, 1241, 16), // "disablePanButton"
QT_MOC_LITERAL(107, 1258, 19), // "unsetDrawingButtons"
QT_MOC_LITERAL(108, 1278, 4), // "pAct"
QT_MOC_LITERAL(109, 1283, 13), // "setTargetArea"
QT_MOC_LITERAL(110, 1297, 28), // "QSharedPointer<drawingShape>"
QT_MOC_LITERAL(111, 1326, 5), // "shape"
QT_MOC_LITERAL(112, 1332, 16), // "StatusBarMessage"
QT_MOC_LITERAL(113, 1349, 3), // "msg"
QT_MOC_LITERAL(114, 1353, 12), // "stageMovedXY"
QT_MOC_LITERAL(115, 1366, 11), // "stageMovedZ"
QT_MOC_LITERAL(116, 1378, 13), // "addFocusValue"
QT_MOC_LITERAL(117, 1392, 6), // "result"
QT_MOC_LITERAL(118, 1399, 13), // "moveObjective"
QT_MOC_LITERAL(119, 1413, 2), // "pt"
QT_MOC_LITERAL(120, 1416, 24), // "on_action_Open_triggered"
QT_MOC_LITERAL(121, 1441, 23), // "on_action_New_triggered"
QT_MOC_LITERAL(122, 1465, 35), // "on_actionCorner_Detection_tri..."
QT_MOC_LITERAL(123, 1501, 33), // "on_actionEdge_Detection_trigg..."
QT_MOC_LITERAL(124, 1535, 28), // "on_actionLaplacian_triggered"
QT_MOC_LITERAL(125, 1564, 31), // "on_actionGrid_Spacing_triggered"
QT_MOC_LITERAL(126, 1596, 7), // "checked"
QT_MOC_LITERAL(127, 1604, 33), // "on_actionAnnotate_Shape_trigg..."
QT_MOC_LITERAL(128, 1638, 32), // "on_action_scan_regions_triggered"
QT_MOC_LITERAL(129, 1671, 38), // "on_actionCreate_Image_Mosaic_..."
QT_MOC_LITERAL(130, 1710, 41), // "on_actionClick_Center_Objecti..."
QT_MOC_LITERAL(131, 1752, 43), // "on_actionReference_fiducial_m..."
QT_MOC_LITERAL(132, 1796, 30), // "on_actionClickTarget_triggered"
QT_MOC_LITERAL(133, 1827, 40), // "on_actionSave_Target_Position..."
QT_MOC_LITERAL(134, 1868, 29), // "on_actionMask_Black_triggered"
QT_MOC_LITERAL(135, 1898, 29), // "on_actionMask_White_triggered"
QT_MOC_LITERAL(136, 1928, 31), // "on_actionEnergy_image_triggered"
QT_MOC_LITERAL(137, 1960, 36), // "on_actionCreate_Mask_Image_tr..."
QT_MOC_LITERAL(138, 1997, 17), // "onThumbImageClick"
QT_MOC_LITERAL(139, 2015, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(140, 2032, 4), // "item"
QT_MOC_LITERAL(141, 2037, 36), // "on_actionProcessFocusStack_tr..."
QT_MOC_LITERAL(142, 2074, 24), // "on_action_Save_triggered"
QT_MOC_LITERAL(143, 2099, 29), // "on_actionSelect_All_triggered"
QT_MOC_LITERAL(144, 2129, 31), // "on_actionDeselect_All_triggered"
QT_MOC_LITERAL(145, 2161, 41), // "on_actionGrab_Image_From_Came..."
QT_MOC_LITERAL(146, 2203, 41), // "on_actionGrab_Video_From_Came..."
QT_MOC_LITERAL(147, 2245, 27), // "on_actionZoom_Out_triggered"
QT_MOC_LITERAL(148, 2273, 26), // "on_actionZoom_In_triggered"
QT_MOC_LITERAL(149, 2300, 31), // "on_actionDetect_lines_triggered"
QT_MOC_LITERAL(150, 2332, 31), // "on_actionRead_Barcode_triggered"
QT_MOC_LITERAL(151, 2364, 46), // "on_actionSample_White_Binary_..."
QT_MOC_LITERAL(152, 2411, 36), // "on_actionRemoveBlackPixels_tr..."
QT_MOC_LITERAL(153, 2448, 32), // "on_actionEntropyFilter_triggered"
QT_MOC_LITERAL(154, 2481, 31), // "on_actionDraw_Polygon_triggered"
QT_MOC_LITERAL(155, 2513, 37), // "on_actionDraw_Circle_Region_t..."
QT_MOC_LITERAL(156, 2551, 42), // "on_actionDraw_Rectangular_Reg..."
QT_MOC_LITERAL(157, 2594, 32), // "on_actionSelect_Object_triggered"
QT_MOC_LITERAL(158, 2627, 30), // "on_action_Move_Image_triggered"
QT_MOC_LITERAL(159, 2658, 14), // "openRecentFile"
QT_MOC_LITERAL(160, 2673, 42), // "on_actionGet_Target_image_reg..."
QT_MOC_LITERAL(161, 2716, 44), // "on_actionSet_as_find_targets_..."
QT_MOC_LITERAL(162, 2761, 32), // "on_actionSet_as_Target_triggered"
QT_MOC_LITERAL(163, 2794, 31), // "on_actionDeleteObject_triggered"
QT_MOC_LITERAL(164, 2826, 31), // "on_actionFind_targets_triggered"
QT_MOC_LITERAL(165, 2858, 29), // "on_actionScoreImage_triggered"
QT_MOC_LITERAL(166, 2888, 30), // "on_actionDeleteImage_triggered"
QT_MOC_LITERAL(167, 2919, 27), // "on_actionSettings_triggered"
QT_MOC_LITERAL(168, 2947, 30), // "on_actionMergeImages_triggered"
QT_MOC_LITERAL(169, 2978, 33), // "on_actionThresholdImage_trigg..."
QT_MOC_LITERAL(170, 3012, 39), // "on_actionConnected_Components..."
QT_MOC_LITERAL(171, 3052, 40), // "on_actionFilter_Binary_Object..."
QT_MOC_LITERAL(172, 3093, 31), // "on_actionFind_Centers_triggered"
QT_MOC_LITERAL(173, 3125, 25), // "on_actionInvert_triggered"
QT_MOC_LITERAL(174, 3151, 35), // "on_actionCalibrate_Camera_tri..."
QT_MOC_LITERAL(175, 3187, 31), // "on_actionCorrectImage_triggered"
QT_MOC_LITERAL(176, 3219, 33), // "on_actionBackground_fit_trigg..."
QT_MOC_LITERAL(177, 3253, 33), // "on_actionEqualise_Image_trigg..."
QT_MOC_LITERAL(178, 3287, 30) // "on_actionTrainTarget_triggered"

    },
    "MainWindow\0getFocusCUDA\0\0FocusResult\0"
    "res\0getVideo\0cameraType::camera\0"
    "assignPorts\0reportCOMPORTS\0QVector<QString>\0"
    "str\0MoveAbsoluteXY\0x\0y\0ACTIONS::action\0"
    "act\0MoveRelativeXY\0MoveAbsoluteZ\0z\0"
    "SendCommandXY\0cmd\0SetVelocityXY\0velo\0"
    "CalibrateXY\0MeasureRangeXY\0ConnectXY\0"
    "DisconnectXY\0AbortXY\0getCOMPORTS\0"
    "connectToPortZ\0AvailablePorts\0excludePort\0"
    "connectToPortXY\0getPositionXY\0isFid\0"
    "getPositionZ\0logDot\0DisplayImage\0index\0"
    "saveBackup\0bLoad\0LogProcessing\0bStart\0"
    "setSamplingDistance\0QSharedPointer<QPolygon>\0"
    "poly\0addFiducialMark\0FIDUCIAL::position\0"
    "pos\0p\0updateVideoImage\0cv::Mat\0im\0"
    "startFocusThreads\0addFocusValueCompleted\0"
    "makeIndexes\0QVector<QPoint>\0"
    "QVector<QPointF>\0positions\0"
    "createTransformationMatrix\0topleft\0"
    "topright\0bottomleft\0getTargetPositionsFromImage\0"
    "cv::Mat&\0centroidsImage\0stats\0"
    "QVector<QPoint>&\0pts\0QVector<QRect>&\0"
    "rects\0updateQTImage\0img\0name\0QAction*\0"
    "pAction\0addTargeterImage\0"
    "QExplicitlySharedDataPointer<targeterImage>\0"
    "tim\0addMatImage\0imagename\0"
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
    "QSharedPointer<drawingShape>\0shape\0"
    "StatusBarMessage\0msg\0stageMovedXY\0"
    "stageMovedZ\0addFocusValue\0result\0"
    "moveObjective\0pt\0on_action_Open_triggered\0"
    "on_action_New_triggered\0"
    "on_actionCorner_Detection_triggered\0"
    "on_actionEdge_Detection_triggered\0"
    "on_actionLaplacian_triggered\0"
    "on_actionGrid_Spacing_triggered\0checked\0"
    "on_actionAnnotate_Shape_triggered\0"
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
    "on_actionEqualise_Image_triggered\0"
    "on_actionTrainTarget_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
     117,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      19,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  599,    2, 0x06 /* Public */,
       5,    1,  602,    2, 0x06 /* Public */,
       7,    0,  605,    2, 0x06 /* Public */,
       8,    1,  606,    2, 0x06 /* Public */,
      11,    3,  609,    2, 0x06 /* Public */,
      16,    3,  616,    2, 0x06 /* Public */,
      17,    2,  623,    2, 0x06 /* Public */,
      19,    1,  628,    2, 0x06 /* Public */,
      21,    1,  631,    2, 0x06 /* Public */,
      23,    0,  634,    2, 0x06 /* Public */,
      24,    0,  635,    2, 0x06 /* Public */,
      25,    0,  636,    2, 0x06 /* Public */,
      26,    0,  637,    2, 0x06 /* Public */,
      27,    0,  638,    2, 0x06 /* Public */,
      28,    0,  639,    2, 0x06 /* Public */,
      29,    2,  640,    2, 0x06 /* Public */,
      32,    2,  645,    2, 0x06 /* Public */,
      33,    1,  650,    2, 0x06 /* Public */,
      35,    1,  653,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      36,    0,  656,    2, 0x0a /* Public */,
      37,    0,  657,    2, 0x0a /* Public */,
      37,    1,  658,    2, 0x0a /* Public */,
      39,    1,  661,    2, 0x0a /* Public */,
      41,    1,  664,    2, 0x0a /* Public */,
      43,    1,  667,    2, 0x0a /* Public */,
      46,    2,  670,    2, 0x0a /* Public */,
      50,    1,  675,    2, 0x0a /* Public */,
      53,    3,  678,    2, 0x0a /* Public */,
      54,    0,  685,    2, 0x0a /* Public */,
      55,    1,  686,    2, 0x0a /* Public */,
      59,    3,  689,    2, 0x0a /* Public */,
      63,    4,  696,    2, 0x0a /* Public */,
      71,    3,  705,    2, 0x0a /* Public */,
      71,    2,  712,    2, 0x2a /* Public | MethodCloned */,
      71,    1,  717,    2, 0x2a /* Public | MethodCloned */,
      76,    2,  720,    2, 0x0a /* Public */,
      76,    1,  725,    2, 0x2a /* Public | MethodCloned */,
      79,    4,  728,    2, 0x0a /* Public */,
      83,    4,  737,    2, 0x0a /* Public */,
      83,    3,  746,    2, 0x2a /* Public | MethodCloned */,
      83,    2,  753,    2, 0x0a /* Public */,
      83,    1,  758,    2, 0x2a /* Public | MethodCloned */,
      83,    2,  761,    2, 0x0a /* Public */,
      83,    1,  766,    2, 0x2a /* Public | MethodCloned */,
      89,    1,  769,    2, 0x0a /* Public */,
      91,    0,  772,    2, 0x0a /* Public */,
      92,    1,  773,    2, 0x0a /* Public */,
      94,    1,  776,    2, 0x0a /* Public */,
      95,    1,  779,    2, 0x0a /* Public */,
      97,    3,  782,    2, 0x08 /* Private */,
      99,    2,  789,    2, 0x08 /* Private */,
     100,    1,  794,    2, 0x08 /* Private */,
     101,    5,  797,    2, 0x08 /* Private */,
     106,    0,  808,    2, 0x08 /* Private */,
     107,    1,  809,    2, 0x08 /* Private */,
     109,    1,  812,    2, 0x08 /* Private */,
     112,    1,  815,    2, 0x08 /* Private */,
     114,    3,  818,    2, 0x08 /* Private */,
     115,    2,  825,    2, 0x08 /* Private */,
     116,    1,  830,    2, 0x08 /* Private */,
     118,    1,  833,    2, 0x08 /* Private */,
     120,    0,  836,    2, 0x08 /* Private */,
     121,    0,  837,    2, 0x08 /* Private */,
     122,    0,  838,    2, 0x08 /* Private */,
     123,    0,  839,    2, 0x08 /* Private */,
     124,    0,  840,    2, 0x08 /* Private */,
     125,    1,  841,    2, 0x08 /* Private */,
     127,    0,  844,    2, 0x08 /* Private */,
     128,    0,  845,    2, 0x08 /* Private */,
     129,    0,  846,    2, 0x08 /* Private */,
     130,    1,  847,    2, 0x08 /* Private */,
     131,    1,  850,    2, 0x08 /* Private */,
     132,    1,  853,    2, 0x08 /* Private */,
     133,    0,  856,    2, 0x08 /* Private */,
     134,    0,  857,    2, 0x08 /* Private */,
     135,    0,  858,    2, 0x08 /* Private */,
     136,    0,  859,    2, 0x08 /* Private */,
     137,    0,  860,    2, 0x08 /* Private */,
     138,    1,  861,    2, 0x08 /* Private */,
     141,    0,  864,    2, 0x08 /* Private */,
     142,    0,  865,    2, 0x08 /* Private */,
     143,    0,  866,    2, 0x08 /* Private */,
     144,    0,  867,    2, 0x08 /* Private */,
     145,    0,  868,    2, 0x08 /* Private */,
     146,    1,  869,    2, 0x08 /* Private */,
     147,    0,  872,    2, 0x08 /* Private */,
     148,    0,  873,    2, 0x08 /* Private */,
     149,    0,  874,    2, 0x08 /* Private */,
     150,    0,  875,    2, 0x08 /* Private */,
     151,    0,  876,    2, 0x08 /* Private */,
     152,    0,  877,    2, 0x08 /* Private */,
     153,    0,  878,    2, 0x08 /* Private */,
     154,    0,  879,    2, 0x08 /* Private */,
     155,    0,  880,    2, 0x08 /* Private */,
     156,    0,  881,    2, 0x08 /* Private */,
     157,    0,  882,    2, 0x08 /* Private */,
     158,    0,  883,    2, 0x08 /* Private */,
     159,    0,  884,    2, 0x08 /* Private */,
     160,    0,  885,    2, 0x08 /* Private */,
     161,    0,  886,    2, 0x08 /* Private */,
     162,    0,  887,    2, 0x08 /* Private */,
     163,    0,  888,    2, 0x08 /* Private */,
     164,    0,  889,    2, 0x08 /* Private */,
     165,    0,  890,    2, 0x08 /* Private */,
     166,    0,  891,    2, 0x08 /* Private */,
     167,    0,  892,    2, 0x08 /* Private */,
     168,    0,  893,    2, 0x08 /* Private */,
     169,    0,  894,    2, 0x08 /* Private */,
     170,    0,  895,    2, 0x08 /* Private */,
     171,    0,  896,    2, 0x08 /* Private */,
     172,    0,  897,    2, 0x08 /* Private */,
     173,    0,  898,    2, 0x08 /* Private */,
     174,    0,  899,    2, 0x08 /* Private */,
     175,    0,  900,    2, 0x08 /* Private */,
     176,    0,  901,    2, 0x08 /* Private */,
     177,    0,  902,    2, 0x08 /* Private */,
     178,    0,  903,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, 0x80000000 | 14,   12,   13,   15,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, 0x80000000 | 14,   12,   13,   15,
    QMetaType::Void, QMetaType::Double, 0x80000000 | 14,   18,   15,
    QMetaType::Void, QMetaType::QString,   20,
    QMetaType::Void, QMetaType::Double,   22,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9, QMetaType::QString,   30,   31,
    QMetaType::Void, 0x80000000 | 9, QMetaType::QString,   30,   31,
    QMetaType::Void, QMetaType::Bool,   34,
    QMetaType::Void, QMetaType::Bool,   34,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Bool,   40,
    QMetaType::Void, QMetaType::Bool,   42,
    QMetaType::Void, 0x80000000 | 44,   45,
    QMetaType::Void, 0x80000000 | 47, QMetaType::QPoint,   48,   49,
    QMetaType::Void, 0x80000000 | 51,   52,
    QMetaType::Void, 0x80000000 | 51, QMetaType::Double, 0x80000000 | 14,   52,   18,   15,
    QMetaType::Void,
    0x80000000 | 56, 0x80000000 | 57,   58,
    QMetaType::Void, QMetaType::QVector3D, QMetaType::QVector3D, QMetaType::QVector3D,   60,   61,   62,
    QMetaType::Void, 0x80000000 | 64, 0x80000000 | 64, 0x80000000 | 67, 0x80000000 | 69,   65,   66,   68,   70,
    QMetaType::Bool, 0x80000000 | 51, QMetaType::QString, 0x80000000 | 74,   72,   73,   75,
    QMetaType::Bool, 0x80000000 | 51, QMetaType::QString,   72,   73,
    QMetaType::Bool, 0x80000000 | 51,   72,
    QMetaType::Void, 0x80000000 | 77, 0x80000000 | 74,   78,   75,
    QMetaType::Void, 0x80000000 | 77,   78,
    QMetaType::Void, 0x80000000 | 51, QMetaType::QString, 0x80000000 | 81, 0x80000000 | 74,   72,   80,   82,   75,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, 0x80000000 | 87,   84,   85,   86,   88,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool,   84,   85,   86,
    QMetaType::Void, 0x80000000 | 81, 0x80000000 | 87,   82,   88,
    QMetaType::Void, 0x80000000 | 81,   82,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 87,   84,   88,
    QMetaType::Void, QMetaType::QString,   84,
    QMetaType::Void, QMetaType::QString,   90,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   93,
    QMetaType::Void, QMetaType::QString,   93,
    QMetaType::Void, QMetaType::Bool,   96,
    QMetaType::Void, QMetaType::Bool, QMetaType::Double, QMetaType::Double,   98,   12,   13,
    QMetaType::Void, QMetaType::Bool, QMetaType::Double,   98,   18,
    QMetaType::Void, QMetaType::QPoint,   48,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,  102,   73,  103,  104,  105,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 74,  108,
    QMetaType::Void, 0x80000000 | 110,  111,
    QMetaType::Void, QMetaType::QString,  113,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, 0x80000000 | 14,   12,   13,   15,
    QMetaType::Void, QMetaType::Double, 0x80000000 | 14,   18,   15,
    QMetaType::Void, 0x80000000 | 3,  117,
    QMetaType::Void, QMetaType::QPoint,  119,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,  126,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,  126,
    QMetaType::Void, QMetaType::Bool,  126,
    QMetaType::Void, QMetaType::Bool,  126,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 139,  140,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,  126,
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
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->getFocusCUDA((*reinterpret_cast< FocusResult(*)>(_a[1]))); break;
        case 1: _t->getVideo((*reinterpret_cast< cameraType::camera(*)>(_a[1]))); break;
        case 2: _t->assignPorts(); break;
        case 3: _t->reportCOMPORTS((*reinterpret_cast< QVector<QString>(*)>(_a[1]))); break;
        case 4: _t->MoveAbsoluteXY((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< ACTIONS::action(*)>(_a[3]))); break;
        case 5: _t->MoveRelativeXY((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< ACTIONS::action(*)>(_a[3]))); break;
        case 6: _t->MoveAbsoluteZ((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< ACTIONS::action(*)>(_a[2]))); break;
        case 7: _t->SendCommandXY((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->SetVelocityXY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->CalibrateXY(); break;
        case 10: _t->MeasureRangeXY(); break;
        case 11: _t->ConnectXY(); break;
        case 12: _t->DisconnectXY(); break;
        case 13: _t->AbortXY(); break;
        case 14: _t->getCOMPORTS(); break;
        case 15: _t->connectToPortZ((*reinterpret_cast< QVector<QString>(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 16: _t->connectToPortXY((*reinterpret_cast< QVector<QString>(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 17: _t->getPositionXY((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->getPositionZ((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 19: _t->logDot(); break;
        case 20: _t->DisplayImage(); break;
        case 21: _t->DisplayImage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->saveBackup((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: _t->LogProcessing((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: _t->setSamplingDistance((*reinterpret_cast< QSharedPointer<QPolygon>(*)>(_a[1]))); break;
        case 25: _t->addFiducialMark((*reinterpret_cast< FIDUCIAL::position(*)>(_a[1])),(*reinterpret_cast< QPoint(*)>(_a[2]))); break;
        case 26: _t->updateVideoImage((*reinterpret_cast< cv::Mat(*)>(_a[1]))); break;
        case 27: _t->startFocusThreads((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< ACTIONS::action(*)>(_a[3]))); break;
        case 28: _t->addFocusValueCompleted(); break;
        case 29: { QVector<QPoint> _r = _t->makeIndexes((*reinterpret_cast< QVector<QPointF>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVector<QPoint>*>(_a[0]) = _r; }  break;
        case 30: _t->createTransformationMatrix((*reinterpret_cast< QVector3D(*)>(_a[1])),(*reinterpret_cast< QVector3D(*)>(_a[2])),(*reinterpret_cast< QVector3D(*)>(_a[3]))); break;
        case 31: _t->getTargetPositionsFromImage((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< cv::Mat(*)>(_a[2])),(*reinterpret_cast< QVector<QPoint>(*)>(_a[3])),(*reinterpret_cast< QVector<QRect>(*)>(_a[4]))); break;
        case 32: { bool _r = _t->updateQTImage((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QAction*(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 33: { bool _r = _t->updateQTImage((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 34: { bool _r = _t->updateQTImage((*reinterpret_cast< cv::Mat(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 35: _t->addTargeterImage((*reinterpret_cast< QExplicitlySharedDataPointer<targeterImage>(*)>(_a[1])),(*reinterpret_cast< QAction*(*)>(_a[2]))); break;
        case 36: _t->addTargeterImage((*reinterpret_cast< QExplicitlySharedDataPointer<targeterImage>(*)>(_a[1]))); break;
        case 37: _t->addMatImage((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< imageType::imageType(*)>(_a[3])),(*reinterpret_cast< QAction*(*)>(_a[4]))); break;
        case 38: _t->LOGCONSOLE((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< CONSOLECOLOURS::colour(*)>(_a[4]))); break;
        case 39: _t->LOGCONSOLE((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 40: _t->LOGCONSOLE((*reinterpret_cast< imageType::imageType(*)>(_a[1])),(*reinterpret_cast< CONSOLECOLOURS::colour(*)>(_a[2]))); break;
        case 41: _t->LOGCONSOLE((*reinterpret_cast< imageType::imageType(*)>(_a[1]))); break;
        case 42: _t->LOGCONSOLE((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< CONSOLECOLOURS::colour(*)>(_a[2]))); break;
        case 43: _t->LOGCONSOLE((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 44: _t->StageMovementCompleted((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 45: _t->receiveSettings(); break;
        case 46: _t->StageConnectedXY((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 47: _t->StageConnectedZ((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 48: _t->enableFiducial((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 49: _t->updatePositionXY((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 50: _t->updatePositionZ((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 51: _t->ProvideContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 52: _t->logFeedback((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 53: _t->disablePanButton(); break;
        case 54: _t->unsetDrawingButtons((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 55: _t->setTargetArea((*reinterpret_cast< QSharedPointer<drawingShape>(*)>(_a[1]))); break;
        case 56: _t->StatusBarMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 57: _t->stageMovedXY((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< ACTIONS::action(*)>(_a[3]))); break;
        case 58: _t->stageMovedZ((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< ACTIONS::action(*)>(_a[2]))); break;
        case 59: _t->addFocusValue((*reinterpret_cast< FocusResult(*)>(_a[1]))); break;
        case 60: _t->moveObjective((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 61: _t->on_action_Open_triggered(); break;
        case 62: _t->on_action_New_triggered(); break;
        case 63: _t->on_actionCorner_Detection_triggered(); break;
        case 64: _t->on_actionEdge_Detection_triggered(); break;
        case 65: _t->on_actionLaplacian_triggered(); break;
        case 66: _t->on_actionGrid_Spacing_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 67: _t->on_actionAnnotate_Shape_triggered(); break;
        case 68: _t->on_action_scan_regions_triggered(); break;
        case 69: _t->on_actionCreate_Image_Mosaic_triggered(); break;
        case 70: _t->on_actionClick_Center_Objective_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 71: _t->on_actionReference_fiducial_marks_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 72: _t->on_actionClickTarget_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 73: _t->on_actionSave_Target_Positions_triggered(); break;
        case 74: _t->on_actionMask_Black_triggered(); break;
        case 75: _t->on_actionMask_White_triggered(); break;
        case 76: _t->on_actionEnergy_image_triggered(); break;
        case 77: _t->on_actionCreate_Mask_Image_triggered(); break;
        case 78: _t->onThumbImageClick((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 79: _t->on_actionProcessFocusStack_triggered(); break;
        case 80: _t->on_action_Save_triggered(); break;
        case 81: _t->on_actionSelect_All_triggered(); break;
        case 82: _t->on_actionDeselect_All_triggered(); break;
        case 83: _t->on_actionGrab_Image_From_Camera_triggered(); break;
        case 84: _t->on_actionGrab_Video_From_Camera_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 85: _t->on_actionZoom_Out_triggered(); break;
        case 86: _t->on_actionZoom_In_triggered(); break;
        case 87: _t->on_actionDetect_lines_triggered(); break;
        case 88: _t->on_actionRead_Barcode_triggered(); break;
        case 89: _t->on_actionSample_White_Binary_Regions_triggered(); break;
        case 90: _t->on_actionRemoveBlackPixels_triggered(); break;
        case 91: _t->on_actionEntropyFilter_triggered(); break;
        case 92: _t->on_actionDraw_Polygon_triggered(); break;
        case 93: _t->on_actionDraw_Circle_Region_triggered(); break;
        case 94: _t->on_actionDraw_Rectangular_Region_triggered(); break;
        case 95: _t->on_actionSelect_Object_triggered(); break;
        case 96: _t->on_action_Move_Image_triggered(); break;
        case 97: _t->openRecentFile(); break;
        case 98: _t->on_actionGet_Target_image_region_triggered(); break;
        case 99: _t->on_actionSet_as_find_targets_image_triggered(); break;
        case 100: _t->on_actionSet_as_Target_triggered(); break;
        case 101: _t->on_actionDeleteObject_triggered(); break;
        case 102: _t->on_actionFind_targets_triggered(); break;
        case 103: _t->on_actionScoreImage_triggered(); break;
        case 104: _t->on_actionDeleteImage_triggered(); break;
        case 105: _t->on_actionSettings_triggered(); break;
        case 106: _t->on_actionMergeImages_triggered(); break;
        case 107: _t->on_actionThresholdImage_triggered(); break;
        case 108: _t->on_actionConnected_Components_triggered(); break;
        case 109: _t->on_actionFilter_Binary_Objects_triggered(); break;
        case 110: _t->on_actionFind_Centers_triggered(); break;
        case 111: _t->on_actionInvert_triggered(); break;
        case 112: _t->on_actionCalibrate_Camera_triggered(); break;
        case 113: _t->on_actionCorrectImage_triggered(); break;
        case 114: _t->on_actionBackground_fit_triggered(); break;
        case 115: _t->on_actionEqualise_Image_triggered(); break;
        case 116: _t->on_actionTrainTarget_triggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
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
        case 16:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QString> >(); break;
            }
            break;
        case 29:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QPointF> >(); break;
            }
            break;
        case 32:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 35:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 37:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 3:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 54:
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
            typedef void (MainWindow::*_t)(FocusResult );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::getFocusCUDA)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(cameraType::camera );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::getVideo)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::assignPorts)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(QVector<QString> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::reportCOMPORTS)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(double , double , ACTIONS::action );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::MoveAbsoluteXY)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(double , double , ACTIONS::action );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::MoveRelativeXY)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(double , ACTIONS::action );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::MoveAbsoluteZ)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::SendCommandXY)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::SetVelocityXY)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::CalibrateXY)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::MeasureRangeXY)) {
                *result = 10;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::ConnectXY)) {
                *result = 11;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::DisconnectXY)) {
                *result = 12;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::AbortXY)) {
                *result = 13;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::getCOMPORTS)) {
                *result = 14;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(QVector<QString> , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::connectToPortZ)) {
                *result = 15;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(QVector<QString> , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::connectToPortXY)) {
                *result = 16;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::getPositionXY)) {
                *result = 17;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::getPositionZ)) {
                *result = 18;
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
        if (_id < 117)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 117;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 117)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 117;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::getFocusCUDA(FocusResult _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::getVideo(cameraType::camera _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::assignPorts()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void MainWindow::reportCOMPORTS(QVector<QString> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MainWindow::MoveAbsoluteXY(double _t1, double _t2, ACTIONS::action _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MainWindow::MoveRelativeXY(double _t1, double _t2, ACTIONS::action _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MainWindow::MoveAbsoluteZ(double _t1, ACTIONS::action _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MainWindow::SendCommandXY(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void MainWindow::SetVelocityXY(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void MainWindow::CalibrateXY()
{
    QMetaObject::activate(this, &staticMetaObject, 9, Q_NULLPTR);
}

// SIGNAL 10
void MainWindow::MeasureRangeXY()
{
    QMetaObject::activate(this, &staticMetaObject, 10, Q_NULLPTR);
}

// SIGNAL 11
void MainWindow::ConnectXY()
{
    QMetaObject::activate(this, &staticMetaObject, 11, Q_NULLPTR);
}

// SIGNAL 12
void MainWindow::DisconnectXY()
{
    QMetaObject::activate(this, &staticMetaObject, 12, Q_NULLPTR);
}

// SIGNAL 13
void MainWindow::AbortXY()
{
    QMetaObject::activate(this, &staticMetaObject, 13, Q_NULLPTR);
}

// SIGNAL 14
void MainWindow::getCOMPORTS()
{
    QMetaObject::activate(this, &staticMetaObject, 14, Q_NULLPTR);
}

// SIGNAL 15
void MainWindow::connectToPortZ(QVector<QString> _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void MainWindow::connectToPortXY(QVector<QString> _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void MainWindow::getPositionXY(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void MainWindow::getPositionZ(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
