#include <iostream>
#include <string>

#include "KeySchedule128.h"

int main()
{
    unsigned char arr[176]
            {
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
    };

    KeySchedule128 keySchedule;
    keySchedule.expandKey(arr);

    for (int i {0}; i < 176; ++i)
    {
        if (i%15==0 && i > 0)
            std::cout << std::hex << static_cast<int>(arr[i]) << ' ' << std::endl;
        else
            std::cout << std::hex << static_cast<int>(arr[i]) << ' ';
    }
    return 0;
}

