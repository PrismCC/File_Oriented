#ifndef FILE_ORIENTED_INTERPRETER_H
#define FILE_ORIENTED_INTERPRETER_H

#include <string>
#include <map>

class Interpreter {
    friend class Code;
public:
    static std::string get_suffix (const std::string &file_name);

    static inline bool is_focode (const std::string &file_name) { return get_suffix(file_name) == "focode"; };

    static inline bool is_label (const std::string &file_name) {
        return is_focode(file_name) && file_name.find("label") != std::string::npos;
    };

    static inline bool is_code (const std::string &file_name) {
        return is_focode(file_name) && file_name.find("label") == std::string::npos;
    };

    static bool is_register (const std::string &file_name) { return get_suffix(file_name) == "register"; };

    static void test ();

private:
    static int get_code_number (const std::string &file_name);

    static int evaluate_parameter (const std::string &para, const std::map<std::string, int> &label_map);

    static std::string get_label (const std::string &file_name);

    static std::map<std::string, int> get_label_map (const std::string &func_path);

    static std::tuple<int, int, int, int>
    get_code_info (const std::string &file_name, const std::map<std::string, int> &label_map);

};


#endif //FILE_ORIENTED_INTERPRETER_H
