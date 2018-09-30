#include <iostream>

#include "../include/ASM_file.hpp"

using namespace std;

int main() {
    ASM_file input("../docs/bin.asm", fstream::in);

    list<string> text = input.readfile();


    input.~ASM_file();

    return 0;
}