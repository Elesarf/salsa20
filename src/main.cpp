#include <iostream>
#include <getopt.h>

#include "salsa_file_wrapper.h"

constexpr char c_nonce[] = "99990001";
static void print_help();

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    std::string key;

    std::string in_file_name;
    std::string out_file_name;

    int c = 0;
    while ((c = getopt(argc, argv, "i:o:k:vh")) != -1)
    {
        switch (c)
        {
        case 'i': in_file_name = optarg;
            break;
        case 'o': out_file_name = optarg;
            break;
        case 'k': key = optarg;
            break;
        case 'v':
        case 'h':
            print_help();
            return 0;
        }
    }

    bool strings_is_ready = true;
    strings_is_ready &= !key.empty();
    strings_is_ready &= !in_file_name.empty();
    strings_is_ready &= !out_file_name.empty();

    if (strings_is_ready)
    {
        salsa_file_wrapper sfw;
        sfw.set_key_and_nonce(key, c_nonce);
        sfw.crypt_file(in_file_name, out_file_name, true);
    }
    else
    {
        print_help();
    }

    return 0;
}

static void print_help()
{
    std::cout << "Usage:" << std::endl;
    std::cout << "-i \"path\" input  file name" << std::endl;
    std::cout << "-o \"path\" output file name" << std::endl;
    std::cout << "-k \"\" key (basic 256 bit)" << std::endl;
    std::cout << "-h show this message." << std::endl;

    std::cout << "example: salsa -i ./some_input_file -o ./some_output_encrypted_file -k my_strong_key" << std::endl;
}
