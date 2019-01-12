#ifndef SERVERINTERFACE_H
#define SERVERINTERFACE_H
#include <QtCore>
class ServerInterface
{
public:
    ServerInterface();
    virtual ~ServerInterface() {}
    virtual void blockPC(int indexOfPC)=0;
    virtual void unblockPC(int indexOfPC)=0;
    virtual void unblockPC(int indexOfPC, QByteArray time)=0;
};

#endif // SERVERINTERFACE_H
