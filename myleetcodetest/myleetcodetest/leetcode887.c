#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

// 1. 动态规划算法一定要先从大到小问题的思路去思考；2. 动态规划一定要减少每次迭代的参数个数；3. 动态规划要存储每个迭代的参数不能遗漏。
// 简化迭代的过程，减少迭代的参数，是动态规划优化的重点
int stoneGameHelper(int* piles, int pilesSize, int l, int r, int* dp) {
    if (l >= r) {
        return piles[l];
    }
    if (dp[l * pilesSize + r] != -1) {
        return dp[l * pilesSize + r];
    }
    int scoreLeft = piles[l] - stoneGameHelper(piles, pilesSize, l + 1, r, dp);
    int scoreRight = piles[r] - stoneGameHelper(piles, pilesSize, l, r - 1, dp);
    //printf("l: %d, r: %d, Left: %d, Right: %d\n", l, r, scoreLeft, scoreRight);
    dp[l * pilesSize + r] = scoreLeft > scoreRight ? scoreLeft : scoreRight;
    return dp[l * pilesSize + r];
}

bool stoneGame(int* piles, int pilesSize) {
    int* dp = (int*)malloc(pilesSize * pilesSize * sizeof(int));
    memset(dp, -1, pilesSize * pilesSize * sizeof(int));
    int ret = stoneGameHelper(piles, pilesSize, 0, pilesSize - 1, dp);
    printf("%d\n", ret);
    return ret > 0;
}
