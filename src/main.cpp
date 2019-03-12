#include <iostream>

#include "fixed.h"

int main() {
    std::cout << "Hello ! Here is a small demo" << std::endl;
    //How to create a Q number
    fp::Q_8_8 demo1(1.0);
    std::cout << "fp::Q_8_8 demo1(1.0);" << std::endl;
    std::cout << fp::to_string(demo1) << "\n" << std::endl;

    fp::Q_8_8 demo2 = fp::fixed_traits<fp::Q_8_8>::pi();
    std::cout << "fp::Q_8_8 demo2 = fp::fixed_traits<fp::Q_8_8>::pi();" << std::endl;
    std::cout << fp::to_string(demo2) << "\n" << std::endl;
    //Here, it's bad because the precision is bad.
    fp::fixed<32,32> demo3 = fp::fixed_traits<fp::fixed<32,32>>::pi();
    std::cout << "fp::fixed<32,32> demo3 = fp::fixed_traits<fp::fixed<32,32>>::pi();" << std::endl;
    std::cout << fp::to_string(demo3) << "\n" << std::endl;

    std::cout << "demo2 = " << (double) demo2 << " and demo3 = " << (double) demo3 << std::endl;
    return 0;
}
