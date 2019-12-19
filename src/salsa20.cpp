/**
 * @file:   salsa20.cpp
 * @author: А.В. Федченко
 * @date    2019.12.18
 */

#include <iostream>

#include "salsa20.h"

// some need strong constants, but not me.
constexpr uint8_t constants[] = "quack constant!!";

salsa20::salsa20(const std::string &key, const std::string &nonce)
{
    /* if key size is not same sizes::key_size
     * copy part of key, or all key bytes and fill other by 0x0
     */
    std::array<uint8_t, sizes::key_size> key_array;
    key_array.fill(0x0);
    std::copy(key.begin(), key.begin() + key_array.size(), key_array.data());

    std::array<uint8_t, sizes::nonce_size> nonce_array;
    nonce_array.fill(0x0);
    std::copy(nonce.begin(), nonce.begin() + nonce_array.size(), nonce_array.data());

    m_array.fill(0x0);

    // initial state of array
    m_array[0] = convert(&constants[0]);
    m_array[1] = convert(&key_array[0]);
    m_array[2] = convert(&key_array[4]);
    m_array[3] = convert(&key_array[8]);
    m_array[4] = convert(&key_array[12]);
    m_array[5] = convert(&constants[4]);

    m_array[6] = convert(&nonce_array[0]);
    m_array[7] = convert(&nonce_array[sizeof (uint32_t)]);

    m_array[10] = convert(&constants[8]);
    m_array[11] = convert(&key_array[16]);
    m_array[12] = convert(&key_array[20]);
    m_array[13] = convert(&key_array[24]);
    m_array[14] = convert(&key_array[28]);
    m_array[15] = convert(&constants[12]);
}

salsa20::~salsa20() {}

void salsa20::begin_crypt()
{
    m_array[8] = 0;
    m_array[9] = 0;
}

void salsa20::print_key_array() const
{
    for (const auto &v : m_array)
        std::cout << v << " ";
    std::cout << std::endl;
}

salsa20::block_array salsa20::generate_keystream()
{
    auto x = m_array;

    for (size_t i = 20; i > 0; i -= 2)
    {
        x[4 ] ^= rotate(static_cast<uint32_t>(x[0 ] + x[12]), 7);
        x[8 ] ^= rotate(static_cast<uint32_t>(x[4 ] + x[0 ]), 9);
        x[12] ^= rotate(static_cast<uint32_t>(x[8 ] + x[4 ]), 13);
        x[0 ] ^= rotate(static_cast<uint32_t>(x[12] + x[8 ]), 18);

        x[9 ] ^= rotate(static_cast<uint32_t>(x[5 ] + x[1 ]), 7);
        x[13] ^= rotate(static_cast<uint32_t>(x[9 ] + x[5 ]), 9);
        x[1 ] ^= rotate(static_cast<uint32_t>(x[13] + x[9 ]), 13);
        x[5 ] ^= rotate(static_cast<uint32_t>(x[1 ] + x[13]), 18);

        x[14] ^= rotate(static_cast<uint32_t>(x[10] + x[6 ]), 7);
        x[2 ] ^= rotate(static_cast<uint32_t>(x[14] + x[10]), 9);
        x[6 ] ^= rotate(static_cast<uint32_t>(x[2 ] + x[14]), 13);
        x[10] ^= rotate(static_cast<uint32_t>(x[6 ] + x[2 ]), 18);

        x[3 ] ^= rotate(static_cast<uint32_t>(x[15] + x[11]), 7);
        x[7 ] ^= rotate(static_cast<uint32_t>(x[3 ] + x[15]), 9);
        x[11] ^= rotate(static_cast<uint32_t>(x[7 ] + x[3 ]), 13);
        x[15] ^= rotate(static_cast<uint32_t>(x[11] + x[7 ]), 18);

        x[1 ] ^= rotate(static_cast<uint32_t>(x[0 ] + x[3 ]), 7);
        x[2 ] ^= rotate(static_cast<uint32_t>(x[1 ] + x[0 ]), 9);
        x[3 ] ^= rotate(static_cast<uint32_t>(x[2 ] + x[1 ]), 13);
        x[0 ] ^= rotate(static_cast<uint32_t>(x[3 ] + x[2 ]), 18);

        x[6 ] ^= rotate(static_cast<uint32_t>(x[5 ] + x[4 ]), 7);
        x[7 ] ^= rotate(static_cast<uint32_t>(x[6 ] + x[5 ]), 9);
        x[4 ] ^= rotate(static_cast<uint32_t>(x[7 ] + x[6 ]), 13);
        x[5 ] ^= rotate(static_cast<uint32_t>(x[4 ] + x[7 ]), 18);

        x[11] ^= rotate(static_cast<uint32_t>(x[10] + x[9 ]), 7);
        x[8 ] ^= rotate(static_cast<uint32_t>(x[11] + x[10]), 9);
        x[9 ] ^= rotate(static_cast<uint32_t>(x[8 ] + x[11]), 13);
        x[10] ^= rotate(static_cast<uint32_t>(x[9 ] + x[8 ]), 18);

        x[12] ^= rotate(static_cast<uint32_t>(x[15] + x[14]), 7);
        x[13] ^= rotate(static_cast<uint32_t>(x[12] + x[15]), 9);
        x[14] ^= rotate(static_cast<uint32_t>(x[13] + x[12]), 13);
        x[15] ^= rotate(static_cast<uint32_t>(x[14] + x[13]), 18);
    }

    std::array<uint8_t, sizes::block_size> result;
    result.fill(0x0);

    for (size_t i = 0; i < sizes::key_array_size; ++i)
    {
        x[i] += m_array[i];

        auto converted = convert(x[i]);
        auto result_start_index = i * sizeof (uint32_t);

        std::copy(converted.begin(), converted.end(), result.begin() + result_start_index);
    }

    auto position = reinterpret_cast<uint64_t *>(&m_array[8]);

    // ++*position - beeeee
    *position = *position + 1;

    return result;
}

std::array<uint8_t, sizeof (uint32_t)> salsa20::convert(const uint32_t value)
{
    return
    {
        static_cast<uint8_t>(value >> 0),
        static_cast<uint8_t>(value >> 8),
        static_cast<uint8_t>(value >> 16),
        static_cast<uint8_t>(value >> 24)
    };
}

salsa20::block_array salsa20::process_block(const salsa20::block_array &input_array)
{
    auto keystream = generate_keystream();

    block_array crypt_block;
    crypt_block.fill(0x0);

    for (size_t i = 0; i < sizes::block_size; ++i)
        crypt_block[i] = keystream.at(i) ^ input_array.at(i);

    return crypt_block;
}

uint32_t salsa20::rotate(const uint32_t value, const uint32_t number_of_bits)
{
    return (value << number_of_bits) | (value >> (sizeof (uint32_t) - number_of_bits));
}

uint32_t salsa20::convert(const uint8_t *array_to_convert)
{
    return ((static_cast<uint32_t>(array_to_convert[0]) << 0) |
            (static_cast<uint32_t>(array_to_convert[1]) << 8) |
            (static_cast<uint32_t>(array_to_convert[2]) << 16) |
            (static_cast<uint32_t>(array_to_convert[3]) << 24));
}
