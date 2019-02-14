#include <iostream>

#include "fixed.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    double a = 0.5;
    fp::fixed<2, 4> test(a);

    std::cout << fp::to_string(test) << "\n";

    fp::fixed<8, 8> test2(sqrt(test));

    std::cout << fp::to_string(test2) << "\n";

    std::cout << "Value = " << test2.value << "\n";

    return 0;
}
