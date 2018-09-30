cmake_minimum_required(VERSION 3.12)
project(SB_Montador)

set(CMAKE_CXX_STANDARD 14)

add_executable(montador src/main.cpp src/ASM_file.cpp include/preprocessor.hpp src/preprocessor.cpp)