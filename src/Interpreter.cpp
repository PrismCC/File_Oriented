#include <cassert>
#include "Code.h"
#include "FileManager.h"
#include "Interpreter.h"
#include <map>
#include <algorithm>

std::string Interpreter::get_suffix (const std::string &file_name) {
    auto pos = file_name.find_last_of('.');
    if (pos == std::string::npos)
        return "";
    return file_name.substr(pos + 1);
}

int Interpreter::get_code_number (const std::string &file_name) {
    assert(is_focode(file_name));
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

std::tuple<int, int, int, int>
Interpreter::get_code_info (const std::string &file_name, const std::map<std::string, int> &label_map) {
    assert(is_focode(file_name));
    auto first_dot = file_name.find_first_of('.');
    assert(first_dot != std::string::npos);
    auto second_dot = file_name.find_last_of('.');
    assert(second_dot != std::string::npos);
    assert(first_dot != second_dot);
    int parameter[3] = {0};
    int parameter_num = 0;
    auto from = first_dot + 1;
    auto to = file_name.find('_', from);
    if (to == std::string::npos) {
        to = second_dot;
        std::string name = file_name.substr(from, to - from);
        return {Code::identify_name(name), 0, 0, 0};
    }

    std::string name = file_name.substr(from, to - from);
    from = to + 1;

    while ((to = file_name.find('_', from)) != std::string::npos) {
        parameter[parameter_num++] = evaluate_parameter(file_name.substr(from, to - from), label_map);
        from = to + 1;
    }
    parameter[parameter_num++] = evaluate_parameter(file_name.substr(from, second_dot - from), label_map);
    assert(parameter_num <= 3);
    return {Code::identify_name(name), parameter[0], parameter[1], parameter[2]};
}

std::map<std::string, int> Interpreter::get_label_map (const std::string &func_path) {
    std::map<std::string, int> m;
    auto list = FileManager::return_list(func_path, true);
    int id = 0;
    for (auto &i: list) {
        if (is_label(i)) {
            auto label_name = get_label(i);
            m.insert({label_name, id++});
        }
    }
    return m;
}

std::string Interpreter::get_label (const std::string &file_name) {
    assert(is_label(file_name));
    auto from = std::find(file_name.begin(), file_name.end(), '_') + 1;
    auto to = std::find(from, file_name.end(), '.');
    assert(from != file_name.end() && to != file_name.end());
    std::string s;
    std::copy(from, to, std::back_inserter(s));
    return s;
}

int Interpreter::evaluate_parameter (const std::string &para, const std::map<std::string, int> &label_map) {
    assert(!para.empty());
    if (isdigit(para[0]))
        return (int) atoi(para.data());
    assert(label_map.find(para) != label_map.end());
    return label_map.at(para);
}

void Interpreter::test () {
    std::string test_path = "play_file/divide/func_divide";
    auto label_map = get_label_map(test_path);
    auto list = FileManager::return_list(test_path);
    for (auto const &i: list) {
        if(is_register(i)||!is_focode(i))
            continue;
        Code c(i, label_map);
        c.printInfo();
    }

}
