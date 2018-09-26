#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"
#include "globals.h"
#include "Settings.h"
#include "qmath.h"
#include <QDebug>
#include <QThread>
#include <QBitmap>
#include <QColorDialog>
#include <QFileDialog>

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
SettingsDialog::SettingsDialog(SettingsValues* v, QWidget *parent):
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
	create(v);

	m_stage_x = -1;
	m_stage_y = -1;

	imageSize = QSize(128, 128);

    ui->setupUi(this);


	//connect(ui->SettingsTab, &QTabWidget::setCurrentIndex, this, &SettingsDialog::onTabIndexChanged);
}
/*
void SettingsDialog::on_SettingsTab_setCurrentIndex(int index)
{
	QString tab = ui->SettingsTab->tabText(index);

	if(tab == "projectData")
	{
		// update QDom structure
		//refresh the display

	}

}
*/
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
	ui->setupUi(this);
}

void SettingsDialog::on_buttonBox_clicked(QAbstractButton *button)
{
	if (button == ui->buttonBox->button(QDialogButtonBox::Ok) || button == ui->buttonBox->button(QDialogButtonBox::Apply)) 
	{
		// get project settings
		m_Settings->s_project_Barcode = ui->editBarcode->text();
		m_Settings->s_project_Description = ui->editDescription->text();
		m_Settings->s_project_Directory = ui->editProjectDirectoryName->text();
		m_Settings->s_project_FilenamePrefix = ui->editFilenamePrefix->text();
		m_Settings->s_project_Username = ui->editName->text();
		m_Settings->s_project_Institute = ui->editInstitute->text();
		m_Settings->s_project_Name = ui->editProjectName->text();
		m_Settings->s_project_ID = ui->editProjectID->text();
		m_Settings->s_project_Version =	ui->editVersion->text();
		m_Settings->s_project_SampleDescription	= ui->editSampleDescription->text();
		m_Settings->d_project_Date = ui->projectDate->date();

		emit sendSettings();
	}
	else if(button == ui->buttonBox->button(QDialogButtonBox::RestoreDefaults))
	{	
		m_Settings->initialize();
		initControls();
	}
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
void SettingsDialog::create(SettingsValues* v)
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

	int w = im.width();
	int h = im.width();

	ui->histogram_image->show();
}

void SettingsDialog::setActiveTab(QString tabName)
{
	int i = ui->SettingsTab->indexOf(ui->SettingsTab->findChild<QWidget*>(tabName));

	if(i>=0)
		ui->SettingsTab->setCurrentIndex(i);
}

void SettingsDialog::setImageGridDisplaySize(QSize size)
{
	int w = size.width();
	int h = size.height();

	// set grid values based on image size
	if (h > 0 && w > 0)
	{
		ui->sliderGridSpacingX->setMaximum(w);
		ui->sliderGridSpacingY->setMaximum(h);
		ui->sliderGridSpacingX->setPageStep(w / 10.0);
		ui->sliderGridSpacingY->setPageStep(h / 10.0);

		imageSize = size;
	}
}

