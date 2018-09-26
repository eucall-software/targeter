/****************************************************************************
** Meta object code from reading C++ file 'settingsdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../settingsdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settingsdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SettingsDialog_t {
    QByteArrayData data[223];
    char stringdata0[6010];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SettingsDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SettingsDialog_t qt_meta_stringdata_SettingsDialog = {
    {
QT_MOC_LITERAL(0, 0, 14), // "SettingsDialog"
QT_MOC_LITERAL(1, 15, 12), // "sendSettings"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 16), // "updatePaddTarget"
QT_MOC_LITERAL(4, 46, 16), // "bPaddTargetImage"
QT_MOC_LITERAL(5, 63, 6), // "levels"
QT_MOC_LITERAL(6, 70, 7), // "setGrid"
QT_MOC_LITERAL(7, 78, 8), // "bChecked"
QT_MOC_LITERAL(8, 87, 4), // "offX"
QT_MOC_LITERAL(9, 92, 4), // "offY"
QT_MOC_LITERAL(10, 97, 6), // "spaceX"
QT_MOC_LITERAL(11, 104, 6), // "spaceY"
QT_MOC_LITERAL(12, 111, 6), // "colour"
QT_MOC_LITERAL(13, 118, 11), // "logFeedback"
QT_MOC_LITERAL(14, 130, 5), // "score"
QT_MOC_LITERAL(15, 136, 4), // "name"
QT_MOC_LITERAL(16, 141, 5), // "email"
QT_MOC_LITERAL(17, 147, 9), // "institute"
QT_MOC_LITERAL(18, 157, 4), // "desc"
QT_MOC_LITERAL(19, 162, 14), // "MoveAbsoluteXY"
QT_MOC_LITERAL(20, 177, 1), // "x"
QT_MOC_LITERAL(21, 179, 1), // "y"
QT_MOC_LITERAL(22, 181, 15), // "ACTIONS::action"
QT_MOC_LITERAL(23, 197, 3), // "act"
QT_MOC_LITERAL(24, 201, 14), // "MoveRelativeXY"
QT_MOC_LITERAL(25, 216, 13), // "MoveAbsoluteZ"
QT_MOC_LITERAL(26, 230, 1), // "z"
QT_MOC_LITERAL(27, 232, 13), // "MoveRelativeZ"
QT_MOC_LITERAL(28, 246, 11), // "stopMotionZ"
QT_MOC_LITERAL(29, 258, 13), // "SendCommandXY"
QT_MOC_LITERAL(30, 272, 3), // "cmd"
QT_MOC_LITERAL(31, 276, 12), // "SendCommandZ"
QT_MOC_LITERAL(32, 289, 13), // "SetVelocityXY"
QT_MOC_LITERAL(33, 303, 4), // "velo"
QT_MOC_LITERAL(34, 308, 13), // "SetJoystickXY"
QT_MOC_LITERAL(35, 322, 2), // "on"
QT_MOC_LITERAL(36, 325, 10), // "SetKeypadZ"
QT_MOC_LITERAL(37, 336, 11), // "CalibrateXY"
QT_MOC_LITERAL(38, 348, 14), // "MeasureRangeXY"
QT_MOC_LITERAL(39, 363, 9), // "ConnectXY"
QT_MOC_LITERAL(40, 373, 12), // "DisconnectXY"
QT_MOC_LITERAL(41, 386, 8), // "ConnectZ"
QT_MOC_LITERAL(42, 395, 11), // "DisconnectZ"
QT_MOC_LITERAL(43, 407, 7), // "AbortXY"
QT_MOC_LITERAL(44, 415, 11), // "getCOMPORTS"
QT_MOC_LITERAL(45, 427, 26), // "moveToFiducialFromOverview"
QT_MOC_LITERAL(46, 454, 2), // "pt"
QT_MOC_LITERAL(47, 457, 26), // "createTransformationMatrix"
QT_MOC_LITERAL(48, 484, 7), // "topleft"
QT_MOC_LITERAL(49, 492, 8), // "topright"
QT_MOC_LITERAL(50, 501, 10), // "bottomleft"
QT_MOC_LITERAL(51, 512, 10), // "saveBackup"
QT_MOC_LITERAL(52, 523, 5), // "bLoad"
QT_MOC_LITERAL(53, 529, 10), // "LOGCONSOLE"
QT_MOC_LITERAL(54, 540, 7), // "strText"
QT_MOC_LITERAL(55, 548, 22), // "CONSOLECOLOURS::colour"
QT_MOC_LITERAL(56, 571, 3), // "col"
QT_MOC_LITERAL(57, 575, 19), // "SETFIDUCIALPOSITION"
QT_MOC_LITERAL(58, 595, 18), // "FIDUCIAL::position"
QT_MOC_LITERAL(59, 614, 5), // "index"
QT_MOC_LITERAL(60, 620, 12), // "LockFiducial"
QT_MOC_LITERAL(61, 633, 7), // "clicked"
QT_MOC_LITERAL(62, 641, 14), // "updateCOMPORTS"
QT_MOC_LITERAL(63, 656, 16), // "QVector<QString>"
QT_MOC_LITERAL(64, 673, 4), // "strs"
QT_MOC_LITERAL(65, 678, 24), // "on_btnCenterGrid_clicked"
QT_MOC_LITERAL(66, 703, 33), // "on_distanceThreshold_valueCha..."
QT_MOC_LITERAL(67, 737, 5), // "value"
QT_MOC_LITERAL(68, 743, 37), // "on_distanceBinsThreshold_valu..."
QT_MOC_LITERAL(69, 781, 27), // "on_numClusters_valueChanged"
QT_MOC_LITERAL(70, 809, 39), // "on_cboThresholdType_currentIn..."
QT_MOC_LITERAL(71, 849, 38), // "on_cboSamplingType_currentInd..."
QT_MOC_LITERAL(72, 888, 34), // "on_ThresholdMaxSlider_valueCh..."
QT_MOC_LITERAL(73, 923, 34), // "on_ThresholdMinSlider_valueCh..."
QT_MOC_LITERAL(74, 958, 33), // "on_sliderGridOffsetX_valueCha..."
QT_MOC_LITERAL(75, 992, 33), // "on_sliderGridOffsetY_valueCha..."
QT_MOC_LITERAL(76, 1026, 34), // "on_sliderGridSpacingX_valueCh..."
QT_MOC_LITERAL(77, 1061, 34), // "on_sliderGridSpacingY_valueCh..."
QT_MOC_LITERAL(78, 1096, 38), // "on_sliderBarcodeThreshold_val..."
QT_MOC_LITERAL(79, 1135, 34), // "on_chkAutoBarcodeThreshold_cl..."
QT_MOC_LITERAL(80, 1170, 7), // "checked"
QT_MOC_LITERAL(81, 1178, 30), // "on_chkProcessGrayscale_clicked"
QT_MOC_LITERAL(82, 1209, 31), // "on_spinGridOffsetX_valueChanged"
QT_MOC_LITERAL(83, 1241, 31), // "on_spinGridOffsetY_valueChanged"
QT_MOC_LITERAL(84, 1273, 32), // "on_spinGridSpacingX_valueChanged"
QT_MOC_LITERAL(85, 1306, 32), // "on_spinGridSpacingY_valueChanged"
QT_MOC_LITERAL(86, 1339, 35), // "on_editPixelSizeMicrons_textC..."
QT_MOC_LITERAL(87, 1375, 3), // "val"
QT_MOC_LITERAL(88, 1379, 37), // "on_spinSamplingDistanceX_valu..."
QT_MOC_LITERAL(89, 1417, 37), // "on_spinSamplingDistanceY_valu..."
QT_MOC_LITERAL(90, 1455, 35), // "on_spinSamplingOffsetX_valueC..."
QT_MOC_LITERAL(91, 1491, 35), // "on_spinSamplingOffsetY_valueC..."
QT_MOC_LITERAL(92, 1527, 28), // "on_btnDeleteFiducial_clicked"
QT_MOC_LITERAL(93, 1556, 25), // "on_btnLogFeedback_clicked"
QT_MOC_LITERAL(94, 1582, 37), // "on_spnTopLeft_Overview_X_valu..."
QT_MOC_LITERAL(95, 1620, 37), // "on_spnTopLeft_Overview_Y_valu..."
QT_MOC_LITERAL(96, 1658, 38), // "on_spnTopRight_Overview_X_val..."
QT_MOC_LITERAL(97, 1697, 38), // "on_spnTopRight_Overview_Y_val..."
QT_MOC_LITERAL(98, 1736, 40), // "on_spnBottomLeft_Overview_X_v..."
QT_MOC_LITERAL(99, 1777, 40), // "on_spnBottomLeft_Overview_Y_v..."
QT_MOC_LITERAL(100, 1818, 41), // "on_spnBottomRight_Overview_X_..."
QT_MOC_LITERAL(101, 1860, 41), // "on_spnBottomRight_Overview_Y_..."
QT_MOC_LITERAL(102, 1902, 39), // "on_spinXPositionAbsoluteXY_va..."
QT_MOC_LITERAL(103, 1942, 39), // "on_spinYPositionAbsoluteXY_va..."
QT_MOC_LITERAL(104, 1982, 39), // "on_spinXPositionRelativeXY_va..."
QT_MOC_LITERAL(105, 2022, 39), // "on_spinYPositionRelativeXY_va..."
QT_MOC_LITERAL(106, 2062, 43), // "on_spnTopLeft_Overview_Stage_..."
QT_MOC_LITERAL(107, 2106, 43), // "on_spnTopLeft_Overview_Stage_..."
QT_MOC_LITERAL(108, 2150, 39), // "on_spnTopLeft_Microscope_X_va..."
QT_MOC_LITERAL(109, 2190, 39), // "on_spnTopLeft_Microscope_Y_va..."
QT_MOC_LITERAL(110, 2230, 45), // "on_spnTopLeft_Microscope_Stag..."
QT_MOC_LITERAL(111, 2276, 45), // "on_spnTopLeft_Microscope_Stag..."
QT_MOC_LITERAL(112, 2322, 45), // "on_spnTopLeft_Microscope_Stag..."
QT_MOC_LITERAL(113, 2368, 40), // "on_spnTopRight_Microscope_X_v..."
QT_MOC_LITERAL(114, 2409, 40), // "on_spnTopRight_Microscope_Y_v..."
QT_MOC_LITERAL(115, 2450, 46), // "on_spnTopRight_Microscope_Sta..."
QT_MOC_LITERAL(116, 2497, 46), // "on_spnTopRight_Microscope_Sta..."
QT_MOC_LITERAL(117, 2544, 46), // "on_spnTopRight_Microscope_Sta..."
QT_MOC_LITERAL(118, 2591, 42), // "on_spnBottomLeft_Microscope_X..."
QT_MOC_LITERAL(119, 2634, 42), // "on_spnBottomLeft_Microscope_Y..."
QT_MOC_LITERAL(120, 2677, 48), // "on_spnBottomLeft_Microscope_S..."
QT_MOC_LITERAL(121, 2726, 48), // "on_spnBottomLeft_Microscope_S..."
QT_MOC_LITERAL(122, 2775, 48), // "on_spnBottomLeft_Microscope_S..."
QT_MOC_LITERAL(123, 2824, 43), // "on_spnBottomRight_Microscope_..."
QT_MOC_LITERAL(124, 2868, 43), // "on_spnBottomRight_Microscope_..."
QT_MOC_LITERAL(125, 2912, 49), // "on_spnBottomRight_Microscope_..."
QT_MOC_LITERAL(126, 2962, 49), // "on_spnBottomRight_Microscope_..."
QT_MOC_LITERAL(127, 3012, 49), // "on_spnBottomRight_Microscope_..."
QT_MOC_LITERAL(128, 3062, 30), // "on_spinFocusRange_valueChanged"
QT_MOC_LITERAL(129, 3093, 40), // "on_spinDefaultFocusPosition_v..."
QT_MOC_LITERAL(130, 3134, 35), // "on_spinCoarseFocusStep_valueC..."
QT_MOC_LITERAL(131, 3170, 33), // "on_spinFineFocusStep_valueCha..."
QT_MOC_LITERAL(132, 3204, 33), // "on_spinFocusFraction_valueCha..."
QT_MOC_LITERAL(133, 3238, 38), // "on_btnCalcTransformationMatri..."
QT_MOC_LITERAL(134, 3277, 30), // "on_spinVelocityXY_valueChanged"
QT_MOC_LITERAL(135, 3308, 28), // "on_btnMoveToFiducial_clicked"
QT_MOC_LITERAL(136, 3337, 28), // "on_btnMoveAbsoluteXY_clicked"
QT_MOC_LITERAL(137, 3366, 28), // "on_btnMoveRelativeXY_clicked"
QT_MOC_LITERAL(138, 3395, 27), // "on_btnSendCommandXY_clicked"
QT_MOC_LITERAL(139, 3423, 27), // "on_btnSetVelocityXY_clicked"
QT_MOC_LITERAL(140, 3451, 25), // "on_btnCalibrateXY_clicked"
QT_MOC_LITERAL(141, 3477, 28), // "on_btnMeasureRangeXY_clicked"
QT_MOC_LITERAL(142, 3506, 23), // "on_btnConnectXY_clicked"
QT_MOC_LITERAL(143, 3530, 26), // "on_btnDisconnectXY_clicked"
QT_MOC_LITERAL(144, 3557, 21), // "on_btnAbortXY_clicked"
QT_MOC_LITERAL(145, 3579, 34), // "on_btnMoveOverviewPosition_cl..."
QT_MOC_LITERAL(146, 3614, 30), // "on_btnAddFocusPosition_clicked"
QT_MOC_LITERAL(147, 3645, 33), // "on_btnRemoveFocusPosition_cli..."
QT_MOC_LITERAL(148, 3679, 27), // "on_btnMoveAbsoluteZ_clicked"
QT_MOC_LITERAL(149, 3707, 27), // "on_btnMoveRelativeZ_clicked"
QT_MOC_LITERAL(150, 3735, 17), // "on_btnUpZ_pressed"
QT_MOC_LITERAL(151, 3753, 19), // "on_btnDownZ_pressed"
QT_MOC_LITERAL(152, 3773, 18), // "on_btnUpZ_released"
QT_MOC_LITERAL(153, 3792, 20), // "on_btnDownZ_released"
QT_MOC_LITERAL(154, 3813, 26), // "on_btnSendCommandZ_clicked"
QT_MOC_LITERAL(155, 3840, 22), // "on_btnConnectZ_clicked"
QT_MOC_LITERAL(156, 3863, 25), // "on_btnDisconnectZ_clicked"
QT_MOC_LITERAL(157, 3889, 37), // "on_spinPositionAbsoluteZ_valu..."
QT_MOC_LITERAL(158, 3927, 37), // "on_spinPositionRelativeZ_valu..."
QT_MOC_LITERAL(159, 3965, 27), // "on_btnRestoreBackup_clicked"
QT_MOC_LITERAL(160, 3993, 24), // "on_btnSaveBackup_clicked"
QT_MOC_LITERAL(161, 4018, 40), // "on_cboSelectFiducial_currentI..."
QT_MOC_LITERAL(162, 4059, 32), // "on_cboBaudXY_currentIndexChanged"
QT_MOC_LITERAL(163, 4092, 40), // "on_cboFocusAlgorithm_currentI..."
QT_MOC_LITERAL(164, 4133, 32), // "on_NoClustersSlider_valueChanged"
QT_MOC_LITERAL(165, 4166, 30), // "on_ScoreThreshold_valueChanged"
QT_MOC_LITERAL(166, 4197, 35), // "on_AlgoComboBox_currentIndexC..."
QT_MOC_LITERAL(167, 4233, 27), // "on_chkAutoThreshold_clicked"
QT_MOC_LITERAL(168, 4261, 41), // "on_chkCV_CALIB_CB_ADAPTIVE_TH..."
QT_MOC_LITERAL(169, 4303, 41), // "on_chkCV_CALIB_CB_NORMALIZE_I..."
QT_MOC_LITERAL(170, 4345, 38), // "on_chkCV_CALIB_CB_FILTER_QUAD..."
QT_MOC_LITERAL(171, 4384, 30), // "on_btnProjectDirectory_clicked"
QT_MOC_LITERAL(172, 4415, 44), // "on_cboCalibrateAlgorithm_curr..."
QT_MOC_LITERAL(173, 4460, 33), // "on_chkCALIB_CB_FAST_CHECK_cli..."
QT_MOC_LITERAL(174, 4494, 33), // "on_chkCALIB_CB_CLUSTERING_cli..."
QT_MOC_LITERAL(175, 4528, 25), // "on_chkFixedAspect_clicked"
QT_MOC_LITERAL(176, 4554, 28), // "on_chkZeroDistortion_clicked"
QT_MOC_LITERAL(177, 4583, 37), // "on_chkFixPrincipalPointCenter..."
QT_MOC_LITERAL(178, 4621, 28), // "on_chkIntrinsicGuess_clicked"
QT_MOC_LITERAL(179, 4650, 28), // "on_chkFixFocalLength_clicked"
QT_MOC_LITERAL(180, 4679, 32), // "on_chkOptimiseFocusRange_clicked"
QT_MOC_LITERAL(181, 4712, 38), // "on_chkInterpolateFocusPositio..."
QT_MOC_LITERAL(182, 4751, 31), // "on_chkUseFocusThreshold_clicked"
QT_MOC_LITERAL(183, 4783, 33), // "on_chkUseCoarseFocusRange_cli..."
QT_MOC_LITERAL(184, 4817, 31), // "on_chkUseFineFocusRange_clicked"
QT_MOC_LITERAL(185, 4849, 25), // "on_chkCenterFocus_clicked"
QT_MOC_LITERAL(186, 4875, 38), // "on_chkUseRegisteredFocusPoint..."
QT_MOC_LITERAL(187, 4914, 32), // "on_chkShowBestFocusImage_clicked"
QT_MOC_LITERAL(188, 4947, 40), // "on_chkDetectTargetsWhileScann..."
QT_MOC_LITERAL(189, 4988, 31), // "on_chkCorrectBackGround_clicked"
QT_MOC_LITERAL(190, 5020, 33), // "on_spinWaveletLevels_valueCha..."
QT_MOC_LITERAL(191, 5054, 30), // "on_spinItemsInRow_valueChanged"
QT_MOC_LITERAL(192, 5085, 33), // "on_spinItemsInColumn_valueCha..."
QT_MOC_LITERAL(193, 5119, 30), // "on_spinSizeSquare_valueChanged"
QT_MOC_LITERAL(194, 5150, 40), // "on_huMomentSimilaritySlider_v..."
QT_MOC_LITERAL(195, 5191, 35), // "on_spinAspectTolerance_valueC..."
QT_MOC_LITERAL(196, 5227, 31), // "on_scoreRegionArea_valueChanged"
QT_MOC_LITERAL(197, 5259, 26), // "on_chkLockFiducial_clicked"
QT_MOC_LITERAL(198, 5286, 29), // "on_chkPaddTargetImage_clicked"
QT_MOC_LITERAL(199, 5316, 41), // "on_spOverviewLensFocalLength_..."
QT_MOC_LITERAL(200, 5358, 43), // "on_spMicroscopeLensFocalLengt..."
QT_MOC_LITERAL(201, 5402, 25), // "on_chkDisplayGrid_clicked"
QT_MOC_LITERAL(202, 5428, 24), // "on_chkJoystickOn_clicked"
QT_MOC_LITERAL(203, 5453, 22), // "on_chkKeypadOn_clicked"
QT_MOC_LITERAL(204, 5476, 38), // "on_cboActiveCamera_currentInd..."
QT_MOC_LITERAL(205, 5515, 20), // "on_buttonBox_clicked"
QT_MOC_LITERAL(206, 5536, 16), // "QAbstractButton*"
QT_MOC_LITERAL(207, 5553, 6), // "button"
QT_MOC_LITERAL(208, 5560, 26), // "on_btnSelectColour_clicked"
QT_MOC_LITERAL(209, 5587, 23), // "on_editName_textChanged"
QT_MOC_LITERAL(210, 5611, 28), // "on_editInstitute_textChanged"
QT_MOC_LITERAL(211, 5640, 30), // "on_editProjectName_textChanged"
QT_MOC_LITERAL(212, 5671, 28), // "on_editProjectID_textChanged"
QT_MOC_LITERAL(213, 5700, 26), // "on_editVersion_textChanged"
QT_MOC_LITERAL(214, 5727, 30), // "on_editDescription_textChanged"
QT_MOC_LITERAL(215, 5758, 36), // "on_editSampleDescription_text..."
QT_MOC_LITERAL(216, 5795, 33), // "on_editFilenamePrefix_textCha..."
QT_MOC_LITERAL(217, 5829, 26), // "on_editBarcode_textChanged"
QT_MOC_LITERAL(218, 5856, 26), // "on_projectDate_dateChanged"
QT_MOC_LITERAL(219, 5883, 4), // "date"
QT_MOC_LITERAL(220, 5888, 39), // "on_editProjectDirectoryName_t..."
QT_MOC_LITERAL(221, 5928, 39), // "on_lineEditOverviewCameraSN_t..."
QT_MOC_LITERAL(222, 5968, 41) // "on_lineEditMicroscopeCameraSN..."

    },
    "SettingsDialog\0sendSettings\0\0"
    "updatePaddTarget\0bPaddTargetImage\0"
    "levels\0setGrid\0bChecked\0offX\0offY\0"
    "spaceX\0spaceY\0colour\0logFeedback\0score\0"
    "name\0email\0institute\0desc\0MoveAbsoluteXY\0"
    "x\0y\0ACTIONS::action\0act\0MoveRelativeXY\0"
    "MoveAbsoluteZ\0z\0MoveRelativeZ\0stopMotionZ\0"
    "SendCommandXY\0cmd\0SendCommandZ\0"
    "SetVelocityXY\0velo\0SetJoystickXY\0on\0"
    "SetKeypadZ\0CalibrateXY\0MeasureRangeXY\0"
    "ConnectXY\0DisconnectXY\0ConnectZ\0"
    "DisconnectZ\0AbortXY\0getCOMPORTS\0"
    "moveToFiducialFromOverview\0pt\0"
    "createTransformationMatrix\0topleft\0"
    "topright\0bottomleft\0saveBackup\0bLoad\0"
    "LOGCONSOLE\0strText\0CONSOLECOLOURS::colour\0"
    "col\0SETFIDUCIALPOSITION\0FIDUCIAL::position\0"
    "index\0LockFiducial\0clicked\0updateCOMPORTS\0"
    "QVector<QString>\0strs\0on_btnCenterGrid_clicked\0"
    "on_distanceThreshold_valueChanged\0"
    "value\0on_distanceBinsThreshold_valueChanged\0"
    "on_numClusters_valueChanged\0"
    "on_cboThresholdType_currentIndexChanged\0"
    "on_cboSamplingType_currentIndexChanged\0"
    "on_ThresholdMaxSlider_valueChanged\0"
    "on_ThresholdMinSlider_valueChanged\0"
    "on_sliderGridOffsetX_valueChanged\0"
    "on_sliderGridOffsetY_valueChanged\0"
    "on_sliderGridSpacingX_valueChanged\0"
    "on_sliderGridSpacingY_valueChanged\0"
    "on_sliderBarcodeThreshold_valueChanged\0"
    "on_chkAutoBarcodeThreshold_clicked\0"
    "checked\0on_chkProcessGrayscale_clicked\0"
    "on_spinGridOffsetX_valueChanged\0"
    "on_spinGridOffsetY_valueChanged\0"
    "on_spinGridSpacingX_valueChanged\0"
    "on_spinGridSpacingY_valueChanged\0"
    "on_editPixelSizeMicrons_textChanged\0"
    "val\0on_spinSamplingDistanceX_valueChanged\0"
    "on_spinSamplingDistanceY_valueChanged\0"
    "on_spinSamplingOffsetX_valueChanged\0"
    "on_spinSamplingOffsetY_valueChanged\0"
    "on_btnDeleteFiducial_clicked\0"
    "on_btnLogFeedback_clicked\0"
    "on_spnTopLeft_Overview_X_valueChanged\0"
    "on_spnTopLeft_Overview_Y_valueChanged\0"
    "on_spnTopRight_Overview_X_valueChanged\0"
    "on_spnTopRight_Overview_Y_valueChanged\0"
    "on_spnBottomLeft_Overview_X_valueChanged\0"
    "on_spnBottomLeft_Overview_Y_valueChanged\0"
    "on_spnBottomRight_Overview_X_valueChanged\0"
    "on_spnBottomRight_Overview_Y_valueChanged\0"
    "on_spinXPositionAbsoluteXY_valueChanged\0"
    "on_spinYPositionAbsoluteXY_valueChanged\0"
    "on_spinXPositionRelativeXY_valueChanged\0"
    "on_spinYPositionRelativeXY_valueChanged\0"
    "on_spnTopLeft_Overview_Stage_X_valueChanged\0"
    "on_spnTopLeft_Overview_Stage_Y_valueChanged\0"
    "on_spnTopLeft_Microscope_X_valueChanged\0"
    "on_spnTopLeft_Microscope_Y_valueChanged\0"
    "on_spnTopLeft_Microscope_Stage_X_valueChanged\0"
    "on_spnTopLeft_Microscope_Stage_Y_valueChanged\0"
    "on_spnTopLeft_Microscope_Stage_Z_valueChanged\0"
    "on_spnTopRight_Microscope_X_valueChanged\0"
    "on_spnTopRight_Microscope_Y_valueChanged\0"
    "on_spnTopRight_Microscope_Stage_X_valueChanged\0"
    "on_spnTopRight_Microscope_Stage_Y_valueChanged\0"
    "on_spnTopRight_Microscope_Stage_Z_valueChanged\0"
    "on_spnBottomLeft_Microscope_X_valueChanged\0"
    "on_spnBottomLeft_Microscope_Y_valueChanged\0"
    "on_spnBottomLeft_Microscope_Stage_X_valueChanged\0"
    "on_spnBottomLeft_Microscope_Stage_Y_valueChanged\0"
    "on_spnBottomLeft_Microscope_Stage_Z_valueChanged\0"
    "on_spnBottomRight_Microscope_X_valueChanged\0"
    "on_spnBottomRight_Microscope_Y_valueChanged\0"
    "on_spnBottomRight_Microscope_Stage_X_valueChanged\0"
    "on_spnBottomRight_Microscope_Stage_Y_valueChanged\0"
    "on_spnBottomRight_Microscope_Stage_Z_valueChanged\0"
    "on_spinFocusRange_valueChanged\0"
    "on_spinDefaultFocusPosition_valueChanged\0"
    "on_spinCoarseFocusStep_valueChanged\0"
    "on_spinFineFocusStep_valueChanged\0"
    "on_spinFocusFraction_valueChanged\0"
    "on_btnCalcTransformationMatrix_clicked\0"
    "on_spinVelocityXY_valueChanged\0"
    "on_btnMoveToFiducial_clicked\0"
    "on_btnMoveAbsoluteXY_clicked\0"
    "on_btnMoveRelativeXY_clicked\0"
    "on_btnSendCommandXY_clicked\0"
    "on_btnSetVelocityXY_clicked\0"
    "on_btnCalibrateXY_clicked\0"
    "on_btnMeasureRangeXY_clicked\0"
    "on_btnConnectXY_clicked\0"
    "on_btnDisconnectXY_clicked\0"
    "on_btnAbortXY_clicked\0"
    "on_btnMoveOverviewPosition_clicked\0"
    "on_btnAddFocusPosition_clicked\0"
    "on_btnRemoveFocusPosition_clicked\0"
    "on_btnMoveAbsoluteZ_clicked\0"
    "on_btnMoveRelativeZ_clicked\0"
    "on_btnUpZ_pressed\0on_btnDownZ_pressed\0"
    "on_btnUpZ_released\0on_btnDownZ_released\0"
    "on_btnSendCommandZ_clicked\0"
    "on_btnConnectZ_clicked\0on_btnDisconnectZ_clicked\0"
    "on_spinPositionAbsoluteZ_valueChanged\0"
    "on_spinPositionRelativeZ_valueChanged\0"
    "on_btnRestoreBackup_clicked\0"
    "on_btnSaveBackup_clicked\0"
    "on_cboSelectFiducial_currentIndexChanged\0"
    "on_cboBaudXY_currentIndexChanged\0"
    "on_cboFocusAlgorithm_currentIndexChanged\0"
    "on_NoClustersSlider_valueChanged\0"
    "on_ScoreThreshold_valueChanged\0"
    "on_AlgoComboBox_currentIndexChanged\0"
    "on_chkAutoThreshold_clicked\0"
    "on_chkCV_CALIB_CB_ADAPTIVE_THRESH_clicked\0"
    "on_chkCV_CALIB_CB_NORMALIZE_IMAGE_clicked\0"
    "on_chkCV_CALIB_CB_FILTER_QUADS_clicked\0"
    "on_btnProjectDirectory_clicked\0"
    "on_cboCalibrateAlgorithm_currentIndexChanged\0"
    "on_chkCALIB_CB_FAST_CHECK_clicked\0"
    "on_chkCALIB_CB_CLUSTERING_clicked\0"
    "on_chkFixedAspect_clicked\0"
    "on_chkZeroDistortion_clicked\0"
    "on_chkFixPrincipalPointCenter_clicked\0"
    "on_chkIntrinsicGuess_clicked\0"
    "on_chkFixFocalLength_clicked\0"
    "on_chkOptimiseFocusRange_clicked\0"
    "on_chkInterpolateFocusPosition_clicked\0"
    "on_chkUseFocusThreshold_clicked\0"
    "on_chkUseCoarseFocusRange_clicked\0"
    "on_chkUseFineFocusRange_clicked\0"
    "on_chkCenterFocus_clicked\0"
    "on_chkUseRegisteredFocusPoints_clicked\0"
    "on_chkShowBestFocusImage_clicked\0"
    "on_chkDetectTargetsWhileScanning_clicked\0"
    "on_chkCorrectBackGround_clicked\0"
    "on_spinWaveletLevels_valueChanged\0"
    "on_spinItemsInRow_valueChanged\0"
    "on_spinItemsInColumn_valueChanged\0"
    "on_spinSizeSquare_valueChanged\0"
    "on_huMomentSimilaritySlider_valueChanged\0"
    "on_spinAspectTolerance_valueChanged\0"
    "on_scoreRegionArea_valueChanged\0"
    "on_chkLockFiducial_clicked\0"
    "on_chkPaddTargetImage_clicked\0"
    "on_spOverviewLensFocalLength_valueChanged\0"
    "on_spMicroscopeLensFocalLength_valueChanged\0"
    "on_chkDisplayGrid_clicked\0"
    "on_chkJoystickOn_clicked\0"
    "on_chkKeypadOn_clicked\0"
    "on_cboActiveCamera_currentIndexChanged\0"
    "on_buttonBox_clicked\0QAbstractButton*\0"
    "button\0on_btnSelectColour_clicked\0"
    "on_editName_textChanged\0"
    "on_editInstitute_textChanged\0"
    "on_editProjectName_textChanged\0"
    "on_editProjectID_textChanged\0"
    "on_editVersion_textChanged\0"
    "on_editDescription_textChanged\0"
    "on_editSampleDescription_textChanged\0"
    "on_editFilenamePrefix_textChanged\0"
    "on_editBarcode_textChanged\0"
    "on_projectDate_dateChanged\0date\0"
    "on_editProjectDirectoryName_textChanged\0"
    "on_lineEditOverviewCameraSN_textChanged\0"
    "on_lineEditMicroscopeCameraSN_textChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SettingsDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
     181,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      28,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  919,    2, 0x06 /* Public */,
       3,    2,  920,    2, 0x06 /* Public */,
       6,    6,  925,    2, 0x06 /* Public */,
      13,    5,  938,    2, 0x06 /* Public */,
      19,    3,  949,    2, 0x06 /* Public */,
      24,    3,  956,    2, 0x06 /* Public */,
      25,    2,  963,    2, 0x06 /* Public */,
      27,    2,  968,    2, 0x06 /* Public */,
      28,    1,  973,    2, 0x06 /* Public */,
      29,    1,  976,    2, 0x06 /* Public */,
      31,    1,  979,    2, 0x06 /* Public */,
      32,    1,  982,    2, 0x06 /* Public */,
      34,    1,  985,    2, 0x06 /* Public */,
      36,    1,  988,    2, 0x06 /* Public */,
      37,    0,  991,    2, 0x06 /* Public */,
      38,    0,  992,    2, 0x06 /* Public */,
      39,    0,  993,    2, 0x06 /* Public */,
      40,    0,  994,    2, 0x06 /* Public */,
      41,    0,  995,    2, 0x06 /* Public */,
      42,    0,  996,    2, 0x06 /* Public */,
      43,    0,  997,    2, 0x06 /* Public */,
      44,    0,  998,    2, 0x06 /* Public */,
      45,    1,  999,    2, 0x06 /* Public */,
      47,    3, 1002,    2, 0x06 /* Public */,
      51,    1, 1009,    2, 0x06 /* Public */,
      53,    2, 1012,    2, 0x06 /* Public */,
      57,    1, 1017,    2, 0x06 /* Public */,
      60,    1, 1020,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      62,    1, 1023,    2, 0x0a /* Public */,
      65,    0, 1026,    2, 0x08 /* Private */,
      66,    1, 1027,    2, 0x08 /* Private */,
      68,    1, 1030,    2, 0x08 /* Private */,
      69,    1, 1033,    2, 0x08 /* Private */,
      70,    1, 1036,    2, 0x08 /* Private */,
      71,    1, 1039,    2, 0x08 /* Private */,
      72,    1, 1042,    2, 0x08 /* Private */,
      73,    1, 1045,    2, 0x08 /* Private */,
      74,    1, 1048,    2, 0x08 /* Private */,
      75,    1, 1051,    2, 0x08 /* Private */,
      76,    1, 1054,    2, 0x08 /* Private */,
      77,    1, 1057,    2, 0x08 /* Private */,
      78,    1, 1060,    2, 0x08 /* Private */,
      79,    1, 1063,    2, 0x08 /* Private */,
      81,    1, 1066,    2, 0x08 /* Private */,
      82,    1, 1069,    2, 0x08 /* Private */,
      83,    1, 1072,    2, 0x08 /* Private */,
      84,    1, 1075,    2, 0x08 /* Private */,
      85,    1, 1078,    2, 0x08 /* Private */,
      86,    1, 1081,    2, 0x08 /* Private */,
      88,    1, 1084,    2, 0x08 /* Private */,
      89,    1, 1087,    2, 0x08 /* Private */,
      90,    1, 1090,    2, 0x08 /* Private */,
      91,    1, 1093,    2, 0x08 /* Private */,
      92,    0, 1096,    2, 0x08 /* Private */,
      93,    0, 1097,    2, 0x08 /* Private */,
      94,    1, 1098,    2, 0x08 /* Private */,
      95,    1, 1101,    2, 0x08 /* Private */,
      96,    1, 1104,    2, 0x08 /* Private */,
      97,    1, 1107,    2, 0x08 /* Private */,
      98,    1, 1110,    2, 0x08 /* Private */,
      99,    1, 1113,    2, 0x08 /* Private */,
     100,    1, 1116,    2, 0x08 /* Private */,
     101,    1, 1119,    2, 0x08 /* Private */,
     102,    1, 1122,    2, 0x08 /* Private */,
     103,    1, 1125,    2, 0x08 /* Private */,
     104,    1, 1128,    2, 0x08 /* Private */,
     105,    1, 1131,    2, 0x08 /* Private */,
     106,    1, 1134,    2, 0x08 /* Private */,
     107,    1, 1137,    2, 0x08 /* Private */,
     108,    1, 1140,    2, 0x08 /* Private */,
     109,    1, 1143,    2, 0x08 /* Private */,
     110,    1, 1146,    2, 0x08 /* Private */,
     111,    1, 1149,    2, 0x08 /* Private */,
     112,    1, 1152,    2, 0x08 /* Private */,
     113,    1, 1155,    2, 0x08 /* Private */,
     114,    1, 1158,    2, 0x08 /* Private */,
     115,    1, 1161,    2, 0x08 /* Private */,
     116,    1, 1164,    2, 0x08 /* Private */,
     117,    1, 1167,    2, 0x08 /* Private */,
     118,    1, 1170,    2, 0x08 /* Private */,
     119,    1, 1173,    2, 0x08 /* Private */,
     120,    1, 1176,    2, 0x08 /* Private */,
     121,    1, 1179,    2, 0x08 /* Private */,
     122,    1, 1182,    2, 0x08 /* Private */,
     123,    1, 1185,    2, 0x08 /* Private */,
     124,    1, 1188,    2, 0x08 /* Private */,
     125,    1, 1191,    2, 0x08 /* Private */,
     126,    1, 1194,    2, 0x08 /* Private */,
     127,    1, 1197,    2, 0x08 /* Private */,
     128,    1, 1200,    2, 0x08 /* Private */,
     129,    1, 1203,    2, 0x08 /* Private */,
     130,    1, 1206,    2, 0x08 /* Private */,
     131,    1, 1209,    2, 0x08 /* Private */,
     132,    1, 1212,    2, 0x08 /* Private */,
     133,    0, 1215,    2, 0x08 /* Private */,
     134,    1, 1216,    2, 0x08 /* Private */,
     135,    0, 1219,    2, 0x08 /* Private */,
     136,    0, 1220,    2, 0x08 /* Private */,
     137,    0, 1221,    2, 0x08 /* Private */,
     138,    0, 1222,    2, 0x08 /* Private */,
     139,    0, 1223,    2, 0x08 /* Private */,
     140,    0, 1224,    2, 0x08 /* Private */,
     141,    0, 1225,    2, 0x08 /* Private */,
     142,    0, 1226,    2, 0x08 /* Private */,
     143,    0, 1227,    2, 0x08 /* Private */,
     144,    0, 1228,    2, 0x08 /* Private */,
     145,    0, 1229,    2, 0x08 /* Private */,
     146,    0, 1230,    2, 0x08 /* Private */,
     147,    0, 1231,    2, 0x08 /* Private */,
     148,    0, 1232,    2, 0x08 /* Private */,
     149,    0, 1233,    2, 0x08 /* Private */,
     150,    0, 1234,    2, 0x08 /* Private */,
     151,    0, 1235,    2, 0x08 /* Private */,
     152,    0, 1236,    2, 0x08 /* Private */,
     153,    0, 1237,    2, 0x08 /* Private */,
     154,    0, 1238,    2, 0x08 /* Private */,
     155,    0, 1239,    2, 0x08 /* Private */,
     156,    0, 1240,    2, 0x08 /* Private */,
     157,    1, 1241,    2, 0x08 /* Private */,
     158,    1, 1244,    2, 0x08 /* Private */,
     159,    0, 1247,    2, 0x08 /* Private */,
     160,    0, 1248,    2, 0x08 /* Private */,
     161,    1, 1249,    2, 0x08 /* Private */,
     162,    1, 1252,    2, 0x08 /* Private */,
     163,    1, 1255,    2, 0x08 /* Private */,
     164,    1, 1258,    2, 0x08 /* Private */,
     165,    1, 1261,    2, 0x08 /* Private */,
     166,    1, 1264,    2, 0x08 /* Private */,
     167,    1, 1267,    2, 0x08 /* Private */,
     168,    1, 1270,    2, 0x08 /* Private */,
     169,    1, 1273,    2, 0x08 /* Private */,
     170,    1, 1276,    2, 0x08 /* Private */,
     171,    1, 1279,    2, 0x08 /* Private */,
     172,    1, 1282,    2, 0x08 /* Private */,
     173,    1, 1285,    2, 0x08 /* Private */,
     174,    1, 1288,    2, 0x08 /* Private */,
     175,    1, 1291,    2, 0x08 /* Private */,
     176,    1, 1294,    2, 0x08 /* Private */,
     177,    1, 1297,    2, 0x08 /* Private */,
     178,    1, 1300,    2, 0x08 /* Private */,
     179,    1, 1303,    2, 0x08 /* Private */,
     180,    1, 1306,    2, 0x08 /* Private */,
     181,    1, 1309,    2, 0x08 /* Private */,
     182,    1, 1312,    2, 0x08 /* Private */,
     183,    1, 1315,    2, 0x08 /* Private */,
     184,    1, 1318,    2, 0x08 /* Private */,
     185,    1, 1321,    2, 0x08 /* Private */,
     186,    1, 1324,    2, 0x08 /* Private */,
     187,    1, 1327,    2, 0x08 /* Private */,
     188,    1, 1330,    2, 0x08 /* Private */,
     189,    1, 1333,    2, 0x08 /* Private */,
     190,    1, 1336,    2, 0x08 /* Private */,
     191,    1, 1339,    2, 0x08 /* Private */,
     192,    1, 1342,    2, 0x08 /* Private */,
     193,    1, 1345,    2, 0x08 /* Private */,
     194,    1, 1348,    2, 0x08 /* Private */,
     195,    1, 1351,    2, 0x08 /* Private */,
     196,    1, 1354,    2, 0x08 /* Private */,
     197,    1, 1357,    2, 0x08 /* Private */,
     198,    1, 1360,    2, 0x08 /* Private */,
     199,    1, 1363,    2, 0x08 /* Private */,
     200,    1, 1366,    2, 0x08 /* Private */,
     201,    1, 1369,    2, 0x08 /* Private */,
     202,    1, 1372,    2, 0x08 /* Private */,
     203,    1, 1375,    2, 0x08 /* Private */,
     204,    1, 1378,    2, 0x08 /* Private */,
     205,    1, 1381,    2, 0x08 /* Private */,
     208,    0, 1384,    2, 0x08 /* Private */,
     209,    1, 1385,    2, 0x08 /* Private */,
     210,    1, 1388,    2, 0x08 /* Private */,
     211,    1, 1391,    2, 0x08 /* Private */,
     212,    1, 1394,    2, 0x08 /* Private */,
     213,    1, 1397,    2, 0x08 /* Private */,
     214,    1, 1400,    2, 0x08 /* Private */,
     215,    1, 1403,    2, 0x08 /* Private */,
     216,    1, 1406,    2, 0x08 /* Private */,
     217,    1, 1409,    2, 0x08 /* Private */,
     218,    1, 1412,    2, 0x08 /* Private */,
     220,    1, 1415,    2, 0x08 /* Private */,
     221,    1, 1418,    2, 0x08 /* Private */,
     222,    1, 1421,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool, QMetaType::Int,    4,    5,
    QMetaType::Void, QMetaType::Bool, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::QColor,    7,    8,    9,   10,   11,   12,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   14,   15,   16,   17,   18,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, 0x80000000 | 22,   20,   21,   23,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, 0x80000000 | 22,   20,   21,   23,
    QMetaType::Void, QMetaType::Double, 0x80000000 | 22,   26,   23,
    QMetaType::Void, QMetaType::Double, 0x80000000 | 22,   26,   23,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void, QMetaType::QString,   30,
    QMetaType::Void, QMetaType::QString,   30,
    QMetaType::Void, QMetaType::Double,   33,
    QMetaType::Void, QMetaType::Bool,   35,
    QMetaType::Void, QMetaType::Bool,   35,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   46,
    QMetaType::Void, QMetaType::QVector3D, QMetaType::QVector3D, QMetaType::QVector3D,   48,   49,   50,
    QMetaType::Void, QMetaType::Bool,   52,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 55,   54,   56,
    QMetaType::Void, 0x80000000 | 58,   59,
    QMetaType::Void, QMetaType::Bool,   61,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 63,   64,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Void, QMetaType::Int,   59,
    QMetaType::Void, QMetaType::Int,   59,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Void, QMetaType::Bool,   80,
    QMetaType::Void, QMetaType::Bool,   80,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::QString,   87,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   67,
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
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Void, QMetaType::Int,   59,
    QMetaType::Void, QMetaType::Bool,   80,
    QMetaType::Void, QMetaType::Bool,   80,
    QMetaType::Void, QMetaType::Bool,   80,
    QMetaType::Void, QMetaType::Bool,   80,
    QMetaType::Void, QMetaType::Bool,   80,
    QMetaType::Void, QMetaType::Int,   59,
    QMetaType::Void, QMetaType::Bool,   80,
    QMetaType::Void, QMetaType::Bool,   80,
    QMetaType::Void, QMetaType::Bool,   80,
    QMetaType::Void, QMetaType::Bool,   80,
    QMetaType::Void, QMetaType::Bool,   80,
    QMetaType::Void, QMetaType::Bool,   80,
    QMetaType::Void, QMetaType::Bool,   80,
    QMetaType::Void, QMetaType::Bool,   80,
    QMetaType::Void, QMetaType::Bool,   80,
    QMetaType::Void, QMetaType::Bool,   80,
    QMetaType::Void, QMetaType::Bool,   80,
    QMetaType::Void, QMetaType::Bool,   80,
    QMetaType::Void, QMetaType::Bool,   80,
    QMetaType::Void, QMetaType::Bool,   80,
    QMetaType::Void, QMetaType::Bool,   80,
    QMetaType::Void, QMetaType::Bool,   80,
    QMetaType::Void, QMetaType::Bool,   80,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Void, QMetaType::Double,   67,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Void, QMetaType::Bool,   80,
    QMetaType::Void, QMetaType::Bool,   80,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Void, QMetaType::Bool,   67,
    QMetaType::Void, QMetaType::Bool,   35,
    QMetaType::Void, QMetaType::Bool,   35,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Void, 0x80000000 | 206,  207,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   87,
    QMetaType::Void, QMetaType::QString,   87,
    QMetaType::Void, QMetaType::QString,   87,
    QMetaType::Void, QMetaType::QString,   87,
    QMetaType::Void, QMetaType::QString,   87,
    QMetaType::Void, QMetaType::QString,   87,
    QMetaType::Void, QMetaType::QString,   87,
    QMetaType::Void, QMetaType::QString,   87,
    QMetaType::Void, QMetaType::QString,   87,
    QMetaType::Void, QMetaType::QDate,  219,
    QMetaType::Void, QMetaType::QString,   87,
    QMetaType::Void, QMetaType::QString,   87,
    QMetaType::Void, QMetaType::QString,   87,

       0        // eod
};

void SettingsDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SettingsDialog *_t = static_cast<SettingsDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendSettings(); break;
        case 1: _t->updatePaddTarget((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->setGrid((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5])),(*reinterpret_cast< QColor(*)>(_a[6]))); break;
        case 3: _t->logFeedback((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 4: _t->MoveAbsoluteXY((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< ACTIONS::action(*)>(_a[3]))); break;
        case 5: _t->MoveRelativeXY((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< ACTIONS::action(*)>(_a[3]))); break;
        case 6: _t->MoveAbsoluteZ((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< ACTIONS::action(*)>(_a[2]))); break;
        case 7: _t->MoveRelativeZ((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< ACTIONS::action(*)>(_a[2]))); break;
        case 8: _t->stopMotionZ((*reinterpret_cast< ACTIONS::action(*)>(_a[1]))); break;
        case 9: _t->SendCommandXY((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->SendCommandZ((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->SetVelocityXY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->SetJoystickXY((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->SetKeypadZ((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->CalibrateXY(); break;
        case 15: _t->MeasureRangeXY(); break;
        case 16: _t->ConnectXY(); break;
        case 17: _t->DisconnectXY(); break;
        case 18: _t->ConnectZ(); break;
        case 19: _t->DisconnectZ(); break;
        case 20: _t->AbortXY(); break;
        case 21: _t->getCOMPORTS(); break;
        case 22: _t->moveToFiducialFromOverview((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 23: _t->createTransformationMatrix((*reinterpret_cast< QVector3D(*)>(_a[1])),(*reinterpret_cast< QVector3D(*)>(_a[2])),(*reinterpret_cast< QVector3D(*)>(_a[3]))); break;
        case 24: _t->saveBackup((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 25: _t->LOGCONSOLE((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< CONSOLECOLOURS::colour(*)>(_a[2]))); break;
        case 26: _t->SETFIDUCIALPOSITION((*reinterpret_cast< FIDUCIAL::position(*)>(_a[1]))); break;
        case 27: _t->LockFiducial((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 28: _t->updateCOMPORTS((*reinterpret_cast< QVector<QString>(*)>(_a[1]))); break;
        case 29: _t->on_btnCenterGrid_clicked(); break;
        case 30: _t->on_distanceThreshold_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 31: _t->on_distanceBinsThreshold_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: _t->on_numClusters_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 33: _t->on_cboThresholdType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 34: _t->on_cboSamplingType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 35: _t->on_ThresholdMaxSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 36: _t->on_ThresholdMinSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 37: _t->on_sliderGridOffsetX_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 38: _t->on_sliderGridOffsetY_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 39: _t->on_sliderGridSpacingX_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 40: _t->on_sliderGridSpacingY_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 41: _t->on_sliderBarcodeThreshold_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 42: _t->on_chkAutoBarcodeThreshold_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 43: _t->on_chkProcessGrayscale_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 44: _t->on_spinGridOffsetX_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 45: _t->on_spinGridOffsetY_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 46: _t->on_spinGridSpacingX_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 47: _t->on_spinGridSpacingY_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 48: _t->on_editPixelSizeMicrons_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 49: _t->on_spinSamplingDistanceX_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 50: _t->on_spinSamplingDistanceY_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 51: _t->on_spinSamplingOffsetX_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 52: _t->on_spinSamplingOffsetY_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 53: _t->on_btnDeleteFiducial_clicked(); break;
        case 54: _t->on_btnLogFeedback_clicked(); break;
        case 55: _t->on_spnTopLeft_Overview_X_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 56: _t->on_spnTopLeft_Overview_Y_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 57: _t->on_spnTopRight_Overview_X_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 58: _t->on_spnTopRight_Overview_Y_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 59: _t->on_spnBottomLeft_Overview_X_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 60: _t->on_spnBottomLeft_Overview_Y_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 61: _t->on_spnBottomRight_Overview_X_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 62: _t->on_spnBottomRight_Overview_Y_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 63: _t->on_spinXPositionAbsoluteXY_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 64: _t->on_spinYPositionAbsoluteXY_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 65: _t->on_spinXPositionRelativeXY_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 66: _t->on_spinYPositionRelativeXY_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 67: _t->on_spnTopLeft_Overview_Stage_X_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 68: _t->on_spnTopLeft_Overview_Stage_Y_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 69: _t->on_spnTopLeft_Microscope_X_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 70: _t->on_spnTopLeft_Microscope_Y_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 71: _t->on_spnTopLeft_Microscope_Stage_X_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 72: _t->on_spnTopLeft_Microscope_Stage_Y_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 73: _t->on_spnTopLeft_Microscope_Stage_Z_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 74: _t->on_spnTopRight_Microscope_X_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 75: _t->on_spnTopRight_Microscope_Y_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 76: _t->on_spnTopRight_Microscope_Stage_X_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 77: _t->on_spnTopRight_Microscope_Stage_Y_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 78: _t->on_spnTopRight_Microscope_Stage_Z_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 79: _t->on_spnBottomLeft_Microscope_X_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 80: _t->on_spnBottomLeft_Microscope_Y_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 81: _t->on_spnBottomLeft_Microscope_Stage_X_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 82: _t->on_spnBottomLeft_Microscope_Stage_Y_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 83: _t->on_spnBottomLeft_Microscope_Stage_Z_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 84: _t->on_spnBottomRight_Microscope_X_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 85: _t->on_spnBottomRight_Microscope_Y_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 86: _t->on_spnBottomRight_Microscope_Stage_X_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 87: _t->on_spnBottomRight_Microscope_Stage_Y_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 88: _t->on_spnBottomRight_Microscope_Stage_Z_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 89: _t->on_spinFocusRange_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 90: _t->on_spinDefaultFocusPosition_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 91: _t->on_spinCoarseFocusStep_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 92: _t->on_spinFineFocusStep_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 93: _t->on_spinFocusFraction_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 94: _t->on_btnCalcTransformationMatrix_clicked(); break;
        case 95: _t->on_spinVelocityXY_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 96: _t->on_btnMoveToFiducial_clicked(); break;
        case 97: _t->on_btnMoveAbsoluteXY_clicked(); break;
        case 98: _t->on_btnMoveRelativeXY_clicked(); break;
        case 99: _t->on_btnSendCommandXY_clicked(); break;
        case 100: _t->on_btnSetVelocityXY_clicked(); break;
        case 101: _t->on_btnCalibrateXY_clicked(); break;
        case 102: _t->on_btnMeasureRangeXY_clicked(); break;
        case 103: _t->on_btnConnectXY_clicked(); break;
        case 104: _t->on_btnDisconnectXY_clicked(); break;
        case 105: _t->on_btnAbortXY_clicked(); break;
        case 106: _t->on_btnMoveOverviewPosition_clicked(); break;
        case 107: _t->on_btnAddFocusPosition_clicked(); break;
        case 108: _t->on_btnRemoveFocusPosition_clicked(); break;
        case 109: _t->on_btnMoveAbsoluteZ_clicked(); break;
        case 110: _t->on_btnMoveRelativeZ_clicked(); break;
        case 111: _t->on_btnUpZ_pressed(); break;
        case 112: _t->on_btnDownZ_pressed(); break;
        case 113: _t->on_btnUpZ_released(); break;
        case 114: _t->on_btnDownZ_released(); break;
        case 115: _t->on_btnSendCommandZ_clicked(); break;
        case 116: _t->on_btnConnectZ_clicked(); break;
        case 117: _t->on_btnDisconnectZ_clicked(); break;
        case 118: _t->on_spinPositionAbsoluteZ_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 119: _t->on_spinPositionRelativeZ_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 120: _t->on_btnRestoreBackup_clicked(); break;
        case 121: _t->on_btnSaveBackup_clicked(); break;
        case 122: _t->on_cboSelectFiducial_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 123: _t->on_cboBaudXY_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 124: _t->on_cboFocusAlgorithm_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 125: _t->on_NoClustersSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 126: _t->on_ScoreThreshold_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 127: _t->on_AlgoComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 128: _t->on_chkAutoThreshold_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 129: _t->on_chkCV_CALIB_CB_ADAPTIVE_THRESH_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 130: _t->on_chkCV_CALIB_CB_NORMALIZE_IMAGE_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 131: _t->on_chkCV_CALIB_CB_FILTER_QUADS_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 132: _t->on_btnProjectDirectory_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 133: _t->on_cboCalibrateAlgorithm_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 134: _t->on_chkCALIB_CB_FAST_CHECK_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 135: _t->on_chkCALIB_CB_CLUSTERING_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 136: _t->on_chkFixedAspect_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 137: _t->on_chkZeroDistortion_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 138: _t->on_chkFixPrincipalPointCenter_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 139: _t->on_chkIntrinsicGuess_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 140: _t->on_chkFixFocalLength_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 141: _t->on_chkOptimiseFocusRange_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 142: _t->on_chkInterpolateFocusPosition_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 143: _t->on_chkUseFocusThreshold_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 144: _t->on_chkUseCoarseFocusRange_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 145: _t->on_chkUseFineFocusRange_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 146: _t->on_chkCenterFocus_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 147: _t->on_chkUseRegisteredFocusPoints_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 148: _t->on_chkShowBestFocusImage_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 149: _t->on_chkDetectTargetsWhileScanning_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 150: _t->on_chkCorrectBackGround_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 151: _t->on_spinWaveletLevels_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 152: _t->on_spinItemsInRow_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 153: _t->on_spinItemsInColumn_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 154: _t->on_spinSizeSquare_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 155: _t->on_huMomentSimilaritySlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 156: _t->on_spinAspectTolerance_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 157: _t->on_scoreRegionArea_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 158: _t->on_chkLockFiducial_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 159: _t->on_chkPaddTargetImage_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 160: _t->on_spOverviewLensFocalLength_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 161: _t->on_spMicroscopeLensFocalLength_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 162: _t->on_chkDisplayGrid_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 163: _t->on_chkJoystickOn_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 164: _t->on_chkKeypadOn_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 165: _t->on_cboActiveCamera_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 166: _t->on_buttonBox_clicked((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 167: _t->on_btnSelectColour_clicked(); break;
        case 168: _t->on_editName_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 169: _t->on_editInstitute_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 170: _t->on_editProjectName_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 171: _t->on_editProjectID_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 172: _t->on_editVersion_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 173: _t->on_editDescription_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 174: _t->on_editSampleDescription_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 175: _t->on_editFilenamePrefix_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 176: _t->on_editBarcode_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 177: _t->on_projectDate_dateChanged((*reinterpret_cast< QDate(*)>(_a[1]))); break;
        case 178: _t->on_editProjectDirectoryName_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 179: _t->on_lineEditOverviewCameraSN_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 180: _t->on_lineEditMicroscopeCameraSN_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 28:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QString> >(); break;
            }
            break;
        case 166:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractButton* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SettingsDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingsDialog::sendSettings)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (SettingsDialog::*_t)(bool , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingsDialog::updatePaddTarget)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (SettingsDialog::*_t)(bool , double , double , double , double , QColor );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingsDialog::setGrid)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (SettingsDialog::*_t)(int , QString , QString , QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingsDialog::logFeedback)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (SettingsDialog::*_t)(double , double , ACTIONS::action );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingsDialog::MoveAbsoluteXY)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (SettingsDialog::*_t)(double , double , ACTIONS::action );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingsDialog::MoveRelativeXY)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (SettingsDialog::*_t)(double , ACTIONS::action );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingsDialog::MoveAbsoluteZ)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (SettingsDialog::*_t)(double , ACTIONS::action );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingsDialog::MoveRelativeZ)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (SettingsDialog::*_t)(ACTIONS::action );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingsDialog::stopMotionZ)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (SettingsDialog::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingsDialog::SendCommandXY)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (SettingsDialog::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingsDialog::SendCommandZ)) {
                *result = 10;
                return;
            }
        }
        {
            typedef void (SettingsDialog::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingsDialog::SetVelocityXY)) {
                *result = 11;
                return;
            }
        }
        {
            typedef void (SettingsDialog::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingsDialog::SetJoystickXY)) {
                *result = 12;
                return;
            }
        }
        {
            typedef void (SettingsDialog::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingsDialog::SetKeypadZ)) {
                *result = 13;
                return;
            }
        }
        {
            typedef void (SettingsDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingsDialog::CalibrateXY)) {
                *result = 14;
                return;
            }
        }
        {
            typedef void (SettingsDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingsDialog::MeasureRangeXY)) {
                *result = 15;
                return;
            }
        }
        {
            typedef void (SettingsDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingsDialog::ConnectXY)) {
                *result = 16;
                return;
            }
        }
        {
            typedef void (SettingsDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingsDialog::DisconnectXY)) {
                *result = 17;
                return;
            }
        }
        {
            typedef void (SettingsDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingsDialog::ConnectZ)) {
                *result = 18;
                return;
            }
        }
        {
            typedef void (SettingsDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingsDialog::DisconnectZ)) {
                *result = 19;
                return;
            }
        }
        {
            typedef void (SettingsDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingsDialog::AbortXY)) {
                *result = 20;
                return;
            }
        }
        {
            typedef void (SettingsDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingsDialog::getCOMPORTS)) {
                *result = 21;
                return;
            }
        }
        {
            typedef void (SettingsDialog::*_t)(QPoint );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingsDialog::moveToFiducialFromOverview)) {
                *result = 22;
                return;
            }
        }
        {
            typedef void (SettingsDialog::*_t)(QVector3D , QVector3D , QVector3D );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingsDialog::createTransformationMatrix)) {
                *result = 23;
                return;
            }
        }
        {
            typedef void (SettingsDialog::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingsDialog::saveBackup)) {
                *result = 24;
                return;
            }
        }
        {
            typedef void (SettingsDialog::*_t)(QString , CONSOLECOLOURS::colour );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingsDialog::LOGCONSOLE)) {
                *result = 25;
                return;
            }
        }
        {
            typedef void (SettingsDialog::*_t)(FIDUCIAL::position );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingsDialog::SETFIDUCIALPOSITION)) {
                *result = 26;
                return;
            }
        }
        {
            typedef void (SettingsDialog::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingsDialog::LockFiducial)) {
                *result = 27;
                return;
            }
        }
    }
}

