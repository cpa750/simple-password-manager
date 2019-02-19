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
    // Constructing the Galois field

    galois::GaloisFieldElement cxElems[4] = {
            galois::GaloisFieldElement(&gf, 0x03),
            galois::GaloisFieldElement(&gf, 0x01),
            galois::GaloisFieldElement(&gf, 0x01),
            galois::GaloisFieldElement(&gf, 0x02)
    };
    galois::GaloisFieldPolynomial cxPoly(&gf, 3, cxElems);
    // Constructing c(x) as defined by AES

    /*
     * Constructing a Galois field in 2^8 space
     * using the x^8+x^4+x^3+x+1 irreducible polynomial
     * as specified by AES
     */
    unsigned char column[AESEncryptor::numRows];

    // Mix all of the columns in the state one at a time
    for (int i {0}; i < AESEncryptor::Nb; ++i)
    {
        for (int j{0}; j < AESEncryptor::numRows; ++j)
        {
            column[j] = *state[j][i];
            // Getting the column vector from the state
        }

        galois::GaloisFieldElement elements[AESEncryptor::numRows];

        for (int k {0}; k < AESEncryptor::numRows; ++k)
        {
            galois::GaloisFieldElement gfe(&gf, column[k]);
            elements[k] = gfe;
            // Creating the elements array which will be used to create the polynomial
        }

        galois::GaloisFieldPolynomial gfp(&gf, AESEncryptor::numRows-1, elements);
        // Constructing galois polynomial from a state column

        galois::GaloisFieldPolynomial res = gfp * cxPoly;
        // Multiplying the two GF polynomials according to AES

        std::vector<galois::GaloisFieldElement> resCoeffs = res.getPolyElems();
        // Getting the resultant elements from the multiplication

        for (int l {0}; l > AESEncryptor::numRows; ++l)
        {
            *state[l][i] = resCoeffs.at(l).getPolyCoeff();
            /*
             * Getting the resultant coefficients (chars) and
             * reassigning them to the state column
             */
        }
    }
}

void AESEncryptor::addRoundKey(unsigned char* state[AESEncryptor::numRows][AESEncryptor::Nb])
{
    //TODO: Implement this
}
