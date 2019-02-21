#include "AES128.h"

void AES128::addRoundKey(unsigned char* state[AES::numRows][AES::Nb],
                      unsigned char* key, int round)
{
    for (int i {0}; i < AES::numRows; ++i)
    {
        for (int j {0}; j < AES::Nb; ++j)
        {
            *state[i][j] ^= key[round * 4 * AES::Nb + i * AES::Nb + j];
            /*
             * This element access arithmetic ensures that the key elements accessed
             * for each round and each element in the state are unique
             */
        }
    }
}

void AES128::round(unsigned char* state[AES::numRows][AES::Nb])
{
    // TODO: Implement this
}

void AES128::finalRound(unsigned char* state[AES::numRows][AES::Nb])
{
    // TODO: Implement this
}
