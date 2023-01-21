//
//  main.cpp
//  HW2_Expression
//
//  Created by Yue Sun on 1/12/23.
//

//#define CATCH_CONFIG_RUNNER

//#include <iostream>
//#include "catch.h"
//#include "cmdline.h"

int add(int a, int b) {
    return a + b;
}

int main(int argc, const char * argv[]) {
    // insert code here...
//    Catch::Session().run(argc, argv);
//    use_arguments(argc, argv);
    printf("%d", add(1, 2));
    return 0;
}
