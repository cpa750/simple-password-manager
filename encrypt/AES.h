#ifndef SIMPLE_PASSWORD_MANAGER_AES_H
#define SIMPLE_PASSWORD_MANAGER_AES_H

#include <cstring>
#include <string>
#include <vector>

#include "KeySchedule128.h"
#include "LUT.h"

class AES
{
protected:
    static const size_t numRows {4};
    static const size_t Nb {4};
    u_char state[numRows][Nb];

    // AES encryption functions
    void byteSub();
    void mixColumns();
    void shiftRow();

    // AES decryption funcions
    void invByteSub();
    void invShiftRow();
    void invMixColumn();

    // Helper functions
    std::string cvtStateToStr();
    void cvtStrToState(std::string plain);

    // Pure virtual functions
    virtual void addRoundKey(u_char* key, int round) = 0;
    virtual void cvtStrToKey(std::string in) = 0;
    virtual void finalRound(int round) = 0;
    virtual void round(int round) = 0;

    virtual void invRound(int round) = 0;
    virtual void invFinalRound(int round) = 0;

public:
    // Main encryption and decryption functions
    virtual std::string cipher(std::string plainText, std::string keyIn) = 0;
    virtual std::string invCipher(std::string plainText, std::string keyIn) = 0;

};

#endif //SIMPLE_PASSWORD_MANAGER_AES_H
