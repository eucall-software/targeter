#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"
#include "globals.h"
#include "qmath.h"
#include <QDebug>
#include <QBitmap>

/**
*
*  class constructor using passed in settings values
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   SettingsDialog::SettingsDialog
* Qualifier  : QDialog(parent), ui(new Ui::SettingsDialog)
* @param     SettingsValues v 
* @param     QWidget * parent 
* @return    
* Access     public 
*/
SettingsDialog::SettingsDialog(SettingsValues v, QWidget *parent):
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
	create(v);

    ui->setupUi(this);
}


/**
*
* class constructor 
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   SettingsDialog::SettingsDialog
* Qualifier  : QDialog(parent), ui(new Ui::SettingsDialog)
* @param     QWidget * parent 
* @return    
* Access     public 
*/
SettingsDialog::SettingsDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SettingsDialog)
{
	m_Settings.distance = 50;
	m_Settings.cluster = 50;
	m_Settings.algorithmType = algoType::COOC;
	m_Settings.threshold_max = 255;
	m_Settings.threshold_min = 0;
	m_Settings.autoThreshold = true;
	m_Settings.ScoreThreshold = 70;
	m_Settings.NoClustersThreshold = 2;
	m_Settings.huMomentSimilarity = 0;

	ui->setupUi(this);

	initControls();
}

/**
*
* sets initial values of class
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   SettingsDialog::create
* Qualifier 
* @param     SettingsValues v 
* @return    void
* Access     public 
*/
void SettingsDialog::create(SettingsValues v)
{
	m_Settings = v;

	initControls();
}

/**
*
*  Displays histogram image in Qlabel
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   SettingsDialog::setHistogramImage
* Qualifier 
* @param     QImage im 
* @return    void
* Access     public 
*/
void SettingsDialog::setHistogramImage(QImage im)
{
	QPixmap pixmap = QPixmap::fromImage(im);
	ui->histogram_image->setPixmap(pixmap);
	ui->histogram_image->setMask(pixmap.mask());

	ui->histogram_image->show();
}

/**
*
*  initialises values
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   SettingsDialog::initControls
* Qualifier 
* @return    void
* Access     private 
*/
void SettingsDialog::initControls()
{
	ui->numClusters->setValue(m_Settings.cluster);
	//ui->numClusters->setMaximum(m_Settings.cluster << 1);

	//ui->distanceThreshold->setMaximum(m_Settings.distance << 1);
	ui->distanceThreshold->setValue(m_Settings.distance);

	ui->label_distance->setText(QString::number(m_Settings.distance));
	ui->labelCluster->setText(QString::number(m_Settings.cluster));

	ui->ThresholdMaxSlider->setValue(m_Settings.threshold_max);
	ui->ThresholdMinSlider->setValue(m_Settings.threshold_min);

	ui->NoClustersSlider->setValue(m_Settings.NoClustersThreshold);

	ui->ScoreThreshold->setValue(m_Settings.ScoreThreshold);

	ui->ScoreThresholdLbl->setText(QString::number(m_Settings.ScoreThreshold));

	ui->ThresholdMinLbl->setText(QString::number(m_Settings.threshold_min));
	ui->ThresholdMaxLbl->setText(QString::number(m_Settings.threshold_max));

	ui->chkAutoThreshold->setChecked(m_Settings.autoThreshold);
	
	ui->ThresholdMinSlider->setEnabled(!m_Settings.autoThreshold);
	ui->ThresholdMaxSlider->setEnabled(!m_Settings.autoThreshold);
	
	int index = m_Settings.algorithmType;

	ui->AlgoComboBox->clear();

	for (int i = 0; i <= algoType::CCOEFF_NORMED; i++)
		ui->AlgoComboBox->addItem(ALGOSTRINGS(i));

	ui->AlgoComboBox->setCurrentIndex(index);
}

/**
*
* class destructor 
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   SettingsDialog::~SettingsDialog
* Qualifier 
* @return    
* Access     public 
*/
SettingsDialog::~SettingsDialog()
{
    delete ui;
}

/**
*
*  gets settings
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   SettingsDialog::getSettings
* Qualifier 
* @return    SettingsValues
* Access     public 
*/
SettingsValues SettingsDialog::getSettings() { return m_Settings; }


/**
*
*  slot for ui->distanceThreshold changed
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   SettingsDialog::on_distanceThreshold_valueChanged
* Qualifier 
* @param     int value 
* @return    void
* Access     private 
*/
void SettingsDialog::on_distanceThreshold_valueChanged(int value)
{
	m_Settings.distance = value;
}

/**
*
*  slot for ui->numClusters changed
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   SettingsDialog::on_numClusters_valueChanged
* Qualifier 
* @param     int value 
* @return    void
* Access     private 
*/
void SettingsDialog::on_numClusters_valueChanged(int value)
{	
	m_Settings.cluster = value;
}

