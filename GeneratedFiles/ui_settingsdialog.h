/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QVBoxLayout *verticalLayout_7;
    QTabWidget *SettingsTab;
    QWidget *ProjectSettingsTab;
    QWidget *verticalLayoutWidget_7;
    QVBoxLayout *verticalLayout_25;
    QLabel *label_105;
    QHBoxLayout *horizontalLayout_16;
    QPushButton *btnSaveBackup;
    QPushButton *btnRestoreBackup;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_6;
    QLabel *label_85;
    QLabel *label_93;
    QLabel *label_89;
    QLabel *label_94;
    QLabel *label_87;
    QLabel *label_40;
    QLabel *label_86;
    QLabel *label_41;
    QLabel *label_88;
    QLabel *label_83;
    QLabel *label_84;
    QPushButton *btnProjectDirectory;
    QLineEdit *editProjectDirectoryName;
    QLineEdit *editName;
    QLineEdit *editInstitute;
    QLineEdit *editProjectName;
    QLineEdit *editProjectID;
    QLineEdit *editVersion;
    QLineEdit *editDescription;
    QLineEdit *editFilenamePrefix;
    QLineEdit *editSampleDescription;
    QLineEdit *editBarcode;
    QDateEdit *projectDate;
    QWidget *CameraSettingsTab;
    QGridLayout *gridLayout_10;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_9;
    QGridLayout *gridLayout_19;
    QSpinBox *spnImageWidthPixels;
    QLineEdit *lineEditOverviewCameraSN;
    QSpinBox *spMicroscopeLensFocalLength;
    QLineEdit *lineEditMicroscopeCameraSN;
    QLabel *label_68;
    QLabel *label_37;
    QLabel *label_36;
    QLabel *label_34;
    QLabel *label_38;
    QLabel *label_35;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_69;
    QSlider *sliderBarcodeThreshold;
    QCheckBox *chkAutoBarcodeThreshold;
    QLabel *label_74;
    QGridLayout *gridLayout_3;
    QLabel *lbl_barCode_H;
    QLabel *lbl_barCode_X;
    QLabel *lbl_barCode_Y;
    QLabel *lbl_barCode_W;
    QLabel *label_75;
    QLabel *label_76;
    QLabel *label_77;
    QLabel *label_78;
    QLabel *lblImageHeightMicrons;
    QLabel *label_102;
    QLabel *label_7;
    QLabel *label_99;
    QSpinBox *spOverviewLensFocalLength;
    QLabel *lblImageWidthMicrons;
    QComboBox *cboActiveCamera;
    QLabel *label_98;
    QLabel *label_103;
    QSpinBox *spnImageHeightPixels;
    QLineEdit *editPixelSizeMicrons;
    QWidget *StageSettingsTab;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_6;
    QGridLayout *gridLayout_4;
    QLabel *lblPORTZ;
    QLabel *label_44;
    QLabel *lblPORTXY;
    QLabel *lblPorts;
    QLabel *label_46;
    QComboBox *cboCOMPORTS;
    QFrame *XYStageFrame;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_49;
    QGridLayout *gridLayout_28;
    QGridLayout *gridLayout_24;
    QVBoxLayout *verticalLayout_13;
    QLabel *label_51;
    QGridLayout *gridLayout_8;
    QLabel *label_81;
    QLabel *label_80;
    QLabel *lbl_positionXY_X;
    QLabel *lbl_positionXY_Y;
    QGridLayout *gridLayout_25;
    QLabel *label_11;
    QLabel *label_52;
    QLabel *label_53;
    QLabel *label_13;
    QLabel *label_15;
    QDoubleSpinBox *spinXPositionAbsoluteXY;
    QDoubleSpinBox *spinXPositionRelativeXY;
    QDoubleSpinBox *spinYPositionAbsoluteXY;
    QDoubleSpinBox *spinYPositionRelativeXY;
    QVBoxLayout *verticalLayout_14;
    QPushButton *btnMoveAbsoluteXY;
    QPushButton *btnMoveRelativeXY;
    QPushButton *btnMoveToFiducial;
    QLabel *label_54;
    QLineEdit *editSendCommandXY;
    QPushButton *btnSendCommandXY;
    QVBoxLayout *verticalLayout_16;
    QLabel *label_55;
    QGridLayout *gridLayout_26;
    QComboBox *cboBaudXY;
    QGridLayout *gridLayout_29;
    QLabel *label_56;
    QHBoxLayout *horizontalLayout_6;
    QDoubleSpinBox *spinVelocityXY;
    QPushButton *btnSetVelocityXY;
    QGridLayout *gridLayout_30;
    QLabel *label_57;
    QVBoxLayout *verticalLayout_17;
    QLabel *label_58;
    QPushButton *btnCalibrateXY;
    QPushButton *btnMeasureRangeXY;
    QLabel *label_17;
    QPushButton *btnAbortXY;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_18;
    QLabel *label_59;
    QPushButton *btnConnectXY;
    QPushButton *btnDisconnectXY;
    QCheckBox *chkJoystickOn;
    QCheckBox *chkKeypadOn;
    QFrame *ZStageFrame;
    QWidget *verticalLayoutWidget_6;
    QVBoxLayout *ZStageLayout;
    QLabel *label_100;
    QVBoxLayout *verticalLayout_22;
    QVBoxLayout *verticalLayout_24;
    QLabel *label_101;
    QHBoxLayout *horizontalLayout_17;
    QPushButton *btnConnectZ;
    QPushButton *btnDisconnectZ;
    QLabel *label_104;
    QGridLayout *gridLayout_17;
    QLabel *lbl_positionZ;
    QLabel *label_106;
    QGridLayout *gridLayout_27;
    QDoubleSpinBox *spinPositionAbsoluteZ;
    QDoubleSpinBox *spinPositionRelativeZ;
    QLabel *label_111;
    QLabel *label_110;
    QLabel *label_45;
    QLabel *label_108;
    QVBoxLayout *verticalLayout_23;
    QPushButton *btnMoveAbsoluteZ;
    QPushButton *btnMoveRelativeZ;
    QHBoxLayout *horizontalLayout_32;
    QPushButton *btnUpZ;
    QPushButton *btnDownZ;
    QLabel *label_112;
    QLineEdit *editSendCommandZ;
    QPushButton *btnSendCommandZ;
    QWidget *tab;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_7;
    QLabel *label_107;
    QComboBox *cboFocusAlgorithm;
    QLabel *label_114;
    QDoubleSpinBox *spinMaxFocus;
    QLabel *label_109;
    QLabel *label_113;
    QLabel *label_115;
    QDoubleSpinBox *spinMinFocus;
    QDoubleSpinBox *spinCoarseFocusStep;
    QDoubleSpinBox *spinFineFocusStep;
    QLabel *label_267;
    QWidget *FiducialMarksTab;
    QLabel *label_8;
    QLabel *lblFiducialCheck;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_12;
    QDoubleSpinBox *spnTopRight_Overview_X;
    QDoubleSpinBox *spnBottomLeft_Overview_X;
    QDoubleSpinBox *spnBottomRight_Overview_X;
    QDoubleSpinBox *spnBottomLeft_Overview_Y;
    QDoubleSpinBox *spnTopRight_Overview_Y;
    QDoubleSpinBox *spnBottomRight_Overview_Y;
    QDoubleSpinBox *spnTopRight_Microscope_X;
    QDoubleSpinBox *spnTopLeft_Microscope_X;
    QDoubleSpinBox *spnBottomLeft_Microscope_X;
    QDoubleSpinBox *spnBottomRight_Microscope_X;
    QDoubleSpinBox *spnTopLeft_Microscope_Y;
    QDoubleSpinBox *spnTopRight_Microscope_Y;
    QDoubleSpinBox *spnBottomRight_Microscope_Y;
    QDoubleSpinBox *spnBottomLeft_Microscope_Y;
    QDoubleSpinBox *spnTopLeft_Microscope_Stage_Z;
    QDoubleSpinBox *spnTopRight_Microscope_Stage_Z;
    QDoubleSpinBox *spnBottomLeft_Microscope_Stage_Z;
    QDoubleSpinBox *spnBottomRight_Microscope_Stage_Z;
    QLabel *label_209;
    QDoubleSpinBox *spnBottomLeft_Microscope_Stage_X;
    QDoubleSpinBox *spnTopRight_Microscope_Stage_X;
    QLabel *lbl_bottomright_overview;
    QDoubleSpinBox *spnTopLeft_Overview_Stage_Y;
    QDoubleSpinBox *spnTopLeft_Overview_Stage_X;
    QLabel *label_207;
    QDoubleSpinBox *spnTopLeft_Microscope_Stage_X;
    QLabel *label_216;
    QLabel *label_218;
    QLabel *label_208;
    QLabel *label_215;
    QLabel *lbl_bottomleft_overview;
    QLabel *label_220;
    QDoubleSpinBox *spnTopLeft_Microscope_Stage_Y;
    QDoubleSpinBox *spnBottomLeft_Microscope_Stage_Y;
    QDoubleSpinBox *spnTopLeft_Overview_X;
    QDoubleSpinBox *spnTopLeft_Overview_Y;
    QDoubleSpinBox *spnTopRight_Microscope_Stage_Y;
    QLabel *label_210;
    QLabel *lbl_bottomright_microscope;
    QLabel *label_212;
    QLabel *label_217;
    QLabel *label_219;
    QLabel *label_214;
    QLabel *lbl_bottomleft_microscope;
    QLabel *label_221;
    QLabel *label_213;
    QDoubleSpinBox *spnBottomRight_Microscope_Stage_Y;
    QDoubleSpinBox *spnBottomRight_Microscope_Stage_X;
    QLabel *label_211;
    QLabel *label_82;
    QLabel *lbl_topleft_overview;
    QLabel *lbl_topright_overview;
    QLabel *label_95;
    QLabel *lbl_topleft_microscope;
    QLabel *lbl_topright_microscope;
    QLabel *label_224;
    QLabel *label_79;
    QLabel *label_72;
    QLabel *label_222;
    QLabel *label_223;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_12;
    QLabel *label_96;
    QHBoxLayout *horizontalLayout;
    QLabel *label_97;
    QPushButton *btnCalcTransformationMatrix;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_19;
    QVBoxLayout *verticalLayout_15;
    QLabel *label_71;
    QComboBox *cboSelectFiducial;
    QPushButton *btnDeleteFiducial;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QCheckBox *chkLockFiducial;
    QWidget *TargetSettingsTab;
    QFormLayout *formLayout_4;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_11;
    QComboBox *AlgoComboBox;
    QSpacerItem *horizontalSpacer_11;
    QLabel *label;
    QGridLayout *gridLayout_20;
    QSlider *ScoreThreshold;
    QLabel *label_5;
    QSlider *numClusters;
    QSlider *distanceThreshold;
    QLabel *label_2;
    QSlider *scoreRegionArea;
    QLabel *label_20;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_9;
    QLabel *ScoreThresholdLbl;
    QLabel *label_70;
    QHBoxLayout *horizontalLayout_10;
    QLabel *lblScoreSizeFactor;
    QLabel *label_73;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_distance;
    QLabel *label_22;
    QLabel *labelCluster;
    QHBoxLayout *horizontalLayout_7;
    QCheckBox *chkTargetImageAsMask;
    QSpacerItem *horizontalSpacer_4;
    QGridLayout *gridLayout_5;
    QSpinBox *spinSamplingDistance;
    QComboBox *cboSamplingType;
    QLabel *label_9;
    QLabel *label_43;
    QLabel *label_42;
    QSpinBox *spinExclusionDistance;
    QWidget *Drawing;
    QFormLayout *formLayout_3;
    QVBoxLayout *verticalLayout_21;
    QGridLayout *gridLayout_9;
    QPushButton *btnSelectColour;
    QComboBox *cboAnnotationColour;
    QLabel *label_6;
    QLabel *label_10;
    QGridLayout *gridLayout_2;
    QDoubleSpinBox *spinGridOffsetY;
    QDoubleSpinBox *spinGridOffsetX;
    QDoubleSpinBox *spinGridSpacingY;
    QSlider *sliderGridOffsetX;
    QLabel *label_31;
    QSlider *sliderGridOffsetY;
    QLabel *label_33;
    QSlider *sliderGridSpacingY;
    QLabel *label_32;
    QSlider *sliderGridSpacingX;
    QDoubleSpinBox *spinGridSpacingX;
    QLabel *label_30;
    QHBoxLayout *horizontalLayout_13;
    QCheckBox *chkDisplayGrid;
    QPushButton *btnCenterGrid;
    QWidget *CalibrationTab;
    QGridLayout *gridLayout_14;
    QVBoxLayout *verticalLayout;
    QLabel *label_39;
    QCheckBox *chkFixedAspect;
    QCheckBox *chkZeroDistortion;
    QCheckBox *chkFixPrincipalPointCenter;
    QCheckBox *chkIntrinsicGuess;
    QCheckBox *chkFixFocalLength;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_26;
    QCheckBox *chkCV_CALIB_CB_ADAPTIVE_THRESH;
    QCheckBox *chkCV_CALIB_CB_NORMALIZE_IMAGE;
    QCheckBox *chkCV_CALIB_CB_FILTER_QUADS;
    QCheckBox *chkCALIB_CB_FAST_CHECK;
    QSpacerItem *horizontalSpacer_6;
    QFormLayout *formLayout_2;
    QLabel *label_21;
    QSpinBox *spinItemsInRow;
    QLabel *label_23;
    QSpinBox *spinItemsInColumn;
    QLabel *label_24;
    QSpinBox *spinSizeSquare;
    QFormLayout *formLayout;
    QLabel *label_25;
    QComboBox *cboCalibrateAlgorithm;
    QSpacerItem *verticalSpacer_6;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_27;
    QCheckBox *chkCALIB_CB_CLUSTERING;
    QWidget *ThresholdSettingsTab;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *verticalLayout_11;
    QGridLayout *gridLayout_18;
    QSlider *NoClustersSlider;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *cboThresholdType;
    QSpacerItem *horizontalSpacer_10;
    QSlider *ThresholdMinSlider;
    QGridLayout *gridLayout_histogram;
    QGridLayout *gridLayout_15;
    QLabel *ThresholdMaxLbl;
    QLabel *ThresholdMinLbl;
    QSpacerItem *horizontalSpacer_7;
    QLabel *histogram_image;
    QLabel *label_92;
    QLabel *label_90;
    QLabel *label_91;
    QLabel *NoClustersLbl;
    QLabel *labelThresholdMin;
    QLabel *labelThresholdMax;
    QLabel *label_28;
    QSlider *ThresholdMaxSlider;
    QLabel *label_12;
    QHBoxLayout *horizontalLayout_12;
    QCheckBox *chkAutoThreshold;
    QSpacerItem *horizontalSpacer_12;
    QWidget *ConnectedComponentsTab;
    QGridLayout *gridLayout_16;
    QGridLayout *gridLayout;
    QLabel *label_18;
    QSpinBox *sizeToleranceLargerSpinBox;
    QLabel *label_29;
    QDoubleSpinBox *spinAspectTolerance;
    QLabel *label_14;
    QSpinBox *sizeToleranceSmallerSpinBox;
    QLabel *label_16;
    QLabel *label_19;
    QSlider *huMomentSimilaritySlider;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *verticalSpacer_3;
    QWidget *Feedback;
    QWidget *gridLayoutWidget_4;
    QGridLayout *gridLayout_11;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_47;
    QLabel *label_66;
    QGridLayout *gridLayout_22;
    QLabel *label_60;
    QLineEdit *editFeedbackName;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_63;
    QSlider *sliderFeedbackSatisfaction;
    QLabel *label_64;
    QLineEdit *editFeedbackInstitute;
    QLabel *label_48;
    QLabel *label_61;
    QLabel *label_50;
    QLineEdit *editFeedbackEmail;
    QPlainTextEdit *editFeedbackDescription;
    QLabel *label_62;
    QLabel *label_65;
    QLabel *label_67;
    QPushButton *btnLogFeedback;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QStringLiteral("SettingsDialog"));
        SettingsDialog->resize(798, 543);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SettingsDialog->sizePolicy().hasHeightForWidth());
        SettingsDialog->setSizePolicy(sizePolicy);
        verticalLayout_7 = new QVBoxLayout(SettingsDialog);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        SettingsTab = new QTabWidget(SettingsDialog);
        SettingsTab->setObjectName(QStringLiteral("SettingsTab"));
        SettingsTab->setStyleSheet(QStringLiteral(""));
        ProjectSettingsTab = new QWidget();
        ProjectSettingsTab->setObjectName(QStringLiteral("ProjectSettingsTab"));
        verticalLayoutWidget_7 = new QWidget(ProjectSettingsTab);
        verticalLayoutWidget_7->setObjectName(QStringLiteral("verticalLayoutWidget_7"));
        verticalLayoutWidget_7->setGeometry(QRect(10, 320, 213, 80));
        verticalLayout_25 = new QVBoxLayout(verticalLayoutWidget_7);
        verticalLayout_25->setObjectName(QStringLiteral("verticalLayout_25"));
        verticalLayout_25->setContentsMargins(0, 0, 0, 0);
        label_105 = new QLabel(verticalLayoutWidget_7);
        label_105->setObjectName(QStringLiteral("label_105"));
        QFont font;
        font.setUnderline(true);
        label_105->setFont(font);

        verticalLayout_25->addWidget(label_105);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        btnSaveBackup = new QPushButton(verticalLayoutWidget_7);
        btnSaveBackup->setObjectName(QStringLiteral("btnSaveBackup"));

        horizontalLayout_16->addWidget(btnSaveBackup);

        btnRestoreBackup = new QPushButton(verticalLayoutWidget_7);
        btnRestoreBackup->setObjectName(QStringLiteral("btnRestoreBackup"));

        horizontalLayout_16->addWidget(btnRestoreBackup);


        verticalLayout_25->addLayout(horizontalLayout_16);

        layoutWidget = new QWidget(ProjectSettingsTab);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(9, 9, 721, 285));
        gridLayout_6 = new QGridLayout(layoutWidget);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_6->setSizeConstraint(QLayout::SetMinimumSize);
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        label_85 = new QLabel(layoutWidget);
        label_85->setObjectName(QStringLiteral("label_85"));

        gridLayout_6->addWidget(label_85, 8, 0, 1, 1);

        label_93 = new QLabel(layoutWidget);
        label_93->setObjectName(QStringLiteral("label_93"));

        gridLayout_6->addWidget(label_93, 9, 0, 1, 1);

        label_89 = new QLabel(layoutWidget);
        label_89->setObjectName(QStringLiteral("label_89"));

        gridLayout_6->addWidget(label_89, 1, 0, 1, 1);

        label_94 = new QLabel(layoutWidget);
        label_94->setObjectName(QStringLiteral("label_94"));

        gridLayout_6->addWidget(label_94, 3, 0, 1, 1);

        label_87 = new QLabel(layoutWidget);
        label_87->setObjectName(QStringLiteral("label_87"));

        gridLayout_6->addWidget(label_87, 10, 0, 1, 1);

        label_40 = new QLabel(layoutWidget);
        label_40->setObjectName(QStringLiteral("label_40"));

        gridLayout_6->addWidget(label_40, 2, 0, 1, 1);

        label_86 = new QLabel(layoutWidget);
        label_86->setObjectName(QStringLiteral("label_86"));

        gridLayout_6->addWidget(label_86, 0, 0, 1, 1);

        label_41 = new QLabel(layoutWidget);
        label_41->setObjectName(QStringLiteral("label_41"));

        gridLayout_6->addWidget(label_41, 4, 0, 1, 1);

        label_88 = new QLabel(layoutWidget);
        label_88->setObjectName(QStringLiteral("label_88"));

        gridLayout_6->addWidget(label_88, 5, 0, 1, 1);

        label_83 = new QLabel(layoutWidget);
        label_83->setObjectName(QStringLiteral("label_83"));

        gridLayout_6->addWidget(label_83, 6, 0, 1, 1);

        label_84 = new QLabel(layoutWidget);
        label_84->setObjectName(QStringLiteral("label_84"));

        gridLayout_6->addWidget(label_84, 7, 0, 1, 1);

        btnProjectDirectory = new QPushButton(layoutWidget);
        btnProjectDirectory->setObjectName(QStringLiteral("btnProjectDirectory"));

        gridLayout_6->addWidget(btnProjectDirectory, 3, 2, 1, 1);

        editProjectDirectoryName = new QLineEdit(layoutWidget);
        editProjectDirectoryName->setObjectName(QStringLiteral("editProjectDirectoryName"));

        gridLayout_6->addWidget(editProjectDirectoryName, 3, 1, 1, 1);

        editName = new QLineEdit(layoutWidget);
        editName->setObjectName(QStringLiteral("editName"));

        gridLayout_6->addWidget(editName, 0, 1, 1, 2);

        editInstitute = new QLineEdit(layoutWidget);
        editInstitute->setObjectName(QStringLiteral("editInstitute"));

        gridLayout_6->addWidget(editInstitute, 1, 1, 1, 2);

        editProjectName = new QLineEdit(layoutWidget);
        editProjectName->setObjectName(QStringLiteral("editProjectName"));

        gridLayout_6->addWidget(editProjectName, 2, 1, 1, 2);

        editProjectID = new QLineEdit(layoutWidget);
        editProjectID->setObjectName(QStringLiteral("editProjectID"));

        gridLayout_6->addWidget(editProjectID, 4, 1, 1, 2);

        editVersion = new QLineEdit(layoutWidget);
        editVersion->setObjectName(QStringLiteral("editVersion"));

        gridLayout_6->addWidget(editVersion, 5, 1, 1, 2);

        editDescription = new QLineEdit(layoutWidget);
        editDescription->setObjectName(QStringLiteral("editDescription"));

        gridLayout_6->addWidget(editDescription, 6, 1, 1, 2);

        editFilenamePrefix = new QLineEdit(layoutWidget);
        editFilenamePrefix->setObjectName(QStringLiteral("editFilenamePrefix"));

        gridLayout_6->addWidget(editFilenamePrefix, 7, 1, 1, 2);

        editSampleDescription = new QLineEdit(layoutWidget);
        editSampleDescription->setObjectName(QStringLiteral("editSampleDescription"));

        gridLayout_6->addWidget(editSampleDescription, 8, 1, 1, 2);

        editBarcode = new QLineEdit(layoutWidget);
        editBarcode->setObjectName(QStringLiteral("editBarcode"));

        gridLayout_6->addWidget(editBarcode, 9, 1, 1, 2);

        projectDate = new QDateEdit(layoutWidget);
        projectDate->setObjectName(QStringLiteral("projectDate"));

        gridLayout_6->addWidget(projectDate, 10, 1, 1, 2);

        SettingsTab->addTab(ProjectSettingsTab, QString());
        CameraSettingsTab = new QWidget();
        CameraSettingsTab->setObjectName(QStringLiteral("CameraSettingsTab"));
        gridLayout_10 = new QGridLayout(CameraSettingsTab);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_10->addItem(verticalSpacer_2, 10, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_2, 3, 5, 1, 1);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        gridLayout_19 = new QGridLayout();
        gridLayout_19->setObjectName(QStringLiteral("gridLayout_19"));
        spnImageWidthPixels = new QSpinBox(CameraSettingsTab);
        spnImageWidthPixels->setObjectName(QStringLiteral("spnImageWidthPixels"));
        spnImageWidthPixels->setMaximum(10000);
        spnImageWidthPixels->setValue(2046);

        gridLayout_19->addWidget(spnImageWidthPixels, 5, 1, 1, 1);

        lineEditOverviewCameraSN = new QLineEdit(CameraSettingsTab);
        lineEditOverviewCameraSN->setObjectName(QStringLiteral("lineEditOverviewCameraSN"));

        gridLayout_19->addWidget(lineEditOverviewCameraSN, 11, 1, 1, 1);

        spMicroscopeLensFocalLength = new QSpinBox(CameraSettingsTab);
        spMicroscopeLensFocalLength->setObjectName(QStringLiteral("spMicroscopeLensFocalLength"));
        spMicroscopeLensFocalLength->setMaximum(100);
        spMicroscopeLensFocalLength->setValue(20);

        gridLayout_19->addWidget(spMicroscopeLensFocalLength, 7, 1, 1, 1);

        lineEditMicroscopeCameraSN = new QLineEdit(CameraSettingsTab);
        lineEditMicroscopeCameraSN->setObjectName(QStringLiteral("lineEditMicroscopeCameraSN"));

        gridLayout_19->addWidget(lineEditMicroscopeCameraSN, 12, 1, 1, 1);

        label_68 = new QLabel(CameraSettingsTab);
        label_68->setObjectName(QStringLiteral("label_68"));

        gridLayout_19->addWidget(label_68, 13, 0, 1, 1);

        label_37 = new QLabel(CameraSettingsTab);
        label_37->setObjectName(QStringLiteral("label_37"));

        gridLayout_19->addWidget(label_37, 8, 0, 1, 1);

        label_36 = new QLabel(CameraSettingsTab);
        label_36->setObjectName(QStringLiteral("label_36"));

        gridLayout_19->addWidget(label_36, 3, 0, 1, 1);

        label_34 = new QLabel(CameraSettingsTab);
        label_34->setObjectName(QStringLiteral("label_34"));

        gridLayout_19->addWidget(label_34, 11, 0, 1, 1);

        label_38 = new QLabel(CameraSettingsTab);
        label_38->setObjectName(QStringLiteral("label_38"));

        gridLayout_19->addWidget(label_38, 7, 0, 1, 1);

        label_35 = new QLabel(CameraSettingsTab);
        label_35->setObjectName(QStringLiteral("label_35"));

        gridLayout_19->addWidget(label_35, 12, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_69 = new QLabel(CameraSettingsTab);
        label_69->setObjectName(QStringLiteral("label_69"));

        horizontalLayout_5->addWidget(label_69);

        sliderBarcodeThreshold = new QSlider(CameraSettingsTab);
        sliderBarcodeThreshold->setObjectName(QStringLiteral("sliderBarcodeThreshold"));
        sliderBarcodeThreshold->setMaximum(100);
        sliderBarcodeThreshold->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(sliderBarcodeThreshold);

        chkAutoBarcodeThreshold = new QCheckBox(CameraSettingsTab);
        chkAutoBarcodeThreshold->setObjectName(QStringLiteral("chkAutoBarcodeThreshold"));

        horizontalLayout_5->addWidget(chkAutoBarcodeThreshold);


        gridLayout_19->addLayout(horizontalLayout_5, 13, 1, 1, 1);

        label_74 = new QLabel(CameraSettingsTab);
        label_74->setObjectName(QStringLiteral("label_74"));

        gridLayout_19->addWidget(label_74, 14, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        lbl_barCode_H = new QLabel(CameraSettingsTab);
        lbl_barCode_H->setObjectName(QStringLiteral("lbl_barCode_H"));
        lbl_barCode_H->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(lbl_barCode_H, 1, 3, 1, 1);

        lbl_barCode_X = new QLabel(CameraSettingsTab);
        lbl_barCode_X->setObjectName(QStringLiteral("lbl_barCode_X"));
        lbl_barCode_X->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(lbl_barCode_X, 1, 1, 1, 1);

        lbl_barCode_Y = new QLabel(CameraSettingsTab);
        lbl_barCode_Y->setObjectName(QStringLiteral("lbl_barCode_Y"));
        lbl_barCode_Y->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(lbl_barCode_Y, 1, 0, 1, 1);

        lbl_barCode_W = new QLabel(CameraSettingsTab);
        lbl_barCode_W->setObjectName(QStringLiteral("lbl_barCode_W"));
        lbl_barCode_W->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(lbl_barCode_W, 1, 2, 1, 1);

        label_75 = new QLabel(CameraSettingsTab);
        label_75->setObjectName(QStringLiteral("label_75"));
        label_75->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_75, 0, 1, 1, 1);

        label_76 = new QLabel(CameraSettingsTab);
        label_76->setObjectName(QStringLiteral("label_76"));
        label_76->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_76, 0, 0, 1, 1);

        label_77 = new QLabel(CameraSettingsTab);
        label_77->setObjectName(QStringLiteral("label_77"));
        label_77->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_77, 0, 2, 1, 1);

        label_78 = new QLabel(CameraSettingsTab);
        label_78->setObjectName(QStringLiteral("label_78"));
        label_78->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_78, 0, 3, 1, 1);


        gridLayout_19->addLayout(gridLayout_3, 14, 1, 1, 1);

        lblImageHeightMicrons = new QLabel(CameraSettingsTab);
        lblImageHeightMicrons->setObjectName(QStringLiteral("lblImageHeightMicrons"));

        gridLayout_19->addWidget(lblImageHeightMicrons, 10, 1, 1, 1);

        label_102 = new QLabel(CameraSettingsTab);
        label_102->setObjectName(QStringLiteral("label_102"));

        gridLayout_19->addWidget(label_102, 5, 0, 1, 1);

        label_7 = new QLabel(CameraSettingsTab);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_19->addWidget(label_7, 4, 0, 1, 1);

        label_99 = new QLabel(CameraSettingsTab);
        label_99->setObjectName(QStringLiteral("label_99"));

        gridLayout_19->addWidget(label_99, 10, 0, 1, 1);

        spOverviewLensFocalLength = new QSpinBox(CameraSettingsTab);
        spOverviewLensFocalLength->setObjectName(QStringLiteral("spOverviewLensFocalLength"));
        spOverviewLensFocalLength->setMaximum(100);
        spOverviewLensFocalLength->setValue(35);

        gridLayout_19->addWidget(spOverviewLensFocalLength, 8, 1, 1, 1);

        lblImageWidthMicrons = new QLabel(CameraSettingsTab);
        lblImageWidthMicrons->setObjectName(QStringLiteral("lblImageWidthMicrons"));

        gridLayout_19->addWidget(lblImageWidthMicrons, 9, 1, 1, 1);

        cboActiveCamera = new QComboBox(CameraSettingsTab);
        cboActiveCamera->setObjectName(QStringLiteral("cboActiveCamera"));

        gridLayout_19->addWidget(cboActiveCamera, 3, 1, 1, 1);

        label_98 = new QLabel(CameraSettingsTab);
        label_98->setObjectName(QStringLiteral("label_98"));

        gridLayout_19->addWidget(label_98, 9, 0, 1, 1);

        label_103 = new QLabel(CameraSettingsTab);
        label_103->setObjectName(QStringLiteral("label_103"));

        gridLayout_19->addWidget(label_103, 6, 0, 1, 1);

        spnImageHeightPixels = new QSpinBox(CameraSettingsTab);
        spnImageHeightPixels->setObjectName(QStringLiteral("spnImageHeightPixels"));
        spnImageHeightPixels->setMaximum(10000);
        spnImageHeightPixels->setValue(2046);

        gridLayout_19->addWidget(spnImageHeightPixels, 6, 1, 1, 1);

        editPixelSizeMicrons = new QLineEdit(CameraSettingsTab);
        editPixelSizeMicrons->setObjectName(QStringLiteral("editPixelSizeMicrons"));

        gridLayout_19->addWidget(editPixelSizeMicrons, 4, 1, 1, 1);


        verticalLayout_9->addLayout(gridLayout_19);


        gridLayout_10->addLayout(verticalLayout_9, 3, 4, 1, 1);

        SettingsTab->addTab(CameraSettingsTab, QString());
        StageSettingsTab = new QWidget();
        StageSettingsTab->setObjectName(QStringLiteral("StageSettingsTab"));
        verticalLayoutWidget = new QWidget(StageSettingsTab);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(430, 20, 221, 71));
        verticalLayout_6 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        lblPORTZ = new QLabel(verticalLayoutWidget);
        lblPORTZ->setObjectName(QStringLiteral("lblPORTZ"));

        gridLayout_4->addWidget(lblPORTZ, 2, 1, 1, 1);

        label_44 = new QLabel(verticalLayoutWidget);
        label_44->setObjectName(QStringLiteral("label_44"));

        gridLayout_4->addWidget(label_44, 2, 0, 1, 1);

        lblPORTXY = new QLabel(verticalLayoutWidget);
        lblPORTXY->setObjectName(QStringLiteral("lblPORTXY"));

        gridLayout_4->addWidget(lblPORTXY, 1, 1, 1, 1);

        lblPorts = new QLabel(verticalLayoutWidget);
        lblPorts->setObjectName(QStringLiteral("lblPorts"));

        gridLayout_4->addWidget(lblPorts, 1, 0, 1, 1);

        label_46 = new QLabel(verticalLayoutWidget);
        label_46->setObjectName(QStringLiteral("label_46"));

        gridLayout_4->addWidget(label_46, 0, 0, 1, 1);

        cboCOMPORTS = new QComboBox(verticalLayoutWidget);
        cboCOMPORTS->setObjectName(QStringLiteral("cboCOMPORTS"));

        gridLayout_4->addWidget(cboCOMPORTS, 0, 1, 1, 1);


        verticalLayout_6->addLayout(gridLayout_4);

        XYStageFrame = new QFrame(StageSettingsTab);
        XYStageFrame->setObjectName(QStringLiteral("XYStageFrame"));
        XYStageFrame->setGeometry(QRect(10, 20, 371, 381));
        XYStageFrame->setFrameShape(QFrame::StyledPanel);
        XYStageFrame->setFrameShadow(QFrame::Raised);
        verticalLayoutWidget_5 = new QWidget(XYStageFrame);
        verticalLayoutWidget_5->setObjectName(QStringLiteral("verticalLayoutWidget_5"));
        verticalLayoutWidget_5->setGeometry(QRect(0, 0, 370, 380));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget_5);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        label_49 = new QLabel(verticalLayoutWidget_5);
        label_49->setObjectName(QStringLiteral("label_49"));
        label_49->setFont(font);
        label_49->setCursor(QCursor(Qt::ArrowCursor));
        label_49->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_49);

        gridLayout_28 = new QGridLayout();
        gridLayout_28->setObjectName(QStringLiteral("gridLayout_28"));
        gridLayout_24 = new QGridLayout();
        gridLayout_24->setObjectName(QStringLiteral("gridLayout_24"));
        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        label_51 = new QLabel(verticalLayoutWidget_5);
        label_51->setObjectName(QStringLiteral("label_51"));
        label_51->setFont(font);
        label_51->setAlignment(Qt::AlignCenter);

        verticalLayout_13->addWidget(label_51);

        gridLayout_8 = new QGridLayout();
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        label_81 = new QLabel(verticalLayoutWidget_5);
        label_81->setObjectName(QStringLiteral("label_81"));

        gridLayout_8->addWidget(label_81, 0, 2, 1, 1);

        label_80 = new QLabel(verticalLayoutWidget_5);
        label_80->setObjectName(QStringLiteral("label_80"));

        gridLayout_8->addWidget(label_80, 0, 0, 1, 1);

        lbl_positionXY_X = new QLabel(verticalLayoutWidget_5);
        lbl_positionXY_X->setObjectName(QStringLiteral("lbl_positionXY_X"));
        lbl_positionXY_X->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(lbl_positionXY_X, 0, 1, 1, 1);

        lbl_positionXY_Y = new QLabel(verticalLayoutWidget_5);
        lbl_positionXY_Y->setObjectName(QStringLiteral("lbl_positionXY_Y"));
        lbl_positionXY_Y->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(lbl_positionXY_Y, 0, 3, 1, 1);


        verticalLayout_13->addLayout(gridLayout_8);

        gridLayout_25 = new QGridLayout();
        gridLayout_25->setObjectName(QStringLiteral("gridLayout_25"));
        label_11 = new QLabel(verticalLayoutWidget_5);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setAlignment(Qt::AlignCenter);

        gridLayout_25->addWidget(label_11, 0, 0, 1, 1);

        label_52 = new QLabel(verticalLayoutWidget_5);
        label_52->setObjectName(QStringLiteral("label_52"));

        gridLayout_25->addWidget(label_52, 1, 0, 1, 1);

        label_53 = new QLabel(verticalLayoutWidget_5);
        label_53->setObjectName(QStringLiteral("label_53"));

        gridLayout_25->addWidget(label_53, 2, 0, 1, 1);

        label_13 = new QLabel(verticalLayoutWidget_5);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setAlignment(Qt::AlignCenter);

        gridLayout_25->addWidget(label_13, 0, 1, 1, 1);

        label_15 = new QLabel(verticalLayoutWidget_5);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setAlignment(Qt::AlignCenter);

        gridLayout_25->addWidget(label_15, 0, 2, 1, 1);

        spinXPositionAbsoluteXY = new QDoubleSpinBox(verticalLayoutWidget_5);
        spinXPositionAbsoluteXY->setObjectName(QStringLiteral("spinXPositionAbsoluteXY"));
        spinXPositionAbsoluteXY->setMinimum(-200);
        spinXPositionAbsoluteXY->setMaximum(200);

        gridLayout_25->addWidget(spinXPositionAbsoluteXY, 1, 1, 1, 1);

        spinXPositionRelativeXY = new QDoubleSpinBox(verticalLayoutWidget_5);
        spinXPositionRelativeXY->setObjectName(QStringLiteral("spinXPositionRelativeXY"));
        spinXPositionRelativeXY->setMinimum(-200);
        spinXPositionRelativeXY->setMaximum(200);

        gridLayout_25->addWidget(spinXPositionRelativeXY, 1, 2, 1, 1);

        spinYPositionAbsoluteXY = new QDoubleSpinBox(verticalLayoutWidget_5);
        spinYPositionAbsoluteXY->setObjectName(QStringLiteral("spinYPositionAbsoluteXY"));
        spinYPositionAbsoluteXY->setMinimum(-200);
        spinYPositionAbsoluteXY->setMaximum(200);

        gridLayout_25->addWidget(spinYPositionAbsoluteXY, 2, 1, 1, 1);

        spinYPositionRelativeXY = new QDoubleSpinBox(verticalLayoutWidget_5);
        spinYPositionRelativeXY->setObjectName(QStringLiteral("spinYPositionRelativeXY"));
        spinYPositionRelativeXY->setMinimum(-200);
        spinYPositionRelativeXY->setMaximum(200);

        gridLayout_25->addWidget(spinYPositionRelativeXY, 2, 2, 1, 1);


        verticalLayout_13->addLayout(gridLayout_25);

        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        btnMoveAbsoluteXY = new QPushButton(verticalLayoutWidget_5);
        btnMoveAbsoluteXY->setObjectName(QStringLiteral("btnMoveAbsoluteXY"));

        verticalLayout_14->addWidget(btnMoveAbsoluteXY);

        btnMoveRelativeXY = new QPushButton(verticalLayoutWidget_5);
        btnMoveRelativeXY->setObjectName(QStringLiteral("btnMoveRelativeXY"));

        verticalLayout_14->addWidget(btnMoveRelativeXY);

        btnMoveToFiducial = new QPushButton(verticalLayoutWidget_5);
        btnMoveToFiducial->setObjectName(QStringLiteral("btnMoveToFiducial"));

        verticalLayout_14->addWidget(btnMoveToFiducial);

        label_54 = new QLabel(verticalLayoutWidget_5);
        label_54->setObjectName(QStringLiteral("label_54"));
        label_54->setFont(font);
        label_54->setAlignment(Qt::AlignCenter);

        verticalLayout_14->addWidget(label_54);

        editSendCommandXY = new QLineEdit(verticalLayoutWidget_5);
        editSendCommandXY->setObjectName(QStringLiteral("editSendCommandXY"));

        verticalLayout_14->addWidget(editSendCommandXY);

        btnSendCommandXY = new QPushButton(verticalLayoutWidget_5);
        btnSendCommandXY->setObjectName(QStringLiteral("btnSendCommandXY"));

        verticalLayout_14->addWidget(btnSendCommandXY);


        verticalLayout_13->addLayout(verticalLayout_14);


        gridLayout_24->addLayout(verticalLayout_13, 0, 0, 1, 1);


        gridLayout_28->addLayout(gridLayout_24, 1, 0, 1, 1);

        verticalLayout_16 = new QVBoxLayout();
        verticalLayout_16->setObjectName(QStringLiteral("verticalLayout_16"));
        label_55 = new QLabel(verticalLayoutWidget_5);
        label_55->setObjectName(QStringLiteral("label_55"));
        label_55->setFont(font);
        label_55->setAlignment(Qt::AlignCenter);

        verticalLayout_16->addWidget(label_55);

        gridLayout_26 = new QGridLayout();
        gridLayout_26->setObjectName(QStringLiteral("gridLayout_26"));
        cboBaudXY = new QComboBox(verticalLayoutWidget_5);
        cboBaudXY->setObjectName(QStringLiteral("cboBaudXY"));

        gridLayout_26->addWidget(cboBaudXY, 1, 1, 1, 1);

        gridLayout_29 = new QGridLayout();
        gridLayout_29->setObjectName(QStringLiteral("gridLayout_29"));
        label_56 = new QLabel(verticalLayoutWidget_5);
        label_56->setObjectName(QStringLiteral("label_56"));

        gridLayout_29->addWidget(label_56, 0, 1, 1, 1);


        gridLayout_26->addLayout(gridLayout_29, 2, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        spinVelocityXY = new QDoubleSpinBox(verticalLayoutWidget_5);
        spinVelocityXY->setObjectName(QStringLiteral("spinVelocityXY"));

        horizontalLayout_6->addWidget(spinVelocityXY);

        btnSetVelocityXY = new QPushButton(verticalLayoutWidget_5);
        btnSetVelocityXY->setObjectName(QStringLiteral("btnSetVelocityXY"));

        horizontalLayout_6->addWidget(btnSetVelocityXY);


        gridLayout_26->addLayout(horizontalLayout_6, 2, 1, 1, 1);

        gridLayout_30 = new QGridLayout();
        gridLayout_30->setObjectName(QStringLiteral("gridLayout_30"));
        label_57 = new QLabel(verticalLayoutWidget_5);
        label_57->setObjectName(QStringLiteral("label_57"));

        gridLayout_30->addWidget(label_57, 0, 0, 1, 1);


        gridLayout_26->addLayout(gridLayout_30, 1, 0, 1, 1);


        verticalLayout_16->addLayout(gridLayout_26);


        gridLayout_28->addLayout(verticalLayout_16, 0, 0, 1, 1);

        verticalLayout_17 = new QVBoxLayout();
        verticalLayout_17->setObjectName(QStringLiteral("verticalLayout_17"));
        label_58 = new QLabel(verticalLayoutWidget_5);
        label_58->setObjectName(QStringLiteral("label_58"));
        label_58->setFont(font);
        label_58->setAlignment(Qt::AlignCenter);

        verticalLayout_17->addWidget(label_58);

        btnCalibrateXY = new QPushButton(verticalLayoutWidget_5);
        btnCalibrateXY->setObjectName(QStringLiteral("btnCalibrateXY"));

        verticalLayout_17->addWidget(btnCalibrateXY);

        btnMeasureRangeXY = new QPushButton(verticalLayoutWidget_5);
        btnMeasureRangeXY->setObjectName(QStringLiteral("btnMeasureRangeXY"));

        verticalLayout_17->addWidget(btnMeasureRangeXY);

        label_17 = new QLabel(verticalLayoutWidget_5);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setFont(font);
        label_17->setAlignment(Qt::AlignCenter);

        verticalLayout_17->addWidget(label_17);

        btnAbortXY = new QPushButton(verticalLayoutWidget_5);
        btnAbortXY->setObjectName(QStringLiteral("btnAbortXY"));
        btnAbortXY->setFocusPolicy(Qt::NoFocus);

        verticalLayout_17->addWidget(btnAbortXY);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_17->addItem(verticalSpacer);


        gridLayout_28->addLayout(verticalLayout_17, 1, 1, 1, 1);

        verticalLayout_18 = new QVBoxLayout();
        verticalLayout_18->setObjectName(QStringLiteral("verticalLayout_18"));
        label_59 = new QLabel(verticalLayoutWidget_5);
        label_59->setObjectName(QStringLiteral("label_59"));
        label_59->setFont(font);
        label_59->setAlignment(Qt::AlignCenter);

        verticalLayout_18->addWidget(label_59);

        btnConnectXY = new QPushButton(verticalLayoutWidget_5);
        btnConnectXY->setObjectName(QStringLiteral("btnConnectXY"));

        verticalLayout_18->addWidget(btnConnectXY);

        btnDisconnectXY = new QPushButton(verticalLayoutWidget_5);
        btnDisconnectXY->setObjectName(QStringLiteral("btnDisconnectXY"));

        verticalLayout_18->addWidget(btnDisconnectXY);


        gridLayout_28->addLayout(verticalLayout_18, 0, 1, 1, 1);


        verticalLayout_5->addLayout(gridLayout_28);


        verticalLayout_4->addLayout(verticalLayout_5);

        chkJoystickOn = new QCheckBox(StageSettingsTab);
        chkJoystickOn->setObjectName(QStringLiteral("chkJoystickOn"));
        chkJoystickOn->setGeometry(QRect(180, 410, 201, 20));
        chkJoystickOn->setLayoutDirection(Qt::RightToLeft);
        chkKeypadOn = new QCheckBox(StageSettingsTab);
        chkKeypadOn->setObjectName(QStringLiteral("chkKeypadOn"));
        chkKeypadOn->setGeometry(QRect(430, 430, 221, 17));
        chkKeypadOn->setLayoutDirection(Qt::RightToLeft);
        ZStageFrame = new QFrame(StageSettingsTab);
        ZStageFrame->setObjectName(QStringLiteral("ZStageFrame"));
        ZStageFrame->setGeometry(QRect(430, 90, 221, 341));
        ZStageFrame->setFrameShape(QFrame::StyledPanel);
        ZStageFrame->setFrameShadow(QFrame::Raised);
        verticalLayoutWidget_6 = new QWidget(ZStageFrame);
        verticalLayoutWidget_6->setObjectName(QStringLiteral("verticalLayoutWidget_6"));
        verticalLayoutWidget_6->setGeometry(QRect(0, 0, 221, 331));
        ZStageLayout = new QVBoxLayout(verticalLayoutWidget_6);
        ZStageLayout->setObjectName(QStringLiteral("ZStageLayout"));
        ZStageLayout->setContentsMargins(0, 0, 0, 0);
        label_100 = new QLabel(verticalLayoutWidget_6);
        label_100->setObjectName(QStringLiteral("label_100"));
        label_100->setFont(font);
        label_100->setCursor(QCursor(Qt::ArrowCursor));
        label_100->setAlignment(Qt::AlignCenter);

        ZStageLayout->addWidget(label_100);

        verticalLayout_22 = new QVBoxLayout();
        verticalLayout_22->setObjectName(QStringLiteral("verticalLayout_22"));
        verticalLayout_24 = new QVBoxLayout();
        verticalLayout_24->setObjectName(QStringLiteral("verticalLayout_24"));
        label_101 = new QLabel(verticalLayoutWidget_6);
        label_101->setObjectName(QStringLiteral("label_101"));
        label_101->setFont(font);
        label_101->setAlignment(Qt::AlignCenter);

        verticalLayout_24->addWidget(label_101);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        btnConnectZ = new QPushButton(verticalLayoutWidget_6);
        btnConnectZ->setObjectName(QStringLiteral("btnConnectZ"));

        horizontalLayout_17->addWidget(btnConnectZ);

        btnDisconnectZ = new QPushButton(verticalLayoutWidget_6);
        btnDisconnectZ->setObjectName(QStringLiteral("btnDisconnectZ"));

        horizontalLayout_17->addWidget(btnDisconnectZ);


        verticalLayout_24->addLayout(horizontalLayout_17);


        verticalLayout_22->addLayout(verticalLayout_24);

        label_104 = new QLabel(verticalLayoutWidget_6);
        label_104->setObjectName(QStringLiteral("label_104"));
        label_104->setFont(font);
        label_104->setAlignment(Qt::AlignCenter);

        verticalLayout_22->addWidget(label_104);

        gridLayout_17 = new QGridLayout();
        gridLayout_17->setObjectName(QStringLiteral("gridLayout_17"));
        lbl_positionZ = new QLabel(verticalLayoutWidget_6);
        lbl_positionZ->setObjectName(QStringLiteral("lbl_positionZ"));
        lbl_positionZ->setAlignment(Qt::AlignCenter);

        gridLayout_17->addWidget(lbl_positionZ, 0, 1, 1, 1);

        label_106 = new QLabel(verticalLayoutWidget_6);
        label_106->setObjectName(QStringLiteral("label_106"));

        gridLayout_17->addWidget(label_106, 0, 0, 1, 1);


        verticalLayout_22->addLayout(gridLayout_17);

        gridLayout_27 = new QGridLayout();
        gridLayout_27->setObjectName(QStringLiteral("gridLayout_27"));
        spinPositionAbsoluteZ = new QDoubleSpinBox(verticalLayoutWidget_6);
        spinPositionAbsoluteZ->setObjectName(QStringLiteral("spinPositionAbsoluteZ"));
        spinPositionAbsoluteZ->setMinimum(0);
        spinPositionAbsoluteZ->setMaximum(200);

        gridLayout_27->addWidget(spinPositionAbsoluteZ, 1, 1, 1, 1);

        spinPositionRelativeZ = new QDoubleSpinBox(verticalLayoutWidget_6);
        spinPositionRelativeZ->setObjectName(QStringLiteral("spinPositionRelativeZ"));
        spinPositionRelativeZ->setMinimum(-200);
        spinPositionRelativeZ->setMaximum(200);

        gridLayout_27->addWidget(spinPositionRelativeZ, 1, 2, 1, 1);

        label_111 = new QLabel(verticalLayoutWidget_6);
        label_111->setObjectName(QStringLiteral("label_111"));
        label_111->setAlignment(Qt::AlignCenter);

        gridLayout_27->addWidget(label_111, 0, 2, 1, 1);

        label_110 = new QLabel(verticalLayoutWidget_6);
        label_110->setObjectName(QStringLiteral("label_110"));
        label_110->setAlignment(Qt::AlignCenter);

        gridLayout_27->addWidget(label_110, 0, 1, 1, 1);

        label_45 = new QLabel(verticalLayoutWidget_6);
        label_45->setObjectName(QStringLiteral("label_45"));
        label_45->setAlignment(Qt::AlignCenter);

        gridLayout_27->addWidget(label_45, 0, 0, 1, 1);

        label_108 = new QLabel(verticalLayoutWidget_6);
        label_108->setObjectName(QStringLiteral("label_108"));

        gridLayout_27->addWidget(label_108, 1, 0, 1, 1);


        verticalLayout_22->addLayout(gridLayout_27);

        verticalLayout_23 = new QVBoxLayout();
        verticalLayout_23->setObjectName(QStringLiteral("verticalLayout_23"));
        btnMoveAbsoluteZ = new QPushButton(verticalLayoutWidget_6);
        btnMoveAbsoluteZ->setObjectName(QStringLiteral("btnMoveAbsoluteZ"));

        verticalLayout_23->addWidget(btnMoveAbsoluteZ);

        btnMoveRelativeZ = new QPushButton(verticalLayoutWidget_6);
        btnMoveRelativeZ->setObjectName(QStringLiteral("btnMoveRelativeZ"));

        verticalLayout_23->addWidget(btnMoveRelativeZ);

        horizontalLayout_32 = new QHBoxLayout();
        horizontalLayout_32->setObjectName(QStringLiteral("horizontalLayout_32"));
        btnUpZ = new QPushButton(verticalLayoutWidget_6);
        btnUpZ->setObjectName(QStringLiteral("btnUpZ"));

        horizontalLayout_32->addWidget(btnUpZ);

        btnDownZ = new QPushButton(verticalLayoutWidget_6);
        btnDownZ->setObjectName(QStringLiteral("btnDownZ"));

        horizontalLayout_32->addWidget(btnDownZ);


        verticalLayout_23->addLayout(horizontalLayout_32);

        label_112 = new QLabel(verticalLayoutWidget_6);
        label_112->setObjectName(QStringLiteral("label_112"));
        label_112->setFont(font);
        label_112->setAlignment(Qt::AlignCenter);

        verticalLayout_23->addWidget(label_112);

        editSendCommandZ = new QLineEdit(verticalLayoutWidget_6);
        editSendCommandZ->setObjectName(QStringLiteral("editSendCommandZ"));

        verticalLayout_23->addWidget(editSendCommandZ);

        btnSendCommandZ = new QPushButton(verticalLayoutWidget_6);
        btnSendCommandZ->setObjectName(QStringLiteral("btnSendCommandZ"));

        verticalLayout_23->addWidget(btnSendCommandZ);


        verticalLayout_22->addLayout(verticalLayout_23);


        ZStageLayout->addLayout(verticalLayout_22);

        SettingsTab->addTab(StageSettingsTab, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayoutWidget_2 = new QWidget(tab);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(20, 10, 361, 152));
        gridLayout_7 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        label_107 = new QLabel(gridLayoutWidget_2);
        label_107->setObjectName(QStringLiteral("label_107"));

        gridLayout_7->addWidget(label_107, 0, 0, 1, 1);

        cboFocusAlgorithm = new QComboBox(gridLayoutWidget_2);
        cboFocusAlgorithm->setObjectName(QStringLiteral("cboFocusAlgorithm"));

        gridLayout_7->addWidget(cboFocusAlgorithm, 0, 1, 1, 1);

        label_114 = new QLabel(gridLayoutWidget_2);
        label_114->setObjectName(QStringLiteral("label_114"));

        gridLayout_7->addWidget(label_114, 3, 0, 1, 1);

        spinMaxFocus = new QDoubleSpinBox(gridLayoutWidget_2);
        spinMaxFocus->setObjectName(QStringLiteral("spinMaxFocus"));
        spinMaxFocus->setDecimals(3);
        spinMaxFocus->setMinimum(-12.5);
        spinMaxFocus->setMaximum(12.5);
        spinMaxFocus->setSingleStep(0.05);
        spinMaxFocus->setValue(8);

        gridLayout_7->addWidget(spinMaxFocus, 1, 1, 1, 1);

        label_109 = new QLabel(gridLayoutWidget_2);
        label_109->setObjectName(QStringLiteral("label_109"));

        gridLayout_7->addWidget(label_109, 1, 0, 1, 1);

        label_113 = new QLabel(gridLayoutWidget_2);
        label_113->setObjectName(QStringLiteral("label_113"));

        gridLayout_7->addWidget(label_113, 2, 0, 1, 1);

        label_115 = new QLabel(gridLayoutWidget_2);
        label_115->setObjectName(QStringLiteral("label_115"));

        gridLayout_7->addWidget(label_115, 4, 0, 1, 1);

        spinMinFocus = new QDoubleSpinBox(gridLayoutWidget_2);
        spinMinFocus->setObjectName(QStringLiteral("spinMinFocus"));
        spinMinFocus->setDecimals(3);
        spinMinFocus->setMinimum(-12.5);
        spinMinFocus->setMaximum(12.5);
        spinMinFocus->setSingleStep(0.005);
        spinMinFocus->setValue(5);

        gridLayout_7->addWidget(spinMinFocus, 2, 1, 1, 1);

        spinCoarseFocusStep = new QDoubleSpinBox(gridLayoutWidget_2);
        spinCoarseFocusStep->setObjectName(QStringLiteral("spinCoarseFocusStep"));
        spinCoarseFocusStep->setDecimals(3);
        spinCoarseFocusStep->setMinimum(0);
        spinCoarseFocusStep->setMaximum(25);
        spinCoarseFocusStep->setSingleStep(0.0001);
        spinCoarseFocusStep->setValue(0.1);

        gridLayout_7->addWidget(spinCoarseFocusStep, 3, 1, 1, 1);

        spinFineFocusStep = new QDoubleSpinBox(gridLayoutWidget_2);
        spinFineFocusStep->setObjectName(QStringLiteral("spinFineFocusStep"));
        spinFineFocusStep->setDecimals(3);
        spinFineFocusStep->setMaximum(25);
        spinFineFocusStep->setSingleStep(0.0001);
        spinFineFocusStep->setValue(0.002);

        gridLayout_7->addWidget(spinFineFocusStep, 4, 1, 1, 1);

        label_267 = new QLabel(tab);
        label_267->setObjectName(QStringLiteral("label_267"));
        label_267->setGeometry(QRect(20, 170, 421, 16));
        SettingsTab->addTab(tab, QString());
        FiducialMarksTab = new QWidget();
        FiducialMarksTab->setObjectName(QStringLiteral("FiducialMarksTab"));
        label_8 = new QLabel(FiducialMarksTab);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 20, 70, 16));
        label_8->setFont(font);
        lblFiducialCheck = new QLabel(FiducialMarksTab);
        lblFiducialCheck->setObjectName(QStringLiteral("lblFiducialCheck"));
        lblFiducialCheck->setGeometry(QRect(10, 340, 231, 20));
        lblFiducialCheck->setStyleSheet(QStringLiteral("color: red"));
        lblFiducialCheck->setWordWrap(true);
        gridLayoutWidget = new QWidget(FiducialMarksTab);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 60, 483, 271));
        gridLayout_12 = new QGridLayout(gridLayoutWidget);
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        gridLayout_12->setContentsMargins(0, 0, 0, 0);
        spnTopRight_Overview_X = new QDoubleSpinBox(gridLayoutWidget);
        spnTopRight_Overview_X->setObjectName(QStringLiteral("spnTopRight_Overview_X"));
        spnTopRight_Overview_X->setAutoFillBackground(true);
        spnTopRight_Overview_X->setStyleSheet(QStringLiteral(""));
        spnTopRight_Overview_X->setDecimals(0);
        spnTopRight_Overview_X->setMaximum(99999);

        gridLayout_12->addWidget(spnTopRight_Overview_X, 2, 1, 1, 1);

        spnBottomLeft_Overview_X = new QDoubleSpinBox(gridLayoutWidget);
        spnBottomLeft_Overview_X->setObjectName(QStringLiteral("spnBottomLeft_Overview_X"));
        spnBottomLeft_Overview_X->setAutoFillBackground(true);
        spnBottomLeft_Overview_X->setDecimals(0);
        spnBottomLeft_Overview_X->setMaximum(99999);

        gridLayout_12->addWidget(spnBottomLeft_Overview_X, 3, 1, 1, 1);

        spnBottomRight_Overview_X = new QDoubleSpinBox(gridLayoutWidget);
        spnBottomRight_Overview_X->setObjectName(QStringLiteral("spnBottomRight_Overview_X"));
        spnBottomRight_Overview_X->setAutoFillBackground(true);
        spnBottomRight_Overview_X->setDecimals(0);
        spnBottomRight_Overview_X->setMaximum(99999);

        gridLayout_12->addWidget(spnBottomRight_Overview_X, 4, 1, 1, 1);

        spnBottomLeft_Overview_Y = new QDoubleSpinBox(gridLayoutWidget);
        spnBottomLeft_Overview_Y->setObjectName(QStringLiteral("spnBottomLeft_Overview_Y"));
        spnBottomLeft_Overview_Y->setAutoFillBackground(true);
        spnBottomLeft_Overview_Y->setDecimals(0);
        spnBottomLeft_Overview_Y->setMaximum(99999);

        gridLayout_12->addWidget(spnBottomLeft_Overview_Y, 3, 2, 1, 1);

        spnTopRight_Overview_Y = new QDoubleSpinBox(gridLayoutWidget);
        spnTopRight_Overview_Y->setObjectName(QStringLiteral("spnTopRight_Overview_Y"));
        spnTopRight_Overview_Y->setAutoFillBackground(true);
        spnTopRight_Overview_Y->setStyleSheet(QStringLiteral(""));
        spnTopRight_Overview_Y->setDecimals(0);
        spnTopRight_Overview_Y->setMaximum(99999);

        gridLayout_12->addWidget(spnTopRight_Overview_Y, 2, 2, 1, 1);

        spnBottomRight_Overview_Y = new QDoubleSpinBox(gridLayoutWidget);
        spnBottomRight_Overview_Y->setObjectName(QStringLiteral("spnBottomRight_Overview_Y"));
        spnBottomRight_Overview_Y->setAutoFillBackground(true);
        spnBottomRight_Overview_Y->setDecimals(0);
        spnBottomRight_Overview_Y->setMaximum(99999);

        gridLayout_12->addWidget(spnBottomRight_Overview_Y, 4, 2, 1, 1);

        spnTopRight_Microscope_X = new QDoubleSpinBox(gridLayoutWidget);
        spnTopRight_Microscope_X->setObjectName(QStringLiteral("spnTopRight_Microscope_X"));
        spnTopRight_Microscope_X->setAutoFillBackground(true);
        spnTopRight_Microscope_X->setDecimals(0);
        spnTopRight_Microscope_X->setMaximum(99999);

        gridLayout_12->addWidget(spnTopRight_Microscope_X, 7, 1, 1, 1);

        spnTopLeft_Microscope_X = new QDoubleSpinBox(gridLayoutWidget);
        spnTopLeft_Microscope_X->setObjectName(QStringLiteral("spnTopLeft_Microscope_X"));
        spnTopLeft_Microscope_X->setAutoFillBackground(true);
        spnTopLeft_Microscope_X->setDecimals(0);
        spnTopLeft_Microscope_X->setMaximum(99999);

        gridLayout_12->addWidget(spnTopLeft_Microscope_X, 6, 1, 1, 1);

        spnBottomLeft_Microscope_X = new QDoubleSpinBox(gridLayoutWidget);
        spnBottomLeft_Microscope_X->setObjectName(QStringLiteral("spnBottomLeft_Microscope_X"));
        spnBottomLeft_Microscope_X->setAutoFillBackground(true);
        spnBottomLeft_Microscope_X->setDecimals(0);
        spnBottomLeft_Microscope_X->setMaximum(99999);

        gridLayout_12->addWidget(spnBottomLeft_Microscope_X, 8, 1, 1, 1);

        spnBottomRight_Microscope_X = new QDoubleSpinBox(gridLayoutWidget);
        spnBottomRight_Microscope_X->setObjectName(QStringLiteral("spnBottomRight_Microscope_X"));
        spnBottomRight_Microscope_X->setAutoFillBackground(true);
        spnBottomRight_Microscope_X->setDecimals(0);
        spnBottomRight_Microscope_X->setMaximum(99999);

        gridLayout_12->addWidget(spnBottomRight_Microscope_X, 9, 1, 1, 1);

        spnTopLeft_Microscope_Y = new QDoubleSpinBox(gridLayoutWidget);
        spnTopLeft_Microscope_Y->setObjectName(QStringLiteral("spnTopLeft_Microscope_Y"));
        spnTopLeft_Microscope_Y->setAutoFillBackground(true);
        spnTopLeft_Microscope_Y->setDecimals(0);
        spnTopLeft_Microscope_Y->setMaximum(99999);

        gridLayout_12->addWidget(spnTopLeft_Microscope_Y, 6, 2, 1, 1);

        spnTopRight_Microscope_Y = new QDoubleSpinBox(gridLayoutWidget);
        spnTopRight_Microscope_Y->setObjectName(QStringLiteral("spnTopRight_Microscope_Y"));
        spnTopRight_Microscope_Y->setAutoFillBackground(true);
        spnTopRight_Microscope_Y->setDecimals(0);
        spnTopRight_Microscope_Y->setMaximum(99999);

        gridLayout_12->addWidget(spnTopRight_Microscope_Y, 7, 2, 1, 1);

        spnBottomRight_Microscope_Y = new QDoubleSpinBox(gridLayoutWidget);
        spnBottomRight_Microscope_Y->setObjectName(QStringLiteral("spnBottomRight_Microscope_Y"));
        spnBottomRight_Microscope_Y->setAutoFillBackground(true);
        spnBottomRight_Microscope_Y->setDecimals(0);
        spnBottomRight_Microscope_Y->setMaximum(99999);

        gridLayout_12->addWidget(spnBottomRight_Microscope_Y, 9, 2, 1, 1);

        spnBottomLeft_Microscope_Y = new QDoubleSpinBox(gridLayoutWidget);
        spnBottomLeft_Microscope_Y->setObjectName(QStringLiteral("spnBottomLeft_Microscope_Y"));
        spnBottomLeft_Microscope_Y->setAutoFillBackground(true);
        spnBottomLeft_Microscope_Y->setDecimals(0);
        spnBottomLeft_Microscope_Y->setMaximum(99999);

        gridLayout_12->addWidget(spnBottomLeft_Microscope_Y, 8, 2, 1, 1);

        spnTopLeft_Microscope_Stage_Z = new QDoubleSpinBox(gridLayoutWidget);
        spnTopLeft_Microscope_Stage_Z->setObjectName(QStringLiteral("spnTopLeft_Microscope_Stage_Z"));
        spnTopLeft_Microscope_Stage_Z->setDecimals(3);
        spnTopLeft_Microscope_Stage_Z->setMaximum(500);

        gridLayout_12->addWidget(spnTopLeft_Microscope_Stage_Z, 6, 5, 1, 1);

        spnTopRight_Microscope_Stage_Z = new QDoubleSpinBox(gridLayoutWidget);
        spnTopRight_Microscope_Stage_Z->setObjectName(QStringLiteral("spnTopRight_Microscope_Stage_Z"));
        spnTopRight_Microscope_Stage_Z->setDecimals(3);
        spnTopRight_Microscope_Stage_Z->setMaximum(500);

        gridLayout_12->addWidget(spnTopRight_Microscope_Stage_Z, 7, 5, 1, 1);

        spnBottomLeft_Microscope_Stage_Z = new QDoubleSpinBox(gridLayoutWidget);
        spnBottomLeft_Microscope_Stage_Z->setObjectName(QStringLiteral("spnBottomLeft_Microscope_Stage_Z"));
        spnBottomLeft_Microscope_Stage_Z->setDecimals(3);
        spnBottomLeft_Microscope_Stage_Z->setMaximum(500);

        gridLayout_12->addWidget(spnBottomLeft_Microscope_Stage_Z, 8, 5, 1, 1);

        spnBottomRight_Microscope_Stage_Z = new QDoubleSpinBox(gridLayoutWidget);
        spnBottomRight_Microscope_Stage_Z->setObjectName(QStringLiteral("spnBottomRight_Microscope_Stage_Z"));
        spnBottomRight_Microscope_Stage_Z->setDecimals(3);
        spnBottomRight_Microscope_Stage_Z->setMaximum(500);

        gridLayout_12->addWidget(spnBottomRight_Microscope_Stage_Z, 9, 5, 1, 1);

        label_209 = new QLabel(gridLayoutWidget);
        label_209->setObjectName(QStringLiteral("label_209"));
        label_209->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_209, 0, 2, 1, 1);

        spnBottomLeft_Microscope_Stage_X = new QDoubleSpinBox(gridLayoutWidget);
        spnBottomLeft_Microscope_Stage_X->setObjectName(QStringLiteral("spnBottomLeft_Microscope_Stage_X"));
        spnBottomLeft_Microscope_Stage_X->setAutoFillBackground(true);
        spnBottomLeft_Microscope_Stage_X->setDecimals(3);
        spnBottomLeft_Microscope_Stage_X->setMaximum(500);

        gridLayout_12->addWidget(spnBottomLeft_Microscope_Stage_X, 8, 3, 1, 1);

        spnTopRight_Microscope_Stage_X = new QDoubleSpinBox(gridLayoutWidget);
        spnTopRight_Microscope_Stage_X->setObjectName(QStringLiteral("spnTopRight_Microscope_Stage_X"));
        spnTopRight_Microscope_Stage_X->setAutoFillBackground(true);
        spnTopRight_Microscope_Stage_X->setDecimals(3);
        spnTopRight_Microscope_Stage_X->setMaximum(500);

        gridLayout_12->addWidget(spnTopRight_Microscope_Stage_X, 7, 3, 1, 1);

        lbl_bottomright_overview = new QLabel(gridLayoutWidget);
        lbl_bottomright_overview->setObjectName(QStringLiteral("lbl_bottomright_overview"));

        gridLayout_12->addWidget(lbl_bottomright_overview, 4, 0, 1, 1);

        spnTopLeft_Overview_Stage_Y = new QDoubleSpinBox(gridLayoutWidget);
        spnTopLeft_Overview_Stage_Y->setObjectName(QStringLiteral("spnTopLeft_Overview_Stage_Y"));
        spnTopLeft_Overview_Stage_Y->setDecimals(3);
        spnTopLeft_Overview_Stage_Y->setMaximum(500);

        gridLayout_12->addWidget(spnTopLeft_Overview_Stage_Y, 1, 4, 1, 1);

        spnTopLeft_Overview_Stage_X = new QDoubleSpinBox(gridLayoutWidget);
        spnTopLeft_Overview_Stage_X->setObjectName(QStringLiteral("spnTopLeft_Overview_Stage_X"));
        spnTopLeft_Overview_Stage_X->setDecimals(3);
        spnTopLeft_Overview_Stage_X->setMaximum(500);

        gridLayout_12->addWidget(spnTopLeft_Overview_Stage_X, 1, 3, 1, 1);

        label_207 = new QLabel(gridLayoutWidget);
        label_207->setObjectName(QStringLiteral("label_207"));
        label_207->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_207, 5, 1, 1, 1);

        spnTopLeft_Microscope_Stage_X = new QDoubleSpinBox(gridLayoutWidget);
        spnTopLeft_Microscope_Stage_X->setObjectName(QStringLiteral("spnTopLeft_Microscope_Stage_X"));
        spnTopLeft_Microscope_Stage_X->setAutoFillBackground(true);
        spnTopLeft_Microscope_Stage_X->setDecimals(3);
        spnTopLeft_Microscope_Stage_X->setMaximum(500);

        gridLayout_12->addWidget(spnTopLeft_Microscope_Stage_X, 6, 3, 1, 1);

        label_216 = new QLabel(gridLayoutWidget);
        label_216->setObjectName(QStringLiteral("label_216"));

        gridLayout_12->addWidget(label_216, 2, 4, 1, 1);

        label_218 = new QLabel(gridLayoutWidget);
        label_218->setObjectName(QStringLiteral("label_218"));

        gridLayout_12->addWidget(label_218, 3, 4, 1, 1);

        label_208 = new QLabel(gridLayoutWidget);
        label_208->setObjectName(QStringLiteral("label_208"));
        label_208->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_208, 0, 1, 1, 1);

        label_215 = new QLabel(gridLayoutWidget);
        label_215->setObjectName(QStringLiteral("label_215"));

        gridLayout_12->addWidget(label_215, 2, 3, 1, 1);

        lbl_bottomleft_overview = new QLabel(gridLayoutWidget);
        lbl_bottomleft_overview->setObjectName(QStringLiteral("lbl_bottomleft_overview"));

        gridLayout_12->addWidget(lbl_bottomleft_overview, 3, 0, 1, 1);

        label_220 = new QLabel(gridLayoutWidget);
        label_220->setObjectName(QStringLiteral("label_220"));

        gridLayout_12->addWidget(label_220, 4, 4, 1, 1);

        spnTopLeft_Microscope_Stage_Y = new QDoubleSpinBox(gridLayoutWidget);
        spnTopLeft_Microscope_Stage_Y->setObjectName(QStringLiteral("spnTopLeft_Microscope_Stage_Y"));
        spnTopLeft_Microscope_Stage_Y->setAutoFillBackground(true);
        spnTopLeft_Microscope_Stage_Y->setDecimals(3);
        spnTopLeft_Microscope_Stage_Y->setMaximum(500);

        gridLayout_12->addWidget(spnTopLeft_Microscope_Stage_Y, 6, 4, 1, 1);

        spnBottomLeft_Microscope_Stage_Y = new QDoubleSpinBox(gridLayoutWidget);
        spnBottomLeft_Microscope_Stage_Y->setObjectName(QStringLiteral("spnBottomLeft_Microscope_Stage_Y"));
        spnBottomLeft_Microscope_Stage_Y->setAutoFillBackground(true);
        spnBottomLeft_Microscope_Stage_Y->setDecimals(3);
        spnBottomLeft_Microscope_Stage_Y->setMaximum(500);

        gridLayout_12->addWidget(spnBottomLeft_Microscope_Stage_Y, 8, 4, 1, 1);

        spnTopLeft_Overview_X = new QDoubleSpinBox(gridLayoutWidget);
        spnTopLeft_Overview_X->setObjectName(QStringLiteral("spnTopLeft_Overview_X"));
        spnTopLeft_Overview_X->setAutoFillBackground(true);
        spnTopLeft_Overview_X->setStyleSheet(QStringLiteral(""));
        spnTopLeft_Overview_X->setDecimals(0);
        spnTopLeft_Overview_X->setMaximum(99999);

        gridLayout_12->addWidget(spnTopLeft_Overview_X, 1, 1, 1, 1);

        spnTopLeft_Overview_Y = new QDoubleSpinBox(gridLayoutWidget);
        spnTopLeft_Overview_Y->setObjectName(QStringLiteral("spnTopLeft_Overview_Y"));
        spnTopLeft_Overview_Y->setAutoFillBackground(true);
        spnTopLeft_Overview_Y->setStyleSheet(QStringLiteral(""));
        spnTopLeft_Overview_Y->setDecimals(0);
        spnTopLeft_Overview_Y->setMaximum(99999);

        gridLayout_12->addWidget(spnTopLeft_Overview_Y, 1, 2, 1, 1);

        spnTopRight_Microscope_Stage_Y = new QDoubleSpinBox(gridLayoutWidget);
        spnTopRight_Microscope_Stage_Y->setObjectName(QStringLiteral("spnTopRight_Microscope_Stage_Y"));
        spnTopRight_Microscope_Stage_Y->setAutoFillBackground(true);
        spnTopRight_Microscope_Stage_Y->setDecimals(3);
        spnTopRight_Microscope_Stage_Y->setMaximum(500);

        gridLayout_12->addWidget(spnTopRight_Microscope_Stage_Y, 7, 4, 1, 1);

        label_210 = new QLabel(gridLayoutWidget);
        label_210->setObjectName(QStringLiteral("label_210"));
        label_210->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_210, 5, 2, 1, 1);

        lbl_bottomright_microscope = new QLabel(gridLayoutWidget);
        lbl_bottomright_microscope->setObjectName(QStringLiteral("lbl_bottomright_microscope"));

        gridLayout_12->addWidget(lbl_bottomright_microscope, 9, 0, 1, 1);

        label_212 = new QLabel(gridLayoutWidget);
        label_212->setObjectName(QStringLiteral("label_212"));
        label_212->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_212, 5, 4, 1, 1);

        label_217 = new QLabel(gridLayoutWidget);
        label_217->setObjectName(QStringLiteral("label_217"));

        gridLayout_12->addWidget(label_217, 3, 3, 1, 1);

        label_219 = new QLabel(gridLayoutWidget);
        label_219->setObjectName(QStringLiteral("label_219"));

        gridLayout_12->addWidget(label_219, 4, 3, 1, 1);

        label_214 = new QLabel(gridLayoutWidget);
        label_214->setObjectName(QStringLiteral("label_214"));
        label_214->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_214, 0, 4, 1, 1);

        lbl_bottomleft_microscope = new QLabel(gridLayoutWidget);
        lbl_bottomleft_microscope->setObjectName(QStringLiteral("lbl_bottomleft_microscope"));

        gridLayout_12->addWidget(lbl_bottomleft_microscope, 8, 0, 1, 1);

        label_221 = new QLabel(gridLayoutWidget);
        label_221->setObjectName(QStringLiteral("label_221"));
        label_221->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_221, 5, 5, 1, 1);

        label_213 = new QLabel(gridLayoutWidget);
        label_213->setObjectName(QStringLiteral("label_213"));
        label_213->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_213, 0, 3, 1, 1);

        spnBottomRight_Microscope_Stage_Y = new QDoubleSpinBox(gridLayoutWidget);
        spnBottomRight_Microscope_Stage_Y->setObjectName(QStringLiteral("spnBottomRight_Microscope_Stage_Y"));
        spnBottomRight_Microscope_Stage_Y->setAutoFillBackground(true);
        spnBottomRight_Microscope_Stage_Y->setDecimals(3);
        spnBottomRight_Microscope_Stage_Y->setMaximum(500);

        gridLayout_12->addWidget(spnBottomRight_Microscope_Stage_Y, 9, 4, 1, 1);

        spnBottomRight_Microscope_Stage_X = new QDoubleSpinBox(gridLayoutWidget);
        spnBottomRight_Microscope_Stage_X->setObjectName(QStringLiteral("spnBottomRight_Microscope_Stage_X"));
        spnBottomRight_Microscope_Stage_X->setAutoFillBackground(true);
        spnBottomRight_Microscope_Stage_X->setDecimals(3);
        spnBottomRight_Microscope_Stage_X->setMaximum(500);

        gridLayout_12->addWidget(spnBottomRight_Microscope_Stage_X, 9, 3, 1, 1);

        label_211 = new QLabel(gridLayoutWidget);
        label_211->setObjectName(QStringLiteral("label_211"));
        label_211->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_211, 5, 3, 1, 1);

        label_82 = new QLabel(gridLayoutWidget);
        label_82->setObjectName(QStringLiteral("label_82"));
        label_82->setFont(font);

        gridLayout_12->addWidget(label_82, 0, 0, 1, 1);

        lbl_topleft_overview = new QLabel(gridLayoutWidget);
        lbl_topleft_overview->setObjectName(QStringLiteral("lbl_topleft_overview"));

        gridLayout_12->addWidget(lbl_topleft_overview, 1, 0, 1, 1);

        lbl_topright_overview = new QLabel(gridLayoutWidget);
        lbl_topright_overview->setObjectName(QStringLiteral("lbl_topright_overview"));

        gridLayout_12->addWidget(lbl_topright_overview, 2, 0, 1, 1);

        label_95 = new QLabel(gridLayoutWidget);
        label_95->setObjectName(QStringLiteral("label_95"));
        label_95->setFont(font);

        gridLayout_12->addWidget(label_95, 5, 0, 1, 1);

        lbl_topleft_microscope = new QLabel(gridLayoutWidget);
        lbl_topleft_microscope->setObjectName(QStringLiteral("lbl_topleft_microscope"));

        gridLayout_12->addWidget(lbl_topleft_microscope, 6, 0, 1, 1);

        lbl_topright_microscope = new QLabel(gridLayoutWidget);
        lbl_topright_microscope->setObjectName(QStringLiteral("lbl_topright_microscope"));

        gridLayout_12->addWidget(lbl_topright_microscope, 7, 0, 1, 1);

        label_224 = new QLabel(gridLayoutWidget);
        label_224->setObjectName(QStringLiteral("label_224"));

        gridLayout_12->addWidget(label_224, 4, 5, 1, 1);

        label_79 = new QLabel(FiducialMarksTab);
        label_79->setObjectName(QStringLiteral("label_79"));
        label_79->setGeometry(QRect(510, 180, 151, 31));
        label_79->setWordWrap(true);
        label_72 = new QLabel(FiducialMarksTab);
        label_72->setObjectName(QStringLiteral("label_72"));
        label_72->setGeometry(QRect(700, 180, 41, 41));
        label_72->setPixmap(QPixmap(QString::fromUtf8("icons/24/marks.png")));
        label_72->setScaledContents(true);
        label_222 = new QLabel(FiducialMarksTab);
        label_222->setObjectName(QStringLiteral("label_222"));
        label_222->setGeometry(QRect(110, 40, 76, 21));
        label_223 = new QLabel(FiducialMarksTab);
        label_223->setObjectName(QStringLiteral("label_223"));
        label_223->setGeometry(QRect(260, 40, 81, 20));
        verticalLayoutWidget_2 = new QWidget(FiducialMarksTab);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(510, 230, 231, 101));
        verticalLayout_12 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(0, 0, 0, 0);
        label_96 = new QLabel(verticalLayoutWidget_2);
        label_96->setObjectName(QStringLiteral("label_96"));
        label_96->setFont(font);

        verticalLayout_12->addWidget(label_96);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_97 = new QLabel(verticalLayoutWidget_2);
        label_97->setObjectName(QStringLiteral("label_97"));
        label_97->setWordWrap(true);

        horizontalLayout->addWidget(label_97);


        verticalLayout_12->addLayout(horizontalLayout);

        btnCalcTransformationMatrix = new QPushButton(verticalLayoutWidget_2);
        btnCalcTransformationMatrix->setObjectName(QStringLiteral("btnCalcTransformationMatrix"));

        verticalLayout_12->addWidget(btnCalcTransformationMatrix);

        verticalLayoutWidget_3 = new QWidget(FiducialMarksTab);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(510, 60, 231, 111));
        verticalLayout_19 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_19->setObjectName(QStringLiteral("verticalLayout_19"));
        verticalLayout_19->setContentsMargins(0, 0, 0, 0);
        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        label_71 = new QLabel(verticalLayoutWidget_3);
        label_71->setObjectName(QStringLiteral("label_71"));
        label_71->setFont(font);

        verticalLayout_15->addWidget(label_71);

        cboSelectFiducial = new QComboBox(verticalLayoutWidget_3);
        cboSelectFiducial->setObjectName(QStringLiteral("cboSelectFiducial"));

        verticalLayout_15->addWidget(cboSelectFiducial);

        btnDeleteFiducial = new QPushButton(verticalLayoutWidget_3);
        btnDeleteFiducial->setObjectName(QStringLiteral("btnDeleteFiducial"));
        QIcon icon;
        icon.addFile(QStringLiteral("icons/24/trashcan.ico"), QSize(), QIcon::Normal, QIcon::Off);
        btnDeleteFiducial->setIcon(icon);

        verticalLayout_15->addWidget(btnDeleteFiducial);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        chkLockFiducial = new QCheckBox(verticalLayoutWidget_3);
        chkLockFiducial->setObjectName(QStringLiteral("chkLockFiducial"));
        chkLockFiducial->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_2->addWidget(chkLockFiducial);


        verticalLayout_15->addLayout(horizontalLayout_2);


        verticalLayout_19->addLayout(verticalLayout_15);

        SettingsTab->addTab(FiducialMarksTab, QString());
        TargetSettingsTab = new QWidget();
        TargetSettingsTab->setObjectName(QStringLiteral("TargetSettingsTab"));
        formLayout_4 = new QFormLayout(TargetSettingsTab);
        formLayout_4->setObjectName(QStringLiteral("formLayout_4"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        label_4 = new QLabel(TargetSettingsTab);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_10->addWidget(label_4);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        AlgoComboBox = new QComboBox(TargetSettingsTab);
        AlgoComboBox->setObjectName(QStringLiteral("AlgoComboBox"));

        horizontalLayout_11->addWidget(AlgoComboBox);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_11);


        verticalLayout_10->addLayout(horizontalLayout_11);

        label = new QLabel(TargetSettingsTab);
        label->setObjectName(QStringLiteral("label"));
        QFont font1;
        font1.setFamily(QStringLiteral("MS Shell Dlg 2"));
        font1.setPointSize(8);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setUnderline(true);
        font1.setWeight(50);
        label->setFont(font1);
        label->setStyleSheet(QStringLiteral(""));

        verticalLayout_10->addWidget(label);

        gridLayout_20 = new QGridLayout();
        gridLayout_20->setObjectName(QStringLiteral("gridLayout_20"));
        ScoreThreshold = new QSlider(TargetSettingsTab);
        ScoreThreshold->setObjectName(QStringLiteral("ScoreThreshold"));
        ScoreThreshold->setMaximum(100);
        ScoreThreshold->setValue(70);
        ScoreThreshold->setOrientation(Qt::Horizontal);

        gridLayout_20->addWidget(ScoreThreshold, 2, 2, 1, 1);

        label_5 = new QLabel(TargetSettingsTab);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_20->addWidget(label_5, 3, 0, 1, 1);

        numClusters = new QSlider(TargetSettingsTab);
        numClusters->setObjectName(QStringLiteral("numClusters"));
        numClusters->setMaximum(20);
        numClusters->setValue(10);
        numClusters->setOrientation(Qt::Horizontal);

        gridLayout_20->addWidget(numClusters, 0, 2, 1, 1);

        distanceThreshold = new QSlider(TargetSettingsTab);
        distanceThreshold->setObjectName(QStringLiteral("distanceThreshold"));
        distanceThreshold->setMaximum(50);
        distanceThreshold->setValue(5);
        distanceThreshold->setOrientation(Qt::Horizontal);

        gridLayout_20->addWidget(distanceThreshold, 1, 2, 1, 1);

        label_2 = new QLabel(TargetSettingsTab);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_20->addWidget(label_2, 0, 0, 1, 1);

        scoreRegionArea = new QSlider(TargetSettingsTab);
        scoreRegionArea->setObjectName(QStringLiteral("scoreRegionArea"));
        scoreRegionArea->setMaximum(500);
        scoreRegionArea->setValue(100);
        scoreRegionArea->setOrientation(Qt::Horizontal);

        gridLayout_20->addWidget(scoreRegionArea, 3, 2, 1, 1);

        label_20 = new QLabel(TargetSettingsTab);
        label_20->setObjectName(QStringLiteral("label_20"));

        gridLayout_20->addWidget(label_20, 2, 0, 1, 1);

        label_3 = new QLabel(TargetSettingsTab);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_20->addWidget(label_3, 1, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        ScoreThresholdLbl = new QLabel(TargetSettingsTab);
        ScoreThresholdLbl->setObjectName(QStringLiteral("ScoreThresholdLbl"));
        ScoreThresholdLbl->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout_9->addWidget(ScoreThresholdLbl);

        label_70 = new QLabel(TargetSettingsTab);
        label_70->setObjectName(QStringLiteral("label_70"));

        horizontalLayout_9->addWidget(label_70);


        gridLayout_20->addLayout(horizontalLayout_9, 2, 3, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        lblScoreSizeFactor = new QLabel(TargetSettingsTab);
        lblScoreSizeFactor->setObjectName(QStringLiteral("lblScoreSizeFactor"));

        horizontalLayout_10->addWidget(lblScoreSizeFactor);

        label_73 = new QLabel(TargetSettingsTab);
        label_73->setObjectName(QStringLiteral("label_73"));

        horizontalLayout_10->addWidget(label_73);


        gridLayout_20->addLayout(horizontalLayout_10, 3, 3, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_distance = new QLabel(TargetSettingsTab);
        label_distance->setObjectName(QStringLiteral("label_distance"));

        horizontalLayout_8->addWidget(label_distance);

        label_22 = new QLabel(TargetSettingsTab);
        label_22->setObjectName(QStringLiteral("label_22"));

        horizontalLayout_8->addWidget(label_22);


        gridLayout_20->addLayout(horizontalLayout_8, 1, 3, 1, 1);

        labelCluster = new QLabel(TargetSettingsTab);
        labelCluster->setObjectName(QStringLiteral("labelCluster"));
        labelCluster->setLayoutDirection(Qt::RightToLeft);

        gridLayout_20->addWidget(labelCluster, 0, 3, 1, 1);


        verticalLayout_10->addLayout(gridLayout_20);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        chkTargetImageAsMask = new QCheckBox(TargetSettingsTab);
        chkTargetImageAsMask->setObjectName(QStringLiteral("chkTargetImageAsMask"));
        chkTargetImageAsMask->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_7->addWidget(chkTargetImageAsMask);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_4);


        verticalLayout_10->addLayout(horizontalLayout_7);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        spinSamplingDistance = new QSpinBox(TargetSettingsTab);
        spinSamplingDistance->setObjectName(QStringLiteral("spinSamplingDistance"));
        spinSamplingDistance->setMinimum(1);
        spinSamplingDistance->setMaximum(100);
        spinSamplingDistance->setValue(35);

        gridLayout_5->addWidget(spinSamplingDistance, 1, 1, 1, 1);

        cboSamplingType = new QComboBox(TargetSettingsTab);
        cboSamplingType->setObjectName(QStringLiteral("cboSamplingType"));

        gridLayout_5->addWidget(cboSamplingType, 0, 1, 1, 1);

        label_9 = new QLabel(TargetSettingsTab);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_5->addWidget(label_9, 0, 0, 1, 1);

        label_43 = new QLabel(TargetSettingsTab);
        label_43->setObjectName(QStringLiteral("label_43"));

        gridLayout_5->addWidget(label_43, 1, 0, 1, 1);

        label_42 = new QLabel(TargetSettingsTab);
        label_42->setObjectName(QStringLiteral("label_42"));

        gridLayout_5->addWidget(label_42, 2, 0, 1, 1);

        spinExclusionDistance = new QSpinBox(TargetSettingsTab);
        spinExclusionDistance->setObjectName(QStringLiteral("spinExclusionDistance"));
        spinExclusionDistance->setMaximum(100);
        spinExclusionDistance->setValue(35);

        gridLayout_5->addWidget(spinExclusionDistance, 2, 1, 1, 1);


        verticalLayout_10->addLayout(gridLayout_5);


        formLayout_4->setLayout(0, QFormLayout::LabelRole, verticalLayout_10);

        SettingsTab->addTab(TargetSettingsTab, QString());
        Drawing = new QWidget();
        Drawing->setObjectName(QStringLiteral("Drawing"));
        formLayout_3 = new QFormLayout(Drawing);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        verticalLayout_21 = new QVBoxLayout();
        verticalLayout_21->setObjectName(QStringLiteral("verticalLayout_21"));
        gridLayout_9 = new QGridLayout();
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        btnSelectColour = new QPushButton(Drawing);
        btnSelectColour->setObjectName(QStringLiteral("btnSelectColour"));

        gridLayout_9->addWidget(btnSelectColour, 1, 1, 1, 1);

        cboAnnotationColour = new QComboBox(Drawing);
        cboAnnotationColour->setObjectName(QStringLiteral("cboAnnotationColour"));

        gridLayout_9->addWidget(cboAnnotationColour, 1, 0, 1, 1);

        label_6 = new QLabel(Drawing);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_9->addWidget(label_6, 0, 0, 1, 1);


        verticalLayout_21->addLayout(gridLayout_9);

        label_10 = new QLabel(Drawing);
        label_10->setObjectName(QStringLiteral("label_10"));

        verticalLayout_21->addWidget(label_10);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        spinGridOffsetY = new QDoubleSpinBox(Drawing);
        spinGridOffsetY->setObjectName(QStringLiteral("spinGridOffsetY"));

        gridLayout_2->addWidget(spinGridOffsetY, 1, 2, 1, 1);

        spinGridOffsetX = new QDoubleSpinBox(Drawing);
        spinGridOffsetX->setObjectName(QStringLiteral("spinGridOffsetX"));

        gridLayout_2->addWidget(spinGridOffsetX, 0, 2, 1, 1);

        spinGridSpacingY = new QDoubleSpinBox(Drawing);
        spinGridSpacingY->setObjectName(QStringLiteral("spinGridSpacingY"));

        gridLayout_2->addWidget(spinGridSpacingY, 3, 2, 1, 1);

        sliderGridOffsetX = new QSlider(Drawing);
        sliderGridOffsetX->setObjectName(QStringLiteral("sliderGridOffsetX"));
        sliderGridOffsetX->setMaximum(500);
        sliderGridOffsetX->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(sliderGridOffsetX, 0, 1, 1, 1);

        label_31 = new QLabel(Drawing);
        label_31->setObjectName(QStringLiteral("label_31"));

        gridLayout_2->addWidget(label_31, 1, 0, 1, 1);

        sliderGridOffsetY = new QSlider(Drawing);
        sliderGridOffsetY->setObjectName(QStringLiteral("sliderGridOffsetY"));
        sliderGridOffsetY->setMaximum(500);
        sliderGridOffsetY->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(sliderGridOffsetY, 1, 1, 1, 1);

        label_33 = new QLabel(Drawing);
        label_33->setObjectName(QStringLiteral("label_33"));

        gridLayout_2->addWidget(label_33, 3, 0, 1, 1);

        sliderGridSpacingY = new QSlider(Drawing);
        sliderGridSpacingY->setObjectName(QStringLiteral("sliderGridSpacingY"));
        sliderGridSpacingY->setMaximum(500);
        sliderGridSpacingY->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(sliderGridSpacingY, 3, 1, 1, 1);

        label_32 = new QLabel(Drawing);
        label_32->setObjectName(QStringLiteral("label_32"));

        gridLayout_2->addWidget(label_32, 2, 0, 1, 1);

        sliderGridSpacingX = new QSlider(Drawing);
        sliderGridSpacingX->setObjectName(QStringLiteral("sliderGridSpacingX"));
        sliderGridSpacingX->setMaximum(500);
        sliderGridSpacingX->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(sliderGridSpacingX, 2, 1, 1, 1);

        spinGridSpacingX = new QDoubleSpinBox(Drawing);
        spinGridSpacingX->setObjectName(QStringLiteral("spinGridSpacingX"));

        gridLayout_2->addWidget(spinGridSpacingX, 2, 2, 1, 1);

        label_30 = new QLabel(Drawing);
        label_30->setObjectName(QStringLiteral("label_30"));

        gridLayout_2->addWidget(label_30, 0, 0, 1, 1);


        verticalLayout_21->addLayout(gridLayout_2);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        chkDisplayGrid = new QCheckBox(Drawing);
        chkDisplayGrid->setObjectName(QStringLiteral("chkDisplayGrid"));
        chkDisplayGrid->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_13->addWidget(chkDisplayGrid);

        btnCenterGrid = new QPushButton(Drawing);
        btnCenterGrid->setObjectName(QStringLiteral("btnCenterGrid"));

        horizontalLayout_13->addWidget(btnCenterGrid);


        verticalLayout_21->addLayout(horizontalLayout_13);


        formLayout_3->setLayout(0, QFormLayout::LabelRole, verticalLayout_21);

        SettingsTab->addTab(Drawing, QString());
        CalibrationTab = new QWidget();
        CalibrationTab->setObjectName(QStringLiteral("CalibrationTab"));
        gridLayout_14 = new QGridLayout(CalibrationTab);
        gridLayout_14->setObjectName(QStringLiteral("gridLayout_14"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_39 = new QLabel(CalibrationTab);
        label_39->setObjectName(QStringLiteral("label_39"));

        verticalLayout->addWidget(label_39);

        chkFixedAspect = new QCheckBox(CalibrationTab);
        chkFixedAspect->setObjectName(QStringLiteral("chkFixedAspect"));
        chkFixedAspect->setLayoutDirection(Qt::RightToLeft);

        verticalLayout->addWidget(chkFixedAspect);

        chkZeroDistortion = new QCheckBox(CalibrationTab);
        chkZeroDistortion->setObjectName(QStringLiteral("chkZeroDistortion"));
        chkZeroDistortion->setLayoutDirection(Qt::RightToLeft);

        verticalLayout->addWidget(chkZeroDistortion);

        chkFixPrincipalPointCenter = new QCheckBox(CalibrationTab);
        chkFixPrincipalPointCenter->setObjectName(QStringLiteral("chkFixPrincipalPointCenter"));
        chkFixPrincipalPointCenter->setLayoutDirection(Qt::RightToLeft);

        verticalLayout->addWidget(chkFixPrincipalPointCenter);

        chkIntrinsicGuess = new QCheckBox(CalibrationTab);
        chkIntrinsicGuess->setObjectName(QStringLiteral("chkIntrinsicGuess"));
        chkIntrinsicGuess->setLayoutDirection(Qt::RightToLeft);

        verticalLayout->addWidget(chkIntrinsicGuess);

        chkFixFocalLength = new QCheckBox(CalibrationTab);
        chkFixFocalLength->setObjectName(QStringLiteral("chkFixFocalLength"));
        chkFixFocalLength->setLayoutDirection(Qt::RightToLeft);

        verticalLayout->addWidget(chkFixFocalLength);


        gridLayout_14->addLayout(verticalLayout, 2, 0, 2, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_26 = new QLabel(CalibrationTab);
        label_26->setObjectName(QStringLiteral("label_26"));

        verticalLayout_2->addWidget(label_26);

        chkCV_CALIB_CB_ADAPTIVE_THRESH = new QCheckBox(CalibrationTab);
        chkCV_CALIB_CB_ADAPTIVE_THRESH->setObjectName(QStringLiteral("chkCV_CALIB_CB_ADAPTIVE_THRESH"));
        chkCV_CALIB_CB_ADAPTIVE_THRESH->setLayoutDirection(Qt::RightToLeft);

        verticalLayout_2->addWidget(chkCV_CALIB_CB_ADAPTIVE_THRESH);

        chkCV_CALIB_CB_NORMALIZE_IMAGE = new QCheckBox(CalibrationTab);
        chkCV_CALIB_CB_NORMALIZE_IMAGE->setObjectName(QStringLiteral("chkCV_CALIB_CB_NORMALIZE_IMAGE"));
        chkCV_CALIB_CB_NORMALIZE_IMAGE->setLayoutDirection(Qt::RightToLeft);

        verticalLayout_2->addWidget(chkCV_CALIB_CB_NORMALIZE_IMAGE);

        chkCV_CALIB_CB_FILTER_QUADS = new QCheckBox(CalibrationTab);
        chkCV_CALIB_CB_FILTER_QUADS->setObjectName(QStringLiteral("chkCV_CALIB_CB_FILTER_QUADS"));
        chkCV_CALIB_CB_FILTER_QUADS->setLayoutDirection(Qt::RightToLeft);

        verticalLayout_2->addWidget(chkCV_CALIB_CB_FILTER_QUADS);

        chkCALIB_CB_FAST_CHECK = new QCheckBox(CalibrationTab);
        chkCALIB_CB_FAST_CHECK->setObjectName(QStringLiteral("chkCALIB_CB_FAST_CHECK"));
        chkCALIB_CB_FAST_CHECK->setLayoutDirection(Qt::RightToLeft);

        verticalLayout_2->addWidget(chkCALIB_CB_FAST_CHECK);


        gridLayout_14->addLayout(verticalLayout_2, 1, 1, 2, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_14->addItem(horizontalSpacer_6, 3, 2, 1, 1);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        label_21 = new QLabel(CalibrationTab);
        label_21->setObjectName(QStringLiteral("label_21"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_21);

        spinItemsInRow = new QSpinBox(CalibrationTab);
        spinItemsInRow->setObjectName(QStringLiteral("spinItemsInRow"));
        spinItemsInRow->setMinimum(1);
        spinItemsInRow->setValue(5);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, spinItemsInRow);

        label_23 = new QLabel(CalibrationTab);
        label_23->setObjectName(QStringLiteral("label_23"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_23);

        spinItemsInColumn = new QSpinBox(CalibrationTab);
        spinItemsInColumn->setObjectName(QStringLiteral("spinItemsInColumn"));
        spinItemsInColumn->setMinimum(1);
        spinItemsInColumn->setValue(5);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, spinItemsInColumn);

        label_24 = new QLabel(CalibrationTab);
        label_24->setObjectName(QStringLiteral("label_24"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_24);

        spinSizeSquare = new QSpinBox(CalibrationTab);
        spinSizeSquare->setObjectName(QStringLiteral("spinSizeSquare"));
        spinSizeSquare->setMinimum(1);
        spinSizeSquare->setMaximum(500);
        spinSizeSquare->setValue(50);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, spinSizeSquare);


        gridLayout_14->addLayout(formLayout_2, 1, 0, 1, 1);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_25 = new QLabel(CalibrationTab);
        label_25->setObjectName(QStringLiteral("label_25"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_25);

        cboCalibrateAlgorithm = new QComboBox(CalibrationTab);
        cboCalibrateAlgorithm->setObjectName(QStringLiteral("cboCalibrateAlgorithm"));

        formLayout->setWidget(0, QFormLayout::FieldRole, cboCalibrateAlgorithm);


        gridLayout_14->addLayout(formLayout, 0, 0, 1, 2);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_14->addItem(verticalSpacer_6, 4, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_27 = new QLabel(CalibrationTab);
        label_27->setObjectName(QStringLiteral("label_27"));

        verticalLayout_3->addWidget(label_27);

        chkCALIB_CB_CLUSTERING = new QCheckBox(CalibrationTab);
        chkCALIB_CB_CLUSTERING->setObjectName(QStringLiteral("chkCALIB_CB_CLUSTERING"));
        chkCALIB_CB_CLUSTERING->setLayoutDirection(Qt::RightToLeft);

        verticalLayout_3->addWidget(chkCALIB_CB_CLUSTERING);


        gridLayout_14->addLayout(verticalLayout_3, 3, 1, 1, 1);

        SettingsTab->addTab(CalibrationTab, QString());
        ThresholdSettingsTab = new QWidget();
        ThresholdSettingsTab->setObjectName(QStringLiteral("ThresholdSettingsTab"));
        verticalLayoutWidget_4 = new QWidget(ThresholdSettingsTab);
        verticalLayoutWidget_4->setObjectName(QStringLiteral("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(20, 30, 641, 301));
        verticalLayout_11 = new QVBoxLayout(verticalLayoutWidget_4);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(0, 0, 0, 0);
        gridLayout_18 = new QGridLayout();
        gridLayout_18->setObjectName(QStringLiteral("gridLayout_18"));
        NoClustersSlider = new QSlider(verticalLayoutWidget_4);
        NoClustersSlider->setObjectName(QStringLiteral("NoClustersSlider"));
        NoClustersSlider->setMinimum(2);
        NoClustersSlider->setMaximum(255);
        NoClustersSlider->setPageStep(5);
        NoClustersSlider->setOrientation(Qt::Horizontal);

        gridLayout_18->addWidget(NoClustersSlider, 4, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        cboThresholdType = new QComboBox(verticalLayoutWidget_4);
        cboThresholdType->setObjectName(QStringLiteral("cboThresholdType"));

        horizontalLayout_3->addWidget(cboThresholdType);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_10);


        gridLayout_18->addLayout(horizontalLayout_3, 3, 1, 1, 1);

        ThresholdMinSlider = new QSlider(verticalLayoutWidget_4);
        ThresholdMinSlider->setObjectName(QStringLiteral("ThresholdMinSlider"));
        ThresholdMinSlider->setEnabled(false);
        ThresholdMinSlider->setMaximum(254);
        ThresholdMinSlider->setOrientation(Qt::Horizontal);

        gridLayout_18->addWidget(ThresholdMinSlider, 1, 1, 1, 1);

        gridLayout_histogram = new QGridLayout();
        gridLayout_histogram->setObjectName(QStringLiteral("gridLayout_histogram"));
        gridLayout_15 = new QGridLayout();
        gridLayout_15->setObjectName(QStringLiteral("gridLayout_15"));
        gridLayout_15->setSizeConstraint(QLayout::SetFixedSize);
        ThresholdMaxLbl = new QLabel(verticalLayoutWidget_4);
        ThresholdMaxLbl->setObjectName(QStringLiteral("ThresholdMaxLbl"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ThresholdMaxLbl->sizePolicy().hasHeightForWidth());
        ThresholdMaxLbl->setSizePolicy(sizePolicy1);

        gridLayout_15->addWidget(ThresholdMaxLbl, 0, 2, 1, 1);

        ThresholdMinLbl = new QLabel(verticalLayoutWidget_4);
        ThresholdMinLbl->setObjectName(QStringLiteral("ThresholdMinLbl"));
        sizePolicy1.setHeightForWidth(ThresholdMinLbl->sizePolicy().hasHeightForWidth());
        ThresholdMinLbl->setSizePolicy(sizePolicy1);

        gridLayout_15->addWidget(ThresholdMinLbl, 0, 0, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_15->addItem(horizontalSpacer_7, 0, 1, 1, 1);


        gridLayout_histogram->addLayout(gridLayout_15, 1, 0, 1, 1);

        histogram_image = new QLabel(verticalLayoutWidget_4);
        histogram_image->setObjectName(QStringLiteral("histogram_image"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(histogram_image->sizePolicy().hasHeightForWidth());
        histogram_image->setSizePolicy(sizePolicy2);
        histogram_image->setFrameShape(QFrame::StyledPanel);
        histogram_image->setScaledContents(true);

        gridLayout_histogram->addWidget(histogram_image, 0, 0, 1, 1);


        gridLayout_18->addLayout(gridLayout_histogram, 0, 1, 1, 1);

        label_92 = new QLabel(verticalLayoutWidget_4);
        label_92->setObjectName(QStringLiteral("label_92"));

        gridLayout_18->addWidget(label_92, 0, 0, 1, 1);

        label_90 = new QLabel(verticalLayoutWidget_4);
        label_90->setObjectName(QStringLiteral("label_90"));

        gridLayout_18->addWidget(label_90, 1, 2, 1, 1);

        label_91 = new QLabel(verticalLayoutWidget_4);
        label_91->setObjectName(QStringLiteral("label_91"));

        gridLayout_18->addWidget(label_91, 2, 2, 1, 1);

        NoClustersLbl = new QLabel(verticalLayoutWidget_4);
        NoClustersLbl->setObjectName(QStringLiteral("NoClustersLbl"));

        gridLayout_18->addWidget(NoClustersLbl, 4, 2, 1, 1);

        labelThresholdMin = new QLabel(verticalLayoutWidget_4);
        labelThresholdMin->setObjectName(QStringLiteral("labelThresholdMin"));

        gridLayout_18->addWidget(labelThresholdMin, 1, 0, 1, 1);

        labelThresholdMax = new QLabel(verticalLayoutWidget_4);
        labelThresholdMax->setObjectName(QStringLiteral("labelThresholdMax"));
        labelThresholdMax->setStyleSheet(QStringLiteral(""));

        gridLayout_18->addWidget(labelThresholdMax, 2, 0, 1, 1);

        label_28 = new QLabel(verticalLayoutWidget_4);
        label_28->setObjectName(QStringLiteral("label_28"));

        gridLayout_18->addWidget(label_28, 3, 0, 1, 1);

        ThresholdMaxSlider = new QSlider(verticalLayoutWidget_4);
        ThresholdMaxSlider->setObjectName(QStringLiteral("ThresholdMaxSlider"));
        ThresholdMaxSlider->setEnabled(false);
        ThresholdMaxSlider->setMinimum(1);
        ThresholdMaxSlider->setMaximum(255);
        ThresholdMaxSlider->setValue(254);
        ThresholdMaxSlider->setOrientation(Qt::Horizontal);

        gridLayout_18->addWidget(ThresholdMaxSlider, 2, 1, 1, 1);

        label_12 = new QLabel(verticalLayoutWidget_4);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_18->addWidget(label_12, 4, 0, 1, 1);


        verticalLayout_11->addLayout(gridLayout_18);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        chkAutoThreshold = new QCheckBox(verticalLayoutWidget_4);
        chkAutoThreshold->setObjectName(QStringLiteral("chkAutoThreshold"));
        chkAutoThreshold->setLayoutDirection(Qt::RightToLeft);
        chkAutoThreshold->setChecked(true);

        horizontalLayout_12->addWidget(chkAutoThreshold);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_12);


        verticalLayout_11->addLayout(horizontalLayout_12);

        SettingsTab->addTab(ThresholdSettingsTab, QString());
        ConnectedComponentsTab = new QWidget();
        ConnectedComponentsTab->setObjectName(QStringLiteral("ConnectedComponentsTab"));
        gridLayout_16 = new QGridLayout(ConnectedComponentsTab);
        gridLayout_16->setObjectName(QStringLiteral("gridLayout_16"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_18 = new QLabel(ConnectedComponentsTab);
        label_18->setObjectName(QStringLiteral("label_18"));

        gridLayout->addWidget(label_18, 3, 0, 1, 1);

        sizeToleranceLargerSpinBox = new QSpinBox(ConnectedComponentsTab);
        sizeToleranceLargerSpinBox->setObjectName(QStringLiteral("sizeToleranceLargerSpinBox"));
        sizeToleranceLargerSpinBox->setMaximum(500);

        gridLayout->addWidget(sizeToleranceLargerSpinBox, 1, 2, 1, 1);

        label_29 = new QLabel(ConnectedComponentsTab);
        label_29->setObjectName(QStringLiteral("label_29"));

        gridLayout->addWidget(label_29, 2, 0, 1, 1);

        spinAspectTolerance = new QDoubleSpinBox(ConnectedComponentsTab);
        spinAspectTolerance->setObjectName(QStringLiteral("spinAspectTolerance"));
        spinAspectTolerance->setSingleStep(0.05);
        spinAspectTolerance->setValue(2);

        gridLayout->addWidget(spinAspectTolerance, 2, 2, 1, 1);

        label_14 = new QLabel(ConnectedComponentsTab);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout->addWidget(label_14, 0, 0, 1, 2);

        sizeToleranceSmallerSpinBox = new QSpinBox(ConnectedComponentsTab);
        sizeToleranceSmallerSpinBox->setObjectName(QStringLiteral("sizeToleranceSmallerSpinBox"));
        sizeToleranceSmallerSpinBox->setMaximum(100);

        gridLayout->addWidget(sizeToleranceSmallerSpinBox, 0, 2, 1, 1);

        label_16 = new QLabel(ConnectedComponentsTab);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout->addWidget(label_16, 1, 0, 1, 2);

        label_19 = new QLabel(ConnectedComponentsTab);
        label_19->setObjectName(QStringLiteral("label_19"));

        gridLayout->addWidget(label_19, 3, 2, 1, 1);

        huMomentSimilaritySlider = new QSlider(ConnectedComponentsTab);
        huMomentSimilaritySlider->setObjectName(QStringLiteral("huMomentSimilaritySlider"));
        huMomentSimilaritySlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(huMomentSimilaritySlider, 3, 1, 1, 1);


        gridLayout_16->addLayout(gridLayout, 0, 0, 1, 2);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_16->addItem(horizontalSpacer_8, 0, 2, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_16->addItem(verticalSpacer_3, 1, 0, 1, 1);

        SettingsTab->addTab(ConnectedComponentsTab, QString());
        Feedback = new QWidget();
        Feedback->setObjectName(QStringLiteral("Feedback"));
        gridLayoutWidget_4 = new QWidget(Feedback);
        gridLayoutWidget_4->setObjectName(QStringLiteral("gridLayoutWidget_4"));
        gridLayoutWidget_4->setGeometry(QRect(30, 20, 589, 391));
        gridLayout_11 = new QGridLayout(gridLayoutWidget_4);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        gridLayout_11->setContentsMargins(0, 0, 0, 0);
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        label_47 = new QLabel(gridLayoutWidget_4);
        label_47->setObjectName(QStringLiteral("label_47"));
        QFont font2;
        font2.setBold(true);
        font2.setItalic(false);
        font2.setUnderline(true);
        font2.setWeight(75);
        label_47->setFont(font2);

        verticalLayout_8->addWidget(label_47);

        label_66 = new QLabel(gridLayoutWidget_4);
        label_66->setObjectName(QStringLiteral("label_66"));
        QFont font3;
        font3.setBold(false);
        font3.setItalic(true);
        font3.setWeight(50);
        label_66->setFont(font3);

        verticalLayout_8->addWidget(label_66);

        gridLayout_22 = new QGridLayout();
        gridLayout_22->setObjectName(QStringLiteral("gridLayout_22"));
        label_60 = new QLabel(gridLayoutWidget_4);
        label_60->setObjectName(QStringLiteral("label_60"));

        gridLayout_22->addWidget(label_60, 5, 0, 1, 1);

        editFeedbackName = new QLineEdit(gridLayoutWidget_4);
        editFeedbackName->setObjectName(QStringLiteral("editFeedbackName"));

        gridLayout_22->addWidget(editFeedbackName, 2, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_63 = new QLabel(gridLayoutWidget_4);
        label_63->setObjectName(QStringLiteral("label_63"));

        horizontalLayout_4->addWidget(label_63);

        sliderFeedbackSatisfaction = new QSlider(gridLayoutWidget_4);
        sliderFeedbackSatisfaction->setObjectName(QStringLiteral("sliderFeedbackSatisfaction"));
        sliderFeedbackSatisfaction->setMaximum(5);
        sliderFeedbackSatisfaction->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(sliderFeedbackSatisfaction);

        label_64 = new QLabel(gridLayoutWidget_4);
        label_64->setObjectName(QStringLiteral("label_64"));

        horizontalLayout_4->addWidget(label_64);


        gridLayout_22->addLayout(horizontalLayout_4, 1, 1, 1, 1);

        editFeedbackInstitute = new QLineEdit(gridLayoutWidget_4);
        editFeedbackInstitute->setObjectName(QStringLiteral("editFeedbackInstitute"));

        gridLayout_22->addWidget(editFeedbackInstitute, 3, 1, 1, 1);

        label_48 = new QLabel(gridLayoutWidget_4);
        label_48->setObjectName(QStringLiteral("label_48"));

        gridLayout_22->addWidget(label_48, 2, 0, 1, 1);

        label_61 = new QLabel(gridLayoutWidget_4);
        label_61->setObjectName(QStringLiteral("label_61"));

        gridLayout_22->addWidget(label_61, 6, 0, 1, 1);

        label_50 = new QLabel(gridLayoutWidget_4);
        label_50->setObjectName(QStringLiteral("label_50"));
        QFont font4;
        font4.setBold(true);
        font4.setWeight(75);
        label_50->setFont(font4);

        gridLayout_22->addWidget(label_50, 1, 0, 1, 1);

        editFeedbackEmail = new QLineEdit(gridLayoutWidget_4);
        editFeedbackEmail->setObjectName(QStringLiteral("editFeedbackEmail"));

        gridLayout_22->addWidget(editFeedbackEmail, 6, 1, 1, 1);

        editFeedbackDescription = new QPlainTextEdit(gridLayoutWidget_4);
        editFeedbackDescription->setObjectName(QStringLiteral("editFeedbackDescription"));

        gridLayout_22->addWidget(editFeedbackDescription, 5, 1, 1, 1);

        label_62 = new QLabel(gridLayoutWidget_4);
        label_62->setObjectName(QStringLiteral("label_62"));

        gridLayout_22->addWidget(label_62, 3, 0, 1, 1);

        label_65 = new QLabel(gridLayoutWidget_4);
        label_65->setObjectName(QStringLiteral("label_65"));
        QFont font5;
        font5.setBold(false);
        font5.setItalic(false);
        font5.setUnderline(false);
        font5.setWeight(50);
        label_65->setFont(font5);

        gridLayout_22->addWidget(label_65, 7, 0, 1, 1);

        label_67 = new QLabel(gridLayoutWidget_4);
        label_67->setObjectName(QStringLiteral("label_67"));

        gridLayout_22->addWidget(label_67, 7, 1, 1, 1);


        verticalLayout_8->addLayout(gridLayout_22);

        btnLogFeedback = new QPushButton(gridLayoutWidget_4);
        btnLogFeedback->setObjectName(QStringLiteral("btnLogFeedback"));

        verticalLayout_8->addWidget(btnLogFeedback);


        gridLayout_11->addLayout(verticalLayout_8, 1, 1, 1, 1);

        SettingsTab->addTab(Feedback, QString());

        verticalLayout_7->addWidget(SettingsTab);

        buttonBox = new QDialogButtonBox(SettingsDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Cancel|QDialogButtonBox::Ok|QDialogButtonBox::RestoreDefaults);

        verticalLayout_7->addWidget(buttonBox);

#ifndef QT_NO_SHORTCUT
        label_85->setBuddy(editSampleDescription);
        label_93->setBuddy(editBarcode);
        label_89->setBuddy(editInstitute);
        label_94->setBuddy(editProjectDirectoryName);
        label_87->setBuddy(projectDate);
        label_40->setBuddy(editProjectName);
        label_86->setBuddy(editName);
        label_41->setBuddy(editProjectID);
        label_88->setBuddy(editVersion);
        label_83->setBuddy(editDescription);
        label_84->setBuddy(editFilenamePrefix);
        label_68->setBuddy(sliderBarcodeThreshold);
        label_37->setBuddy(spOverviewLensFocalLength);
        label_36->setBuddy(cboActiveCamera);
        label_34->setBuddy(lineEditOverviewCameraSN);
        label_38->setBuddy(spMicroscopeLensFocalLength);
        label_35->setBuddy(lineEditMicroscopeCameraSN);
        label_46->setBuddy(cboCOMPORTS);
        label_52->setBuddy(spinXPositionAbsoluteXY);
        label_53->setBuddy(spinYPositionAbsoluteXY);
        label_13->setBuddy(spinXPositionAbsoluteXY);
        label_15->setBuddy(spinXPositionRelativeXY);
        label_54->setBuddy(editSendCommandXY);
        label_56->setBuddy(spinVelocityXY);
        label_57->setBuddy(cboBaudXY);
        label_58->setBuddy(btnCalibrateXY);
        label_59->setBuddy(btnConnectXY);
        label_101->setBuddy(btnConnectXY);
        label_111->setBuddy(spinXPositionRelativeXY);
        label_110->setBuddy(spinXPositionAbsoluteXY);
        label_108->setBuddy(spinXPositionAbsoluteXY);
        label_112->setBuddy(editSendCommandXY);
        label_4->setBuddy(AlgoComboBox);
        label->setBuddy(numClusters);
        label_5->setBuddy(scoreRegionArea);
        label_2->setBuddy(numClusters);
        label_20->setBuddy(ScoreThreshold);
        label_3->setBuddy(distanceThreshold);
        label_9->setBuddy(cboSamplingType);
        label_43->setBuddy(spinSamplingDistance);
        label_42->setBuddy(spinExclusionDistance);
        label_31->setBuddy(sliderGridOffsetY);
        label_33->setBuddy(sliderGridSpacingY);
        label_32->setBuddy(sliderGridSpacingX);
        label_30->setBuddy(sliderGridOffsetX);
        label_39->setBuddy(chkFixedAspect);
        label_26->setBuddy(chkCV_CALIB_CB_ADAPTIVE_THRESH);
        label_21->setBuddy(spinItemsInRow);
        label_23->setBuddy(spinItemsInColumn);
        label_24->setBuddy(spinSizeSquare);
        label_25->setBuddy(cboCalibrateAlgorithm);
        label_27->setBuddy(chkCALIB_CB_CLUSTERING);
        labelThresholdMin->setBuddy(ThresholdMinSlider);
        labelThresholdMax->setBuddy(ThresholdMaxSlider);
        label_28->setBuddy(cboThresholdType);
        label_12->setBuddy(NoClustersSlider);
        label_18->setBuddy(huMomentSimilaritySlider);
        label_29->setBuddy(spinAspectTolerance);
        label_14->setBuddy(sizeToleranceSmallerSpinBox);
        label_16->setBuddy(sizeToleranceLargerSpinBox);
        label_19->setBuddy(huMomentSimilaritySlider);
        label_60->setBuddy(editFeedbackDescription);
        label_48->setBuddy(editFeedbackName);
        label_61->setBuddy(editFeedbackEmail);
        label_50->setBuddy(sliderFeedbackSatisfaction);
        label_62->setBuddy(editFeedbackInstitute);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(editName, editInstitute);
        QWidget::setTabOrder(editInstitute, editProjectName);
        QWidget::setTabOrder(editProjectName, editProjectDirectoryName);
        QWidget::setTabOrder(editProjectDirectoryName, btnProjectDirectory);
        QWidget::setTabOrder(btnProjectDirectory, editProjectID);
        QWidget::setTabOrder(editProjectID, editVersion);
        QWidget::setTabOrder(editVersion, editDescription);
        QWidget::setTabOrder(editDescription, editFilenamePrefix);
        QWidget::setTabOrder(editFilenamePrefix, editSampleDescription);
        QWidget::setTabOrder(editSampleDescription, editBarcode);
        QWidget::setTabOrder(editBarcode, projectDate);
        QWidget::setTabOrder(projectDate, spMicroscopeLensFocalLength);
        QWidget::setTabOrder(spMicroscopeLensFocalLength, lineEditOverviewCameraSN);
        QWidget::setTabOrder(lineEditOverviewCameraSN, lineEditMicroscopeCameraSN);
        QWidget::setTabOrder(lineEditMicroscopeCameraSN, sliderBarcodeThreshold);
        QWidget::setTabOrder(sliderBarcodeThreshold, chkAutoBarcodeThreshold);
        QWidget::setTabOrder(chkAutoBarcodeThreshold, cboBaudXY);
        QWidget::setTabOrder(cboBaudXY, btnConnectXY);
        QWidget::setTabOrder(btnConnectXY, spinVelocityXY);
        QWidget::setTabOrder(spinVelocityXY, btnSetVelocityXY);
        QWidget::setTabOrder(btnSetVelocityXY, btnDisconnectXY);
        QWidget::setTabOrder(btnDisconnectXY, btnCalibrateXY);
        QWidget::setTabOrder(btnCalibrateXY, btnMeasureRangeXY);
        QWidget::setTabOrder(btnMeasureRangeXY, spinXPositionAbsoluteXY);
        QWidget::setTabOrder(spinXPositionAbsoluteXY, spinXPositionRelativeXY);
        QWidget::setTabOrder(spinXPositionRelativeXY, spinYPositionAbsoluteXY);
        QWidget::setTabOrder(spinYPositionAbsoluteXY, spinYPositionRelativeXY);
        QWidget::setTabOrder(spinYPositionRelativeXY, btnMoveAbsoluteXY);
        QWidget::setTabOrder(btnMoveAbsoluteXY, btnMoveRelativeXY);
        QWidget::setTabOrder(btnMoveRelativeXY, cboCOMPORTS);
        QWidget::setTabOrder(cboCOMPORTS, cboSelectFiducial);
        QWidget::setTabOrder(cboSelectFiducial, btnDeleteFiducial);
        QWidget::setTabOrder(btnDeleteFiducial, AlgoComboBox);
        QWidget::setTabOrder(AlgoComboBox, numClusters);
        QWidget::setTabOrder(numClusters, distanceThreshold);
        QWidget::setTabOrder(distanceThreshold, ScoreThreshold);
        QWidget::setTabOrder(ScoreThreshold, scoreRegionArea);
        QWidget::setTabOrder(scoreRegionArea, chkTargetImageAsMask);
        QWidget::setTabOrder(chkTargetImageAsMask, cboSamplingType);
        QWidget::setTabOrder(cboSamplingType, spinSamplingDistance);
        QWidget::setTabOrder(spinSamplingDistance, spinExclusionDistance);
        QWidget::setTabOrder(spinExclusionDistance, cboAnnotationColour);
        QWidget::setTabOrder(cboAnnotationColour, btnSelectColour);
        QWidget::setTabOrder(btnSelectColour, sliderGridOffsetX);
        QWidget::setTabOrder(sliderGridOffsetX, spinGridOffsetX);
        QWidget::setTabOrder(spinGridOffsetX, sliderGridOffsetY);
        QWidget::setTabOrder(sliderGridOffsetY, spinGridOffsetY);
        QWidget::setTabOrder(spinGridOffsetY, sliderGridSpacingX);
        QWidget::setTabOrder(sliderGridSpacingX, spinGridSpacingX);
        QWidget::setTabOrder(spinGridSpacingX, sliderGridSpacingY);
        QWidget::setTabOrder(sliderGridSpacingY, spinGridSpacingY);
        QWidget::setTabOrder(spinGridSpacingY, chkDisplayGrid);
        QWidget::setTabOrder(chkDisplayGrid, btnCenterGrid);
        QWidget::setTabOrder(btnCenterGrid, cboCalibrateAlgorithm);
        QWidget::setTabOrder(cboCalibrateAlgorithm, spinItemsInRow);
        QWidget::setTabOrder(spinItemsInRow, spinItemsInColumn);
        QWidget::setTabOrder(spinItemsInColumn, spinSizeSquare);
        QWidget::setTabOrder(spinSizeSquare, chkFixedAspect);
        QWidget::setTabOrder(chkFixedAspect, chkZeroDistortion);
        QWidget::setTabOrder(chkZeroDistortion, chkFixPrincipalPointCenter);
        QWidget::setTabOrder(chkFixPrincipalPointCenter, chkIntrinsicGuess);
        QWidget::setTabOrder(chkIntrinsicGuess, chkFixFocalLength);
        QWidget::setTabOrder(chkFixFocalLength, chkCV_CALIB_CB_ADAPTIVE_THRESH);
        QWidget::setTabOrder(chkCV_CALIB_CB_ADAPTIVE_THRESH, chkCV_CALIB_CB_NORMALIZE_IMAGE);
        QWidget::setTabOrder(chkCV_CALIB_CB_NORMALIZE_IMAGE, chkCV_CALIB_CB_FILTER_QUADS);
        QWidget::setTabOrder(chkCV_CALIB_CB_FILTER_QUADS, chkCALIB_CB_FAST_CHECK);
        QWidget::setTabOrder(chkCALIB_CB_FAST_CHECK, chkCALIB_CB_CLUSTERING);
        QWidget::setTabOrder(chkCALIB_CB_CLUSTERING, ThresholdMinSlider);
        QWidget::setTabOrder(ThresholdMinSlider, ThresholdMaxSlider);
        QWidget::setTabOrder(ThresholdMaxSlider, cboThresholdType);
        QWidget::setTabOrder(cboThresholdType, NoClustersSlider);
        QWidget::setTabOrder(NoClustersSlider, chkAutoThreshold);
        QWidget::setTabOrder(chkAutoThreshold, sizeToleranceSmallerSpinBox);
        QWidget::setTabOrder(sizeToleranceSmallerSpinBox, sizeToleranceLargerSpinBox);
        QWidget::setTabOrder(sizeToleranceLargerSpinBox, spinAspectTolerance);
        QWidget::setTabOrder(spinAspectTolerance, huMomentSimilaritySlider);
        QWidget::setTabOrder(huMomentSimilaritySlider, sliderFeedbackSatisfaction);
        QWidget::setTabOrder(sliderFeedbackSatisfaction, editFeedbackName);
        QWidget::setTabOrder(editFeedbackName, editFeedbackInstitute);
        QWidget::setTabOrder(editFeedbackInstitute, editFeedbackDescription);
        QWidget::setTabOrder(editFeedbackDescription, editFeedbackEmail);
        QWidget::setTabOrder(editFeedbackEmail, btnLogFeedback);

        retranslateUi(SettingsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SettingsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SettingsDialog, SLOT(reject()));
        QObject::connect(NoClustersSlider, SIGNAL(valueChanged(int)), NoClustersLbl, SLOT(setNum(int)));
        QObject::connect(huMomentSimilaritySlider, SIGNAL(valueChanged(int)), label_19, SLOT(setNum(int)));
        QObject::connect(ThresholdMinSlider, SIGNAL(valueChanged(int)), label_90, SLOT(setNum(int)));
        QObject::connect(numClusters, SIGNAL(valueChanged(int)), labelCluster, SLOT(setNum(int)));
        QObject::connect(ThresholdMaxSlider, SIGNAL(valueChanged(int)), label_91, SLOT(setNum(int)));
        QObject::connect(distanceThreshold, SIGNAL(valueChanged(int)), label_distance, SLOT(setNum(int)));
        QObject::connect(ScoreThreshold, SIGNAL(valueChanged(int)), ScoreThresholdLbl, SLOT(setNum(int)));
        QObject::connect(sliderBarcodeThreshold, SIGNAL(valueChanged(int)), label_69, SLOT(setNum(int)));
        QObject::connect(chkAutoBarcodeThreshold, SIGNAL(toggled(bool)), sliderBarcodeThreshold, SLOT(setDisabled(bool)));
        QObject::connect(spnTopLeft_Overview_Stage_X, SIGNAL(valueChanged(QString)), label_215, SLOT(setText(QString)));
        QObject::connect(spnTopLeft_Overview_Stage_Y, SIGNAL(valueChanged(QString)), label_216, SLOT(setText(QString)));
        QObject::connect(spnTopLeft_Overview_Stage_X, SIGNAL(valueChanged(QString)), label_217, SLOT(setText(QString)));
        QObject::connect(spnTopLeft_Overview_Stage_Y, SIGNAL(valueChanged(QString)), label_218, SLOT(setText(QString)));
        QObject::connect(spnTopLeft_Overview_Stage_Y, SIGNAL(valueChanged(QString)), label_220, SLOT(setText(QString)));
        QObject::connect(spnTopLeft_Overview_Stage_X, SIGNAL(valueChanged(QString)), label_217, SLOT(setText(QString)));
        QObject::connect(spnTopLeft_Overview_Stage_X, SIGNAL(valueChanged(QString)), label_219, SLOT(setText(QString)));

        SettingsTab->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QApplication::translate("SettingsDialog", "Dialog", Q_NULLPTR));
        label_105->setText(QApplication::translate("SettingsDialog", "Backup project settings", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        btnSaveBackup->setToolTip(QApplication::translate("SettingsDialog", "Save all project settings to a backup file", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        btnSaveBackup->setText(QApplication::translate("SettingsDialog", "Save to BACKUP", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        btnRestoreBackup->setToolTip(QApplication::translate("SettingsDialog", "Restore all project settings from a backup file", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        btnRestoreBackup->setText(QApplication::translate("SettingsDialog", "Restore from  BACKUP", Q_NULLPTR));
        label_85->setText(QApplication::translate("SettingsDialog", "Sample Type", Q_NULLPTR));
        label_93->setText(QApplication::translate("SettingsDialog", "BarCode", Q_NULLPTR));
        label_89->setText(QApplication::translate("SettingsDialog", "Name of Institute", Q_NULLPTR));
        label_94->setText(QApplication::translate("SettingsDialog", "Project Directory", Q_NULLPTR));
        label_87->setText(QApplication::translate("SettingsDialog", "Date", Q_NULLPTR));
        label_40->setText(QApplication::translate("SettingsDialog", "Project Name", Q_NULLPTR));
        label_86->setText(QApplication::translate("SettingsDialog", "Researcher Name(s)", Q_NULLPTR));
        label_41->setText(QApplication::translate("SettingsDialog", "Project Reference (ID)", Q_NULLPTR));
        label_88->setText(QApplication::translate("SettingsDialog", "Version name", Q_NULLPTR));
        label_83->setText(QApplication::translate("SettingsDialog", "Project Description", Q_NULLPTR));
        label_84->setText(QApplication::translate("SettingsDialog", "Saved Filename Prefix", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        btnProjectDirectory->setToolTip(QApplication::translate("SettingsDialog", "Choose directory path", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        btnProjectDirectory->setText(QApplication::translate("SettingsDialog", "Choose Directory Path", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        editProjectDirectoryName->setToolTip(QApplication::translate("SettingsDialog", "name of directory to create", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        editName->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>Names of the experiments involved in the project</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        editInstitute->setToolTip(QApplication::translate("SettingsDialog", "Name of your institute", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        editProjectName->setToolTip(QApplication::translate("SettingsDialog", "Give your experiment a name", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        editProjectID->setToolTip(QApplication::translate("SettingsDialog", "You can also add a reference ID", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        editVersion->setToolTip(QApplication::translate("SettingsDialog", "You can give this experiment a version number", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        editDescription->setToolTip(QApplication::translate("SettingsDialog", "Use this field to describe your experiment", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        editFilenamePrefix->setToolTip(QApplication::translate("SettingsDialog", "The name will be used when saving files", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        editSampleDescription->setToolTip(QApplication::translate("SettingsDialog", "Explain more about your sample here", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        editBarcode->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>If unable to scan the barcode of the sample frame the barcode can be entered here. This field also tells you what the scanned barcode is.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        projectDate->setToolTip(QApplication::translate("SettingsDialog", "This should be the date of the experiment", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        SettingsTab->setTabText(SettingsTab->indexOf(ProjectSettingsTab), QApplication::translate("SettingsDialog", "Project Settings", Q_NULLPTR));
        spnImageWidthPixels->setSuffix(QApplication::translate("SettingsDialog", " pixels", Q_NULLPTR));
        lineEditOverviewCameraSN->setInputMask(QApplication::translate("SettingsDialog", "00000000", Q_NULLPTR));
        lineEditOverviewCameraSN->setText(QApplication::translate("SettingsDialog", "21799625", Q_NULLPTR));
        lineEditOverviewCameraSN->setPlaceholderText(QApplication::translate("SettingsDialog", "21799625", Q_NULLPTR));
        spMicroscopeLensFocalLength->setSuffix(QApplication::translate("SettingsDialog", "mm", Q_NULLPTR));
        spMicroscopeLensFocalLength->setPrefix(QString());
        lineEditMicroscopeCameraSN->setInputMask(QApplication::translate("SettingsDialog", "00000000", Q_NULLPTR));
        lineEditMicroscopeCameraSN->setText(QApplication::translate("SettingsDialog", "21799596", Q_NULLPTR));
        label_68->setText(QApplication::translate("SettingsDialog", "Bar Code Threshold", Q_NULLPTR));
        label_37->setText(QApplication::translate("SettingsDialog", "focal length of overview lens (mm)", Q_NULLPTR));
        label_36->setText(QApplication::translate("SettingsDialog", "Active Camera", Q_NULLPTR));
        label_34->setText(QApplication::translate("SettingsDialog", "Overview Camera IP address", Q_NULLPTR));
        label_38->setText(QApplication::translate("SettingsDialog", "focal length of microscope lens (mm)", Q_NULLPTR));
        label_35->setText(QApplication::translate("SettingsDialog", "Microscope Camera IP address", Q_NULLPTR));
        label_69->setText(QApplication::translate("SettingsDialog", "0", Q_NULLPTR));
        chkAutoBarcodeThreshold->setText(QApplication::translate("SettingsDialog", "Auto", Q_NULLPTR));
        label_74->setText(QApplication::translate("SettingsDialog", "Barcode Image Rect Position", Q_NULLPTR));
        lbl_barCode_H->setText(QApplication::translate("SettingsDialog", "0", "1"));
        lbl_barCode_X->setText(QApplication::translate("SettingsDialog", "0", "1"));
        lbl_barCode_Y->setText(QApplication::translate("SettingsDialog", "0", "1"));
        lbl_barCode_W->setText(QApplication::translate("SettingsDialog", "0", "1"));
        label_75->setText(QApplication::translate("SettingsDialog", "Y", "1"));
        label_76->setText(QApplication::translate("SettingsDialog", "X", "1"));
        label_77->setText(QApplication::translate("SettingsDialog", "width", "1"));
        label_78->setText(QApplication::translate("SettingsDialog", "height", "1"));
        lblImageHeightMicrons->setText(QString());
        label_102->setText(QApplication::translate("SettingsDialog", "Image Width", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_7->setToolTip(QApplication::translate("SettingsDialog", "This is the actual experimental value of pixel size and is best measured using a graticule and dividing the unit length by the image distance in pixels", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_7->setText(QApplication::translate("SettingsDialog", "Size of image pixel ", Q_NULLPTR));
        label_99->setText(QApplication::translate("SettingsDialog", "Microscope Image height", Q_NULLPTR));
        spOverviewLensFocalLength->setSuffix(QApplication::translate("SettingsDialog", "mm", Q_NULLPTR));
        lblImageWidthMicrons->setText(QString());
        cboActiveCamera->clear();
        cboActiveCamera->insertItems(0, QStringList()
         << QApplication::translate("SettingsDialog", "none", Q_NULLPTR)
         << QApplication::translate("SettingsDialog", "overview", Q_NULLPTR)
         << QApplication::translate("SettingsDialog", "microscope", Q_NULLPTR)
        );
        label_98->setText(QApplication::translate("SettingsDialog", "Microscope Image width", Q_NULLPTR));
        label_103->setText(QApplication::translate("SettingsDialog", "Image Height", Q_NULLPTR));
        spnImageHeightPixels->setSuffix(QApplication::translate("SettingsDialog", " pixels", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        editPixelSizeMicrons->setToolTip(QApplication::translate("SettingsDialog", "This is the actual experimental value of pixel size and is best measured using a graticule and dividing the unit length by the image distance in pixels", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        editPixelSizeMicrons->setText(QApplication::translate("SettingsDialog", "6.1274509803921568627450980392157", Q_NULLPTR));
        SettingsTab->setTabText(SettingsTab->indexOf(CameraSettingsTab), QApplication::translate("SettingsDialog", "Camera Settings", Q_NULLPTR));
        lblPORTZ->setText(QApplication::translate("SettingsDialog", "?", Q_NULLPTR));
        label_44->setText(QApplication::translate("SettingsDialog", "Newport Z Stage", Q_NULLPTR));
        lblPORTXY->setText(QApplication::translate("SettingsDialog", "?", Q_NULLPTR));
        lblPorts->setText(QApplication::translate("SettingsDialog", "Marzhauser XY Stage", Q_NULLPTR));
        label_46->setText(QApplication::translate("SettingsDialog", "DETECTED COM PORTS", Q_NULLPTR));
        label_49->setText(QApplication::translate("SettingsDialog", "Marzhauser Stage XY Axis  Control", Q_NULLPTR));
        label_51->setText(QApplication::translate("SettingsDialog", "Axis Positions", Q_NULLPTR));
        label_81->setText(QApplication::translate("SettingsDialog", "Y position (\316\274m)", Q_NULLPTR));
        label_80->setText(QApplication::translate("SettingsDialog", "X position (\316\274m)", Q_NULLPTR));
        lbl_positionXY_X->setText(QApplication::translate("SettingsDialog", "?", Q_NULLPTR));
        lbl_positionXY_Y->setText(QApplication::translate("SettingsDialog", "?", Q_NULLPTR));
        label_11->setText(QApplication::translate("SettingsDialog", "Position", Q_NULLPTR));
        label_52->setText(QApplication::translate("SettingsDialog", "Position X", Q_NULLPTR));
        label_53->setText(QApplication::translate("SettingsDialog", "Position Y", Q_NULLPTR));
        label_13->setText(QApplication::translate("SettingsDialog", "Absolute", Q_NULLPTR));
        label_15->setText(QApplication::translate("SettingsDialog", "Relative", Q_NULLPTR));
        btnMoveAbsoluteXY->setText(QApplication::translate("SettingsDialog", "Move Absolute", Q_NULLPTR));
        btnMoveRelativeXY->setText(QApplication::translate("SettingsDialog", "Move Relative", Q_NULLPTR));
        btnMoveToFiducial->setText(QApplication::translate("SettingsDialog", "Move Stage To Selected Fiducial Position", Q_NULLPTR));
        label_54->setText(QApplication::translate("SettingsDialog", "Send Text Command to Stage", Q_NULLPTR));
        btnSendCommandXY->setText(QApplication::translate("SettingsDialog", "Send Command", Q_NULLPTR));
        label_55->setText(QApplication::translate("SettingsDialog", "Stage Control Parameters", Q_NULLPTR));
        cboBaudXY->clear();
        cboBaudXY->insertItems(0, QStringList()
         << QApplication::translate("SettingsDialog", "1200", Q_NULLPTR)
         << QApplication::translate("SettingsDialog", "2400", Q_NULLPTR)
         << QApplication::translate("SettingsDialog", "4800", Q_NULLPTR)
         << QApplication::translate("SettingsDialog", "9600", Q_NULLPTR)
         << QApplication::translate("SettingsDialog", "19200", Q_NULLPTR)
         << QApplication::translate("SettingsDialog", "38400", Q_NULLPTR)
         << QApplication::translate("SettingsDialog", "57600", Q_NULLPTR)
         << QApplication::translate("SettingsDialog", " 115200", Q_NULLPTR)
        );
        label_56->setText(QApplication::translate("SettingsDialog", "Axis Velocity", Q_NULLPTR));
        btnSetVelocityXY->setText(QApplication::translate("SettingsDialog", "Set Velocity", Q_NULLPTR));
        label_57->setText(QApplication::translate("SettingsDialog", "Baud Rate", Q_NULLPTR));
        label_58->setText(QApplication::translate("SettingsDialog", "Calibrate Stage", Q_NULLPTR));
        btnCalibrateXY->setText(QApplication::translate("SettingsDialog", "Calibrate", Q_NULLPTR));
        btnMeasureRangeXY->setText(QApplication::translate("SettingsDialog", "Measure Range", Q_NULLPTR));
        label_17->setText(QApplication::translate("SettingsDialog", "Abort Movement", Q_NULLPTR));
        btnAbortXY->setText(QApplication::translate("SettingsDialog", "ABORT!", Q_NULLPTR));
        label_59->setText(QApplication::translate("SettingsDialog", "Connect Stage", Q_NULLPTR));
        btnConnectXY->setText(QApplication::translate("SettingsDialog", "Connect", Q_NULLPTR));
        btnDisconnectXY->setText(QApplication::translate("SettingsDialog", "Disconnect", Q_NULLPTR));
        chkJoystickOn->setText(QApplication::translate("SettingsDialog", "XY Stage Joystick on", Q_NULLPTR));
        chkKeypadOn->setText(QApplication::translate("SettingsDialog", "Z Axis stage Keypad on", Q_NULLPTR));
        label_100->setText(QApplication::translate("SettingsDialog", "Newport Stage Z Axis  Control", Q_NULLPTR));
        label_101->setText(QApplication::translate("SettingsDialog", "Connect Stage", Q_NULLPTR));
        btnConnectZ->setText(QApplication::translate("SettingsDialog", "Connect", Q_NULLPTR));
        btnDisconnectZ->setText(QApplication::translate("SettingsDialog", "Disconnect", Q_NULLPTR));
        label_104->setText(QApplication::translate("SettingsDialog", "Axis Positions", Q_NULLPTR));
        lbl_positionZ->setText(QApplication::translate("SettingsDialog", "?", Q_NULLPTR));
        label_106->setText(QApplication::translate("SettingsDialog", "Z position (\316\274m)", Q_NULLPTR));
        label_111->setText(QApplication::translate("SettingsDialog", "Relative", Q_NULLPTR));
        label_110->setText(QApplication::translate("SettingsDialog", "Absolute", Q_NULLPTR));
        label_45->setText(QApplication::translate("SettingsDialog", "Position", Q_NULLPTR));
        label_108->setText(QApplication::translate("SettingsDialog", "Position Z", Q_NULLPTR));
        btnMoveAbsoluteZ->setText(QApplication::translate("SettingsDialog", "Move Absolute", Q_NULLPTR));
        btnMoveRelativeZ->setText(QApplication::translate("SettingsDialog", "Move Relative", Q_NULLPTR));
        btnUpZ->setText(QApplication::translate("SettingsDialog", "UP", Q_NULLPTR));
        btnDownZ->setText(QApplication::translate("SettingsDialog", "DOWN", Q_NULLPTR));
        label_112->setText(QApplication::translate("SettingsDialog", "Send Text Command to Stage", Q_NULLPTR));
        btnSendCommandZ->setText(QApplication::translate("SettingsDialog", "Send Command", Q_NULLPTR));
        SettingsTab->setTabText(SettingsTab->indexOf(StageSettingsTab), QApplication::translate("SettingsDialog", "Translation Stage Control", Q_NULLPTR));
        label_107->setText(QApplication::translate("SettingsDialog", "Algorithm used for focusing", Q_NULLPTR));
        label_114->setText(QApplication::translate("SettingsDialog", "Coarse Focus Step", Q_NULLPTR));
        label_109->setText(QApplication::translate("SettingsDialog", "Maximum Focus position", Q_NULLPTR));
        label_113->setText(QApplication::translate("SettingsDialog", "Minimum Focus Position", Q_NULLPTR));
        label_115->setText(QApplication::translate("SettingsDialog", "Fine Focus Step", Q_NULLPTR));
        label_267->setText(QApplication::translate("SettingsDialog", "Fine forcus range is coarse focus step either side of the best coarse focus position", Q_NULLPTR));
        SettingsTab->setTabText(SettingsTab->indexOf(tab), QApplication::translate("SettingsDialog", "Focusing", Q_NULLPTR));
        label_8->setText(QApplication::translate("SettingsDialog", "Fuducial Marks", Q_NULLPTR));
        lblFiducialCheck->setText(QString());
        label_209->setText(QApplication::translate("SettingsDialog", "Y (px)", Q_NULLPTR));
        lbl_bottomright_overview->setText(QApplication::translate("SettingsDialog", "Bottom Right", Q_NULLPTR));
        label_207->setText(QApplication::translate("SettingsDialog", "X (px)", Q_NULLPTR));
        label_216->setText(QString());
        label_218->setText(QString());
        label_208->setText(QApplication::translate("SettingsDialog", "X (px)", Q_NULLPTR));
        label_215->setText(QString());
        lbl_bottomleft_overview->setText(QApplication::translate("SettingsDialog", "Bottom Left", Q_NULLPTR));
        label_220->setText(QString());
        label_210->setText(QApplication::translate("SettingsDialog", "Y (px)", Q_NULLPTR));
        lbl_bottomright_microscope->setText(QApplication::translate("SettingsDialog", "Bottom Right", Q_NULLPTR));
        label_212->setText(QApplication::translate("SettingsDialog", "Y (\316\274m)", Q_NULLPTR));
        label_217->setText(QString());
        label_219->setText(QString());
        label_214->setText(QApplication::translate("SettingsDialog", "Y (\316\274m)", Q_NULLPTR));
        lbl_bottomleft_microscope->setText(QApplication::translate("SettingsDialog", "Bottom Left", Q_NULLPTR));
        label_221->setText(QApplication::translate("SettingsDialog", "Z (\316\274m)", Q_NULLPTR));
        label_213->setText(QApplication::translate("SettingsDialog", "X (\316\274m)", Q_NULLPTR));
        label_211->setText(QApplication::translate("SettingsDialog", "X (\316\274m)", Q_NULLPTR));
        label_82->setText(QApplication::translate("SettingsDialog", "Overview Camera", Q_NULLPTR));
        lbl_topleft_overview->setText(QApplication::translate("SettingsDialog", "Top Left", Q_NULLPTR));
        lbl_topright_overview->setText(QApplication::translate("SettingsDialog", "Top Right", Q_NULLPTR));
        label_95->setText(QApplication::translate("SettingsDialog", "Microscope Camera", Q_NULLPTR));
        lbl_topleft_microscope->setText(QApplication::translate("SettingsDialog", "Top Left", Q_NULLPTR));
        lbl_topright_microscope->setText(QApplication::translate("SettingsDialog", "Top Right", Q_NULLPTR));
        label_224->setText(QApplication::translate("SettingsDialog", "Focus", Q_NULLPTR));
        label_79->setText(QApplication::translate("SettingsDialog", "Click fiducial button then on image to record fiducial position", Q_NULLPTR));
        label_72->setText(QString());
        label_222->setText(QApplication::translate("SettingsDialog", "Image Position", Q_NULLPTR));
        label_223->setText(QApplication::translate("SettingsDialog", "Stage Position", Q_NULLPTR));
        label_96->setText(QApplication::translate("SettingsDialog", "Create Transformation Matrices", Q_NULLPTR));
        label_97->setText(QApplication::translate("SettingsDialog", "This will map overview image XY position with microscope coordinates and align fiducial marks XYZ positions with stage coordinates", Q_NULLPTR));
        btnCalcTransformationMatrix->setText(QApplication::translate("SettingsDialog", "Create", Q_NULLPTR));
        label_71->setText(QApplication::translate("SettingsDialog", "Selected fiducial marker", Q_NULLPTR));
        cboSelectFiducial->clear();
        cboSelectFiducial->insertItems(0, QStringList()
         << QApplication::translate("SettingsDialog", "top left", Q_NULLPTR)
         << QApplication::translate("SettingsDialog", "top right", Q_NULLPTR)
         << QApplication::translate("SettingsDialog", "bottom left", Q_NULLPTR)
         << QApplication::translate("SettingsDialog", "bottom right", Q_NULLPTR)
        );
        btnDeleteFiducial->setText(QApplication::translate("SettingsDialog", "Delete selected Fiducial", Q_NULLPTR));
        chkLockFiducial->setText(QApplication::translate("SettingsDialog", "lock Settings", Q_NULLPTR));
        SettingsTab->setTabText(SettingsTab->indexOf(FiducialMarksTab), QApplication::translate("SettingsDialog", "Fiducial Marks", Q_NULLPTR));
        label_4->setText(QApplication::translate("SettingsDialog", "Algorithm Type", Q_NULLPTR));
        label->setText(QApplication::translate("SettingsDialog", "COOC (Colour Cooccurrance) Settings", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_5->setToolTip(QApplication::translate("SettingsDialog", "This value determines the area over which the score is summed (relative to the target object size). If the value is less than 1 then the summed area will be smaller than the example object, if it is greater than one then larger image regions than that of the example target will be summed. When the value is 1 then the summed score region willl be the same as the target.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_5->setText(QApplication::translate("SettingsDialog", "Score Region \n"
"Size Factor", Q_NULLPTR));
        label_2->setText(QApplication::translate("SettingsDialog", "No. Clusters", Q_NULLPTR));
        label_20->setText(QApplication::translate("SettingsDialog", "Score\n"
"Threshold", Q_NULLPTR));
        label_3->setText(QApplication::translate("SettingsDialog", "Distance", Q_NULLPTR));
        ScoreThresholdLbl->setText(QApplication::translate("SettingsDialog", "100", Q_NULLPTR));
        label_70->setText(QApplication::translate("SettingsDialog", "%", Q_NULLPTR));
        lblScoreSizeFactor->setText(QApplication::translate("SettingsDialog", "100", Q_NULLPTR));
        label_73->setText(QApplication::translate("SettingsDialog", "%", Q_NULLPTR));
        label_distance->setText(QApplication::translate("SettingsDialog", "5", Q_NULLPTR));
        label_22->setText(QApplication::translate("SettingsDialog", "%", Q_NULLPTR));
        labelCluster->setText(QApplication::translate("SettingsDialog", "10", Q_NULLPTR));
        chkTargetImageAsMask->setText(QApplication::translate("SettingsDialog", "Target image as mask", Q_NULLPTR));
        label_9->setText(QApplication::translate("SettingsDialog", "Type of region sampling", Q_NULLPTR));
        label_43->setText(QApplication::translate("SettingsDialog", "Spacing of sampling grid (px)", Q_NULLPTR));
        label_42->setText(QApplication::translate("SettingsDialog", "Distance From edge/center (px) ", Q_NULLPTR));
        SettingsTab->setTabText(SettingsTab->indexOf(TargetSettingsTab), QApplication::translate("SettingsDialog", "Target Settings", Q_NULLPTR));
        btnSelectColour->setText(QApplication::translate("SettingsDialog", "Choose Colour", Q_NULLPTR));
        cboAnnotationColour->clear();
        cboAnnotationColour->insertItems(0, QStringList()
         << QApplication::translate("SettingsDialog", "Annotation", Q_NULLPTR)
         << QApplication::translate("SettingsDialog", "Grid", Q_NULLPTR)
        );
        label_6->setText(QApplication::translate("SettingsDialog", "Drawing Element Colours", Q_NULLPTR));
        label_10->setText(QApplication::translate("SettingsDialog", "Grid Settings", Q_NULLPTR));
        label_31->setText(QApplication::translate("SettingsDialog", "Grid Offset Y", Q_NULLPTR));
        label_33->setText(QApplication::translate("SettingsDialog", "Grid Spacing Y", Q_NULLPTR));
        label_32->setText(QApplication::translate("SettingsDialog", "Grid Spacing X", Q_NULLPTR));
        label_30->setText(QApplication::translate("SettingsDialog", "Grid Offset X", Q_NULLPTR));
        chkDisplayGrid->setText(QApplication::translate("SettingsDialog", "Display Grid", Q_NULLPTR));
        btnCenterGrid->setText(QApplication::translate("SettingsDialog", "Center Grid", Q_NULLPTR));
        SettingsTab->setTabText(SettingsTab->indexOf(Drawing), QApplication::translate("SettingsDialog", "Drawing", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_39->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>This section allows you to modify tweek the camera calibration algorithm to simplify the optimisation by fixing, setting to zero or using preset values in the camera matrix.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_39->setText(QApplication::translate("SettingsDialog", "<html><head/><body><p><span style=\" text-decoration: underline;\">Calibration algorithm flags</span></p></body></html>", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        chkFixedAspect->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>Fix the focal length to be the same in the horizontal and vertical directions </p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        chkFixedAspect->setText(QApplication::translate("SettingsDialog", "Calibrate with fixed aspect ratio", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        chkZeroDistortion->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>If true tangential distortion coefficients (calibrating for camera chip alignment) are set to zero </p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        chkZeroDistortion->setText(QApplication::translate("SettingsDialog", "Assume zero tangential distortion", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        chkFixPrincipalPointCenter->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>If checked the principal point is set to center of image and not changed during calibration</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        chkFixPrincipalPointCenter->setText(QApplication::translate("SettingsDialog", "Fix principal point at center", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        chkIntrinsicGuess->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>If set the calibration uses preset values, for instance focal length</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        chkIntrinsicGuess->setText(QApplication::translate("SettingsDialog", "Calibrate using intrinsic guess", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        chkFixFocalLength->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>If set algorithm uses focal length (and pixel size) value set in camera settings tab</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        chkFixFocalLength->setText(QApplication::translate("SettingsDialog", "Fix lens focal length", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_26->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>These settings allow you to tweek the performance of the corner finding algorithm in the case that corners are not detected</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_26->setText(QApplication::translate("SettingsDialog", "<html><head/><body><p><span style=\" text-decoration: underline;\">Corner finding algorithm flags</span></p></body></html>", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        chkCV_CALIB_CB_ADAPTIVE_THRESH->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>Use adaptive thresholding to convert the image to black and white, rather than a fixed threshold level (computed from the average image brightness)</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        chkCV_CALIB_CB_ADAPTIVE_THRESH->setText(QApplication::translate("SettingsDialog", "CV_CALIB_CB_ADAPTIVE_THRESH", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        chkCV_CALIB_CB_NORMALIZE_IMAGE->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>Normalize the image gamma with equalizeHist() before applying fixed or adaptive thresholding</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        chkCV_CALIB_CB_NORMALIZE_IMAGE->setText(QApplication::translate("SettingsDialog", "CV_CALIB_CB_NORMALIZE_IMAGE", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        chkCV_CALIB_CB_FILTER_QUADS->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>Use additional criteria (like contour area, perimeter, square-like shape) to filter out false quads extracted at the contour retrieval stage</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        chkCV_CALIB_CB_FILTER_QUADS->setText(QApplication::translate("SettingsDialog", "CV_CALIB_CB_FILTER_QUADS", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        chkCALIB_CB_FAST_CHECK->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>Run a fast check on the image that looks for chessboard corners, and shortcut the call if none is found. This can drastically speed up the call in the degenerate condition when no chessboard is observed</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        chkCALIB_CB_FAST_CHECK->setText(QApplication::translate("SettingsDialog", "CALIB_CB_FAST_CHECK", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_21->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p><span style=\" font-family:'monospace'; font-size:13px; color:#000000;\">Number of inner corners per item for square horizontally (ie. number of squares in row -1), for circles it is the number of circles in row</span></p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_21->setText(QApplication::translate("SettingsDialog", "<html><head/><body><p>Number of repeat items in row</p></body></html>", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_23->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p><span style=\" font-family:'monospace'; font-size:13px; color:#000000;\">Number of inner corners per item for square vertically (ie. number of squares in column -1), for circles it is the number of circles in column</span></p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_23->setText(QApplication::translate("SettingsDialog", "<html><head/><body><p>Number of repeat items in column</p></body></html>", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_24->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p><span style=\" font-family:'monospace'; font-size:13px; color:#000000;\">The measured size of printed square/circle of pattern (mm)</span></p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_24->setText(QApplication::translate("SettingsDialog", "Size of Square/Circle (mm)", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_25->setToolTip(QApplication::translate("SettingsDialog", "Type of image : CHESSBOARD = chessboard pattern\n"
"	CIRCLES_GRID = filled circles spaced in grid pattern\n"
"                           ASYMMETRIC_CIRCLES_GRID = spaced asymmetric circles in grid ( body centered cubic in XY plane)", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_25->setText(QApplication::translate("SettingsDialog", "Type of input image", Q_NULLPTR));
        cboCalibrateAlgorithm->clear();
        cboCalibrateAlgorithm->insertItems(0, QStringList()
         << QApplication::translate("SettingsDialog", "CHESSBOARD", Q_NULLPTR)
         << QApplication::translate("SettingsDialog", "CIRCLES_GRID", Q_NULLPTR)
         << QApplication::translate("SettingsDialog", "ASYMMETRIC_CIRCLES_GRID", Q_NULLPTR)
        );
#ifndef QT_NO_TOOLTIP
        label_27->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>These settings allow you to tweek the circle finding algorithm performance. Generally asymmetric circle grids perfom best</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_27->setText(QApplication::translate("SettingsDialog", "<html><head/><body><p><span style=\" text-decoration: underline;\">Type of algorithm for finding circle centers</span></p></body></html>", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        chkCALIB_CB_CLUSTERING->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>Uses a special algorithm for circle grid detection. It is more robust to perspective distortions but much more sensitive to background clutter</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        chkCALIB_CB_CLUSTERING->setText(QApplication::translate("SettingsDialog", "CALIB_CB_CLUSTERING", Q_NULLPTR));
        SettingsTab->setTabText(SettingsTab->indexOf(CalibrationTab), QApplication::translate("SettingsDialog", "Camera Calibration", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        NoClustersSlider->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>The image will be posterized into the set number of gray levels. When No. levels = 2, this isthe same as performing a binary threshold.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        cboThresholdType->clear();
        cboThresholdType->insertItems(0, QStringList()
         << QApplication::translate("SettingsDialog", "Posterize (greyscale clusters)", Q_NULLPTR)
        );
#ifndef QT_NO_TOOLTIP
        ThresholdMinSlider->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>All values <span style=\" font-weight:600;\">above</span> this threshold are white in the image otherwise black</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        ThresholdMaxLbl->setText(QApplication::translate("SettingsDialog", "255", Q_NULLPTR));
        ThresholdMinLbl->setText(QApplication::translate("SettingsDialog", "0", Q_NULLPTR));
        histogram_image->setText(QString());
        label_92->setText(QApplication::translate("SettingsDialog", "Image Histogram", Q_NULLPTR));
        label_90->setText(QApplication::translate("SettingsDialog", " 0", Q_NULLPTR));
        label_91->setText(QApplication::translate("SettingsDialog", "255", Q_NULLPTR));
        NoClustersLbl->setText(QApplication::translate("SettingsDialog", "2", Q_NULLPTR));
        labelThresholdMin->setText(QApplication::translate("SettingsDialog", "Threshold Min", Q_NULLPTR));
        labelThresholdMax->setText(QApplication::translate("SettingsDialog", "Threshold Max", Q_NULLPTR));
        label_28->setText(QApplication::translate("SettingsDialog", "Threshold Type", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        ThresholdMaxSlider->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>All values <span style=\" font-weight:600;\">below</span> this threshold are white in the image otherwise black</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_12->setText(QApplication::translate("SettingsDialog", "Number of levels", Q_NULLPTR));
        chkAutoThreshold->setText(QApplication::translate("SettingsDialog", "Automatic Thresholding", Q_NULLPTR));
        SettingsTab->setTabText(SettingsTab->indexOf(ThresholdSettingsTab), QApplication::translate("SettingsDialog", "Threshold Settings", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_18->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>Hu moments are calculated for the binary shape, these are shape measures. The similarity setting determines how important similar shape of the detected targets are (100% =  shape must be the same, 0% = shape not important).</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_18->setText(QApplication::translate("SettingsDialog", "Hu Moment Similarity (% similar)", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        sizeToleranceLargerSpinBox->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>How much bigger can the detected targets be than the example target.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_29->setToolTip(QApplication::translate("SettingsDialog", "How rectangular the bounding box of the detected object can be", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_29->setText(QApplication::translate("SettingsDialog", "Aspect ratio of object tolerance", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_14->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>How much smaller can the detected targets be than the example target.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_14->setText(QApplication::translate("SettingsDialog", "Size tolerance (% smaller)", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        sizeToleranceSmallerSpinBox->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>How much smaller can the detected targets be than the example target.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_16->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>How much bigger can the detected targets be than the example target.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_16->setText(QApplication::translate("SettingsDialog", "Size tolerance (% larger)", Q_NULLPTR));
        label_19->setText(QApplication::translate("SettingsDialog", "0", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        huMomentSimilaritySlider->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>Hu moments are calculated for the binary shape, these are shape measures. The similarity setting determines how important similar shape of the detected targets are (100% = shape must be the same, 0% = shape not important).</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        SettingsTab->setTabText(SettingsTab->indexOf(ConnectedComponentsTab), QApplication::translate("SettingsDialog", "Connected Components", Q_NULLPTR));
        label_47->setText(QApplication::translate("SettingsDialog", "Any feedback you have would be helpful for further developmemt of Targeter", Q_NULLPTR));
        label_66->setText(QApplication::translate("SettingsDialog", "your feedback will be logged to a file on the XFEL network (or locally if outside XFEL^)", Q_NULLPTR));
        label_60->setText(QApplication::translate("SettingsDialog", "Feedback*", Q_NULLPTR));
        label_63->setText(QApplication::translate("SettingsDialog", "hate it!", Q_NULLPTR));
        label_64->setText(QApplication::translate("SettingsDialog", "love it!", Q_NULLPTR));
        label_48->setText(QApplication::translate("SettingsDialog", "name*", Q_NULLPTR));
        label_61->setText(QApplication::translate("SettingsDialog", "email address*", Q_NULLPTR));
        label_50->setText(QApplication::translate("SettingsDialog", "How statistied are you with the software?", Q_NULLPTR));
        label_62->setText(QApplication::translate("SettingsDialog", "institute*", Q_NULLPTR));
        label_65->setText(QApplication::translate("SettingsDialog", "* optional", Q_NULLPTR));
        label_67->setText(QApplication::translate("SettingsDialog", "^ we would appreciate if you emailed us this file when sufficiently large", Q_NULLPTR));
        btnLogFeedback->setText(QApplication::translate("SettingsDialog", "Log Feedback", Q_NULLPTR));
        SettingsTab->setTabText(SettingsTab->indexOf(Feedback), QApplication::translate("SettingsDialog", "Feedback", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        buttonBox->setToolTip(QApplication::translate("SettingsDialog", "Save the settings or restore default settings ", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
