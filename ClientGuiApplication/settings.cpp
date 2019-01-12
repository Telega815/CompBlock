#include "settings.h"


Settings::Settings(QString path)
{
    this->readSettings(path);
}

Settings::Settings()
{
    this->readSettings();
}

QString Settings::getOption(QString key)
{
    if (!settingsReaded) return NULL;

    return settings.value(key);
}

QString Settings::getOption(const char *key)
{
    QString str = QString::fromUtf8(key);
    return this->getOption(str);
}

bool Settings::readSettings(QString path)
{
    QFile mSettings(path);
    if(!mSettings.open(QFile::ReadOnly | QFile::Text)){
        this->settingsReaded = false;
        return false;
    }

    QTextStream in(&mSettings);
    in.setCodec("UTF-8");
    QString mText;
    QStringList list;

    while(!in.atEnd()){
        mText = in.readLine();
        list = mText.split("=");
        settings.insert(list.at(0),list.at(1));
    }
    mSettings.close();
    this->settingsReaded = true;
    return true;
}

bool Settings::readSettings()
{
    QString path = QDir::currentPath();
    path.append("/Settings.cfg");

    return this->readSettings(path);
}
