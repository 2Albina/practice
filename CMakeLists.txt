cmake_minimum_required(VERSION 3.16.3)

# позволит при сборке увидеть время на компиляцию или линковку
set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")

# позволяет вывести для каждого юнита время каждой фазы компиляции
add_compile_options(-ftime-report)

# название проекта
project(with_pch)
 
# Установка переменной со списком исходников для исполняемого файла
set(SOURCE_LIB stdafx.cpp)
 
# создание статической библиотеки с именем stdafx
add_library(stdafx STATIC ${SOURCE_LIB})

# добавляет заголовочные файлы к PRECOMPILE_HEADERS целевым свойствам stdafx. 
# именованный объект stdafx должен быть создан с помощью такой команды, 
# как add_executable() или add_library(), и не должен быть целевым псевдонимом.
target_precompile_headers(stdafx PUBLIC stdafx.h)

# Установка переменной со списком исходников для исполняемого файла
set(SOURCE_EXE with_pch_1.cpp with_pch_2.cpp with_pch_3.cpp)

# создаёт исполняемый файл с именем main из исходников SOURCE_EXE.
add_executable(main ${SOURCE_EXE})
