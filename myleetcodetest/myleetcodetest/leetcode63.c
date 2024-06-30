//
//  leetcode63.c
//  myleetcodetest
//
//  Created by jason on 2024-06-22.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include "leetcode63.h"

#define PACK(a,b) (((a)<<16)+b)
#define UNPACK(v,a,b) {(a) = (v)>>16; (b) = (v)&0xff;}
int uniquePathsWithObstaclesOld(int** obstacleGrid, int obstacleGridSize, int* obstacleGridColSize) {
    int maxQueSize = 1000000;
    unsigned short* que = (unsigned short*)malloc(maxQueSize * sizeof(unsigned short));
    int front = 0, tail = 0, queSize = 0;
    unsigned char* visited = (unsigned char*)malloc(obstacleGridSize * obstacleGridColSize[0] * sizeof(unsigned char));
    for (int i = 0; i < obstacleGridSize * obstacleGridColSize[0]; i++) {
        visited[i] = 0;
    }

    int ways = 0;

    que[tail++] = PACK(0, 0);
    queSize ++;
    while (queSize > 0) {
        int m = 0, n = 0;
        int v = que[front];
        UNPACK(v, m, n)
        front = (front + 1) % maxQueSize;

        if (m == obstacleGridSize - 1 && n == obstacleGridColSize[0] - 1) {
            //
        }

        visited[m * obstacleGridColSize[0] + n] = 1;

        // up
        if (m > 0 && visited[(m - 1) * obstacleGridColSize[0] + n] == 0) {

        }
        // down
        // left
        // right

    }

    return 0;
}

int uniquePathsWithObstaclesHelper(int** grid, int m, int n, int i, int j) {
    if (grid[i][j] == 1) {
        return 0;
    }
    if (i == m - 1 && j == n - 1) {
        return 1;
    }
    //printf("%d,%d\n", i, j);
    int sum = 0;
    // down
    if (i < m - 1 && grid[i + 1][j] == 0) {
        sum += uniquePathsWithObstaclesHelper(grid, m, n, i + 1, j);
    }
    // right
    if (j < n - 1 && grid[i][j + 1] == 0) {
        sum += uniquePathsWithObstaclesHelper(grid, m, n, i, j + 1);
    }
    return sum;
}

int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridSize, int* obstacleGridColSize) {
    if (obstacleGrid[0][0] == 1 || obstacleGrid[obstacleGridSize - 1][obstacleGridColSize[0] - 1] == 1) {
        return 0;
    }
    //return uniquePathsWithObstaclesHelper(obstacleGrid, obstacleGridSize, obstacleGridColSize[0], 0, 0);
    int m = obstacleGridSize, n = obstacleGridColSize[0];
    int* dp = (int*)malloc(m * n * sizeof(int));
    for (int i = 0; i < m * n; i++) {
        dp[i] = 0;
    }

    dp[0] = 1;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (obstacleGrid[i][j] == 1) {
                dp[i * n + j] = 0;
            } else {
                if (i > 0) { // up
                    dp[i * n + j] += dp[(i - 1) * n + j];
                }
                if (j > 0) { // left
                    dp[i * n + j] += dp[i * n + j - 1];
                }
            }
        }
    }

    return dp[m * n - 1];
}
