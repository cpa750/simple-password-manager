#ifndef SIMPLE_PASSWORD_MANAGER_AES128_H
#define SIMPLE_PASSWORD_MANAGER_AES128_H

#include "AES.h"

class AES128 : public AES
{
private:
    const static size_t keySize {176};
    std::array<u_char, keySize> key;
    const int Nr {10};

    // AES encryption functions
    void addRoundKey(std::array<u_char, 176>& key, int round) final;
    void finalRound(int round) final;
    void round(int round) final;

    // AES decryption functions
    void invFinalRound(int round) final;
    void invRound(int round) final;

public:
    State cipher(State state, std::array<u_char, 176> keyIn) final;
    State invCipher(State state, std::array<u_char, 176> keyIn) final;

    void printState();
    void printKey();
};

#endif //SIMPLE_PASSWORD_MANAGER_AES128_H
