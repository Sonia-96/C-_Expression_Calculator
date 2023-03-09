//
// Created by Yue Sun on 2/23/23.
//

#include "ExprGen.h"
#include "val.h"

std::string ExprGen::random_expr_string()  {
    return exprGenerator()->to_string();
}

Expr* ExprGen::exprGenerator() {
    return exprGenerator("");
}

Expr* ExprGen::exprGenerator(std::string var) {
    int n = rand() % 10;
    if (n < 6) { // 50% - numbers
        return numExprGenerator();
    }
    if (n < 8) { // 10% - add, 10% - mult
        return addOrMultExprGenerator(var);
    }
    if (n < 9) { // 10% - let
        return letExprGenerator(var);
    }
    return ifExprGenerator(var);
}

Expr* ExprGen::addOrMultExprGenerator(std::string var) {
    Expr* lhs = exprGenerator(var);
    Expr* rhs = exprGenerator(var);
    // generate add or mult
    if (rand() & 1) {
        return new AddExpr(lhs, rhs);
    }
    return new MultExpr(lhs, rhs);
}

LetExpr* ExprGen::letExprGenerator(std::string var) {
    if (var.empty()) {
        var = varExprGenerator()->getVal();
    }
    Expr* rhs = exprGenerator(var);
    int n = rand() % 10;
    Expr* body;
    if (n < 8) { // 80% - same var name
        body = exprGenerator(var);
    } else { // 20% - new var name (might trigger an error in interp)
        body = exprGenerator(varExprGenerator()->getVal()); // different var name, will trigger an error in interp
    }
    return new LetExpr(var, rhs, body);
}

IfExpr* ExprGen::ifExprGenerator(std::string var) {
    Expr* test_part;
    int n = rand() % 10;
    if (n < 7) {
        test_part = eqExprGenerator(var);
    } else {
        test_part = boolExprGenerator();
    }
    Expr* then_part = exprGenerator(var);
    Expr* else_part = exprGenerator(var);
    return new IfExpr(test_part, then_part, else_part);
}

EqExpr* ExprGen::eqExprGenerator(std::string var) {
    Expr* lhs = exprGenerator(var);
    Expr* rhs = exprGenerator(var);
    return new EqExpr(lhs, rhs);
}

BoolExpr* ExprGen::boolExprGenerator() {
    if (rand() & 1) {
        return new BoolExpr(true);
    }
    return new BoolExpr(false);
}

NumExpr* ExprGen::numExprGenerator() {
    return new NumExpr(rand() % 100000 - 50000);
}

VarExpr* ExprGen::varExprGenerator() {
    std::string res;
    int len = rand() % 5 + 1; //  length 1-5
    for (int i = 0; i < len; i++) {
        res += alphaGenerator();
    }
    return new VarExpr(res);
}

char ExprGen::alphaGenerator() {
    int n = rand();
    if (n & 1) { // upper case
        n = 'A' + n % 26;
    } else { // lower case
        n = 'a' + n % 26;
    }
    return n;
}