void SettingsDialog::on_btnCenterGrid_clicked()
{
	ui->sliderGridSpacingX->setValue(imageSize.width() / 2.0);
	ui->sliderGridSpacingY->setValue(imageSize.height() / 2.0);
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
	m_stage_x = 0;
	m_stage_y = 0;

	ui->numClusters->setValue(m_Settings->cluster);
	ui->labelCluster->setText(QString::number(m_Settings->cluster));

	ui->distanceThreshold->setValue(m_Settings->distance);
	ui->label_distance->setText(QString::number(m_Settings->distance));

	ui->distanceBinsThreshold->setValue(m_Settings->distanceBins);
	ui->label_distanceBins->setText(QString::number(m_Settings->distanceBins));

	ui->ThresholdMaxSlider->setValue(m_Settings->threshold_max);
	ui->ThresholdMinSlider->setValue(m_Settings->threshold_min);

	ui->NoClustersSlider->setValue(m_Settings->NoClustersThreshold);

	ui->ScoreThreshold->setValue(m_Settings->ScoreThreshold);

	ui->scoreRegionArea->setValue(m_Settings->scoreAreaFactor);

	ui->ScoreThresholdLbl->setText(QString::number(m_Settings->ScoreThreshold));

	ui->ThresholdMinLbl->setText(QString::number(m_Settings->threshold_min));
	ui->ThresholdMaxLbl->setText(QString::number(m_Settings->threshold_max));

	ui->chkAutoThreshold->setChecked(m_Settings->autoThreshold);
	
	ui->ThresholdMinSlider->setEnabled(!m_Settings->autoThreshold);
	ui->ThresholdMaxSlider->setEnabled(!m_Settings->autoThreshold);


	ui->chkCALIB_CB_CLUSTERING->setChecked(m_Settings->bCALIB_CB_CLUSTERING);
	ui->chkCALIB_CB_FAST_CHECK->setChecked(m_Settings->bCALIB_CB_FAST_CHECK);
	
	ui->chkCV_CALIB_CB_ADAPTIVE_THRESH->setChecked(m_Settings->bCV_CALIB_CB_ADAPTIVE_THRESH);
	ui->chkCV_CALIB_CB_FILTER_QUADS->setChecked(m_Settings->bCV_CALIB_CB_FILTER_QUADS);
	ui->chkCV_CALIB_CB_NORMALIZE_IMAGE->setChecked(m_Settings->bCV_CALIB_CB_NORMALIZE_IMAGE);

	ui->chkFixedAspect->setChecked(m_Settings->FixedAspect);
	ui->chkFixPrincipalPointCenter->setChecked(m_Settings->FixPrincipalPointCenter);
	ui->chkZeroDistortion->setChecked(m_Settings->ZeroDistortion);

	ui->chkProcessGrayscale->setChecked(m_Settings->bProcessGrayscale);

	ui->spinSizeSquare->setValue(m_Settings->SizeOfSquare);
	ui->spinItemsInRow->setValue(m_Settings->calibrateNoRows);
	ui->spinItemsInColumn->setValue(m_Settings->calibrateNoRows);

	ui->spinGridOffsetX->setValue(m_Settings->gridOffsetX);
	ui->spinGridOffsetY->setValue(m_Settings->gridOffsetY);
	ui->spinGridSpacingX->setValue(m_Settings->gridSpacingX);
	ui->spinGridSpacingY->setValue(m_Settings->gridSpacingY);
	ui->chkDisplayGrid->setChecked(m_Settings->displayGrid);

	ui->spinDefaultFocusPosition->setValue(m_Settings->m_DefaultFocusPosition);
	ui->spinFocusRange->setValue(m_Settings->m_FocusRange);
	ui->spinCoarseFocusStep->setValue(m_Settings->m_CoarseFocusStep);
	ui->spinFineFocusStep->setValue(m_Settings->m_FineFocusStep);

	updateSamplingSpacing();

	ui->spOverviewLensFocalLength->setValue(m_Settings->focalDistanceOverviewCamera);
	ui->spMicroscopeLensFocalLength->setValue(m_Settings->focalDistanceMicroscopeCamera);

	ui->chkIntrinsicGuess->setChecked(m_Settings->UseIntrinsicGuess);
	ui->chkFixFocalLength->setChecked(m_Settings->FixFocalLength);

	ui->chkLockFiducial->setChecked(m_Settings->bLockFiducial);
	ui->chkPaddTargetImage->setChecked(m_Settings->bPaddTargetImage);
	ui->spinWaveletLevels->setValue(m_Settings->numWaveletLevels);

	ui->chkOptimiseFocusRange->setChecked(m_Settings->m_bOptimiseFocusRange);
	ui->chkInterpolateFocusPosition->setChecked(m_Settings->m_bInterpolateFocusPosition);
	ui->chkUseFocusThreshold->setChecked(m_Settings->m_bUseFocusThreshold);
	ui->chkUseCoarseFocusRange->setChecked(m_Settings->m_bUseCoarseFocusRange);
	ui->chkUseFineFocusRange->setChecked(m_Settings->m_bUseFineFocusRange);
	ui->chkCenterFocus->setChecked(m_Settings->m_bCenterFocus);
	ui->chkUseRegisteredFocusPoints->setChecked(m_Settings->m_bUseRegisteredFocusPoints);
	ui->chkShowBestFocusImage->setChecked(m_Settings->m_bShowBestFocusImage);
	ui->chkDetectTargetsWhileScanning->setChecked(m_Settings->m_bDetectTargetsWhileScanning);
	ui->chkCorrectBackGround->setChecked(m_Settings->bCorrectBackGround);

	enableFiducial(m_Settings->bLockFiducial);

	ui->sliderBarcodeThreshold->setValue(m_Settings->BarcodeThreshold);
	ui->chkAutoBarcodeThreshold->setChecked(m_Settings->BarcodeAutoThreshold);

	ui->spinAspectTolerance->setValue(m_Settings->AspectTolerance);

	ui->huMomentSimilaritySlider->setValue(m_Settings->huMomentSimilarity);

	ui->cboCalibrateAlgorithm->setCurrentIndex((int)m_Settings->CalibrateAlgorithm);

	ui->lbl_barCode_X->setText(QString::number(m_Settings->s_BarCodeImageRect.x()));
	ui->lbl_barCode_Y->setText(QString::number(m_Settings->s_BarCodeImageRect.y()));
	ui->lbl_barCode_W->setText(QString::number(m_Settings->s_BarCodeImageRect.width()));
	ui->lbl_barCode_H->setText(QString::number(m_Settings->s_BarCodeImageRect.height()));

	ui->editPixelSizeMicrons->setText(QString::number(m_Settings->mmPerPixel));

	ui->spnImageWidthPixels->setValue(m_Settings->imageWidth);
	ui->spnImageHeightPixels->setValue(m_Settings->imageHeight);

	ui->lblImageWidthMicrons->setText(QString::number(m_Settings->mmPerPixel*double(m_Settings->imageWidth)));
	ui->lblImageHeightMicrons->setText(QString::number(m_Settings->mmPerPixel*double(m_Settings->imageHeight)));

	int index = m_Settings->algorithmType;

	ui->AlgoComboBox->clear();

	for (int i = 0; i <= algoType::LASTALGO; i++)
		ui->AlgoComboBox->addItem(ALGOSTRINGS(i));

	ui->AlgoComboBox->setCurrentIndex(index);

	index = m_Settings->FocusAlgorithm;

	ui->cboFocusAlgorithm->clear();

	for (int i = 0; i <= FOCUSALGO::algo::HAARPY; i++)
		ui->cboFocusAlgorithm->addItem(FOCUS_ALGO_STRINGS(i));

	ui->cboFocusAlgorithm->setCurrentIndex(index);

	ui->cboFocusPosition->clear();

	for (int i = 0; i < m_Settings->focusPoints.length(); i++)
	{
		QVector3D pos = m_Settings->focusPoints[i];
		ui->cboFocusPosition->addItem("{x: " + QString::number(pos.x()) + ", y: " + QString::number(pos.y()) + ", z: " + QString::number(pos.z()) + "}");
	}

	int cameraType = m_Settings->activeCamera;

	ui->cboActiveCamera->clear();

	for (int i = 0; i <= cameraType::camera::none; i++)
		ui->cboActiveCamera->addItem(CAMERATYPE(i));

	ui->cboActiveCamera->setCurrentIndex(cameraType);
	
	int type = m_Settings->ThresholdType;	// needed because setcurrentindex changes this value

	ui->cboThresholdType->clear();

	for (int i = 0; i <= thresholdType::posterize; i++)
		ui->cboThresholdType->addItem(THRESHOLDSTRINGS(i));

	ui->cboThresholdType->setCurrentIndex(type);

	ui->cboAnnotationColour->clear();

	for (int i = 0; i <= drawingItems::grid; i++)
	{
		ui->cboAnnotationColour->addItem(DRAWINGITEMS(i));
		ui->cboAnnotationColour->setItemData(i, m_Settings->objectColours[i], Qt::ForegroundRole);
	}

	type = m_Settings->samplingType;

	ui->cboSamplingType->setCurrentIndex(type);

	ui->cboSamplingType->clear();

	for (int i = 0; i <= SAMPLINGTYPE::noedge; i++)
		ui->cboSamplingType->addItem(SAMPLINGTYPE_STRINGS(i));
	
	// camera IP addresses
	ui->lineEditMicroscopeCameraSN->setText(QString::number(m_Settings->microscopeCameraSN));
	ui->lineEditOverviewCameraSN->setText(QString::number(m_Settings->overviewCameraSN));

	ui->projectDate->setCalendarPopup(true);

	ui->editName->setText(m_Settings->s_project_Username);
	ui->editInstitute->setText(m_Settings->s_project_Institute);
	ui->editProjectName->setText(m_Settings->s_project_Name);
	ui->editProjectID->setText(m_Settings->s_project_ID);
	ui->editVersion->setText(m_Settings->s_project_Version);
	ui->editDescription->setText(m_Settings->s_project_Description);
	ui->editSampleDescription->setText(m_Settings->s_project_SampleDescription);
	ui->editFilenamePrefix->setText(m_Settings->s_project_FilenamePrefix);
	ui->editBarcode->setText(m_Settings->s_project_Barcode);
	ui->projectDate->setDate(m_Settings->d_project_Date);
	ui->editProjectDirectoryName->setText(m_Settings->s_project_Directory);

	ui->spinXPositionRelativeXY->setValue(m_Settings->XPositionRelativeXY);
	ui->spinYPositionRelativeXY->setValue(m_Settings->YPositionRelativeXY);
	ui->spinXPositionAbsoluteXY->setValue(m_Settings->XPositionAbsoluteXY);
	ui->spinYPositionAbsoluteXY->setValue(m_Settings->YPositionAbsoluteXY);
	ui->spinPositionAbsoluteZ->setValue(m_Settings->PositionAbsoluteZ);
	ui->spinPositionRelativeZ->setValue(m_Settings->PositionRelativeZ);

	ui->spinFocusFraction->setValue(m_Settings->m_FocusThresholdFraction);

	ui->spinVelocityXY->setValue(m_Settings->VelocityXY);
	ui->cboBaudXY->setCurrentIndex(3);
	ui->editSendCommandXY->setText(m_Settings->s_CommandTextXY);

	setupFiducialMarks();
}

void SettingsDialog::updateFiducialComboIndex()
{
	ui->cboSelectFiducial->setCurrentIndex(ui->cboSelectFiducial->findData(QString::number(m_Settings->fiducialPos)));
}

