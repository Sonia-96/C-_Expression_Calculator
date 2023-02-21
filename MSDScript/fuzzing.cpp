//
// Created by Yue Sun on 2/21/23.
//

#include "fuzzing.h"

std::string random_expr_string() {
    if (rand() % 10 < 6) {
        return std::to_string(rand());
    }
    // TODO add *
    return random_expr_string() + "+" + random_expr_string();
}
