#ifndef PREPROCESSOR_HPP
#define PREPROCESSOR_HPP

#include <iostream>
#include <list>
#include <string>
#include <regex>

#define COMMENTS_REGEX ";(.*)"
#define LABEL_REGEX "\w*\s*:"
#define SEC_TEXT_REGEX "^SECTION TEXT(\n?)$"
#define SEC_DATA_REGEX "^SECTION DATA(\n?)$"
#define SEC_BSS_REGEX  "^SECTION BSS(\n?)$"

using namespace std;

class preprocessor{
private:
public:
    list<pair<int,string>> text;
    list<pair<int,string>>::iterator text_it, sec_text, sec_data, sec_bss;

    void sections();
    void clear_comments();

public:
    explicit preprocessor(list<string>& file_text){
        list<string>::iterator it;
        int line;
        for(line  = 1, it = file_text.begin(); it != file_text.end(); line++, ++it){
            text.emplace_back(line, it.operator*());
        }
    };

    virtual ~preprocessor() = default;

};

#endif //PREPROCESSOR_HPP
