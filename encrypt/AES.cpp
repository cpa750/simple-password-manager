#include "AES.h"

void AES::byteSub(unsigned char* state[AES::numRows][AES::Nb])
{
    for (int i {0}; i < AES::numRows; ++i)
    {
        for (int j {0}; j < AES::Nb; ++j)
        {
            *state[i][j] = LUT::SBox[*state[i][j]];
            /*
             * Implementation of the lookup table
             * for the s-box
             */
        }
    }
}

void AES::shiftRow(unsigned char* state[AES::numRows][AES::Nb])
{
    for (int i {0}; i < AES::numRows; ++i)
    {
        if (i == 0) continue; // Skip shifting the first row according to the AES standard.
        else
        {
            unsigned char row[AES::Nb];
            for (int j {0}; j < AES::Nb; ++j)
            {
                int newPos = (j - i) % AES::Nb;
                row[newPos] = *state[i][j];
                /*
                 * This algorithm shifts the elements
                 * in each row of the state according to the AES
                 * standard, placing them in the temp array row.
                 */
            }

            for (int k {0}; k < AES::Nb; ++k)
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

void AES::mixColumns(unsigned char* state[AES::numRows][AES::Nb])
{
    using namespace LUT;
    unsigned char col[AES::numRows];
    for (int i {0}; i < AES::Nb; ++i)
    {
        for (int j {0}; i < AES::numRows; ++j)
        {
            col[j] = *state[j][i];
            /*
             * These loops construct a 1 dimensional column vector from
             * one column of the state. This will repeat for every column in the state
             */
        }

        *state[0][i] = GMult2[col[0]] ^ GMult3[col[1]] ^ col[2] ^ col[3];
        *state[1][i] = col[0] ^ GMult2[col[1]] ^ GMult3[col[2]] ^ col[3];
        *state[2][i] = col[0] ^ col[1] ^ GMult2[col[2]] ^ GMult3[col[3]];
        *state[3][i] = GMult3[col[0]] ^ col[1] ^ col[2] ^ GMult2[col[3]];
        /*
         * The above code applies the mixColumns operation specified by the AES standard.
         * The explanation for how this operation is carried out and the lookup tables used
         * can be found at https://ipfs.io/ipfs/QmXoypizjW3WknFiJnKLwHCnL72vedxjQkDDP1mXWo6uco/wiki/Rijndael_mix_columns.html
         */
    }
}

void AES::cvtStrToState(std::string in)
{
    // TODO: implement this 
}
