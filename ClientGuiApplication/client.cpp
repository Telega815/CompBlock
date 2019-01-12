#include "client.h"

Client::Client(MainWindow *window)
{
    this->window = window;
}

void Client::run(){


}

void Client::initializeSocketAndTimers(Settings *set)
{
    qtimerForView = new QTimer();
    qtimerForBlock = new QTimer();
    qtimerForReconection = new QTimer();
    qtimeLeft = QTime::fromString("00:00:00");
    qtimerForView->setInterval(1000);
    qtimerForReconection->setInterval(1000);
    connect(qtimerForView, &QTimer::timeout, this, &Client::changeTimeSlot);
    connect(qtimerForBlock, &QTimer::timeout, this, &Client::blockPcSlot);
    connect(qtimerForReconection, &QTimer::timeout, this, &Client::tryToConnect);

    settings = set;

    socket = new QTcpSocket();
    thr = new DeskBlockThread(this);
    connect(socket, &QAbstractSocket::hostFound, this, &Client::hostFound, Qt::DirectConnection);
    connect(thr, &DeskBlockThread::unblockCorrectPWD, this, &Client::unblockedByPWD, Qt::DirectConnection);
    connectedToServer = 0;
    qtimerForReconection->start();
}

void Client::closeSocketAndDeleteClient()
{
    socket->disconnect();
    socket->close();
    qtimerForBlock->stop();
    qtimerForView->stop();
    this->deleteLater();
}


void Client::blockPcSlot()
{
    qDebug() << "blockingPCSLot";
    window->changeTime("--:--:--");
    this->blockPC();
}

void Client::changeTimeSlot()
{
    qtimeLeft = qtimeLeft.addSecs(-1);
    window->changeTime(qtimeLeft.toString(Qt::TextDate));
}

void Client::hostFound()
{

    qDebug() << "Sending: " << qtimeLeft.toString(Qt::TextDate).toUtf8();

    socket->write("00:00:00");
    socket->waitForBytesWritten(500);

    connect(socket, &QIODevice::readyRead, this, &Client::readyRead, Qt::DirectConnection);
    connect(socket, &QAbstractSocket::disconnected, this, &Client::disconected, Qt::DirectConnection);

}

void Client::readyRead()
{
    qDebug() << "Reading:" << socket->bytesAvailable();
    QByteArray answ = socket->readAll();
    qDebug() << answ;
    if(answ == ""){}
    else if(answ == "connected") {
        qDebug() << "Connected";
        connectedToServer = 1;
        qtimerForReconection->stop();
    }else if(answ == "unblock") {
        this->unblockPC();
    }else if(answ == "block"){
        this->blockPC();
    }else{
        QTime time = QTime::fromString(answ);
        window->changeTime(answ);
        this->setTimersAndStart(time);
    }
}

void Client::disconected()
{
    qDebug() << "disConnected";
    connectedToServer = 0;
    qtimerForReconection->start();
}

void Client::unblockedByPWD()
{
    socket->write("unblocked");
    socket->waitForBytesWritten(500);
}

void Client::tryToConnect()
{
    if (socket->state() == QAbstractSocket::UnconnectedState || socket->state() == QAbstractSocket::BoundState){
        if(settings->settingsReaded)
            socket->connectToHost( settings->getOption("hostIP"), 2319);
        else
            socket->connectToHost( "127.0.0.1", 2319);
    }
}

void Client::blockPC()
{
    if (!thr->isRunning() || thr->isBlocked == 0) {
        this->stopTimers();
        window->changeTime(QString::fromUtf8("00:00:00"));
        thr->start();
    }
    socket->write("blocked");
    socket->waitForBytesWritten(500);
}

void Client::unblockPC()
{
    this->stopTimers();
    window->changeTime(QString::fromUtf8("00:00:00"));
    if (thr->isBlocked == 1){
        thr->closeBlockDesk();
        thr->terminate();
        thr->wait();
    }
    socket->write("unblocked");
    socket->waitForBytesWritten(500);

}

void Client::setTimersAndStart(QTime time)
{
    this->unblockPC();
    qtimeLeft = time;
    uint64_t seconds = time.hour()*60*60 + time.minute()*60 + time.second();
    qtimerForBlock->setInterval(seconds*1000);
    qtimerForBlock->start();
    qtimerForView->start();
    qDebug() << "Timers started!";
}

void Client::stopTimers()
{
    if(qtimerForView->isActive()){
        qtimerForView->stop();
    }
    if (qtimerForBlock->isActive()) {
        qtimerForBlock->stop();
    }
}
