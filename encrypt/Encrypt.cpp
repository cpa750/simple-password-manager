#include "Encrypt.h"

// TODO: add functionality to encrypt multiple blocks using CBC

std::string CBC(stringVector& blocks, std::string& key,
                std::string& initializationVector, EncryptionType encryptionType)
{
    std::string res;
    std::string temp;
    for (int i{0}; i < blocks.size(); ++i)
    {
        std::string toXor;
        if (i == 0) toXor = initializationVector;
        else toXor = temp;
        /*
         * temp should never be assigned when it's null
         * as it will be set when the encrypption is
         * completed (below)
         */

        unsigned char a[16];
        unsigned char b[16];
        memcpy(a, blocks[i].c_str(), 16);
        memcpy(b, toXor.c_str(), 16);
        for (int j {0}; j < 16; ++j) a[j] ^= b[j];

        std::string in;
        for (int k {0}; k < 16; ++k) in.push_back(a[k]);
        /*
         * std::string doesn't accept u_chars in its constructor
         * hence this workaround
         */

        switch (encryptionType)
        {
            case aes128:
            {
                AES128 aes;
                temp = aes.cipher(in, key);
                res += temp;
            }
            case aes192:break;
            case aes256:break;
        }

    }
    return res;
}

stringVector cvtToBlocks(std::string& plainIn)
{
    std::vector<std::string> out;

    if (plainIn.size() <= 16)
    {
        plainIn = padBlock(plainIn);
        out.push_back(plainIn);
        return out;
    }
    /*
     * If the plaintext in is less than or equal to 16 characters,
     * pad it then add to the out vector, which is then returned.
     * It can be returned as there is no need for multiple blocks.
     */


    for (int i {0}; i < plainIn.size() / 16; ++i)
    {
        std::string sub = plainIn.substr(i*16, 16);
        /*
         * Generating a substring from the original.
         * i*16 gets the value to start value, which is every
         * 16th value of the original string.
         */
        if (sub.size() == 16) out.push_back(sub);
        else
        {
            sub = padBlock(sub);
            out.push_back(sub);
        }
    }

    return out;
}

std::string encrypt(std::string& plainIn, std::string& keyIn, EncryptionType encryptionType)
{
    std::string out;
    stringVector blocks {cvtToBlocks(plainIn)};
    /*
     * This function is intended to take raw user input, then
     * handle the entire encryption process
     */
    if (plainIn.empty())
    {
        std::cout << "Nothing to encrpyt, string empty" << std::endl;
        return "";
        // TODO: make this throw an actual exception
    }
    std::string iv {"aaaaaaaaaaaaaaaa"};
    out = CBC(blocks, keyIn, iv, encryptionType);
    // TODO: add functionality to use a randomized initialization vector
    // ^ this will have to be stored alongside the password

    return out;
}

std::string padBlock(std::string& plainIn)
{
    int remainder = static_cast<int>(plainIn.size() % 16);

    if (remainder == 0) return plainIn;

    std::string out;
    out = plainIn;

    int diff = 16 - out.size();

    for (int i {0}; i < diff; ++i) out += '0';

    return out;
}
