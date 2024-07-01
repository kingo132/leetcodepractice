//
//  leetcode670.c
//  myleetcodetest
//
//  Created by jason on 2024-06-30.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode670.h"

int maximumSwap(int num) {
    int ary[10];
    int digitCnt = 0;

    int t = num;
    while (t > 0) {
        ary[digitCnt++] = t % 10;
        t /= 10;
    }
    for (int i = 0; i < digitCnt; i++) {
        printf("%d ", ary[i]);
    }
    printf("\n");

    for (int i = digitCnt - 1; i > 0; i--) {
        int max = ary[i];
        int maxIdx = -1;
        for (int j = i - 1; j >= 0; j--) {
            if (ary[j] >= max) {
                max = ary[j];
                maxIdx = j;
            }
        }
        if (maxIdx != -1 && ary[maxIdx] != ary[i]) {
            printf("Swap %d <=> %d\n", maxIdx, i);
            int t = ary[maxIdx];
            ary[maxIdx] = ary[i];
            ary[i] = t;
            break;
        }
    }

    int ret = 0;
    for (int i = digitCnt - 1; i >= 0; i--) {
        ret = ret * 10 + ary[i];
    }
    return ret;
}
