/******************************************************************************
 * Разработчик: Закрытое акционерное общество "Научно исследовательский       *
 * институт "Центрпрограммсистем", г. Тверь (ЗАО НИИ ЦПС)					  *
 *																			  *
 * Интеллектуальная собственность ЗАО НИИ ЦПС								  *
 ******************************************************************************/

/**
 * @file:	include/json_parser.h
 * @author:	А.В. Федченко
 * @date	2019.12.23
 */

#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <QList>

class data_model;
class json_parser
{
public:

    static QList<data_model> load(const QString &file_name);
    static void save(const QString &file_name, const QList<data_model> &data);
};

#endif // JSON_PARSER_H
