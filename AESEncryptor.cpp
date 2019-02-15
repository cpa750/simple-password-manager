#include "AESEncryptor.h"

void AESEncryptor::byteSub(unsigned char state[AESEncryptor::numRows][AESEncryptor::Nb])
{
    for (int i {0}; i < AESEncryptor::numRows; ++i)
    {
        for (int j {0}; j < AESEncryptor::Nb; ++j)
        {
            state[i][j] = SBox::LUT[state[i][j]];
        }
    }
}

void AESEncryptor::shiftRow(unsigned char state[AESEncryptor::numRows][AESEncryptor::Nb])
{
    for (int i {0}; i < AESEncryptor::numRows; ++i)
    {
        if (i == 0) continue; // prevent modulo by 0, also skipping first row according to AES
        else
        {
            unsigned char temp;
            for (int j {0}; j < AESEncryptor::Nb; ++j)
            {
                int newPos = (j - i) % AESEncryptor::Nb;
                temp = state[i][newPos];
                state[i][newPos] = state[i][j];
            }
        }
    }
    // TODO: Finish the implementation of this algorithm
}
