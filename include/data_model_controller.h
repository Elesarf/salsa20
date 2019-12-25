/******************************************************************************
 * Разработчик: Закрытое акционерное общество "Научно исследовательский       *
 * институт "Центрпрограммсистем", г. Тверь (ЗАО НИИ ЦПС)					  *
 *																			  *
 * Интеллектуальная собственность ЗАО НИИ ЦПС								  *
 ******************************************************************************/

/**
 * @file:	include/data_model_controller.h
 * @author:	А.В. Федченко
 * @date	2019.12.24
 */

#ifndef DATA_MODEL_CONTROLLER_H
#define DATA_MODEL_CONTROLLER_H

#include <QSharedPointer>
#include <QObject>
#include "data_model.h"

class salsa20;
class dataModelController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(cardModel *modelData READ modelData CONSTANT)
    Q_PROPERTY(int size READ size NOTIFY sizeChanged)

public:
    explicit dataModelController(QObject *parent = nullptr);
    int size() const;

    Q_INVOKABLE cardModel *modelData();

    Q_INVOKABLE void clear();
    Q_INVOKABLE void add();

    Q_INVOKABLE bool save(QSharedPointer<salsa20> salsa = QSharedPointer<salsa20>(nullptr));
    Q_INVOKABLE bool load(QSharedPointer<salsa20> salsa = QSharedPointer<salsa20>(nullptr));
    Q_INVOKABLE bool isDataFileAvailable() const;

signals:
    void sizeChanged(int size);

private:
    int m_size;
    cardModel *m_model;

    QString m_path;
    QString m_fileName;
};

#endif // DATA_MODEL_CONTROLLER_H
