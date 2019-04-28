#include <iostream>
#include <string>

#include  "encrypt/AES128.h"

int main()
{
    AES128 aes;

    State test_vec
            {
                    0x00, 0x44, 0x88, 0xcc,
                    0x11, 0x55, 0x99, 0xdd,
                    0x22, 0x66, 0xaa, 0xee,
                    0x33, 0x77, 0xbb, 0xff
            };

    std::array<u_char, 176> test_vec_key
            {
                    0x00, 0x01, 0x02, 0x03,
                    0x04, 0x05, 0x06, 0x07,
                    0x08, 0x09, 0x0a, 0x0b,
                    0x0c, 0x0d, 0x0e, 0x0f
            };

    State inv_test_vec
            {
                    0x69, 0x6a, 0xd8, 0x70,
                    0xc4, 0x7b, 0xcd, 0xb4,
                    0xe0, 0x04, 0xb7, 0xc5,
                    0xd8, 0x30, 0x80, 0x5a
            };

    State cipherTest = aes.cipher(test_vec, test_vec_key);
    State invCipherTest = aes.invCipher(inv_test_vec, test_vec_key);

    for (int i {0}; i < 4; ++i)
    {
        for (int j{0}; j < 4; ++j)
        {
            std::cout << std::hex << (int) cipherTest[i][j];
            if (j == 3) std::cout << '\n';
        }

    }

    std::cout << '\n';

    for (int i {0}; i < 4; ++i)
    {
        for (int j {0}; j < 4; ++j)
        {
            std::cout << std::hex << (int)invCipherTest[i][j];
            if (j == 3) std::cout << '\n';
        }
    }
    return 0;
}
