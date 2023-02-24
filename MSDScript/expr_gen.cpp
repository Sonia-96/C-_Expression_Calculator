//
// Created by Yue Sun on 2/23/23.
//

#include "expr_gen.h"

std::string expr_gen::random_expr_string()  {
    return exprGenerator()->to_pretty_string();
}

Expr* expr_gen::exprGenerator() {
    return exprGenerator("");
}

Expr* expr_gen::exprGenerator(std::string var) {
    int n = rand() % 10;
    if (n < 6) {
        return numExprGenerator();
    }
    if (n < 9) {
        return addOrMultExprGenerator(var);
    }
    return letExprGenerator();
}

Expr* expr_gen::addOrMultExprGenerator(std::string var) {
    Expr* expr1;
    if (!var.empty()) {
        expr1 = new VarExpr(var);
    } else {
        expr1 = exprGenerator();
    }
    Expr* expr2 = exprGenerator();
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

LetExpr* expr_gen::letExprGenerator() {
    std::string var = varExprGenerator()->getVal();
    Expr* lhs = exprGenerator();
    int n = rand() % 10;
    Expr* rhs;
    if (n < 6) { // 80% - same var name
        rhs = exprGenerator(var);
    } else if (n < 9) {
        rhs = exprGenerator(); // 20% - just numbers
    } else { // 10% - new var name (will trigger an error in interp)
        rhs = exprGenerator(varExprGenerator()->getVal()); // different var name, will trigger an error in interp
    }
    return new LetExpr(var, lhs, rhs);
}

NumExpr* expr_gen::numExprGenerator() {
    return new NumExpr(rand());
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
        n = 65 + n % 26;
    } else { // lower case
        n = 97 + n % 26;
    }
    return n;
}