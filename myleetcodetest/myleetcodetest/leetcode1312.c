//
//  leetcode1312.c
//  myleetcodetest
//
//  Created by jason on 2024-07-09.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode1312.h"

int minInsertionsHelper(char* s, char* p, char* se, char* pe, int** dp) {
    //printf("Process %c <-> %c, ", *p, *pe);
    int i = p - s;
    int j = se - pe;
    //printf("%d,%d\n", i, j);
    if (dp[i][j] != -1) {
        return dp[i][j];
    }
    while (p <= pe) {
        if (*p == *pe) {
            p++;
            pe--;
        } else {
            int len1 = minInsertionsHelper(s, p + 1, se, pe, dp);
            int len2 = minInsertionsHelper(s, p, se, pe - 1, dp);
            dp[p + 1 - s][se - pe] = len1;
            dp[p - s][se - pe + 1] = len2;
            dp[i][j] = 1 + (len1 > len2 ? len2 : len1);
            //printf("return: %d\n", dp[i][j]);
            return dp[i][j];
        }
    }
    dp[i][j] = 0;
    //printf("return: %d\n", dp[i][j]);
    return dp[i][j];
}

int minInsertions(char* s) {
    int sLen = 0;
    char* p = s;
    while (*p) {
        sLen++;
        p++;
    }

    int** dp = (int**)malloc(sLen * sizeof(int*));
    for (int i = 0; i < sLen; i++) {
        dp[i] = (int*)malloc(sLen * sizeof(int));
        for (int j = 0; j < sLen; j++) {
            dp[i][j] = -1;
        }
    }

    return minInsertionsHelper(s, s, s + sLen - 1, s + sLen - 1, dp);
}
