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

dataModelController::dataModelController(QObject *parent) : QObject(parent),
    m_model(new cardModel()),
    m_path(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/sc/"),
    m_fileName("data.json")
{}

int dataModelController::size() const
{
    return m_size;
}

cardModel *dataModelController::modelData()
{
    return m_model;
}

void dataModelController::clear() {m_model->clear();}

void dataModelController::add()
{
    m_model->add();
    emit sizeChanged(m_model->rowCount(QModelIndex()));
}

bool dataModelController::save(QSharedPointer<salsa20> salsa)
{
    QDir dir(m_path);

    if (!dir.exists())
        dir.mkpath(m_path);

    QFile jsonFile(m_path + m_fileName);

    if(!jsonFile.open(QIODevice::WriteOnly))
        return false;

    QJsonArray jsArray;

    for(const auto &o : m_model->rawData())
        jsArray.append(o.toJSONObject());

    QJsonObject jsObj;
    jsObj["data"] = jsArray;
    QJsonDocument jsDoc(jsObj);

    auto fileBuffer = jsDoc.toJson(QJsonDocument::Indented);

    if (!salsa)
    {
        jsonFile.resize(0);
        jsonFile.write(fileBuffer);
        jsonFile.close();
        return true;
    }

    QByteArray encryptFileBuffer;
    salsa->begin_crypt();
    salsa20::block_array blockBuffer;
    quint32 byteCounter = 0;

    for (qint32 i = 0; i < fileBuffer.size(); ++i)
    {
        if (byteCounter < blockBuffer.size())
        {
            blockBuffer[byteCounter] = static_cast<quint8>(fileBuffer.at(i));
            ++byteCounter;
        }
        else
        {
            auto encrypt_block = salsa->process_block(blockBuffer);

            for (quint32 j = 0; j < byteCounter; ++j)
                encryptFileBuffer.append(static_cast<char>(encrypt_block.at(j)));

            blockBuffer.fill(0x0);
            byteCounter = 0;
            --i;
        }
    }

    if (byteCounter != 0)
    {
        auto encryptBlock = salsa->process_block(blockBuffer);

        for (quint32 j = 0; j < byteCounter; ++j)
            encryptFileBuffer.append(static_cast<char>(encryptBlock.at(j)));
    }

    jsonFile.resize(0);
    jsonFile.write(encryptFileBuffer);
    jsonFile.close();
    return true;
}

bool dataModelController::load(QSharedPointer<salsa20> salsa)
{
    QByteArray fileBuffer;
    auto fileName = m_path + m_fileName;

    QFile jsFile(fileName);
    if(!jsFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    if (!salsa)
    {
        fileBuffer = jsFile.readAll();
    }
    else
    {
        salsa->begin_crypt();
        std::ifstream inputFile(fileName.toStdString());
        salsa20::block_array fileBlock;
        QByteArray ba;

        inputFile.seekg (0, std::ios::end);
        uint32_t fileLength = static_cast<uint32_t>(inputFile.tellg());
        auto tailSize = fileLength % fileBlock.size();
        inputFile.seekg (0, std::ios::beg);

        while (inputFile.good())
        {
            // clear block buffer
            fileBlock.fill(0x0);

            // read next data block
            inputFile.read(reinterpret_cast<char *>(&fileBlock[0]), fileBlock.size());

            // encrypt block
            auto crypt = salsa->process_block(fileBlock);

            // copy encrypt data to out file
            if (inputFile.good())
            {
                for (const auto &v : crypt)
                    ba.append(static_cast<char>(v));

            }
            else
            {
                for (size_t i = 0; i < tailSize; ++i)
                    ba.append(static_cast<char>(crypt.at(i)));
            }
        }

        fileBuffer = ba;
    }

    QJsonDocument jsDoc = QJsonDocument::fromJson(fileBuffer);
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

bool dataModelController::isDataFileAvailable() const
{
    return QFile::exists(m_path + m_fileName);
}
