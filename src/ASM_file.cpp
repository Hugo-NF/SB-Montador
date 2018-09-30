#include "../include/ASM_file.hpp"

list<string> ASM_file::readfile() {
    list<string> text;
    string buffer;
    while(!this->file_stream.eof()){
        getline(this->file_stream, buffer);
        text.emplace_back(buffer);
    }
    this->file_stream.seekg(0, fstream::beg);
    return text;
}

void ASM_file::writefile(list<string>& content) {
    list<string>::iterator it;
    for(it = content.begin(); it != content.end(); ++it){
        this->file_stream.write(it.operator*().c_str(), it.operator*().size());
        this->file_stream.put('\n');
    }
}


