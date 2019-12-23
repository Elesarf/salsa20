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


card_type::card_type()
{

}

card_type::card_type(const QString &_name, const QString &_login, const QString &_pass) :
    m_name(_name),
    m_login(_login),
    m_pass(_pass)
{}

card_type::card_type(const QVariantMap &v_map) :
    m_name(v_map["name"].toString()),
    m_login(v_map["login"].toString()),
    m_pass(v_map["password"].toString())
{}

card_type::card_type(const QJsonObject &j_obj) :
    m_name(j_obj.value("name").toString()),
    m_login(j_obj.value("login").toString()),
    m_pass(j_obj.value("pass").toString())
{}

card_type::card_type(const card_type &other) : QObject(other.parent()),
    m_name(other.m_name),
    m_login(other.m_login),
    m_pass(other.m_pass)
{}

card_type &card_type::operator=(const card_type &other)
{
    m_name = other.m_name;
    m_login = other.m_login;
    m_pass = other.m_pass;

    return *this;
}

card_type::~card_type(){}

QVariantMap card_type::toVariant() const
{
    return
    {
        {"name", QVariant::fromValue(m_name)}
        , {"login", QVariant::fromValue(m_login)}
        , {"pass", QVariant::fromValue(m_pass)}
    };
}

QJsonObject card_type::toJSONObject() const
{
    return QJsonObject
    {
        {"name", m_name}
        , {"login", m_login}
        , {"pass", m_pass}
    };
}

QString card_type::name() const
{
    return m_name;
}

QString card_type::login() const
{
    return m_login;
}

void card_type::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
}

void card_type::setLogin(QString login)
{
    if (m_login == login)
        return;

    m_login = login;
}

void card_type::setPass(QString pass)
{
    if (m_pass == pass)
        return;

    m_pass = pass;
    emit passChanged(m_pass);
}

QString card_type::pass() const
{
    return m_pass;
}


card_model::card_model(QObject *parent) : QAbstractListModel(parent)
{}

card_model::~card_model()
{

}

int card_model::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;

    return m_data.size();
}

QVariant card_model::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
            return QVariant();

        switch (role)
        {
        case CardName:
            return QVariant::fromValue(m_data.at(index.row()).name());
        case Login:
            return QVariant::fromValue(m_data.at(index.row()).login());
        case Password:
            return QVariant::fromValue(m_data.at(index.row()).pass());
        default:
            return QVariant();
        }
}

QHash<int, QByteArray> card_model::roleNames() const
{
    return
     {
         {CardName, "cardName"},
         {Login, "cardLogin"},
         {Password, "cardPassword"}
     };
}

void card_model::add(const card_type &card)
{
    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.append(card);
    endInsertRows();
    QModelIndex index = createIndex(0, 0, static_cast<void *>(nullptr));
    emit dataChanged(index, index);
    emit countChanged(m_data.size());
}

QList<card_type> card_model::rawData() const
{
    return m_data;
}

int card_model::count() const
{
    return m_data.length();
}
