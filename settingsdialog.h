#ifndef SettingsDialog_H
#define SettingsDialog_H

#include "globals.h"
#include "settingsdialog.h"
#include <QDialog>



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
    explicit SettingsDialog(SettingsValues v, QWidget *parent = 0);
	explicit SettingsDialog(QWidget *parent = 0);

	void create(SettingsValues v);

	void setHistogramImage(QImage im);

    ~SettingsDialog();

	SettingsValues getSettings();

private slots:
    void on_distanceThreshold_valueChanged(int value);
    void on_numClusters_valueChanged(int value);

	void on_ThresholdMaxSlider_valueChanged(int value);
	void on_ThresholdMinSlider_valueChanged(int value);
	void on_NoClustersSlider_valueChanged(int value);
	void on_ScoreThreshold_valueChanged(int value);

    void on_AlgoComboBox_currentIndexChanged(int index);
	void on_chkAutoThreshold_clicked(bool checked);
	void on_resetValues_clicked();

private:
    Ui::SettingsDialog *ui;

	void initControls();

	SettingsValues m_Settings;
};

#endif // SettingsDialog_H
