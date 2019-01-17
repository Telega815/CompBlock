#-------------------------------------------------
#
# Project created by QtCreator 2018-06-07T15:15:34
#
#-------------------------------------------------

QT       += core
QT       += network
QT       += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ClientGuiApplication
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    deskblockthread.cpp \
    client.cpp \
    settings.cpp \
    alertdialog.cpp

HEADERS  += mainwindow.h \
    deskblockthread.h \
    client.h \
    settings.h \
    alertdialog.h

FORMS    += mainwindow.ui \
    alertdialog.ui

RESOURCES += \
    trayicon.qrc

DISTFILES +=
