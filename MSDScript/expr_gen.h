//
// Created by Yue Sun on 2/23/23.
//

#ifndef MSDSCRIPT_EXPR_GEN_H
#define MSDSCRIPT_EXPR_GEN_H

#include "expr.h"
#include <iostream>

class expr_gen {
private:
    static char alphaGenerator();
public:
    static std::string random_expr_string();
    static Expr* exprGenerator();
    static Expr* exprGenerator(std::string var);
    static Expr* addOrMultExprGenerator(std::string var);
    static LetExpr* letExprGenerator();
    static NumExpr* numExprGenerator();
    static VarExpr* varExprGenerator();
};


#endif //MSDSCRIPT_EXPR_GEN_H
