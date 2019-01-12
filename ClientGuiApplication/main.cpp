#include "mainwindow.h"
#include <QApplication>
#include "client.h"


int j = 1;
void corPWD(){
    j=0;
    qDebug() << "Corrrect PWD";
}

void incorPWD(){
    j=1;
    qDebug() << "Incorrrect PWD";
}

int main(int argc, char *argv[])
{
    Settings *set = new Settings();
    while(j != 0){
        QApplication a(argc, argv);
        MainWindow w(0, set);
        Client *c = new Client(&w);
        w.show();
        QObject::connect(&w, &MainWindow::correctPWD, corPWD);
        QObject::connect(&w, &MainWindow::incorrectPWD, incorPWD);
        c->initializeSocketAndTimers(set);
        a.exec();
        c->closeSocketAndDeleteClient();
        Sleep(3000);
    }
    return 0;
}


