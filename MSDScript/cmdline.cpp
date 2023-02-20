//
//  cmdline.cpp
//
//  Created by Yue Sun on 1/12/23.
//

#define CATCH_CONFIG_RUNNER
#include <iostream>
#include "catch.h"
#include "cmdline.h"
#include "parser.h"

run_mode_t use_arguments(int argc, const char* argv[]) {
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
//            std::string line;
//            while (getline(std::cin, line)) {
//                std::istringstream in{line};
//                Expr* expr = parse_expr(in);
//                printf("Standard Expression: %s\n", expr->to_pretty_string().c_str());
//                printf("Value: %d\n", expr->interp());
//            }
            task = do_interp;
            Expr* expr = parse_expr(std::cin);
            printf("Value: %d\n", expr->interp());
            exit(0);
        } else if (strcmp(argv[i], "--print") == 0) {
            task = do_print;
            Expr* expr = parse_expr(std::cin);
            printf("Standard Expression (print):\n%s\n", expr->to_string().c_str());
            exit(0);
        } else if (strcmp(argv[i], "--pretty-print") == 0) {
            task = do_print;
            Expr* expr = parse_expr(std::cin);
            printf("Standard Expression (pretty_print):\n%s\n", expr->to_pretty_string().c_str());
            exit(0);
        }
        else {
            std::cerr << argv[i] << " is an illegal argument!\n";
            exit(1);
        }
    }
    return task;
}
