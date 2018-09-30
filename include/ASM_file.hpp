#ifndef ASM_FILE_HPP
#define ASM_FILE_HPP

#include <iostream>
#include <fstream>
#include <list>

using namespace std;

class ASM_file{
public:
    fstream file_stream;

    list<string> readfile();
    void writefile(list<string>& content);

public:
    explicit ASM_file(const char* filename, fstream::openmode flag){
        file_stream.open(filename, flag);
        if (!file_stream.is_open())
            cout << "IOError: Could not open file: "<<filename<< endl;
    }

    virtual ~ASM_file(){
        file_stream.close();
    };

};

#endif //ASM_FILE_HPP
