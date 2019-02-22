#include <iostream>
#include <string>

#include "encrypt/Encrypt.h"

int main()
{
    std::string a = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77};
    a += "\u0088\u0099ª»ÌÝîÿ";
    std::string b = "\u0001\u0002\u0003\u0004\u0005\u0006\u0007\b\t\n\u000B\f\n\u000E\u000F";

    test128(a, b, aes128);

    return 0;
}
