cmake_minimum_required(VERSION 3.25)
project(File_Oriented)

set(CMAKE_CXX_STANDARD 20)

add_executable(File_Oriented src/main.cpp src/Interpreter.cpp src/Interpreter.h src/Editor.cpp src/Editor.h src/FileManager.cpp src/FileManager.h src/Code.cpp src/Code.h src/Register.cpp src/Register.h)
