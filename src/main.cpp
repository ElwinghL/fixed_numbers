#include <iostream>

#include "fixed.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    double a = 4.0;
    double b = 2.0;
    fp::fixed<8, 8> test(a);

    std::cout << "Value = " << test.value << "\n";

    fp::fixed<16, 16> test2(sqrt(test));

    std::cout << fp::to_string(test2) << "\n";

    std::cout << "Value = " << test2.value << "\n";

    std::cout << (int) 23.45 << std::endl;
    std::cout << (int) 22.99 << std::endl;

    return 0;
}