#ifndef SIMPLE_PASSWORD_MANAGER_AESENCRYPTOR_H
#define SIMPLE_PASSWORD_MANAGER_AESENCRYPTOR_H

#include "Encryptor.h"
#include "SBox.cpp"

class AESEncryptor : public Encryptor
{
private:
    static const int stateSize {128};
    static const  int CKSize {128};
    unsigned char State[stateSize];
    unsigned char cipherKey[128];
    unsigned char expandedKey;

    // Helper function used by the cipher
    unsigned char expandKey(unsigned char cipherKey, const int CKSize);

public:
    // Functions used in the Rijndael cipher
    void byteSub(unsigned char state[256]);
    void shiftRow(unsigned char state[256]);
    void mixColumn(unsigned char state[256]);
    void addRoundKey(unsigned char state[256]);
    /*
     * TODO: figure out how to implement the round key
     * as derived from the cipher key
     */

};


#endif //SIMPLE_PASSWORD_MANAGER_AESENCRYPTOR_H
