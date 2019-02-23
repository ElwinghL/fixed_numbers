#include <iostream>

#include "fixed.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    fp::fixed<32,32> test = fp::fixed_traits<fp::fixed<32,32>>::max();
    std::cout << double(test) << std::endl;

    return 0;
}
