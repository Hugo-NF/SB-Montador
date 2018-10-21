#include "../include/linker.hpp"

void linker::get_files(int argc, char** file_names){
    int count_opened_files = 0;

    // Abre cada arquivo e salva nas variaveis de classe
    for(int i=0; i < argc; i++){
        io_file file_obj((string(file_names[i]) + ".obj").c_str(), fstream::in);

        if(file_obj.is_open()) {
            string str_text = file_obj.read_in_string();
            add_obj_to_data(str_text);
            count_opened_files += 1;
        }

        file_obj.close();
    }

    // Salva nome do primeiro arquivo, se ele existir
    if(count_opened_files){
        obj_file = file_names[0];
    }
}

void linker::add_obj_to_data(string& obj){
    regex rgx_name_address("([a-zA-Z][a-zA-Z_\\d]*) (\\d+)",regex::ECMAScript);
    regex rgx_address("(\\d+)",regex::ECMAScript);
    regex rgx_header("(TABLE USE|TABLE DEFINITION|RELATIVE|CODE)",regex::ECMAScript);

    vector<string> groups;

    //Remove cabeçalho
    obj = regex_replace(obj, rgx_header, "@");

    //Quebra em 4 grupos table_use, table_definition, relative e code
    groups = split(obj, "\n\n");

    //table_use
    deque<tuple<string, int>> temp_table_use_obj;
    for (auto &matches : regex_scan(groups[0], rgx_name_address)) {
        temp_table_use_obj.emplace_back(matches[0],stoi(matches[1]));
    }
    table_use.push_back(temp_table_use_obj);

    //table_definition
    deque<tuple<string, int>> temp_table_definition_obj;
    for (auto &matches : regex_scan(groups[1], rgx_name_address)) {
        temp_table_definition_obj.emplace_back(matches[0],stoi(matches[1]));
    }
    table_definition.push_back(temp_table_definition_obj);

    //relative
    deque<int> temp_relative_obj;
    for (auto &matches : regex_scan(groups[2], rgx_address)) {
        temp_relative_obj.emplace_back(stoi(matches[0]));
    }
    relative.push_back(temp_relative_obj);

    //code
    deque<int> temp_code_obj;
    for (auto &matches : regex_scan(groups[3], rgx_address)) {
        temp_code_obj.emplace_back(stoi(matches[0]));
    }
    code.push_back(temp_code_obj);
}

int linker::is_all_defined() {
    deque<string> name_of_not_defineds;

    // Pega todas as labels definidas
    deque<string> all_label_defined;

    for(auto &table_use_obj : table_definition){
        for(auto &name_and_address : table_use_obj){
            all_label_defined.push_back(get<0>(name_and_address));
        }
    }

    // Pega todas as labels usadas
    deque<string> all_label_used;

    for(auto &table_definition_obj : table_use){
        for(auto &name_and_address : table_definition_obj){
            all_label_used.push_back(get<0>(name_and_address));
        }
    }

    // Checa se alguma usada não foi definida
    for(auto &label_used : all_label_used){
        if(!include(name_of_not_defineds, label_used) && !include(all_label_defined, label_used) ){
            name_of_not_defineds.push_back(label_used);
        }
    }

    // Retorna true se foram todas definida, se não retorna false e exibe quais nao foram definidas
    if (name_of_not_defineds.empty()) {
        return 1;
    } else {
        error("Linker: Not defined labels:\n");
        customize_flags(1, TEXT_COLOR_RED);
        for(auto &label_name : name_of_not_defineds){
            message("\t-> %s\n", label_name.c_str());
        }
        message("\n");
        reset_flags();
        return 0;
    }

}

