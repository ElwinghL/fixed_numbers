#include <iostream>

#include "fixed.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    float a = 2.0;
    double b = 1.0;
    fp::fixed<8, 8> test(a);

    std::cout << "Value = " << test.value << "\n";

    fp::fixed<8, 8> test2(b);
    test2 /= test;

    std::cout << "Value = " << test2.value << "\n";

    std::cout << (int) 23.45 << std::endl;
    std::cout << (int) 22.99 << std::endl;

    return 0;
}