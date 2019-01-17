#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QSystemTrayIcon>
#include "deskblockthread.h"
#include "QTimer"
#include "settings.h"
#include "alertdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, Settings *set = 0);
    ~MainWindow();
    void changeTime(QString time);
private slots:
    void on_Pwd_returnPressed();

    void changeEvent(QEvent* event);
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void trayActionExecute();
    void setTrayIconActions();
    void showTrayIcon();

private:
    AlertDialog *alertDialog;
    Ui::MainWindow *ui;

    QMenu *trayIconMenu;
    QAction *minimizeAction;
    QAction *restoreAction;
    QAction *quitAction;
    QSystemTrayIcon *trayIcon;
signals:
    void correctPWD();
    void incorrectPWD();

};

#endif // MAINWINDOW_H
