/******************************************************************************
 * Разработчик: Закрытое акционерное общество "Научно исследовательский       *
 * институт "Центрпрограммсистем", г. Тверь (ЗАО НИИ ЦПС)					  *
 *																			  *
 * Интеллектуальная собственность ЗАО НИИ ЦПС								  *
 ******************************************************************************/

/**
 * @file:	salsa_file_wrapper.cpp
 * @author:	А.В. Федченко
 * @date	2019.12.19
 */

#include <fstream>

#include "salsa20.h"

#include "salsa_file_wrapper.h"

salsa_file_wrapper::salsa_file_wrapper(){}
salsa_file_wrapper::~salsa_file_wrapper(){}

void salsa_file_wrapper::set_key_and_nonce(const std::string &key, const std::string &nonce)
{
    m_cryptoman = std::make_unique<salsa20>(key);
    m_cryptoman->set_nonce(nonce);
}

void salsa_file_wrapper::crypt_file(const std::string &in_file_name, const std::string &out_file_name)
{
    if (!m_cryptoman)
        throw std::runtime_error("create crypter firstly");

    std::ifstream input_file(in_file_name);
    if (!input_file.is_open())
        throw std::runtime_error("input file not open");

    input_file.seekg (0, std::ios::end);
    long file_length = input_file.tellg();
    input_file.seekg (0, std::ios::beg);

    std::ofstream out_file(out_file_name);
    if (!out_file.is_open())
        throw std::runtime_error("output file not open");


    salsa20::block_array file_block;
    auto tail_size = static_cast<uint32_t>(file_length) % file_block.size();

    while (input_file.good())
    {
        file_block.fill(0x0);

        input_file.read(reinterpret_cast<char *>(&file_block[0]), file_block.size());

        auto crypt = m_cryptoman->process_block(file_block);

        if (input_file.good())
        {
            for (const auto &v:crypt)
                out_file.put(static_cast<char>(v));
        }
        else
        {
            for (size_t i = 0; i < tail_size; ++i)
                out_file.put(static_cast<char>(crypt.at(i)));
        }
    }

    input_file.close();
    out_file.close();
}
