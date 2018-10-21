#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <cstdio>
#include <cstdarg>

#define TEXT_COLOR_BLACK   "\x1b[30m"
#define TEXT_COLOR_RED     "\x1b[31m"
#define TEXT_COLOR_GREEN   "\x1b[32m"
#define TEXT_COLOR_YELLOW  "\x1b[33m"
#define TEXT_COLOR_BLUE    "\x1b[34m"
#define TEXT_COLOR_MAGENTA "\x1b[35m"
#define TEXT_COLOR_CYAN    "\x1b[36m"
#define TEXT_COLOR_WHITE   "\x1b[37m"

#define BKGD_COLOR_BLACK   "\x1b[40m"
#define BKGD_COLOR_RED     "\x1b[41m"
#define BKGD_COLOR_GREEN   "\x1b[42m"
#define BKGD_COLOR_YELLOW  "\x1b[43m"
#define BKGD_COLOR_BLUE    "\x1b[44m"
#define BKGD_COLOR_MAGENTA "\x1b[45m"
#define BKGD_COLOR_CYAN    "\x1b[46m"
#define BKGD_COLOR_WHITE   "\x1b[47m"

#define TEXT_BCOLOR_BLACK   "\x1b[90m"
#define TEXT_BCOLOR_RED     "\x1b[91m"
#define TEXT_BCOLOR_GREEN   "\x1b[92m"
#define TEXT_BCOLOR_YELLOW  "\x1b[93m"
#define TEXT_BCOLOR_BLUE    "\x1b[94m"
#define TEXT_BCOLOR_MAGENTA "\x1b[95m"
#define TEXT_BCOLOR_CYAN    "\x1b[96m"
#define TEXT_BCOLOR_WHITE   "\x1b[97m"

#define BKGD_BCOLOR_BLACK   "\x1b[100m"
#define BKGD_BCOLOR_RED     "\x1b[101m"
#define BKGD_BCOLOR_GREEN   "\x1b[102m"
#define BKGD_BCOLOR_YELLOW  "\x1b[103m"
#define BKGD_BCOLOR_BLUE    "\x1b[104m"
#define BKGD_BCOLOR_MAGENTA "\x1b[105m"
#define BKGD_BCOLOR_CYAN    "\x1b[106m"
#define BKGD_BCOLOR_WHITE   "\x1b[107m"

#define TEXT_BOLD_UNDL   "\x1b[1m"

#define RESET   "\x1b[0m"

using namespace std;

namespace console{
    static void assembler_help(){
        printf("Uso:\n"
               "Em sistemas Unix:\t./montador myfile1.asm ... myfileN.asm\n"
               "Em sistemas Windows:\tmontador myfile.asm ... myfileN.asm\n\n"
               "Flags disponiveis:\n"
               "-h\t= ver ajuda\n"
               "-pre\t= ver arquivo pre-processado\n"
               "-o\t= gerar executável, aka: montar e ligar\n"
               "-c\t= apenas montar (default)\n"
               "-v\t= mostrar versão\n\n");
    }

    static void linker_help(){
        printf("Uso:\n"
               "Em sistemas Unix:\t./ligador myfile1.obj ... myfileN.obj\n"
               "Em sistemas Windows:\t ligador myfile.obj ... myfileN.obj\n\n");
    }

    static void sucess(const char* msg_fmt,...){
        printf(TEXT_COLOR_GREEN "[SUCESS] ");
        va_list arg_list;
        va_start(arg_list, msg_fmt);
        vprintf(msg_fmt, arg_list);
        va_end(arg_list);
        printf(RESET);
    }

    static void error(const char* msg_fmt,...) {
        printf(TEXT_COLOR_RED "[ERROR] ");
        va_list arg_list;
        va_start(arg_list, msg_fmt);
        vprintf(msg_fmt, arg_list);
        va_end(arg_list);
        printf(RESET);
    }

    static void fatal(const char* msg_fmt,...) {
        printf(BKGD_COLOR_RED TEXT_BCOLOR_YELLOW "[FATAL] ");
        va_list arg_list;
        va_start(arg_list, msg_fmt);
        vprintf(msg_fmt, arg_list);
        va_end(arg_list);
        printf(RESET);
    }

    static void info(const char* msg_fmt,...) {
        printf(TEXT_COLOR_BLUE "[INFO] ");
        va_list arg_list;
        va_start(arg_list, msg_fmt);
        vprintf(msg_fmt, arg_list);
        va_end(arg_list);
        printf(RESET);
    }

    static void warning(const char* msg_fmt,...) {
        printf(TEXT_BCOLOR_YELLOW "[WARNING] ");
        va_list arg_list;
        va_start(arg_list, msg_fmt);
        vprintf(msg_fmt, arg_list);
        va_end(arg_list);
        printf(RESET);
    }

    static void message(const char* msg_fmt,...){
        va_list arg_list;
        va_start(arg_list, msg_fmt);
        vprintf(msg_fmt, arg_list);
        va_end(arg_list);
    }

    static void customize_flags(int num_flags, ...){
        va_list arg_list;
        va_start(arg_list, num_flags);
        for(int i = 0; i < num_flags; i++){
            printf("%s", va_arg(arg_list, const char*));
        }
        va_end(arg_list);
    }

    static void reset_flags(){
        printf(RESET);
    }
};

#endif //CONSOLE_HPP
