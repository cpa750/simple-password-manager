#ifndef SIMPLE_PASSWORD_MANAGER_AESENCRYPTOR_H
#define SIMPLE_PASSWORD_MANAGER_AESENCRYPTOR_H

#include "Encryptor.h"
#include "SBox.cpp"

#include "GaloisFieldElement.h"

class AESEncryptor : public Encryptor
{
private:
    static const int numRows {32};
    static const int Nb {4};
    static const int Nk {4};
    unsigned char state[numRows][Nb];
    unsigned char cipherKey[numRows][Nk];

    // Helper function used by the cipher
    unsigned char expandKey(unsigned char cipherKey, const int CKSize);

public:
    // Functions used in the Rijndael cipher
    void byteSub(unsigned char* state[numRows][Nb]);
    void shiftRow(unsigned char* state[numRows][Nb]);
    void mixColumn(unsigned char* state[numRows][Nb]);
    void addRoundKey(unsigned char* state[numRows][Nb]);
    /*
     * TODO: figure out how to implement the round key
     * as derived from the cipher key
     */

};

#endif //SIMPLE_PASSWORD_MANAGER_AESENCRYPTOR_H
