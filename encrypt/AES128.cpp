#include "AES128.h"

//================= AES encryption functions =================//

void AES128::addRoundKey(unsigned char* key, int round)
{
    for (int i {0}; i < numRows; ++i)
    {
        for (int j{0}; j < Nb; ++j)
        {
            state[j][i] ^= key[round * 4 * Nb + i * Nb + j];
            /*
             * This element access arithmetic ensures that the key elements accessed
             * for each round and each element in the state are unique
             */
        }
    }
}

std::string AES128::cipher(std::string plainText, std::string keyIn)
{
    std::string res;
    cvtStrToKey(keyIn);
    cvtStrToState(plainText);

    KeySchedule128 ks;
    ks.expandKey(key);

    int roundNum {0};
    addRoundKey(key, roundNum);
    while (roundNum < Nr)
    {
        round(++roundNum);
    }
    finalRound(roundNum+1);

    res = cvtStateToStr();
    return res;
}


void AES128::cvtStrToKey(std::string plain)
{
    memcpy(key, plain.c_str(), 16);
    /*
     * Key string must be 16 chars long.
     * This class does not ensure that this is the case,
     * nor does it ensure that the key is padded correctly.
     */
}

void AES128::finalRound(int round)
{
    byteSub();
    shiftRow();
    addRoundKey(key, round);
}

void AES128::round(int round)
{
    byteSub();
    shiftRow();
    mixColumns();
    addRoundKey(key, round);
}

//================= AES decryption functions =================//

std::string AES128::invCipher(std::string plainText, std::string keyIn)
{
    std::string res;
    cvtStrToKey(keyIn);
    cvtStrToState(plainText);

    KeySchedule128 ks;
    ks.expandKey(key);

    int roundNum {Nr + 1};
    addRoundKey(key, roundNum);
    while (roundNum > 1)
    {
        round(--roundNum);
    }
    finalRound(--roundNum);

    res = cvtStateToStr();
    return res;
}

void AES128::invFinalRound(int round)
{
    invShiftRow();
    invByteSub();
    addRoundKey(key, round);
}

void AES128::invRound(int round)
{
    invShiftRow();
    invByteSub();
    addRoundKey(key, round);
    invMixColumn();
}

//==================== Debugging functions ===================//

void AES128::test128(unsigned char stateIn[numRows][Nb], unsigned char keyIn[keySize])
{
    for (int i {0}; i < numRows; ++i)
    {
        for (int j {0}; j < Nb; ++j) state[i][j] = stateIn[i][j];
    }
    memcpy(key, keyIn, keySize);

    KeySchedule128 ks;
    ks.expandKey(key);

    int roundNum {0};
    addRoundKey(key, roundNum);
    printKey();
    while (roundNum < Nr)
    {
        round(++roundNum);
        printState();
    }
    finalRound(roundNum+1);
    printState();
    printHexOut();
}

void AES128::printKey()
{
    for (int i{0}; i < keySize; ++i)
    {
        if (i%15==0 && i > 0) std::cout << std::hex << (int)key[i] << std::endl;
        else std::cout << std::hex << (int)key[i];
    }
    std::cout <<  " " << std::endl;
}

void AES128::printState()
{
    for (int i{0}; i < numRows; ++i)
    {
        for (int j{0}; j < Nb; ++j)
        {
            if (j == 3) std::cout << std::hex << (int)state[i][j] << std::endl;
            else
            {
                std::cout << std::hex << (int)state[i][j];
            }
        }
    }
    std::cout << " " << std::endl;
}

void AES128::printHexOut()
{
    for (int i{0}; i < numRows; ++i)
    {
        for (int j{0}; j < Nb; ++j)
        {
            std::cout << std::hex << (int)state[j][i];
        }
    }
    std::cout << " " << std::endl;
}

void AES128::test128(std::string plainText, std::string keyIn)
{
    std::string res;
    cvtStrToKey(keyIn);
    cvtStrToState(plainText);
    printState();
    printKey();

    KeySchedule128 ks;
    ks.expandKey(key);

    int roundNum {0};
    addRoundKey(key, roundNum);
    while (roundNum < Nr)
    {
        round(++roundNum);
    }
    finalRound(roundNum+1);

    res = cvtStateToStr();
    std::cout << res <<std::endl;
}

void AES128::testInv128(unsigned char stateIn[numRows][Nb], unsigned char keyIn[keySize])
{
    for (int i {0}; i < numRows; ++i)
    {
        for (int j {0}; j < Nb; ++j) state[i][j] = stateIn[i][j];
    }
    memcpy(key, keyIn, keySize);

    KeySchedule128 ks;
    ks.expandKey(key);

    int roundNum {Nr+1};
    addRoundKey(key, roundNum);
    std::cout << "Round " << Nr - roundNum + 2 << " in:"<< std::endl;
    printHexOut();
    while (roundNum > 1)
    {
        std::cout << "Round " << Nr - roundNum + 3 << " in:"<< std::endl;
        invRound(--roundNum);
        printHexOut();
    }
    invFinalRound(--roundNum);
    std::cout << "Output: " << std::endl;
    printHexOut();
}
