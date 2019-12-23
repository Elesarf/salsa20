/**
 * @file:   salsa_file_wrapper.cpp
 * @author: А.В. Федченко
 * @date    2019.12.19
 */

#include <fstream>
#include <iomanip>
#include <iostream>

#include "salsa20.h"

#include "salsa_file_wrapper.h"

salsa_file_wrapper::salsa_file_wrapper() {}
salsa_file_wrapper::~salsa_file_wrapper() {}

constexpr char c_nonce[] = "99990001";

void salsa_file_wrapper::set_key_and_nonce(const std::string &key)
{
    m_cryptoman = std::make_unique<salsa20>(key, c_nonce);
}

void salsa_file_wrapper::crypt_file(const std::string &in_file_name, const std::string &out_file_name, bool print_process)
{
    if (!m_cryptoman)
        throw std::runtime_error("create crypter firstly");

    std::ifstream input_file(in_file_name);
    if (!input_file.is_open())
        throw std::runtime_error("input file not open");

    std::ofstream out_file(out_file_name);
    if (!out_file.is_open())
        throw std::runtime_error("output file not open");

    // reset chiper
    m_cryptoman->begin_crypt();

    salsa20::block_array file_block;

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
        auto crypt = m_cryptoman->process_block(file_block);

        // copy encrypt data to out file
        if (input_file.good())
        {
            for (const auto &v : crypt)
                out_file.put(static_cast<char>(v));

            if (print_process)
                std::cout << "\r" << "progress: " << input_file.tellg() << " / " << file_length;
        }
        else
        {
            for (size_t i = 0; i < tail_size; ++i)
                out_file.put(static_cast<char>(crypt.at(i)));

            if (print_process)
                std::cout << "\rfinish" << std::string(50, ' ');
        }

    }

    // close files
    input_file.close();
    out_file.close();
}
