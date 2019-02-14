#ifndef SIMPLE_PASSWORD_MANAGER_ENCRYPTOR_H
#define SIMPLE_PASSWORD_MANAGER_ENCRYPTOR_H

#include <string>
#include <iostream>

using std::string;

class encryptor
{
private:
    char key[];

public:
    encryptor();
    ~encryptor();

    virtual string encrypt() = 0;
    virtual string decrypt() = 0;

};


#endif //SIMPLE_PASSWORD_MANAGER_ENCRYPTOR_H
