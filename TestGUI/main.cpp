#include "mypinas.h"
#include <QApplication>
#include "myserver.h"
#include "settings.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyPinas w;
    w.show();

    MyServer server;
    w.server = &server;
    server.StartServer(&w);

    return a.exec();
}
