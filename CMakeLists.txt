cmake_minimum_required(VERSION 3.12.1)

project(Simple_password_manager)


set(CMAKE_CXX_STANDARD 14)
add_executable (Simple-password-manager main.cpp
                hash/Hasher.cpp hash/Hasher.h encrypt/LUT.h
                encrypt/AES.cpp encrypt/AES.h
                encrypt/AES128.cpp encrypt/AES128.h
                encrypt/KeySchedule.cpp encrypt/KeySchedule.h
                encrypt/KeySchedule128.cpp encrypt/KeySchedule128.h
                encrypt/typedefs.h encrypt/Encrypt.h encrypt/Encrypt.cpp
                encrypt/Decrypt.cpp encrypt/Decrypt.h)
