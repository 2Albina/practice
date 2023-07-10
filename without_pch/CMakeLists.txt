# Проверка версии CMake.
cmake_minimum_required(VERSION 3.16)

# название проекта
project(myProject)

# создаёт исполняемый файл с именем myProject из исходников.
add_executable(myProject Source1.cpp Source2.cpp Source3.cpp Source4.cpp Source5.cpp)
