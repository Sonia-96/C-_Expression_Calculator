//
// Created by Yue Sun on 3/30/23.
//

#ifndef MSDSCRIPT_ENV_H
#define MSDSCRIPT_ENV_H

#include "pointer.h"
#include <string>

class Val;
class Expr;

CLASS(Env) {
public:
    static PTR(Env) empty;
    virtual PTR(Val) lookup(std::string find_name) = 0;
};

class EmptyEnv : public Env {
public:
    PTR(Val) lookup(std::string find_name);
};

class ExtendedEnv : public Env {
private:
    std::string name;
    PTR(Val) val;
    PTR(Env) rest;
public:
    ExtendedEnv(std::string name_, PTR(Val) val_, PTR(Env) rest_);
    PTR(Val) lookup(std::string find_name);
};


#endif //MSDSCRIPT_ENV_H
