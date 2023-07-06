## Изучить CMake. С его помощью создать инструкции для сборки проектов с предкомпилированным заголовком и без. Собрать проекты, используя разные компиляторы (gcc, clang, msvc).

*CMake* - кроссплатформенное программное средство автоматизации сборки
программного обеспечения из исходного кода. Не занимается
непосредственно сборкой, а лишь генерирует файлы сборки из
предварительно написанного файла сценария CMakeLists.txt и предоставляет
простой единый интерфейс управления. Помимо этого, способно
автоматизировать процесс установки и сборки пакетов.

CMake может создавать файлы проектов для нескольких популярных интегрированных средств разработки. Может создавать сценарии
сборки для MSBuild и nmake в Windows, make на Unix-подобных системах.
CMake поддерживает обширный список компиляторов, в который входят в том
числе Clang, GNU GCC, MSVC.

Сборка программы с помощью CMake представляет собой двухэтапный процесс.
На первом этапе стандартные файлы сборки генерируются из файлов
конфигурации (CMakeLists.txt), которые написаны на языке CMake. Затем
задействуются системные инструменты сборки, такие как make, msbuild,
используемые для непосредственной компиляции программ.

**Подготовка исходных файлов**

Проект состоит из Source.cpp и stdafx.h.

*Source.cpp*
```
#include "stdafx.h"

int main()
{
    std::string s = "Hello World!\n";
    std::string sub1 = s.substr(0, 5);
    std::string sub2 = s.substr(6, 5);
    std::cout << s;
    std::map <std::string, std::string> book = { {"Hi", "Привет"},
                             {"Student", "Студент"},
                             {"!", "!"} };
    book["num_1"] = "num_2";
}
```

*stdafx.h*
```
#pragma once

#include <iostream>
#include <map>
#include <string>
```

Необходимо в корне дерева исходников разместить файл CMakeLists.txt,
хранящий правила и цели сборки.

*CMakeLists.txt:*
```
# название проекта
project(myProject)

# создаёт исполняемый файл с именем myProject из исходника Source.cpp.
add_executable(myProject Source.cpp)
```

Теперь сделаем stdafx.h предкомпилированным заголовочным файлом. 
Для этого добавим команду target_precompile_headers(myProject PUBLIC stdafx.h).  
Команда target_precompile_headers добавляет заголовочные файлы (а именно stdafx.h) к PRECOMPILE_HEADERS целевым свойствам myProject. Именованный объект myProject должен быть создан с помощью такой команды, как add_executable() или add_library(), и не должен быть целевым псевдонимом.

*CMakeLists.txt* будет выглядеть так:
```
# проверка версии CMake. 
cmake_minimum_required(VERSION 3.16)

# название проекта
project(myProject)

# создаёт исполняемый файл с именем myProject из исходников.
add_executable(myProject Source.cpp)

# добавляет заголовочные файлы к PRECOMPILE_HEADERS целевым свойствам myProject.
target_precompile_headers(myProject PUBLIC stdafx.h)
```

Чтобы при сборке увидеть время на компиляцию или линковку, добавим в CMakeLists.txt следующее:
```
set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
 set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")
```
 
**Сборка проекта средствами CMake в командной строке Linux**

Исходные файлы находятся в папке ~/practice_unix/with_pch. 
Создадим пустую директорию для временных файлов и перейдём туда.

> belkalia@DESKTOP-A1S40CT:\~/practice\_unix/tmp\$

Теперь запустим команду cmake, передав ей в качестве параметра путь к
папке с исходниками:

> belkalia@DESKTOP-A1S40CT:\~/practice\_unix/tmp\$ cmake ../with\_pch  
> …  
> -- Build files have been written to: /home/belkalia/practice\_unix/tmp

Видим, что в папке появилось несколько временных файлов, необходимых для
сборки проекта.  
Теперь можно запустить непосредственно make:

