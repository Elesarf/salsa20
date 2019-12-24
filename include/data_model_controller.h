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

class data_model_controller : public QObject
{
    Q_OBJECT
public:
    explicit data_model_controller(QObject *parent = nullptr);

signals:

};

#endif // DATA_MODEL_CONTROLLER_H
