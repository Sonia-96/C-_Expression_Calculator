//
// Created by Yue Sun on 3/4/23.
//

#ifndef MSDSCRIPT_VAL_H
#define MSDSCRIPT_VAL_H

#include <string>

class Expr;

class Val {
public:
    virtual Expr* to_expr() = 0;
    virtual bool equals(Val* rhs) = 0;
    virtual Val* add_to(Val* rhs) = 0;
    virtual Val* mult_with(Val* rhs) = 0;
    virtual std::string to_string() = 0;
};

class NumVal : public Val {
private:
    int val;
public:
    NumVal(int v);
    Expr * to_expr();
    bool equals(Val* rhs);
    Val* add_to(Val* rhs);
    Val* mult_with(Val* rhs);
    std::string to_string();
};

#endif //MSDSCRIPT_VAL_H
