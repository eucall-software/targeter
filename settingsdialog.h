#ifndef SettingsDialog_H
#define SettingsDialog_H

#include "globals.h"
#include "Settings.h"
#include "settingsdialog.h"
#include <memory>
#include <QDialog>
#include <QLabel>
#include <QHash>
#include <QDoubleSpinBox>


namespace Ui {
	class SettingsDialog;
}
/**
* dialog class to manage application settings
*/
class SettingsDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SettingsDialog(SettingsValues* v, QWidget *parent = 0);
	explicit SettingsDialog(QWidget *parent = 0);

	void create(SettingsValues* v);
	void initializeSettings() { m_Settings->initialize(); };

	void initControls();

	void updateCONNECTPORT(bool XY, QString port);

	void enableFiducial(bool lock);

	void setHistogramImage(QImage im);
	void setImageGridDisplaySize(QSize size);

	bool checkIndex(const double& val1, const double& val2);

	void updateFiducialComboIndex();
	bool checkFiducialsOrder(QInt3DMap fiducial_marks_stage, QIntPointMap fiducial_marks_image, bool bFlagRed = false);

	void setFiducial();
	void updatePositions();
	void updatePosition();
	void setFiducial(int type);

	void setupFiducialMarks();
	bool checkOrder(int startIndex, QPointF tl, QPointF tr, QPointF bl, QPointF br, bool flagRed = true);
	void flagFiducialOrderRed(int ind1, int ind2);

	bool checkFiducialsOrder(bool bFlagRed = true);

	void setActiveTab(QString tabName);

	~SettingsDialog();

	QSize imageSize;				/// Size of current image

	double m_stage_x;
	double m_stage_y;
private:
	Ui::SettingsDialog *ui;

	SettingsValues* m_Settings;

	QHash<int, QLabel*> labelsFiducial;
	QHash<int, QDoubleSpinBox*> spinFiducials_X;
	QHash<int, QDoubleSpinBox*> spinFiducials_Y;
	QHash<int, QDoubleSpinBox*> spinFiducials_stage_X;
	QHash<int, QDoubleSpinBox*> spinFiducials_stage_Y;
	QHash<int, QDoubleSpinBox*> spinFiducials_stage_Z;

public slots:
	void updateCOMPORTS(QVector<QString> strs);
