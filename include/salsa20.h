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
constexpr auto key_array_size = 16;
constexpr auto block_size = 64;
constexpr auto key_size = 32;
constexpr auto nonce_size = 8;
}

/**
 * @brief The salsa20 class
 *
 * implement salsa20 chipher (https://en.wikipedia.org/wiki/Salsa20)
 *
 * key_array structure:
 * [cons, key, key, key, cons,
 *  nonce, nonce, pos, pos
 *  cons, key, key, key, cons]
 *
 */
class salsa20
{
public:
    using block_array = std::array<uint8_t, sizes::block_size>;

    /**
     * @brief salsa20
     *
     * construct chipher with key and nonce
     * @param key
     * @param nonce
     */
    salsa20(const std::string &key, const std::string &nonce);

    ~salsa20();

    /**
     * @brief begin_crypt prepare chipher to process file
     */
    void begin_crypt();

    /**
     * @brief print_vector print key array values
     */
    void print_key_array() const;

    /**
     * @brief process_block encrypts data block
     * @return
     */
    block_array process_block(const block_array &);

private:

    /**
     * @brief generate_keystream generate new keystream sequence
     * @return new keystream
     */
    block_array generate_keystream();

    /**
     * @brief convert 32 bit number to array of 8 bit values
     * @param value
     * @return
     */
    std::array<uint8_t, sizeof (uint32_t)> convert(const uint32_t value);

    /**
     * @brief rotate rotate value around bit number
     * @param value
     * @param number_of_bits
     * @return
     */
    uint32_t rotate(const uint32_t value, const uint32_t number_of_bits);

    /**
     * @brief convert array of 8 bit values to 32 bit number
     * @return
     */
    uint32_t convert(const uint8_t *);

private:

    ///< key array member
    std::array<uint32_t, sizes::key_array_size> m_array;
};

#endif // SALSA20_H
