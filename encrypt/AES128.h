#ifndef SIMPLE_PASSWORD_MANAGER_AES128_H
#define SIMPLE_PASSWORD_MANAGER_AES128_H

#include "AES.h"

class AES128 : public AES
{
private:
    const static int keySize {176};
    unsigned char key[keySize];
    const int Nr {10};

    void addRoundKey(unsigned char* key, int round) final;
    void cvtStrToKey(std::string in) final;
    void finalRound(int round) final;
    void round(int round) final;


public:
    std::string cipher(std::string plainText, std::string keyIn) final;

};

#endif //SIMPLE_PASSWORD_MANAGER_AES128_H
