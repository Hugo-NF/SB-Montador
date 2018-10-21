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
#include "../include/assembler.hpp"

#define VERSION "0.0.3"

using namespace std;
using namespace console;

int main(int argc, char **argv) {
#ifdef _WIN32
    windows_cmd();
#endif

    message("Imaginary assembler - version: " VERSION "\n");
    message("Developers:\tHugo N. Fonseca - 16/0008166\n\t\tJose Luiz G. Nogueira - 16/0032458\n\n");

    io_file input_file("../docs/bin.asm", fstream::in);
    deque<string> lines = input_file.readfile();

    assembler pre_file(lines);
    pre_file.assemble();

    input_file.~io_file();

    return 0;
}