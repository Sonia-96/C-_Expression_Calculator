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
    virtual int interp() = 0;
    virtual bool has_variable() = 0;
    virtual Expr* subst(std::string s, Expr* expr) = 0;
};

class NumExpr : public Expr {
private:
    int val;
public:
    NumExpr(int v);
    bool equals(Expr* expr);
    int interp();
    bool has_variable();
    Expr* subst(std::string s, Expr* expr);
};

class AddExpr : public Expr {
private:
    Expr* lhs;
    Expr* rhs;
public:
    AddExpr(Expr *left, Expr *right);
    AddExpr(int left, int right);
    bool equals(Expr* expr);
    int interp();
    bool has_variable();
    Expr* subst(std::string s, Expr* expr);
};

class MultExpr : public Expr {
public:
    Expr* lhs;
    Expr* rhs;
public:
    MultExpr(Expr *left, Expr *right);
    MultExpr(int left, int right);
    bool equals(Expr* expr);
    int interp();
    bool has_variable();
    Expr* subst(std::string s, Expr* expr);
};

class VarExpr : public Expr {
private:
    std::string val;
public:
    VarExpr(std::string s);
    bool equals(Expr* expr);
    int interp();
    bool has_variable();
    Expr* subst(std::string s, Expr* expr);
};

#endif /* expr_hpp */
