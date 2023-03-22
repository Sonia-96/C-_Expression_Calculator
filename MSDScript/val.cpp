//
// Created by Yue Sun on 3/4/23.
//

#include "val.h"
#include "expr.h"

  ///////////////////////////////////////////
 //                NumVal                 //
///////////////////////////////////////////

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
    return new NumVal((unsigned) val + (unsigned) numVal->val);
}

Val* NumVal::mult_with(Val* rhs) {
    NumVal* numVal = dynamic_cast<NumVal*>(rhs);
    if (numVal == nullptr) {
        throw std::runtime_error("multiply with non-number");
    }
    return new NumVal((unsigned) val * (unsigned) numVal->val);
}

std::string NumVal::to_string() {
    return std::to_string(val);
}

bool NumVal::is_true() {
    throw std::runtime_error("a number value can not be evaluated to a boolean");
}

Val* NumVal::call(Val *actual_arg) {
    throw std::runtime_error("no function to call!"); // TODO
}

///////////////////////////////////////////
 //                BoolVal                //
///////////////////////////////////////////

BoolVal::BoolVal(bool v) {
    val = v;
}

Expr* BoolVal::to_expr() {
    return new BoolExpr(val);
}

bool BoolVal::equals(Val *rhs) {
    BoolVal* other = dynamic_cast<BoolVal*>(rhs);
    if (other == nullptr) {
        return false;
    }
    return val == other->val;
}

Val* BoolVal::add_to(Val *rhs) {
    throw std::runtime_error("add of non-number");
}

Val* BoolVal::mult_with(Val *rhs) {
    throw std::runtime_error("multiply with non-number");
}

std::string BoolVal::to_string() {
    return val ? "_true" : "_false";
}

bool BoolVal::is_true() {
    return val;
}

Val* BoolVal::call(Val *actual_arg) {
    throw std::runtime_error("no function to call!"); // TODO
}

  ///////////////////////////////////////////
 //                FunVal                 //
///////////////////////////////////////////

FunVal::FunVal(std::string arg, Expr* expr) {
    formal_arg = arg;
    body = expr;
}

Expr* FunVal::to_expr() {
    return new FunExpr(formal_arg, body);
}

bool FunVal::equals(Val* rhs) {
    FunVal* other = dynamic_cast<FunVal*>(rhs);
    if (other == nullptr) {
        return false;
    }
    return formal_arg == other->formal_arg && body->equals(other->body);
}

Val* FunVal::add_to(Val* rhs) {
    throw std::runtime_error("add of non-number");
}

Val* FunVal::mult_with(Val* rhs) {
    throw std::runtime_error("multiply with non-number");
}

std::string FunVal::to_string() {
    return to_expr()->to_pretty_string();
}

bool FunVal::is_true() { // TODO should I interp the function before I check if it's true?
    throw std::runtime_error("a function value can not be evaluated to a boolean");
}

Val* FunVal::call(Val *actual_arg) {
    return body->subst(formal_arg, actual_arg->to_expr())->interp(); // TODO
}






