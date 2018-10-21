#include "../include/io_file.hpp"

bool io_file::is_open() {
    return this->file_stream.is_open();
}

void io_file::close() {
    this->file_stream.close();
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

string io_file::read_in_string(){
    string buffer;
    while(!this->file_stream.eof())
        buffer += (char) this->file_stream.get();
    this->file_stream.seekg(0, fstream::beg);
    return buffer;
}

void io_file::writeline(const string &line) {
    this->file_stream.write(line.c_str(), line.size());
}

void io_file::writefile(deque<pair<int,string>>& content) {
    deque<pair<int,string>>::iterator it;
    for(it = content.begin(); it != content.end(); ++it){
        this->file_stream.write(it.operator*().second.c_str(), it.operator*().second.size());
        this->file_stream.put('\n');
    }
}

