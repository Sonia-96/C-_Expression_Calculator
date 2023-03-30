//
//  cmdline.cpp
//
//  Created by Yue Sun on 1/12/23.
//

#define CATCH_CONFIG_RUNNER
#include <iostream>
#include "catch.h"
#include "cmdline.h"

run_mode_t use_arguments(int argc, const char* argv[], const char** filename) {
    run_mode_t task = do_nothing;
    bool tested = false;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            std::cout << "legal arguments: --help, --test, --interp, --print, --pretty-print\n";
            exit(0);
        } else if (strcmp(argv[i], "--test") == 0) {
            if (!tested) {
                if (Catch::Session().run(1, argv) != 0) {
                    exit(1);
                }
                tested = true;
            } else {
                std::cerr << "Duplicated --test!\n";
                exit(1);
            }
        } else if (strcmp(argv[i], "--interp") == 0) {
            task = do_interp;
        } else if (strcmp(argv[i], "--print") == 0) {
            task = do_print;
        } else if (strcmp(argv[i], "--pretty-print") == 0) {
            task = do_pretty_print;
        } else if (i == 2){
            *filename = argv[i];
        } else {
            std::cerr << argv[i] << " is an illegal argument!\n";
            exit(1);
        }
    }
    return task;
}
