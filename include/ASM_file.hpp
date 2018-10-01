#ifndef ASM_FILE_HPP
#define ASM_FILE_HPP

#include <iostream>
#include <fstream>
#include <list>

#include "console.hpp"

using namespace std;
using namespace console;

class ASM_file{
private:
    fstream file_stream;

public:
    explicit ASM_file(const char* filename, fstream::openmode flag){
        file_stream.open(filename, flag);
        if (!file_stream.is_open())
            error("IOModule: Could not open file %s\n", filename);
        else
            info("Current file: %s\n", filename);
    }

    virtual ~ASM_file(){
        file_stream.close();
    };


    list<string> readfile();
    void writefile(list<string>& content);

};

#endif //ASM_FILE_HPP
