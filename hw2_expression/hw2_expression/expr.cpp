//
//  expr.cpp
//  HW2_Expression
//
//  Created by Yue Sun on 1/12/23.
//

#include <sstream>
#include <stdexcept>
#include <string>
#include <iostream>
#include "expr.hpp"

// Num Expression

NumExpr::NumExpr(int v) {
    val = v;
}

bool NumExpr::equals(Expr* expr) {
    NumExpr *n = dynamic_cast<NumExpr*>(expr);
    if (n == NULL) {
        return false;
    }
    return val == n -> val;
}

int NumExpr::interp() {
    return val;
}

bool NumExpr::has_variable() {
    return false;
}

Expr* NumExpr::subst(std::string s, Expr *expr) {
    return new NumExpr(val);
}

void NumExpr::print(std::ostream& out) {
    out << val;
}

std::string NumExpr::to_string() {
    std::stringstream st("");
    print(st);
    return st.str();
}

// Add Expression

AddExpr::AddExpr(Expr *left, Expr *right) {
    lhs = left;
    rhs = right;
}

AddExpr::AddExpr(int left, int right) {
    lhs = new NumExpr(left);
    rhs = new NumExpr(right);
}

AddExpr::AddExpr(std::string left, int right) {
    lhs = new VarExpr(left);
    rhs = new NumExpr(right);
}

AddExpr::AddExpr(int left, std::string right) {
    lhs = new NumExpr(left);
    rhs = new VarExpr(right);
}

AddExpr::AddExpr(std::string left, std::string right) {
    lhs = new VarExpr(left);
    rhs = new VarExpr(right);
}

bool AddExpr::equals(Expr* expr) {
    AddExpr *a = dynamic_cast<AddExpr*>(expr);
    if (a == NULL) {
        return false;
    }
    return lhs->equals(a->lhs) && rhs->equals(a->rhs);
}

int AddExpr::interp() {
    return lhs->interp() + rhs->interp();
}

bool AddExpr::has_variable() {
    return lhs->has_variable() || rhs->has_variable();
}

Expr* AddExpr::subst(std::string s, Expr *expr) {
    return new AddExpr(lhs->subst(s, expr), rhs->subst(s, expr));
}

void AddExpr::print(std::ostream& out) {
    out << "(";
    lhs -> print(out);
    out << "+";
    rhs -> print(out);
    out << ")";
}

std::string AddExpr::to_string() {
    std::stringstream st("");
    print(st);
    return st.str();
}

// Mult Expression

MultExpr::MultExpr(Expr *left, Expr *right) {
    lhs = left;
    rhs = right;
}

MultExpr::MultExpr(int left, int right) {
    lhs = new NumExpr(left);
    rhs = new NumExpr(right);
}

MultExpr::MultExpr(std::string left, int right) {
    lhs = new VarExpr(left);
    rhs = new NumExpr(right);
}

MultExpr::MultExpr(int left, std::string right) {
    lhs = new NumExpr(left);
    rhs = new VarExpr(right);
}

MultExpr::MultExpr(std::string left, std::string right) {
    lhs = new VarExpr(left);
    rhs = new VarExpr(right);
}

bool MultExpr::equals(Expr* expr) {
    MultExpr *m = dynamic_cast<MultExpr*>(expr);
    if (m == NULL) {
        return false;
    }
    return lhs->equals(m->lhs) && rhs->equals(m->rhs);
}

int MultExpr::interp() {
    return lhs->interp() * rhs -> interp();
}

bool MultExpr::has_variable() {
    return lhs->has_variable() || rhs->has_variable();
}

Expr* MultExpr::subst(std::string s, Expr *expr) {
    return new MultExpr(lhs->subst(s, expr), rhs->subst(s, expr));
}

void MultExpr::print(std::ostream& out) {
    out << "(";
    lhs -> print(out);
    out << "*";
    rhs -> print(out);
    out << ")";
}

std::string MultExpr::to_string() {
    std::stringstream st("");
    print(st);
    return st.str();
}

// Variable Expression

VarExpr::VarExpr(std::string s) {
    val = s;
}

bool VarExpr::equals(Expr* expr) {
    VarExpr *var = dynamic_cast<VarExpr*>(expr);
    if (var == NULL) {
        return false;
    }
    return val == var->val;
}

int VarExpr::interp() {
    throw std::runtime_error("A variable has no value!");
}

bool VarExpr::has_variable() {
    return true;
}

Expr* VarExpr::subst(std::string s, Expr* expr) {
    if (val == s) {
        return expr; // TODO just return expr?
    }
    return new VarExpr(val);
}

void VarExpr::print(std::ostream& out) {
    out << val;
}

std::string VarExpr::to_string() {
    std::stringstream st("");
    print(st);
    return st.str();
}
