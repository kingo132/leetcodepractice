#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {
    int m = matrixSize, n = matrixColSize[0];
    int direction[4][2] = {
        {0, 1},
        {1, 0},
        {0, -1},
        {-1, 0}
    };

    int** visited = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        visited[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            visited[i][j] = 0;
        }
    }

    int* retAry = (int*)malloc(m * n * sizeof(int));
    *returnSize = 0;

    int didx = 0;
    int ii = 0, jj = 0;
    while (1) {
        printf("Visit: %d, %d = %d\n", ii, jj, matrix[ii][jj]);

        retAry[(*returnSize)++] = matrix[ii][jj];
        visited[ii][jj] = 1;

        int nextii = ii + direction[didx][0];
        int nextjj = jj + direction[didx][1];
        if (nextii < 0 || nextii >= m || nextjj < 0 || nextjj >= n) {
            didx = (didx + 1) % 4;
            nextii = ii + direction[didx][0];
            nextjj = jj + direction[didx][1];
            if (nextii < 0 || nextii >= m || nextjj < 0 || nextjj >= n || visited[nextii][nextjj] != 0) {
                break;
            }
        } else if (visited[nextii][nextjj] != 0) {
            didx = (didx + 1) % 4;
            nextii = ii + direction[didx][0];
            nextjj = jj + direction[didx][1];
            if (visited[nextii][nextjj] != 0) {
                break;
            }
        }
        ii = nextii;
        jj = nextjj;
    }

    for (int i = 0; i < m; i++) {
        free(visited[i]);
    }
    free(visited);
    
    return retAry;
}