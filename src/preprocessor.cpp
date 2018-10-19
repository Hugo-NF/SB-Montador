#include "../include/preprocessor.hpp"

bool preprocessor::is_module(int line) {
    smatch matches;
    string label;
    if(regex_search(text[line].second, matches, directives[2])) {
        label = matches[1].str();
        if (valid_label(label)){
            text.erase(text.begin() + line);
            return true;
        } else {
            text.erase(text.begin() + line);
            error("Preprocessor - lexical: Bad formed token \"%s\" in module identification\n", label.c_str());
        }
    }
    return false;
}

bool preprocessor::is_section(int line) {
    if(regex_match(text[line].second, sections[0])) {
        if(text_section == -1)
            text_section = line;
        else
            warning("Preprocessor - semantic: SECTION TEXT redeclared. First seen at line %d\n", text[text_section].first);
    }
    else if(regex_match(text[line].second, sections[1])) {
        if(data_section == -1)
            data_section = line;
        else
            warning("Preprocessor - semantic: SECTION DATA redeclared. First seen at line %d\n", text[data_section].first);
    }
    else if(regex_match(text[line].second, sections[2])){
        if(bss_section == -1)
            bss_section = line;
        else
            warning("Preprocessor - semantic: SECTION BSS redeclared. First seen at line %d\n", text[bss_section].first);
    }
    else
        return false;

    return true;
}

void preprocessor::clear_line(string& line) {
    line.assign(regex_replace(line, formatting[0], ""));
    line.assign(regex_replace(line, formatting[1], " "));
    line.assign(regex_replace(line, formatting[2], ""));
    line.assign(regex_replace(line, formatting[3], ":"));
    line.assign(regex_replace(line, formatting[4], " $1"));
}

bool preprocessor::found_section() {
    return (text_section != -1) || (bss_section != -1) || (data_section != -1);
}

int preprocessor::valid_number(string& token){
    smatch m;
    if(regex_search(token, m, symbols[1]))
        return stoi(m[0].str());
    else
        return 1;
}

bool preprocessor::valid_label(string& label) {
    return regex_match(label, symbols[0]);
}

int preprocessor::has_label(int line){
    smatch matches;
    string label, op_mne, rline;
    int alloc = 1;

    if(regex_search(text[line].second, matches, symbols[2])){
        label = matches[1].str();
        op_mne = matches[2].str();
        rline = matches[3].str();
        if(instructions[op_mne].first == INST_EXTERN) {
            symbols_use[label] = code_size;
        }
        else if(instructions[op_mne].first == INST_SPACE){
            if(!rline.empty())
                alloc = valid_number(rline);
        }

        if(labels_addresses.count(label) == 0){
            labels_addresses[label] = code_size;
            if(op_mne.empty())
                return 0;
            else{
                if(instructions.count(op_mne))
                    return alloc * instructions[op_mne].second;
                else
                    error("Preprocessor - syntatic: Instruction mnemonic \"%s\" at line %d does NOT exist.\n", op_mne.c_str(), text[line].first);
            }
        }
        else
            error("Preprocessor - semantic: Label \"%s\" at line %d was redeclared.\n", label.c_str(), text[line].first);
    }
    else if(regex_search(text[line].second, matches, symbols[3])){
        op_mne = matches[1].str();
        label = matches[2].str();
        if(instructions[op_mne].first == INST_PUBLIC){
            symbols_definition[label] = code_size;
        }
        if(instructions.count(op_mne))
            return instructions[op_mne].second;
        else
            error("Preprocessor - syntatic: Instruction mnemonic \"%s\" at line %d does NOT exist.\n", op_mne.c_str(), text[line].first);
    }
    return 0;
}

bool preprocessor::is_equ(int line) {
    smatch matches;
    string label, value;

    if(regex_search(text[line].second, matches, directives[0])){
        label = matches[1].str();
        value = matches[2].str();
        if(valid_label(label)){
            if(equ_definitions.count(label))
                error("Preprocessor - semantic: EQU label \"%s\" redeclared\n", label.c_str());
            else
                equ_definitions[label] = value;
            return true;
        }
        else
            error("Preprocessor - lexical: Bad formed token \"%s\" in EQU condition. Line %d\n", label.c_str(), text[line].first);
    }
    else
        return false;
}

bool preprocessor::is_if(int line) {
   smatch matches;
   string label;

   if(regex_search(text[line].second, matches, directives[1])) {
       label = matches[1].str();
       if(valid_label(label)){
           if (equ_definitions[label] == IF_TRUE_EVAL)
                if_eval = true;
           return true;
       }
       else
           error("Preprocessor - lexical: Bad formed token \"%s\" in IF condition. Line %d\n", label.c_str(), text[line].first);
   }
   return false;
}

deque<pair<int, string>>& preprocessor::process_file() {
    module_def = is_module(0);
    int stop = text.size();
    for(int line = 0; line < stop; line++){
        if(is_equ(line)){
            text.erase(text.begin()+line);
            stop = text.size();
            line--;
        }
        else if(!is_section(line) && !found_section())
            warning("Preprocessor - semantic: Statement at line %d declared outside any section\n", text[line].first);

        else if(is_if(line)){
            if(line != stop-1){
                if(!if_eval){
                    if_eval = false;
                    text.erase(text.begin()+line);
                    text.erase(text.begin()+line);
                    stop = text.size();
                    line--;
                }
                else {
                    text.erase(text.begin()+line);
                    stop = text.size();
                    line--;
                }
            }
            else {
                text.erase(text.begin() + line);
                error("Preprocessor - syntatic: IF clause without a target line. Line %d\n", text[line].first);
            }
        }
        else
            code_size += has_label(line);
    }
    for(auto it = symbols_definition.begin(); it != symbols_definition.end(); ++it)
        symbols_definition[it.operator*().first] = labels_addresses[it.operator*().first];

    return text;
}
