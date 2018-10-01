#include <iostream>

#include "../include/console.hpp"
#include "../include/io_file.hpp"
#include "../include/preprocessor.hpp"

using namespace std;
using namespace console;

void print_list(list<pair<int, string>>& mylist){
    list<pair<int,string>>::iterator it;
    for(it = mylist.begin(); it != mylist.end(); ++it){
        cout << "line " << it.operator*().first << " = " << it.operator*().second << endl;
    }
}

int main(int argc, char **argv) {
    list<int> flags;
    list<int> files;

    message("Imaginary assembler v.0.0.1 (Alpha do alpha)\n");
    message("Developers:\tHugo N. Fonseca - 16/0008166\n\t\tJose Luiz G. Nogueira - 16/0032458\n\n");

    if(argc < 2)
        fatal("Assembler: No files were provided. Stop\n");
    else {
        for (int i = 1; i < argc; i++) {
            if (argv[i][0] == '-') {
                flags.push_back(i);
                info("Assembler: Flag '%s' detected\n", argv[i]);
            } else {
                files.push_back(i);
            }
        }
    }
    return 0;
}