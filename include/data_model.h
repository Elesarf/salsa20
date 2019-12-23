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

struct data_model
{
    Q_GADGET
public:
    data_model();
    data_model(const QString&, const QString&, const QString&);
    data_model(const QVariantMap &);
    data_model(const QJsonObject &);

    data_model(const data_model&);
    data_model &operator=(const data_model&);

    ~data_model();

    QVariantMap toVariant() const;
    QJsonObject toJSONObject() const;

    QString name() const;
    QString login() const;
    QString password() const;

    void setName(QString name);
    void setLogin(QString login);
    void setPassword(QString password);

private:
    QString m_name;
    QString m_login;
    QString m_password;
};

// регистрация для Qt
#include <qmetatype.h>
Q_DECLARE_METATYPE(data_model);

#endif // DATA_MODEL_H
