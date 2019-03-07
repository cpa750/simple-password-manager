#include "Decrypt.h"

std::string invCBC(stringVector& blocks, std::string& key,
                   std::string& initializationVector, EncryptionType encryptionType)
{
    /*
     * This function employs the CBC mode of operation
     * using AES to decrypt an arbitrary number of blocks.
     * See https://en.wikipedia.org/wiki
     * /Block_cipher_mode_of_operation#Cipher_Block_Chaining_(CBC)
     * for information on how this process works.
     */
    std::string res;
    unsigned char temp[16];
    unsigned char toXor[16];

    int iters {0};
    for (std::string block: blocks)
    {
        for (int a {0}; a < block.size(); ++a)
        {
            toXor[a] = static_cast<unsigned char>(block[a]);
        }
        std::string out;
        switch (encryptionType)
        {
            case aes128:
            {
                AES128 aes;
                out = aes.invCipher(block, key);
                for (int j {0}; j < 16; ++j)
                {
                    temp[j] = static_cast<unsigned char>(out[j]);
                }
            }
            break;
            case aes256: break;
            // TODO: Implement once AES256 is written
        }
        for (int k {0}; k < 16; ++k)
        {
            if (iters == 0)
            {
                temp[k] ^= static_cast<unsigned char>(initializationVector[k]);
            }
            else
            {
                temp[k] ^= toXor[k];
            }
            res += temp[k];
        }
        ++iters;
    }
    return res;
}
