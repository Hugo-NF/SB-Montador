#include "../include/assembler.hpp"

bool assembler::eval_operator(string& optr){
    if(optr == "+")
        return true;
    else if(optr == "-")
        return false;
    else
        throw invalid_argument("Assembler - syntatic: Unknown operator between label and index");
}

int assembler::eval_index(string& idx){
    try{
        return stoi(idx);
    }
    catch (exception& exc){
        throw invalid_argument("Assembler - lexical: Wrong token used as numerical offset");
    }
}

int assembler::eval_addr(int code_size, string& opr, int idx, bool check_data){

    if(i_file.labels_addresses.count(opr)) {
        int addr = get<0>(i_file.labels_addresses[opr]);
        bool is_data = get<1>(i_file.labels_addresses[opr]);
        bool is_extern = get<2>(i_file.labels_addresses[opr]);
        if(check_data){
            if(!is_data && !is_extern)
                throw invalid_argument("Assembler - semantic: Segmentation fault. Modifying memory address outside data section");
            else{
                if(is_extern)
                    i_file.symbols_use[opr].push_back(code_size+1);
                return addr + idx;
            }
        }
        else{
            if(is_data && !is_extern)
                throw invalid_argument("Assembler - semantic: Segmentation fault. Jumping to memory address outside text section");
            else{
                if(is_extern)
                    i_file.symbols_use[opr].push_back(code_size+1);
                return addr + idx;
            }
        }
    }
    else
        throw invalid_argument("Assembler - syntatic: Label does not exist");
}

void assembler::eval_const(string &amt){
    try{
        code.push_back(eval_index(amt));
        current_address++;
    }
    catch (exception& exc){
        proceed = false;
        error(exc.what()); customize_flags(1, TEXT_COLOR_RED);
        message(" at CONST directive\n");reset_flags();
    }
}

void assembler::eval_space(string& amt){
    try{
        for(int i = 0; i < eval_index(amt); i++) {
            code.push_back(0);
            current_address++;
        }
    }
    catch (exception& exc){
        proceed = false;
        error(exc.what()); customize_flags(1, TEXT_COLOR_RED);
        message(" at SPACE directive\n");reset_flags();
    }
}

void assembler::eval_copy(int line, bool is_data, const string& op_mne, string& opr1, string& optr1, string& idx1, string& opr2, string& optr2, string& idx2){
    bool sum_idx;
    int offset, addr;

    try {
        if(!optr1.empty() && !idx1.empty()){
            sum_idx = eval_operator(optr1);
            offset = eval_index(idx1);
            if(!sum_idx)
                offset = -offset;
            addr = eval_addr(current_address, opr1, offset, is_data);
        }
        else
            addr = eval_addr(current_address, opr1, 0, is_data);
        code.push_back(get<0>(i_file.instructions[op_mne]));
        code.push_back(addr);
        relative.push_back(current_address+1);

        if(!optr2.empty() && !idx2.empty()){
            sum_idx = eval_operator(optr2);
            offset = eval_index(idx2);
            if(!sum_idx)
                offset = -offset;
            addr = eval_addr(current_address+1, opr2, offset, is_data);
        }
        else
            addr = eval_addr(current_address+1, opr2, 0, is_data);
        code.push_back(addr);
        relative.push_back(current_address+2);
    }
    catch (exception& exc){
        proceed = false;
        error(exc.what()); customize_flags(1, TEXT_COLOR_RED);
        message(" at line %d\n", this->i_file.text[line].first);reset_flags();
    }
}

void assembler::eval_one_arg(bool is_data, const string& mne, string& opr, string& optr, string& idx){
    bool sum_idx;
    int offset;
    int addr;

    if(!optr.empty() && !idx.empty()){
        sum_idx = eval_operator(optr);
        offset = eval_index(idx);
        if(!sum_idx)
            offset = -offset;
        addr = eval_addr(current_address, opr, offset, is_data);
    }
    else
        addr = eval_addr(current_address, opr, 0, is_data);

    code.push_back(get<0>(i_file.instructions[mne]));
    code.push_back(addr);
    relative.push_back(current_address+1);
}

void assembler::mount_one_arg(int line, bool is_data, const string& op_mne, string& opr1, string& optr1, string& idx1, const string& opr2, const string& optr2, const string& idx2){
    if(!opr2.empty() || !optr2.empty() || !idx2.empty() || opr1.empty()) {
        proceed = false;
        error("Assembler - syntatic: Wrong number of arguments to instruction %s (line %d)\n", op_mne.c_str(), this->i_file.text[line].first);
    }
    else{
        try {
            eval_one_arg(is_data, op_mne, opr1, optr1, idx1);
        }
        catch (exception& exc){
            proceed = false;
            error(exc.what()); customize_flags(1, TEXT_COLOR_RED);
            message(" at line %d\n", this->i_file.text[line].first);reset_flags();
        }
    }
}

