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

#include "cmdline.h"
#include "expr.h"
#include "parser.h"
#include <iostream>

int main(int argc, const char * argv[]) {
    run_mode_t mode = use_arguments(argc, argv);
    if (mode != do_nothing) {
        Expr* expr = parse_expr(std::cin);
        if (mode == do_interp) {
            printf("Value: %d\n", expr->interp());
        } else if (mode == do_print) {
            printf("Standard Expression (print):\n%s\n", expr->to_string().c_str());
        } else {
            printf("Standard Expression (pretty_print):\n%s\n", expr->to_pretty_string().c_str());
        }
    }
    return 0;
}
