#include "mypinas.h"
#include "ui_mypinas.h"
#include "pc_form.h"
#include "QDebug"
#include "synchapi.h"



MyPinas::MyPinas(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyPinas)

{
    ui->setupUi(this);
    ui->RP_scrollAreaWidgetContents->setLayout(ui->RP_VLayout);
    clientsCount = 0;
    selectedPC = -1;
    namesWriter = new PcNamesWriter();
    renameDialog = new RenameDialog();
    connect(renameDialog, SIGNAL(rename(QString)), this, SLOT(renamePC(QString)));
    set = new Settings();
    confirmDialog = new ConfirmDialog(0, set);
    connect(confirmDialog, SIGNAL(applyClick()), this, SLOT(on_LP_TimerBox_ApplyButton_clicked()));
    connect(confirmDialog, SIGNAL(cancelClick()), this, SLOT(on_LP_TimerBox_CancelButton_clicked()));

    if (set->settingsReaded){
        ui->LP_BlockPC_Button->setText(set->getOption("Block PC"));
        ui->LP_UnBlockPC_Button->setText(set->getOption("Unblock PC"));
        ui->LP_TimerBox_AddButton->setText(set->getOption("Add"));
        ui->LP_TimerBox_SetButton->setText(set->getOption("Set"));
        ui->LP_TimerBox_TimerLabel->setText(set->getOption("Timer (H:MM:SS):"));
        ui->LP_StatusLabel->setText(set->getOption("Status"));
        ui->LP_TimeLabel->setText(set->getOption("timeLeft"));
        ui->RenameButton->setText(set->getOption("Rename PC"));
    }
}



MyPinas::~MyPinas()
{
    delete ui;
}

void MyPinas::setViewTime(int clientIndex, QByteArray *time)
{
    qDebug() << "serViewTime: " << time;
    MyGroupBox *box = clients.at(clientIndex);
    if (QString::compare("--:--:--", box->TimerLabel->text(), Qt::CaseInsensitive) == 0){
        box->TimerLabel->setText(time->toStdString().c_str());
        box->TimerLabel->update();
    }
    if(selectedPC == clientIndex)
        box->ChooseButton->click();
}

void MyPinas::setViewStatus(int clientIndex, int status)
{
    qDebug() << "serViewStatus: " << status;
    MyGroupBox *box = clients.at(clientIndex);
    box->StatusButton->setCheckable(true);
    if (status == 0) {
        if (set->settingsReaded) {
            box->StatusButton->setText(set->getOption("Unblocked"));
        } else {
            box->StatusButton->setText("unblocked");
        }
        if(selectedPC == clientIndex)
            box->StatusButton->setStyleSheet(QStringLiteral("color: rgba(0, 0, 108, 255);"));
        else
            box->StatusButton->setStyleSheet(QStringLiteral("color: rgba(0, 0, 0, 255);"));
        box->StatusButton->setChecked(false);
    }else {
        if (set->settingsReaded) {
            box->StatusButton->setText(set->getOption("Blocked"));
        } else {
            box->StatusButton->setText("blocked");
        }
        box->StatusButton->setStyleSheet(QStringLiteral("color: rgba(108, 0, 0, 255);"));
        box->StatusButton->setChecked(true);
    }
    box->StatusButton->update();
    if(selectedPC == clientIndex)
        box->ChooseButton->click();
}

int MyPinas::addPC(QString *ip){

    MyGroupBox *box = new MyGroupBox(clientsCount, set);
    clientsCount++;
    QString name = namesWriter->getName(*ip);
    if (name == NULL) {
        name = "Comp" + QString::number(clientsCount);
    }
    QString *time = new QString("--:--:--");
    QGroupBox *qbox = box->createPCbox(name, *ip, *time);
    connect(box->ChooseButton, SIGNAL (released()), this, SLOT (on_myBtn_clicked()));
    clients << box;
    ui->RP_VLayout->insertWidget(0,qbox);
    QTimer  *qtimerForView = new QTimer();
    qtimersForTimeChanging << qtimerForView;
    connect(qtimerForView, SIGNAL(timeout()), this, SLOT(changeTime()));
    ui->RightPanel->update();
    if(clientsCount == 1)
        box->ChooseButton->click();
    return clientsCount-1;
}

void MyPinas::setTimers(int clientIndex, QString *time){
    QTime qtime = QTime::fromString(*time, Qt::TextDate);
    QTimer *qtimerForView;
    MyGroupBox *box = clients.at(clientIndex);
    qtimerForView = qtimersForTimeChanging.at(clientIndex);
    uint64_t secondsLeft = qtime.hour()*60*60 + qtime.minute()*60 + qtime.second();
    box->timeLeft = secondsLeft;
    qtimerForView->setInterval(1000);
    qtimerForView->start();
}

int MyPinas::checkIP(QString IP)
{
    foreach (MyGroupBox *box, clients) {
        if(box->IPvalue->text() == IP){
            return clients.indexOf(box);
        }
    }
    return -1;
}

