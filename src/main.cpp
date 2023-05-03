#include <iostream>
#include "FileManager.h"
#include "Interpreter.h"
#include <string>

int main () {
    std::cout << "This is File_Oriented" << std::endl;
    Interpreter::test();
    std::cin.get();
    return 0;
}
