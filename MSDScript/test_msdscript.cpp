//
// Created by Yue Sun on 2/21/23.
//

#include "exec.h"
#include "expr_gen.h"
#include <iostream>

#define ITERATION 100

// TODO should generate all cases
std::string random_expr_string() {
    if (rand() % 10 < 6) {
        return std::to_string(rand()); // TODO this may cause integer stack overflow
    }
    return random_expr_string() + "+" + random_expr_string();
}

int main(int argc, const char * argv[]) {
    for (int i = 0; i < ITERATION; i++) {
        Expr* expr = ExprGenerator::exprGenerator();
//        Expr* expr = ExprGenerator::letExprGenerator();
        std::cout << expr->to_pretty_string() << std::endl;
    }
//    const char* modes[] = {"--interp", "--print", "--pretty-print"};
//    const char* args1[2];
//    const char* args2[2];
//    if (argc == 2) {
//        args1[0] = "clear";
//        args2[0] = argv[1];
//    } else {
//        args1[0] = argv[1];
//        args2[0] = argv[2];
//    }
//    for (int j = 0; j < 3; j++) {
//        printf("================================%s================================", modes[j]);
//        args1[1] = modes[j];
//        args2[1] = modes[j];
//
//        for (int i = 0; i < ITERATION; i++) {
//            std::string in = random_expr_string();
//            printf("Trying: %s \n", in.c_str());
//
//            ExecResult res1 = exec_program(2, args1, in);
//            ExecResult res2 = exec_program(2, args2, in);
//
//            if (res1.out != res2.out) {
//                printf("%s: %s", args1[0], res1.out.c_str());
//                printf("%s: %s", args2[0], res2.out.c_str());
//                std::cout << "\n";
//                throw std::runtime_error("Different result!\n");
//            } else {
//                std::cout << ">>> Test passed!\n";
//            }
//        }
//    }
}