//
//  leetcode329.c
//  myleetcodetest
//
//  Created by jason on 2024-07-11.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode329.h"

typedef struct {
    unsigned char x;
    unsigned char y;
    unsigned short steps;
    unsigned char* visited;
    //int maxSteps;
} QueNode;

int longestIncreasingPathAtXY(int** matrix, int m, int n, int x, int y) {
    int maxQueSize = 925;
    QueNode* que = (QueNode*)malloc(maxQueSize * sizeof(QueNode));
    int front = 0, tail = 0, queSize = 0;
    for (int i = 0; i < maxQueSize; i++) {
        que[i].visited = (unsigned char*)malloc(m * n * sizeof(unsigned char));
        memset(que[i].visited, 0, m * n * sizeof(unsigned char));
        que[i].steps = 0;
        //que[i].maxSteps = INT_MIN;
    }

    que[tail].x = x;
    que[tail].y = y;
    que[tail].steps = 1;
    tail++;
    queSize++;

    int totalMaxStep = INT_MIN;
    while (queSize > 0) {
        int xx = que[front].x;
        int yy = que[front].y;
        int steps = que[front].steps;
        unsigned char* visited = que[front].visited;
        front = (front + 1) % maxQueSize;
        queSize --;

        visited[xx * n + yy] = 1;

        //printf("Check %d,%d\n", xx, yy);
        
        if (steps > totalMaxStep) {
            totalMaxStep = steps;
        }

        if (xx < m - 1 && visited[(xx + 1) * n + yy] == 0 && matrix[xx + 1][yy] > matrix[xx][yy]) {
            que[tail].x = xx + 1;
            que[tail].y = yy;
            que[tail].steps = steps + 1;
            memcpy(que[tail].visited, visited, m * n * sizeof(unsigned char));
            tail = (tail + 1) % maxQueSize;
            queSize++;
            if (queSize >= maxQueSize) {
                printf("Que full.\n");
                return -1;
            }
        }
        if (xx > 0 && visited[(xx - 1) * n + yy] == 0 && matrix[xx - 1][yy] > matrix[xx][yy]) {
            que[tail].x = xx - 1;
            que[tail].y = yy;
            que[tail].steps = steps + 1;
            memcpy(que[tail].visited, visited, m * n * sizeof(unsigned char));
            tail = (tail + 1) % maxQueSize;
            queSize++;
            if (queSize >= maxQueSize) {
                printf("Que full.\n");
                return -1;
            }
        }
        if (yy < n - 1 && visited[xx * n + yy + 1] == 0 && matrix[xx][yy + 1] > matrix[xx][yy]) {
            que[tail].x = xx;
            que[tail].y = yy + 1;
            que[tail].steps = steps + 1;
            memcpy(que[tail].visited, visited, m * n * sizeof(unsigned char));
            tail = (tail + 1) % maxQueSize;
            queSize++;
            if (queSize >= maxQueSize) {
                printf("Que full.\n");
                return -1;
            }
        }
        if (yy > 0 && visited[xx * n + yy - 1] == 0 && matrix[xx][yy - 1] > matrix[xx][yy]) {
            que[tail].x = xx;
            que[tail].y = yy - 1;
            que[tail].steps = steps + 1;
            memcpy(que[tail].visited, visited, m * n * sizeof(unsigned char));
            tail = (tail + 1) % maxQueSize;
            queSize++;
            if (queSize >= maxQueSize) {
                printf("Que full.\n");
                return -1;
            }
        }
    }

    // free
    for (int i = 0; i < maxQueSize; i++) {
        free(que[i].visited);
    }
    free(que);
    return totalMaxStep;
}

