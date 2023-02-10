//
//  expr.cpp
//  HW2_Expression
//
//  Created by Yue Sun on 1/12/23.
//

#include <sstream>
#include "expr.hpp"

// Expr

/**
 * Store the result of print method into a string.
 * @return the string representation of the print method
 */
std::string Expr::to_string() {
    std::stringstream st("");
    print(st);
    return st.str();
}

/**
 * Store the result of pretty_print method into a string.
 * @return the string representation of the pretty_print method
 */
std::string Expr::to_pretty_string() {
    std::stringstream st("");
    pretty_print(st);
    return st.str();
}

// Num Expression

/**
 * Constructs a NumExpr with the specified value and the precedence 0.
 * @param v the specified value
 */
NumExpr::NumExpr(int v) {
    val = v;
    prec = prec_none;
}

/**
 * Compared the specified expression with this object for equality.
 * @param expr the expression to be compared for equality with this object
 * @return true if the specified expression is a NumExpr object and it
 * has the same value with this object. Otherwise returns false.
 */
bool NumExpr::equals(Expr* expr) {
    NumExpr *n = dynamic_cast<NumExpr*>(expr);
    if (n == NULL) {
        return false;
    }
    return val == n -> val;
}

/**
 * Evaluated the expression and returns the int value.
 * @return the int value of the member variable val
 */
int NumExpr::interp() {
    return val;
}

/**
 * Check if this NumExpr expression object contains a VarExpr object.
 * @return false since a NumExpr object won't have a varibale
 */
bool NumExpr::has_variable() {
    return false;
}

/**
 * Substitute the specified string in this object with a specified expression
 * @param s the specified string to be substituted
 * @param expr the specified expression used to substitute the string
 * @return a new NumExpr object with the same value as this object
 */
Expr* NumExpr::subst(std::string s, Expr *expr) {
    return new NumExpr(val);
}

/**
 * Print this object.
 * @param out the output stream used to print this object
 */
void NumExpr::print(std::ostream& out) {
    out << val;
}

/**
 * Print this object in a prettier way. To specify, we'll
 * omit redundant parentheses and add space around operators.
 * @param out the output stream used to print this object
 */
void NumExpr::pretty_print(std::ostream& out) {
    out << val;
}

// Add Expression

/**
 * Constructs a AddExpr object with the specified left and right expressions.
 * @param left the specified left expression
 * @param right the specified right expression
 */
AddExpr::AddExpr(Expr *left, Expr *right) {
    lhs = left;
    rhs = right;
    prec = prec_add;
}

/**
 * Constructs a AddExpr object with the specified int values.
 * @param left the specified int value in the left expression
 * @param right the specified int value in the right expression
 */
AddExpr::AddExpr(int left, int right) {
    lhs = new NumExpr(left);
    rhs = new NumExpr(right);
    prec = prec_add;
}

/**
 * Constructs a AddExpr object with a specified string as the left
 * expression and a specified int value as the right expression.
 * @param left the specified string in the left expression
 * @param right the specified int value in the right expression
 */
AddExpr::AddExpr(std::string left, int right) {
    lhs = new VarExpr(left);
    rhs = new NumExpr(right);
    prec = prec_add;
}

/**
 * Constructs a AddExpr object with a specified int as the left
 * expression and a specified string value as the right expression.
 * @param left the specified int value in the left expression
 * @param right the specified string in the right expression
 */
AddExpr::AddExpr(int left, std::string right) {
    lhs = new NumExpr(left);
    rhs = new VarExpr(right);
    prec = prec_add;
}

/**
 * Constructs a AddExpr object with the specified strings.
 * @param left the specified string in the left VarExpr expression
 * @param right the specified string in the right VarExpr expression
 */
AddExpr::AddExpr(std::string left, std::string right) {
    lhs = new VarExpr(left);
    rhs = new VarExpr(right);
    prec = prec_add;
}

