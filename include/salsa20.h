/******************************************************************************
 * Разработчик: Закрытое акционерное общество "Научно исследовательский       *
 * институт "Центрпрограммсистем", г. Тверь (ЗАО НИИ ЦПС)					  *
 *																			  *
 * Интеллектуальная собственность ЗАО НИИ ЦПС								  *
 ******************************************************************************/

/**
 * @file:	salsa20.h
 * @author:	А.В. Федченко
 * @date	2019.12.18
 */

#ifndef SALSA20_H
#define SALSA20_H

#include <cstdint>
#include <array>

namespace sizes
{
static constexpr auto vector_size = 16;
static constexpr auto block_size = 64;
static constexpr auto key_size = 32;
static constexpr auto nonce_value = 8;
}

class salsa20
{

public:
    using block_array = std::array<uint8_t, sizes::block_size>;

    salsa20() = delete;
    salsa20(salsa20 &&) = delete;
    salsa20(const salsa20 &) = delete;
    salsa20 &operator=(const salsa20 &) = delete;
    salsa20 &operator=(salsa20 &&) = delete;

    salsa20(const std::string &);
    ~salsa20();

    void set_nonce(const std::string &);
    void begin_crypt();
    void print_vector() const;

    block_array generate_keystream();
    block_array process_block(const block_array &);

private:
    std::array<uint8_t, sizeof (uint32_t)> convert(const uint32_t value);
    uint32_t rotate(const uint32_t value, const uint32_t number_of_bits);
    uint32_t convert(const uint8_t *);

    std::array<uint32_t, sizes::vector_size> m_array;
};

#endif // SALSA20_H
