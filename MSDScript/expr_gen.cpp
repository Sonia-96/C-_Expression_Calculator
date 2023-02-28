//
// Created by Yue Sun on 2/23/23.
//

#include "expr_gen.h"

std::string expr_gen::random_expr_string()  {
    return exprGenerator()->to_string();
}

Expr* expr_gen::exprGenerator() {
    return exprGenerator("");
}

Expr* expr_gen::exprGenerator(std::string var) {
    int n = rand() % 10;
    if (n < 6) { // 60% - numbers
        return numExprGenerator();
    }
    if (n < 9) { // 15% - add, 15% - mult
        return addOrMultExprGenerator(var);
    }
    return letExprGenerator(var); // 10% - let
}

Expr* expr_gen::addOrMultExprGenerator(std::string var) {
    Expr* expr1 = exprGenerator(var);
    Expr* expr2 = exprGenerator(var);
    // put variable on either side
    Expr* lhs;
    Expr* rhs;
    if (rand() & 1) {
        lhs = expr1, rhs = expr2;
    } else {
        lhs = expr2, rhs = expr1;
    }
    // generate add or mult
    if (rand() & 1) {
        return new AddExpr(lhs, rhs);
    }
    return new MultExpr(lhs, rhs);
}

LetExpr* expr_gen::letExprGenerator(std::string var) {
    if (var.empty()) {
        var = varExprGenerator()->getVal();
    }
    Expr* rhs = exprGenerator();
    int n = rand() % 10;
    Expr* body;
    if (n < 6) { // 80% - same var name
        body = exprGenerator(var);
    } else { // 20% - new var name (might trigger an error in interp)
        body = exprGenerator(varExprGenerator()->getVal()); // different var name, will trigger an error in interp
    }
    return new LetExpr(var, rhs, body);
}

NumExpr* expr_gen::numExprGenerator() {
    return new NumExpr(rand() % 100000 - 50000);
}

VarExpr* expr_gen::varExprGenerator() {
    std::string res;
    int len = rand() % 5 + 1; //  length 1-5
    for (int i = 0; i < len; i++) {
        res += alphaGenerator();
    }
    return new VarExpr(res);
}

char expr_gen::alphaGenerator() {
    int n = rand();
    if (n & 1) { // upper case
        n = 'A' + n % 26;
    } else { // lower case
        n = 'a' + n % 26;
    }
    return n;
}