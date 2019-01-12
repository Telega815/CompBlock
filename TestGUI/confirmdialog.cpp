#include "confirmdialog.h"
#include "ui_confirmdialog.h"

ConfirmDialog::ConfirmDialog(QWidget *parent, Settings *settings) :
    QDialog(parent),
    ui(new Ui::ConfirmDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window
    | Qt::WindowMinimizeButtonHint);
    if (settings != 0 && settings->settingsReaded) {
        ui->LP_TimerBox_AfterLabel->setText(settings->getOption("After change:"));
    }

}

ConfirmDialog::~ConfirmDialog()
{
    delete ui;
}

void ConfirmDialog::changeTime()
{
    QTime time = QTime::fromString(ui->LP_TimerBox_TimeLeftLabel->text());
    time = time.addSecs(-1);
    QString newTimeLeft = time.toString(Qt::TextDate);
    ui->LP_TimerBox_TimeLeftLabel->setText(newTimeLeft);
    ui->LP_TimerBox_TimeLeftLabel->update();
}

void ConfirmDialog::setTime(QString time)
{
    ui->LP_TimerBox_TimeLeftLabel->setText(time);
}

QString ConfirmDialog::getTime()
{
    return ui->LP_TimerBox_TimeLeftLabel->text();
}

void ConfirmDialog::on_buttonBox_accepted()
{
    emit applyClick();
}

void ConfirmDialog::on_buttonBox_rejected()
{
    emit cancelClick();
}