void MyPinas::reconectPC(int index)
{
    MyGroupBox *box = clients.at(index);
    box->PCbox->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));
    box->connected = 1;
    if(selectedPC == index){

        ui->LP_UnBlockPC_Button->setDisabled(false);
        ui->LP_BlockPC_Button->setDisabled(false);
        ui->LP_TimerBox_AddButton->setDisabled(false);
        ui->LP_TimerBox_SetButton->setDisabled(false);
        ui->RenameButton->setDisabled(false);
        ui->LeftBox->update();
    }

    Sleep(1000);
    if (qtimersForTimeChanging.at(index)->isActive()) {
        box->ChooseButton->click();
        confirmDialog->setTime(ui->LP_TimeValue->text());
        this->on_LP_TimerBox_ApplyButton_clicked();
        if (set->settingsReaded) {
            ui->LP_StatusValue->setText(set->getOption("Unblocked"));
            box->StatusButton->setText(ui->LP_StatusValue->text());
        } else {
            ui->LP_StatusValue->setText("unblocked");
            box->StatusButton->setText(ui->LP_StatusValue->text());
        }
        ui->LP_StatusValue->setStyleSheet(QStringLiteral("color: rgba(0, 0, 0, 255);"));
        if (index == selectedPC){
            box->StatusButton->setStyleSheet(QStringLiteral("color: rgba(0, 0, 108, 255);"));
        }else{
            box->StatusButton->setStyleSheet(QStringLiteral("color: rgba(0, 0, 0, 255);"));
        }

    } else {
        if (box->mustBeBlocked) {
            box->ChooseButton->click();
            this->on_LP_BlockPC_Button_clicked();
            if (set->settingsReaded) {
                ui->LP_StatusValue->setText(set->getOption("Blocked"));
                box->StatusButton->setText(ui->LP_StatusValue->text());
            } else {
                ui->LP_StatusValue->setText("blocked");
                box->StatusButton->setText(ui->LP_StatusValue->text());
            }
            ui->LP_StatusValue->setStyleSheet(QStringLiteral("color: rgba(108, 0, 0, 255);"));
            box->StatusButton->setStyleSheet(QStringLiteral("color: rgba(108, 0, 0, 255);"));
        }
    }
    ui->LP_StatusValue->update();
    box->StatusButton->update();

}

void MyPinas::removePC(int index){
    MyGroupBox *box = clients.at(index);
    box->PCbox->setStyleSheet(QStringLiteral("color: rgba(108, 0, 0, 255);"));
    if(selectedPC == index){
        if (set->settingsReaded) {
            box->StatusButton->setText(set->getOption("Disconected"));
        } else {
            box->StatusButton->setText("disconected");
        }
        ui->LP_StatusValue->setText(box->StatusButton->text());
        ui->LP_StatusValue->setStyleSheet(QStringLiteral("color: rgba(108, 0, 0, 255);"));
        ui->LP_UnBlockPC_Button->setDisabled(true);
        ui->LP_BlockPC_Button->setDisabled(true);
        ui->LP_TimerBox_AddButton->setDisabled(true);
        ui->LP_TimerBox_SetButton->setDisabled(true);
        ui->RenameButton->setDisabled(true);
        ui->LeftBox->update();
    }
    box->connected = 0;
    ui->RightPanel->update();
}




void MyPinas::changeLP(QString name, QString ip, QString time, bool status)
{
    timeBeforeChange = time;
    ui->LeftBox->setTitle(name);
    ui->LP_IPvalue->setText(ip);
    ui->LP_TimeValue->setText(time);
    if (status == 0) {
        if (set->settingsReaded) {
            ui->LP_StatusValue->setText(set->getOption("Unblocked"));
        } else {
            ui->LP_StatusValue->setText("unblocked");
        }
        ui->LP_StatusValue->setStyleSheet(QStringLiteral("color: rgba(0, 0, 0, 255);"));
    }else {
        if (set->settingsReaded) {
            ui->LP_StatusValue->setText(set->getOption("Blocked"));
        } else {
            ui->LP_StatusValue->setText("blocked");
        }
        ui->LP_StatusValue->setStyleSheet(QStringLiteral("color: rgba(108, 0, 0, 255);"));
    }
    ui->LP_StatusValue->update();
    ui->LeftBox->update();
    ui->LP_IPvalue->update();
    ui->LP_TimeValue->update();
}

void MyPinas::changeTime(){
    QTimer* qtimerSender = qobject_cast<QTimer*>(sender());
    int indexOfSender = qtimersForTimeChanging.indexOf(qtimerSender);
    MyGroupBox *box = clients.at(indexOfSender);
    if (box->timeLeft != 0) {
        box->timeLeft--;
        QTime time = QTime::fromString(box->TimerLabel->text());
        time = time.addSecs(-1);
        QString newTimeLeft = time.toString(Qt::TextDate);
        box->TimerLabel->setText(newTimeLeft);
        box->TimerLabel->update();
        if(indexOfSender == selectedPC){
            ui->LP_TimeValue->setText(newTimeLeft);
            if (confirmDialog->isVisible()) {
                confirmDialog->changeTime();
            }
            ui->LP_TimeValue->update();
        }
    }else{
        box->mustBeBlocked = true;
        qtimerSender->stop();
    }
}

