#ifndef MONTADOR_TABLES_HPP
#define MONTADOR_TABLES_HPP

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
#define NUMBER_REGEX "^(?:\\s|\t)*([0-9]+)(?:\\s|\t)*"
#define LINE_REGEX "^([A-Za-z_](?:\\w)*):(?:\\s|\n)(\\w+)?(?:(.*))"
#define INST_REGEX "^([A-Za-z_](?:\\w)*)(?: (.*))?"

#define DIR_EQU_REGEX "(.*): EQU (.*)"
#define DIR_IF_REGEX "^IF (.*)$"
#define DIR_BEGIN_REGEX "^(.*): BEGIN"

#define SECTION_REGEX "^(?:\t|\\s)*(?:SECTION(?:\t|\\s)*(.*))(?:\t|\\s)*$"

#endif //MONTADOR_TABLES_HPP