void SettingsDialog::setupFiducialMarks()
{
	labelsFiducial[FIDUCIAL::position::topleft_overview] = ui->lbl_topleft_overview;
	labelsFiducial[FIDUCIAL::position::topright_overview] = ui->lbl_topright_overview;
	labelsFiducial[FIDUCIAL::position::bottomleft_overview] = ui->lbl_bottomleft_overview;
	labelsFiducial[FIDUCIAL::position::bottomright_overview] = ui->lbl_bottomright_overview;
	labelsFiducial[FIDUCIAL::position::topleft_microscope] = ui->lbl_topleft_microscope;
	labelsFiducial[FIDUCIAL::position::topright_microscope] = ui->lbl_topright_microscope;
	labelsFiducial[FIDUCIAL::position::bottomleft_microscope] = ui->lbl_bottomleft_microscope;
	labelsFiducial[FIDUCIAL::position::bottomright_microscope] = ui->lbl_bottomright_microscope;

	// fiducial marks

	int fidpos = m_Settings->fiducialPos;

	ui->cboSelectFiducial->clear();

	for (int i = 0; i <= FIDUCIAL::position::bottomright_microscope; i++)
	{
		QString s = FIDUCIAL_POSITION_STRINGS(i);

		ui->cboSelectFiducial->addItem(s, QString::number(i));
	}

	ui->cboSelectFiducial->setCurrentIndex(ui->cboSelectFiducial->findData(QString::number(fidpos)));

	spinFiducials_X.clear();
	spinFiducials_Y.clear();

	// images

	// overview
	spinFiducials_X[FIDUCIAL::position::topleft_overview] = ui->spnTopLeft_Overview_X;
	spinFiducials_Y[FIDUCIAL::position::topleft_overview] = ui->spnTopLeft_Overview_Y;

	spinFiducials_X[FIDUCIAL::position::topright_overview] = ui->spnTopRight_Overview_X;
	spinFiducials_Y[FIDUCIAL::position::topright_overview] = ui->spnTopRight_Overview_Y;

	spinFiducials_X[FIDUCIAL::position::bottomleft_overview] = ui->spnBottomLeft_Overview_X;
	spinFiducials_Y[FIDUCIAL::position::bottomleft_overview] = ui->spnBottomLeft_Overview_Y;

	spinFiducials_X[FIDUCIAL::position::bottomright_overview] = ui->spnBottomRight_Overview_X;
	spinFiducials_Y[FIDUCIAL::position::bottomright_overview] = ui->spnBottomRight_Overview_Y;

	// microscope image
	spinFiducials_X[FIDUCIAL::position::topleft_microscope] = ui->spnTopLeft_Microscope_X;
	spinFiducials_Y[FIDUCIAL::position::topleft_microscope] = ui->spnTopLeft_Microscope_Y;

	spinFiducials_X[FIDUCIAL::position::topright_microscope] = ui->spnTopRight_Microscope_X;
	spinFiducials_Y[FIDUCIAL::position::topright_microscope] = ui->spnTopRight_Microscope_Y;

	spinFiducials_X[FIDUCIAL::position::bottomleft_microscope] = ui->spnBottomLeft_Microscope_X;
	spinFiducials_Y[FIDUCIAL::position::bottomleft_microscope] = ui->spnBottomLeft_Microscope_Y;

	spinFiducials_X[FIDUCIAL::position::bottomright_microscope] = ui->spnBottomRight_Microscope_X;
	spinFiducials_Y[FIDUCIAL::position::bottomright_microscope] = ui->spnBottomRight_Microscope_Y;

	//  stage

	//stage
	spinFiducials_stage_X[FIDUCIAL::position::topleft_overview] = ui->spnTopLeft_Overview_Stage_X;
	spinFiducials_stage_Y[FIDUCIAL::position::topleft_overview] = ui->spnTopLeft_Overview_Stage_Y;

	spinFiducials_stage_X[FIDUCIAL::position::topright_overview] = ui->spnTopLeft_Overview_Stage_X;
	spinFiducials_stage_Y[FIDUCIAL::position::topright_overview] = ui->spnTopLeft_Overview_Stage_Y;

	spinFiducials_stage_X[FIDUCIAL::position::bottomleft_overview] = ui->spnTopLeft_Overview_Stage_X;
	spinFiducials_stage_Y[FIDUCIAL::position::bottomleft_overview] = ui->spnTopLeft_Overview_Stage_Y;

	spinFiducials_stage_X[FIDUCIAL::position::bottomright_overview] = ui->spnTopLeft_Overview_Stage_X;
	spinFiducials_stage_Y[FIDUCIAL::position::bottomright_overview] = ui->spnTopLeft_Overview_Stage_Y;

	// microscope
	spinFiducials_stage_X[FIDUCIAL::position::topleft_microscope] = ui->spnTopLeft_Microscope_Stage_X;
	spinFiducials_stage_Y[FIDUCIAL::position::topleft_microscope] = ui->spnTopLeft_Microscope_Stage_Y;
	spinFiducials_stage_Z[FIDUCIAL::position::topleft_microscope] = ui->spnTopLeft_Microscope_Stage_Z;

	spinFiducials_stage_X[FIDUCIAL::position::topright_microscope] = ui->spnTopRight_Microscope_Stage_X;
	spinFiducials_stage_Y[FIDUCIAL::position::topright_microscope] = ui->spnTopRight_Microscope_Stage_Y;
	spinFiducials_stage_Z[FIDUCIAL::position::topright_microscope] = ui->spnTopRight_Microscope_Stage_Z;

	spinFiducials_stage_X[FIDUCIAL::position::bottomleft_microscope] = ui->spnBottomLeft_Microscope_Stage_X;
	spinFiducials_stage_Y[FIDUCIAL::position::bottomleft_microscope] = ui->spnBottomLeft_Microscope_Stage_Y;
	spinFiducials_stage_Z[FIDUCIAL::position::bottomleft_microscope] = ui->spnBottomLeft_Microscope_Stage_Z;

	spinFiducials_stage_X[FIDUCIAL::position::bottomright_microscope] = ui->spnBottomRight_Microscope_Stage_X;
	spinFiducials_stage_Y[FIDUCIAL::position::bottomright_microscope] = ui->spnBottomRight_Microscope_Stage_Y;
	spinFiducials_stage_Z[FIDUCIAL::position::bottomright_microscope] = ui->spnBottomRight_Microscope_Stage_Z;

	// image positions
	for (int i = 0; i <= FIDUCIAL::position::bottomright_microscope; i++)
	{
		QPointF p = m_Settings->fiducial_marks_image[i];

		spinFiducials_X[i]->setValue(p.x());
		spinFiducials_Y[i]->setValue(p.y());

		// stage positions
		QVector3D pv = m_Settings->fiducial_marks_stage[i];

		spinFiducials_stage_X[i]->setValue(pv.x());
		spinFiducials_stage_Y[i]->setValue(pv.y());

		// only do focus Z axis for microscope
		if(i>FIDUCIAL::position::bottomright_overview)
			spinFiducials_stage_Z[i]->setValue(pv.z());
	}

	this->setStyleSheet("QDoubleSpinBox.highlight{ background-color: yellow; }");

	checkFiducialsOrder();
}

void SettingsDialog::flagFiducialOrderRed(int ind1, int ind2)
{
	spinFiducials_X[ind1]->setStyleSheet("color: rgb(255,0,0); ");
	spinFiducials_Y[ind1]->setStyleSheet("color: rgb(255,0,0); ");
	spinFiducials_X[ind2]->setStyleSheet("color: rgb(255,0,0); ");
	spinFiducials_Y[ind2]->setStyleSheet("color: rgb(255,0,0); ");
}

bool SettingsDialog::checkIndex(const double& val1, const double& val2)
{
	if (val1 < 0 || val2 < 0)
		return false;

	if (val1 < val2)
		return true;
	else
		return false;
}

bool SettingsDialog::checkOrder(int startIndex, QPointF top_Left, QPointF top_Right, QPointF bottom_Left, QPointF bottom_Right, bool flagRed)
{
	bool bInOrder = true;
	
	int c = startIndex > 3 ? 4 : 0;	// reference XY stage not image
	int ind1, ind2, col=0;

	QModelIndex index1, index2;

	ind1 = startIndex;

	if (!checkIndex(top_Left.x(), top_Right.x()))
		if (flagRed)
			flagFiducialOrderRed(ind1, startIndex + 1);

	if (!checkIndex(top_Left.x(), bottom_Right.x()))
		if (flagRed)
			flagFiducialOrderRed(ind1, startIndex + 3);

	if (!checkIndex(top_Left.y(), bottom_Left.y()))
		if (flagRed)
			flagFiducialOrderRed(ind1, startIndex + 2);

	if (!checkIndex(top_Left.y(), bottom_Right.y()))
		if (flagRed)
			flagFiducialOrderRed(ind1, startIndex + 3);
	
	ind1 = startIndex + 3;

	if (!checkIndex(bottom_Left.x(), bottom_Right.x()))
		if (flagRed)
			flagFiducialOrderRed(startIndex + 2, ind1);

	if (!checkIndex(top_Right.y(), bottom_Right.y()))
		if (flagRed)
			flagFiducialOrderRed(startIndex + 1, ind1);

	return bInOrder;
}

bool SettingsDialog::checkFiducialsOrder(bool bFlagRed)
{
	bool bInOrder = true;

	QString str= "";		

	for (int i = 0; i <= FIDUCIAL::position::bottomright_microscope; i++)
	{
		spinFiducials_X[i]->setStyleSheet("color: rgb(0,0,0); ");
		spinFiducials_Y[i]->setStyleSheet("color: rgb(0,0,0); ");
		spinFiducials_stage_X[i]->setStyleSheet("color: rgb(0,0,0); ");
		spinFiducials_stage_Y[i]->setStyleSheet("color: rgb(0,0,0); ");

		if(i>FIDUCIAL::position::bottomright_overview)
			spinFiducials_stage_Z[i]->setStyleSheet("color: rgb(0,0,0); ");
	}

	return checkFiducialsOrder(m_Settings->fiducial_marks_stage, m_Settings->fiducial_marks_image, true);
}

