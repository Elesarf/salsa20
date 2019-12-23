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

#include "salsa20.h"
#include "data_model.h"

#include "json_parser.h"

#include <fstream>

QList<card_type> json_parser::load(const QString &file_name, std::shared_ptr<salsa20> salsa)
{
    QByteArray file_buffer;

    QFile jsFile(file_name);
    if(!jsFile.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::runtime_error("JSONSaver: Error: Failed open test file");

    if (!salsa)
    {
        file_buffer = jsFile.readAll();
    }
    else
    {
        salsa->begin_crypt();
        std::ifstream input_file(file_name.toStdString());
        salsa20::block_array file_block;
        QByteArray ba;
        input_file.seekg (0, std::ios::end);
        uint32_t file_length = static_cast<uint32_t>(input_file.tellg());
        auto tail_size = file_length % file_block.size();
        input_file.seekg (0, std::ios::beg);

        while (input_file.good())
        {
            // clear block buffer
            file_block.fill(0x0);

            // read next data block
            input_file.read(reinterpret_cast<char *>(&file_block[0]), file_block.size());

            // encrypt block
            auto crypt = salsa->process_block(file_block);

            // copy encrypt data to out file
            if (input_file.good())
            {
                for (const auto &v : crypt)
                    ba.append(static_cast<char>(v));

            }
            else
            {
                for (size_t i = 0; i < tail_size; ++i)
                    ba.append(static_cast<char>(crypt.at(i)));
            }
        }

        file_buffer = ba;
    }

    QJsonDocument jsDoc = QJsonDocument::fromJson(file_buffer);
    jsFile.close();

    if(!jsDoc.isObject())
        throw std::runtime_error("JSONSaver: Error: bad JSON file");

    QJsonObject jsObj = jsDoc.object();
    QJsonValue jsVal = jsObj["data"];

    if(!jsVal.isArray())
        throw std::runtime_error("JSONSaver: Error: bad JSON file");

    QJsonArray jsArr = jsVal.toArray();

    QList<card_type> resultList;
    for(const auto o : jsArr)
    {
        if(!o.isObject())
            throw std::runtime_error("JSONSaver: Error: bad JSON file");

        resultList.append(card_type(o.toObject()));
    }

    return resultList;
}

void json_parser::save(const QString &file_name, const QList<card_type> &data, std::shared_ptr<salsa20> salsa)
{
    QFile json_file(file_name);
    if(!json_file.open(QIODevice::Append))
    {
        return;
    }

    QJsonArray js_array;

    for(const auto &o:data)
        js_array.append(o.toJSONObject());

    QJsonObject jsObj;
    jsObj["data"] = js_array;
    QJsonDocument jsDoc(jsObj);

    auto file_buffer = jsDoc.toJson(QJsonDocument::Indented);

    if (!salsa)
    {
        json_file.resize(0);
        json_file.write(file_buffer);
        json_file.close();
        return;
    }

    QByteArray encrypt_file_buffer;
    salsa->begin_crypt();
    salsa20::block_array block_buffer;
    quint32 byte_counter = 0;

    for (qint32 i = 0; i < file_buffer.size(); ++i)
    {
        if (byte_counter != block_buffer.size())
        {
            block_buffer[byte_counter] = static_cast<quint8>(file_buffer.at(i));
            ++byte_counter;
        }
        else
        {
            auto encrypt_block = salsa->process_block(block_buffer);

            for (quint32 j = 0; j < byte_counter; ++j)
                encrypt_file_buffer.append(static_cast<char>(encrypt_block.at(j)));

            block_buffer.fill(0x0);
            byte_counter = 0;
        }
    }

    if (byte_counter != 0)
    {
        auto encrypt_block = salsa->process_block(block_buffer);

        for (quint32 j = 0; j < byte_counter; ++j)
            encrypt_file_buffer.append(static_cast<char>(encrypt_block.at(j)));
    }

    json_file.resize(0);
    json_file.write(encrypt_file_buffer);
    json_file.close();
}
