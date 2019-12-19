#include <iostream>
#include <fstream>
#include "salsa_file_wrapper.h"

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    std::string key("zxcvbnmasdfghjklqwertyuasdfgjkll");
    std::string none("qwertyui");

    salsa_file_wrapper sfw;
    sfw.set_key_and_nonce(key, none);
    sfw.crypt_file("./test_file", "./result");

    return 0;
}
