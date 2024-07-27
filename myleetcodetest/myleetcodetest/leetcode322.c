#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

int coinChangeHelper(int* coins, int n, int ii, int m, int step, int** dp) {
    if (ii >= n || m < 0) {
        return INT_MAX;
    }

    //printf("%d,%d\n", ii, m);
    if (dp[ii][m] != -1 && step >= dp[ii][m]) {
        return dp[ii][m];
    }

    int minStep = INT_MAX;
    if (m == 0) {
        //printf("step: %d\n", step);
        minStep = step;
    } else {
        for (int i = ii; i < n; i++) {
            if (coins[i] > m) {
                continue;
            } else {
                int v1 = coinChangeHelper(coins, n, ii, m - coins[i], step + 1, dp);
                int v2 = coinChangeHelper(coins, n, ii + 1, m - coins[i], step + 1, dp);
                int min = v1 > v2 ? v2 : v1;
                if (min < minStep) {
                    minStep = min;
                }
                if (dp[i][m] == -1 || min < dp[i][m]) {
                    dp[i][m] = min;
                }
            }
        }
    }

    if (dp[ii][m] == -1 || minStep < dp[ii][m]) {
        dp[ii][m] = minStep;
    }
    printf("ii: %d, m: %d, minStep: %d\n", ii, m, minStep);
    return dp[ii][m];
}

int coinChangeOld(int* coins, int coinsSize, int amount) {
    int** dp = (int**)malloc(coinsSize * sizeof(int*));
    for (int i = 0; i < coinsSize; i++) {
        dp[i] = (int*)malloc((amount + 1) * sizeof(int));
        memset(dp[i], -1, (amount + 1) * sizeof(int));
    }

    int ret = coinChangeHelper(coins, coinsSize, 0, amount, 0, dp);
    for (int i = 0; i < coinsSize; i++) {
        free(dp[i]);
    }
    free(dp);
    return ret == INT_MAX ? -1 : ret;
}

// 1. 尽可能简化dp数组的大小，这里每次从1到n遍历，就不需要再保存这个角标这一维度了
// 2. DP算法优化的终极状态，就是只累积计算DP数组
int coinHelperOld(int* coins, int n, int m, int* dp) {
    if (m < 0) return -1;
    if (m == 0) return 0;

    if (dp[m] != -1) return dp[m];

    int min = INT_MAX;
    for (int i = 0; i < n; i++) {
        int v = coinHelperOld(coins, n, m - coins[i], dp);
        if (v >= 0 && v < min) {
            min = v + 1;
        }
    }

    dp[m] = (min == INT_MAX) ? -1 : min;
    return dp[m];
}

int compareLT322ASC(void* a, void* b) {
    int ia = *(int*)a;
    int ib = *(int*)b;
    return ia - ib;
}

int compareLT322DESC(void* a, void* b) {
    int ia = *(int*)a;
    int ib = *(int*)b;
    return ib - ia;
}

int coinChange(int* coins, int coinsSize, int amount) {
    qsort(coins, coinsSize, sizeof(int), compareLT322ASC);

    long* dp = (long*)malloc((amount + 1) * sizeof(long));
    for (int i = 0; i < amount + 1; i++) {
        dp[i] = INT_MAX;
    }
    //memset(dp, -1, (amount + 1) * sizeof(int));

    //int ret = coinHelperOld(coins, coinsSize, amount, dp);

    dp[0] = 0;

    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < coinsSize; j++) {
            if (i - coins[j] >= 0) {
                // dp[i] = MIN(dp[i], dp[i - coins[j]] + 1);
                dp[i] = dp[i] > dp[i - coins[j]] + 1 ? dp[i - coins[j]] + 1 : dp[i];
            }
        }
    }

    for (int i = 0; i < amount + 1; i++) {
        printf("%ld ", dp[i]);
    }
    printf("\n");

    int ret = (dp[amount] == INT_MAX) ? -1 : dp[amount];

    /*
    for (int i = 0; i <= amount; i++) {
        dp[i] = amount + 1; // Initialize with a value larger than the maximum possible amount
    }
    dp[0] = 0;

    // Iteratively fill the DP array
    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < coinsSize; j++) {
            if (coins[j] <= i) {
                if (dp[i - coins[j]] != amount + 1) { // Only update if the subproblem was solvable
                    dp[i] = dp[i] < (dp[i - coins[j]] + 1) ? dp[i] : (dp[i - coins[j]] + 1);
                }
            } else {
                break;  // Since coins array is sorted, no need to check further
            }
        }
    }

    int ret = (dp[amount] == amount + 1) ? -1 : dp[amount];
    */

    free(dp);
    return ret;
}