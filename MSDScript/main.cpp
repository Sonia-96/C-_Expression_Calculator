//
//  main.cpp
//
//  Created by Yue Sun on 1/12/23.
//

/**
 * \mainpage MSDScript
 * \author Yue Sun
 * \date 02-07-2023
 */

#include <iostream>
#include "cmdline.h"
#include "expr.h"
#include "parser.h"
#include "fuzzing.h"
#include "exec.h"

#define ITERATION 100

int main(int argc, const char * argv[]) {
//    run_mode_t mode = use_arguments(argc, argv);
//    if (mode != do_nothing) {
//        Expr* expr = parse_expr(std::cin);
//        switch (mode) {
//            case do_interp:
//                printf("Value: %d\n", expr->interp());
//                break;
//            case do_print:
//                printf("Standard Expression (print):\n%s\n", expr->to_string().c_str());
//                break;
//            default:
//                printf("Standard Expression (pretty_print):\n%s\n", expr->to_pretty_string().c_str());
//        }
//    }
    srand(clock());
    const char* interp_argv[] = {"program", "--interp"};
    const char* print_argv[] = {"program", "--print"};
    for (int i = 0; i < ITERATION; i++) {
        std::string in = random_expr_string();
        printf("Trying: %s \n", in.c_str());

        ExecResult interpRes = exec_program(2, interp_argv, in); // TODO implement exec_program
        ExecResult printRes = exec_program(2, print_argv, in);

        ExecResult interRes2 = exec_program(2, interp_argv, printRes.out);
        if (interpRes.out != interRes2.out) {
            throw std::runtime_error("different result for printed\n");
        }
    }
    return 0;
}
