cmake_minimum_required(VERSION 3.10.3)
project(SB_Montador)

set(CMAKE_CXX_STANDARD 11)

add_executable(montador src/main.cpp include/io_file.hpp
        src/io_file.cpp include/preprocessor.hpp
        src/preprocessor.cpp include/console.hpp)