/******************************************************************************
 * Разработчик: Закрытое акционерное общество "Научно исследовательский       *
 * институт "Центрпрограммсистем", г. Тверь (ЗАО НИИ ЦПС)					  *
 *																			  *
 * Интеллектуальная собственность ЗАО НИИ ЦПС								  *
 ******************************************************************************/

/**
 * @file:	src/json_parser.cpp
 * @author:	А.В. Федченко
 * @date	2019.12.23
 */

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QVector>

#include "data_model.h"

#include "json_parser.h"

QList<data_model> json_parser::load(const QString &file_name)
{
    QFile jsFile(file_name);
    if(!jsFile.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::runtime_error("JSONSaver: Error: Failed open test file");

    QJsonDocument jsDoc = QJsonDocument::fromJson(jsFile.readAll());
    jsFile.close();

    if(!jsDoc.isObject())
        throw std::runtime_error("JSONSaver: Error: bad JSON file");

    QJsonObject jsObj = jsDoc.object();
    QJsonValue jsVal = jsObj["data"];

    if(!jsVal.isArray())
        throw std::runtime_error("JSONSaver: Error: bad JSON file");

    QJsonArray jsArr = jsVal.toArray();

    QList<data_model> resultList;
    for(const auto o : jsArr)
    {
        if(!o.isObject())
            throw std::runtime_error("JSONSaver: Error: bad JSON file");

        resultList.append(data_model(o.toObject()));
    }

    return resultList;
}

void json_parser::save(const QString &file_name, const QList<data_model> &data)
{
    QFile json_file(file_name);
    if(!json_file.open(QIODevice::Append))
    {
        return;
    }

    QJsonArray js_array;

    for(const auto &o:data)
        js_array.append(o.toJSONObject());

    json_file.write(QJsonDocument(js_array).toJson(QJsonDocument::Indented));
    json_file.close();
}
