#include "stdafx.h"

void vec() {
    std::vector<int> data = { 3, 1, 4, 1, 5, 9, 2, 6 };
    data.push_back(0);
    data.push_back(10);

    std::sort(data.begin(), data.end());
    
    for (size_t i = 0; i != data.size(); ++i) {
        std::cout << data[i] << ' ';
    }
}