#ifndef MYGROUPBOX_H
#define MYGROUPBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "settings.h"


class MyGroupBox
{
public:
    MyGroupBox(int index, Settings *set);
    int index;
    int connected;
    uint64_t timeLeft;
    QGroupBox* createPCbox(QString name, QString ip, QString time);
    QGroupBox *PCbox;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *IPvalue;
    QPushButton *ChooseButton;
    QVBoxLayout *verticalLayout_2;
    QLabel *TimerLabel;
    QRadioButton *StatusButton;
    bool mustBeBlocked;
private:
    Settings *set;
};

#endif // MYGROUPBOX_H
