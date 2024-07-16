#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

int getIslandSize(int** grid, int m, int n, int ii, int jj, unsigned char** visited) {
    visited[ii][jj] = 1;
    int sz = 1;
    // up
    if (ii > 0 && visited[ii - 1][jj] == 0 && grid[ii - 1][jj] == 1) {
        sz += getIslandSize(grid, m, n, ii - 1, jj, visited);
    }
    // down
    if (ii < m - 1 && visited[ii + 1][jj] == 0 && grid[ii + 1][jj] == 1) {
        sz += getIslandSize(grid, m, n, ii + 1, jj, visited);
    }
    // left
    if (jj > 0 && visited[ii][jj - 1] == 0 && grid[ii][jj - 1] == 1) {
        sz += getIslandSize(grid, m, n, ii, jj - 1, visited);
    }
    // right
    if (jj < n - 1 && visited[ii][jj + 1] == 0 && grid[ii][jj + 1] == 1) {
        sz += getIslandSize(grid, m, n, ii, jj + 1, visited);
    }
    return sz;
}

int maxAreaOfIsland(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize, n = gridColSize[0];
    unsigned char** visited = (unsigned char**)malloc(m * sizeof(char*));
    for (int i = 0; i < m; i++) {
        visited[i] = (unsigned char*)malloc(n * sizeof(char));
        memset(visited[i], 0, n * sizeof(char));
    }

    int max = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (visited[i][j] == 0 && grid[i][j] == 1) {
                int sz = getIslandSize(grid, m, n, i, j, visited);
                if (sz > max) {
                    max = sz;
                }
            }
        }
    }

    return max;
}