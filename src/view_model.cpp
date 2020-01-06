/**
 * @file:   src/view_model.cpp
 * @author: А.В. Федченко
 * @date    2019.12.23
 */

#include <QDebug>
#include <QStandardPaths>

#include "salsa20.h"
#include "data_model_controller.h"

#include "view_model.h"

constexpr char c_nonce[] = "99990001";

view_model::view_model(QObject *parent) : QObject(parent),
    m_masterPassword(""),
    m_readyToWork(false)
{
#ifdef ANDROID
    checkPermission();
#endif

    m_cardModel = new dataModelController(this);
}

view_model::~view_model() {}

QString view_model::masterPassword() const
{
    return m_masterPassword;
}

bool view_model::readyToWork() const
{
    return m_readyToWork;
}

void view_model::save()
{
    if (m_masterPassword.isEmpty())
        return;

    if (m_readyToWork)
    {
        m_cardModel->backup();
        m_cardModel->save(m_salsa);
    }
}

bool view_model::load()
{
    if (m_masterPassword.isEmpty())
        return false;

    m_cardModel->clear();

    m_readyToWork = true;
    emit readyToWorkChanged(m_readyToWork);

    return m_cardModel->load(m_salsa);
}

bool view_model::exportData(const QUrl &exportPath) const
{
    return m_cardModel->exportData(exportPath);
}

bool view_model::importData(const QUrl &importFileName)
{
    return m_cardModel->importData(importFileName, m_salsa);
}

dataModelController *view_model::cardController()
{
    return m_cardModel;
}

QString view_model::fileName() const
{
    return m_fileName;
}

void view_model::setMasterPassword(QString masterPassword)
{
    if (m_masterPassword == masterPassword)
        return;

    m_masterPassword = masterPassword;

    m_salsa.reset(new salsa20{masterPassword.toStdString(), c_nonce});

    emit masterPasswordChanged(m_masterPassword);
}

void view_model::setReadyToWork(bool readyToWork)
{
    if (m_readyToWork == readyToWork)
        return;

    m_readyToWork = readyToWork;
    emit readyToWorkChanged(m_readyToWork);
}

void view_model::setFileName(QString fileName)
{
    if (m_fileName == fileName)
        return;

    m_fileName = fileName;
    emit fileNameChanged(m_fileName);
}

#ifdef ANDROID
#include <QtAndroidExtras/QtAndroid>
bool view_model::checkPermission() {
    QtAndroid::PermissionResult r = QtAndroid::checkPermission("android.permission.WRITE_EXTERNAL_STORAGE");
    if(r == QtAndroid::PermissionResult::Denied) {
        QtAndroid::requestPermissionsSync( QStringList() << "android.permission.WRITE_EXTERNAL_STORAGE" );
        r = QtAndroid::checkPermission("android.permission.WRITE_EXTERNAL_STORAGE");
        if(r == QtAndroid::PermissionResult::Denied) {
            qDebug() << "Permission denied";
            return false;
        }
    }

    qDebug() << "Permissions granted!";
    return true;
}
#endif

