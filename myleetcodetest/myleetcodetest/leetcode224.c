//
//  leetcode224.c
//  myleetcodetest
//
//  Created by jason on 2024-07-12.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode224.h"

// 这类问题最好背下来
int evaltwo(int a, char op, int b) {
    int ret = -1;
    switch (op) {
        case '+':
            ret = a + b;
            break;
        case '-':
            ret = a - b;
            break;
    }
    printf("eval %d %c %d = %d\n", a, op, b, ret);
    return ret;
}

void dump2stacks(int* stack1, int top1, char* stack2, int top2) {
    printf("Dump stack:\n");
    for (int i = 0; i < top1; i++) {
        printf("%d ", stack1[i]);
    }
    printf("\n");
    for (int i = 0; i < top2; i++) {
        printf("%c ", stack2[i]);
    }
    printf("\n");
}

int calculateLT224(char* s) {
    int sLen = 0;
    char* p = s;
    while (*p) {
        sLen++;
        p++;
    }

    int* stack1 = (int*)malloc(sLen * 2 * sizeof(int)); // operand
    char* stack2 = (char*)malloc(sLen * 2 * sizeof(char)); // operator
    int top1 = 0, top2 = 0;

    p = s;
    int num = -1;
    int prevType = 0; // 1 number, 2 operand & other
    while (*p) {
        //dump2stacks(stack1, top1, stack2, top2);
        if ((*p < '0' || *p > '9') && *p != ' ' && num >= 0) {
            stack1[top1++] = num;
            num = -1;
            prevType = 1;
        }

        if (*p == ' ') {
        } else if (*p == '+' || *p == '-') {
            while (top2 > 0 && (stack2[top2 - 1] == '+' || stack2[top2 - 1] == '-')) {
                if (top1 < 2) {
                    printf("Not enough oprand: %d\n", top1);
                }
                int v = evaltwo(stack1[top1 - 2], stack2[top2 - 1], stack1[top1 - 1]);
                top2--;
                top1 -= 2;
                stack1[top1++] = v;
            }
            if (*p == '-' && prevType != 1) {
                stack1[top1++] = 0;
            }
            stack2[top2++] = *p;
            prevType = 2;
        } else if (*p == '(') {
            stack2[top2++] = *p;
            prevType = 2;
        } else if (*p == ')') {
            while (stack2[top2 - 1] != '(') {
                if (top1 < 2) {
                    printf("Not enough oprand: %d\n", top1);
                }
                int v = evaltwo(stack1[top1 - 2], stack2[top2 - 1], stack1[top1 - 1]);
                top2--;
                top1 -= 2;
                stack1[top1++] = v;
            }
            top2--;
        } else if (*p >= '0' && *p <= '9') {
            if (num > 0) {
                num = num * 10 + (*p - '0');
            } else {
                num = *p - '0';
            }
        } else {
            printf("Invalid char: %c\n", *p);
        }
        p++;
    }
    if (num >= 0) {
        stack1[top1++] = num;
        num = -1;
    }
    //dump2stacks(stack1, top1, stack2, top2);
    while (top2 > 0 && (stack2[top2 - 1] == '+' || stack2[top2 - 1] == '-')) {
        if (top1 < 2) {
            printf("Not enough oprand: %d\n", top1);
        }
        int v = evaltwo(stack1[top1 - 2], stack2[top2 - 1], stack1[top1 - 1]);
        top2--;
        top1 -= 2;
        stack1[top1++] = v;
    }

    return stack1[0];
}
