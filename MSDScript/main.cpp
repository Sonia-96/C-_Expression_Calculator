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
#include "val.h"

int main(int argc, const char * argv[]) {
    try {
        run_mode_t mode = use_arguments(argc, argv);
        if (mode != do_nothing) {
            Expr* expr = parse_comparg(std::cin);
            switch (mode) {
                case do_interp:
//                    printf("Value: %d\n", expr->interp());
                    printf("%s\n", expr->interp()->to_string().c_str());
                    break;
                case do_print:
//                    printf("Standard Expression (print):\n%s\n", expr->to_string().c_str());
                    printf("%s\n", expr->to_string().c_str());
                    break;
                default:
//                    printf("Standard Expression (pretty_print):\n%s\n", expr->to_pretty_string().c_str());
                    printf("%s\n", expr->to_pretty_string().c_str());
            }
        }
        return 0;
    } catch (std::runtime_error err) {
        std::cerr << err.what() << std::endl;
        return 1;
    }
}
