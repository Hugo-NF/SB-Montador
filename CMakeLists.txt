cmake_minimum_required(VERSION 3.12)
project(Montador)

set(CMAKE_CXX_STANDARD 14)

option(_MONTADOR "Compilando o montador" ON)
option(_LIGADOR "Compilando o ligador" ON)

if (_MONTADOR)
    add_executable(montador src/montador.cpp include/console.hpp
            include/io_file.hpp src/io_file.cpp
            include/preprocessor.hpp src/preprocessor.cpp)
endif()

if (_LIGADOR)
    add_executable(ligador src/ligador.cpp include/console.hpp
            include/io_file.hpp src/io_file.cpp)
endif ()