bool SettingsDialog::checkFiducialsOrder(QInt3DMap fiducial_marks_stage, QIntPointMap fiducial_marks_image, bool bFlagRed)
{
	bool bInOrder = true;

	QString str = "";

	int startIndex = FIDUCIAL::position::topleft_overview;

	QPointF tl = m_Settings->fiducial_marks_image[startIndex];
	QPointF tr = m_Settings->fiducial_marks_image[startIndex + 1];
	QPointF bl = m_Settings->fiducial_marks_image[startIndex + 2];
	QPointF br = m_Settings->fiducial_marks_image[startIndex + 3];

	if (!checkOrder(startIndex, tl, tr, bl, br, bFlagRed))
	{
		str = "fiducial marks of overview camera image are not in order";
		bInOrder = false;
	}

	startIndex = FIDUCIAL::position::topleft_microscope;

	tl = m_Settings->fiducial_marks_stage[startIndex].toPointF();
	tr = m_Settings->fiducial_marks_stage[startIndex + 1].toPointF();
	bl = m_Settings->fiducial_marks_stage[startIndex + 2].toPointF();
	br = m_Settings->fiducial_marks_stage[startIndex + 3].toPointF();

	if (!checkOrder(startIndex, br, bl, tr, tl, bFlagRed))	// stage coordinate system reversed in X and Y!
	{
		str += " fiducial marks of microscope image are not in order";
		bInOrder = false;
	}

	ui->lblFiducialCheck->setText(str);

	return bInOrder;
}

void SettingsDialog::on_cboSelectFiducial_currentIndexChanged(int value)
{
	int index = ui->cboSelectFiducial->itemData(value).toInt();

	foreach(QWidget* label, labelsFiducial)
		((QLabel*)label)->setStyleSheet("color: rgb(0,0,0); ");

	// change text colour of fiducials or underline
	labelsFiducial[index]->setStyleSheet("color: rgb(0,255,0); ");

	emit SETFIDUCIALPOSITION((FIDUCIAL::position) index);
}

void SettingsDialog::on_chkLockFiducial_clicked(bool clicked)
{
	m_Settings->bLockFiducial = clicked;

	enableFiducial(clicked);
}

void SettingsDialog::on_chkPaddTargetImage_clicked(bool checked)
{
	m_Settings->bPaddTargetImage = checked;
	emit updatePaddTarget(m_Settings->bPaddTargetImage, m_Settings->numWaveletLevels);
}

void SettingsDialog::enableFiducial(bool lock)
{
	if (lock)
	{
		for (int i = 0; i <= FIDUCIAL::position::bottomright_microscope; i++)
		{
			if (spinFiducials_X[i])
				spinFiducials_X[i]->setEnabled(false);
			if (spinFiducials_Y[i])
				spinFiducials_Y[i]->setEnabled(false);
			if (spinFiducials_stage_X[i])
				spinFiducials_stage_X[i]->setEnabled(false);
			if (spinFiducials_stage_Y[i])
				spinFiducials_stage_Y[i]->setEnabled(false);
			if (spinFiducials_stage_Z[i])
				spinFiducials_stage_Z[i]->setEnabled(false);

			ui->btnDeleteFiducial->setEnabled(false);
		}
	}
	else
	{
		for (int i = 0; i <= FIDUCIAL::position::bottomright_microscope; i++)
		{
			if (spinFiducials_X[i])
				spinFiducials_X[i]->setEnabled(true);
			if (spinFiducials_Y[i])
				spinFiducials_Y[i]->setEnabled(true);
			if (spinFiducials_stage_X[i])
				spinFiducials_stage_X[i]->setEnabled(true);
			if (spinFiducials_stage_Y[i])
				spinFiducials_stage_Y[i]->setEnabled(true);
			if (spinFiducials_stage_Z[i])
				spinFiducials_stage_Z[i]->setEnabled(true);

			ui->btnDeleteFiducial->setEnabled(true);
		}
	}

	emit LockFiducial(lock);
}

void SettingsDialog::setFiducial(int type)
{
	if (type > FIDUCIAL::position::bottomright_microscope)
	{
		QString message = "To properly set the stage fiducial position the microscope objective must be used so that the stage is in the correct position";
		emit LOGCONSOLE(message, CONSOLECOLOURS::colour::Warning);
	}

	if (type <= FIDUCIAL::position::bottomright_microscope)
	{
		m_Settings->fiducial_marks_image[type] = QPointF(m_Settings->m_image_position_XY_X, m_Settings->m_image_position_XY_Y);
		m_Settings->fiducial_marks_stage[type] = QVector3D(m_Settings->m_stage_position_XY_X, m_Settings->m_stage_position_XY_Y, m_Settings->m_stage_position_Z);

		spinFiducials_X[type]->setValue(m_Settings->m_image_position_XY_X);
		spinFiducials_Y[type]->setValue(m_Settings->m_image_position_XY_Y);

		// if microscope then set stage positions
		spinFiducials_stage_X[type]->setValue(m_Settings->m_stage_position_XY_X);
		spinFiducials_stage_Y[type]->setValue(m_Settings->m_stage_position_XY_Y);

		if(type>FIDUCIAL::position::bottomright_overview)
			spinFiducials_stage_Z[type]->setValue(m_Settings->m_stage_position_Z);
	}

	checkFiducialsOrder();
}

void SettingsDialog::setFiducial()
{
	QVariant v = ui->cboSelectFiducial->currentData();

	int value = v.toInt();

	setFiducial(value);
}

void SettingsDialog::on_btnDeleteFiducial_clicked()
{
	int value = ui->cboSelectFiducial->currentIndex();

	spinFiducials_X[value]->setValue(-1);
	spinFiducials_Y[value]->setValue(-1);

	spinFiducials_stage_X[value]->setValue(-1);
	spinFiducials_stage_Y[value]->setValue(-1);

	if (value > FIDUCIAL::position::bottomright_microscope)
	{
		spinFiducials_stage_Z[value]->setValue(-1);
		m_Settings->fiducial_marks_stage[value] = QVector3D(-1, -1, -1);
	}
	else
		m_Settings->fiducial_marks_image[value] = QPointF(-1, -1);
}

void SettingsDialog::on_btnMoveToFiducial_clicked()
{
	int index = ui->cboSelectFiducial->currentData().toInt();

	if (index > FIDUCIAL::position::bottomright_overview)
	{
		QVector3D p = m_Settings->fiducial_marks_stage[index];

		if(p.x()>=0 && p.y()>=0)
		{
			emit MoveAbsoluteXY(p.x(), p.y(), ACTIONS::action::nothing);
			emit MoveAbsoluteZ(p.z(), ACTIONS::action::nothing);
		}
		else
		{
			QString s = "no stage fiducial position for ";
			s += FIDUCIAL_POSITION_STRINGS(index);
			s += " recorded";

			emit LOGCONSOLE(s, CONSOLECOLOURS::Information);
		}
	}
	else
	{
		QPointF pt = m_Settings->fiducial_marks_image[index];
	
		if (pt.x() >= 0 && pt.y() >= 0)
			emit moveToFiducialFromOverview(pt.toPoint());
		else
		{
			QString s = "no image fiducial position for ";
			s += FIDUCIAL_POSITION_STRINGS(index);
			s += " recorded";

			emit LOGCONSOLE(s, CONSOLECOLOURS::Information);
		}
	}
}

