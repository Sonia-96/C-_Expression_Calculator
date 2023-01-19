//
//  expr.cpp
//  HW2_Expression
//
//  Created by Yue Sun on 1/12/23.
//

#include "expr.hpp"

Num::Num(int v) {
    val = v;
}

bool Num::equals(Expr* expr) {
    Num *n = dynamic_cast<Num*>(expr);
    if (n == NULL) {
        return false;
    }
    return val == n -> val;
}

Add::Add(Expr *left, Expr *right) {
    lhs = left;
    rhs = right;
}

bool Add::equals(Expr* expr) {
    Add *a = dynamic_cast<Add*>(expr);
    if (a == NULL) {
        return false;
    }
    return lhs->equals(a->lhs) && rhs->equals(a->rhs);
}

Mult::Mult(Expr *left, Expr *right) {
    lhs = left;
    rhs = right;
}

bool Mult::equals(Expr* expr) {
    Mult *m = dynamic_cast<Mult*>(expr);
    if (m == NULL) {
        return false;
    }
    return lhs->equals(m->lhs) && rhs->equals(m->rhs);
}

Variable::Variable(std::string s) {
    val = s;
}

bool Variable::equals(Expr* expr) {
    Variable *var = dynamic_cast<Variable*>(expr);
    if (var == NULL) {
        return false;
    }
    return val == var->val;
}
