//
// Created by Yue Sun on 2/21/23.
//

#ifndef MSDSCRIPT_EXEC_H
#define MSDSCRIPT_EXEC_H

#include <string>

class ExecResult {
public:
    int exit_code;
    std::string out;
    std::string err;
};

ExecResult exec_program(int argc, const char** argv, std::string in);

#endif //MSDSCRIPT_EXEC_H