void SettingsDialog::on_btnCalcTransformationMatrix_clicked()
{
	if(checkFiducialsOrder())
	{
		// create QRect of fiducial positions in image
		QPolygonF imageFiducials;
		imageFiducials.append(QPointF(m_Settings->fiducial_marks_image[FIDUCIAL::position::topleft_overview].x(), m_Settings->fiducial_marks_image[FIDUCIAL::position::topleft_overview].y()));
		imageFiducials.append(QPointF(m_Settings->fiducial_marks_image[FIDUCIAL::position::topright_overview].x(), m_Settings->fiducial_marks_image[FIDUCIAL::position::topright_overview].y()));
		imageFiducials.append(QPointF(m_Settings->fiducial_marks_image[FIDUCIAL::position::bottomleft_overview].x(), m_Settings->fiducial_marks_image[FIDUCIAL::position::bottomleft_overview].y()));
		imageFiducials.append(QPointF(m_Settings->fiducial_marks_image[FIDUCIAL::position::bottomright_overview].x(), m_Settings->fiducial_marks_image[FIDUCIAL::position::bottomright_overview].y()));

		QPolygonF stageFiducials;

		stageFiducials.append(QPointF(m_Settings->fiducial_marks_stage[FIDUCIAL::position::topleft_microscope].x(), m_Settings->fiducial_marks_stage[FIDUCIAL::position::topleft_microscope].y()));
		stageFiducials.append(QPointF(m_Settings->fiducial_marks_stage[FIDUCIAL::position::topright_microscope].x(), m_Settings->fiducial_marks_stage[FIDUCIAL::position::topright_microscope].y()));
		stageFiducials.append(QPointF(m_Settings->fiducial_marks_stage[FIDUCIAL::position::bottomleft_microscope].x(), m_Settings->fiducial_marks_stage[FIDUCIAL::position::bottomleft_microscope].y()));
		stageFiducials.append(QPointF(m_Settings->fiducial_marks_stage[FIDUCIAL::position::bottomright_microscope].x(), m_Settings->fiducial_marks_stage[FIDUCIAL::position::bottomright_microscope].y()));

		QTransform trans;

		// if possible to get transformation matrix
		if (QTransform::quadToQuad(imageFiducials, stageFiducials, m_Settings->m_coordinateTransform)) 
			emit LOGCONSOLE("coordinate transform successfully registered", CONSOLECOLOURS::Information);
		else
			emit LOGCONSOLE("unable to calculate coordinate transform", CONSOLECOLOURS::Information);

		// now create Fiducials to Stage transformation matrix
/*
		emit createTransformationMatrix(QVector3D(3,3,3), QVector3D(6,3,3), QVector3D(3, 6,6));	// test matrix
*/
		
		emit createTransformationMatrix(m_Settings->fiducial_marks_stage[FIDUCIAL::position::topleft_microscope],
			m_Settings->fiducial_marks_stage[FIDUCIAL::position::topright_microscope],
			m_Settings->fiducial_marks_stage[FIDUCIAL::position::bottomleft_microscope]);
			
	}
	else
		emit LOGCONSOLE("please ensure that fiducial marks correctly registered", CONSOLECOLOURS::Information);
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
	m_Settings->distance = value;
}

