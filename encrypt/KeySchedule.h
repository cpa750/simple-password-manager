#ifndef SIMPLE_PASSWORD_MANAGER_KEYSCHEDULE_H
#define SIMPLE_PASSWORD_MANAGER_KEYSCHEDULE_H

#include <string>

#include "LUT.h"

/*
 * Base class for the Rijndael key schedule.
 * This class is intended to be inherited by others
 * implementing the different bit-lengths.
 */

class KeySchedule
{
protected:
    void rotate(unsigned char* in);
    unsigned char rcon(unsigned char in);
    void scheduleCore(unsigned char* in, unsigned char i);

public:
    virtual void expandKey(unsigned char* key) = 0;

};


#endif //SIMPLE_PASSWORD_MANAGER_KEYSCHEDULE_H