#include "Code.h"
#include "Interpreter.h"
#include <string>
#include <cassert>
#include <map>
#include <iostream>

const int code_num = 22;
const std::map<std::string, int> Code::name_id_map{{"none",  0},
                                                   {"beg", 1},
                                                   {"ret",   2},
                                                   {"halt",  3},
                                                   {"load",  10},
                                                   {"save",  11},
                                                   {"copy",  12},
                                                   {"set",   13},
                                                   {"res",   14},
                                                   {"addi",  20},
                                                   {"add",   21},
                                                   {"sub",   22},
                                                   {"mut",   23},
                                                   {"and",   30},
                                                   {"or",    31},
                                                   {"not",   32},
                                                   {"jmp",   40},
                                                   {"zero",  41},
                                                   {"neg",   42},
                                                   {"call",  50},
                                                   {"label", 60}};
const std::map<int, std::string> Code::id_name_map{{0,  "none"},
                                                   {1,  "beg"},
                                                   {2,  "ret"},
                                                   {3,  "halt"},
                                                   {10, "load"},
                                                   {11, "save"},
                                                   {12, "copy"},
                                                   {13, "set"},
                                                   {14, "res"},
                                                   {20, "addi"},
                                                   {21, "add"},
                                                   {22, "sub"},
                                                   {23, "mut"},
                                                   {30, "and"},
                                                   {31, "or"},
                                                   {32, "not"},
                                                   {40, "jmp"},
                                                   {41, "zero"},
                                                   {42, "neg"},
                                                   {50, "call"},
                                                   {60, "label"}};

int Code::identify_name (std::string &name) {
    assert(name_id_map.find(name) != name_id_map.end());
    return name_id_map.at(name);
}

std::string Code::identify_id (int id) {
    assert(id_name_map.find(id) != id_name_map.end());
    return id_name_map.at(id);
}

Code::Code (const std::string &name, const std::map<std::string, int> &label_map) {
    number = Interpreter::get_code_number(name);
    auto data = Interpreter::get_code_info(name, label_map);
    type = std::get<0>(data);
    para1 = std::get<1>(data);
    para2 = std::get<2>(data);
    para3 = std::get<3>(data);
    path = name;
}

void Code::printInfo () {
    std::cout << "name: " << path << std::endl << "type: " << id_name_map.at(type) << "  number: " << number
              << std::endl
              << "parameters: " << para1 << " " << para2 << " " << para3 << std::endl << std::endl;
}
