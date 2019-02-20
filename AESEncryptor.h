#ifndef SIMPLE_PASSWORD_MANAGER_AESENCRYPTOR_H
#define SIMPLE_PASSWORD_MANAGER_AESENCRYPTOR_H

#include <string>
#include <vector>

#include "SBox.h"

#include "GaloisField.h"
#include "GaloisFieldElement.h"
#include "GaloisFieldPolynomial.h"

class AESEncryptor
{
private:
    static const int numRows {32};
    static const int Nb {4};
    static const int Nk {4};
    static const int Nr {10};
    unsigned char state[numRows][Nb];
    unsigned char cipherKey[numRows][Nk];

    // Functions used in the Rijndael cipher
    void byteSub(unsigned char* state[numRows][Nb]);
    void shiftRow(unsigned char* state[numRows][Nb]);
    void mixColumns(unsigned char* state[numRows][Nb]);
    void addRoundKey(unsigned char* state[numRows][Nb]);

    void round(unsigned char* state[numRows][Nb]);
    void finalRound(unsigned char* state[numRows][Nb]);
    // TODO: Implemment these

public:
    // Put the cipher method here when the time comes

};

#endif //SIMPLE_PASSWORD_MANAGER_AESENCRYPTOR_H
