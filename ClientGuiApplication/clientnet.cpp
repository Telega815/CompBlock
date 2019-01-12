#include <stdio.h>
#include <winsock2.h>
#include <WS2tcpip.h>

//int CALLBACK WinMain(HINSTANCE hInstance,
//	HINSTANCE hPrevInstance,
//	LPSTR     lpCmdLine,
//	int       nCmdShow)
int ConnectToServer()
{

    WSADATA wsaData;
    int retVal = 0;


    int err = WSAStartup(0x0101, &wsaData);
    if (err == SOCKET_ERROR)
    {
        system("pause");
        printf("WSAStartup() failed: %ld\n", GetLastError());
        return 1;
    }


    //Ñîçäàåì ñîêåò
    SOCKET clientSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (clientSock == SOCKET_ERROR)
    {
        system("pause");
        printf("Unable to create socket\n");
        WSACleanup();
        return 1;
    }

    SOCKADDR_IN serverInfo;

    serverInfo.sin_family = AF_INET;
    InetPton(AF_INET, L"(192.168.1.150)", &serverInfo.sin_addr.S_un.S_addr);
    serverInfo.sin_port = htons(2319);

    retVal = connect(clientSock, (struct sockaddr *)&serverInfo, sizeof(struct sockaddr));
    if (retVal == SOCKET_ERROR)
    {
        system("pause");
        printf("Unable to connect\n");
        WSACleanup();
        return 1;
    }

    printf("Connection made sucessfully\n");

    char pBuf[] = "PIDR";

    printf("Sending request from client\n");
    retVal = send(clientSock, pBuf, 5, 0);

    if (retVal == SOCKET_ERROR)
    {
        system("pause");
        printf("Unable to send\n");
        WSACleanup();
        return 1;
    }

    char szResponse[5];
    retVal = recv(clientSock, szResponse, 5, 0);

    if (retVal == SOCKET_ERROR)
    {
        system("pause");
        printf("Unable to recv\n");
        WSACleanup();
        return 1;
    }

    printf("Got the response from server\n%s\n", szResponse);

    if (strncmp(szResponse, "STOP", 5)) {
        const HDESK hOld = GetThreadDesktop(GetCurrentThreadId());

        const HDESK hNew = CreateDesktop(
            TEXT("reminder"),
            NULL,
            NULL,
            0,
            DESKTOP_SWITCHDESKTOP
            | DESKTOP_WRITEOBJECTS
            | DESKTOP_READOBJECTS
            | DESKTOP_CREATEWINDOW,
            NULL
        );

        SetThreadDesktop(hNew);
        SwitchDesktop(hNew);

        MessageBox(NULL, TEXT("szResponse"), TEXT("Reminder"), MB_ICONWARNING);

        SwitchDesktop(hOld);
        CloseDesktop(hNew);
    }
    else
    {
        system("pause");
    }

    closesocket(clientSock);
    WSACleanup();

    return 0;
}
