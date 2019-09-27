cmake_minimum_required(VERSION 3.14)
project(RNM_Generator C)

set(CMAKE_C_STANDARD 99)

add_executable(RNM_Generator main.c crc.h crc.c)