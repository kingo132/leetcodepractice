//
//  leetcode679.c
//  myleetcodetest
//
//  Created by jason on 2024-06-26.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "leetcode679.h"

double eval24(double a, char op, double b, double* ret2) {
    switch (op) {
        case '+':
            *ret2 = b + a;
            return a + b;
        case '-':
            *ret2 = b - a;
            return a - b;
        case '*':
            *ret2 = b * a;
            return a * b;
        case '/':
            *ret2 = b / a;
            return a / b;
        default:
            *ret2 = 0;
            return 0;
    }
}

bool myRound24(double v) {
    if (v >= 23.9 && v <= 24.1) {
        return true;
    }
    return false;
}

bool isDebugLT679 = false;

bool judgePoint24Old(int* cards, int cardsSize) {
    char opAry[4] = {'+', '-', '*', '/'};
    for (int c1 = 0; c1 < 4; c1++) {
        for (int c2 = 0; c2 < 4; c2++) {
            if (c2 == c1) {
                continue;
            }
            for (int c3 = 0; c3 < 4; c3++) {
                if (c3 == c1 || c3 == c2) {
                    continue;
                }
                for (int c4 = 0; c4 < 4; c4 ++) {
                    if (c4 == c3 || c4 == c2 || c4 == c1) {
                        continue;
                    }
                    for (int op1 = 0; op1 < 4; op1++) {
                        double vv1 = 0;
                        double v1 = eval24(cards[c1], opAry[op1], cards[c2], &vv1);
                        if (isDebugLT679) printf("%d %c %d, ", cards[c1], opAry[op1], cards[c2]);
                        for (int op2 = 0; op2 < 4; op2++) {
                            double vv2 = 0;
                            double v2 = eval24(v1, opAry[op2], cards[c3], &vv2);
                            if (isDebugLT679) printf("%.2f %c %d, ", v1, opAry[op2], cards[c3]);
                            for (int op3 = 0; op3 < 4; op3++) {
                                double vv3 = 0;
                                double v3 = eval24(v2, opAry[op3], cards[c4], &vv3);
                                if (isDebugLT679) printf("%.2f %c %d, = %.2f,%.2f, ", v2, opAry[op3], cards[c4], v3, vv3);
                                if (myRound24(v3) || myRound24(vv3)) {
                                    if (isDebugLT679) printf("Found\n");
                                    return true;
                                }
                                if (isDebugLT679) printf("Pass\n");
                            }
                            if (vv2 != v2) {
                                if (isDebugLT679) printf("%.2f %c %d, ", cards[c3], opAry[op2], v1);
                                for (int op3 = 0; op3 < 4; op3++) {
                                    double vv3 = 0;
                                    double v3 = eval24(vv2, opAry[op3], cards[c4], &vv3);
                                    if (isDebugLT679) printf("%.2f %c %d, = %.2f,%.2f, ", v2, opAry[op3], cards[c4], v3, vv3);
                                    if (myRound24(v3) || myRound24(vv3)) {
                                        if (isDebugLT679) printf("Found\n");
                                        return true;
                                    }
                                    if (isDebugLT679) printf("Pass\n");
                                }
                            }
                        }
                        if (vv1 != v1) {
                            if (isDebugLT679) printf("%d %c %d, ", cards[c2], opAry[op1], cards[c1]);
                            for (int op2 = 0; op2 < 4; op2++) {
                                double vv2 = 0;
                                double v2 = eval24(vv1, opAry[op2], cards[c3], &vv2);
                                if (isDebugLT679) printf("%.2f %c %d, ", vv1, opAry[op2], cards[c3]);
                                for (int op3 = 0; op3 < 4; op3++) {
                                    double vv3 = 0;
                                    double v3 = eval24(v2, opAry[op3], cards[c4], &vv3);
                                    if (isDebugLT679) printf("%.2f %c %d, = %.2f,%.2f, ", v2, opAry[op3], cards[c4], v3, vv3);
                                    if (myRound24(v3) || myRound24(vv3)) {
                                        if (isDebugLT679) printf("Found\n");
                                        return true;
                                    }
                                    if (isDebugLT679) printf("Pass\n");
                                }
                                if (vv2 != v2) {
                                    if (isDebugLT679) printf("%.2f %c %d, ", cards[c3], opAry[op2], v1);
                                    for (int op3 = 0; op3 < 4; op3++) {
                                        double vv3 = 0;
                                        double v3 = eval24(vv2, opAry[op3], cards[c4], &vv3);
                                        if (isDebugLT679) printf("%.2f %c %d, = %.2f,%.2f, ", v2, opAry[op3], cards[c4], v3, vv3);
                                        if (myRound24(v3) || myRound24(vv3)) {
                                            if (isDebugLT679) printf("Found\n");
                                            return true;
                                        }
                                        if (isDebugLT679) printf("Pass\n");
                                    }
                                }
                            }
                        }
                    }
                    for (int op1 = 0; op1 < 4; op1++) {
                        double vv1 = 0;
                        double v1 = eval24(cards[c1], opAry[op1], cards[c2], &vv1);
                        if (isDebugLT679) printf("%d %c %d, ", cards[c1], opAry[op1], cards[c2]);
                        for (int op2 = 0; op2 < 4; op2++) {
                            double vv2 = 0;
                            double v2 = eval24(cards[c3], opAry[op2], cards[c4], &vv2);
                            if (isDebugLT679) printf("%d %c %d, ", cards[c3], opAry[op2], cards[c4]);
                            for (int op3 = 0; op3 < 4; op3++) {
                                double vv3 = 0;
                                double v3 = eval24(v1, opAry[op3], v2, &vv3);
                                if (isDebugLT679) printf("%.2f %c %.2f, = %.2f,%.2f, ", v1, opAry[op3], v2, v3, vv3);
                                if (myRound24(v3) || myRound24(vv3)) {
                                    if (isDebugLT679) printf("Found\n");
                                    return true;
                                }
                                if (isDebugLT679) printf("Pass\n");
                            }
                            if (vv2 != v2) {
                                for (int op3 = 0; op3 < 4; op3++) {
                                    double vv3 = 0;
                                    double v3 = eval24(v1, opAry[op3], vv2, &vv3);
                                    if (isDebugLT679) printf("%.2f %c %.2f, = %.2f,%.2f, ", v1, opAry[op3], vv2, v3, vv3);
                                    if (myRound24(v3) || myRound24(vv3)) {
                                        if (isDebugLT679) printf("Found\n");
                                        return true;
                                    }
                                    if (isDebugLT679) printf("Pass\n");
                                }
                            }
                        }
                        if (vv1 != v1) {
                            for (int op2 = 0; op2 < 4; op2++) {
                                double vv2 = 0;
                                double v2 = eval24(cards[c3], opAry[op2], cards[c4], &vv2);
                                if (isDebugLT679) printf("%d %c %d, ", cards[c3], opAry[op2], cards[c4]);
                                for (int op3 = 0; op3 < 4; op3++) {
                                    double vv3 = 0;
                                    double v3 = eval24(vv1, opAry[op3], v2, &vv3);
                                    if (isDebugLT679) printf("%.2f %c %.2f, = %.2f,%.2f, ", vv1, opAry[op3], v2, v3, vv3);
                                    if (myRound24(v3) || myRound24(vv3)) {
                                        if (isDebugLT679) printf("Found\n");
                                        return true;
                                    }
                                    if (isDebugLT679) printf("Pass\n");
                                }
                                if (vv2 != v2) {
                                    for (int op3 = 0; op3 < 4; op3++) {
                                        double vv3 = 0;
                                        double v3 = eval24(vv1, opAry[op3], vv2, &vv3);
                                        if (isDebugLT679) printf("%.2f %c %.2f, = %.2f,%.2f, ", vv1, opAry[op3], vv2, v3, vv3);
                                        if (myRound24(v3) || myRound24(vv3)) {
                                            if (isDebugLT679) printf("Found\n");
                                            return true;
                                        }
                                        if (isDebugLT679) printf("Pass\n");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return false;
}

// 1. 如果数组比较小，直接写嵌套For循环，否则就递归，二分，或者用辅助队列
// 2. 数组枚举+运算符枚举
// TODO: 有空研究一下二分递归，可能可以解决更多的问题

double eval24New(double a, char op, double b) {
    switch (op) {
        case '+':
            if (isDebugLT679) printf("%.2f %c %.2f = %.2f\n", a, op, b, a + b);
            return a + b;
        case '-':
            if (isDebugLT679) printf("%.2f %c %.2f = %.2f\n", a, op, b, a - b);
            return a - b;
        case '*':
            if (isDebugLT679) printf("%.2f %c %.2f = %.2f\n", a, op, b, a * b);
            return a * b;
        case '/':
            if (isDebugLT679) printf("%.2f %c %.2f = %.2f\n", a, op, b, a / b);
            return a / b;
        default:
            return 0;
    }
}

bool judgePoint24Helper(double* cards, int cardsSize) {
    if (isDebugLT679) printf("judgePoint24 - %d: ", cardsSize);
    for (int i = 0; i < cardsSize; i++) {
        if (isDebugLT679) printf("%.2f ", cards[i]);
    }
    if (isDebugLT679) printf("\n");
    if (cardsSize <= 1) {
        return fabs(cards[0] - 24.0) < 0.1;
    }

    double* cardsTmp = (double*)malloc(cardsSize * sizeof(double));

    char opAry[4] = {'+', '-', '*', '/'};

    for (int i = 0; i < cardsSize; i++) {
        for (int j = 0; j < cardsSize; j++) {
            if (i == j) {
                continue;
            }

            // 保存除i和j以外的操作数
            int cardsTmpIdx = 0;
            for (int k = 0; k < cardsSize; k++) {
                if (k != i && k != j) {
                    cardsTmp[cardsTmpIdx++] = cards[k];
                }
            }

            // 计算i和j的结果
            for (int k = 0; k < 4; k++) {
                cardsTmp[cardsTmpIdx] = eval24New(cards[i], opAry[k], cards[j]);
                if (judgePoint24Helper(cardsTmp, cardsTmpIdx + 1)) {
                    free(cardsTmp);
                    return true;
                }
            }
        }
    }
    
    free(cardsTmp);
    return false;
}

bool judgePoint24(int* cards, int cardsSize) {
    double cardsDouble[4] = {cards[0], cards[1], cards[2], cards[3]};
    return judgePoint24Helper(cardsDouble, cardsSize);
}
