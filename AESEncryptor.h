#ifndef SIMPLE_PASSWORD_MANAGER_AESENCRYPTOR_H
#define SIMPLE_PASSWORD_MANAGER_AESENCRYPTOR_H

#include <string>
#include <vector>

#include "SBox.h"

#include "GaloisField.h"
#include "GaloisFieldElement.h"
#include "GaloisFieldPolynomial.h"

// TODO: Make this a base class which encryptor classes using different bit-counts inherit from
class AESEncryptor
{
private:
    static const int numRows {32};
    static const int Nb {4};
    static const int Nk {4};
    static const int Nr {10};
    unsigned char state[numRows][Nb];
    unsigned char cipherKey[numRows][Nk];

public:
    // Functions used in the Rijndael cipher
    void byteSub(unsigned char* state[numRows][Nb]);
    void shiftRow(unsigned char* state[numRows][Nb]);
    void mixColumns(unsigned char* state[numRows][Nb]);
    void addRoundKey(unsigned char* state[numRows][Nb]);
    /*
     * TODO: figure out how to implement the round key
     * as derived from the cipher key
     */

};

#endif //SIMPLE_PASSWORD_MANAGER_AESENCRYPTOR_H
