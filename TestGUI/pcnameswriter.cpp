#include "pcnameswriter.h"

PcNamesWriter::PcNamesWriter()
{
    readFile();
}

QString PcNamesWriter::getName(QString key)
{
    if (names.contains(key)) {
        return names.value(key);
    } else {
        return NULL;
    }

}

void PcNamesWriter::addName(QString ip, QString name)
{
    if (names.contains(ip)) {
        names.remove(ip);
    }
    names.insert(ip, name);
    this->writeFile();
}

bool PcNamesWriter::readFile()
{
    QString path = QDir::currentPath();
    path.append("/PcNames.txt");

    QFile mSettings(path);
    if(!mSettings.open(QFile::ReadOnly | QFile::Text)){

        return false;
    }

    QTextStream in(&mSettings);
    in.setCodec("UTF-8");
    QString mText;
    QStringList list;

    while(!in.atEnd()){
        mText = in.readLine();
        list = mText.split("=");
        names.insert(list.at(0),list.at(1));
    }
    mSettings.close();
    return true;
}

bool PcNamesWriter::writeFile()
{
    QString path = QDir::currentPath();
    path.append("/PcNames.txt");

    QFile mSettings(path);
    if(!mSettings.open(QFile::WriteOnly | QFile::Text)){
        return false;
    }

    QTextStream out(&mSettings);
    out.setCodec("UTF-8");
    foreach (QString key, names.keys()) {
        out << key << "=" << names.value(key) << "\n";
    }
    mSettings.flush();
    mSettings.close();
    return true;
}
