#include "pc_form.h"
#include "ui_pc_form.h"
#include "mypinas.h"

PC_Form::PC_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PC_Form)
{
    ui->setupUi(this);
}

PC_Form::~PC_Form()
{
    delete ui;
}

void PC_Form::setParams(QString name, QString ip, QString time){

    ui->PCbox->setTitle(name);
    ui->IP_Label->setText(ip);
    ui->TimerLabel->setText(time);
}
void PC_Form::setTime(QString time){
    ui->TimerLabel->setText(time);
}

void PC_Form::on_PCbox_clicked()
{
    MyPinas *mp = (MyPinas*)parent();
    mp->changeLP(ui->PCbox->title(), ui->IP_Label->text(), ui->TimerLabel->text());
}

void PC_Form::on_StatusLabel_clicked()
{
    on_PCbox_clicked();
}
