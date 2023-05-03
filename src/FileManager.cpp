#include "FileManager.h"
#include "Interpreter.h"
#include <cassert>
#include <iostream>


/**
 * --tool function used to repeat a string--\n
 * It is used like string*int in python.
 * Well, I have to say it has no connection with FileManager.
 * @param str string to repeat
 * @param times times to repeat
 * @return the repeated string
 */
std::string repeat_str (const std::string &str, int times) {
    std::string result;
    for (int i = 0; i < times; ++i)
        result += str;
    return result;
}

/**
 * --the relative path where FO program is running--\n
 */
const fs::path FileManager::play_path = "./play_file";

/**
 * --the ofstream used to write data to files--\n
 */
std::ofstream FileManager::fout;

/**
 * --constructor function for FileManager--\n
 * It will create a temporary directory named pro_name_running.
 * Which will be deleted by the destructor function.
 * @param pro_name the program name to manage
 */
FileManager::FileManager (std::string &pro_name) {
    program_name = pro_name + "_running";
    main_path = play_path / program_name;
    Neo_office = main_path;
    Neo_name = "ready.neo";
    copy_directory(play_path / pro_name, main_path);
    assert(fs::exists(main_path));
    print_folder(main_path);
    auto Neo_path = find_Neo(main_path);
    assert(Neo_path != "");
    rename(Neo_path, Neo_office / Neo_name);
    modify_file(Neo_office / Neo_name, "0\t0\n0");
    std::cout << "Project successfully loaded" << std::endl;
}

/**
 * --the destructor function for FileManager--\n
 * It will delete the temporary directory created by constructor function.
 * If the directory is not deleted because of interruption of program,
 * the program can still run correctly and delete the file after a normal exit.
 */
FileManager::~FileManager () {
    delete_directory(main_path);
}

/**
 * --check whether the path exists--\n
 * And all the paths below are relative paths.
 * @param path relative path to check
 * @return whether the path exists
 */
bool FileManager::file_exists (const fs::path &path) {
    return fs::exists(path);
}

/**
 * --create a file and write the input into it--
 * if the file already exists, all its contents will be overwritten
 * @param file_path the path to the file
 * @param input the input data
 */
void FileManager::create_file (const fs::path &file_path, const std::string &input) {
    fout.open(file_path, std::ios_base::trunc);
    assert(fout.good());
    fout << input;
    fout.close();
}

/**
 * --modify a file--\n
 * equal to the function create_file()
 * @param file_path the path to the file
 * @param input the input data
 */
void FileManager::modify_file (const fs::path &file_path, const std::string &input) {
    create_file(file_path, input);
}

/**
 * --delete a file--\n
 * @param file_path the path to the file
 */
void FileManager::delete_file (const fs::path &file_path) {
    assert(fs::exists(file_path));
    fs::remove(file_path);
}

/**
 * --create a directory--\n
 * @param directory the path to the directory
 */
void FileManager::create_directory (const fs::path &directory) {
    assert(!fs::exists(directory));
    fs::create_directory(directory);
}

/**
 * --copy a directory--\n
 * include all its files and directories
 * @param from the path to the directory to be copied
 * @param to the path to the new directory
 */
void FileManager::copy_directory (const fs::path &from, const fs::path &to) {
    assert(fs::exists(from) || fs::is_directory(from));
    if (fs::exists(to))
        delete_directory(to);
    fs::copy(from, to, fs::copy_options::recursive);
}

/**
 * --delete the directory and all its contents--\n
 * @param directory the path to the directory
 */
void FileManager::delete_directory (const fs::path &directory) {
    assert(fs::exists(directory));
    fs::remove_all(directory);
}

/**
 * --find the path of Neo--\n
 * @param scan_path where to search
 * @return Neo's path
 */
fs::path FileManager::find_Neo (const fs::path &scan_path) {
    if (!fs::exists(scan_path) || !fs::is_directory(scan_path)) {
        return "";
    }
    std::filesystem::directory_iterator iter(scan_path);
    for (auto &i: iter) {
        if (i.status().type() == fs::file_type::directory) {
            auto tmp = find_Neo(i.path());
            if (tmp != "")
                return tmp;
        }
        else if (i.status().type() == fs::file_type::regular) {
            if (Interpreter::get_suffix(i.path().filename().string()) == "neo") {
                return i.path();
            }
        }
    }
    return "";
}

/**
 * --print the structure of a folder--\n
 * @param scan_path the path to the folder
 * @param tab how many tabs to print
 */
void FileManager::print_folder (const fs::path &scan_path, int tab) {
    assert (std::filesystem::exists(scan_path) && std::filesystem::is_directory(scan_path));

    std::cout << repeat_str("\t", tab) << scan_path.filename().string() << "{\n";
    std::filesystem::directory_iterator iter(scan_path);
    for (auto &i: iter) {
        if (i.status().type() == std::filesystem::file_type::directory)
            print_folder(i.path(), tab + 1);
        else if (i.status().type() == std::filesystem::file_type::regular)
            std::cout << repeat_str("\t", tab) << "\t" << i.path().filename().string() << std::endl;
    }
    std::cout << repeat_str("\t", tab) << "}\n";
}

/**
 * --return Neo's path--\n
 * @return Neo's path
 */
fs::path FileManager::Neo_path () {
    return Neo_office / Neo_name;
}

/**
 * --move Neo into a function--\n
 * @param func_name which function to move into
 */
void FileManager::move_Neo (const std::string &func_name) {
    if (func_name.empty())
        rename(Neo_path(), main_path / Neo_name);
    else
        rename(Neo_path(), main_path / func_name / Neo_name);
    Neo_office = main_path / func_name;
}

/**
 * --create a new function--\n
 * include the six registers
 * @param func_name name of the new function
 */
void FileManager::create_function (const std::string &func_name) {
    auto func_path = main_path / func_name;
    create_directory(func_path);
    create_file(func_path / "LF.register");
    create_file(func_path / "PC.register");
    create_file(func_path / "R1.register");
    create_file(func_path / "R2.register");
    create_file(func_path / "R3.register");
    create_file(func_path / "R4.register");
}

/**
 * --create a list of files in a directory--\n
 * @param directory the path to the directory
 * @param need_files need the list of files or directories
 * @return a string list of files/directories
 */
std::list<std::string> FileManager::return_list (const fs::path &directory, bool need_files) {
    assert (std::filesystem::exists(directory) && std::filesystem::is_directory(directory));

    std::list<std::string> result;
    std::filesystem::directory_iterator iter(directory);
    for (auto &i: iter) {
        if (fs::is_directory(i.path()) ^ need_files)
            result.push_back(i.path().filename().string());
    }
    return result;
}

/**
 * --test the FileManager--\n
 */
void FileManager::test () {

    std::cout << "program list:" << std::endl;
    auto pro_list = FileManager::return_list(FileManager::play_path, false);
    for (auto &i: pro_list)
        if (FileManager::find_Neo(FileManager::play_path / i) != "")
            std::cout << i << std::endl;


    std::string pro_name = "divide";
    FileManager fManager(pro_name);
    std::cin.get();
    fManager.create_function("foo");
    std::cin.get();
    auto old_Neo = fManager.Neo_path();
    fManager.move_Neo("func_divide");
    std::cin.get();
    puts(file_exists(old_Neo) ? "exists" : "gone");
    auto list = return_list(fManager.Neo_office, true);
    std::cin.get();
    for (auto &i: list)
        if (Interpreter::is_focode(i))
            std::cout << i << std::endl;
}

