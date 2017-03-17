#include "mergesettingsdialog.h"
#include "ui_mergesettingsdialog.h"

MergeSettingsDialog::MergeSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MergeSettingsDialog)
{
    ui->setupUi(this);
}

MergeSettingsDialog::~MergeSettingsDialog()
{
    delete ui;
}
