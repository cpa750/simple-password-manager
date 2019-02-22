#include "AES.h"

void AES::byteSub()
{
    for (int i {0}; i < numRows; ++i)
    {
        for (int j {0}; j < Nb; ++j)
        {
            state[i][j] = LUT::SBox[state[i][j]];
            /*
             * Implementation of the lookup table
             * for the s-box
             */
        }
    }
}

void AES::shiftRow()
{
    for (int i {0}; i < numRows; ++i)
    {
        if (i == 0) continue; // Skip shifting the first row according to the AES standard.
        else
        {
            unsigned char row[Nb];
            for (int j {0}; j < Nb; ++j)
            {
                int newPos = (j - i) % Nb;
                row[newPos] = state[i][j];
                /*
                 * This algorithm shifts the elements
                 * in each row of the state according to the AES
                 * standard, placing them in the temp array row.
                 */
            }

            for (int k {0}; k < AES::Nb; ++k)
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

void AES::mixColumns()
{
    using namespace LUT;
    unsigned char col[numRows];
    for (int i {0}; i < Nb; ++i)
    {
        for (int j {0}; j < numRows; ++j)
        {
            col[j] = state[j][i];
            /*
             * These loops construct a 1 dimensional column vector from
             * one column of the state. This will repeat for every column in the state.
             * The reason this copy is necessary is because the transformation is
             * dependent on the inputs, which cannot change over the operation.
             * Hence, a copy that is not modified.
             */
        }

        state[0][i] = GMult2[col[0]] ^ GMult3[col[1]] ^ col[2] ^ col[3];
        state[1][i] = col[0] ^ GMult2[col[1]] ^ GMult3[col[2]] ^ col[3];
        state[2][i] = col[0] ^ col[1] ^ GMult2[col[2]] ^ GMult3[col[3]];
        state[3][i] = GMult3[col[0]] ^ col[1] ^ col[2] ^ GMult2[col[3]];
        /*
         * The above code applies the mixColumns operation specified by the AES standard.
         * The explanation for how this operation is carried out and the lookup tables used
         * can be found at https://ipfs.io/ipfs/QmXoypizjW3WknFiJnKLwHCnL72vedxjQkDDP1mXWo6uco/wiki/Rijndael_mix_columns.html
         */
    }
}

std::string AES::cvtStateToStr()
{
    std::string res;
    for (int i {0}; i < numRows; ++i)
    {
        for (int j {0}; j < Nb; ++j)
        {
            res.push_back(state[i][j]);
        }
    }
    return res;
}

void AES::cvtStrToState(std::string plain)
{
    /*
     * String must be 128 bits (16 bytes) in length.
     * This class does not take care of concatenation of blocks,
     * padding input strings, or splitting the input into 128 bit blocks.
     */
    int sz = plain.size();
    for (int i {0}; i < 16; i += 4)
    {
        std::string sub = plain.substr(i, 4);
        const char* chars = sub.c_str();
        std::memcpy(state[i/4], chars, 4);
    }
}
