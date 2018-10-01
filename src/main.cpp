#include <iostream>

#include "../include/console.hpp"
#include "../include/ASM_file.hpp"
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

    message("Imaginary assembler v.0.0.1 (Alpha do alpha)\n");
    message("Developers:\tHugo N. Fonseca - 16/0008166\n\t\t\tJose Luiz G. Nogueira - 16/0032458\n");

    ASM_file input("../docs/exemplo.asm", fstream::in);

    list<string> text = input.readfile();
    preprocessor prec(text);

    prec.clear_comments();
    prec.sections();

    print_list(prec.text);

    input.~ASM_file();

    return 0;
}