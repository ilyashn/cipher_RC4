cmake_minimum_required(VERSION 3.8)
project(cipher_RC4)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
add_executable(cipher_RC4 ${SOURCE_FILES})