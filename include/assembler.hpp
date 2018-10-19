#ifndef MONTADOR_ASSEMBLER_HPP
#define MONTADOR_ASSEMBLER_HPP

#include <deque>
#include <map>
#include <string>
#include <tuple>
#include <vector>
#include "console.hpp"
#include "tables.hpp"

#define INST_DELIM " ,"

using namespace std;
using namespace console;
using namespace tables;

class assembler{
private:
public:
    deque<pair<int, string>> text;
    map<string, int> labels;
    int text_section, data_section, bss_section;


    deque<tuple<int*, int*, int>> code;
    deque<int> relative;
    bool is_module, proceed;
    int code_size;

    static vector<string> split(const string &line, const string &del);
    void assemble_module();
    void assemble_exec();
    void evaluate_line(vector<string>& fields);
    void mount_instruction(int opcode, vector<string>& fields);

public:
    explicit assembler(deque<pair<int, string>>& preprocessor_text, map<string, int>& preprocessor_labels, bool is_mod, int s_text, int s_data, int s_bss){
        text.assign(preprocessor_text.begin(), preprocessor_text.end());
        labels = preprocessor_labels;

        proceed = true;
        code_size = 0;
        text_section = s_text;
        data_section = s_data;
        bss_section = s_bss;
        is_module = is_mod;

    }
    virtual ~assembler(){
        text.clear();
        labels.clear();
        instructions.clear();
    }
};


#endif //MONTADOR_ASSEMBLER_HPP
