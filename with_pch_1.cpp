#include "stdafx.h"

//void vec();
//void str();

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
    //vec();
    //str();
}