void SettingsDialog::on_distanceBinsThreshold_valueChanged
(int value)
{
	m_Settings->distanceBins = value;
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
	m_Settings->cluster = value;
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
	m_Settings->threshold_max = value;

	if (m_Settings->ThresholdType == thresholdType::Range)
	{
		if (value <= m_Settings->threshold_min)
		{
			ui->ThresholdMinSlider->setValue(value - 1);
			ui->ThresholdMinLbl->setText(QString::number(value - 1));
		}
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
	m_Settings->threshold_min = value;

	if (m_Settings->ThresholdType == thresholdType::Range)
	{
		if (value >= m_Settings->threshold_max)
		{
			ui->ThresholdMaxSlider->setValue(value + 1);
			ui->ThresholdMaxLbl->setText(QString::number(value + 1));
		}
	}
}

void SettingsDialog::on_btnProjectDirectory_clicked(bool checked)
{
	QFileDialog dialog;
	QString directory = dialog.getExistingDirectory(this, tr("Select Project Directory"), QDir::currentPath(), QFileDialog::DontUseNativeDialog);

	/* // should be in dialog close 
	QDir dir(directory);

	// create if not existing
	if (!dir.exists()) {
		dir.mkpath(".");
	}
	*/
	if (!directory.isEmpty()) {
		if (directory.right(1) != "/")
			directory += "/";
		
		m_Settings->s_project_Directory = directory;

		ui->editProjectDirectoryName->setText(directory);
	}
}

void SettingsDialog::on_spnTopLeft_Overview_X_valueChanged(double value) {	m_Settings->fiducial_marks_image[FIDUCIAL::position::topleft_overview].setX(value); checkFiducialsOrder();}
void SettingsDialog::on_spnTopLeft_Overview_Y_valueChanged(double value) { m_Settings->fiducial_marks_image[FIDUCIAL::position::topleft_overview].setY(value);  checkFiducialsOrder();}

void SettingsDialog::on_spnTopRight_Overview_X_valueChanged(double value) { m_Settings->fiducial_marks_image[FIDUCIAL::position::topright_overview].setX(value);  checkFiducialsOrder();}
void SettingsDialog::on_spnTopRight_Overview_Y_valueChanged(double value) { m_Settings->fiducial_marks_image[FIDUCIAL::position::topright_overview].setY(value);  checkFiducialsOrder();}

void SettingsDialog::on_spnBottomLeft_Overview_X_valueChanged(double value) { m_Settings->fiducial_marks_image[FIDUCIAL::position::bottomleft_overview].setX(value);  checkFiducialsOrder();}
void SettingsDialog::on_spnBottomLeft_Overview_Y_valueChanged(double value) { m_Settings->fiducial_marks_image[FIDUCIAL::position::bottomleft_overview].setY(value);  checkFiducialsOrder();}

void SettingsDialog::on_spnBottomRight_Overview_X_valueChanged(double value) { m_Settings->fiducial_marks_image[FIDUCIAL::position::bottomright_overview].setX(value);  checkFiducialsOrder();}
void SettingsDialog::on_spnBottomRight_Overview_Y_valueChanged(double value) { m_Settings->fiducial_marks_image[FIDUCIAL::position::bottomright_overview].setY(value);  checkFiducialsOrder();}

void SettingsDialog::on_spnTopLeft_Overview_Stage_X_valueChanged(double value)
{

	m_Settings->fiducial_marks_stage[FIDUCIAL::position::topleft_overview].setX(value);
	m_Settings->fiducial_marks_stage[FIDUCIAL::position::topright_overview].setX(value);
	m_Settings->fiducial_marks_stage[FIDUCIAL::position::bottomleft_overview].setX(value);
	m_Settings->fiducial_marks_stage[FIDUCIAL::position::bottomright_overview].setX(value); 
	checkFiducialsOrder();
}
void SettingsDialog::on_spnTopLeft_Overview_Stage_Y_valueChanged(double value)
{
	m_Settings->fiducial_marks_stage[FIDUCIAL::position::topleft_overview].setY(value);
	m_Settings->fiducial_marks_stage[FIDUCIAL::position::topright_overview].setY(value);
	m_Settings->fiducial_marks_stage[FIDUCIAL::position::bottomleft_overview].setY(value);
	m_Settings->fiducial_marks_stage[FIDUCIAL::position::bottomright_overview].setY(value);
	checkFiducialsOrder();
}

void SettingsDialog::on_spnTopLeft_Microscope_X_valueChanged(double value){ m_Settings->fiducial_marks_image[FIDUCIAL::position::topleft_microscope].setX(value); }
void SettingsDialog::on_spnTopLeft_Microscope_Y_valueChanged(double value){ m_Settings->fiducial_marks_image[FIDUCIAL::position::topleft_microscope].setY(value); }
void SettingsDialog::on_spnTopLeft_Microscope_Stage_X_valueChanged(double value){ m_Settings->fiducial_marks_stage[FIDUCIAL::position::topleft_microscope].setX(value); checkFiducialsOrder();}
void SettingsDialog::on_spnTopLeft_Microscope_Stage_Y_valueChanged(double value){ m_Settings->fiducial_marks_stage[FIDUCIAL::position::topleft_microscope].setY(value); checkFiducialsOrder();}
void SettingsDialog::on_spnTopLeft_Microscope_Stage_Z_valueChanged(double value){ m_Settings->fiducial_marks_stage[FIDUCIAL::position::topleft_microscope].setZ(value);}

void SettingsDialog::on_spnTopRight_Microscope_X_valueChanged(double value){ m_Settings->fiducial_marks_image[FIDUCIAL::position::topright_microscope].setX(value); }
void SettingsDialog::on_spnTopRight_Microscope_Y_valueChanged(double value){ m_Settings->fiducial_marks_image[FIDUCIAL::position::topright_microscope].setY(value); }
void SettingsDialog::on_spnTopRight_Microscope_Stage_X_valueChanged(double value){ m_Settings->fiducial_marks_stage[FIDUCIAL::position::topright_microscope].setX(value); checkFiducialsOrder();}
void SettingsDialog::on_spnTopRight_Microscope_Stage_Y_valueChanged(double value){ m_Settings->fiducial_marks_stage[FIDUCIAL::position::topright_microscope].setY(value); checkFiducialsOrder();}
void SettingsDialog::on_spnTopRight_Microscope_Stage_Z_valueChanged(double value){ m_Settings->fiducial_marks_stage[FIDUCIAL::position::topright_microscope].setZ(value);}

void SettingsDialog::on_spnBottomLeft_Microscope_X_valueChanged(double value){ m_Settings->fiducial_marks_image[FIDUCIAL::position::bottomleft_microscope].setX(value); }
void SettingsDialog::on_spnBottomLeft_Microscope_Y_valueChanged(double value){ m_Settings->fiducial_marks_image[FIDUCIAL::position::bottomleft_microscope].setY(value); }
void SettingsDialog::on_spnBottomLeft_Microscope_Stage_X_valueChanged(double value){ m_Settings->fiducial_marks_stage[FIDUCIAL::position::bottomleft_microscope].setX(value); checkFiducialsOrder();}
void SettingsDialog::on_spnBottomLeft_Microscope_Stage_Y_valueChanged(double value){ m_Settings->fiducial_marks_stage[FIDUCIAL::position::bottomleft_microscope].setY(value); checkFiducialsOrder();}
void SettingsDialog::on_spnBottomLeft_Microscope_Stage_Z_valueChanged(double value){ m_Settings->fiducial_marks_stage[FIDUCIAL::position::bottomleft_microscope].setZ(value); }

void SettingsDialog::on_spnBottomRight_Microscope_X_valueChanged(double value){ m_Settings->fiducial_marks_image[FIDUCIAL::position::bottomright_microscope].setX(value); }
void SettingsDialog::on_spnBottomRight_Microscope_Y_valueChanged(double value){ m_Settings->fiducial_marks_image[FIDUCIAL::position::bottomright_microscope].setY(value); }
void SettingsDialog::on_spnBottomRight_Microscope_Stage_X_valueChanged(double value){ m_Settings->fiducial_marks_stage[FIDUCIAL::position::bottomright_microscope].setX(value); checkFiducialsOrder();}
void SettingsDialog::on_spnBottomRight_Microscope_Stage_Y_valueChanged(double value){ m_Settings->fiducial_marks_stage[FIDUCIAL::position::bottomright_microscope].setY(value); checkFiducialsOrder();}
void SettingsDialog::on_spnBottomRight_Microscope_Stage_Z_valueChanged(double value){ m_Settings->fiducial_marks_stage[FIDUCIAL::position::bottomright_microscope].setZ(value); }

void SettingsDialog::on_cboSamplingType_currentIndexChanged(int index)
{
	m_Settings->samplingType = static_cast<SAMPLINGTYPE::type>(index);

	DBOUT(ALGOSTRINGS(index) << std::endl);
}

void SettingsDialog::on_cboThresholdType_currentIndexChanged(int index)
{
	m_Settings->ThresholdType = static_cast<thresholdType::thresholdType>(index);

	if (m_Settings->ThresholdType == thresholdType::adaptive)
	{
		ui->labelThresholdMin->setText("Adaptive Region Size");
		ui->labelThresholdMax->setText("Adaptive Region Offset");

		ui->ThresholdMinSlider->setEnabled(true);
		ui->ThresholdMaxSlider->setEnabled(true);
	}
	else if (m_Settings->ThresholdType == thresholdType::Range)
	{
		ui->labelThresholdMin->setText("Threshold Min");
		ui->labelThresholdMax->setText("Threshold Max");

		ui->ThresholdMinSlider->setEnabled(true);
		ui->ThresholdMaxSlider->setEnabled(true);
	}
	else
	{
		ui->ThresholdMinSlider->setEnabled(false);
		ui->ThresholdMaxSlider->setEnabled(false);
	}

	DBOUT(ALGOSTRINGS(index) << std::endl);
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
	m_Settings->NoClustersThreshold = value;
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
	m_Settings->ScoreThreshold = value;
}


/**
*
*  slot for ui->scoreRegionArea changed
*
* @author    David Watts
* @since     2017/04/12
*
* FullName   SettingsDialog::on_scoreRegionArea_valueChanged
* Qualifier
* @param     int value
* @return    void
* Access     private
*/
void SettingsDialog::on_scoreRegionArea_valueChanged(int value)
{
	m_Settings->scoreAreaFactor = value;
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
	m_Settings->algorithmType = static_cast<algoType::algoType>(index);

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
	m_Settings->autoThreshold = checked;

	ui->ThresholdMinSlider->setEnabled(!m_Settings->autoThreshold);
	ui->ThresholdMaxSlider->setEnabled(!m_Settings->autoThreshold);
}

void SettingsDialog::on_chkCV_CALIB_CB_ADAPTIVE_THRESH_clicked(bool checked)
{
	m_Settings->bCV_CALIB_CB_ADAPTIVE_THRESH = checked;
}

void SettingsDialog::on_cboCalibrateAlgorithm_currentIndexChanged(int value)
{
	m_Settings->CalibrateAlgorithm = (calibrateAlgoType::algoType)value;
}

void SettingsDialog::on_cboActiveCamera_currentIndexChanged(int value)
{
	m_Settings->activeCamera = (cameraType::camera)value;
}

void SettingsDialog::on_chkCV_CALIB_CB_NORMALIZE_IMAGE_clicked(bool checked)
{
	m_Settings->bCV_CALIB_CB_NORMALIZE_IMAGE = checked;
}

void SettingsDialog::on_chkOptimiseFocusRange_clicked(bool checked)
{
	m_Settings->m_bOptimiseFocusRange = checked;
}
void SettingsDialog::on_chkInterpolateFocusPosition_clicked(bool checked)
{
	m_Settings->m_bInterpolateFocusPosition = checked;
}
void SettingsDialog::on_chkUseFocusThreshold_clicked(bool checked)
{
	m_Settings->m_bUseFocusThreshold = checked;
}
void SettingsDialog::on_chkUseCoarseFocusRange_clicked(bool checked)
{
	m_Settings->m_bUseCoarseFocusRange = checked;
}
void SettingsDialog::on_chkUseFineFocusRange_clicked(bool checked)
{
	m_Settings->m_bUseFineFocusRange = checked;
}
void SettingsDialog::on_chkCenterFocus_clicked(bool checked)
{
	m_Settings->m_bCenterFocus = checked;
}
void SettingsDialog::on_chkUseRegisteredFocusPoints_clicked(bool checked)
{
	m_Settings->m_bUseRegisteredFocusPoints = checked;
}
void SettingsDialog::on_chkShowBestFocusImage_clicked(bool checked)
{
	m_Settings->m_bShowBestFocusImage = checked;
}

void SettingsDialog::on_chkDetectTargetsWhileScanning_clicked(bool checked)
{
	m_Settings->m_bDetectTargetsWhileScanning = checked;
}

void SettingsDialog::on_chkCorrectBackGround_clicked(bool checked)
{
	m_Settings->bCorrectBackGround = checked;
}

void SettingsDialog::on_chkCV_CALIB_CB_FILTER_QUADS_clicked(bool checked)
{
	m_Settings->bCV_CALIB_CB_FILTER_QUADS = checked;
}

void SettingsDialog::on_chkCALIB_CB_FAST_CHECK_clicked(bool checked)
{
	m_Settings->bCALIB_CB_FAST_CHECK = checked;
}

void SettingsDialog::on_chkCALIB_CB_CLUSTERING_clicked(bool checked)
{
	m_Settings->bCALIB_CB_CLUSTERING = checked;
}
void SettingsDialog::on_chkFixedAspect_clicked(bool checked)
{
	m_Settings->FixedAspect = checked;
}
void SettingsDialog::on_chkZeroDistortion_clicked(bool checked)
{
	m_Settings->ZeroDistortion = checked;
}
void SettingsDialog::on_chkFixPrincipalPointCenter_clicked(bool checked)
{
	m_Settings->FixPrincipalPointCenter = checked;
}

void SettingsDialog::on_chkIntrinsicGuess_clicked(bool checked)
{
	m_Settings->UseIntrinsicGuess = checked;
}

void SettingsDialog::on_chkFixFocalLength_clicked(bool checked)
{
	m_Settings->FixFocalLength = checked;
}

void SettingsDialog::on_chkProcessGrayscale_clicked(bool checked)
{
	m_Settings->bProcessGrayscale = checked;
}

void SettingsDialog::on_spinItemsInRow_valueChanged(int value)
{
	m_Settings->calibrateNoRows = value;
}
void SettingsDialog::on_spinItemsInColumn_valueChanged(int value)
{
	m_Settings->calibrateNoCols = value;
}
void SettingsDialog::on_spinSizeSquare_valueChanged(int value)
{
	m_Settings->SizeOfSquare = value;
}

void SettingsDialog::on_spinXPositionAbsoluteXY_valueChanged(double value)
{
	m_Settings->XPositionAbsoluteXY = value;
}

void SettingsDialog::on_spinYPositionAbsoluteXY_valueChanged(double value)
{
	m_Settings->YPositionAbsoluteXY = value;
}
void SettingsDialog::on_spinPositionAbsoluteZ_valueChanged(double value)
{
	m_Settings->PositionAbsoluteZ = value;
}

void SettingsDialog::on_spinPositionRelativeZ_valueChanged(double value)
{
	m_Settings->PositionRelativeZ = value;
}

void SettingsDialog::on_spinXPositionRelativeXY_valueChanged(double value)
{
	m_Settings->XPositionRelativeXY = value;
}

void SettingsDialog::on_spinYPositionRelativeXY_valueChanged(double value)
{
	m_Settings->YPositionRelativeXY = value;
}
void SettingsDialog::on_spinVelocityXY_valueChanged(double value)
{
	m_Settings->VelocityXY = value;
}

void SettingsDialog::on_spinDefaultFocusPosition_valueChanged(double value)
{
	m_Settings->m_DefaultFocusPosition = value;
}
void SettingsDialog::on_spinFocusRange_valueChanged(double value)
{
	m_Settings->m_FocusRange = value;
}
void SettingsDialog::on_spinFocusFraction_valueChanged(double value)
{
	m_Settings->m_FocusThresholdFraction = value;
}
void SettingsDialog::on_spinCoarseFocusStep_valueChanged(double value)
{
	m_Settings->m_CoarseFocusStep = value;
}
void SettingsDialog::on_spinFineFocusStep_valueChanged(double value)
{
	m_Settings->m_FineFocusStep = value;
}

void SettingsDialog::on_spinWaveletLevels_valueChanged(int value)
{
	m_Settings->numWaveletLevels = value;
	emit updatePaddTarget(m_Settings->bPaddTargetImage, m_Settings->numWaveletLevels);
}

void SettingsDialog::on_btnMoveAbsoluteXY_clicked()
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	emit MoveAbsoluteXY(m_Settings->XPositionAbsoluteXY, m_Settings->YPositionAbsoluteXY, ACTIONS::action::nothing);
}

