//
// Created by Yue Sun on 2/14/23.
//

#include "parser.h"
#include <vector>
#include <set>

// <expr> = <addend> | <addend> + <expr>
Expr* parse_expr(std::istream& in) {
    Expr* lhs = parse_addend(in);
    skip_whitespace(in); // remove the white spaces after addend
    int c = in.peek();
    if (c == '+') {
        consume(in, '+');
        Expr* rhs = parse_expr(in);
        return new AddExpr(lhs, rhs);
    }
    return lhs;
}

// <addend> = <multicand> | <multicand> * <addend>
Expr* parse_addend(std::istream& in) {
    skip_whitespace(in);
    Expr* lhs = parse_multicand(in);
    skip_whitespace(in);
    int c = in.peek();
    if (c == '*') {
        consume(in, '*');
        Expr* rhs = parse_addend(in);
        return new MultExpr(lhs, rhs);
    }
    return lhs;
}

// <multicand> = <num> | (<expr>)
Expr* parse_multicand(std::istream& in) {
    skip_whitespace(in);
    int c = in.peek();
    if (c == '-' || isdigit(c)) {
        return parse_num(in);
    } else if (isalpha(c)) {
        return parse_var(in);
    } else if (c == '_') {
        return parse_let(in);
    } else if (c == '(') {
        consume(in, '(');
        Expr* expr = parse_expr(in);
        skip_whitespace(in);
        consume(in, ')', "parentheses mismatch");
        return expr;
    } else {
        consume(in, c);
        throw std::runtime_error("bad input");
    }
}

Expr* parse_num(std::istream& in) {
    int num = 0;
    bool negative = false;
    if (in.peek() == '-') {
        negative = true;
        consume(in, '-');
    }
    skip_whitespace(in);
    if (!isdigit(in.peek())) {
        throw std::runtime_error("invalid input");
    }
    int c;
    while (isdigit(c = in.peek())) {
        consume(in, c);
        num = num * 10 + c - '0';
    }
    std::set<char> ops = {'+', '*', '=', ')'};
    if (c != -1 && !isspace(c) && ops.find(c) == ops.end()) {
        throw std::runtime_error("bad input");
    }
    if (negative) {
        num = - num;
    }
    return new NumExpr(num);
}

Expr* parse_var(std::istream& in) {
    skip_whitespace(in);
    std::vector<char> s;
    int c;
    while (isalpha(c = in.peek())) {
        consume(in, c);
        s.push_back(c);
    }
    std::set<char> ops = {'+', '*', '=', ')'};
    if (c != -1 && !isspace(c) && ops.find(c) == ops.end()) {
        throw std::runtime_error("invalid variable name");
    }
    return new VarExpr(std::string(s.begin(), s.end()));
}

Expr* parse_let(std::istream& in) {
    std::string errorMsg = "wrong format for let expression";
    consume(in, "_let", errorMsg);
    Expr* temp = parse_var(in);
    VarExpr* var = dynamic_cast<VarExpr*>(temp);
    if (var == NULL) {
        throw std::runtime_error(errorMsg);
    }
    skip_whitespace(in);
    consume(in, '=', errorMsg);
    Expr* rhs = parse_expr(in);
    skip_whitespace(in);
    consume(in, "_in", errorMsg);
    Expr* body = parse_expr(in);
    return new LetExpr(var->getVal(), rhs, body);
}

void consume(std::istream& in, std::string expect, const std::string& message) {
    for (const char& c : expect) {
        consume(in, c, message);
    }
}

void consume(std::istream& in, int expect, const std::string& message) {
    int c = in.get();
    if (c != expect) {
        throw std::runtime_error(message);
    }
}

void skip_whitespace(std::istream& in) {
    int c;
    while (isspace(c = in.peek())) {
        consume(in, c);
    }
}

// used for tests
Expr* parse_str(std::string s) {
    std::istringstream in(s);
    return parse_expr(in);
}
