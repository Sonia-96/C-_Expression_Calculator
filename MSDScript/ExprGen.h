//
// Created by Yue Sun on 2/23/23.
//

#ifndef MSDSCRIPT_EXPRGEN_H
#define MSDSCRIPT_EXPRGEN_H

#include "expr.h"
#include <iostream>

class ExprGen {
private:
    static char alphaGenerator();
public:
    static std::string random_expr_string();
    static Expr* exprGenerator();
    static Expr* exprGenerator(std::string var);
    static Expr* addOrMultExprGenerator(std::string var);
    static LetExpr* letExprGenerator(std::string var);
    static IfExpr* ifExprGenerator(std::string var);
    static NumExpr* numExprGenerator();
    static VarExpr* varExprGenerator();
    static BoolExpr* boolExprGenerator();
    static EqExpr* eqExprGenerator(std::string var);
    static FunExpr* funExprGenerator();
    static CallExpr* callExprGenerator();
};


#endif //MSDSCRIPT_EXPRGEN_H
