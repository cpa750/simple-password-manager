#include "KeySchedule128.h"

void KeySchedule128::expandKey(unsigned char* in)
{
    unsigned char t[4];
    /* c is 16 because the first sub-key is the user-supplied key */
    unsigned char c = 16;
    unsigned char i = 1;
    unsigned char a;

    /* We need 11 sets of sixteen bytes each for 128-bit mode */
    while(c < 176) {
        /* Copy the temporary variable over from the last 4-byte
         * block */
        for(a = 0; a < 4; a++)
            t[a] = in[a + c - 4];
        /* Every four blocks (of four bytes),
         * do a complex calculation */
        if(c % 16 == 0) {
            scheduleCore(t,i);
            i++;
        }
        for(a = 0; a < 4; a++) {
            in[c] = in[c - 16] ^ t[a];
            c++;
        }
    }
}