private slots:
	void on_btnCenterGrid_clicked();
	void on_distanceThreshold_valueChanged(int value);
	void on_numClusters_valueChanged(int value);

	void on_cboThresholdType_currentIndexChanged(int index);
	void on_cboSamplingType_currentIndexChanged(int index);

	void on_ThresholdMaxSlider_valueChanged(int value);
	void on_ThresholdMinSlider_valueChanged(int value);

	void on_sliderGridOffsetX_valueChanged(int value);
	void on_sliderGridOffsetY_valueChanged(int value);
	void on_sliderGridSpacingX_valueChanged(int value);
	void on_sliderGridSpacingY_valueChanged(int value);

	void on_sliderBarcodeThreshold_valueChanged(int value);
	void on_chkAutoBarcodeThreshold_clicked(bool checked);

	void on_spinGridOffsetX_valueChanged(double value);
	void on_spinGridOffsetY_valueChanged(double value);
	void on_spinGridSpacingX_valueChanged(double value);
	void on_spinGridSpacingY_valueChanged(double value);

	void on_spinSamplingDistance_valueChanged(int value);
	void on_spinExclusionDistance_valueChanged(int value);

	void on_btnDeleteFiducial_clicked();
	void on_btnLogFeedback_clicked();

	void on_spnTopLeft_Overview_X_valueChanged(double value);
	void on_spnTopLeft_Overview_Y_valueChanged(double value);
	void on_spnTopRight_Overview_X_valueChanged(double value);
	void on_spnTopRight_Overview_Y_valueChanged(double value);
	void on_spnBottomLeft_Overview_X_valueChanged(double value);
	void on_spnBottomLeft_Overview_Y_valueChanged(double value);
	void on_spnBottomRight_Overview_X_valueChanged(double value);
	void on_spnBottomRight_Overview_Y_valueChanged(double value);

	void on_spinXPositionAbsoluteXY_valueChanged(double value);
	void on_spinYPositionAbsoluteXY_valueChanged(double value);
	void on_spinXPositionRelativeXY_valueChanged(double value);
	void on_spinYPositionRelativeXY_valueChanged(double value);

	void on_spnTopLeft_Overview_Stage_X_valueChanged(double value);
	void on_spnTopLeft_Overview_Stage_Y_valueChanged(double value);

	void on_spnTopLeft_Microscope_X_valueChanged(double value);
	void on_spnTopLeft_Microscope_Y_valueChanged(double value);
	void on_spnTopLeft_Microscope_Stage_X_valueChanged(double value);
	void on_spnTopLeft_Microscope_Stage_Y_valueChanged(double value);
	void on_spnTopLeft_Microscope_Stage_Z_valueChanged(double value);

	void on_spnTopRight_Microscope_X_valueChanged(double value);
	void on_spnTopRight_Microscope_Y_valueChanged(double value);
	void on_spnTopRight_Microscope_Stage_X_valueChanged(double value);
	void on_spnTopRight_Microscope_Stage_Y_valueChanged(double value);
	void on_spnTopRight_Microscope_Stage_Z_valueChanged(double value);

	void on_spnBottomLeft_Microscope_X_valueChanged(double value);
	void on_spnBottomLeft_Microscope_Y_valueChanged(double value);
	void on_spnBottomLeft_Microscope_Stage_X_valueChanged(double value);
	void on_spnBottomLeft_Microscope_Stage_Y_valueChanged(double value);
	void on_spnBottomLeft_Microscope_Stage_Z_valueChanged(double value);

	void on_spnBottomRight_Microscope_X_valueChanged(double value);
	void on_spnBottomRight_Microscope_Y_valueChanged(double value);
	void on_spnBottomRight_Microscope_Stage_X_valueChanged(double value);
	void on_spnBottomRight_Microscope_Stage_Y_valueChanged(double value);
	void on_spnBottomRight_Microscope_Stage_Z_valueChanged(double value);

	void on_spinMinFocus_valueChanged(double value);
	void on_spinMaxFocus_valueChanged(double value);
	void on_spinCoarseFocusStep_valueChanged(double value);
	void on_spinFineFocusStep_valueChanged(double value);

	void on_btnCalcTransformationMatrix_clicked();

	void on_spinVelocityXY_valueChanged(double value);
	void on_btnMoveToFiducial_clicked();

	void on_btnMoveAbsoluteXY_clicked();
	void on_btnMoveRelativeXY_clicked();
	void on_btnSendCommandXY_clicked();
	void on_btnSetVelocityXY_clicked();
	void on_btnCalibrateXY_clicked();
	void on_btnMeasureRangeXY_clicked();
	void on_btnConnectXY_clicked();
	void on_btnDisconnectXY_clicked();
	void on_btnAbortXY_clicked();

	void on_btnMoveAbsoluteZ_clicked();
	void on_btnMoveRelativeZ_clicked();
	void on_btnUpZ_pressed();
	void on_btnDownZ_pressed();
	void on_btnUpZ_released();
	void on_btnDownZ_released();

	void on_btnSendCommandZ_clicked();
	void on_btnConnectZ_clicked();
	void on_btnDisconnectZ_clicked();

	void on_spinPositionAbsoluteZ_valueChanged(double value);
	void on_spinPositionRelativeZ_valueChanged(double value);

	void on_btnRestoreBackup_clicked();
	void on_btnSaveBackup_clicked();

	void on_cboSelectFiducial_currentIndexChanged(int value);

	void on_cboBaudXY_currentIndexChanged(int value);

	void on_cboFocusAlgorithm_currentIndexChanged(int value);

	void on_NoClustersSlider_valueChanged(int value);
	void on_ScoreThreshold_valueChanged(int value);

	void on_AlgoComboBox_currentIndexChanged(int index);
	void on_chkAutoThreshold_clicked(bool checked);

	void on_chkCV_CALIB_CB_ADAPTIVE_THRESH_clicked(bool checked);
	void on_chkCV_CALIB_CB_NORMALIZE_IMAGE_clicked(bool checked);

	void on_chkCV_CALIB_CB_FILTER_QUADS_clicked(bool checked);

	void on_btnProjectDirectory_clicked(bool checked);

	void on_cboCalibrateAlgorithm_currentIndexChanged(int index);

	void on_chkCALIB_CB_FAST_CHECK_clicked(bool checked);
	void on_chkCALIB_CB_CLUSTERING_clicked(bool checked);
	void on_chkFixedAspect_clicked(bool checked);
	void on_chkZeroDistortion_clicked(bool checked);
	void on_chkFixPrincipalPointCenter_clicked(bool checked);
	void on_chkIntrinsicGuess_clicked(bool checked);
	void on_chkFixFocalLength_clicked(bool checked);

	void on_spinItemsInRow_valueChanged(int value);
	void on_spinItemsInColumn_valueChanged(int value);
	void on_spinSizeSquare_valueChanged(int value);
	void on_huMomentSimilaritySlider_valueChanged(int value);
	void on_spinAspectTolerance_valueChanged(double value);
	void on_scoreRegionArea_valueChanged(int value);

	void on_chkLockFiducial_clicked(bool checked);
	void on_spOverviewLensFocalLength_valueChanged(int value);
	void on_spMicroscopeLensFocalLength_valueChanged(int value);

	void on_chkDisplayGrid_clicked(bool value);

	void on_chkJoystickOn_clicked(bool on);
	void on_chkKeypadOn_clicked(bool on);

	void on_cboActiveCamera_currentIndexChanged(int value);

	void on_buttonBox_clicked(QAbstractButton *button);

	void on_btnSelectColour_clicked();

	void on_editName_textChanged(QString val);
	void on_editInstitute_textChanged(QString val);
	void on_editProjectName_textChanged(QString val);
	void on_editProjectID_textChanged(QString val);
	void on_editVersion_textChanged(QString val);
	void on_editDescription_textChanged(QString val);
	void on_editSampleDescription_textChanged(QString val);
	void on_editFilenamePrefix_textChanged(QString val);
	void on_editBarcode_textChanged(QString val);
	void on_projectDate_dateChanged(QDate date);
	void on_editProjectDirectoryName_textChanged(QString val);
	void on_lineEditOverviewCameraSN_textChanged(QString val);
	void on_lineEditMicroscopeCameraSN_textChanged(QString val);
	void on_editPixelSizeMicrons_textChanged(QString val);
	
