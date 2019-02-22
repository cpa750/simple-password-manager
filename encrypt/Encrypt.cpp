#include "Encrypt.h"

std::vector<std::string> cvtToBlocks(std::string& plainIn)
{
    std::vector<std::string> out;

    if (plainIn.size() <= 16)
    /*
     * If the plaintext in is less than or equal to 16 characters,
     * pad it then add to the out vector, which is then returned.
     * It can be returned as there is no need for multiple blocks.
     */
    {
        plainIn = padBlock(plainIn);
        out.push_back(plainIn);
        return out;
    }

    for (int i {0}; i < plainIn.size() % 16; ++i)
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
            out.push_back(padBlock(sub));
        }
    }

    return out;
}

std::string encrypt(std::string& plainIn, std::string& keyIn, EncryptionType encryptionType)
{
    std::string out;
    std::vector<std::string> blocks {cvtToBlocks(plainIn)};
    /*
     * This function is intended to take raw user input, then
     * handle the entire encryption process
     */
    switch (encryptionType)
    {
        case aes128:
        {
            AES128 aes;
            for (std::string& i: blocks) out += aes.cipher(i, keyIn);
        };
            break;
        case aes192:break;
        case aes256:break;
        // TODO: implement these when the classes are written
        default:
            std::cout << "Not a valid encryption type!";
    }

    return out;
}

std::string padBlock(std::string& plainIn)
{
    int remainder = static_cast<int>(plainIn.size() % 16);

    if (remainder == 0) return plainIn;

    std::string out;
    out = plainIn;

    for (int i {0}; i < remainder; ++i) out.push_back('0');

    return out;
}
