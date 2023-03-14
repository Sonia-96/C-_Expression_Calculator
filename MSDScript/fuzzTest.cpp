//
// Created by Yue Sun on 2/21/23.
//

#include <iostream>
#include "exec.h"
#include "ExprGen.h"
#include "val.h"

#define ITERATION 100

void testWithMSDScript();
void testArgs(int argc, const char* argv[]);
void printTestResult(const char* name, const char* modes[], double rate[]);
int checkResult(const ExecResult& expectedRes, const ExecResult& actualRes, const std::string& name1, const std::string& name2);


int main(int argc, const char * argv[]) {
//    testWithMSDScript();
    testArgs(argc, argv);
}

void testArgs(int argc, const char* argv[]) {
    srand(clock());
    if (argc == 2) {
        for (int i = 0; i < ITERATION; i++) {
            const char* interp_args[] = {argv[1], "--interp"};
            const char* print_args[] = {argv[1], "--print"};
            Expr* expr = ExprGen::exprGenerator();
            std::string in = expr->to_pretty_string();
            printf(">>> Trying:\n%s \n", in.c_str());
            ExecResult interp_result = exec_program(2, interp_args, in);
            ExecResult print_result = exec_program(2, print_args, in);
            ExecResult interp_result_2 = exec_program(2, interp_args, print_result.out);
            if (checkResult(interp_result, interp_result_2, "interp", "print") > 0) {
                exit(1);
            }
//            if (expr->interp()->to_string() + "\n" != interp_result.out) {
//                std::cout << "failed!\n";
//                std::cout << expr->interp()->to_string() + "\n";
//                std::cout << interp_result.err;
//                exit(1);
//            }
        }
    } else {
        const char* modes[] = {"--interp", "--print", "--pretty-print"};
        const char* expected_args[2];
        const char* actual_args[2];
        expected_args[0] = argv[1];
        actual_args[0] = argv[2];
        for (int j = 0; j < 3; j++) {
            printf("================================%s================================\n", modes[j]);
            expected_args[1] = modes[j];
            actual_args[1] = modes[j];
            for (int i = 0; i < ITERATION; i++) {
                Expr* expr = ExprGen::exprGenerator();
                std::string in = expr->to_string();
                printf("Trying:\n%s \n", in.c_str());
                ExecResult expected_res = exec_program(2, expected_args, in);
                ExecResult actual_res = exec_program(2, actual_args, in);
                if (checkResult(expected_res, actual_res, expected_args[0], actual_args[0]) > 0) {
                    exit(1);
                }
            }
        }
    }
}


void testWithMSDScript() {
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
            int failCount = 0;
            for (int k = 0; k < ITERATION; k++) {
                std::string in = ExprGen::random_expr_string();
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

int checkResult(const ExecResult& expectedRes, const ExecResult& actualRes, const std::string& name1, const std::string& name2) {
    if (expectedRes.exit_code == 0 && actualRes.exit_code == 0) {
        if (expectedRes.out != actualRes.out) {
            printf("%s:\n%s\n", name1.c_str(), expectedRes.out.c_str());
            printf("%s:\n%s\n", name2.c_str(), actualRes.out.c_str());
            std::cout << "\n";
            throw std::runtime_error("Different result!\n");
        } else {
            std::cout << "Test passed!\n";
            return 0;
        }
    } else {
        std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>> Failed test! >>>>>>>>>>>>>>>>>>>>>>>>>>\n";
        printf("%s: %d, %s\n", name1.c_str(), expectedRes.exit_code, expectedRes.err.c_str());
        printf("%s: %d, %s\n", name2.c_str(), actualRes.exit_code, actualRes.err.c_str());
        if (expectedRes.err != actualRes.err) {
            return 1;
        }
        return 0;
    }
}