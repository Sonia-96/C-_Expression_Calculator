//
//  expr.cpp
//  HW2_Expression
//
//  Created by Yue Sun on 1/12/23.
//

#include <sstream>
#include "val.h"
#include "expr.h"

////////////////////////////////////////////
//                  Expr                  //
///////////////////////////////////////////

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

/**
 * Print an Expr object in a prettier format.
 * @param out the output stream
 */
void Expr::pretty_print(std::ostream &out) {
    std::streampos pos = out.tellp();
    pretty_print_at(out, prec_none, pos, false);
}

///////////////////////////////////////////
//                NumExpr                //
///////////////////////////////////////////

/**
 * Constructs a NumExpr with the specified value and the precedence 0.
 * @param v the specified value
 */
NumExpr::NumExpr(int v) {
    val = v;
}

/**
 * Compared the specified expression with this object for equality.
 * @param expr the expression to be compared for equality with this object
 * @return true if the specified expression is a NumExpr object and it
 * has the same value with this object. Otherwise returns false.
 */
bool NumExpr::equals(Expr* expr) {
    NumExpr *n = dynamic_cast<NumExpr*>(expr);
    if (n == nullptr) {
        return false;
    }
    return val == n->val;
}

/**
 * Evaluated the expression and returns the int value.
 * @return the int value of the member variable val
 */