void longestIncreasingPathAtXY2(int** matrix, int m, int n, int x, int y, unsigned char* visited, int steps, int* maxSteps) {
    visited[x * n + y] = 1;
    if (steps > *maxSteps) {
        *maxSteps = steps;
    }
    if (x < m - 1 && visited[(x + 1) * n + y] == 0 && matrix[x + 1][y] > matrix[x][y]) {
        longestIncreasingPathAtXY2(matrix, m, n, x + 1, y, visited, steps + 1, maxSteps);
    }
    if (x > 0 && visited[(x - 1) * n + y] == 0 && matrix[x - 1][y] > matrix[x][y]) {
        longestIncreasingPathAtXY2(matrix, m, n, x - 1, y, visited, steps + 1, maxSteps);
    }
    if (y < n - 1 && visited[x * n + y + 1] == 0 && matrix[x][y + 1] > matrix[x][y]) {
        longestIncreasingPathAtXY2(matrix, m, n, x, y + 1, visited, steps + 1, maxSteps);
    }
    if (y > 0 && visited[x * n + y - 1] == 0 && matrix[x][y - 1] > matrix[x][y]) {
        longestIncreasingPathAtXY2(matrix, m, n, x, y - 1, visited, steps + 1, maxSteps);
    }
    visited[x * n + y] = 0;
}

void longestIncreasingPathAtXY3(int** matrix, int m, int n, int x, int y, unsigned char* visited, int steps, int* maxSteps) {
    visited[x * n + y] = 1;
    //printf("Test %d,%d, step: %d\n", x, y, steps);
    if (steps > *maxSteps) {
        *maxSteps = steps;
    }
    int direction = -1; // 1 up, 2 down, 3 left, 4 right
    int min = INT_MAX;
    if (x < m - 1 && visited[(x + 1) * n + y] == 0 && matrix[x + 1][y] > matrix[x][y] && matrix[x + 1][y] - matrix[x][y] < min) {
        min = matrix[x + 1][y] - matrix[x][y];
        direction = 2;
    }
    if (x > 0 && visited[(x - 1) * n + y] == 0 && matrix[x - 1][y] > matrix[x][y] && matrix[x - 1][y] - matrix[x][y] < min) {
        min = matrix[x - 1][y] - matrix[x][y];
        direction = 1;
    }
    if (y < n - 1 && visited[x * n + y + 1] == 0 && matrix[x][y + 1] > matrix[x][y] && matrix[x][y + 1] - matrix[x][y] < min) {
        min = matrix[x][y + 1] - matrix[x][y];
        direction = 4;
    }
    if (y > 0 && visited[x * n + y - 1] == 0 && matrix[x][y - 1] > matrix[x][y] && matrix[x][y - 1] - matrix[x][y] < min) {
        min = matrix[x][y - 1] - matrix[x][y];
        direction = 3;
    }
    if (min > 0 ) {
        if (direction == 2) {
            longestIncreasingPathAtXY3(matrix, m, n, x + 1, y, visited, steps + 1, maxSteps);
        } else if (direction == 1) {
            longestIncreasingPathAtXY3(matrix, m, n, x - 1, y, visited, steps + 1, maxSteps);
        } else if (direction == 4) {
            longestIncreasingPathAtXY3(matrix, m, n, x, y + 1, visited, steps + 1, maxSteps);
        } else if (direction == 3) {
            longestIncreasingPathAtXY3(matrix, m, n, x, y - 1, visited, steps + 1, maxSteps);
        }
    }
    visited[x * n + y] = 0;
}

void longestIncreasingPathAtXY4(int** matrix, int m, int n, int x, int y, int steps, int* maxSteps) {
    printf("Test %d,%d, step: %d\n", x, y, steps);
    if (steps > *maxSteps) {
        *maxSteps = steps;
    }
    if (x < m - 1 && matrix[x + 1][y] > matrix[x][y]) {
        longestIncreasingPathAtXY4(matrix, m, n, x + 1, y, steps + 1, maxSteps);
    }
    if (x > 0 && matrix[x - 1][y] > matrix[x][y]) {
        longestIncreasingPathAtXY4(matrix, m, n, x - 1, y, steps + 1, maxSteps);
    }
    if (y < n - 1 && matrix[x][y + 1] > matrix[x][y]) {
        longestIncreasingPathAtXY4(matrix, m, n, x, y + 1, steps + 1, maxSteps);
    }
    if (y > 0 && matrix[x][y - 1] > matrix[x][y]) {
        longestIncreasingPathAtXY4(matrix, m, n, x, y - 1, steps + 1, maxSteps);
    }
}

