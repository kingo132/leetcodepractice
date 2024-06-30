//
//  leetcode556.c
//  myleetcodetest
//
//  Created by jason on 2024-06-28.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#include "leetcode556.h"

void swapLT556(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void reverseLT556(int* ary, int s, int e) {
    while (s < e) {
        swapLT556(&ary[s], &ary[e]);
        s++;
        e--;
    }
}

void dumpAryLT556(int* ary, int n) {
    printf("Dump: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", ary[i]);
    }
    printf("\n");
}

int nextGreaterElement(int n) {
    int intAry[32];
    for (int i = 0; i < 32; i++) {
        intAry[i] = 0;
    }
    int tmp = n;
    int digitCnt = 0;
    while (tmp > 0) {
        intAry[digitCnt++] = tmp % 10;
        tmp /= 10;
    }

    //dumpAry(intAry, digitCnt);

    int found = 0;
    for (int i = 1; i < digitCnt; i++) {
        for (int j = 0; j < i; j++) {
            if (intAry[j] > intAry[i]) {
                //dumpAry(intAry, digitCnt);
                swapLT556(&intAry[j], &intAry[i]);
                //dumpAry(intAry, digitCnt);
                reverseLT556(intAry, 0, i - 1);
                //dumpAry(intAry, digitCnt);
                found = 1;
                break;
            }
        }
        if (found) {
            break;
        }
    }
    
    //dumpAry(intAry, digitCnt);
    
    if (found == 0) {
        return -1;
    }

    long rst = 0;
    long base = 1;
    for (int i = 0; i < digitCnt; i++) {
        rst += intAry[i] * base;
        base *= 10;
    }
    if (rst > INT_MAX) {
        return -1;
    }

    return rst;
}
