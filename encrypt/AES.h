#ifndef SIMPLE_PASSWORD_MANAGER_AES_H
#define SIMPLE_PASSWORD_MANAGER_AES_H

#include <array>
#include <string>
#include <vector>

#include "KeySchedule128.h"
#include "LUT.h"
#include "typedefs.h"

class AES
{
protected:
    static const size_t numRows {4};
    static const size_t Nb {4};
    State state;

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
    virtual void addRoundKey(std::array<u_char, 176>& key, int round) = 0;
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
