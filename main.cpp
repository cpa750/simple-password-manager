#include <iostream>
#include <string>

#include "encrypt/Decrypt.h"
#include "encrypt/Encrypt.h"

int main()
{
    unsigned char a[4][4]
            {
                    {0x69, 0x6a, 0xd8, 0x70},
                    {0xc4, 0x7b, 0xcd, 0xb4},
                    {0xe0, 0x04, 0xb7, 0xc5},
                    {0xd8, 0x30, 0x80, 0x5a}
            };
    unsigned char b[16]
            {
                    0x00, 0x01, 0x02, 0x03,
                    0x04, 0x05, 0x06, 0x07,
                    0x08, 0x09, 0x0a, 0x0b,
                    0x0c, 0x0d, 0x0e, 0x0f
            };

    std::string c, d;
    c = "hello00000000000";
    d = c;
    AES128 aes;
    std::string cipher = aes.cipher(c, d);
    aes.test128(c, d);
    std::string plain = aes.invCipher(cipher, d);
    std::cout << cipher << '\n' << plain;

    return 0;
}