> belkalia@DESKTOP-A1S40CT:\~/practice\_unix/tmp\$ make  
> [ 33%] Building CXX object CMakeFiles/myProject.dir/cmake_pch.hxx.gch  
> Elapsed time: 2 s. (time), 0.001276 s. (clock)  
> [ 66%] Building CXX object CMakeFiles/myProject.dir/Source.cpp.o  
> Elapsed time: 0 s. (time), 0.002157 s. (clock)  
> [100%] Linking CXX executable myProject  
> Elapsed time: 1 s. (time), 0.000748 s. (clock)  
> [100%] Built target myProject

Итак, наша программа собралась.
Можно запускать:

> belkalia@DESKTOP-A1S40CT:~/practice_unix/tmp$ ./myProject
> Hello World!

Чтобы поменять компилятор, необходимо вызвать команду *CMake* с ключом  
-D CMAKE\_C\_COMPILER=&lt;name&gt; -D CMAKE\_CXX\_COMPILER=&lt;name&gt;  
где "name" название компилятора.
Пример:
> cmake -D CMAKE\_C\_COMPILER=gcc -D CMAKE\_CXX\_COMPILER=g++ ../with_pch

**В итоге**

С помощью CMake и командной строки Linux удалось собрать проекты без и с использованием предварительно откомпилированного заголовка, также получилось поменять компиляторы на gcc и clang(по умолчанию - сс), но на msvc не получается.

**Сборка проекта средствами CMake в командной строке Windows.**

Возьмём исходные файлы и CMakeLists.txt из предыдущего пункта и поместим в папку C:\Users\belkalia\practice_win\with_pch.  
Созданим папку tmp в practice_win и переместимся в нее.

> C:\Users\belkalia>cd ./practice_win/tmp_with  

Выполним команду
> C:\Users\belkalia\practice_win\tmp_with>call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"  
> **********************************************************************  
> ** Visual Studio 2022 Developer Command Prompt v17.6.4  
> ** Copyright (c) 2022 Microsoft Corporation  
> **********************************************************************

Далее соберём и скомпилируем проект:

> C:\Users\belkalia\practice_win\tmp_with>cmake ../with_pch  
> -- Building for: Visual Studio 17 2022  
> -- Selecting Windows SDK version 10.0.19041.0 to target Windows 10.0.19045.  
> -- The C compiler identification is MSVC 19.36.32535.0  
> ...  
> -- Build files have been written to: C:/Users/belkalia/practice_win/tmp_with  

> C:\Users\belkalia\practice_win\tmp_with>MSBulid  myProject.sln  
> MSBuild version 17.6.3+07e294721 for .NET Framework  
> Выполняется последовательная сборка проектов в этом решении. Чтобы включить параллельную сборку, добавьте параметр "-m".  
> Сборка начата 06.07.2023 12:00:13.  
> ...  
> Сборка успешно завершена.  
>    Предупреждений: 0  
>    Ошибок: 0  
>    
> Прошло времени 00:00:03.95

*Возможная проблема*  
В командной строке windows может не получиться собрать проект. Выводится такое сообщение:
> C:\\Users\\belkalia\\practice\_win\\tmp&gt;msbuild  
> "msbuild" не является внутренней или внешней командой, исполняемой программой или пакетным файлом.

Проблема решается двумя способами:

-   сначала необходимо выполнить такую команду:

> call “C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Auxiliary\\Build\\vcvars64.bat”

-   или открыть командную строку для разработчиков VS и в ней  выполнять необходимые команды.

**Итог**  
Получилось средствами CMake создать сценарии сборки для разных компиляторов. При этом исходные файлы и CMakeLists.txt остаются одинаковыми для разных компиляторов.


**Источники:**

<https://ru.wikipedia.org/wiki/CMake>  
<https://habr.com/ru/articles/155467/>  
<https://habr.com/ru/articles/503302/>  
<https://cmake.org/cmake/help/latest/command/target_precompile_headers.html>  
<https://edgarluque.com/blog/cmake-precompiled-headers/>  
<https://www.youtube.com/watch?v=8_X5Iq9niDE>