const QMetaObject SettingsDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SettingsDialog.data,
      qt_meta_data_SettingsDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SettingsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SettingsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SettingsDialog.stringdata0))
        return static_cast<void*>(const_cast< SettingsDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int SettingsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 181)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 181;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 181)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 181;
    }
    return _id;
}

// SIGNAL 0
void SettingsDialog::sendSettings()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void SettingsDialog::updatePaddTarget(bool _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SettingsDialog::setGrid(bool _t1, double _t2, double _t3, double _t4, double _t5, QColor _t6)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SettingsDialog::logFeedback(int _t1, QString _t2, QString _t3, QString _t4, QString _t5)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SettingsDialog::MoveAbsoluteXY(double _t1, double _t2, ACTIONS::action _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void SettingsDialog::MoveRelativeXY(double _t1, double _t2, ACTIONS::action _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void SettingsDialog::MoveAbsoluteZ(double _t1, ACTIONS::action _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void SettingsDialog::MoveRelativeZ(double _t1, ACTIONS::action _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void SettingsDialog::stopMotionZ(ACTIONS::action _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void SettingsDialog::SendCommandXY(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void SettingsDialog::SendCommandZ(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void SettingsDialog::SetVelocityXY(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void SettingsDialog::SetJoystickXY(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void SettingsDialog::SetKeypadZ(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void SettingsDialog::CalibrateXY()
{
    QMetaObject::activate(this, &staticMetaObject, 14, Q_NULLPTR);
}

// SIGNAL 15
void SettingsDialog::MeasureRangeXY()
{
    QMetaObject::activate(this, &staticMetaObject, 15, Q_NULLPTR);
}

// SIGNAL 16
void SettingsDialog::ConnectXY()
{
    QMetaObject::activate(this, &staticMetaObject, 16, Q_NULLPTR);
}

// SIGNAL 17
void SettingsDialog::DisconnectXY()
{
    QMetaObject::activate(this, &staticMetaObject, 17, Q_NULLPTR);
}

// SIGNAL 18
void SettingsDialog::ConnectZ()
{
    QMetaObject::activate(this, &staticMetaObject, 18, Q_NULLPTR);
}

// SIGNAL 19
void SettingsDialog::DisconnectZ()
{
    QMetaObject::activate(this, &staticMetaObject, 19, Q_NULLPTR);
}

// SIGNAL 20
void SettingsDialog::AbortXY()
{
    QMetaObject::activate(this, &staticMetaObject, 20, Q_NULLPTR);
}

// SIGNAL 21
void SettingsDialog::getCOMPORTS()
{
    QMetaObject::activate(this, &staticMetaObject, 21, Q_NULLPTR);
}

// SIGNAL 22
void SettingsDialog::moveToFiducialFromOverview(QPoint _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void SettingsDialog::createTransformationMatrix(QVector3D _t1, QVector3D _t2, QVector3D _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}

// SIGNAL 24
void SettingsDialog::saveBackup(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 24, _a);
}

// SIGNAL 25
void SettingsDialog::LOGCONSOLE(QString _t1, CONSOLECOLOURS::colour _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}

// SIGNAL 26
void SettingsDialog::SETFIDUCIALPOSITION(FIDUCIAL::position _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 26, _a);
}

// SIGNAL 27
void SettingsDialog::LockFiducial(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 27, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
