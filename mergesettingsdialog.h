#ifndef MERGESETTINGSDIALOG_H
#define MERGESETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class MergeSettingsDialog;
}

class MergeSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MergeSettingsDialog(QWidget *parent = 0);
    ~MergeSettingsDialog();

private:
    Ui::MergeSettingsDialog *ui;
};

#endif // MERGESETTINGSDIALOG_H
