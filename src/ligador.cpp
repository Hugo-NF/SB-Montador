#include <iostream>
#include <string>
#include <map>
#include <regex>
#include <vector>

#include "../include/tables.hpp"

using namespace std;

int main(int argc, char **argv){
    vector<string> lines = {"A_1: ADD N1",
                            "MOD: EXTERN",
                            "ADD N1",
                            "OUTPUT N1 + 1",
                            "COPY N2 + 2 , N3 + 5",
                            "STOP",
                            "_A: CONST -5",
                            "B: SPACE 4",
                            "PUBLIC N3",
                            "MOD: BEGIN",
                            "END"};
    cmatch m;
    regex r(UNIVERSAL_REGEX, regex::ECMAScript);
    for(int line = 0; line < lines.size(); line++){
        printf("Line: %s\n", lines[line].c_str());
        if(regex_search(lines[line].c_str(), m, r)){
            for(auto it = m.begin(); it != m.end(); it++){
                printf("Group: %s\n", it.operator*().str().c_str());
            }
            printf("\n\n");
        }
        else
            printf("DOES NOT MATCH\n\n");
    }



    return 0;
}
