#ifndef SIMPLE_PASSWORD_MANAGER_ENCRYPTOR_H
#define SIMPLE_PASSWORD_MANAGER_ENCRYPTOR_H

#include <string>
#include <iostream>

using std::string;

class Encryptor
{
private:
    char key[128];

public:
    Encryptor();
    ~Encryptor();

    virtual string encrypt() = 0;
    virtual string decrypt() = 0;

};


#endif //SIMPLE_PASSWORD_MANAGER_ENCRYPTOR_H
