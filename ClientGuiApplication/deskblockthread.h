#ifndef DESKBLOCKTHREAD_H
#define DESKBLOCKTHREAD_H
#include <QtCore>
#include <QDebug>
#include <stdio.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <QMessageBox>
#include <QApplication>

class DeskBlockThread : public QThread
{
    Q_OBJECT
public:
    DeskBlockThread(QObject *parent = 0);
    void run();
    void closeBlockDesk();
    int isBlocked;
private:
    HDESK hOld;
    HDESK hNew;
signals:
    void unblockCorrectPWD();

};

#endif // DESKBLOCKTHREAD_H
