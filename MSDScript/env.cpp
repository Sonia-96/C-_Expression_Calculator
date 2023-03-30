//
// Created by Yue Sun on 3/30/23.
//

#include "env.h"

PTR(Env) Env::empty = NEW(EmptyEnv)();

PTR(Val) EmptyEnv::lookup(std::string find_name) {
    throw std::runtime_error("free variable: " + find_name);
};

ExtendedEnv::ExtendedEnv(std::string name_, PTR(Val) val_, PTR(Env) rest_) {
    name = name_;
    val = val_;
    rest = rest_;
}

PTR(Val) ExtendedEnv::lookup(std::string find_name) {
    if (find_name == name) {
        return val;
    } else {
        return rest->lookup(find_name);
    }
};
