#ifndef MYPINAS_H
#define MYPINAS_H

#include <QMainWindow>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QLinkedList>
#include <QTime>
#include <QTimer>
#include "mygroupbox.h"
#include "serverinterface.h"
#include "settings.h"
#include "confirmdialog.h"
#include "renamedialog.h"
#include "pcnameswriter.h"

namespace Ui {
class MyPinas;
}

class MyPinas : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyPinas(QWidget *parent = 0);
    ~MyPinas();
    int addPC(QString *ip);
    void setViewTime(int clientIndex, QByteArray *time);
    void setViewStatus(int clientIndex, int status);
    void removePC(int clientsCount);
    QList<MyGroupBox*> clients;
    QList<QTimer*> qtimersForTimeChanging;
    void setTimers(int clientIndex, QString *time);
    int selectedPC;
    int clientsCount;
    QString timeBeforeChange = Q_NULLPTR;
    ServerInterface *server;
    int checkIP(QString IP);
    void reconectPC(int index);


public:
    Ui::MyPinas *ui;
    void changeLP(QString name, QString ip, QString time, bool status);
private:
    RenameDialog *renameDialog;
    Settings *set;
    ConfirmDialog *confirmDialog;
    PcNamesWriter * namesWriter;
private slots:
    void changeTime();
    void on_myBtn_clicked();
    void on_LP_TimerBox_SetButton_clicked();
    void on_LP_TimerBox_AddButton_clicked();
    void on_LP_TimerBox_CancelButton_clicked();
    void on_LP_TimerBox_ApplyButton_clicked();
    void on_LP_UnBlockPC_Button_clicked();
    void on_LP_BlockPC_Button_clicked();
    void on_RenameButton_clicked();
    void renamePC(QString name);
};

#endif // MYPINAS_H
