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
    Expr * to_expr() override;
    bool equals(Val* rhs) override;
    Val* add_to(Val* rhs) override;
    Val* mult_with(Val* rhs) override;
    std::string to_string() override;
};

class BoolVal : public Val {
private:
    bool val;
public:
    BoolVal(bool v);
    Expr* to_expr() override;
    bool equals(Val* rhs) override;
    Val* add_to(Val* rhs) override;
    Val* mult_with(Val* rhs) override;
    std::string to_string() override;
};

#endif //MSDSCRIPT_VAL_H
