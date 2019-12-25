/******************************************************************************
 * Разработчик: Закрытое акционерное общество "Научно исследовательский       *
 * институт "Центрпрограммсистем", г. Тверь (ЗАО НИИ ЦПС)					  *
 *																			  *
 * Интеллектуальная собственность ЗАО НИИ ЦПС								  *
 ******************************************************************************/

/**
 * @file:	include/data_model.h
 * @author:	А.В. Федченко
 * @date	2019.12.23
 */

#ifndef DATA_MODEL_H
#define DATA_MODEL_H

#include <QObject>
#include <QJsonObject>
#include <QVariantMap>
#include <QAbstractListModel>

class cardModel: public QAbstractListModel
{
    Q_OBJECT

public:

    struct cardType
    {
        cardType(){}
        cardType(const QString &_name, const QString &_login, const QString &_pass) :
            name(_name),
            login(_login),
            pass(_pass)
        {}

        cardType(const QVariantMap &v_map) :
            name(v_map["name"].toString()),
            login(v_map["login"].toString()),
            pass(v_map["pass"].toString())
        {}

        cardType(const QJsonObject &j_obj) :
            name(j_obj.value("name").toString()),
            login(j_obj.value("login").toString()),
            pass(j_obj.value("pass").toString())
        {}

        QVariantMap toVariant() const
        {
            return
            {
                {"name", QVariant::fromValue(name)}
                , {"login", QVariant::fromValue(login)}
                , {"pass", QVariant::fromValue(pass)}
            };
        }

        QJsonObject toJSONObject() const
        {
            return QJsonObject
            {
                {"name", name}
                , {"login", login}
                , {"pass", pass}
            };
        }

        QString name;
        QString login;
        QString pass;
    };

    using CardList = QList<cardType>;

    explicit cardModel(QObject *parent = nullptr);

    enum logMessageRoles{
        CardName = Qt::UserRole + 1,
        Login,
        Password
    };

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    Q_INVOKABLE bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex()) override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Q_INVOKABLE void add();
    Q_INVOKABLE void clear();
    Q_INVOKABLE QList<cardType> rawData() const;

    bool fromVariantList(const QVariantList &list);
    QVariantList toVariantList() const;

private:
    CardList m_data;
};

#endif // DATA_MODEL_H
