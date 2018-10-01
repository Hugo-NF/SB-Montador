#include "../include/preprocessor.hpp"

void preprocessor::clear_comments() {
    regex comment_pattern(COMMENTS_REGEX, regex::ECMAScript);
    list<pair<int, string>>::iterator erase_it;

    for(text_it = text.begin(); text_it != text.end(); ++text_it){
        text_it->second.assign(regex_replace(text_it->second, comment_pattern, ""));

        if(text_it->second.empty()) {
            text_it = text.erase(text_it);
            text_it--;
        }
    }
}

void preprocessor::sections() {
    int t_match = 0, d_match = 0, b_match = 0;
    regex sec_text(SEC_TEXT_REGEX, regex::ECMAScript | regex::icase);
    regex sec_data(SEC_DATA_REGEX, regex::ECMAScript | regex::icase);
    regex sec_bss(SEC_BSS_REGEX, regex::ECMAScript | regex::icase);

    for(text_it = text.begin(); text_it != text.end(); ++text_it) {
        if (regex_match(text_it->second, sec_text)){
            this->sec_text = text_it;
            t_match++;
        }
        else if (regex_match(text_it->second, sec_data)){
            this->sec_data = text_it;
            d_match++;
        }
        else if(regex_match(text_it->second, sec_bss)){
            this->sec_bss = text_it;
            b_match++;
        }
    }


    if(t_match < 1)
        message(0, "TokenError: Section TEXT was not declared\n");
    else
        cout << "TokenError: Section TEXT was declared more than once. Last seen at line " << this->sec_text.operator*().first << endl;
    if(d_match > 1)
        cout << "TokenError: Section DATA was declared more than once. Last seen at line " << this->sec_data.operator*().first << endl;
    if(b_match > 1)
        cout << "TokenError: Section BSS was declared more than once. Last seen at line " << this->sec_bss.operator*().first << endl;

}
