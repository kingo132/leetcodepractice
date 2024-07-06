//
//  leetcode386.c
//  myleetcodetest
//
//  Created by jason on 2024-07-03.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode386.h"

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int compareLexi(int a, int b) {
    char as[11], bs[11];

    int ai = 0, bi = 0;
    int aa = a, bb = b;
    while (a > 0) {
        as[ai++] = a % 10;
        a /= 10;
    }
    while (b > 0) {
        bs[bi++] = b % 10;
        b /= 10;
    }

    //printf("Compare %d <-> %d, ai: %d, bi: %d\n", aa, bb, ai, bi);

    ai--;
    bi--;
    while (1) {
        //printf("-> comp %d <-> %d\n", as[ai], bs[bi]);
        if (as[ai] != bs[bi]) {
            return as[ai] - bs[bi];
        }
        ai--;
        bi--;
        if (ai == bi) {
            if (ai < 0) {
                //printf("equal\n");
                return 0; // equal
            }
        } else {
            if (ai < 0) {
                //printf("-1\n");
                return -1; // a is smaller
            }
            if (bi < 0) {
                //printf("1\n");
                return 1; // b is smaller
            }
        }
    }
}

void swapLT386(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int* lexicalOrderInsertionSort(int n, int* returnSize) {
    int* retAry = (int*)malloc(n * sizeof(int));
    *returnSize = 0;

    for (int i = 1; i <= n; i++) {
        retAry[*returnSize] = i;

        for (int j = *returnSize; j > 0; j--) {
            if (compareLexi(retAry[j], retAry[j - 1]) < 0) {
                swapLT386(&retAry[j], &retAry[j - 1]);
            } else {
                break;
            }
        }

        (*returnSize)++;
    }

    return retAry;
}

void lexicalOrderHelper(int ii, int n, int* retAry, int* returnSize) {
    for (int i = 0; i < 10; i++) {
        int v = ii * 10 + i;
        if (v == 0) {
            continue;
        } else if (v > n) {
            break;
        }
        retAry[(*returnSize)++] = v;
        //printf("%d\n", v);
        lexicalOrderHelper(v, n, retAry, returnSize);
    }
}

int* lexicalOrder(int n, int* returnSize) {
    int* retAry = (int*)malloc(n * sizeof(int));
    *returnSize = 0;

    lexicalOrderHelper(0, n, retAry, returnSize);

    return retAry;
}
