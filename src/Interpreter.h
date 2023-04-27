#ifndef FILE_ORIENTED_INTERPRETER_H
#define FILE_ORIENTED_INTERPRETER_H

#include <string>

class Interpreter {
public:
    static std::string get_suffix (const std::string &file_name);

    static bool is_code (const std::string &file_name) { return get_suffix(file_name) == "focode"; };

    static bool is_register (const std::string &file_name) { return get_suffix(file_name) == "register"; };

private:
    static int get_code_number (const std::string &file_name);

    static std::tuple<int, int, int, int> get_code_info (const std::string &file_name);

    static void test ();
};


#endif //FILE_ORIENTED_INTERPRETER_H
