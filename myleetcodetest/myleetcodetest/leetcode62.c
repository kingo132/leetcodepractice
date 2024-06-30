//
//  leetcode62.c
//  myleetcodetest
//
//  Created by jason on 2024-06-27.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "leetcode62.h"

#define IDX(i,j,n) ((i) * (n) + (j))

int uniquePaths(int m, int n) {
    int* dp = (int*)malloc(m * n * sizeof(int));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 || j == 0) {
                dp[IDX(i,j,n)] = 1;
            } else {
                dp[IDX(i,j,n)] = dp[IDX(i - 1,j,n)] + dp[IDX(i,j - 1,n)];
            }
        }
    }
    int ret = dp[IDX(m - 1,n - 1,n)];
    free(dp);
    return ret;
}