/**
 * Compared the specified expression with this object for equality.
 * @param expr the expression to be compared for equality with this object
 * @return true if the specified expression is a AddExpr object and it
 * has the same value with this object. Otherwise returns false.
 */
bool AddExpr::equals(Expr* expr) {
    AddExpr *a = dynamic_cast<AddExpr*>(expr);
    if (a == NULL) {
        return false;
    }
    return lhs->equals(a->lhs) && rhs->equals(a->rhs);
}

/**
 * Add the left and right expressions and returns the int value of the result.
 * @return the int value of the addition of the left and right expressions
 */
int AddExpr::interp() {
    return lhs->interp() + rhs->interp();
}

/**
 * Check if this AddExpr expression object contains a VarExpr object.
 * @return true if either its left or right expression contains a VarExpr object
 */
bool AddExpr::has_variable() {
    return lhs->has_variable() || rhs->has_variable();
}

/**
 * Substitute the specified string in this object with a specified expression
 * @param s the specified string to be substituted
 * @param expr the specified expression used to substitute the string
 * @return a new AddExpr object with the specified strings in its
 * left and right expressions have been substituted
 */
Expr* AddExpr::subst(std::string s, Expr *expr) {
    return new AddExpr(lhs->subst(s, expr), rhs->subst(s, expr));
}

/**
 * Print this object with parentheses and a add sign.
 * @param out the output stream used to print this object
 */
void AddExpr::print(std::ostream& out) {
    out << "(";
    lhs -> print(out);
    out << "+";
    rhs -> print(out);
    out << ")";
}

/**
 * Print this object in a prettier way. To specify, we'll
 * omit redundant parentheses and add a space around operators.
 * @param out the output stream used to print this object
 */
void AddExpr::pretty_print(std::ostream &out) {
    if (lhs -> get_precedence() != 0 && lhs -> get_precedence() <= prec_add) {
        out << "(";
        lhs -> pretty_print(out);
        out << ")";
    } else {
        lhs -> pretty_print(out);
    }
    out << " + ";
    rhs -> pretty_print(out);
}

// Mult Expression

/**
 * Constructs a MultExpr object with the specified left and right expressions.
 * @param left the specified left expression
 * @param right the specified right expression
 */
MultExpr::MultExpr(Expr *left, Expr *right) {
    lhs = left;
    rhs = right;
    prec = prec_mult;
}

/**
 * Constructs a MultExpr object with the specified int values.
 * @param left the specified int value in the left expression
 * @param right the specified int value in the right expression
 */
MultExpr::MultExpr(int left, int right) {
    lhs = new NumExpr(left);
    rhs = new NumExpr(right);
    prec = prec_mult;
}

/**
 * Constructs a MultExpr object with a specified string as the left
 * expression and a specified int value as the right expression.
 * @param left the specified string in the left expression
 * @param right the specified int value in the right expression
 */
MultExpr::MultExpr(std::string left, int right) {
    lhs = new VarExpr(left);
    rhs = new NumExpr(right);
    prec = prec_mult;
}

/**
 * Constructs a MultExpr object with a specified int as the left
 * expression and a specified string value as the right expression.
 * @param left the specified int value in the left expression
 * @param right the specified string in the right expression
 */
MultExpr::MultExpr(int left, std::string right) {
    lhs = new NumExpr(left);
    rhs = new VarExpr(right);
    prec = prec_mult;
}

/**
 * Constructs a MultExpr object with the specified strings.
 * @param left the specified string in the left VarExpr expression
 * @param right the specified string in the right VarExpr expression
 */
MultExpr::MultExpr(std::string left, std::string right) {
    lhs = new VarExpr(left);
    rhs = new VarExpr(right);
    prec = prec_mult;
}

/**
 * Compared the specified expression with this object for equality.
 * @param expr the expression to be compared for equality with this object
 * @return true if the specified expression is a MultExpr object and it
 * has the same value with this object. Otherwise returns false.
 */
