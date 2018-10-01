#ifndef ASM_FILE_HPP
#define ASM_FILE_HPP

#include <iostream>
#include <fstream>
#include <list>

using namespace std;

class ASM_file{
private:
    fstream file_stream;

public:
    explicit ASM_file(const char* filename, fstream::openmode flag){
        file_stream.open(filename, flag);
        if (!file_stream.is_open())
            cout << "IOError: Could not open file: "<<filename<< endl;
        else
            cout << "FILE: " <<filename<< endl;
    }

    virtual ~ASM_file(){
        file_stream.close();
    };


    list<string> readfile();
    void writefile(list<string>& content);

};

#endif //ASM_FILE_HPP
