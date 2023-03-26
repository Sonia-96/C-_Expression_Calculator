//
// Created by Yue Sun on 2/23/23.
//

#include "ExprGen.h"
#include "val.h"

std::string ExprGen::random_expr_string()  {
    return exprGenerator()->to_string();
}

PTR(Expr) ExprGen::exprGenerator() {
    return exprGenerator("");
}

PTR(Expr) ExprGen::exprGenerator(std::string var) {
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

PTR(Expr) ExprGen::addOrMultExprGenerator(std::string var) {
    PTR(Expr) expr1;
    if (rand() & 1) { // 50% - num
        expr1 = numExprGenerator();
    } else { // 50% - var
        if (var.empty()) {
            expr1 = exprGenerator(var);
        } else {
            expr1 = NEW(VarExpr)(var);
        }
    }
    PTR(Expr) expr2 = exprGenerator(var);
    PTR(Expr) lhs;
    PTR(Expr) rhs;
    if (rand() & 1) {
        lhs = expr1, rhs = expr2;
    } else {
        lhs = expr2, rhs = expr1;
    }
    // generate add or mult
    if (rand() & 1) {
        return NEW(AddExpr)(lhs, rhs);
    }
    return NEW(MultExpr)(lhs, rhs);
}

PTR(LetExpr) ExprGen::letExprGenerator(std::string var) {
    if (var.empty()) {
        var = varExprGenerator()->getVal();
    }
    PTR(Expr) rhs = exprGenerator(var);
    int n = rand() % 10;
    PTR(Expr) body;
    if (n < 8) { // 80% - same var name
        body = exprGenerator(var);
    } else { // 20% - new var name (might trigger an error in interp)
        body = exprGenerator(varExprGenerator()->getVal()); // different var name, will trigger an error in interp
    }
    return NEW(LetExpr)(var, rhs, body);
}

PTR(IfExpr) ExprGen::ifExprGenerator(std::string var) {
    PTR(Expr) test_part;
    int n = rand() % 10;
    if (n < 7) { // 70% - EqExpr
        test_part = eqExprGenerator(var);
    } else { // 30% boolExpr
        test_part = boolExprGenerator();
    }
    PTR(Expr) then_part = exprGenerator(var);
    PTR(Expr) else_part = exprGenerator(var);
    return NEW(IfExpr)(test_part, then_part, else_part);
}

PTR(EqExpr) ExprGen::eqExprGenerator(std::string var) {
    PTR(Expr) lhs = exprGenerator(var);
    PTR(Expr) rhs = exprGenerator(var);
    return NEW(EqExpr)(lhs, rhs);
}

PTR(FunExpr) ExprGen::funExprGenerator() {
    std::string formal_arg = varExprGenerator()->to_string();
    int n = rand() % 10;
    PTR(Expr) body;
    if (n < 6) {
        body = addOrMultExprGenerator(formal_arg);
    } else if (n < 8) {
        body = letExprGenerator(formal_arg);
    } else {
        body = ifExprGenerator(formal_arg);
    }
    return NEW(FunExpr)(formal_arg, body);
}

PTR(CallExpr) ExprGen::callExprGenerator() {
    PTR(Expr) to_be_called = funExprGenerator();
    PTR(Expr) actual_arg = exprGenerator();
    return NEW(CallExpr)(to_be_called, actual_arg);
}

PTR(BoolExpr) ExprGen::boolExprGenerator() {
    if (rand() & 1) {
        return NEW(BoolExpr)(true);
    }
    return NEW(BoolExpr)(false);
}

PTR(NumExpr) ExprGen::numExprGenerator() {
    return NEW(NumExpr)(rand() % 10000 - 5000);
}

PTR(VarExpr) ExprGen::varExprGenerator() {
    std::string res;
    int len = rand() % 5 + 1; //  length 1-5
    for (int i = 0; i < len; i++) {
        res += alphaGenerator();
    }
    return NEW(VarExpr)(res);
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