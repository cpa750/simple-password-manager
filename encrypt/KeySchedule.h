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
    unsigned char rcon(u_char in);
    void rotate(std::array<u_char, 4>& in);
    void scheduleCore(std::array<u_char, 4>& in, u_char i);

public:
    virtual void expandKey(std::array<u_char, 176>& key) = 0;

};


#endif //SIMPLE_PASSWORD_MANAGER_KEYSCHEDULE_H
