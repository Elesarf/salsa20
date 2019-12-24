/******************************************************************************
 * Разработчик: Закрытое акционерное общество "Научно исследовательский       *
 * институт "Центрпрограммсистем", г. Тверь (ЗАО НИИ ЦПС)                   *
 *                                                                            *
 * Интеллектуальная собственность ЗАО НИИ ЦПС                               *
 ******************************************************************************/

/**
 * @file:   src/data_model_controller.cpp
 * @author: А.В. Федченко
 * @date    2019.12.24
 */

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QVector>
#include <QDebug>
#include <fstream>

#include "salsa20.h"

#include "../include/data_model_controller.h"

data_model_controller::data_model_controller(QObject *parent) : QObject(parent),
    m_model(new card_model())
{
}

int data_model_controller::size() const
{
    return m_size;
}

card_model *data_model_controller::modelData()
{
    return m_model;
}

void data_model_controller::clear() {m_model->clear();}

void data_model_controller::add()
{
    m_model->add();
    emit sizeChanged(m_model->rowCount(QModelIndex()));
}

bool data_model_controller::save(salsa20 *salsa)
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/pc/";
    QString fileName = path + "data.json";

    QDir dir(path);

    if (!dir.exists())
    {
        dir.mkpath(path);
    }

    QFile json_file(fileName);
    if(!json_file.open(QIODevice::WriteOnly))
    {
        return false;
    }

    QJsonArray js_array;

    for(const auto &o : m_model->rawData())
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
        return true;
    }

    QByteArray encrypt_file_buffer;
    salsa->begin_crypt();
    salsa20::block_array block_buffer;
    quint32 byte_counter = 0;

    for (qint32 i = 0; i < file_buffer.size(); ++i)
    {
        if (byte_counter < block_buffer.size())
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
            --i;
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
    return true;
}

bool data_model_controller::load(salsa20 *salsa)
{
    QByteArray file_buffer;
    auto fileName = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/pc/data.json";

    QFile jsFile(fileName);
    if(!jsFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    if (!salsa)
    {
        file_buffer = jsFile.readAll();
    }
    else
    {
        salsa->begin_crypt();
        std::ifstream input_file(fileName.toStdString());
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
        return false;

    QJsonObject jsObj = jsDoc.object();
    QJsonValue jsVal = jsObj["data"];

    if(!jsVal.isArray())
        return false;

    QJsonArray jsArr = jsVal.toArray();

    m_model->fromVariantList(jsArr.toVariantList());
    return true;
}
