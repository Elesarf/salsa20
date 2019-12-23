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

#include <QObject>

class view_model : public QObject
{
    Q_OBJECT
public:
    explicit view_model(QObject *parent = nullptr);
    ~view_model();
};

#endif // VIEW_MODEL_H