signals:
	void sendSettings();
	void logFeedback(int score, QString name, QString email, QString institute, QString desc);
	void MoveAbsoluteXY(double x, double y, ACTIONS::action act);
	void MoveRelativeXY(double x, double y, ACTIONS::action act);
	void MoveAbsoluteZ(double z, ACTIONS::action act);
	void MoveRelativeZ(double z, ACTIONS::action act);
	void stopMotionZ(ACTIONS::action act);
	void SendCommandXY(QString cmd);
	void SendCommandZ(QString cmd);
	void SetVelocityXY(double velo);
	void SetJoystickXY(bool on);
	void SetKeypadZ(bool on);
	void CalibrateXY();
	void MeasureRangeXY();
	void ConnectXY();
	void DisconnectXY();
	void ConnectZ();
	void DisconnectZ();
	void AbortXY();
	void getCOMPORTS();
	void moveToFiducialFromOverview(QPoint pt);
	void createTransformationMatrix(QVector3D topleft, QVector3D topright, QVector3D bottomleft);

	void saveBackup(bool bLoad);
	
	void LOGCONSOLE(QString strText, CONSOLECOLOURS::colour col);
	void SETFIDUCIALPOSITION(FIDUCIAL::position index);
	void LockFiducial(bool clicked);
};

#endif // SettingsDialog_H
