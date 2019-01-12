#include "mygroupbox.h"

MyGroupBox::MyGroupBox(int index, Settings *set)
{
    this->index = index;
    this->connected = 1;
    this->set = set;
}

QGroupBox* MyGroupBox::createPCbox(QString name, QString ip, QString time){

    //----------------------------
    PCbox = new QGroupBox();
    QString str = QString("PCbox_");
    str = str + QString::number(index);
    PCbox->setObjectName(str);
    QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(PCbox->sizePolicy().hasHeightForWidth());
    PCbox->setSizePolicy(sizePolicy2);
    PCbox->setMinimumSize(QSize(0, 90));
    QPalette palette;
    PCbox->setPalette(palette);
    QFont font2;
    font2.setPointSize(12);
    font2.setBold(false);
    font2.setWeight(50);
    PCbox->setFont(font2);
    PCbox->setMouseTracking(false);
    PCbox->setFocusPolicy(Qt::NoFocus);
    PCbox->setAutoFillBackground(false);
    PCbox->setStyleSheet(QLatin1String("QGroupBox { \n"
"     border: 2px solid rgb(218, 218, 218); \n"
"     border-radius: 3px; \n"
" } "));
    PCbox->setFlat(false);
    PCbox->setCheckable(false);
    PCbox->setChecked(false);
    widget = new QWidget(PCbox);
    str = (QString("widget_"));
    str = str + QString::number(index);
    widget->setObjectName(str);
    widget->setGeometry(QRect(13, 16, 231, 61));
    horizontalLayout = new QHBoxLayout(widget);
    horizontalLayout->setSpacing(6);
    horizontalLayout->setContentsMargins(11, 11, 11, 11);
    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout_2"));
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    verticalLayout = new QVBoxLayout();
    verticalLayout->setSpacing(6);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    IPvalue = new QLabel(widget);
    str = (QString("IPvalue_"));
    str = str + QString::number(index);
    IPvalue->setObjectName(str);
    IPvalue->setFont(font2);
    IPvalue->setAlignment(Qt::AlignCenter);

    verticalLayout->addWidget(IPvalue);

    ChooseButton = new QPushButton(widget);
    str = (QString("pushButton_"));
    str = str + QString::number(index);
    ChooseButton->setObjectName(str);

    verticalLayout->addWidget(ChooseButton);


    horizontalLayout->addLayout(verticalLayout);

    verticalLayout_2 = new QVBoxLayout();
    verticalLayout_2->setSpacing(6);
    verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
    TimerLabel = new QLabel(widget);
    str = (QString("PC_Timer_"));
    str = str + QString::number(index);
    TimerLabel->setObjectName(str);
    TimerLabel->setFont(font2);
    TimerLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    verticalLayout_2->addWidget(TimerLabel);

    StatusButton = new QRadioButton(widget);
    str = (QString("PC_Status_"));
    str = str + QString::number(index);
    StatusButton->setObjectName(str);
    QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(StatusButton->sizePolicy().hasHeightForWidth());
    StatusButton->setSizePolicy(sizePolicy3);
    StatusButton->setLayoutDirection(Qt::RightToLeft);
    StatusButton->setAutoFillBackground(false);
    StatusButton->setCheckable(true);
    StatusButton->setChecked(false);

    verticalLayout_2->addWidget(StatusButton);


    horizontalLayout->addLayout(verticalLayout_2);

    PCbox->setTitle(name);
    IPvalue->setText(ip);
    if(set->settingsReaded){
        ChooseButton->setText(set->getOption("Choose"));
        StatusButton->setText(set->getOption("Unblocked"));
    }else{
        ChooseButton->setText("Choose");
        StatusButton->setText("Unblocked");
    }

    TimerLabel->setText(time);

    StatusButton->setEnabled(false);
    return PCbox;
}
