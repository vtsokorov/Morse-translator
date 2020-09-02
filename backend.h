#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include "qmorse.h"

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString result READ resultConvert WRITE setResultConvert)
    Q_PROPERTY(QString content READ content WRITE setContent)

public:
    explicit Backend(QObject *parent = nullptr);

public:
    QString resultConvert() const;
    void setResultConvert(const QString &text);

    QString content() const;
    void setContent(const QString &text);

public slots:
    void createNew();
    void inputContent(const QString &element, bool isMorse);

    void readFile(const QString &path);
    void saveFile(const QString &path);

private:
    QMorse object;
    QString result;
    QString textContent;
};

#endif // BACKEND_H
