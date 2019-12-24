/******************************************************************************
 * Разработчик: Закрытое акционерное общество "Научно исследовательский       *
 * институт "Центрпрограммсистем", г. Тверь (ЗАО НИИ ЦПС)					  *
 *																			  *
 * Интеллектуальная собственность ЗАО НИИ ЦПС								  *
 ******************************************************************************/

/**
 * @file:	src/view_model.cpp
 * @author:	А.В. Федченко
 * @date	2019.12.23
 */

#include <QStandardPaths>

#include "salsa20.h"
#include "json_parser.h"
#include "data_model_controller.h"

#include "view_model.h"

constexpr char c_nonce[] = "99990001";

view_model::view_model(QObject *parent) : QObject(parent),
    m_masterPassword(""),
    m_readyToWork(false)
{
    m_cardModel = new data_model_controller(this);
}

view_model::~view_model(){}

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

    m_cardModel->save(m_salsa.get());
}

void view_model::load()
{
    if (m_masterPassword.isEmpty())
        return;

    m_cardModel->load(m_salsa.get());
}

data_model_controller *view_model::cardController()
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

    m_salsa = std::make_shared<salsa20>(masterPassword.toStdString(), c_nonce);

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
