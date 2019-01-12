#include "deskblockthread.h"


DeskBlockThread::DeskBlockThread(QObject *parent) :
    QThread(parent)
{
    isBlocked = 0;
}

void DeskBlockThread::run(){
    hOld = GetThreadDesktop(GetCurrentThreadId());

    hNew = CreateDesktop(
        TEXT("reminder"),
        NULL,
        NULL,
        0,
        GENERIC_ALL,
        NULL
    );


    if(SetThreadDesktop(hNew)!=0){
        SwitchDesktop(hNew);
        isBlocked = 1;

        int help = 0;
        while(true){
            int answ = MessageBox(NULL, TEXT("PC is blocked!"), TEXT("Reminder"), MB_YESNOCANCEL);
            switch (answ) {
            case IDYES:
                if(help == 0 || help == 4 || help == 8) help++;
                else help = 0;
                break;
            case IDNO:
                if(help == 2 || help == 5 || help == 7) help++;
                else help = 0;
                break;
            case IDCANCEL:
                if(help == 1 || help == 3 || help == 6) help++;
                else help = 0;
                break;
            }
            if(help == 9) break;
        }
//132312321

        qDebug() << "Password is correct, unblocking";
        closeBlockDesk();
        emit this->unblockCorrectPWD();
    }


}

void DeskBlockThread::closeBlockDesk(){
    SwitchDesktop(hOld);
    isBlocked = 0;
    CloseDesktop(hNew);
    qDebug() << "PCs unblocked";
}

