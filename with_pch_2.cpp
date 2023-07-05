#include "stdafx.h"

void str() {
    std::string s = "Hello World!\n";
    std::string sub1 = s.substr(0, 5);
    std::string sub2 = s.substr(6, 5);
    std::cout << sub1 + ' ' + sub2 + "!\n";
    std::map <std::string, std::string> book = { {"Hi", "Привет"},
                             {"Student", "Студент"},
                             {"!", "!"} };
    book["num_1"] = "num_2";
}