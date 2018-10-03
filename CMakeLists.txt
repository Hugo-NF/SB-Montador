cmake_minimum_required(VERSION 3.10.3)
project(SB_Montador)

set(CMAKE_CXX_STANDARD 11)

option(_MONTADOR "Compilando o montador" ON)
option(_LIGADOR "Compilando o ligador" ON)

if (_MONTADOR)
    add_executable(montador src/montador.cpp include/io_file.hpp
            src/io_file.cpp include/preprocessor.hpp
            src/preprocessor.cpp include/console.hpp)
endif()

if (_LIGADOR)
    add_executable(ligador src/ligador.cpp)
endif ()