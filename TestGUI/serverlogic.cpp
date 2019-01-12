#include "MainLogic.h"
#include <thread>

SOCKET servSock;
SOCKET *clientSocks;
int clientsCount = 0;


int initializeSockets()
{
    clientSocks = (SOCKET*)malloc(14);
    WSADATA wsaData;
    int retVal;

    int err = WSAStartup(0x0101, &wsaData);
    if (err == SOCKET_ERROR)
    {
        printf("WSAStartup() failed: %ld\n", GetLastError());
        return 1;
    }



    servSock = createServerSocket();

    retVal = listen(servSock, SOMAXCONN);
    if (retVal == SOCKET_ERROR)
    {
        printf("Unable to listen\n");
        WSACleanup();
        return SOCKET_ERROR;
    }
    closeSockets();
    return 0;
}



char* acceptClients() {
    char ip[INET_ADDRSTRLEN];

    SOCKET clientSock = createAndAcceptClient(servSock, ip);
    string name = "ANAL_" + to_string(clientsCount);
    thread t(runThread, clientSock);
    t.detach();
    clientsCount++;
    clientSocks[clientsCount] = clientSock;

    return ip;
}





//---------------------------------creating server sockets and accept clients----------------------------------------------
SOCKET createServerSocket() {
    int retVal;
    SOCKET servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (servSock == INVALID_SOCKET)
    {
        WSACleanup();
        return SOCKET_ERROR;
    }

    SOCKADDR_IN sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(2319);
    sin.sin_addr.s_addr = INADDR_ANY;

    retVal = ::bind(servSock, (LPSOCKADDR)&sin, sizeof(sin));
    if (retVal == SOCKET_ERROR)
    {
        WSACleanup();
        return SOCKET_ERROR;
    }
    return servSock;
}

SOCKET createAndAcceptClient(SOCKET servSock, char *retIP)
{

    SOCKET clientSock;
    struct sockaddr_in addr;
    int addrlen = sizeof(addr);

    clientSock = accept(servSock, (sockaddr*)&addr, &addrlen);

    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(addr.sin_addr), ip, addrlen);

    //printf("%s\n", ip);
    strncpy(retIP, ip, INET_ADDRSTRLEN);

    if (clientSock == INVALID_SOCKET)
    {
        WSACleanup();
        return SOCKET_ERROR;
    }

    return clientSock;
}


//---------------------------------sending data to client----------------------------------------------
int setPCTimer(int minutes, SOCKET clientSock)
{
    int retVal;
    string str = to_string(minutes);
    const char *szResp = str.c_str();

    retVal = send(clientSock, szResp, 5, 0);

    if (retVal == SOCKET_ERROR)
    {
        return SOCKET_ERROR;
    }
    return 0;
}

int blockPC(SOCKET clientSock)
{
    int retVal;
    const char* str = "block";
    retVal = send(clientSock, str, 5, 0);

    if (retVal == SOCKET_ERROR)
    {
        return SOCKET_ERROR;
    }
    return 0;
}

int ublockPC(SOCKET clientSock)
{
    int retVal;
    const char* str = "unblk";
    retVal = send(clientSock, str, 5, 0);

    if (retVal == SOCKET_ERROR)
    {
        return SOCKET_ERROR;
    }
    return 0;
}






int runThread(SOCKET clientSock)
{
    int retVal;

    //-----------------recieving
    char szReq[5];
    retVal = recv(clientSock, szReq, 5, 0);

    if (retVal == SOCKET_ERROR)
    {
        printf("Unable to recv\n");
        return SOCKET_ERROR;
    }

    printf("Got the request from client\n%s\n", szReq);

    setPCTimer(1488, clientSock);

    closesocket(clientSock);
    return 0;
}

void closeSockets()
{
    closesocket(servSock);
    WSACleanup();
}
