//
//  leetcode227.c
//  myleetcodetest
//
//  Created by jason on 2024-06-16.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "leetcode227.h"

// 1. 表达式求值和中缀转后缀，是同一个算法
int precedence(char c) {
    if (c == '+' || c == '-') {
        return 1;
    } else if (c == '*' || c == '/') {
        return 2;
    }
    return -1;
}

int evalLT227(int num1, char op, int num2) {
    //printf("Eval %d %c %d\n", num1, op, num2);
    if (op == '+') {
        return num1 + num2;
    } else if (op == '-') {
        return num1 - num2;
    } else if (op == '*') {
        return num1 * num2;
    } else if (op == '/') {
        return num1 / num2;
    }
    printf("Invalid op: %c\n", op);
    return -1;
}

// 1. 如果不想用atoi，可以每次乘以10这样来获得整数
int calculate(char* s) {
    int stackOperand[300000] = {0};
    int topOperand = 0;
    char stackOperator[300000] = {0};
    int topOperator = 0;

    int retVal = 0;

    char* p = s;
    char numBuf[32] = {0};
    int numBufIdx = 0;
    while (*p) {
        if (*p >= '0' && *p <= '9') {
            //printf("Accumulate num: %c\n", *p);
            numBuf[numBufIdx++] = *p;
        } else if (*p == ' ') { // Ignore
        } else {
            if (numBufIdx > 0) {
                numBuf[numBufIdx++] = '\0';
                int num = atoi(numBuf);
                //printf("Push num: %d\n", num);
                stackOperand[topOperand++] = num;

                numBufIdx = 0;
            }
            if (*p == '+' || *p == '-' || *p == '*' || *p == '/') {
                // 注意：这里优先级等于的情况也要出栈计算，否则加减就无法保证从左到右计算，导致结果不对
                while (topOperator > 0 && precedence(stackOperator[topOperator - 1]) >= precedence(*p)) {
                    if (topOperand < 2) {
                        printf("Not enough operand: %d, p: %c\n", topOperand, *p);
                        return -1;
                    }
                    int num2 = stackOperand[--topOperand];
                    int num1 = stackOperand[--topOperand];
                    char op = stackOperator[--topOperator];
                    int val = evalLT227(num1, op, num2);
                    //printf("Push intermedate result: %d\n", val);
                    stackOperand[topOperand++] = val;
                }
                //printf("Push operator: %c\n", *p);
                stackOperator[topOperator++] = *p;
            } else {
                printf("Invalid char: %d,%c, abort.\n", *p, *p);
                return -1;
            }
        }
        p ++;
    }
    if (numBufIdx > 0) {
        numBuf[numBufIdx++] = '\0';
        int num = atoi(numBuf);
        //printf("Push num: %d\n", num);
        stackOperand[topOperand++] = num;

        numBufIdx = 0;
    }
    while (topOperator > 0) {
        if (topOperand < 2) {
            printf("Not enough operand: %d, topOperator: %d\n", topOperand, topOperator);
            return -1;
        }
        int num2 = stackOperand[--topOperand];
        int num1 = stackOperand[--topOperand];
        char op = stackOperator[--topOperator];
        int val = evalLT227(num1, op, num2);
        //printf("Push intermedate result: %d\n", val);
        stackOperand[topOperand++] = val;
    }

    if (topOperand <= 0) {
        printf("No result\n");
        return -1;
    }
    return stackOperand[0];
}
