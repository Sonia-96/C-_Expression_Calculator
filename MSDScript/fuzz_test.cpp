//
// Created by Yue Sun on 2/21/23.
//

#include <iostream>
#include "exec.h"
#include "expr_gen.h"

#define ITERATION 100

void testExecutables();
void testArgs(int argc, const char* argv[]);
void printTestResult(const char* name, const char* modes[], double rate[]);


int main(int argc, const char * argv[]) {
//    testExecutables();
    testArgs(argc, argv);
}

void testArgs(int argc, const char* argv[]) {
    const char* modes[] = {"--interp", "--print", "--pretty-print"};
    const char* expected_args[2];
    const char* actual_args[2];
    if (argc == 2) {
        expected_args[0] = "msdscript";
        actual_args[0] = argv[1];
    } else {
        expected_args[0] = argv[1];
        actual_args[0] = argv[2];
    }
    srand(clock());
    for (int j = 0; j < 3; j++) {
        printf("================================%s================================\n", modes[j]);
        expected_args[1] = modes[j];
        actual_args[1] = modes[j];
        for (int i = 0; i < ITERATION; i++) {
            std::string in = expr_gen::random_expr_string();
            printf("Trying:\n%s \n", in.c_str());

            ExecResult expected_res = exec_program(2, expected_args, in);
            ExecResult actual_res = exec_program(2, actual_args, in);
            if (expected_res.out != actual_res.out) {
                printf("%s:\n %s\n", expected_args[0], expected_res.out.c_str());
                printf("%s:\n %s\n", actual_args[0], actual_res.out.c_str());
                std::cout << "\n";
                throw std::runtime_error("Different result!\n");
            } else {
                std::cout << ">>> Test passed!\n";
            }
        }
    }
}


void testExecutables() {
    const char* modes[] = {"--interp", "--print", "--pretty-print"};
    const char* args1[2];
    const char* args2[2];
    args1[0] = "../msdscript";
    char buff[20];
    srand(clock());
    for (int i = 0; i < 8; i++) {
        strcpy(buff, args1[0]);
        strcat(buff, std::to_string(i).c_str());
        args2[0] = buff;
        double passRates[3];
        for (int j = 0; j < 3; j++) {
            args1[1] = modes[j];
            args2[1] = modes[j];
//            std::cout << args1[0] << " " << args1[1] << "\n";
//            std::cout << args2[0] << " " << args2[1] << "\n";
            int failCount = 0;
            for (int k = 0; k < ITERATION; k++) {
                std::string in = expr_gen::random_expr_string();
                ExecResult res1 = exec_program(2, args1, in);
                ExecResult res2 = exec_program(2, args2, in);
                if (res1.out != res2.out) {
                    failCount++;
                }
            }
            passRates[j] = (ITERATION + 0.0 - failCount) / ITERATION;
        }
        printTestResult(args2[0], modes, passRates);
    }
}

void printTestResult(const char* name, const char* modes[], double rate[]) {
    printf(">>>%s\n", name);
    for (int i = 0; i < 3; i++) {
        printf("%s: %.0f%%\n", modes[i], rate[i] * 100);
    }
}