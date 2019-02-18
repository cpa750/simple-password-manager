cmake_minimum_required(VERSION 3.12.1)

project(Simple_password_manager)

set(GFA /lib/GaloisFieldArithmetic)

include_directories(${GFA})

set(CMAKE_CXX_STANDARD 14)
add_executable (Simple-password-manager Encryptor.cpp Encryptor.h Hasher.cpp Hasher.h SBox.cpp SBox.cpp AESEncryptor.cpp AESEncryptor.h main.cpp)
