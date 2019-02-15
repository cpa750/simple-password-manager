#ifndef SIMPLE_PASSWORD_MANAGER_HASHER_H
#define SIMPLE_PASSWORD_MANAGER_HASHER_H

#include <iostream>

class Hasher
{
public:
    Hasher();
    ~Hasher();

    virtual void hash() = 0;

};


#endif //SIMPLE_PASSWORD_MANAGER_HASHER_H
