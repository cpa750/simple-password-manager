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

void AES128::round(unsigned char* state[AES::numRows][AES::Nb], int round)
{
    byteSub(state);
    shiftRow(state);
    mixColumns(state);
    addRoundKey(state, AES128::key, round);
}

void AES128::finalRound(unsigned char* state[AES::numRows][AES::Nb], int round)
{
    byteSub(state);
    shiftRow(state);
    addRoundKey(state, AES128::key, round);
}

void AES128::cipher()
{
    int round {0};
    //addRoundKey()
    // TODO: Finish implementation of this (must take a string and return a string)
}
