//
//  main.cpp
//  HW2_Expression
//
//  Created by Yue Sun on 1/12/23.
//

#include <iostream>
#include "cmdline.h"
#include "expr.hpp"

int add(int a, int b) {
    return a + b;
}

int main(int argc, const char * argv[]) {
//    Num num(1);
//    Add add(1, 2);
//    std::cout << typeid(num).name() << std::endl;
//    std::cout << typeid(add).name() << std::endl;
    use_arguments(argc, argv);
    return 0;
}
