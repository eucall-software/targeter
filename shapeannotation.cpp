#include "shapeannotation.h"
#include "ui_shapeannotation.h"

ShapeAnnotation::ShapeAnnotation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShapeAnnotation)
{
    ui->setupUi(this);
}

void ShapeAnnotation::setValues(QString ID, QString name, QString desc, shapeAnnotationType::Type typ)
{
	this->ID = ID;
	this->name = name;
	this->typ = typ;
	this->desc = desc;

	ui->editRegionName->setText(name);
	ui->editRegionDescription->setText(desc);
	ui->editRegionID->setText(ID);

	int index = (shapeAnnotationType::Type)typ;

	ui->cboRegionType->clear();

	for (int i = 0; i <= shapeAnnotationType::none; i++)
		ui->cboRegionType->addItem(SHAPEANNOTATIONSTRINGS(i));

	ui->cboRegionType->setCurrentIndex(index);
}

ShapeAnnotation::~ShapeAnnotation()
{
    delete ui;
}

void ShapeAnnotation::on_editRegionName_textChanged(const QString &arg1)
{
	name = arg1;
}

void ShapeAnnotation::on_editRegionID_textChanged(const QString &arg1)
{
	ID = arg1;
}

void ShapeAnnotation::on_editRegionDescription_textChanged(const QString &arg1)
{
	desc = arg1;
}

void ShapeAnnotation::on_cboRegionType_currentIndexChanged(int index)
{
	typ = (shapeAnnotationType::Type)index;
}

void ShapeAnnotation::on_buttonBox_accepted()
{
	ID = ui->editRegionID->text();
	name = ui->editRegionName->text();
	desc = ui->editRegionDescription->text();

	int index = ui->cboRegionType->currentIndex();
	typ = (shapeAnnotationType::Type)index;
}

void ShapeAnnotation::GetValues(QString& ID, QString& name, QString& desc, shapeAnnotationType::Type& typ)
{
	ID = this->ID;
	name = this->name;
	desc = this->desc;
	typ = this->typ;
}