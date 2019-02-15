project(Simple_password_manager)

set(CMAKE_CXX_STANDARD 14)
add_executable (Simle-password-manager Encryptor.cpp Encryptor.h Hasher.cpp Hasher.h SBox.cpp SBox.cpp AESEncryptor.cpp AESEncryptor.h)