void SettingsDialog::on_btnMoveRelativeXY_clicked()
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	emit MoveRelativeXY(m_Settings->XPositionRelativeXY, m_Settings->YPositionRelativeXY, ACTIONS::action::nothing);
}

void SettingsDialog::on_btnMoveAbsoluteZ_clicked()
{
	emit MoveAbsoluteZ(m_Settings->PositionAbsoluteZ, ACTIONS::action::nothing);
}

void SettingsDialog::on_btnMoveRelativeZ_clicked()
{
	emit MoveRelativeZ(m_Settings->PositionRelativeZ, ACTIONS::action::nothing);
}

void SettingsDialog::on_btnUpZ_pressed()
{
	emit MoveAbsoluteZ(12.5, ACTIONS::action::jog);
}

void SettingsDialog::on_btnDownZ_pressed()
{
	emit MoveAbsoluteZ(-12.5, ACTIONS::action::jog);
}

void SettingsDialog::on_btnUpZ_released()
{
	emit stopMotionZ(ACTIONS::action::jog);
}

void SettingsDialog::on_btnDownZ_released()
{
	emit stopMotionZ(ACTIONS::action::jog);
}

void SettingsDialog::on_btnSendCommandZ_clicked()
{
	m_Settings->s_CommandTextZ = ui->editSendCommandZ->text();
	emit SendCommandZ(m_Settings->s_CommandTextZ);
}
void SettingsDialog::on_btnConnectZ_clicked(){
	emit ConnectZ();
}
void SettingsDialog::on_btnDisconnectZ_clicked(){
	emit DisconnectZ();
}

void SettingsDialog::on_btnAddFocusPosition_clicked()
{
	QVector3D pos = QVector3D(m_Settings->m_stage_position_XY_X, m_Settings->m_stage_position_XY_Y, m_Settings->m_stage_position_Z);

	m_Settings->focusPoints.append(pos);

	// optimise focus range based on values

	if(m_Settings->focusPoints.size()==1)
	{
		m_Settings->m_DefaultFocusPosition = m_Settings->focusPoints.at(0).z();
		ui->spinDefaultFocusPosition->setValue(m_Settings->focusPoints.at(0).z());
	}
	else if(m_Settings->focusPoints.size()>1)
	{
		double maxZ = m_Settings->focusPoints.at(0).z();
		double minZ = maxZ;

		for (int i = 1; i < m_Settings->focusPoints.size(); i++)
		{
			if(m_Settings->focusPoints.at(i).z() > maxZ)
				maxZ = m_Settings->focusPoints.at(i).z();
			if (m_Settings->focusPoints.at(i).z() < minZ)
				minZ = m_Settings->focusPoints.at(i).z();
		}
		ui->spinFocusRange->setValue(maxZ-minZ);

		m_Settings->m_FocusRange = maxZ - minZ;
	}

	ui->cboFocusPosition->addItem("{x: " + QString::number(pos.x()) + ", y: " + QString::number(pos.y()) + ", z: " + QString::number(pos.z()) + "}");
}

void SettingsDialog::on_btnRemoveFocusPosition_clicked()
{
	m_Settings->focusPoints.removeAt(ui->cboFocusPosition->currentIndex());
	ui->cboFocusPosition->removeItem(ui->cboFocusPosition->currentIndex());
}

void SettingsDialog::updateCONNECTPORT(bool XY, QString port)
{
	if (XY)
		ui->lblPORTXY->setText(port);
	else
		ui->lblPORTZ->setText(port);
}

void SettingsDialog::updatePositions()
{
	ui->lbl_positionXY_X->setText(QString::number(m_Settings->m_stage_position_XY_X));
	ui->lbl_positionXY_Y->setText(QString::number(m_Settings->m_stage_position_XY_Y));
	
	// update z position
	//m_Settings->m_stage_position_XY_Z
	
}

void SettingsDialog::updatePosition()
{
	ui->lbl_positionZ->setText(QString::number(m_Settings->m_stage_position_Z));
}

void SettingsDialog::updateCOMPORTS(QVector<QString> strs)
{
	ui->cboCOMPORTS->clear();

	for each (QString var in strs)
	{
		ui->cboCOMPORTS->addItem(var);
	}
	
}

void SettingsDialog::on_chkJoystickOn_clicked(bool on)
{
	if(on)
		ui->XYStageFrame->setEnabled(false);
	else
		ui->XYStageFrame->setEnabled(true);

	ui->chkJoystickOn->setEnabled(true);
	
	emit SetJoystickXY(on);
}

void SettingsDialog::on_chkKeypadOn_clicked(bool on)
{
	if (on)
		ui->ZStageFrame->setEnabled(false);
	else
		ui->ZStageFrame->setEnabled(true);

	ui->chkKeypadOn->setEnabled(true);

	emit SetKeypadZ(on);
}

