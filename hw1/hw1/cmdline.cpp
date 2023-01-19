//
//  cmdline.cpp
//  hw1
//
//  Created by Yue Sun on 1/12/23.
//

#include <iostream>
#include "cmdline.h"
using namespace std;

void use_arguments(int argc, const char* argv[]) {
    bool tested = false;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            cout << "legal arguments: --help, --test\n";
            exit(0);
        } else if (strcmp(argv[i], "--test") == 0) {
            if (!tested) {
                cout << "Tests passed\n";
                tested = true;
            } else {
                cerr << "Duplicated --test!\n";
                exit(1);
            }
        } else {
            cerr << argv[i] << " is an illegal argument!\n";
            exit(1);
        }
    }
}
