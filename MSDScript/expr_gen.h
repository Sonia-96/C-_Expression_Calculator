//
// Created by Yue Sun on 2/23/23.
//

#ifndef MSDSCRIPT_EXPR_GEN_H
#define MSDSCRIPT_EXPR_GEN_H

#include "expr.h"
#include <iostream>

class ExprGenerator {
public:
    static Expr* exprGenerator() {
        int n = rand() % 10;
        if (n < 6) {
            return numExprGenerator();
        }
        if (n < 9) {
            return addOrMultExprGenerator();
        }
        return letExprGenerator();
    }

    static Expr* exprGenerator(std::string var) {
        int n = rand() % 10;
        if (n < 6) {
            return numExprGenerator();
        }
        if (n < 9) {
            return addOrMultExprGenerator(var);
        }
        return letExprGenerator();
    }

    static Expr* addOrMultExprGenerator() {
        Expr* lhs = exprGenerator();
        Expr* rhs = exprGenerator();
        int n = rand();
        if (n & 1) {
            return new AddExpr(lhs, rhs);
        }
        return new MultExpr(lhs, rhs);
    }

    static Expr* addOrMultExprGenerator(std::string var) {
        VarExpr* lhs = new VarExpr(var);
        Expr* rhs = exprGenerator();
        int n = rand();
        if (n & 1) {
            return new AddExpr(lhs, rhs);
        }
        return new MultExpr(lhs, rhs);
    }

    static LetExpr* letExprGenerator() {
        std::string var = varExprGenerator()->getVal();
        Expr* lhs = exprGenerator();
        Expr* rhs = exprGenerator(var);
        return new LetExpr(var, lhs, rhs);
    }

    static NumExpr* numExprGenerator() {
        return new NumExpr(rand());
    }

    static VarExpr* varExprGenerator() {
        std::string res;
        int len = rand() % 5 + 1; //  length 1-5
        for (int i = 0; i < len; i++) {
            res += alphaGenerator();
        }
        return new VarExpr(res);
    }

    static char alphaGenerator() {
        int n = rand();
        if (n & 1) { // upper case
            n = 65 + n % 26;
        } else { // lower case
            n = 97 + n % 26;
        }
        return n;
    }
};


#endif //MSDSCRIPT_EXPR_GEN_H
