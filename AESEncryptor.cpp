#include "AESEncryptor.h"

void AESEncryptor::byteSub(unsigned char state[])
{
    for (int i {0}; i < AESEncryptor::stateSize; ++i)
    {
        state[i] = SBox::LUT.at(state[i]);
    }
}

void AESEncryptor::shiftRow(unsigned char state[])
{
    // TODO: implement this method
}
