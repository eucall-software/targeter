/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
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
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QTabWidget *SettingsTab;
    QWidget *CameraSettingsTab;
    QDoubleSpinBox *spPixelSize;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *lbl_fm_TL_X;
    QLabel *label_13;
    QLabel *lbl_fm_TL_Y;
    QPushButton *btn_fm_TL;
    QLabel *lbl_fm_TR_Y;
    QPushButton *btn_fm_TR;
    QLabel *lbl_fm_TR_X;
    QLabel *label_15;
    QLabel *lbl_fm_BL_Y;
    QPushButton *btn_fm_BL;
    QLabel *lbl_fm_BL_X;
    QLabel *label_17;
    QWidget *StageSettingsTab;
    QWidget *TargetSettingsTab;
    QLabel *label_4;
    QLabel *label_distance;
    QLabel *labelCluster;
    QComboBox *AlgoComboBox;
    QLabel *label;
    QLabel *ScoreThresholdLbl;
    QLabel *label_22;
    QSplitter *splitter;
    QSlider *numClusters;
    QSlider *distanceThreshold;
    QSlider *ScoreThreshold;
    QSplitter *splitter_2;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_20;
    QWidget *ThresholdSettingsTab;
    QSlider *ThresholdMinSlider;
    QLabel *ThresholdMinLbl;
    QLabel *label_6;
    QLabel *label_5;
    QSlider *ThresholdMaxSlider;
    QLabel *ThresholdMaxLbl;
    QCheckBox *chkAutoThreshold;
    QLabel *histogram_image;
    QFrame *lineThresholdMin;
    QFrame *lineThresholdMax;
    QSlider *NoClustersSlider;
    QLabel *label_12;
    QLabel *NoClustersLbl;
    QWidget *tab;
    QLabel *label_14;
    QLabel *label_16;
    QSpinBox *sizeToleranceSmallerSpinBox;
    QSpinBox *sizeToleranceLargerSpinBox;
    QLabel *label_18;
    QSlider *huMomentSimilaritySlider;
    QLabel *label_19;
    QDialogButtonBox *buttonBox;
    QPushButton *resetValues;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QStringLiteral("SettingsDialog"));
        SettingsDialog->resize(542, 419);
        SettingsTab = new QTabWidget(SettingsDialog);
        SettingsTab->setObjectName(QStringLiteral("SettingsTab"));
        SettingsTab->setGeometry(QRect(20, 20, 491, 321));
        CameraSettingsTab = new QWidget();
        CameraSettingsTab->setObjectName(QStringLiteral("CameraSettingsTab"));
        spPixelSize = new QDoubleSpinBox(CameraSettingsTab);
        spPixelSize->setObjectName(QStringLiteral("spPixelSize"));
        spPixelSize->setGeometry(QRect(150, 20, 62, 22));
        spPixelSize->setValue(1);
        label_7 = new QLabel(CameraSettingsTab);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(30, 20, 111, 16));
        label_8 = new QLabel(CameraSettingsTab);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(30, 60, 111, 16));
        QFont font;
        font.setUnderline(true);
        label_8->setFont(font);
        label_9 = new QLabel(CameraSettingsTab);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(30, 90, 47, 13));
        label_10 = new QLabel(CameraSettingsTab);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(30, 120, 47, 13));
        label_11 = new QLabel(CameraSettingsTab);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(30, 150, 81, 16));
        lbl_fm_TL_X = new QLabel(CameraSettingsTab);
        lbl_fm_TL_X->setObjectName(QStringLiteral("lbl_fm_TL_X"));
        lbl_fm_TL_X->setGeometry(QRect(105, 90, 41, 20));
        lbl_fm_TL_X->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_13 = new QLabel(CameraSettingsTab);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(150, 90, 21, 16));
        lbl_fm_TL_Y = new QLabel(CameraSettingsTab);
        lbl_fm_TL_Y->setObjectName(QStringLiteral("lbl_fm_TL_Y"));
        lbl_fm_TL_Y->setGeometry(QRect(160, 90, 31, 20));
        lbl_fm_TL_Y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        btn_fm_TL = new QPushButton(CameraSettingsTab);
        btn_fm_TL->setObjectName(QStringLiteral("btn_fm_TL"));
        btn_fm_TL->setGeometry(QRect(220, 90, 75, 23));
        lbl_fm_TR_Y = new QLabel(CameraSettingsTab);
        lbl_fm_TR_Y->setObjectName(QStringLiteral("lbl_fm_TR_Y"));
        lbl_fm_TR_Y->setGeometry(QRect(160, 120, 31, 20));
        lbl_fm_TR_Y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        btn_fm_TR = new QPushButton(CameraSettingsTab);
        btn_fm_TR->setObjectName(QStringLiteral("btn_fm_TR"));
        btn_fm_TR->setGeometry(QRect(220, 120, 75, 23));
        lbl_fm_TR_X = new QLabel(CameraSettingsTab);
        lbl_fm_TR_X->setObjectName(QStringLiteral("lbl_fm_TR_X"));
        lbl_fm_TR_X->setGeometry(QRect(105, 120, 41, 20));
        lbl_fm_TR_X->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_15 = new QLabel(CameraSettingsTab);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(150, 120, 21, 16));
        lbl_fm_BL_Y = new QLabel(CameraSettingsTab);
        lbl_fm_BL_Y->setObjectName(QStringLiteral("lbl_fm_BL_Y"));
        lbl_fm_BL_Y->setGeometry(QRect(160, 150, 31, 20));
        lbl_fm_BL_Y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        btn_fm_BL = new QPushButton(CameraSettingsTab);
        btn_fm_BL->setObjectName(QStringLiteral("btn_fm_BL"));
        btn_fm_BL->setGeometry(QRect(220, 150, 75, 23));
        lbl_fm_BL_X = new QLabel(CameraSettingsTab);
        lbl_fm_BL_X->setObjectName(QStringLiteral("lbl_fm_BL_X"));
        lbl_fm_BL_X->setGeometry(QRect(105, 150, 41, 20));
        lbl_fm_BL_X->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_17 = new QLabel(CameraSettingsTab);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(150, 150, 21, 16));
        SettingsTab->addTab(CameraSettingsTab, QString());
        StageSettingsTab = new QWidget();
        StageSettingsTab->setObjectName(QStringLiteral("StageSettingsTab"));
        SettingsTab->addTab(StageSettingsTab, QString());
        TargetSettingsTab = new QWidget();
        TargetSettingsTab->setObjectName(QStringLiteral("TargetSettingsTab"));
        label_4 = new QLabel(TargetSettingsTab);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(40, 30, 91, 16));
        label_distance = new QLabel(TargetSettingsTab);
        label_distance->setObjectName(QStringLiteral("label_distance"));
        label_distance->setGeometry(QRect(360, 158, 16, 16));
        labelCluster = new QLabel(TargetSettingsTab);
        labelCluster->setObjectName(QStringLiteral("labelCluster"));
        labelCluster->setGeometry(QRect(360, 130, 16, 16));
        AlgoComboBox = new QComboBox(TargetSettingsTab);
        AlgoComboBox->setObjectName(QStringLiteral("AlgoComboBox"));
        AlgoComboBox->setGeometry(QRect(40, 60, 331, 20));
        label = new QLabel(TargetSettingsTab);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 100, 221, 16));
        label->setStyleSheet(QLatin1String("font: 75 10pt \"MS Shell Dlg 2\";\n"
"text-decoration: underline;"));
        ScoreThresholdLbl = new QLabel(TargetSettingsTab);
        ScoreThresholdLbl->setObjectName(QStringLiteral("ScoreThresholdLbl"));
        ScoreThresholdLbl->setGeometry(QRect(360, 185, 18, 16));
        label_22 = new QLabel(TargetSettingsTab);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(380, 185, 16, 16));
        splitter = new QSplitter(TargetSettingsTab);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setGeometry(QRect(110, 130, 231, 81));
        splitter->setOrientation(Qt::Vertical);
        numClusters = new QSlider(splitter);
        numClusters->setObjectName(QStringLiteral("numClusters"));
        numClusters->setMaximum(20);
        numClusters->setValue(10);
        numClusters->setOrientation(Qt::Horizontal);
        splitter->addWidget(numClusters);
        distanceThreshold = new QSlider(splitter);
        distanceThreshold->setObjectName(QStringLiteral("distanceThreshold"));
        distanceThreshold->setMaximum(50);
        distanceThreshold->setValue(5);
        distanceThreshold->setOrientation(Qt::Horizontal);
        splitter->addWidget(distanceThreshold);
        ScoreThreshold = new QSlider(splitter);
        ScoreThreshold->setObjectName(QStringLiteral("ScoreThreshold"));
        ScoreThreshold->setMaximum(100);
        ScoreThreshold->setValue(70);
        ScoreThreshold->setOrientation(Qt::Horizontal);
        splitter->addWidget(ScoreThreshold);
        splitter_2 = new QSplitter(TargetSettingsTab);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setGeometry(QRect(40, 130, 59, 81));
        splitter_2->setOrientation(Qt::Vertical);
        label_2 = new QLabel(splitter_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        splitter_2->addWidget(label_2);
        label_3 = new QLabel(splitter_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        splitter_2->addWidget(label_3);
        label_20 = new QLabel(splitter_2);
        label_20->setObjectName(QStringLiteral("label_20"));
        splitter_2->addWidget(label_20);
        SettingsTab->addTab(TargetSettingsTab, QString());
        ThresholdSettingsTab = new QWidget();
        ThresholdSettingsTab->setObjectName(QStringLiteral("ThresholdSettingsTab"));
        ThresholdMinSlider = new QSlider(ThresholdSettingsTab);
        ThresholdMinSlider->setObjectName(QStringLiteral("ThresholdMinSlider"));
        ThresholdMinSlider->setEnabled(false);
        ThresholdMinSlider->setGeometry(QRect(40, 50, 160, 19));
        ThresholdMinSlider->setMaximum(254);
        ThresholdMinSlider->setOrientation(Qt::Horizontal);
        ThresholdMinLbl = new QLabel(ThresholdSettingsTab);
        ThresholdMinLbl->setObjectName(QStringLiteral("ThresholdMinLbl"));
        ThresholdMinLbl->setGeometry(QRect(230, 50, 47, 13));
        label_6 = new QLabel(ThresholdSettingsTab);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(40, 20, 201, 16));
        label_5 = new QLabel(ThresholdSettingsTab);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(40, 80, 121, 16));
        label_5->setStyleSheet(QStringLiteral(""));
        ThresholdMaxSlider = new QSlider(ThresholdSettingsTab);
        ThresholdMaxSlider->setObjectName(QStringLiteral("ThresholdMaxSlider"));
        ThresholdMaxSlider->setEnabled(false);
        ThresholdMaxSlider->setGeometry(QRect(40, 110, 160, 19));
        ThresholdMaxSlider->setMinimum(1);
        ThresholdMaxSlider->setMaximum(255);
        ThresholdMaxSlider->setValue(254);
        ThresholdMaxSlider->setOrientation(Qt::Horizontal);
        ThresholdMaxLbl = new QLabel(ThresholdSettingsTab);
        ThresholdMaxLbl->setObjectName(QStringLiteral("ThresholdMaxLbl"));
        ThresholdMaxLbl->setGeometry(QRect(230, 110, 47, 13));
        chkAutoThreshold = new QCheckBox(ThresholdSettingsTab);
        chkAutoThreshold->setObjectName(QStringLiteral("chkAutoThreshold"));
        chkAutoThreshold->setGeometry(QRect(40, 150, 151, 17));
        chkAutoThreshold->setChecked(true);
        histogram_image = new QLabel(ThresholdSettingsTab);
        histogram_image->setObjectName(QStringLiteral("histogram_image"));
        histogram_image->setGeometry(QRect(276, 50, 171, 181));
        histogram_image->setFrameShape(QFrame::StyledPanel);
        histogram_image->setScaledContents(true);
        lineThresholdMin = new QFrame(ThresholdSettingsTab);
        lineThresholdMin->setObjectName(QStringLiteral("lineThresholdMin"));
        lineThresholdMin->setGeometry(QRect(267, 50, 20, 181));
        lineThresholdMin->setStyleSheet(QStringLiteral("color:red"));
        lineThresholdMin->setFrameShadow(QFrame::Plain);
        lineThresholdMin->setLineWidth(3);
        lineThresholdMin->setFrameShape(QFrame::VLine);
        lineThresholdMax = new QFrame(ThresholdSettingsTab);
        lineThresholdMax->setObjectName(QStringLiteral("lineThresholdMax"));
        lineThresholdMax->setGeometry(QRect(437, 50, 20, 181));
        lineThresholdMax->setAutoFillBackground(false);
        lineThresholdMax->setStyleSheet(QStringLiteral("color:red"));
        lineThresholdMax->setFrameShadow(QFrame::Plain);
        lineThresholdMax->setLineWidth(3);
        lineThresholdMax->setFrameShape(QFrame::VLine);
        NoClustersSlider = new QSlider(ThresholdSettingsTab);
        NoClustersSlider->setObjectName(QStringLiteral("NoClustersSlider"));
        NoClustersSlider->setGeometry(QRect(40, 230, 160, 19));
        NoClustersSlider->setMinimum(2);
        NoClustersSlider->setMaximum(255);
        NoClustersSlider->setPageStep(5);
        NoClustersSlider->setOrientation(Qt::Horizontal);
        label_12 = new QLabel(ThresholdSettingsTab);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(40, 190, 131, 16));
        NoClustersLbl = new QLabel(ThresholdSettingsTab);
        NoClustersLbl->setObjectName(QStringLiteral("NoClustersLbl"));
        NoClustersLbl->setGeometry(QRect(226, 230, 41, 20));
        SettingsTab->addTab(ThresholdSettingsTab, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        label_14 = new QLabel(tab);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(30, 30, 201, 16));
        label_16 = new QLabel(tab);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(30, 70, 201, 16));
        sizeToleranceSmallerSpinBox = new QSpinBox(tab);
        sizeToleranceSmallerSpinBox->setObjectName(QStringLiteral("sizeToleranceSmallerSpinBox"));
        sizeToleranceSmallerSpinBox->setGeometry(QRect(210, 30, 51, 22));
        sizeToleranceSmallerSpinBox->setMaximum(100);
        sizeToleranceLargerSpinBox = new QSpinBox(tab);
        sizeToleranceLargerSpinBox->setObjectName(QStringLiteral("sizeToleranceLargerSpinBox"));
        sizeToleranceLargerSpinBox->setGeometry(QRect(210, 65, 51, 22));
        sizeToleranceLargerSpinBox->setMaximum(500);
        label_18 = new QLabel(tab);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(30, 110, 161, 16));
        huMomentSimilaritySlider = new QSlider(tab);
        huMomentSimilaritySlider->setObjectName(QStringLiteral("huMomentSimilaritySlider"));
        huMomentSimilaritySlider->setGeometry(QRect(210, 110, 160, 19));
        huMomentSimilaritySlider->setOrientation(Qt::Horizontal);
        label_19 = new QLabel(tab);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(390, 110, 47, 13));
        SettingsTab->addTab(tab, QString());
        buttonBox = new QDialogButtonBox(SettingsDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(340, 360, 171, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        resetValues = new QPushButton(SettingsDialog);
        resetValues->setObjectName(QStringLiteral("resetValues"));
        resetValues->setGeometry(QRect(20, 362, 75, 25));

        retranslateUi(SettingsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SettingsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SettingsDialog, SLOT(reject()));
        QObject::connect(ThresholdMinSlider, SIGNAL(valueChanged(int)), ThresholdMinLbl, SLOT(setNum(int)));
        QObject::connect(ThresholdMaxSlider, SIGNAL(valueChanged(int)), ThresholdMaxLbl, SLOT(setNum(int)));
        QObject::connect(numClusters, SIGNAL(valueChanged(int)), labelCluster, SLOT(setNum(int)));
        QObject::connect(distanceThreshold, SIGNAL(valueChanged(int)), label_distance, SLOT(setNum(int)));
        QObject::connect(NoClustersSlider, SIGNAL(valueChanged(int)), NoClustersLbl, SLOT(setNum(int)));
        QObject::connect(huMomentSimilaritySlider, SIGNAL(valueChanged(int)), label_19, SLOT(setNum(int)));
        QObject::connect(ScoreThreshold, SIGNAL(valueChanged(int)), ScoreThresholdLbl, SLOT(setNum(int)));

        SettingsTab->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QApplication::translate("SettingsDialog", "Dialog", 0));
        label_7->setText(QApplication::translate("SettingsDialog", "Size of pixel in microns", 0));
        label_8->setText(QApplication::translate("SettingsDialog", "Fuducial Marks", 0));
        label_9->setText(QApplication::translate("SettingsDialog", "top left", 0));
        label_10->setText(QApplication::translate("SettingsDialog", "top right", 0));
        label_11->setText(QApplication::translate("SettingsDialog", "bottom left", 0));
        lbl_fm_TL_X->setText(QApplication::translate("SettingsDialog", "X", 0));
        label_13->setText(QApplication::translate("SettingsDialog", ",", 0));
        lbl_fm_TL_Y->setText(QApplication::translate("SettingsDialog", "Y", 0));
        btn_fm_TL->setText(QApplication::translate("SettingsDialog", "Display", 0));
        lbl_fm_TR_Y->setText(QApplication::translate("SettingsDialog", "Y", 0));
        btn_fm_TR->setText(QApplication::translate("SettingsDialog", "Display", 0));
        lbl_fm_TR_X->setText(QApplication::translate("SettingsDialog", "X", 0));
        label_15->setText(QApplication::translate("SettingsDialog", ",", 0));
        lbl_fm_BL_Y->setText(QApplication::translate("SettingsDialog", "Y", 0));
        btn_fm_BL->setText(QApplication::translate("SettingsDialog", "Display", 0));
        lbl_fm_BL_X->setText(QApplication::translate("SettingsDialog", "X", 0));
        label_17->setText(QApplication::translate("SettingsDialog", ",", 0));
        SettingsTab->setTabText(SettingsTab->indexOf(CameraSettingsTab), QApplication::translate("SettingsDialog", "Camera Settings", 0));
        SettingsTab->setTabText(SettingsTab->indexOf(StageSettingsTab), QApplication::translate("SettingsDialog", "Stage Settings", 0));
        label_4->setText(QApplication::translate("SettingsDialog", "Algorithm Type", 0));
        label_distance->setText(QApplication::translate("SettingsDialog", "5", 0));
        labelCluster->setText(QApplication::translate("SettingsDialog", "10", 0));
        label->setText(QApplication::translate("SettingsDialog", "COOC (Colour Cooccurrance) Settings", 0));
        ScoreThresholdLbl->setText(QApplication::translate("SettingsDialog", "100", 0));
        label_22->setText(QApplication::translate("SettingsDialog", "%", 0));
        label_2->setText(QApplication::translate("SettingsDialog", "No. Clusters", 0));
        label_3->setText(QApplication::translate("SettingsDialog", "Distance", 0));
        label_20->setText(QApplication::translate("SettingsDialog", "Score\n"
"Threshold", 0));
        SettingsTab->setTabText(SettingsTab->indexOf(TargetSettingsTab), QApplication::translate("SettingsDialog", "Target Settings", 0));
#ifndef QT_NO_TOOLTIP
        ThresholdMinSlider->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>All values <span style=\" font-weight:600;\">above</span> this threshold are white in the image otherwise black</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        ThresholdMinLbl->setText(QApplication::translate("SettingsDialog", "0", 0));
        label_6->setText(QApplication::translate("SettingsDialog", "Threshold Min", 0));
        label_5->setText(QApplication::translate("SettingsDialog", "Threshold Max", 0));
#ifndef QT_NO_TOOLTIP
        ThresholdMaxSlider->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>All values <span style=\" font-weight:600;\">below</span> this threshold are white in the image otherwise black</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        ThresholdMaxLbl->setText(QApplication::translate("SettingsDialog", "255", 0));
        chkAutoThreshold->setText(QApplication::translate("SettingsDialog", "Automatic Thresholding", 0));
        histogram_image->setText(QString());
#ifndef QT_NO_TOOLTIP
        NoClustersSlider->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>The image will be posterized into the set number of gray levels. When No. levels = 2, this isthe same as performing a binary threshold.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        label_12->setText(QApplication::translate("SettingsDialog", "Number of levels", 0));
        NoClustersLbl->setText(QApplication::translate("SettingsDialog", "2", 0));
        SettingsTab->setTabText(SettingsTab->indexOf(ThresholdSettingsTab), QApplication::translate("SettingsDialog", "Threshold Settings", 0));
#ifndef QT_NO_TOOLTIP
        label_14->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>How much smaller can the detected targets be than the example target.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        label_14->setText(QApplication::translate("SettingsDialog", "Size tolerance (% smaller)", 0));
#ifndef QT_NO_TOOLTIP
        label_16->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>How much bigger can the detected targets be than the example target.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        label_16->setText(QApplication::translate("SettingsDialog", "Size tolerance (% larger)", 0));
#ifndef QT_NO_TOOLTIP
        sizeToleranceSmallerSpinBox->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>How much smaller can the detected targets be than the example target.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        sizeToleranceLargerSpinBox->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>How much bigger can the detected targets be than the example target.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_18->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>Hu moments are calculated for the binary shape, these are shape measures. The similarity setting determines how important similar shape of the detected targets are (100% =  shape must be the same, 0% = shape not important).</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        label_18->setText(QApplication::translate("SettingsDialog", "Hu Moment Similarity (% similar)", 0));
#ifndef QT_NO_TOOLTIP
        huMomentSimilaritySlider->setToolTip(QApplication::translate("SettingsDialog", "<html><head/><body><p>Hu moments are calculated for the binary shape, these are shape measures. The similarity setting determines how important similar shape of the detected targets are (100% = shape must be the same, 0% = shape not important).</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        label_19->setText(QApplication::translate("SettingsDialog", "0", 0));
        SettingsTab->setTabText(SettingsTab->indexOf(tab), QApplication::translate("SettingsDialog", "Connected Components", 0));
        resetValues->setText(QApplication::translate("SettingsDialog", "Reset Values", 0));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
