#ifndef VERSION_H
#define VERSION_H

#include <QObject>

#include "../build_number.h"

class Version : public QObject{
    Q_OBJECT

public:

    explicit Version(QObject *parent = nullptr): QObject(parent),
        m_versionString(QString::number(BUILD_NUMBER))
    {}

    Q_INVOKABLE QString versionNumber() const
    {
        return m_versionString;
    }

private:
    QString m_versionString;
};

#endif // VERSION_H
