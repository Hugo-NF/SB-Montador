#include <iostream>
#include <cstdio>

#include "../include/ASM_file.hpp"
#include "../include/preprocessor.hpp"

using namespace std;

void print_list(list<pair<int, string>>& mylist){
    list<pair<int,string>>::iterator it;
    for(it = mylist.begin(); it != mylist.end(); ++it){
        cout << "line " << it.operator*().first << " = " << it.operator*().second << endl;
    }
}

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main() {
    ASM_file input("../docs/exemplo.asm", fstream::in);

    list<string> text = input.readfile();
    preprocessor prec(text);

    prec.clear_comments();
    prec.sections();

    print_list(prec.text);

    input.~ASM_file();

    return 0;
}