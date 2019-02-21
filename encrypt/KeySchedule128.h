#ifndef SIMPLE_PASSWORD_MANAGER_KEYSCHEDULE128_H
#define SIMPLE_PASSWORD_MANAGER_KEYSCHEDULE128_H

#include <cstring>
#include <iostream>

#include "KeySchedule.h"

class KeySchedule128 : public KeySchedule
{
public:
    void expandKey(unsigned char* key) final;
};


#endif //SIMPLE_PASSWORD_MANAGER_KEYSCHEDULE128_H
