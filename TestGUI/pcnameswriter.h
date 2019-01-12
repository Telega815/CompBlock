#ifndef PCNAMESWRITER_H
#define PCNAMESWRITER_H
#include <QMap>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include "QDebug"
#include <QStringList>

class PcNamesWriter
{
public:
    PcNamesWriter();
    QString getName(QString key);
    void addName(QString ip, QString name);
private:
    bool readFile();
    bool writeFile();
    QMap<QString, QString> names;
};

#endif // PCNAMESWRITER_H
