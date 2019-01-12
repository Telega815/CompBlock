#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include <QDebug>
#include <QTime>


MainWindow::MainWindow(QWidget *parent, Settings *set) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window
    | Qt::WindowMinimizeButtonHint);
    alertDialog = new AlertDialog(0, set);
    if (set != 0 && set->settingsReaded) {
        ui->label->setText(set->getOption("PC_will_be_blocked"));
    }
}
//TODO disconected
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeTime(QString time){
    if (alertDialog->isVisible()) {
        alertDialog->setTime(time);
    }
    ui->timer->setText(time);
    ui->timer->update();
    if (QString::compare("00:05:00", time, Qt::CaseInsensitive) == 0){
        //this->setWindowState(Qt::WindowMaximized);
        alertDialog->setTime(time);
        alertDialog->open();
    }
    if (QString::compare("00:01:00", time, Qt::CaseInsensitive) == 0){
        //this->setWindowState(Qt::WindowMaximized);
        alertDialog->setTime(time);
        alertDialog->open();
    }
}

void MainWindow::on_Pwd_returnPressed()
{
    if (QString::compare("563453sei", ui->Pwd->text(), Qt::CaseSensitive) == 0)
        emit this->correctPWD();
    else
        emit this->incorrectPWD();
}
