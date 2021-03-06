#include "KeySchedule.h"

/*
 * The functions defined here are not my own.
 * They can be found at https://www.samiam.org/key-schedule.html
 * Only small changes have been made to improve readability and
 * adherence to conventions.
 */

unsigned char KeySchedule::rcon(unsigned char in)
{
    unsigned char c {1};
    if (in == 0)
        return 0;
    while(in != 1)
    {
        unsigned char b;
        b = c & 0x80;
        c <<= 1;
        if (b == 0x80)
        {
            c ^= 0x1b;
        }
        --in;
    }
    return c;
}

void KeySchedule::rotate(unsigned char *in)
{
    unsigned char a, c;
    a = in[0];
    for (c = 0; c < 3; ++c)
        in[c] = in[c + 1];
    in[3] = a;
}

void KeySchedule::scheduleCore(unsigned char *in, unsigned char i)
{
    char a;
    /* Rotate the input 8 bits to the left */
    rotate(in);
    /* Apply Rijndael's s-box on all 4 bytes */
    for(a = 0; a < 4; a++)
        in[a] = LUT::SBox[in[a]];
    /* On just the first byte, add 2^i to the byte */
    in[0] ^= rcon(i);
}
