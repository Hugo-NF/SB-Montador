#include "../include/assembler.hpp"

vector<string> assembler::split(const string &line, const string &del) {
    static bool dict[256] = { false};
    vector<string> res;
    string token;

    for (int i = 0; i < del.size(); ++i)
        dict[del[i]] = true;

    for (auto &i : line) {
        if (dict[i]) {
            if (!token.empty()) {
                res.push_back(token);
                token.clear();
            }
        }
        else
            token += i;
    }
    if (!token.empty())
        res.push_back(token);
    return res;
}

void assembler::assemble_module() {

}

void assembler::assemble_exec() {
    int line = text_section+1;
    vector<string> line_fields;

    while(line < data_section || line < bss_section){
        line_fields = split(text[line].second, INST_DELIM);
        evaluate_line(line_fields);
        line++;
    }
}

void assembler::evaluate_line(vector<string>& fields){
    size_t label_pos = fields[0].find(':');
    int opcode;
    if(label_pos != -1) {  //Line has label
        fields[0].erase(label_pos);
        labels[fields[0]] = code_size; //Fix to code addr
        opcode = 1;
    }
    else
        opcode = 0;
    mount_instruction(opcode, fields);
}

void assembler::mount_instruction(int idx_opcode, vector<string>& fields){
    string opcode = fields[idx_opcode];
    int offset[2] = {0,0};
    int *addr_label[2] = {nullptr, nullptr};

    //code[code_size] = make_tuple(&instructions[opcode].first, &a, b);
    switch (instructions[opcode].first){
        case INST_ADD:
            if(labels.count(fields[idx_opcode+1])){
                addr_label[0] = &labels[fields[idx_opcode+1]];
            }
            break;
        case INST_SUB:

            break;
        case INST_MUL:

            break;
        case INST_DIV:

            break;
        case INST_JMP:

            break;
        case INST_JMPN:

            break;
        case INST_JMPP:

            break;
        case INST_JMPZ:

            break;
        case INST_COPY:

            break;
        case INST_LOAD:

            break;
        case INST_STORE:

            break;
        case INST_INPUT:

            break;
        case INST_OUTPUT:

            break;
        case INST_STOP:

            break;
        default:
            error("Assembler - syntatic: Unknown instruction \"%s\"\n", opcode.c_str());
            proceed = false;
    }
}

