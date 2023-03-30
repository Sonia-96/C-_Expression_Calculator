//
// Created by Yue Sun on 2/9/23.
//

#ifndef MSDSCRIPT_CMDLINE_H
#define MSDSCRIPT_CMDLINE_H

enum run_mode_t {
    do_nothing,
    do_interp,
    do_print,
    do_pretty_print
};

run_mode_t use_arguments(int argc, const char* argv[], const char** filename);

#endif //MSDSCRIPT_CMDLINE_H
