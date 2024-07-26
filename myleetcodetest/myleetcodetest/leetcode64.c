#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

int minPathSumHelper(int** grid, int m, int n, int i, int j, int** dp) {
    if (dp[i][j] != -1) {
        return dp[i][j];
    }
    if (i == m - 1 && j == n - 1) {
        dp[i][j] = grid[i][j];
        return dp[i][j];
    }
    int v1 = INT_MAX;
    if (j < n - 1) {
        v1 = grid[i][j] + minPathSumHelper(grid, m, n, i, j + 1, dp);
    }
    int v2 = INT_MAX;
    if (i < m - 1) {
        v2 = grid[i][j] + minPathSumHelper(grid, m, n, i + 1, j, dp);
    }
    int ret = v1 > v2 ? v2 : v1;
    printf("Visit %d,%d, ret: %d\n", i, j, ret);
    dp[i][j] = ret;
    return ret;
}

int minPathSum(int** grid, int gridSize, int* gridColSize) {
    int** dp = (int**)malloc(gridSize * sizeof(int*));
    for (int i = 0; i < gridSize; i++) {
        dp[i] = (int*)malloc(gridColSize[0] * sizeof(int));
        memset(dp[i], -1, gridColSize[0] * sizeof(int));
    }
    return minPathSumHelper(grid, gridSize, gridColSize[0], 0, 0, dp);
}
