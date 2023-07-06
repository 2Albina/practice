# Проверка версии CMake.
cmake_minimum_required(VERSION 3.16)

# позволит при сборке увидеть время на компиляцию или линковку
 set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
 set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")

# название проекта
project(myProject)

# создаёт исполняемый файл с именем myProject из исходников.
add_executable(myProject Source1.cpp Source2.cpp Source3.cpp Source4.cpp Source5.cpp)

# добавляет заголовочные файлы к PRECOMPILE_HEADERS целевым свойствам myProject.
target_precompile_headers(myProject PUBLIC stdafx.h)
