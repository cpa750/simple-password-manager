cmake_minimum_required(VERSION 3.12.1)

project(Simple_password_manager)

set(GFLIB /home/cian/GaloisFieldArithmetic)

include_directories(${GFLIB})

set(CMAKE_CXX_STANDARD 14)
add_executable (Simple-password-manager
                Encryptor.cpp Encryptor.h
                Hasher.cpp Hasher.h SBox.h
                AESEncryptor.cpp AESEncryptor.h main.cpp
                ${GFLIB}/GaloisField.h ${GFLIB}/GaloisField.cpp
                ${GFLIB}/GaloisFieldElement.h ${GFLIB}/GaloisFieldElement.cpp
                ${GFLIB}/GaloisFieldPolynomial.h ${GFLIB}/GaloisFieldPolynomial.cpp KeySchedule.cpp KeySchedule.h)
