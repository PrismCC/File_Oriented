#include "Code.h"
#include <string>
#include <cassert>

const int code_num = 22;
std::string code_table[code_num] = {"None",
                              "Load", "Save", "Res", "Take", "Pack",
                              "Copy", "Set",
                              "Addi", "Add", "Sub", "Mut",
                              "And", "Or", "Not",
                              "Jmp", "Zero", "Neg",
                              "Beg", "End", "Func", "Halt"};

int Code::identify_name (std::string &name) {
    for(int i=0;i<code_num;++i)
        if(code_table[i]==name)
            return i;
    assert(true);
    return -1;
}
