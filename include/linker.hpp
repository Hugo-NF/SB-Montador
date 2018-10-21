#ifndef MONTADOR_LINKER_HPP
#define MONTADOR_LINKER_HPP

#include <deque>
#include <map>
#include <regex>
#include <vector>
#include <string>
#include <tuple>
#include "io_file.hpp"
#include "console.hpp"

using namespace std;
using namespace console;

class linker {
/*
 *   Estrutura das variaveis:
 *   Organizado em HASH com chaves = table_use, table_definition, relative e code
 *
 *   table_use = [tabela_use_obj1, tabela_use_obj2, ...]
 *   table_definition = [table_definition_obj1, table_definition_obj2, ...]
 *   relative = [relative_obj1, relative_obj2, ...]
 *   code = [code_obj1, code_obj2, ...]
 *
 *   tabela_use_obj = [[nome, endereço],[nome, endereço],...]
 *   table_definition_obj = [[nome, endereço],[nome, endereço],...]
 *   relative_obj = [endereço, endereço, ...]
 *   code_obj = [codigo, codigo, codigo, ...]
 */

private:

    string obj_file;
    deque<deque<tuple<string, int>>> table_use, table_definition;
    deque<deque<int>> relative, code;
    deque<int> code_output;

    /**
     * Realiza leitura dos objs
     */
    void get_files(int argc, char** file_names);

    /**
     * Pega os campos table_use, table_definition, relative e code
     * de cada obj e armazena em $data
     */
    void add_obj_to_data(string& obj);

    /**
     * Quebra a string em vetores onde o delimitador é encontrado
     */
    vector<string> split(string &line, const string &del);

    /**
     * retorna os grupos da expressão regular que deram match na string
     */
    deque<deque<string>> regex_scan(string &str, regex &reg);

    /**
     * checa se o array de string inclui uma determinada string
     */
    int include(deque<string>arr, string &str);

    /**
     * converte um array de tuplas(chave, valor) em um map (chave, valor)
     */
    map<string,int> to_map(deque<tuple<string,int>> &arr_names_and_address);

public:
    explicit linker(int argc, char** args){
        get_files(argc, args);
    }

    /**
     * checa se para cada extern existe algum public
     */
    int is_all_defined();

    /**
     * checa se cada public possui definição unica
     */
    int is_something_redefined();

    /**
     * corrigi enderreço relativo das tables e code
     */
    void set_right_address();

    /**
     * substitui para cada item da tabela de uso no endereço indicado
     * o endereço equivalente da tabela de definição
     */
    void replace_address_exter_used();

    /**
     * uni o array de codigo separado por espaco e joga na saida .e
     */
    void puts_code_out();

};

#endif //MONTADOR_LINKER_HPP
