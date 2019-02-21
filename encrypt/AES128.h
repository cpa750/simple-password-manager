#ifndef SIMPLE_PASSWORD_MANAGER_AES128_H
#define SIMPLE_PASSWORD_MANAGER_AES128_H

#include "AES.h"

class AES128 : public AES
{
private:
    const static int keySize {176};
    const int Nr {10};
    unsigned char key[keySize];
    // TODO: Initialize this

    void addRoundKey(unsigned char* state[AES::numRows][AES::Nb],
                             unsigned char* key, int round) final;

    void round(unsigned char* state[AES::numRows][AES::Nb], int round) final;
    void finalRound(unsigned char* state[AES::numRows][AES::Nb], int round) final;

public:
    void cipher();

};

#endif //SIMPLE_PASSWORD_MANAGER_AES128_H
