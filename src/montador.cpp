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

#include "../include/assembler.hpp"
#include "../include/console.hpp"
#include "../include/io_file.hpp"

using namespace std;
using namespace console;

vector<int> eval_flags(int argc, const char **argv, bool& pre, bool& link, bool& start){
    vector<int> res;
    for(int arg = 1; arg < argc; arg++){
        if(argv[arg][0] != '-')
            res.push_back(arg);
        else {
            if(string(argv[arg]) == FLAG_HELP){
                help();
                start = false;
            }
            else if(string(argv[arg]) == FLAG_VERSION){
                asm_version();
                start = false;
            }
            else if(string(argv[arg]) == FLAG_DEV){
                devs();
                start = false;
            }
            else if(string(argv[arg]) == FLAG_PRE)
                pre = true;
            else if(string(argv[arg]) == FLAG_LINK)
                link = true;
            else if(string(argv[arg]) == FLAG_MOUNT)
                link = false;
            else {
                fatal("Assembler: Unknown flag option %s\n", argv[arg]);
                start = false;
            }
        }
    }
    return res;
}

int main(int argc, const char **argv) {
#ifdef _WIN32
    windows_cmd();
    string linker_call = "ligador.exe";
#else
    string linker_call = "./ligador";
#endif
    bool start = true, flag_pre = false, flag_link = false;
    if(argc < 2)
        fatal("Assembler: No arguments provided. STOP\n");
    else {
        vector<int> index_files = eval_flags(argc, argv, flag_pre, flag_link, start);
        if (start && !index_files.empty()) {
            asm_version();
            devs();

            for (auto &index : index_files) {
                io_file input_file((string(argv[index]) + ".asm").c_str(), fstream::in);
                if (input_file.is_open()) {
                    info("Assembler: Current file = %s\n", argv[index]);
                    deque<string> lines = input_file.readfile();
                    assembler pre_file(lines, argv[index], flag_pre);
                    if (flag_link)
                        linker_call += " " + string(argv[index]);
                }
                input_file.~io_file();
            }
            if (flag_link)
                return system(linker_call.c_str());

        }
    }
    return 0;
}