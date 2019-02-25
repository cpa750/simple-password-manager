#include "AES.h"

//================ AES encryption functions ================//

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
         * can be found at
         * https://ipfs.io/ipfs/QmXoypizjW3WknFiJnKLwHCnL72vedxjQkDDP1mXWo6uco/wiki/Rijndael_mix_columns.html
         */
    }
}

void AES::shiftRow()
{
    for (int i {0}; i < numRows; ++i)
    {
        if (i > 0)
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
            memcpy(state[i], row, 4);
        }
    }
}

//================ AES decryption functions ================//

void AES::invByteSub()
{
    for (int i {0}; i < numRows; ++i)
    {
        for (int j {0}; j < Nb; ++j)
        {
            state[i][j] = LUT::invSBox[state[i][j]];
            /*
             * Implementation of the lookup table
             * for the s-box
             */
        }
    }
}

void AES::invMixColumn()
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
             * Reminder: b/c the rows and columns are switched you can't write
             * this using memcpy!
             */
        }

        state[0][i] = GMult14[col[0]] ^ GMult11[col[1]] ^ GMult13[col[2]] ^ GMult9[col[3]];
        state[1][i] = GMult9[col[0]] ^ GMult14[col[1]] ^ GMult11[col[2]] ^ GMult13[col[3]];
        state[2][i] = GMult13[col[0]] ^ GMult9[col[1]] ^ GMult14[col[2]] ^ GMult11[col[3]];
        state[3][i] = GMult11[col[0]] ^ GMult13[col[1]] ^ GMult9[col[2]] ^ GMult14[col[3]];
        /*
         * The above code applies the invMixColumns operation specified by the AES standard.
         * The explanation for how this operation is carried out and the lookup tables used
         * can be found at
         * https://ipfs.io/ipfs/QmXoypizjW3WknFiJnKLwHCnL72vedxjQkDDP1mXWo6uco/wiki/Rijndael_mix_columns.html
         */
    }
}

void AES::invShiftRow()
{
    for (int i {0}; i < numRows; ++i)
    {
        if (i > 0)
        {
            unsigned char row[Nb];
            for (int j {0}; j < Nb; ++j)
            {
                int newPos = (i + j) % Nb;
                row[newPos] = state[i][j];
                /*
                 * This algorithm shifts the elements
                 * in each row of the state according to the AES
                 * standard, placing them in the temp array row.
                 */
            }
            memcpy(state[i], row, 4);
        }
    }
}

//==================== Helper functions ====================//

std::string AES::cvtStateToStr()
{
    std::string res;
    for (int i {0}; i < numRows; ++i)
    {
        for (int j {0}; j < Nb; ++j)
        {
            res.push_back(state[j][i]);
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
    unsigned char temp[numRows];
    for (int i {0}; i < 16; i += 4)
    {
        std::string sub = plain.substr(i, 4);
        const char* chars = sub.c_str();
        memcpy(temp, chars, 4);
        for (int j {0}; j < Nb; ++j) state[j][i/4] = temp[j];
        /*
         * This code copies the original string, in blocks of 4,
         * to the columns of the state. memcpy() is required to
         * remove the const and cast from signed to unsigned.
         * i/4 gives the column in which to copy to, as i
         * increments by 4 each time.
         */
        // TODO: fix this so the rows and columns are switched
    }
}
