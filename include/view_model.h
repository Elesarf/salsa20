/**
 * @file:	/include/view_model.h
 * @author:	А.В. Федченко
 * @date	2019.12.23
 */

#ifndef VIEW_MODEL_H
#define VIEW_MODEL_H

#include <QSharedPointer>

#include <QObject>
#include <QList>

class dataModelController;
class salsa20;
class view_model : public QObject
{
    Q_OBJECT

public:
    Q_PROPERTY(QString masterPassword READ masterPassword WRITE setMasterPassword NOTIFY masterPasswordChanged)
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(bool readyToWork READ readyToWork WRITE setReadyToWork NOTIFY readyToWorkChanged)
    Q_PROPERTY(dataModelController *cardController READ cardController CONSTANT)

    explicit view_model(QObject *parent = nullptr);
    ~view_model();

    QString masterPassword() const;
    QString fileName() const;

    dataModelController* cardController();
    bool readyToWork() const;

    Q_INVOKABLE void save();
    Q_INVOKABLE bool load();

    Q_INVOKABLE bool exportData(const QUrl &) const;
    Q_INVOKABLE bool importData(const QUrl &);

public slots:
    void setMasterPassword(QString masterPassword);
    void setReadyToWork(bool readyToWork);
    void setFileName(QString fileName);

signals:
    void masterPasswordChanged(QString masterPassword);
    void readyToWorkChanged(bool readyToWork);
    void fileNameChanged(QString fileName);

#ifdef ANDROID
private:
    bool checkPermission();
#endif

private:
    QString m_masterPassword;
    bool m_readyToWork;

    QSharedPointer<salsa20> m_salsa;
    QString m_fileName;
    dataModelController* m_cardModel;
};


#endif // VIEW_MODEL_H
