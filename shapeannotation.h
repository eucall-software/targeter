#ifndef SHAPEANNOTATION_H
#define SHAPEANNOTATION_H

#include <QDialog>
#include "globals.h"

namespace Ui {
class ShapeAnnotation;
}

class ShapeAnnotation : public QDialog
{
    Q_OBJECT

public:
    explicit ShapeAnnotation(QWidget *parent = 0);
	void setValues(QString ID, QString name, QString desc, shapeAnnotationType::Type typ);
    ~ShapeAnnotation();

	void GetValues(QString& ID, QString& name, QString& desc, shapeAnnotationType::Type& typ);

private:
	QString ID; 
	QString name; 
	QString desc; 
	shapeAnnotationType::Type typ;

private slots:
        void on_editRegionName_textChanged(const QString &arg1);

        void on_editRegionID_textChanged(const QString &arg1);

        void on_editRegionDescription_textChanged(const QString &arg1);

        void on_cboRegionType_currentIndexChanged(int index);

        void on_buttonBox_accepted();

private:
    Ui::ShapeAnnotation *ui;
};

#endif // SHAPEANNOTATION_H
