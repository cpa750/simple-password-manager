#include "AES128.h"

//================= AES encryption functions =================//

void AES128::addRoundKey(std::array<u_char, 176>& key, int round)
{
    for (int i {0}; i < numRows; ++i)
    {
        for (int j{0}; j < Nb; ++j)
        {
            state[j][i] ^= key[round * 4 * Nb + i * Nb + j];
            /*
             * This element access arithmetic ensures that the key elements accessed
             * fo{r each round and each element in the state are unique
             */
        }
    }
}

State AES128::cipher(State stateIn, std::array<u_char, 176> keyIn)
{
    state = stateIn;
    key = keyIn;

    KeySchedule128 ks;
    ks.expandKey(key);

    int roundNum {0};
    addRoundKey(key, roundNum);
    while (roundNum < Nr-1)
    {
        round(++roundNum);
    }
    finalRound(++roundNum);

    return state;
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

State AES128::invCipher(State stateIn, std::array<u_char, 176> keyIn)
{
    state = stateIn;
    key = keyIn;

    KeySchedule128 ks;
    ks.expandKey(key);

    int roundNum {Nr};
    addRoundKey(key, roundNum);
    while (roundNum > 1)
    {
        invRound(--roundNum);
    }
    invFinalRound(--roundNum);

    return state;
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

void AES128::printState()
{
    for (int i {0}; i < 4; ++i)
    {
        for (int j {0}; j < 4; ++j)
        {
            std::cout << std::hex << (int)state[i][j];
            if (j == 3) std::cout << '\n';
        }
    }
    std::cout << '\n';
}

void AES128::printKey()
{
    int i {0};
    while (i < 176)
    {
        std::cout << std::hex << (int)key[i];
        ++i;
    }
    std::cout << '\n';
}
