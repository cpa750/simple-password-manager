#include "AESEncryptor.h"

// TODO: replace C-style arrays with std::array/vector

void AESEncryptor::byteSub(unsigned char* state[AESEncryptor::numRows][AESEncryptor::Nb])
{
    for (int i {0}; i < AESEncryptor::numRows; ++i)
    {
        for (int j {0}; j < AESEncryptor::Nb; ++j)
        {
            *state[i][j] = SBox::LUT[*state[i][j]];
            /*
             * Implementation of the lookup table
             * for the s-box
             */
            // TODO: Rewrite this method using Galois Field arithmetic using the GFA library
        }
    }
}

void AESEncryptor::shiftRow(unsigned char* state[AESEncryptor::numRows][AESEncryptor::Nb])
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
                row[newPos] = *state[i][j];
                /*
                 * This algorithm shifts the elements
                 * in each row of the state according to the AES
                 * standard, placing them in the temp array row.
                 */
            }

            for (int k {0}; k < AESEncryptor::Nb; ++k)
            {
                *state[i][k] = row[k];
                /*
                 * This temp array is then assigned back to the
                 * state.
                 */
            }
        }
    }
}

void AESEncryptor::mixColumns(unsigned char* state[AESEncryptor::numRows][AESEncryptor::Nb])
{
    const unsigned int pow {8};
    unsigned int primePoly[9] = {1, 0, 0, 0, 1, 1, 0, 1, 1};
    galois::GaloisField gf(pow, primePoly);
    /*
     * Constructing a Galois field in 2^8 space
     * using the x^8+x^4+x^3+x+1 irreducible polynomial
     * as specified by AES
     */

    galois::GaloisFieldElement elements[32];
    int elementIndex {31};
    unsigned char character;
    // TODO: Replace this placeholder with a value from the state

    for (unsigned int i = 1 << 31; i > 0; i = i / 2)
    {
        elements[elementIndex] = galois::GaloisFieldElement(&gf, (character & i));
        /*
         * This code gets the single binary digit at the index where i=1,
         * by &ing i with a character.
         */
        --elementIndex;
    }
    // Have to do galois arithmetic over the column

    // TODO: Finish implementing this
}

void AESEncryptor::addRoundKey(unsigned char* state[AESEncryptor::numRows][AESEncryptor::Nb])
{
    //TODO: Implement this
}
