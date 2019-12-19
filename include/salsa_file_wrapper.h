/******************************************************************************
 * Разработчик: Закрытое акционерное общество "Научно исследовательский       *
 * институт "Центрпрограммсистем", г. Тверь (ЗАО НИИ ЦПС)					  *
 *																			  *
 * Интеллектуальная собственность ЗАО НИИ ЦПС								  *
 ******************************************************************************/

/**
 * @file:	salsa_file_wrapper.h
 * @author:	А.В. Федченко
 * @date	2019.12.19
 */

#ifndef SALSA_FILE_WRAPPER_H
#define SALSA_FILE_WRAPPER_H

#include <string>
#include <memory>

class salsa20;
class salsa_file_wrapper
{
public:
    salsa_file_wrapper();
    ~salsa_file_wrapper();

    void set_key_and_nonce(const std::string &key, const std::string &nonce);
    void crypt_file(const std::string &in_file, const std::string &out_file);

private:
    std::unique_ptr<salsa20> m_cryptoman;
};

#endif // SALSA_FILE_WRAPPER_H