int linker::is_something_redefined(){
    deque<string> name_of_redefined;

    // Pega todas as labels definidas
    deque<string> all_label_defined;

    for(auto &table_use_obj : table_definition){
        for(auto &name_and_address : table_use_obj){
            if (include(all_label_defined, get<0>(name_and_address))) {
                name_of_redefined.push_back(get<0>(name_and_address));
            }else {
                all_label_defined.push_back(get<0>(name_and_address));
            }
        }
    }


    // Retorna true se redefinida e quais foram redefinidas, se não retorna false
    if(name_of_redefined.empty()){
        return 0;
    }else{
        error("Linker: Redefined labels:\n");
        customize_flags(1, TEXT_COLOR_RED);
        for(auto &label_name : name_of_redefined){
            message("\t-> %s\n", label_name.c_str());
        }
        message("\n");
        reset_flags();
        return 1;
    }
}

void linker::set_right_address(){
    int address_add = 0;

    // Atualiza endereço das tabelas e do codigo
    for(int i=0; i< relative.size(); i++){
        //Atualize na tabela de uso
        for(auto &name_and_address : table_use[i]){
            get<1>(name_and_address) += address_add;
        }

        //Atualiza na tabela de definicao
        for(auto &name_and_address : table_definition[i]){
            get<1>(name_and_address) += address_add;
        }

        //Atualiza no codigo
        for(auto &address_index : relative[i]){
            code[i][address_index] += address_add;
        }

        address_add += code[i].size();
    }

}

void linker::replace_address_exter_used(){
    deque<tuple<string,int>> table_use_unified;
    deque<tuple<string,int>> table_definition_unified;
    map<string,int> map_table_definition_unified;

    // Converte array de array em array (todos os array de objs em um so array)
    for(auto &table_use_obj : table_use){
        for(auto &name_address : table_use_obj ){
            table_use_unified.push_back(name_address);
        }
    }

    // Converte array de array em array (todos os array de objs em um so array)
    for(auto &table_definition_obj : table_definition){
        for(auto &name_address : table_definition_obj ){
            table_definition_unified.push_back(name_address);
        }
    }

    // Converte array de array em array (todos os array de objs em um so array)
    for(auto &code_obj : code){
        for(auto &code : code_obj) {
            code_output.push_back(code);
        }
    }

    // Converte array de array em hash para acesso de busca direta
    map_table_definition_unified = to_map(table_definition_unified);

    for(auto &name_and_address : table_use_unified){
        code_output[get<1>(name_and_address)] = map_table_definition_unified[get<0>(name_and_address)];
    }
}

void linker::puts_code_out(){

    // Se nao há pelomenos um obj retorna
    if(obj_file.empty()) { return; }

    string output;

    for(auto &code : code_output){
        output += to_string(code) + " ";
    }

    io_file file_obj((obj_file + ".e").c_str(), fstream::out);
    file_obj.writeline(output);
    file_obj.close();

    success("--> Executable file: %s.e saved\n\n", obj_file.c_str());
}

vector<string> linker::split(string &line, const string &del) {
    vector<string> res;

    size_t pos = 0;
    std::string token;
    while ((pos = line.find(del)) != std::string::npos) {
        token = line.substr(0, pos);
        res.push_back(token);
        line.erase(0, pos + del.length());
    }

    return res;
}

deque<deque<string>> linker::regex_scan(string &str, regex &reg){
    std::sregex_iterator iter(str.begin(), str.end(), reg);
    std::sregex_iterator end;
    deque<deque<string>> ret;

    while(iter != end)
    {
        deque<string> temp_deque;

        for(unsigned i = 1; i < iter->size(); ++i)
        {
            temp_deque.push_back((*iter)[i]);
        }

        ret.push_back(temp_deque);
        ++iter;
    }

    return ret;
}

int linker::include(deque<string>arr, string &str){
    int ret = 0;

    for(auto &arr_str : arr){
        if(arr_str == str){
            ret = 1;
        }
    }

    return ret;
}

map<string,int> linker::to_map(deque<tuple<string,int>> &arr_names_and_address){
    map<string,int> ret;

    for(auto &name_address : arr_names_and_address){
        ret[get<0>(name_address)] = get<1>(name_address);
    }

    return ret;
}