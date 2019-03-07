#ifndef SIMPLE_PASSWORD_MANAGER_DECRYPT_H
#define SIMPLE_PASSWORD_MANAGER_DECRYPT_H

#include "Encrypt.h"

std::string invCBC(stringVector& blocks, std::string& key,
                   std::string& initializationVector, EncryptionType encryptionType);

#endif //SIMPLE_PASSWORD_MANAGER_DECRYPT_H
