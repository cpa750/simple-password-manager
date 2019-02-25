#ifndef SIMPLE_PASSWORD_MANAGER_AES128_H
#define SIMPLE_PASSWORD_MANAGER_AES128_H

#include "AES.h"

class AES128 : public AES
{
private:
    const static size_t keySize {176};
    u_char key[keySize];
    const int Nr {9};

    // AES encryption functions
    void addRoundKey(u_char* key, int round) final;
    void cvtStrToKey(std::string in) final;
    void finalRound(int round) final;
    void round(int round) final;

    // AES decryption functions
    void invFinalRound(int round) final;
    void invRound(int round) final;

    // Debugging functions
    void printKey();
    void printState();
    void printHexOut();

public:
    std::string cipher(std::string plainText, std::string keyIn) final;
    std::string invCipher(std::string plainText, std::string keyIn) final;

    // Debugging functions
    void test128(u_char stateIn[numRows][Nb], u_char keyIn[keySize]);
    void test128(std::string plainText, std::string keyIn);

    void testInv128(u_char stateIn[numRows][Nb], u_char keyIn[keySize]);

};

#endif //SIMPLE_PASSWORD_MANAGER_AES128_H
