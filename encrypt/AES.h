#ifndef SIMPLE_PASSWORD_MANAGER_AESENCRYPTOR_H
#define SIMPLE_PASSWORD_MANAGER_AESENCRYPTOR_H

#include <cstring>
#include <string>
#include <vector>

#include "KeySchedule128.h"
#include "LUT.h"

class AES
{
protected:
    static const int numRows {4};
    static const int Nb {4};
    unsigned char state[numRows][Nb];

    // Functions used in the Rijndael cipher
    void byteSub();
    void shiftRow();
    void mixColumns();

    std::string cvtStateToStr();
    void cvtStrToState(std::string plain);

    virtual void addRoundKey(unsigned char* key, int round) = 0;
    virtual void cvtStrToKey(std::string in) = 0;
    virtual void finalRound(int round) = 0;
    virtual void round(int round) = 0;

public:
    virtual std::string cipher(std::string plainText, std::string keyIn) = 0;

};

#endif //SIMPLE_PASSWORD_MANAGER_AESENCRYPTOR_H
