#ifndef PC_FORM_H
#define PC_FORM_H

#include <QWidget>

namespace Ui {
class PC_Form;
}

class PC_Form : public QWidget
{
    Q_OBJECT

public:
    explicit PC_Form(QWidget *parent = 0);
    ~PC_Form();

public:
    Ui::PC_Form *ui;
    void setParams(QString name, QString ip, QString time);
    void setTime(QString time);
private slots:
    void on_PCbox_clicked();
    void on_StatusLabel_clicked();
};

#endif // PC_FORM_H
