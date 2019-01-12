#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
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

private:
    AlertDialog *alertDialog;
    Ui::MainWindow *ui;
signals:
    void correctPWD();
    void incorrectPWD();

};

#endif // MAINWINDOW_H
