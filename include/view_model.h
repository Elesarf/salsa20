/******************************************************************************
 * Разработчик: Закрытое акционерное общество "Научно исследовательский       *
 * институт "Центрпрограммсистем", г. Тверь (ЗАО НИИ ЦПС)					  *
 *																			  *
 * Интеллектуальная собственность ЗАО НИИ ЦПС								  *
 ******************************************************************************/

/**
 * @file:	/include/view_model.h
 * @author:	А.В. Федченко
 * @date	2019.12.23
 */

#ifndef VIEW_MODEL_H
#define VIEW_MODEL_H

#include <memory>

#include <QObject>
#include <QList>

class data_model_controller;
class salsa20;
class view_model : public QObject
{
    Q_OBJECT

public:
    Q_PROPERTY(QString masterPassword READ masterPassword WRITE setMasterPassword NOTIFY masterPasswordChanged)
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(bool readyToWork READ readyToWork WRITE setReadyToWork NOTIFY readyToWorkChanged)
    Q_PROPERTY(data_model_controller *cardController READ cardController CONSTANT)

    explicit view_model(QObject *parent = nullptr);
    ~view_model();

    QString masterPassword() const;
    QString fileName() const;

    data_model_controller* cardController();
    bool readyToWork() const;

    Q_INVOKABLE void save();
    Q_INVOKABLE void load();

public slots:
    void setMasterPassword(QString masterPassword);
    void setReadyToWork(bool readyToWork);
    void setFileName(QString fileName);

signals:
    void masterPasswordChanged(QString masterPassword);
    void readyToWorkChanged(bool readyToWork);
    void fileNameChanged(QString fileName);

private:
    QString m_masterPassword;
    bool m_readyToWork;

    std::shared_ptr<salsa20> m_salsa;
    QString m_fileName;
    data_model_controller* m_cardModel;
};


#endif // VIEW_MODEL_H
