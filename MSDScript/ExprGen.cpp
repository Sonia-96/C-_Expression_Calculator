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
    int n = rand() % 100;
    if (n < 60) { // 60% - numbers
        return numExprGenerator();
    }
    if (n < 80) { // 10% - add, 10% - mult
        return addOrMultExprGenerator(var);
    }
    if (n < 90) { // 10% - let
        return letExprGenerator(var);
    }
    if (n < 95) {
        return ifExprGenerator(var);
    }
    return callExprGenerator();
}

Expr* ExprGen::addOrMultExprGenerator(std::string var) {
    Expr* expr1;
    if (rand() & 1) { // 50% - num
        expr1 = numExprGenerator();
    } else { // 50% - var
        if (var.empty()) {
            expr1 = exprGenerator(var);
        } else {
            expr1 = new VarExpr(var);
        }
    }
    Expr* expr2 = exprGenerator(var);
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
    if (n < 7) { // 70% - EqExpr
        test_part = eqExprGenerator(var);
    } else { // 30% boolExpr
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

FunExpr* ExprGen::funExprGenerator() {
    std::string formal_arg = varExprGenerator()->to_string();
    int n = rand() % 10;
    Expr* body;
    if (n < 6) {
        body = addOrMultExprGenerator(formal_arg);
    } else if (n < 8) {
        body = letExprGenerator(formal_arg);
    } else {
        body = ifExprGenerator(formal_arg);
    }
    return new FunExpr(formal_arg, body);
}

CallExpr* ExprGen::callExprGenerator() {
    Expr* to_be_called = funExprGenerator();
    Expr* actual_arg = exprGenerator();
    return new CallExpr(to_be_called, actual_arg);
}

BoolExpr* ExprGen::boolExprGenerator() {
    if (rand() & 1) {
        return new BoolExpr(true);
    }
    return new BoolExpr(false);
}

NumExpr* ExprGen::numExprGenerator() {
    return new NumExpr(rand() % 10000 - 5000);
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