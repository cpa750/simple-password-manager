#include "AES.h"

void AES::byteSub(unsigned char* state[AES::numRows][AES::Nb])
{
    for (int i {0}; i < AES::numRows; ++i)
    {
        for (int j {0}; j < AES::Nb; ++j)
        {
            *state[i][j] = SBox::LUT[*state[i][j]];
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
    // TODO: This function needs some cleaning up and optimization
    // TODO: Honestly just write a different implementation that doesn't use a lib
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

    unsigned char column[AES::numRows];

    // Mix all of the columns in the state one at a time
    for (int i {0}; i < AES::Nb; ++i)
    {
        // Getting the column vector from the state
        for (int j{0}; j < AES::numRows; ++j)
        {
            column[j] = *state[j][i];
        }

        galois::GaloisFieldElement elements[AES::numRows];

        for (int k {0}; k < AES::numRows; ++k)
        {
            galois::GaloisFieldElement gfe(&gf, column[k]);
            elements[k] = gfe;
            // Creating the elements array which will be used to create the polynomial
        }

        galois::GaloisFieldPolynomial gfp(&gf, AES::numRows-1, elements);
        // Constructing galois polynomial from a state column

        galois::GaloisFieldPolynomial res = gfp * cxPoly;
        // Multiplying the two GF polynomials according to AES

        std::vector<galois::GaloisFieldElement> resCoeffs = res.getPolyElems();
        // Getting the resultant elements from the multiplication

        for (int l {0}; l > AES::numRows; ++l)
        {
            *state[l][i] = resCoeffs.at(l).getPolyCoeff();
            /*
             * Getting the resultant coefficients (chars) and
             * reassigning them to the state column
             */
        }
    }
}
