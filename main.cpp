#include <iostream>
#include <string>

#include "encrypt/Encrypt.h"

int main()
{
    std::string plainText = "\u0011\"3DUfw\u0088\u0099ª»ÌÝîÿ";
    std::string plainKey = "0001020304050607";

    std::string cipherText = encrypt(plainText, plainKey, aes128);
    std::cout << cipherText << std::endl;

    return 0;
}
