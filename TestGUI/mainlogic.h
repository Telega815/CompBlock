#ifndef MAINLOGIC_H
#define MAINLOGIC_H

#endif // MAINLOGIC_H

#include <iostream>
#include <string>
#include <Ws2tcpip.h>
#include <ctime>
#include <stdlib.h>


using namespace std;

SOCKET createServerSocket();
SOCKET createAndAcceptClient(SOCKET servSock, char *retIP);
int setPCTimer(int minutes, SOCKET clientSock);
int blockPC(SOCKET clientSock);
int ublockPC(SOCKET clientSock);
int runThread(SOCKET clientSock);
void closeSockets();
char* acceptClients();
