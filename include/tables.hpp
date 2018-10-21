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
#define DIR_CONST      20
#define DIR_SPACE      21
#define DIR_SECTION    22
#define DIR_PUBLIC     23
#define DIR_EXTERN     24
#define DIR_END        25

#define IF_TRUE_EVAL "1"

#define COMMENTS "(\t|\\s)*;(.*)"
#define TABS_SPACES "(\t|\\s)+"
#define LINE_BEGIN "^ "
#define OPR_REGEX "(?:|\t|\\s)*([,+\\-])(?:|\t|\\s)*"
#define LABEL_DIV "(\t|\\s)+:"
#define LABEL_STA  "^(?:[A-Za-z_]\\w*):$"

#define LABEL_REGEX "^[A-Za-z_](\\w+)?$"
#define NUMBER_REGEX "^(?:\\s|\t)*([0-9]+)(?:\\s|\t)*"
#define LINE_REGEX "^([A-Za-z_](?:\\w)*):(?:\\s|\n)(\\w+)?(?:(.*))"
#define INST_REGEX "^([A-Za-z_](?:\\w)*)(?: (.*))?"

#define UNIVERSAL_REGEX "^(?:([A-Za-z_]\\w*): )?([A-Za-z]+)(?: ([A-Za-z_]\\w*))?(?: ([+-]) )?(?: ?([-\\d]+))?(?: ,)?(?: ([A-Za-z_]\\w*))?(?: ([+-]) )?(?: ?([-\\d]+))?$"

#define DIR_EQU_REGEX "(.*): EQU (.*)"
#define DIR_IF_REGEX "^IF (.*)$"
#define DIR_BEGIN_REGEX "^(.*): BEGIN"

#define SECTION_REGEX "^(?:\t|\\s)*(?:SECTION(?:\t|\\s)*(.*))(?:\t|\\s)*$"

#endif //MONTADOR_TABLES_HPP
