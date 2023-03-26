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
    static PTR(Expr) exprGenerator();
    static PTR(Expr) exprGenerator(std::string var);
    static PTR(Expr) addOrMultExprGenerator(std::string var);
    static PTR(LetExpr) letExprGenerator(std::string var);
    static PTR(IfExpr) ifExprGenerator(std::string var);
    static PTR(NumExpr) numExprGenerator();
    static PTR(VarExpr) varExprGenerator();
    static PTR(BoolExpr) boolExprGenerator();
    static PTR(EqExpr) eqExprGenerator(std::string var);
    static PTR(FunExpr) funExprGenerator();
    static PTR(CallExpr) callExprGenerator();
};


#endif //MSDSCRIPT_EXPRGEN_H
