#-------------------------------------------------
#
# Project created by QtCreator 2018-05-27T18:53:50
#
#-------------------------------------------------

QT       += core
QT       += network
QT       += gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestGUI
TEMPLATE = app


SOURCES += main.cpp\
        mypinas.cpp \
    mygroupbox.cpp \
    myserver.cpp \
    mythread.cpp \
    serverinterface.cpp \
    settings.cpp \
    confirmdialog.cpp \
    renamedialog.cpp \
    pcnameswriter.cpp

HEADERS  += mypinas.h \
    mygroupbox.h \
    myserver.h \
    mythread.h \
    serverinterface.h \
    settings.h \
    confirmdialog.h \
    renamedialog.h \
    pcnameswriter.h

FORMS    += mypinas.ui \
    confirmdialog.ui \
    renamedialog.ui

DISTFILES +=
