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

    this -> setTrayIconActions();
    this -> showTrayIcon();

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
        this->showNormal();
        //alertDialog->setTime(time);
        //alertDialog->open();
    }
    if (QString::compare("00:01:00", time, Qt::CaseInsensitive) == 0){
        //this->setWindowState(Qt::WindowMaximized);
        this->showNormal();
        //alertDialog->setTime(time);
        //alertDialog->open();
    }
}

void MainWindow::on_Pwd_returnPressed()
{
    if (QString::compare("563453sei", ui->Pwd->text(), Qt::CaseSensitive) == 0)
        emit this->correctPWD();
    else
        emit this->incorrectPWD();
}

void MainWindow::changeEvent(QEvent *event)
{
    QMainWindow::changeEvent(event);
        if (event -> type() == QEvent::WindowStateChange)
        {
            if (isMinimized())
            {
                this -> hide();
            }
        }
}

void MainWindow::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
        {
//            case QSystemTrayIcon::Trigger:
//                break;
            case QSystemTrayIcon::DoubleClick:
                this -> trayActionExecute();
                break;
            default:
                break;
    }
}

void MainWindow::trayActionExecute()
{
//    QMessageBox::information(this, "TrayIcon", "Тестовое сообщение. Замените вызов этого сообщения своим кодом.");
    showNormal();
}

void MainWindow::setTrayIconActions()
{
    // Setting actions...
        minimizeAction = new QAction("Свернуть", this);
        restoreAction = new QAction("Восстановить", this);

        // Connecting actions to slots...
        connect (minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));
        connect (restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

        // Setting system tray's icon menu...
        trayIconMenu = new QMenu(this);
        trayIconMenu -> addAction (minimizeAction);
        trayIconMenu -> addAction (restoreAction);
}

void MainWindow::showTrayIcon()
{
    // Создаём экземпляр класса и задаём его свойства...
        trayIcon = new QSystemTrayIcon(this);
        QIcon trayImage(":/images/TrayIcon.png");
        trayIcon -> setIcon(trayImage);
        trayIcon -> setContextMenu(trayIconMenu);

        // Подключаем обработчик клика по иконке...
        connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));

        // Выводим значок...
        trayIcon -> show();
}
