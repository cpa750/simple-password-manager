#ifndef SIMPLE_PASSWORD_MANAGER_DECRYPT_H
#define SIMPLE_PASSWORD_MANAGER_DECRYPT_H

#include "Encrypt.h"

State convertStringToState(std::string in);
std::string invCBC(std::string in, std::string& key,
                   std::string& initializationVector, EncryptionType encryptionType);

#endif //SIMPLE_PASSWORD_MANAGER_DECRYPT_H
