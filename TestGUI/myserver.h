#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QDebug>
#include "mythread.h"
#include "mypinas.h"
#include "serverinterface.h"

class MyServer : public QTcpServer, public ServerInterface
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);
    void StartServer(MyPinas *window);
    QList<MyThread*> clientsThreads;
    virtual void blockPC(int indexOfPC) override;
    virtual void unblockPC(int indexOfPC) override;
    virtual void unblockPC(int indexOfPC, QByteArray time) override;

protected:
    void incomingConnection(int socketDescriptor);
    MyPinas *window;
};

#endif // MYSERVER_H