void MyPinas::on_myBtn_clicked()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    QString objname =  buttonSender->objectName();
    QStringList list = objname.split("_");
    QString strIndex = list.value(1);
    if (selectedPC != -1) {
        clients.at(selectedPC)->PCbox->setStyleSheet(QStringLiteral("color: rgba(0, 0, 0, 255);"));
    }
    selectedPC = strIndex.toInt();
    MyGroupBox *box = clients.at(selectedPC);
    box->PCbox->setStyleSheet(QStringLiteral("color: rgba(0, 0, 108, 255);"));
    if(box->connected == 0){
        if (set->settingsReaded) {
            box->StatusButton->setText(set->getOption("Disconected"));
        } else {
            ui->LP_StatusValue->setText("disconected");
        }
        ui->LP_UnBlockPC_Button->setDisabled(true);
        ui->LP_BlockPC_Button->setDisabled(true);
        ui->LP_TimerBox_AddButton->setDisabled(true);
        ui->LP_TimerBox_SetButton->setDisabled(true);
        ui->RenameButton->setDisabled(true);
    }else {
        ui->LP_UnBlockPC_Button->setDisabled(false);
        ui->LP_BlockPC_Button->setDisabled(false);
        ui->LP_TimerBox_AddButton->setDisabled(false);
        ui->LP_TimerBox_SetButton->setDisabled(false);
        ui->RenameButton->setDisabled(false);
    }
    changeLP(box->PCbox->title(), box->IPvalue->text(), box->TimerLabel->text(), box->StatusButton->isChecked());
}

void MyPinas::on_LP_TimerBox_SetButton_clicked()
{
    QTime time = ui->LP_TimerBox_timeEdit->time();
    QString timeStr = time.toString(Qt::TextDate);
    time = time.fromString("00:00:00", Qt::TextDate);
    ui->LP_TimerBox_timeEdit->setTime(time);
    ui->LP_TimerBox_timeEdit->update();
    confirmDialog->setTime(timeStr);
    confirmDialog->open();
}

void MyPinas::on_LP_TimerBox_AddButton_clicked()
{
    QString oldTimeStr = ui->LP_TimeValue->text();
    QStringList list = oldTimeStr.split(":");
    QString oldHoursStr = list.at(0);
    QString oldMinutesStr = list.at(1);
    QString oldSecondsStr = list.at(2);

    int oldHours = oldHoursStr.toInt();
    int oldMinutes = oldMinutesStr.toInt();
    int oldSeconds = oldSecondsStr.toInt();
    oldSeconds += oldMinutes*60 + oldHours*60*60;

    QTime time = ui->LP_TimerBox_timeEdit->time();
    time = time.addSecs(oldSeconds);
    QString timeStr = time.toString(Qt::TextDate);
    time = time.fromString("00:00:00", Qt::TextDate);
    ui->LP_TimerBox_timeEdit->setTime(time);
    ui->LP_TimerBox_timeEdit->update();
    confirmDialog->setTime(timeStr);
    confirmDialog->open();
}

void MyPinas::on_LP_TimerBox_CancelButton_clicked()
{

}

void MyPinas::on_LP_TimerBox_ApplyButton_clicked()
{
    qDebug() << "on_LP_TimerBox_ApplyButton_clicked";
    QString timeStr = confirmDialog->getTime();
    ui->LP_TimeValue->setText(timeStr);
    ui->LP_TimeValue->update();
    MyGroupBox *box = clients.at(selectedPC);
    box->TimerLabel->setText(timeStr);
    box->mustBeBlocked = false;
    setTimers(selectedPC, &timeStr);
    server->unblockPC(selectedPC, timeStr.toUtf8());

}

void MyPinas::on_LP_UnBlockPC_Button_clicked()
{
    qDebug() << "unblockingPC";
    qtimersForTimeChanging.at(selectedPC)->stop();
    ui->LP_TimeValue->setText("00:00:00");
    MyGroupBox *box = clients.at(selectedPC);
    box->TimerLabel->setText("00:00:00");
    box->mustBeBlocked = false;
    server->unblockPC(selectedPC);
}

void MyPinas::on_LP_BlockPC_Button_clicked()
{
    qDebug() << "blockingPC";
    qtimersForTimeChanging.at(selectedPC)->stop();
    ui->LP_TimeValue->setText("00:00:00");
    clients.at(selectedPC)->TimerLabel->setText("00:00:00");
    server->blockPC(selectedPC);
}

void MyPinas::on_RenameButton_clicked()
{
    renameDialog->setLabels(ui->LP_IPvalue->text(), ui->LeftBox->title());
    renameDialog->open();
}

void MyPinas::renamePC(QString name)
{
    namesWriter->addName(ui->LP_IPvalue->text(), name);
    ui->LeftBox->setTitle(name);
    clients.at(selectedPC)->PCbox->setTitle(name);
}
