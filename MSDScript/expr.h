//
//  expr.hpp
//
//  Created by Yue Sun on 1/12/23.
//

#ifndef MSDSCRIPT_EXPR_H
#define MSDSCRIPT_EXPR_H

#include <sstream>
#include <string>

class Val;

enum precedence_t {
    prec_none, // 0
    prec_add, // 1
    prec_mult, // 2
};

//class Val;

/** \brief
 * Expr class - the base class for all expressions
 */
class Expr {
public:
    virtual bool equals(Expr* expr)=0;
    virtual Val* interp() = 0;
    virtual bool has_variable() = 0;
    virtual Expr* subst(std::string s, Expr* expr) = 0;
    virtual void print(std::ostream& out) = 0;
    std::string to_string();
    void pretty_print(std::ostream& out);
    virtual void pretty_print_at(std::ostream& out, precedence_t precedence, std::streampos& newLinePrevPos, bool addParenthesesToLet) = 0;
    std::string to_pretty_string();
};

/** \brief
 * NumExpr class - for number expressions
 */
class NumExpr : public Expr {
private:
    int val;
public:
    NumExpr(int v);
    bool equals(Expr* expr) override;
    Val* interp() override;
    bool has_variable() override;
    Expr* subst(std::string s, Expr* expr) override;
    void print(std::ostream& out) override;
    void pretty_print_at(std::ostream& out, precedence_t precedence, std::streampos& newLinePrevPos, bool addParenthesesToLet) override;
};

/** \brief
 * AddExpr class - for add expressions
 */
class AddExpr : public Expr {
private:
    Expr* lhs;
    Expr* rhs;
public:
    AddExpr(Expr *left, Expr *right);
    AddExpr(int left, int right);
    AddExpr(std::string left, int right);
    AddExpr(int left, std::string right);
    AddExpr(std::string left, std::string right);
    bool equals(Expr* expr);
    Val* interp();
    bool has_variable();
    Expr* subst(std::string s, Expr* expr);
    void print(std::ostream& out);
    void pretty_print_at(std::ostream& out, precedence_t precedence, std::streampos& newLinePrevPos, bool addParenthesesToLet);
};

/** \brief
 * MultExpr class - for multiplication expressions
 */
class MultExpr : public Expr {
public:
    Expr* lhs;
    Expr* rhs;
public:
    MultExpr(Expr *left, Expr *right);
    MultExpr(int left, int right);
    MultExpr(std::string left, int right);
    MultExpr(int left, std::string right);
    MultExpr(std::string left, std::string right);
    bool equals(Expr* expr);
    Val* interp();
    bool has_variable();
    Expr* subst(std::string s, Expr* expr);
    void print(std::ostream& out);
    void pretty_print_at(std::ostream& out, precedence_t precedence, std::streampos& newLinePrevPos, bool addParenthesesToLet);
};

/** \brief
 * VarExpr class - for variable expressions
 */
class VarExpr : public Expr {
private:
    std::string val;
public:
    VarExpr(std::string s);
    bool equals(Expr* expr);
    Val* interp();
    bool has_variable();
    Expr* subst(std::string s, Expr* expr);
    void print(std::ostream& out);
    void pretty_print_at(std::ostream& out, precedence_t prec, std::streampos& newLinePrevPos, bool addParenthesesToLet);
    std::string getVal();
};

/** \brief
 * LetExpr class is used to give a variable a value
 */
class LetExpr : public Expr {
private:
    std::string variable;
    Expr* rhs;
    Expr* body;
public:
    LetExpr(std::string v, Expr* r, Expr* b);
    bool equals(Expr* expr) override;
    Val* interp() override;
    bool has_variable() override;
    Expr* subst(std::string s, Expr* expr) override;
    void print(std::ostream& out) override;
    void pretty_print_at(std::ostream& out, precedence_t precedence, std::streampos& newLinePrevPos, bool addParenthesesToLet) override;
};

class BoolExpr : public Expr {
private:
    bool val;
public:
    BoolExpr(bool v);
    bool equals(Expr* rhs) override;
    Val* interp() override;
    bool has_variable() override;
    Expr* subst(std::string s, Expr* expr) override;
    void print(std::ostream& out) override;
    void pretty_print_at(std::ostream& out, precedence_t precedence, std::streampos& newLinePrevPos, bool addParenthesesToLet) override;
};


#endif //MSDSCRIPT_EXPR_H
