#include "KeySchedule128.h"

/*
 * The functions defined here are not my own.
 * They can be found at https://www.samiam.org/key-schedule.html
 * Only small changes have been made to improve readability and
 * adherence to conventions.
 */

void KeySchedule128::expandKey(std::array<u_char, 176>& key)
{
    std::array<u_char, 4> t;
    /* c is 16 because the first sub-key is the user-supplied key */
    unsigned char c = 16;
    unsigned char i = 1;
    unsigned char a;

    /* We need 11 sets of sixteen bytes each for 128-bit mode */
    while(c < 176)
    {
        /* Copy the temporary variable over from the last 4-byte
         * block */
        for (a = 0; a < 4; ++a)
            t[a] = key[a + c - 4];
        /* Every four blocks (of four bytes),
         * do a complex calculation */
        if (c % 16 == 0)
        {
            scheduleCore(t, i);
            i++;
        }
        for (a = 0; a < 4; ++a)
        {
            key[c] = key[c - 16] ^ t[a];
            ++c;
        }
    }
}
