#include "../include/preprocessor.hpp"

void preprocessor::clear_comments(string& line) {
    regex comment_pattern(COMMENTS_REGEX, regex::ECMAScript);
    line.assign(regex_replace(line, comment_pattern, ""));
}

void preprocessor::process_file() {

}

