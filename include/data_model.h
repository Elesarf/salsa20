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

class card_type : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString login READ login WRITE setLogin NOTIFY loginChanged)
    Q_PROPERTY(QString pass READ pass WRITE setPass NOTIFY passChanged)

    card_type();
    card_type(const QString&, const QString&, const QString&);
    card_type(const QVariantMap &);
    card_type(const QJsonObject &);

    card_type(const card_type&);
    card_type &operator=(const card_type&);

    ~card_type();

    QVariantMap toVariant() const;
    QJsonObject toJSONObject() const;

    QString name() const;
    QString login() const;
    QString pass() const;

    void setName(QString name);
    void setLogin(QString login);

public slots:
    void setPass(QString pass);

signals:
    void nameChanged(QString name);
    void loginChanged(QString login);
    void passChanged(QString pass);

private:
    QString m_name;
    QString m_login;
    QString m_pass;
};

class card_model: public QAbstractListModel
{
    Q_OBJECT

public:
    Q_PROPERTY(int count READ count NOTIFY countChanged)

    explicit card_model(QObject *parent = nullptr);
    ~card_model() override;

    enum logMessageRoles{
        CardName = Qt::UserRole + 1,
        Login,
        Password
    };

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void add(const card_type&);
    Q_INVOKABLE void clear();
    Q_INVOKABLE QList<card_type> rawData() const;

    int count() const;

signals:
    void countChanged(int count);

private:
    QList<card_type> m_data;
};


// регистрация для Qt
#include <qmetatype.h>
Q_DECLARE_METATYPE(card_type);

#endif // DATA_MODEL_H
