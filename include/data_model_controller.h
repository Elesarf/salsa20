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

#include <QObject>
#include "data_model.h"

class salsa20;
class data_model_controller : public QObject
{
    Q_OBJECT

    Q_PROPERTY(card_model *modelData READ modelData CONSTANT)
    Q_PROPERTY(int size READ size NOTIFY sizeChanged)

public:
    explicit data_model_controller(QObject *parent = nullptr);
    int size() const;

    Q_INVOKABLE card_model *modelData();

    Q_INVOKABLE void clear();
    Q_INVOKABLE void add();

    Q_INVOKABLE bool save(salsa20 *salsa = nullptr);
    Q_INVOKABLE bool load(salsa20 *salsa = nullptr);
    Q_INVOKABLE bool isDataFileAvailable() const;

signals:
    void sizeChanged(int size);

private:
    int m_size;
    card_model *m_model;

    QString m_path;
    QString m_fileName;
};

#endif // DATA_MODEL_CONTROLLER_H
