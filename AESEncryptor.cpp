#include "AESEncryptor.h"

void AESEncryptor::byteSub(unsigned char state[AESEncryptor::numRows][AESEncryptor::Nb])
{
    for (int i {0}; i < AESEncryptor::numRows; ++i)
    {
        for (int j {0}; j < AESEncryptor::Nb; ++j)
        {
            state[i][j] = SBox::LUT[state[i][j]];
        }
    }
}

void AESEncryptor::shiftRow(unsigned char state[AESEncryptor::numRows][AESEncryptor::Nb])
{
    for (int i {0}; i < AESEncryptor::numRows; ++i)
    {
        if (i == 0) continue; // Skip shifting the first row according to the AES standard.
        else
        {
            unsigned char row[AESEncryptor::Nb];
            for (int j {0}; j < AESEncryptor::Nb; ++j)
            {
                int newPos = (j - i) % AESEncryptor::Nb;
                row[newPos] = state[i][j];
                /*
                 * This algorithm shifts the elements
                 * in each row of the state according to the AES
                 * standard, placing them in the temp array row.
                 */
            }
            for (int k {0}; k < AESEncryptor::Nb; ++k)
            {
                state[i][k] = row[k];
                /*
                 * This temp array is then assigned back to the
                 * state.
                 */
            }
        }
    }
}
