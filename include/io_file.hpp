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

public:
    explicit io_file(const char* filename, fstream::openmode flag){
        file_stream.open(filename, flag);
        if (!file_stream.is_open())
            error("IOModule: Could not open file %s\n", filename);

    }

    virtual ~io_file() = default;
    bool is_open();
    void close();
    string read_in_string();
    deque<string> readfile();
    void writeline(const string& line);
    void writefile(deque<pair<int,string>>& content);

};

#endif //MONTADOR_IO_FILE_HPP
