#include "../include/io_file.hpp"

bool io_file::is_open() {
    return this->file_stream.is_open();
}

string io_file::get_filename() {
    return this->filename;
}

deque<string> io_file::readfile() {
    deque<string> text;
    string buffer;
    while(!this->file_stream.eof()){
        getline(this->file_stream, buffer);
        text.emplace_back(buffer);
    }
    this->file_stream.seekg(0, fstream::beg);
    return text;
}

void io_file::writefile(deque<pair<int,string>>& content) {
    deque<pair<int,string>>::iterator it;
    for(it = content.begin(); it != content.end(); ++it){
        this->file_stream.write(it.operator*().second.c_str(), it.operator*().second.size());
        this->file_stream.put('\n');
    }
}
