#include "myserver.h"

MyServer::MyServer(QObject *parent) :
    QTcpServer(parent)
{

}

void MyServer::StartServer(MyPinas *window){
    this->window = window;
    if(!this->listen(QHostAddress::AnyIPv4, 2319)){
        qDebug() << "could not start server";
    }else{
        qDebug() << "Listening...";
    }
}

void MyServer::incomingConnection(int socketDescriptor){
    qDebug() << socketDescriptor << "Connecting...";

    MyThread *thread = new MyThread(socketDescriptor, &clientsThreads, this);
    //clientsThreads << thread;

    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->window = window;
    thread->acceptClient();
}

void MyServer::blockPC(int indexOfPC){
    qDebug() << "blockingPCinServer";
    MyThread *thread = clientsThreads.at(indexOfPC);
    thread->sendData("block");
}

void MyServer::unblockPC(int indexOfPC) {
    qDebug() << "unBlockingPCinServer";
    MyThread *thread = clientsThreads.at(indexOfPC);
    thread->sendData("unblock");
}
void MyServer::unblockPC(int indexOfPC, QByteArray time) {
    qDebug() << "unBlockingPCinServerWithTimer";
    MyThread *thread = clientsThreads.at(indexOfPC);
    thread->sendData(time);
}

