#include <iostream>
#include <string>

#include "encrypt/AES128.h"
#include "encrypt/KeySchedule128.h"

int main()
{
    std::string plainText = "\u0011\"3DUfw\u0088\u0099ª»ÌÝîÿ";
    std::string plainKey = "0001020304050607";

    AES128 aes;
    std::string enc = aes.cipher(plainText, plainKey);
    std::cout << enc;
    return 0;
}
