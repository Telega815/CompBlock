#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QHostAddress>
#include "mypinas.h"

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(int ID, QList<MyThread*> *clientsThreads, QObject *parent = 0);
    void run();
    QHostAddress ip;
    qint16 port;
    void sendData(QByteArray data);
    void acceptClient();
    MyPinas *window;
    int boxIndex;
    uint64_t timer;
signals:
    void error(QTcpSocket::SocketError sockedError);

public slots:
    void readyRead();
    void disconected();

private:
    QList<MyThread*> *clientsThreads;
    QTcpSocket *socket;
    int socketDescriptor;
};

#endif // MYTHREAD_H
