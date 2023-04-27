#ifndef FILE_ORIENTED_FILEMANAGER_H
#define FILE_ORIENTED_FILEMANAGER_H

#include <fstream>
#include <filesystem>
#include <list>

namespace fs = std::filesystem;

class FileManager {
public:
    explicit FileManager (std::string &pro_name);

    ~FileManager();

    bool find_Neo (const fs::path &scan_path);

    static void test ();

private:
    static void print_folder (const fs::path &scan_path, int tab = 0);

    static inline bool file_exists (const fs::path &path);

    static inline void create_file (const fs::path &file_path, const std::string &input = "0");

    static inline void modify_file (const fs::path &file_path, const std::string &input = "0");

    static inline void delete_file (const fs::path &file_path);

    static inline void create_directory (const fs::path &directory);

    static inline void copy_directory (const fs::path &from,const fs::path &to);

    static inline void delete_directory (const fs::path &directory);

    static std::list<std::string> code_list(const fs::path &directory);

    inline fs::path Neo_path();

    inline void move_Neo (const std::string &func_name);

    inline void create_function (const std::string &func_name);

    static const fs::path play_path;
    static std::ofstream fout;
    std::string program_name;
    fs::path main_path;
    fs::path Neo_office;
    std::string Neo_name;
};


#endif //FILE_ORIENTED_FILEMANAGER_H
