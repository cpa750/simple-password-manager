#include "Decrypt.h"

State cvtStringToState(std::string in)
{
    State out;
    int row {0};
    int col{0};
    for (int i{0}; i < 16; ++i)
    {
        out[row++][col] = static_cast<u_char>(in[i]);
        if ((i+1) % 4 == 0) ++col;
    }
    return out;
}


// TODO: change the parameters so invCBC and CBC take the same types
std::string invCBC(std::string in, std::string& key,
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

    std::vector<State> states = cvtStrToStates(in);

    std::array<u_char, 176> keyIn;
    for (int i{0}; i < key.size(); ++i)
    {
        keyIn[i] = static_cast<u_char>(key[i]);
    }

    int iters {0};

    for (int i{0}; i < states.size(); ++i)
    {
        if (iters > 0)
        {
            for (int a{0}; a < states.size(); ++a)
            {
                toXor[a] = static_cast<unsigned char>(states[a]);
            }
        }
    }
        State out;
        switch (encryptionType)
        {
            case aes128:
            {
                AES128 aes;
                out = aes.invCipher(cvtStringToState(block), keyIn);
                for (int j {0}; j < 16; ++j)
                {
                    int row{0};
                    int col{0};
                    temp[j] = static_cast<unsigned char>(out[row++][col]);
                    if ((j+1) % 4 == 0) ++col;
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
            res += static_cast<char>(temp[k]);
        }
        ++iters;
    }
    return res;
}
