#include "alertdialog.h"
#include "ui_alertdialog.h"

AlertDialog::AlertDialog(QWidget *parent, Settings *settings) :
    QDialog(parent),
    ui(new Ui::AlertDialog)
{
    ui->setupUi(this);
    if (settings != 0 && settings->settingsReaded) {
        ui->TimeLeftLabel->setText(settings->getOption("Time left:"));
    }

}

AlertDialog::~AlertDialog()
{
    delete ui;
}

void AlertDialog::setTime(QString time)
{
    ui->label_2->setText(time);
}
