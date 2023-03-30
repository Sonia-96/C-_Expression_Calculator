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
#include <fstream>
#include "cmdline.h"
#include "expr.h"
#include "parser.h"
#include "val.h"

int main(int argc, const char * argv[]) {
    try {
        const char* filename;
        run_mode_t mode = use_arguments(argc, argv, &filename);
        if (mode != do_nothing) {
            PTR(Expr) expr;
            if (filename != nullptr) {
                std::ifstream f_in(filename);
                expr = parse_expr(f_in);
            } else {
                expr = parse_expr(std::cin);
            }
            switch (mode) {
                case do_interp:
//                    printf("Value: %d\n", expr->interp());
                    printf("%s\n", expr->interp()->to_string().c_str());
                    break;
                case do_print:
//                    printf("Standard Expression (print):\n%s\n", expr->to_string().c_str());
                    printf("%s\n", expr->to_string().c_str());
                    break;
                default: //pretty_print
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
