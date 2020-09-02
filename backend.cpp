#include "backend.h"

#include <QFile>
#include <QFileInfo>

Backend::Backend(QObject *parent) : QObject(parent) {

}

void Backend::createNew()
{
    result.clear();
    textContent.clear();
}

void Backend::readFile(const QString &path)
{
    if(QFileInfo(path).isFile()){
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QByteArray bytes = file.readAll();
        textContent = QString::fromStdString(bytes.toStdString());
    }
}

void Backend::saveFile(const QString &path)
{
    QString pathWithSufix = path;
    QFile file(pathWithSufix.append(".txt"));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    file.write(result.toStdString().c_str());
    file.close();
}

void Backend::inputContent(const QString &data, bool isMorse)
{
    if(isMorse)
        result = object.decode(data);
    else
        result = object.encode(data);
}

QString Backend::resultConvert() const {
   return result;
}

void Backend::setResultConvert(const QString &text) {
    result = text;
}

QString Backend::content() const {
    return textContent;
}

void Backend::setContent(const QString &text){
    textContent = text;
}