void assembler::assemble() {
    smatch matches;
    for(int line = 0; line < this->i_file.text.size(); line++) {
        if (regex_search(this->i_file.text[line].second, matches, regexes)) {
            string label, op_mne, opr1, optr1, idx1, opr2, optr2, idx2;
            label = matches[1].str();
            op_mne = matches[2].str();
            opr1 = matches[3].str();
            optr1 = matches[4].str();
            idx1 = matches[5].str();
            opr2 = matches[6].str();
            optr2 = matches[7].str();
            idx2 = matches[8].str();
            switch (i_file.instructions[op_mne].first) {
                case INST_ADD:
                    mount_one_arg(line, true, op_mne, opr1, optr1, idx1, opr2, optr2, idx2);
                    current_address += 2;
                    break;
                case INST_SUB:
                    mount_one_arg(line, true, op_mne, opr1, optr1, idx1, opr2, optr2, idx2);
                    current_address += 2;
                    break;
                case INST_MUL:
                    mount_one_arg(line, true, op_mne, opr1, optr1, idx1, opr2, optr2, idx2);
                    current_address += 2;
                    break;
                case INST_DIV:
                    mount_one_arg(line, true, op_mne, opr1, optr1, idx1, opr2, optr2, idx2);
                    current_address += 2;
                    break;
                case INST_JMP:
                    mount_one_arg(line, false, op_mne, opr1, optr1, idx1, opr2, optr2, idx2);
                    current_address += 2;
                    break;
                case INST_JMPN:
                    mount_one_arg(line, false, op_mne, opr1, optr1, idx1, opr2, optr2, idx2);
                    current_address += 2;
                    break;
                case INST_JMPP:
                    mount_one_arg(line, false, op_mne, opr1, optr1, idx1, opr2, optr2, idx2);
                    current_address += 2;
                    break;
                case INST_JMPZ:
                    mount_one_arg(line, false, op_mne, opr1, optr1, idx1, opr2, optr2, idx2);
                    current_address += 2;
                    break;
                case INST_COPY:
                    eval_copy(line, true, op_mne, opr1, optr1, idx1, opr2, optr2, idx2);
                    current_address += 3;
                    break;
                case INST_LOAD:
                    mount_one_arg(line, true, op_mne, opr1, optr1, idx1, opr2, optr2, idx2);
                    current_address += 2;
                    break;
                case INST_STORE:
                    mount_one_arg(line, true, op_mne, opr1, optr1, idx1, opr2, optr2, idx2);
                    current_address += 2;
                    break;
                case INST_INPUT:
                    mount_one_arg(line, true, op_mne, opr1, optr1, idx1, opr2, optr2, idx2);
                    current_address += 2;
                    break;
                case INST_OUTPUT:
                    mount_one_arg(line, true, op_mne, opr1, optr1, idx1, opr2, optr2, idx2);
                    current_address += 2;
                    break;
                case INST_STOP:
                    if (!i_file.module_def && !end_found)
                        end_found = true;
                    else if (end_found)
                        error("Assembler - semantic: Repeated STOP instruction. Redefinition at line %d\n", this->i_file.text[line].first);
                    code.push_back(i_file.instructions[op_mne].first);
                    current_address++;
                    break;
                case DIR_CONST:
                    if (!opr2.empty() || !optr2.empty() || !idx2.empty() || !opr1.empty() || !optr1.empty()) {
                        proceed = false;
                        error("Assembler - syntatic: Wrong number of arguments to directive %s (line %d)\n", op_mne.c_str(), this->i_file.text[line].first);
                    } else
                        eval_const(idx1);
                    break;
                case DIR_SPACE:
                    if (!opr2.empty() || !optr2.empty() || !idx2.empty() || !opr1.empty() || !optr1.empty()) {
                        proceed = false;
                        error("Assembler - syntatic: Wrong number of arguments to directive %s (line %d)\n", op_mne.c_str(), this->i_file.text[line].first);
                    } else if (idx1.empty()) {
                        idx1 = "1";
                        eval_space(idx1);
                    } else
                        eval_space(idx1);
                    break;
                case DIR_SECTION:
                    break;
                case DIR_PUBLIC:
                    break;
                case DIR_EXTERN:
                    break;
                case DIR_END:
                    if (i_file.module_def && !end_found)
                        end_found = true;
                    else if (end_found)
                        error("Assembler - semantic: Repeated end module declaration. Redefinition at line %d\n", this->i_file.text[line].first);
                    break;
                case 0:
                default:
                    error("Assembler - syntatic: Unknown operation mnemonic at line %d\n", this->i_file.text[line].first);
            }
        } else if (this->i_file.text[line].second.back() != ':') {
            proceed = false;
            error("Unknown ERROR at line %d - standard exception thrown: regex bad logic\n", this->i_file.text[line].first);
        }
    }
}

void assembler::write_output(const char* filename, bool gen_pre_out) {
    if(gen_pre_out){
        io_file pre_out_obj((string(filename) + ".pre").c_str(), fstream::out);
        pre_out_obj.writefile(i_file.text);
        pre_out_obj.close();
    }
    if(proceed){
        if(i_file.module_def){
            io_file obj_out((string(filename) + ".obj").c_str(), fstream::out);
            obj_out.writeline("TABLE USE\n");
            for(auto &mem: i_file.symbols_use){
                for(auto &use: mem.second)
                    obj_out.writeline(mem.first + " " + to_string(use) + "\n");

            }
            obj_out.writeline("\nTABLE DEFINITION\n");
            for(auto &mem: i_file.symbols_definition)
                obj_out.writeline(mem.first + " " + to_string(mem.second) + "\n");
            obj_out.writeline("\nRELATIVE\n");
            for(auto &mem: relative)
                obj_out.writeline(to_string(mem)+" ");
            obj_out.writeline("\n\nCODE\n");
            for(auto &mem: code)
                obj_out.writeline(to_string(mem)+" ");
            obj_out.writeline("\n\n");
            obj_out.close();
        }
        else {
            io_file exec_out_obj((string(filename) + ".e").c_str(), fstream::out);
            for(auto &mem: code)
                exec_out_obj.writeline(to_string(mem)+" ");
            exec_out_obj.close();
        }
        success("Assembler: File %s completed with success\n", filename);
    } else
        fatal("Assembler: Synthesis failed" RESET "\n");
}

