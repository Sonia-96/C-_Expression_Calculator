//
// Created by Yue Sun on 3/4/23.
//

#include "val.h"
#include "expr.h"

NumVal::NumVal(int v) {
    val = v;
}

Expr* NumVal::to_expr() {
    return new NumExpr(val);
}

bool NumVal::equals(Val* rhs) {
    NumVal* numVal = dynamic_cast<NumVal*>(rhs);
    if (numVal == nullptr) {
        return false;
    }
    return val == numVal->val;
}

Val* NumVal::add_to(Val* rhs) {
    NumVal* numVal = dynamic_cast<NumVal*>(rhs);
    if (numVal == nullptr) {
        throw std::runtime_error("add of non-number");
    }
    return new NumVal(val + numVal->val);
}

Val* NumVal::mult_with(Val* rhs) {
    NumVal* numVal = dynamic_cast<NumVal*>(rhs);
    if (numVal == nullptr) {
        throw std::runtime_error("multiply with non-number");
    }
    return new NumVal(val * numVal->val);
}

std::string NumVal::to_string() {
    return std::to_string(val);
}
