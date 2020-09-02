#ifndef QMORSE_H
#define QMORSE_H

#include <QMap>
#include <QString>

class QMorse
{
public:
    QMorse();

    QString encode(const QString& s);
    QString decode(const QString& s);

private:
    QMap<QChar, QString> alphabet;
};

#endif
