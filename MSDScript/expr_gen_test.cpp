//
// Created by Yue Sun on 2/23/23.
//

#include "expr_gen_test.h"

void testAll() {
    testNum();
    testVar();
    testLet();
    testAddOrMult();
    testExpr();
}

void testNum() {
    for (int i = 0; i < ITERATION; i++) {
        Expr* expr = expr_gen::numExprGenerator();
        std::cout << expr->to_pretty_string() << std::endl;
    }
}

void testVar() {
    for (int i = 0; i < ITERATION; i++) {
        Expr* expr = expr_gen::varExprGenerator();
        std::cout << expr->to_pretty_string() << std::endl;
    }
}

void testAddOrMult() {
    for (int i = 0; i < ITERATION; i++) {
        Expr* expr = expr_gen::addOrMultExprGenerator("");
        std::cout << expr->to_pretty_string() << std::endl;
    }
}

void testLet() {
    for (int i = 0; i < ITERATION; i++) {
        Expr* expr = expr_gen::letExprGenerator();
        std::cout << expr->to_pretty_string() << std::endl;
    }
}

void testExpr() {
    for (int i = 0; i < ITERATION; i++) {
        Expr* expr = expr_gen::exprGenerator();
        std::cout << expr->to_pretty_string() << std::endl;
    }
}
