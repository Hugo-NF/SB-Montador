#ifndef MONTADOR_PREPROCESSOR_HPP
#define MONTADOR_PREPROCESSOR_HPP

#include <deque>
#include <string>
#include <regex>

#include "console.hpp"

#define COMMENTS_REGEX ";(.*)"
#define LABEL_REGEX "\w*\s*:"
#define SEC_TEXT_REGEX "^SECTION TEXT(\n?)$"
#define SEC_DATA_REGEX "^SECTION DATA(\n?)$"
#define SEC_BSS_REGEX  "^SECTION BSS(\n?)$"

using namespace std;
using namespace console;

class preprocessor{
private:
public:
    deque<pair<int, string>> text;
    deque<regex> sections;
    deque<regex> symbols;
    int text_section, data_section, bss_section;

    void clear_comments(string& line);
    void process_file();

public:
    explicit preprocessor(deque<string>& file_text){
        text_section = data_section = bss_section = -1;
        for(int line = 0; line < file_text.size(); line++) {
            clear_comments(file_text[line]);
            if(!file_text[line].empty())
                text.emplace_back(line + 1, file_text[line]);
        }
        sections.emplace_back(SEC_TEXT_REGEX, regex::ECMAScript);
        sections.emplace_back(SEC_DATA_REGEX, regex::ECMAScript);
        sections.emplace_back(SEC_BSS_REGEX, regex::ECMAScript);

        symbols.emplace_back(LABEL_REGEX, regex::ECMAScript);
    }

    virtual ~preprocessor() = default;
};

#endif //MONTADOR_PREPROCESSOR_HPP
