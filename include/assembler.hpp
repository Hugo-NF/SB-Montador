#ifndef MONTADOR_ASSEMBLER_HPP
#define MONTADOR_ASSEMBLER_HPP

#include <deque>
#include <string>
#include <map>
#include "console.hpp"

using namespace std;
class assembler{
private:
public:
    deque<pair<int, string>> text;
    map<string, int> labels;
    map<string, pair<int, int>> instructions;           // OPCODE string => (OPCODE, INST. SIZE)
    int text_section, data_section, bss_section;

    deque<int> code;
    deque<int> relative;
    map<string, int> table_use;
    map<string, int> table_definition;
    bool is_module;

    void assemble_module();
    void assemble_exec();

public:
    explicit assembler(deque<pair<int, string>>& preprocessor_text, map<string, int>& preprocessor_labels, bool is_mod, int s_text, int s_data, int s_bss){
        text.assign(preprocessor_text.begin(), preprocessor_text.end());
        labels = preprocessor_labels;
        text_section = s_text;
        data_section = s_data;
        bss_section = s_bss;
        is_module = is_mod;
        instructions["ADD"] = pair<int, int>(1,2); instructions["SUB"] = pair<int, int>(2,2);
        instructions["MUL"] = pair<int, int>(3,2); instructions["DIV"] = pair<int, int>(4,2);
        instructions["JMP"] = pair<int, int>(5,2); instructions["JMPN"]= pair<int, int>(6,2);
        instructions["JMPP"]= pair<int, int>(7,2); instructions["JMPZ"]= pair<int, int>(8,2);
        instructions["COPY"]= pair<int, int>(9,3); instructions["LOAD"]= pair<int, int>(10,2);
        instructions["STORE"]=pair<int, int>(11,2);instructions["INPUT"]=pair<int, int>(12,2);
        instructions["OUTPUT"]=pair<int, int>(13,2);instructions["STOP"]=pair<int, int>(14,1);
    }
    virtual ~assembler(){
        text.clear();
    }
};


#endif //MONTADOR_ASSEMBLER_HPP
