//
// Created by Yue Sun on 2/23/23.
//

#include "ExprGenTest.h"

int main(int argc, const char * argv[]) {
    testAll();
//    testExpr();
}

void testAll() {
    testNum();
    testVar();
    testLet();
    testAddOrMult();
    testExpr();
}

void testNum() {
    for (int i = 0; i < ITERATION; i++) {
        PTR(Expr) expr = ExprGen::numExprGenerator();
        std::cout << expr->to_pretty_string() << std::endl;
    }
}

void testVar() {
    for (int i = 0; i < ITERATION; i++) {
        PTR(Expr) expr = ExprGen::varExprGenerator();
        std::cout << expr->to_pretty_string() << std::endl;
    }
}

void testAddOrMult() {
    for (int i = 0; i < ITERATION; i++) {
        PTR(Expr) expr = ExprGen::addOrMultExprGenerator("");
        std::cout << expr->to_pretty_string() << std::endl;
    }
}

void testLet() {
    for (int i = 0; i < ITERATION; i++) {
        PTR(Expr) expr = ExprGen::letExprGenerator("");
        std::cout << expr->to_pretty_string() << std::endl;
    }
}

void testExpr() {
    for (int i = 0; i < ITERATION; i++) {
        PTR(Expr) expr = ExprGen::exprGenerator();
        std::cout << expr->to_pretty_string() << std::endl;
    }
}