Val* NumExpr::interp() {
    return new NumVal(val);
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
    return this;
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
void NumExpr::pretty_print_at(std::ostream& out, precedence_t precedence, std::streampos& newLinePrevPos, bool addParen) {
    out << val;
}

///////////////////////////////////////////
//                AddExpr                //
///////////////////////////////////////////

/**
 * Constructs a AddExpr object with the specified left and right expressions.
 * @param left the specified left expression
 * @param right the specified right expression
 */
AddExpr::AddExpr(Expr *left, Expr *right) {
    lhs = left;
    rhs = right;
}

/**
 * Constructs a AddExpr object with the specified int values.
 * @param left the specified int value in the left expression
 * @param right the specified int value in the right expression
 */
AddExpr::AddExpr(int left, int right) {
    lhs = new NumExpr(left);
    rhs = new NumExpr(right);
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
}

/**
 * Constructs a AddExpr object with the specified strings.
 * @param left the specified string in the left VarExpr expression
 * @param right the specified string in the right VarExpr expression
 */
AddExpr::AddExpr(std::string left, std::string right) {
    lhs = new VarExpr(left);
    rhs = new VarExpr(right);
}

AddExpr::AddExpr(int left, Expr* right) {
    lhs = new NumExpr(left);
    rhs = right;
}

AddExpr::AddExpr(Expr* left, int right) {
    lhs = left;
    rhs = new NumExpr(right);
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
Val* AddExpr::interp() {
    return lhs->interp()->add_to(rhs->interp());
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
    lhs->print(out);
    out << "+";
    rhs->print(out);
    out << ")";
}

/**
 * Print this object in a prettier way. To specify, we'll
 * omit redundant parentheses and add a space around operators.
 * @Rules
 * An expression can be represented as: lhs op rhs. And
 * the operator (op) is right associative. Therefore:<br>
 * For expressions other than LetExpr:<br>
 * - if precedence(lhs) \<= op, add parentheses around lhs<br>
 * - if precedence(rhs) \< op (or precedence(rhs) \<= op - 1), add parentheses around rhs<br>
 * For letExpr: only add parentheses when it's in lhs
 * @param out the output stream used to print this object
 * @param precedence the precedence of the outer expression (or the op in the above expression)
 * @param newLinePrevPos the position of the previous new line in the output stream
 * @param addParen should we add parentheses around a LetExpr object
 */
void AddExpr::pretty_print_at(std::ostream &out, precedence_t precedence, std::streampos& newLinePrevPos, bool addParen) {
    bool printParen = prec_add <= precedence;
    if (printParen) {
        out << "(";
    }
    lhs->pretty_print_at(out, prec_add, newLinePrevPos, true);
    out << " + ";
    // let as right arg in AddExpr never need parentheses
    rhs->pretty_print_at(out, prec_equal, newLinePrevPos, false);
    if (printParen) {
        out << ")";
    }
}

////////////////////////////////////////////
//                MultExpr               //
///////////////////////////////////////////

/**
 * Constructs a MultExpr object with the specified left and right expressions.
 * @param left the specified left expression
 * @param right the specified right expression
 */
MultExpr::MultExpr(Expr *left, Expr *right) {
    lhs = left;
    rhs = right;
}

/**
 * Constructs a MultExpr object with the specified int values.
 * @param left the specified int value in the left expression
 * @param right the specified int value in the right expression
 */
MultExpr::MultExpr(int left, int right) {
    lhs = new NumExpr(left);
    rhs = new NumExpr(right);
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
}

/**
 * Constructs a MultExpr object with the specified strings.
 * @param left the specified string in the left VarExpr expression
 * @param right the specified string in the right VarExpr expression
 */
MultExpr::MultExpr(std::string left, std::string right) {
    lhs = new VarExpr(left);
    rhs = new VarExpr(right);
}

MultExpr::MultExpr(int left, Expr* right) {
    lhs = new NumExpr(left);
    rhs = right;
}

MultExpr::MultExpr(Expr* left, int right) {
    lhs = left;
    rhs = new NumExpr(right);
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
Val* MultExpr::interp() {
    return lhs->interp()->mult_with(rhs->interp());
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
 * @Rules
 * An expression can be represented as: lhs op rhs. And
 * the operator (op) is right associative. Therefore:<br>
 * For expressions other than LetExpr:<br>
 * - if precedence(lhs) \<= op, add parentheses around lhs<br>
 * - if precedence(rhs) \< op (or precedence(rhs) \<= op - 1), add parentheses around rhs<br>
 * For letExpr:
 * - add parentheses when it's in lhs<br>
 * - add parentheses when it's in rhs and this MultExpr object is followed with an AddExpr
 * @param out the output stream used to print this object
 * @param precedence the precedence of the outer expression (or the op in the above expression)
 * @param newLinePrevPos the position of the previous new line in the output stream
 * @param addParen should we add parentheses around a LetExpr object
 */
void MultExpr::pretty_print_at(std::ostream &out, precedence_t precedence, std::streampos& newLinePrevPos, bool addParen) {
    bool printParen = prec_mult <= precedence;
    if (printParen) {
        out << "(";
    }
    lhs->pretty_print_at(out, prec_mult, newLinePrevPos, true);
    out << " * ";
    // add parentheses for rhs when : 1. rhs is let 2. the outermost mult expression is followed with an add expression
    rhs->pretty_print_at(out, prec_add, newLinePrevPos, addParen && !printParen);
    if (printParen) {
        out << ")";
    }
}

///////////////////////////////////////////
//                VarExpr                //
///////////////////////////////////////////

/**
 * Constructs a NumExpr with the specified string and the precedence 0.
 * @param s the specified string
 */
VarExpr::VarExpr(std::string s) {
    val = s;
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
 * @return throw a runtime error since a variable cannot be evaluated to a int value
 */
Val * VarExpr::interp() {
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
        return expr;
    }
    return this;
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
void VarExpr::pretty_print_at(std::ostream& out, precedence_t precedence, std::streampos& newLinePrevPos, bool addParen) {
    out << val;
}

std::string VarExpr::getVal() {
    return val;
}

///////////////////////////////////////////
//                LetExpr                //
///////////////////////////////////////////

/**
 * Constructs a LetExpr object with given variable name, rhs, and body
 * @param v given variable name
 * @param r given rhs expression
 * @param b given body expression
 */
LetExpr::LetExpr(std::string v, Expr* r, Expr* b) {
    variable = v;
    rhs = r;
    body = b;
}

/**
 * Compared the specified expression with this object for equality.
 * @param expr the expression to be compared for equality with this object
 * @return true if the specified expression is a LetExpr object and all
 * the member variables are equal. Otherwise returns false.
 */
bool LetExpr::equals(Expr* expr) {
    LetExpr* other = dynamic_cast<LetExpr*>(expr);
    if (other == nullptr) {
        return false;
    }
    return variable == other->variable && rhs->equals(other->rhs) && body->equals(other->body);
}

/**
 * Returns the int value of this LetExpr object
 * @return the int value of the its body after substitute the variable with rhs
 */
Val * LetExpr::interp() {
    Val* rhs_val = rhs->interp();
    return body->subst(variable, rhs_val->to_expr())->interp();
//    return body->subst(variable, rhs)->interp(); not correct
}

/**
 * Check if this LetExpr object contains a VarExpr object.
 * @return true only when its rhs or body has a VarExpr object.
 * Otherwise returns false.
 */
bool LetExpr::has_variable() {
    return rhs->has_variable() || body->has_variable();
}

/**
 * Substitute the specified string in this object with a specified expression
 * @param s the specified string to be substituted
 * @param expr the specified expression used to substitute the string
 * @return a new LetExpr object with the specified strings in its
 * left and right expressions which have been substituted
 */
Expr* LetExpr::subst(std::string s, Expr* expr) {
    // substitute rhs first, so the value of higher-level variable can be passed to the lower level
    Expr* temp = rhs->subst(s, expr);
    // if variable == s, update the value of the variable
    if (variable == s) {
        return new LetExpr(variable, temp, body);
    }
    // else substitute the body
    return new LetExpr(variable, temp, body->subst(s, expr));
}

/**
 * Print this object. There will always be parentheses outside of a LetExpr object.
 * @param out the output stream
 */
void LetExpr::print(std::ostream& out) {
    out << "(_let " << variable << "=";
    rhs->print(out);
    out << " _in ";
    body->print(out);
    out << ")";
}

/**
* Print a LetExpr object in a prettier way. To specify, we'll
* omit redundant parentheses and add a space around operators.
* @Rules
* 1. the rhs or body need no more parentheses if they are the whole expression <br>
* 2. needs parentheses as the left argument of + or * <br>
* 3. needs parentheses as the right argument of an un-parenthesized * <br>
* @param out the output stream used to print this object
* @param precedence the precedence of the outer expression (or the op in the above expression)
* @param newLinePrevPos the position of the previous new line in the output stream
* @param addParen should we add parentheses around a LetExpr object
*/
void LetExpr::pretty_print_at(std::ostream& out, precedence_t precedence, std::streampos& newLinePrevPos, bool addParen) {
    if (addParen) {
        out << "(";
    }
    int indentation = out.tellp() - newLinePrevPos;
    out << "_let " << variable << " = ";
    rhs->pretty_print_at(out, prec_none,newLinePrevPos, false);
    out << "\n";
    newLinePrevPos = out.tellp();

    out << std::string(indentation, ' ');
    out << "_in  ";
    body->pretty_print_at(out, prec_none, newLinePrevPos, false);

    if (addParen) {
        out << ")";
    }
}

  ///////////////////////////////////////////
 //               BoolExpr                //
///////////////////////////////////////////

BoolExpr::BoolExpr(bool v) {
    val = v;
}

bool BoolExpr::equals(Expr* rhs) {
    BoolExpr* other = dynamic_cast<BoolExpr*>(rhs);
    if (other == nullptr) {
        return false;
    }
    return val == other->val;
}

Val* BoolExpr::interp() {
    return new BoolVal(val);
}


bool BoolExpr::has_variable() {
    return false;
}

Expr* BoolExpr::subst(std::string s, Expr* expr) {
    return this; // TODO is this right?
}

void BoolExpr::print(std::ostream& out) {
    val ? out << "_true" : out << "_false";
}

void BoolExpr::pretty_print_at(std::ostream& out, precedence_t precedence, std::streampos& newLinePrevPos, bool addParen) {
    val ? out << "_true" : out << "_false";
}

  ///////////////////////////////////////////
 //                IfExpr                 //
///////////////////////////////////////////

IfExpr::IfExpr(Expr* test, Expr* then, Expr* else_) {
    test_part = test;
    then_part = then;
    else_part = else_;
}

bool IfExpr::equals(Expr* rhs) {
    IfExpr* other = dynamic_cast<IfExpr*>(rhs);
    if (other == nullptr) {
        return false;
    }
    return test_part->equals(other->test_part) && then_part->equals(other->then_part) && else_part->equals(other->else_part);
}

Val* IfExpr::interp() {
    if (test_part->interp()->is_true()) {
        return then_part->interp();
    }
    return else_part->interp();
}

bool IfExpr::has_variable() {
    return test_part->has_variable() || then_part->has_variable() || else_part->has_variable();
}

Expr* IfExpr::subst(std::string s, Expr* expr) {
    return new IfExpr(test_part->subst(s, expr), then_part->subst(s, expr), else_part->subst(s, expr));
}

void IfExpr::print(std::ostream& out) {
    out << "(_if ";
    test_part->print(out);
    out << " _then ";
    then_part->print(out);
    out << " _else ";
    else_part->print(out);
    out << ")";
}

void IfExpr::pretty_print_at(std::ostream& out, precedence_t precedence, std::streampos& newLinePrevPos, bool addParen) {
    if (addParen) {
        out << "(";
    }
    int indentation = out.tellp() - newLinePrevPos;
    out << "_if ";
    test_part->pretty_print_at(out, prec_none, newLinePrevPos, false);
    out << "\n";
    newLinePrevPos = out.tellp();

    out << std::string(indentation, ' ') << "_then ";
    then_part->pretty_print_at(out, prec_none, newLinePrevPos, false);
    out << "\n";
    newLinePrevPos = out.tellp();

    out << std::string(indentation, ' ') << "_else ";
    else_part->pretty_print_at(out, prec_none, newLinePrevPos, false);

    if (addParen) {
        out << ")";
    }
}

  ///////////////////////////////////////////
 //                EqExpr                 //
///////////////////////////////////////////

EqExpr::EqExpr(Expr* left, Expr* right) {
    lhs = left;
    rhs = right;
}

EqExpr::EqExpr(int left, int right) {
    lhs = new NumExpr(left);
    rhs = new NumExpr(right);
}

bool EqExpr::equals(Expr* rhs_) {
    EqExpr* other = dynamic_cast<EqExpr*>(rhs_);
    if (other == nullptr) {
        return false;
    }
    return lhs->equals(other->lhs) && rhs->equals(other->rhs);
}

Val* EqExpr::interp() {
    return new BoolVal(lhs->interp()->equals(rhs->interp()));
}

bool EqExpr::has_variable() {
    return lhs->has_variable() || rhs->has_variable();
}

Expr *EqExpr::subst(std::string s, Expr* expr) {
    return new EqExpr(lhs->subst(s, expr), rhs->subst(s, expr));
}

void EqExpr::print(std::ostream& out) {
    out << "(";
    lhs->print(out);
    out << "==";
    rhs->print(out);
    out << ")";
}

void EqExpr::pretty_print_at(std::ostream& out, precedence_t precedence, std::streampos& newLinePrevPos,
                             bool addParen) {
    bool printParen = prec_equal <= precedence;
    if (printParen) {
        out << "(";
    }
    lhs->pretty_print_at(out, prec_equal, newLinePrevPos, true);
    out << " == ";
    rhs->pretty_print_at(out, prec_none, newLinePrevPos, !printParen && addParen);
    if (printParen) {
        out << ")";
    }
}




