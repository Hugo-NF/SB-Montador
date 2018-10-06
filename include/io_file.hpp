#ifndef MONTADOR_IO_FILE_HPP
#define MONTADOR_IO_FILE_HPP

#include <iostream>
#include <fstream>
#include <deque>

#include "console.hpp"

using namespace std;
using namespace console;

class io_file{
private:
    fstream file_stream;
    string filename;

public:
    explicit io_file(const char* filename, fstream::openmode flag){
        file_stream.open(filename, flag);
        if (!file_stream.is_open())
            error("IOModule: Could not open file %s\n", filename);
        else
            this->filename = string(filename);
    }

    virtual ~io_file(){
        file_stream.close();
    };

    bool is_open();
    string get_filename();
    deque<string> readfile();
    void writefile(deque<pair<int,string>>& content);

};

#endif //MONTADOR_IO_FILE_HPP
