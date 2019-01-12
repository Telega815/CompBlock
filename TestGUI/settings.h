#ifndef SETTINGS_H
#define SETTINGS_H
#include <QMap>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include "QDebug"
#include <QStringList>


class Settings
{
public:
    Settings();
    Settings(QString path);
    QString getOption(QString key);
    QString getOption(const char *key);
    bool readSettings(QString path);
    bool settingsReaded;
private:
    QMap<QString, QString> settings;
    bool readSettings();
};

#endif // SETTINGS_H
