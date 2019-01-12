#include "mythread.h"

MyThread::MyThread(int ID, QList<MyThread*> *clientsThreads,QObject *parent) :
    QThread(parent)
{
    this->socketDescriptor = ID;
    this->clientsThreads = clientsThreads;
}


void MyThread::run(){
    exec();
}

void MyThread::acceptClient(){
    qDebug() << socketDescriptor << "Starting thread";
    socket = new QTcpSocket();
    if(!socket->setSocketDescriptor(this->socketDescriptor)){
        emit error(socket->error());
        return;
    }

    connect(socket, &QIODevice::readyRead, this, &MyThread::readyRead,Qt::DirectConnection);
    connect(socket, &QAbstractSocket::disconnected, this, &MyThread::disconected,Qt::DirectConnection);

    qDebug() << socketDescriptor << "clientConnected";
    ip = socket->peerAddress();
    port = socket->peerPort();
    QString ipStr = ip.toString();
    int ind = window->checkIP(ipStr);
    if(ind == -1){
        boxIndex = window->addPC(&ipStr);
        clientsThreads->append(this);
    }else{
        boxIndex = ind;
        clientsThreads->removeAt(ind);
        clientsThreads->insert(ind, this);
        window->reconectPC(ind);
    }
    socket->waitForReadyRead(500);
    socket->write("connected");
    socket->waitForBytesWritten(500);
}

void MyThread::readyRead(){
    QByteArray Data = socket->readAll();
    qDebug() << socketDescriptor << " Data in: " << Data;
    if(Data == "blocked"){
        window->setViewStatus(this->boxIndex, 1);
    }else if (Data == "unblocked") {
        window->setViewStatus(this->boxIndex, 0);
    }else {
        window->setViewTime(this->boxIndex, &Data);
    }

}

void MyThread::disconected(){
    qDebug() << socketDescriptor << " Disconected";
    window->removePC(boxIndex);
    this->disconnect();
    socket->deleteLater();
    this->deleteLater();
}

void MyThread::sendData(QByteArray data){
    socket->write(data);
    socket->waitForBytesWritten(500);
}