/**
*
* slot for ui->ThresholdMaxSlider changed
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   SettingsDialog::on_ThresholdMaxSlider_valueChanged
* Qualifier 
* @param     int value 
* @return    void
* Access     private 
*/
void SettingsDialog::on_ThresholdMaxSlider_valueChanged(int value)
{
	// ui->labelCluster->setText(QString::number(value));
	m_Settings.threshold_max = value;

	QRect g = ui->lineThresholdMax->geometry();
	QRect gRectLabel = ui->histogram_image->geometry();

	double posX = double(gRectLabel.width())*(double(value) / 255.0);

	ui->lineThresholdMax->setGeometry(gRectLabel.x() + posX - g.width()/2.0, g.y(), g.width(), g.height());

	if (value <= m_Settings.threshold_min)
	{
		ui->ThresholdMinSlider->setValue(value-1);
		ui->ThresholdMinLbl->setText(QString::number(value-1));
		
		g = ui->lineThresholdMin->geometry();
		posX = double(gRectLabel.width())*(double(value-1) / 255.0);

		ui->lineThresholdMin->setGeometry(gRectLabel.x() + posX - g.width() / 2.0, g.y(), g.width(), g.height());
	}
}



/**
*
* slot for ui->ThresholdMinSlider changed
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   SettingsDialog::on_ThresholdMinSlider_valueChanged
* Qualifier 
* @param     int value 
* @return    void
* Access     private 
*/
void SettingsDialog::on_ThresholdMinSlider_valueChanged(int value)
{
	m_Settings.threshold_min = value;

	QRect g = ui->lineThresholdMin->geometry();
	QRect gRectLabel = ui->histogram_image->geometry();

	double posX = double(gRectLabel.width())*(double(value) / 255.0);

	ui->lineThresholdMin->setGeometry(gRectLabel.x() + posX - g.width()/2.0, g.y(), g.width(), g.height());

	if (value >= m_Settings.threshold_max)
	{
		ui->ThresholdMaxSlider->setValue(value+1);
		ui->ThresholdMaxLbl->setText(QString::number(value+1));
	
		g = ui->lineThresholdMax->geometry();
		posX = double(gRectLabel.width())*(double(value+1) / 255.0);

		ui->lineThresholdMax->setGeometry(gRectLabel.x() + posX - g.width() / 2.0, g.y(), g.width(), g.height());
		
	}
}

/**
*
*  slot for ui->NoClustersSlider changed
*
* @author    David Watts
* @since     2017/03/07
*
* FullName   SettingsDialog::on_NoClustersSlider_valueChanged
* Qualifier
* @param     int value
* @return    void
* Access     private
*/
void SettingsDialog::on_NoClustersSlider_valueChanged(int value)
{
	m_Settings.NoClustersThreshold = value;
}

/**
*
*   slot for ui->ScoreThreshold changed
*
* @author    David Watts
* @since     2017/03/09
* 
* FullName   SettingsDialog::on_ScoreThreshold_valueChanged
* Qualifier 
* @param     int value 
* @return    void
* Access     public 
*/
void SettingsDialog::on_ScoreThreshold_valueChanged(int value)
{
	m_Settings.ScoreThreshold = value;
}

/**
*
*  slot for ui->AlgoComboBox changed Index
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   SettingsDialog::on_AlgoComboBox_currentIndexChanged
* Qualifier 
* @param     int index 
* @return    void
* Access     private 
*/
void SettingsDialog::on_AlgoComboBox_currentIndexChanged(int index)
{
	m_Settings.algorithmType = static_cast<algoType::algoType>(index);

	DBOUT(ALGOSTRINGS(index)<<std::endl);
}

/**
*
*  slot for ui->chkAutoThreshold clicked
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   SettingsDialog::on_chkAutoThreshold_clicked
* Qualifier 
* @param     bool checked 
* @return    void
* Access     private 
*/
void SettingsDialog::on_chkAutoThreshold_clicked(bool checked)
{
	m_Settings.autoThreshold = checked;

	ui->ThresholdMinSlider->setEnabled(!m_Settings.autoThreshold);
	ui->ThresholdMaxSlider->setEnabled(!m_Settings.autoThreshold);
}

/**
*
*  slot for ui->resetValues clicked
*
* @author    David Watts
* @since     2017/03/07
* 
* FullName   SettingsDialog::on_resetValues_clicked
* Qualifier 
* @return    void
* Access     private 
*/
void SettingsDialog::on_resetValues_clicked()
{
	m_Settings.algorithmType = algoType::COOC;
	m_Settings.cluster = 50;
	m_Settings.distance = 50;
	m_Settings.threshold_min = 0;
	m_Settings.threshold_max = 255;
	m_Settings.ScoreThreshold = 70;
	m_Settings.autoThreshold = true;
	m_Settings.NoClustersThreshold = 2;

	initControls();
}


