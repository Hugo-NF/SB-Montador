#ifndef MONTADOR_TABLES_HPP
#define MONTADOR_TABLES_HPP

#include <map>
#include <string>

#define INST_ADD        1
#define INST_SUB        2
#define INST_MUL        3
#define INST_DIV        4
#define INST_JMP        5
#define INST_JMPN       6
#define INST_JMPP       7
#define INST_JMPZ       8
#define INST_COPY       9
#define INST_LOAD       10
#define INST_STORE      11
#define INST_INPUT      12
#define INST_OUTPUT     13
#define INST_STOP       14
#define INST_CONST      20
#define INST_SPACE      21
#define INST_SECTION    22
#define INST_PUBLIC     23
#define INST_EXTERN     24
#define INST_END        25



#define IF_TRUE_EVAL "1"

#define COMMENTS ";(.*)"
#define TABS_SPACES "(\t|\\s)+"
#define LINE_BEGIN "^ "
#define OPR_REGEX "(?:|\t|\\s)*([,+\\-])(?:|\t|\\s)*"
#define LABEL_DIV "(\t|\\s)+:"

#define LABEL_REGEX "^[A-Za-z](\\w+)?$"
#define NUMBER_REGEX "^[0-9]+$"
#define LINE_REGEX "^([A-Za-z_](?:\\w)*):(?:\\s|\n)(\\w+)?(?:.*)"
#define INST_REGEX "^([A-Za-z_](?:\\w)*)(?: (.*))?"

#define DIR_EQU_REGEX "(.*): EQU (.*)"
#define DIR_IF_REGEX "^IF (.*)$"
#define DIR_BEGIN_REGEX "^(.*): BEGIN"

#define SEC_TEXT_REGEX "^(\t|\\s)*SECTION TEXT(\t|\\s)*$"
#define SEC_DATA_REGEX "^(\t|\\s)*SECTION DATA(\t|\\s)*$"
#define SEC_BSS_REGEX  "^(\t|\\s)*SECTION BSS(\t|\\s)*$"

using namespace std;

namespace tables{
    static  map<string, pair<int, int>> instructions = {{"ADD",    pair<int, int>(1, 2)},   //OPCODES
                                                        {"SUB",    pair<int, int>(2, 2)}
                                                        {"MUL",    pair<int, int>(3, 2)},
                                                        {"DIV",    pair<int, int>(4, 2)},
                                                        {"JMP",    pair<int, int>(5, 2)},
                                                        {"JMPN",   pair<int, int>(6, 2)},
                                                        {"JMPP",   pair<int, int>(7, 2)},
                                                        {"JMPZ",   pair<int, int>(8, 2)},
                                                        {"COPY",   pair<int, int>(9, 3)},
                                                        {"LOAD",   pair<int, int>(10, 2)},
                                                        {"STORE",  pair<int, int>(11, 2)},
                                                        {"INPUT",  pair<int, int>(12, 2)},
                                                        {"OUTPUT", pair<int, int>(13, 2)},
                                                        {"STOP",   pair<int, int>(14, 1)},
                                                        {"CONST",  pair<int, int>(20, 1)},  //Directives
                                                        {"SPACE",  pair<int, int>(21, 1)},
                                                        {"SECTION",pair<int, int>(22, 0)},
                                                        {"PUBLIC", pair<int, int>(23, 0)},
                                                        {"EXTERN", pair<int, int>(24, 0)},
                                                        {"END",    pair<int, int>(25, 0)}};
};

#endif //MONTADOR_TABLES_HPP
