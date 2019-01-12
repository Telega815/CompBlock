#ifndef CONFIRMDIALOG_H
#define CONFIRMDIALOG_H

#include <QDialog>
#include <QTime>
#include "settings.h"

namespace Ui {
class ConfirmDialog;
}

class ConfirmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmDialog(QWidget *parent = 0, Settings *settings = 0);
    ~ConfirmDialog();
    void changeTime();
    void setTime(QString time);
    QString getTime();
signals:
    void applyClick();
    void cancelClick();
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ConfirmDialog *ui;
};

#endif // CONFIRMDIALOG_H
