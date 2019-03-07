#ifndef SIMPLE_PASSWORD_MANAGER_ENCRYPT_H
#define SIMPLE_PASSWORD_MANAGER_ENCRYPT_H

#include <string>
#include <vector>

#include "AES.h"
#include "AES128.h"

typedef std::vector<std::string> stringVector;

typedef enum EncryptionType
{
    aes128,
    aes256

} EncryptionType;

std::string CBC(std::string in, std::string key);
std::string cvtStateToStr(State in);
std::vector<State> cvtStrToStates(std::string in);
std::string padString(std::string in);

#endif //SIMPLE_PASSWORD_MANAGER_ENCRYPT_H
