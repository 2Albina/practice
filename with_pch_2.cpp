#include "stdafx.h"

void str() {
    std::string s = "Hello World!\n";
    std::string sub1 = s.substr(0, 5);
    std::string sub2 = s.substr(6, 5);
    std::cout << sub1 + ' ' + sub2 + '!';
}