void SettingsDialog::on_btnSendCommandXY_clicked()
{
	m_Settings->s_CommandTextXY = ui->editSendCommandXY->text();
	emit SendCommandXY(m_Settings->s_CommandTextXY);
}

void SettingsDialog::on_btnSetVelocityXY_clicked()
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	emit SetVelocityXY(m_Settings->VelocityXY);
}

void SettingsDialog::on_btnCalibrateXY_clicked()
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	emit CalibrateXY();
}

void SettingsDialog::on_btnAbortXY_clicked()
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	emit AbortXY();
}

void SettingsDialog::on_btnMeasureRangeXY_clicked()
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	emit MeasureRangeXY();
	
}

void SettingsDialog::on_btnConnectXY_clicked()
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	emit ConnectXY();
	
}

void SettingsDialog::on_btnDisconnectXY_clicked()
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	emit DisconnectXY();
}

void SettingsDialog::on_btnMoveOverviewPosition_clicked()
{
	// move to bottom left for overview image
	emit MoveAbsoluteXY(0, 155, ACTIONS::action::nothing);
}

void SettingsDialog::on_cboBaudXY_currentIndexChanged(int value)
{
	m_Settings->BaudXY = ui->cboBaudXY->itemData(value).toInt();
}

void SettingsDialog::on_cboFocusAlgorithm_currentIndexChanged(int value)
{
	m_Settings->FocusAlgorithm = (FOCUSALGO::algo) value;
}


void SettingsDialog::on_huMomentSimilaritySlider_valueChanged(int value)
{
	m_Settings->huMomentSimilarity = value;
}

void SettingsDialog::on_spinAspectTolerance_valueChanged(double value)
{
	m_Settings->AspectTolerance = value;
}

void SettingsDialog::on_sliderGridOffsetX_valueChanged(int value){
	m_Settings->gridOffsetX = value;
	ui->spinGridOffsetX->setValue((double)value);
	emit updateGrid();
}

void SettingsDialog::on_sliderGridOffsetY_valueChanged(int value){
	m_Settings->gridOffsetY = value;
	ui->spinGridOffsetY->setValue((double)value);
	emit updateGrid();
}

void SettingsDialog::on_sliderGridSpacingX_valueChanged(int value){
	m_Settings->gridSpacingX = value;
	ui->spinGridSpacingX->setValue((double)value);
	emit updateGrid();
}
void SettingsDialog::on_sliderGridSpacingY_valueChanged(int value){
	m_Settings->gridSpacingY = value;
	ui->spinGridSpacingY->setValue((double)value);
	emit updateGrid();
}

void SettingsDialog::on_spinGridOffsetX_valueChanged(double value)
{
	m_Settings->gridOffsetX = value;
	ui->sliderGridOffsetX->setValue((int)value);
	emit updateGrid();
}

void SettingsDialog::on_spinGridOffsetY_valueChanged(double value)
{
	m_Settings->gridOffsetY = value;
	ui->sliderGridOffsetY->setValue((int)value);
	emit updateGrid();
}

void SettingsDialog::on_spinGridSpacingX_valueChanged(double value)
{
	m_Settings->gridSpacingX = value;
	ui->sliderGridSpacingX->setValue((int)value);
	emit updateGrid();
}

void SettingsDialog::on_spinGridSpacingY_valueChanged(double value)
{
	m_Settings->gridSpacingY = value;
	ui->sliderGridSpacingY->setValue((int)value);
	emit updateGrid();
}

void SettingsDialog::on_sliderBarcodeThreshold_valueChanged(int value)
{
	m_Settings->BarcodeThreshold = value;
}

void SettingsDialog::on_chkAutoBarcodeThreshold_clicked(bool checked)
{
	m_Settings->BarcodeAutoThreshold = checked;
}

void SettingsDialog::on_spinSamplingDistanceX_valueChanged(int value)
{
	m_Settings->samplingSpacing.setX(value);
}

void SettingsDialog::on_spinSamplingDistanceY_valueChanged(int value)
{
	m_Settings->samplingSpacing.setY(value);
}

void SettingsDialog::on_spinSamplingOffsetX_valueChanged(int value)
{
	m_Settings->samplingOffset.setX(value);
}

void SettingsDialog::on_spinSamplingOffsetY_valueChanged(int value)
{
	m_Settings->samplingOffset.setY(value);
}

void SettingsDialog::updateSamplingSpacing()
{
	ui->spinSamplingDistanceX->setValue(m_Settings->samplingSpacing.x());
	ui->spinSamplingOffsetX->setValue(m_Settings->samplingOffset.x());
	ui->spinSamplingDistanceY->setValue(m_Settings->samplingSpacing.y());
	ui->spinSamplingOffsetY->setValue(m_Settings->samplingOffset.y());
}

void SettingsDialog::on_spMicroscopeLensFocalLength_valueChanged(int value)
{
	m_Settings->focalDistanceMicroscopeCamera = value;
}

void SettingsDialog::on_spOverviewLensFocalLength_valueChanged(int value)
{
	m_Settings->focalDistanceOverviewCamera = value;
}

void SettingsDialog::on_chkDisplayGrid_clicked(bool value)
{
	m_Settings->displayGrid = value;
}

void SettingsDialog::on_btnSelectColour_clicked()
{
	QColor anotationcolor = QColorDialog::getColor(Qt::red, this);

	if (anotationcolor.isValid())
	{
		m_Settings->objectColours[ui->cboAnnotationColour->currentIndex()] = anotationcolor;

		ui->cboAnnotationColour->setItemData(ui->cboAnnotationColour->currentIndex(), QBrush(anotationcolor), Qt::TextColorRole);
	}
}

void SettingsDialog::on_btnLogFeedback_clicked()
{
	QString desc = ui->editFeedbackDescription->toPlainText();
	QString email = ui->editFeedbackEmail->text();
	QString institute = ui->editFeedbackInstitute->text();
	QString name = ui->editFeedbackName->text();
	int score = ui->sliderFeedbackSatisfaction->value();

	emit logFeedback(score, name, email, institute, desc);
}

void SettingsDialog::on_editName_textChanged(QString val) {
	m_Settings->s_project_Username = val;
};
void SettingsDialog::on_editInstitute_textChanged(QString val) {
	m_Settings->s_project_Institute = val;
};
void SettingsDialog::on_editProjectName_textChanged(QString val) {
	m_Settings->s_project_Name = val;
};
void SettingsDialog::on_editProjectID_textChanged(QString val) {
	m_Settings->s_project_ID = val;
};
void SettingsDialog::on_editVersion_textChanged(QString val) {
	m_Settings->s_project_Version = val;
};
void SettingsDialog::on_editDescription_textChanged(QString val) {
	m_Settings->s_project_Description = val;
};
void SettingsDialog::on_editSampleDescription_textChanged(QString val) {
	m_Settings->s_project_SampleDescription = val;
};
void SettingsDialog::on_editFilenamePrefix_textChanged(QString val) {
	m_Settings->s_project_FilenamePrefix = val;
};
void SettingsDialog::on_editBarcode_textChanged(QString val) {
	m_Settings->s_project_Barcode = val;
};
void SettingsDialog::on_projectDate_dateChanged(QDate date) {
	m_Settings->d_project_Date = date;
};
void SettingsDialog::on_editProjectDirectoryName_textChanged(QString val) {
	m_Settings->s_project_Directory = val;
};

void SettingsDialog::on_lineEditOverviewCameraSN_textChanged(QString val) {
	m_Settings->overviewCameraSN = atoi(val.toLocal8Bit().data());
};
void SettingsDialog::on_lineEditMicroscopeCameraSN_textChanged(QString val) {
	m_Settings->microscopeCameraSN = atoi(val.toLocal8Bit().data());
};

void SettingsDialog::on_btnRestoreBackup_clicked()
{
	emit saveBackup(true);
}
void SettingsDialog::on_btnSaveBackup_clicked()
{
	emit saveBackup(false);
}

void SettingsDialog::on_editPixelSizeMicrons_textChanged(QString val){
	m_Settings->mmPerPixel = val.replace(",", ".").toDouble();
}