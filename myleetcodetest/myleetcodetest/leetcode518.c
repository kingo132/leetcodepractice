#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>

// 1. 动态规划只需要考虑当前idx就可以了，不需要考虑下一个idx的事情；
int changeHelper(int amount, int* coins, int coinsSize, int idx, int** dp, int* path, int pathIdx) {
    if (amount < 0) {
        return 0;
    }

    //printf("%d,%d\n", amount, idx);
    if (dp[amount][idx] != -1) {
        return dp[amount][idx];
    }

    int ret = 0;
    if (amount == 0) {
        //printf("Path(idx:%d,pathIdx:%d): ", idx, pathIdx);
        //for (int i = 0; i < pathIdx; i++) {
        //    printf("%d ", path[i]);
        //}
        //printf("\n");
        ret = 1;
    } else { // amount > 0
        // not choose, choose current, choose next
        ret = 0;
        if (idx < coinsSize - 1) {
            ret += changeHelper(amount, coins, coinsSize, idx + 1, dp, path, pathIdx);
        }
        //path[pathIdx] = coins[idx];
        ret += changeHelper(amount - coins[idx], coins, coinsSize, idx, dp, path, pathIdx + 1);
        //if (idx < coinsSize - 1) {
        //    path[pathIdx] = coins[idx + 1];
        //    ret += changeHelper(amount - coins[idx + 1], coins, coinsSize, idx + 1, dp, path, pathIdx + 1);
        //}
    }

    dp[amount][idx] = ret;
    //printf("amount: %d, idx: %d(%d), ret: %d\n", amount, idx, coins[idx], ret);
    return dp[amount][idx];
}

int change(int amount, int* coins, int coinsSize) {
    int** dp = (int**)malloc((amount + 1) * sizeof(int*));
    for (int i = 0; i < amount + 1; i++) {
        dp[i] = malloc(coinsSize * sizeof(int));
        memset(dp[i], -1, coinsSize * sizeof(int));
    }

    int* path = (int*)malloc(1000 * sizeof(int));

    int ret = changeHelper(amount, coins, coinsSize, 0, dp, path, 0);
    for (int i = 0; i < amount + 1; i++) {
        for (int j = 0; j < coinsSize; j++) {
            printf("%d ", dp[i][j]);
        }
        printf("\n");
    }
    return ret;
}