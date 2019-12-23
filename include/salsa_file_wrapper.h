/**
 * @file:   salsa_file_wrapper.h
 * @author: А.В. Федченко
 * @date    2019.12.19
 */

#ifndef SALSA_FILE_WRAPPER_H
#define SALSA_FILE_WRAPPER_H

#include <string>
#include <memory>

class salsa20;

/**
 * @brief The salsa_file_wrapper class provides api to encrypt file
 */
class salsa_file_wrapper
{
public:
    salsa_file_wrapper();
    ~salsa_file_wrapper();

    /**
     * @brief set_key_and_nonce initialize new chiper
     * @param key
     * @param nonce
     */
    void set_key_and_nonce(const std::string &key);

    /**
     * @brief crypt_file encrypt input file to output file
     * @param in_file
     * @param out_file
     */
    void crypt_file(const std::string &in_file, const std::string &out_file, bool print_process = false);

private:

    ///< chiper
    std::unique_ptr<salsa20> m_cryptoman;
};

#endif // SALSA_FILE_WRAPPER_H
