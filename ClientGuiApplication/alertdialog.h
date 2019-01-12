#ifndef ALERTDIALOG_H
#define ALERTDIALOG_H

#include <QDialog>
#include <settings.h>

namespace Ui {
class AlertDialog;
}

class AlertDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AlertDialog(QWidget *parent = 0, Settings *settings = 0);
    ~AlertDialog();
    void setTime(QString time);

private:
    Ui::AlertDialog *ui;
};

#endif // ALERTDIALOG_H
