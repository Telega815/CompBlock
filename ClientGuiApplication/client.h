#ifndef CLIENT_H
#define CLIENT_H
#include <QtCore>
#include "mainwindow.h"
#include <QTimer>
#include <QTime>
#include <settings.h>

class Client: public QThread
{
public:
    Client(MainWindow *window);
    void run();
    void initializeSocketAndTimers(Settings *set);
    void closeSocketAndDeleteClient();
private slots:
    void blockPcSlot();
    void changeTimeSlot();
    void hostFound();
    void readyRead();
    void disconected();
    void unblockedByPWD();
    void tryToConnect();
private:
    Settings *settings;
    MainWindow *window;
    QTcpSocket *socket;
    int connectedToServer;
    DeskBlockThread *thr;
    const QString serverIP = "192.168.1.150";
    QTimer *qtimerForBlock;
    QTimer *qtimerForView;
    QTimer *qtimerForReconection;
    QTime qtimeLeft;
    void blockPC();
    void unblockPC();
    void setTimersAndStart(QTime time);
    void stopTimers();

};

#endif // CLIENT_H
