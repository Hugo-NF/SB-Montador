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

#include <iostream>
#include <string>
#include <map>
#include "../include/linker.hpp"

using namespace std;

int main(int argc, char **argv){
#ifdef _WIN32
    windows_cmd();
#endif
    linker_version();
    devs();
    if (argc < 2){
        fatal("Linker: No source files provided. STOP" RESET "\n");
        return -1;
    }

    // Cria linker, ele já irá setas as tabelas e codigos
    linker linker_obj(argc-1, &argv[1]);

    // Checa se todos os externs foram definidos
    if ( !linker_obj.is_all_defined() )
        return -1;


    // Checa se algum public foi redefinido
    if( linker_obj.is_something_redefined() )
        return -1;


    // Ajusta os endereços relativos
    linker_obj.set_right_address();

    // Substitui endereços externos usados
    linker_obj.replace_address_exter_used();

    // Exibe a saida
    linker_obj.puts_code_out();

    return 0;

}
