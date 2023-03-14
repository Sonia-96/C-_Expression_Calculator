//
// Created by Yue Sun on 2/14/23.
//

#include "parser.h"
#include <vector>
#include <set>

// <expr> = <comparg> | <comparg> == <expr>
Expr* parse_expr(std::istream& in) {
    Expr* lhs = parse_comparg(in);
    skip_whitespace(in);
    int c = in.peek();
    if (c == '=') {
        consume(in, "==");
        Expr* rhs = parse_expr(in);
        return new EqExpr(lhs, rhs);
    }
    return lhs;
}

// <comparg> = <addend> | <addend> + <comparg>
Expr* parse_comparg(std::istream& in) {
    Expr* lhs = parse_addend(in);
    skip_whitespace(in); // remove the white spaces after addend
    int c = in.peek();
    if (c == '+') {
        consume(in, '+');
        Expr* rhs = parse_comparg(in);
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
    std::set<char> ops = {'+', '*', '=', ')', '_'}; // handle "<expr> <expr>" error
    if (c != -1 && ops.find(c) == ops.end()) {
        throw std::runtime_error("bad input");
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
        consume(in, c);
        std::string keyword = parse_keyword(in);
        if (keyword == "let") {
            return parse_let(in);
        } else if (keyword == "false") {
            return new BoolExpr(false);
        } else if (keyword == "true") {
            return new BoolExpr(true);
        } else if (keyword == "if") {
            return parse_if(in);
        }
        throw std::runtime_error("unknown keyword: " + keyword);
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
    if (!isdigit(in.peek())) {
        throw std::runtime_error("invalid input");
    }
    int c;
    while (isdigit(c = in.peek())) {
        consume(in, c);
        num = num * 10 + c - '0';
    }
    if (negative) {
        num = - num;
    }
    return new NumExpr(num);
}

Expr* parse_let(std::istream& in) {
    std::string errorMsg = "wrong format for let expression";
//    consume(in, "_let", errorMsg);
    VarExpr* var = dynamic_cast<VarExpr*>(parse_var(in));
    skip_whitespace(in);
    consume(in, '=', errorMsg);
    Expr* rhs = parse_expr(in);
    skip_whitespace(in);
    consume(in, "_in", errorMsg);
    Expr* body = parse_expr(in);
    return new LetExpr(var->getVal(), rhs, body);
}

Expr* parse_if(std::istream& in) {
    std::string errorMsg = "wrong format for if expression";
    Expr* test_part = parse_expr(in);
    consume(in, "_then", errorMsg);
    Expr* then_part = parse_expr(in);
    consume(in, "_else", errorMsg);
    Expr* else_part = parse_expr(in);
    return new IfExpr(test_part, then_part, else_part);
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

std::string parse_keyword(std::istream& in) {
    std::stringstream ss;
    char c;
    while (isalpha(c = in.peek())) {
        consume(in, c);
        ss << c;
    }
    return ss.str();
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
