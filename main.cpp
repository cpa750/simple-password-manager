#include <iostream>
#include <string>

#include "encrypt/Encrypt.h"

int main()
{
    unsigned char a[4][4]
            {
                    {0x32, 0x88, 0x31, 0xe0},
                    {0x43, 0x5a, 0x31, 0x37},
                    {0xf6, 0x30, 0x98, 0x07},
                    {0xa8, 0x8d, 0xa2, 0x34}
            };
    unsigned char b[16]
            {
                    0x2b, 0x7e, 0x15, 0x16,
                    0x28, 0xae, 0xd2, 0xa6,
                    0xab, 0xf7, 0x15, 0x88,
                    0x09, 0xcf, 0x4f, 0x3c
            };

    std::string c, d;
    c = "this is a message that is longer than 16 bytes";
    d = c;
    AES128 aes;
    //aes.test128(c, d);
    std::cout << encrypt(c, d, aes128) << std::endl;
    return 0;
}
