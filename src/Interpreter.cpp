#include <cassert>
#include "Code.h"
#include "FileManager.h"
#include "Interpreter.h"
#include <cassert>

std::string Interpreter::get_suffix (const std::string &file_name) {
    auto pos = file_name.find_last_of('.');
    if (pos == std::string::npos)
        return "";
    return file_name.substr(pos + 1);
}

int Interpreter::get_code_number (const std::string &file_name) {
    int result = 0;
    for (const auto i: file_name) {
        if (isdigit(i))
            result = result * 10 + (i - '0');
        else {
            assert(i == '.');
            break;
        }
    }
    return result;
}

void Interpreter::test () {

}

std::tuple<int, int, int, int> Interpreter::get_code_info (const std::string &file_name) {
    auto first_dot = file_name.find_first_of('.');
    assert(first_dot != std::string::npos);
    auto second_dot = file_name.find_last_of('.');
    assert(first_dot != second_dot);
    std::string name;
    long long parameter[3] = {0};
    int parameter_num = 0;
    auto p = first_dot + 1;
    for (; p < second_dot; ++p) {
        if (!isalpha(file_name[p])) {
            assert(p == '_' || p == '.');
            name = file_name.substr(first_dot + 1, p - (first_dot + 1));
            break;
        }
    }
    for (; p < second_dot; ++p) {
        if (file_name[p] == '_')
            ++parameter_num;
        else if (isdigit(file_name[p]))
            parameter[parameter_num - 1] = parameter[parameter_num - 1] * 10 + (file_name[p] - '0');
        else
            assert(true);
    }
    return {Code::identify_name(name), parameter[0], parameter[1], parameter[2]};
}


