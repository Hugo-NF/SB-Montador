#ifndef MONTADOR_PREPROCESSOR_HPP
#define MONTADOR_PREPROCESSOR_HPP

#include <deque>
#include <map>
#include <regex>
#include <string>
#include "console.hpp"
#include "defs.hpp"

using namespace std;
using namespace console;

class preprocessor{
private:
    regex sections;                             // Regular expression to catalog sections
    deque<regex> symbols;                       // Regular expressions to catalog symbols
    deque<regex> formatting;                    // Regular expressions to format input file
    deque<regex> directives;                    // Regular expressions to preprocessor directives

    bool if_eval;                               // Flags a true IF directive

    bool is_module(int line);
    bool is_section(int line);
    void clear_line(string& line);
    bool found_section();
    int valid_number(string& token);
    bool valid_label(string& label);
    int has_label(int line);
    bool is_equ(int line);
    bool is_if(int line);

public:
    deque<pair<int, string>> text;                                  // Holds the text with it's original line number
    int text_section, data_section, bss_section;
    int code_size;                                                  // Space needed to load the code
    bool module_def;
    map<string, tuple<int, bool, bool>> labels_addresses;           // Holds the line for each valid label (addr, data?, extern?)
    map<string, string> equ_definitions;                            // Holds EQUs definitions
    map<string, vector<int>> symbols_use;
    map<string, int> symbols_definition;
    map<string, pair<int, int>> instructions;

    explicit preprocessor(deque<string>& file_text){
        text_section = data_section = bss_section = -1;
        if_eval = module_def = false;
        code_size = 0;
        sections = regex(SECTION_REGEX, regex::ECMAScript|regex::icase);

        symbols.emplace_back(regex(LABEL_REGEX, regex::ECMAScript|regex::icase));
        symbols.emplace_back(regex(NUMBER_REGEX, regex::ECMAScript|regex::icase));
        symbols.emplace_back(regex(LINE_REGEX, regex::ECMAScript));
        symbols.emplace_back(regex(INST_REGEX, regex::ECMAScript));

        formatting.emplace_back(regex(COMMENTS, regex::ECMAScript));
        formatting.emplace_back(regex(TABS_SPACES, regex::ECMAScript));
        formatting.emplace_back(regex(LINE_BEGIN, regex::ECMAScript));
        formatting.emplace_back(regex(LABEL_DIV, regex::ECMAScript));
        formatting.emplace_back(regex(OPR_REGEX, regex::ECMAScript));
        formatting.emplace_back(regex(HEX_REGEX, regex::ECMAScript));

        directives.emplace_back(regex(DIR_EQU_REGEX, regex::ECMAScript|regex::icase));
        directives.emplace_back(regex(DIR_IF_REGEX, regex::ECMAScript|regex::icase));
        directives.emplace_back(regex(DIR_BEGIN_REGEX, regex::ECMAScript|regex::icase));

        instructions["ADD"] = pair<int, int>(1, 2);  //OPCODES
        instructions["SUB"] = pair<int, int>(2, 2);
        instructions["MUL"] = pair<int, int>(3, 2);
        instructions["DIV"] = pair<int, int>(4, 2);
        instructions["JMP"] = pair<int, int>(5, 2);
        instructions["JMPN"] = pair<int, int>(6, 2);
        instructions["JMPP"] = pair<int, int>(7, 2);
        instructions["JMPZ"] = pair<int, int>(8, 2);
        instructions["COPY"] = pair<int, int>(9, 3);
        instructions["LOAD"] = pair<int, int>(10, 2);
        instructions["STORE"] = pair<int, int>(11, 2);
        instructions["INPUT"] = pair<int, int>(12, 2);
        instructions["OUTPUT"] = pair<int, int>(13, 2);
        instructions["STOP"] = pair<int, int>(14, 1);
        instructions["CONST"] = pair<int, int>(20, 1);  //Directives
        instructions["SPACE"] = pair<int, int>(21, 1);
        instructions["SECTION"] = pair<int, int>(22, 0);
        instructions["PUBLIC"] = pair<int, int>(23, 0);
        instructions["EXTERN"] = pair<int, int>(24, 0);
        instructions["END"] = pair<int, int>(25, 0);

        for(int line = 0; line < file_text.size(); line++) {
            clear_line(file_text[line]);
            if(!file_text[line].empty())
                text.emplace_back(line + 1, file_text[line]);
        }
    }

    virtual ~preprocessor(){
        symbols.clear();
        formatting.clear();
        directives.clear();
        text.clear();
        equ_definitions.clear();
        labels_addresses.clear();
        symbols_use.clear();
        symbols_definition.clear();
    }

    deque<pair<int, string>>& process_file();
};

#endif //MONTADOR_PREPROCESSOR_HPP
