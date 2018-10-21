#ifndef MONTADOR_ASSEMBLER_HPP
#define MONTADOR_ASSEMBLER_HPP

#include <deque>
#include <exception>
#include <map>
#include <string>
#include <regex>
#include <tuple>
#include <vector>
#include "console.hpp"
#include "io_file.hpp"
#include "preprocessor.hpp"
#include "tables.hpp"

using namespace std;
using namespace console;

class assembler {
private:
public:
    preprocessor i_file;
    io_file out_file;

    deque<int> code;
    deque<int> relative;
    int current_address;
    deque<regex> regexes;
    bool proceed, end_found;

    bool eval_operator(string& optr);
    int eval_index(string& idx);
    int eval_addr(string& opr, int idx, bool check_data);
    void eval_const(string &amt);
    void eval_space(string& amt);
    void eval_one_arg(bool is_data, const string& mne, string& opr, string& optr, string& idx);
    void eval_copy(int line, bool is_data, const string& op_mne, string& opr1, string& optr1, string& idx1, string& opr2, string& optr2, string& idx2);
    void mount_one_arg(int line, bool is_data, const string& op_mne, string& opr1, string& optr1, string& idx1, const string& opr2, const string& optr2, const string& idx2);
    void assemble();

public:
    explicit assembler(deque<string> &text) :
            i_file(text),
            out_file("../docs/bin.pre", fstream::out){

        regexes.emplace_back(regex(UNIVERSAL_REGEX, regex::ECMAScript));
        regexes.emplace_back(regex(LABEL_STA, regex::ECMAScript));
        out_file.writefile(i_file.process_file());
        proceed = true;
        end_found = false;
        current_address = 0;
    }
    virtual ~assembler(){
        //i_file.~preprocessor();
        out_file.~io_file();
        relative.clear();
        code.clear();
    }
};


#endif //MONTADOR_ASSEMBLER_HPP