bool MultExpr::equals(Expr* expr) {
    MultExpr *m = dynamic_cast<MultExpr*>(expr);
    if (m == NULL) {
        return false;
    }
    return lhs->equals(m->lhs) && rhs->equals(m->rhs);
}

/**
 * Multiply the left and right expressions and returns the int value of the result.
 * @return the int value of the multiplication of the left and right expressions
 */
int MultExpr::interp() {
    return lhs->interp() * rhs -> interp();
}

/**
 * Check if this MultExpr expression object contains a VarExpr object.
 * @return true if either its left or right expression contains a VarExpr object
 */
bool MultExpr::has_variable() {
    return lhs->has_variable() || rhs->has_variable();
}

/**
 * Substitute the specified string in this object with a specified expression
 * @param s the specified string to be substituted
 * @param expr the specified expression used to substitute the string
 * @return a new MultExpr object with the specified strings in its
 * left and right expressions have been substituted
 */
Expr* MultExpr::subst(std::string s, Expr *expr) {
    return new MultExpr(lhs->subst(s, expr), rhs->subst(s, expr));
}

/**
 * Print this object with parentheses and a add sign.
 * @param out the output stream used to print this object
 */
void MultExpr::print(std::ostream& out) {
    out << "(";
    lhs -> print(out);
    out << "*";
    rhs -> print(out);
    out << ")";
}

/**
 * Print this object in a prettier way. To specify, we'll
 * omit redundant parentheses and add a space around operators.
 * @param out the output stream used to print this object
 */
void MultExpr::pretty_print(std::ostream &out) {
    if (lhs -> get_precedence() != 0 && lhs -> get_precedence() <= prec_mult) {
        out << "(";
        lhs -> pretty_print(out);
        out << ")";
    } else {
        lhs -> pretty_print(out);
    }
    out << " * ";
    if (rhs -> get_precedence() != 0 && rhs -> get_precedence() < prec_mult) {
        out << "(";
        rhs -> pretty_print(out);
        out << ")";
    } else {
        rhs -> pretty_print(out);
    }
}

// Variable Expression

/**
 * Constructs a NumExpr with the specified string and the precedence 0.
 * @param s the specified string
 */
VarExpr::VarExpr(std::string s) {
    val = s;
    prec = prec_none;
}

/**
 * Compared the specified expression with this object for equality.
 * @param expr the expression to be compared for equality with this object
 * @return true if the specified expression is a VarExpr object and it
 * has the same value with this object. Otherwise returns false.
 */
bool VarExpr::equals(Expr* expr) {
    VarExpr *var = dynamic_cast<VarExpr*>(expr);
    if (var == NULL) {
        return false;
    }
    return val == var->val;
}

/**
 * Returns the int value of this VarExpr object
 * @return throw a runtime error since a varibale cannot be evaluated to a int value
 */
int VarExpr::interp() {
    throw std::runtime_error("A variable has no value!");
}

/**
 * Check if this VarExpr expression object contains a VarExpr object.
 * @return true because a VarExpr object always contains a VarExpr object
 */
bool VarExpr::has_variable() {
    return true;
}

/**
 * Substitute the specified string in this object with a specified expression
 * @param s the specified string to be substituted
 * @param expr the specified expression used to substitute the string
 * @return the specified expression if s equals val, otherwise return
 * a new VarExpr object with the same val as this object
 */
Expr* VarExpr::subst(std::string s, Expr* expr) {
    if (val == s) {
        return expr; // TODO just return expr?
    }
    return new VarExpr(val);
}

/**
 * Print this object.
 * @param out the output stream used to print this object
 */
void VarExpr::print(std::ostream& out) {
    out << val;
}

/**
 * Print this object in a prettier way.
 * @param out the output stream used to print this object
 */
void VarExpr::pretty_print(std::ostream& out) {
    out << val;
}
