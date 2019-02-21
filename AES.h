#ifndef SIMPLE_PASSWORD_MANAGER_AESENCRYPTOR_H
#define SIMPLE_PASSWORD_MANAGER_AESENCRYPTOR_H

#include <string>
#include <vector>

#include "KeySchedule.h"
#include "SBox.h"

#include "GaloisField.h"
#include "GaloisFieldElement.h"
#include "GaloisFieldPolynomial.h"

class AES
{
protected:
    static const int numRows {4};
    static const int Nb {4};
    const static int keySize;
    const static int Nr;

    unsigned char state[numRows][Nb];

    // Functions used in the Rijndael cipher
    void byteSub(unsigned char* state[numRows][Nb]);
    void shiftRow(unsigned char* state[numRows][Nb]);
    void mixColumns(unsigned char* state[numRows][Nb]);
    virtual void addRoundKey(unsigned char* state[numRows][Nb],
                     unsigned char* key, int round) = 0;

    virtual void round(unsigned char* state[numRows][Nb]) = 0;
    virtual void finalRound(unsigned char* state[numRows][Nb]) = 0;
    // TODO: Implement these

public:
    virtual void cipher() = 0;
    // TODO: change arguments/return type when needed

};

#endif //SIMPLE_PASSWORD_MANAGER_AESENCRYPTOR_H
