/******************************************************************************
 * Разработчик: Закрытое акционерное общество "Научно исследовательский       *
 * институт "Центрпрограммсистем", г. Тверь (ЗАО НИИ ЦПС)					  *
 *																			  *
 * Интеллектуальная собственность ЗАО НИИ ЦПС								  *
 ******************************************************************************/

/**
 * @file:	src/data_model.cpp
 * @author:	А.В. Федченко
 * @date	2019.12.23
 */

#include "data_model.h"


data_model::data_model()
{

}

data_model::data_model(const QString &_name, const QString &_login, const QString &_pass) :
    m_name(_name),
    m_login(_login),
    m_password(_pass)
{}

data_model::data_model(const QVariantMap &v_map) :
    m_name(v_map["name"].toString()),
    m_login(v_map["login"].toString()),
    m_password(v_map["password"].toString())
{}

data_model::data_model(const QJsonObject &j_obj) :
    m_name(j_obj.value("name").toString()),
    m_login(j_obj.value("login").toString()),
    m_password(j_obj.value("pass").toString())
{}

data_model::data_model(const data_model &other) :
    m_name(other.m_name),
    m_login(other.m_login),
    m_password(other.m_password)
{}

data_model &data_model::operator=(const data_model &other)
{
    m_name = other.m_name;
    m_login = other.m_login;
    m_password = other.m_password;

    return *this;
}

data_model::~data_model(){}

QVariantMap data_model::toVariant() const
{
    return
    {
        {"name", QVariant::fromValue(m_name)}
        , {"login", QVariant::fromValue(m_login)}
        , {"pass", QVariant::fromValue(m_password)}
    };
}

QJsonObject data_model::toJSONObject() const
{
    return QJsonObject
    {
        {"name", m_name}
        , {"login", m_login}
        , {"pass", m_password}
    };
}

QString data_model::name() const
{
    return m_name;
}

QString data_model::login() const
{
    return m_login;
}

QString data_model::password() const
{
    return m_password;
}

void data_model::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
}

void data_model::setLogin(QString login)
{
    if (m_login == login)
        return;

    m_login = login;
}

void data_model::setPassword(QString password)
{
    if (m_password == password)
        return;

    m_password = password;
}
