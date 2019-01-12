#include "renamedialog.h"
#include "ui_renamedialog.h"

RenameDialog::RenameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RenameDialog)
{
    ui->setupUi(this);
}

RenameDialog::~RenameDialog()
{
    delete ui;
}

void RenameDialog::setLabels(QString ip, QString pcName)
{
    ui->IP_value->setText(ip);
    ui->PcName->setText(pcName);
}

void RenameDialog::on_buttonBox_accepted()
{
    emit rename(ui->PcName->text());
}

void RenameDialog::on_buttonBox_rejected()
{

}
