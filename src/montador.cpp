#ifdef _WIN32
#include <windows.h>
#include <wchar.h>
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
void windows_cmd(){
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#endif

#include "../include/io_file.hpp"
#include "../include/console.hpp"
#include "../include/preprocessor.hpp"

#define VERSION "0.0.2"

using namespace std;
using namespace console;

void print_list(deque<string>& mylist){
    deque<string>::iterator it;
    for(it = mylist.begin(); it != mylist.end(); ++it)
        printf("%s\n", it.operator*().c_str());
}

void print_list_pair(deque<pair<int, string>>& mylist){
    deque<pair<int,string>>::iterator it;
    for(it = mylist.begin(); it != mylist.end(); ++it)
       printf("line %d = %s\n", it.operator*().first, it.operator*().second.c_str());
}

int main(int argc, char **argv) {
#ifdef _WIN32
    windows_cmd();
#endif

    message("Imaginary assembler - version: " VERSION "\n");
    message("Developers:\tHugo N. Fonseca - 16/0008166\n\t\tJose Luiz G. Nogueira - 16/0032458\n\n");

    io_file input_file("../docs/bin.asm", fstream::in);
    deque<string> lines = input_file.readfile();

    preprocessor pre_file(lines);

    io_file output_file("../docs/bin.pre", fstream::out);
    output_file.writefile(pre_file.process_file());

    printf("USE\n");
    for(auto it1 = pre_file.symbols_use.begin(); it1 != pre_file.symbols_use.end(); ++it1){
        printf("Label: %s\tValue: %d\n", it1.operator*().first.c_str(), it1.operator*().second);
    }
    printf("DEF\n");
    for(auto it2 = pre_file.symbols_definition.begin(); it2 != pre_file.symbols_definition.end(); ++it2){
        printf("Label: %s\tValue: %d\n", it2.operator*().first.c_str(), it2.operator*().second);
    }
    printf("LABELS\n");
    for(auto it3 = pre_file.labels_addresses.begin(); it3 != pre_file.labels_addresses.end(); ++it3){
        printf("Label: %s\tValue: %d\n", it3.operator*().first.c_str(), it3.operator*().second);
    }


    input_file.~io_file();
    output_file.~io_file();
    pre_file.~preprocessor();

    return 0;
}