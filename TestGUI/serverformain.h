#ifndef SERVERFORMAIN_H
#define SERVERFORMAIN_H

#endif // SERVERFORMAIN_H

int initializeSockets();
SOCKET createServerSocket();
SOCKET createAndAcceptClient(SOCKET servSock, char * retIP);
int setPCTimer(int minutes, SOCKET clientSock);
int blockPC(SOCKET clientSock);
int ublockPC(SOCKET clientSock);
int runThread(SOCKET clientSock);
char* acceptClients();
