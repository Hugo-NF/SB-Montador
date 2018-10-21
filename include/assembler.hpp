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
#include "defs.hpp"

using namespace std;
using namespace console;

class assembler {
private:
public:
    preprocessor i_file;

    deque<int> code;
    deque<int> relative;
    int current_address;
    regex regexes;
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
    void write_output(const char* filename, bool gen_pre_out);

public:
    explicit assembler(deque<string> &text, const char* filename, bool gen_pre_out) :
            i_file(text){
        regexes = regex(UNIVERSAL_REGEX, regex::ECMAScript);
        proceed = true;
        end_found = false;
        current_address = 0;
        assemble();
        write_output(filename, gen_pre_out);
    }
    virtual ~assembler(){
        //i_file.~preprocessor();
        relative.clear();
        code.clear();
    }
};


#endif //MONTADOR_ASSEMBLER_HPP
