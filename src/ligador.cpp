#include <iostream>
#include <string>
#include <map>
#include "../include/linker.hpp"

using namespace std;

int main(int argc, char **argv){
    if (argc < 2){
        fatal("Linker: No source files provided. STOP\n");
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
