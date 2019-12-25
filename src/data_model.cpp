/**
 * @file:   src/data_model.cpp
 * @author: А.В. Федченко
 * @date    2019.12.23
 */

#include "data_model.h"
#include <QDebug>

cardModel::cardModel(QObject *parent) : QAbstractListModel(parent) {}

int cardModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;

    return m_data.size();
}

QVariant cardModel::data(const QModelIndex &index, int role) const
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

QHash<int, QByteArray> cardModel::roleNames() const
{
    return
    {
        {CardName, "cardName"},
        {Login, "cardLogin"},
        {Password, "cardPassword"}
    };
}

bool cardModel::setData(const QModelIndex &index, const QVariant &value, int role)
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

bool cardModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    for (int i = (row + count - 1); i >= row; i-- )
        m_data.removeAt(i);
    endRemoveRows();
    return true;
}

bool cardModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    for ( int i = row; i < (row + count - 1); i++ )
        m_data.append(cardType{"Name", "Login", "Password"});
    endInsertRows();
    return true;
}

void cardModel::add()
{
    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.append(cardType{"Name", "Login", "Password"});
    endInsertRows();
}

void cardModel::clear()
{
    beginResetModel();
    m_data.clear();
    endResetModel();
}

QList<cardModel::cardType> cardModel::rawData() const
{
    return m_data;
}

bool cardModel::fromVariantList(const QVariantList &list)
{
    beginResetModel();

    for (const auto &item : list)
        m_data.append(cardType(item.toMap()));

    endResetModel();
    return true;
}

QVariantList cardModel::toVariantList() const
{
    QVariantList list;

    for (const auto &item : m_data)
        list.append(item.toVariant());

    return list;
}
