//
//  expr.hpp
//  HW2_Expression
//
//  Created by Yue Sun on 1/12/23.
//

#ifndef expr_hpp
#define expr_hpp

#include <string>

class Expr {
public:
    virtual bool equals(Expr* expr) = 0;
};

class Num : public Expr {
private:
    int val;
public:
    Num(int v);
    bool equals(Expr* expr);
};

class Add : public Expr {
private:
    Expr* lhs;
    Expr* rhs;
public:
    Add(Expr *left, Expr *right);
    bool equals(Expr* expr);
};

class Mult : public Expr {
public:
    Expr* lhs;
    Expr* rhs;
public:
    Mult(Expr *left, Expr *right);
    bool equals(Expr* expr);
};

class Variable : public Expr {
private:
    std::string val;
public:
    Variable(std::string s);
    bool equals(Expr* expr);
};

#endif /* expr_hpp */
