/******************************************************************************
 * Разработчик: Закрытое акционерное общество "Научно исследовательский       *
 * институт "Центрпрограммсистем", г. Тверь (ЗАО НИИ ЦПС)                   *
 *                                                                            *
 * Интеллектуальная собственность ЗАО НИИ ЦПС                               *
 ******************************************************************************/

/**
 * @file:   src/data_model.cpp
 * @author: А.В. Федченко
 * @date    2019.12.23
 */

#include "data_model.h"
#include <QDebug>

card_model::card_model(QObject *parent) : QAbstractListModel(parent)
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
    if(!index.isValid() || index.row() > m_data.size())
        return QVariant();

    const auto item = m_data.at(index.row());

    switch (role)
    {
    case CardName:
        return QVariant::fromValue(item.name);
    case Login:
        return QVariant::fromValue(item.login);
    case Password:
        return QVariant::fromValue(item.pass);
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

bool card_model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() > m_data.size())
        return false;

    auto row = index.row();

    switch (role)
    {
    case CardName:
        m_data[row].name = value.toString();
        break;
    case Login:
        m_data[row].login = value.toString();
        break;
    case Password:
        m_data[row].pass = value.toString();
        break;
    }

    emit dataChanged(index, index, {role});
    return true;
}

bool card_model::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    for (int i = (row + count - 1); i >= row; i-- )
        m_data.removeAt(i);
    endRemoveRows();
    return true;
}

bool card_model::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    for ( int i = row; i < (row + count - 1); i++ )
        m_data.append({"", "", ""});
    endInsertRows();
    return true;
}

void card_model::add()
{
    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.append(card_type());
    endInsertRows();
}

void card_model::clear()
{
    beginResetModel();
    m_data.clear();
    endResetModel();
}

QList<card_model::card_type> card_model::rawData() const
{
    return m_data;
}

bool card_model::fromVariantList(const QVariantList &list)
{
    beginResetModel();

    for (const auto &item : list)
        m_data.append(card_type(item.toMap()));

    endResetModel();
    return true;
}

QVariantList card_model::toVariantList() const
{
    QVariantList list;

    for (const auto &item : m_data)
        list.append(item.toVariant());

    return list;
}
