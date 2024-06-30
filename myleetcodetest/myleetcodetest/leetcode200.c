//
//  leetcode200.c
//  myleetcodetest
//
//  Created by jason on 2024-06-20.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include "leetcode200.h"

void visitIsland(char** grid, int m, int n, int i, int j, unsigned char* visitMatrix, int* que, int maxQueSize) {
    int front = 0, tail = 0, queSize = 0;
    que[tail++] = (i << 16) + j;
    visitMatrix[i * n + j] = 1;
    queSize ++;
    while (queSize > 0) {
        int v = que[front];
        int ii = v >> 16;
        int jj = v & 0xffff;
        front = (front + 1) % maxQueSize;
        queSize --;
        //printf("%d,%d->1\n", ii, jj);

        if (ii > 0 && visitMatrix[(ii - 1) * n + jj] == 0 && grid[ii - 1][jj] == '1') {
            //printf("Push up %d,%d\n", ii - 1, jj);
            que[tail] = ((ii - 1) << 16) + jj;
            tail = (tail + 1) % maxQueSize;
            queSize ++;
            visitMatrix[(ii - 1) * n + jj] = 1;
        }
        if (ii < m - 1 && visitMatrix[(ii + 1) * n + jj] == 0 && grid[ii + 1][jj] == '1') {
            //printf("Push down %d,%d\n", ii + 1, jj);
            que[tail] = ((ii + 1) << 16) + jj;
            tail = (tail + 1) % maxQueSize;
            queSize ++;
            visitMatrix[(ii + 1) * n + jj] = 1;
        }
        if (jj > 0 && visitMatrix[ii * n + jj - 1] == 0 && grid[ii][jj - 1] == '1') {
            //printf("Push left %d,%d\n", ii, jj - 1);
            que[tail] = (ii << 16) + jj - 1;
            tail = (tail + 1) % maxQueSize;
            queSize ++;
            visitMatrix[ii * n + jj - 1] = 1;
        }
        if (jj < n - 1 && visitMatrix[ii * n + jj + 1] == 0 && grid[ii][jj + 1] == '1') {
            //printf("Push right %d,%d\n", ii, jj + 1);
            que[tail] = (ii << 16) + jj + 1;
            tail = (tail + 1) % maxQueSize;
            queSize ++;
            visitMatrix[ii * n + jj + 1] = 1;
        }
    }
}

int numIslands(char** grid, int gridSize, int* gridColSize) {
    int m = gridSize, n = gridColSize[0];
    //printf("m: %d, n: %d\n", m, n);
    unsigned char* visitMatrix = (unsigned char*)malloc(m * n * sizeof(char));
    for (int i = 0; i < m * n; i++) {
        visitMatrix[i] = 0;
    }
    int* que = (int*)malloc(m * n * 10 * sizeof(int));

    int islandCnt = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (visitMatrix[i * n + j] == 0 && grid[i][j] == '1') {
                visitIsland(grid, m, n, i, j, visitMatrix, que, m * n);
                //printf("%d,%d\n", i, j);
                islandCnt ++;
            }
        }
    }

    return islandCnt;
}
