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

#include <memory>

#include <QList>

class card_type;
class salsa20;
class json_parser
{
public:

    static QList<card_type> load(const QString &file_name, std::shared_ptr<salsa20> salsa = nullptr);
    static void save(const QString &file_name, const QList<card_type> &data, std::shared_ptr<salsa20> salsa = nullptr);
};

#endif // JSON_PARSER_H
