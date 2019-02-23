#ifndef SIMPLE_PASSWORD_MANAGER_ENCRYPT_H
#define SIMPLE_PASSWORD_MANAGER_ENCRYPT_H

#include <string>
#include <vector>

#include "AES.h"
#include "AES128.h"

typedef enum EncryptionType
{
    aes128,
    aes192,
    aes256

} EncryptionType;

std::vector<std::string> cvtToBlocks(std::string& plainIn);
std::string encrypt(std::string& plainIn, std::string& keyIn, EncryptionType encryptionType);
std::string padBlock(std::string& plainIn);

#endif //SIMPLE_PASSWORD_MANAGER_ENCRYPT_H