int longestIncreasingPathAtXY5(int** matrix, int m, int n, int x, int y, int* dp) {
    if (dp[x * n + y] != -1) {
        return dp[x * n + y];
    }
    int maxSteps = 1;
    if (x < m - 1 && matrix[x + 1][y] > matrix[x][y]) {
        int steps = 1 + longestIncreasingPathAtXY5(matrix, m, n, x + 1, y, dp);
        if (steps > maxSteps) {
            maxSteps = steps;
        }
    }
    if (x > 0 && matrix[x - 1][y] > matrix[x][y]) {
        int steps = 1 + longestIncreasingPathAtXY5(matrix, m, n, x - 1, y, dp);
        if (steps > maxSteps) {
            maxSteps = steps;
        }
    }
    if (y < n - 1 && matrix[x][y + 1] > matrix[x][y]) {
        int steps = 1 + longestIncreasingPathAtXY5(matrix, m, n, x, y + 1, dp);
        if (steps > maxSteps) {
            maxSteps = steps;
        }
    }
    if (y > 0 && matrix[x][y - 1] > matrix[x][y]) {
        int steps = 1 + longestIncreasingPathAtXY5(matrix, m, n, x, y - 1, dp);
        if (steps > maxSteps) {
            maxSteps = steps;
        }
    }
    //printf("Test %d,%d, step: %d\n", x, y, maxSteps);
    dp[x * n + y] = maxSteps;
    return maxSteps;
}

int longestIncreasingPath(int** matrix, int matrixSize, int* matrixColSize) {
    int m = matrixSize, n = matrixColSize[0];
    //unsigned char* visited = (unsigned char*)malloc(m * n * sizeof(unsigned char));
    //memset(visited, 0, m * n * sizeof(unsigned char));
    int* dp = (unsigned char*)malloc(m * n * sizeof(int));
    memset(dp, -1, m * n * sizeof(int));
    int max = INT_MIN;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            //printf("Start from %d,%d\n", i, j);
            //longestIncreasingPathAtXY2(matrix, m, n, i, j, visited, 1, &v);
            int v = longestIncreasingPathAtXY5(matrix, m, n, i, j, dp);
            if (v > max) {
                max = v;
            }
        }
    }
    return max;
}

int dfsLT329(int** matrix, int** memo, int m, int n, int i, int j) {
    if (memo[i][j] != -1) {
        return memo[i][j];
    }

    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    int maxLength = 1;

    for (int d = 0; d < 4; d++) {
        int x = i + directions[d][0];
        int y = j + directions[d][1];

        if (x >= 0 && x < m && y >= 0 && y < n && matrix[x][y] > matrix[i][j]) {
            int length = 1 + dfsLT329(matrix, memo, m, n, x, y);
            if (length > maxLength) {
                maxLength = length;
            }
        }
    }

    memo[i][j] = maxLength;
    return maxLength;
}

int longestIncreasingPathChatGPT(int** matrix, int matrixSize, int* matrixColSize) {
    if (matrixSize == 0 || *matrixColSize == 0) {
        return 0;
    }

    int m = matrixSize;
    int n = *matrixColSize;

    int** memo = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        memo[i] = (int*)malloc(n * sizeof(int));
        memset(memo[i], -1, n * sizeof(int));
    }

    int maxLength = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int length = dfsLT329(matrix, memo, m, n, i, j);
            if (length > maxLength) {
                maxLength = length;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        free(memo[i]);
    }
    free(memo);

    return maxLength;
}
