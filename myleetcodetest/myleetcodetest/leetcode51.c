//
//  leetcode51.c
//  myleetcodetest
//
//  Created by jason on 2024-07-02.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "leetcode51.h"

#define GMAXSOLU 1000
#define ISDBG false

bool sloveNQueensHelper(char* ary, int n, char*** retAry, int ii, int jj,
                        int* returnSize, int* returnColumnSizes, int queens) {
    // Horizontal
    for (int i = 0; i < n; i++) {
        if (ary[ii * n + i] == 'Q') {
            if (ISDBG) printf("%d: Horizontal fail %d,%d\n", queens, ii, i);
            return false;
        }
    }

    // Vertical
    for (int i = 0; i < n; i++) {
        if (ary[i * n + jj] == 'Q') {
            if (ISDBG) printf("%d: Vertical fail %d,%d\n", queens, i, jj);
            return false;
        }
    }

    // Diagonals
    for (int i = 1; i < n; i++) {
        // Right diagonal (从左上到右下)
        if (ii + i < n && jj + i < n && ary[(ii + i) * n + (jj + i)] == 'Q') {
            if (ISDBG) printf("%d: Right diag fail %d,%d\n", queens, ii + i, jj + i);
            return false;
        }
        if (ii - i >= 0 && jj - i >= 0 && ary[(ii - i) * n + (jj - i)] == 'Q') {
            if (ISDBG) printf("%d: Right diag fail %d,%d\n", queens, ii - i, jj - i);
            return false;
        }

        // Left diagonal (从右上到左下)
        if (ii + i < n && jj - i >= 0 && ary[(ii + i) * n + (jj - i)] == 'Q') {
            if (ISDBG) printf("%d: Left diag fail %d,%d\n", queens, ii + i, jj - i);
            return false;
        }
        if (ii - i >= 0 && jj + i < n && ary[(ii - i) * n + (jj + i)] == 'Q') {
            if (ISDBG) printf("%d: Left diag fail %d,%d\n", queens, ii - i, jj + i);
            return false;
        }
    }

    bool ret = false;

    ary[ii * n + jj] = 'Q';
    if (ISDBG) printf("%d: Put Q on %d,%d\n", queens, ii, jj);
    if (queens <= 1) {
        // output
        retAry[*returnSize] = (char**)malloc(n * sizeof(char*));
        //printf("%d: malloc %p\n", *returnSize, retAry[*returnSize]);
        for (int i = 0; i < n; i++) {
            retAry[*returnSize][i] = (char*)malloc((n + 1) * sizeof(char));
            //printf("%d,%d: malloc %p\n", *returnSize, i, retAry[*returnSize][i]);
            for (int j = 0; j < n; j++) {
                retAry[*returnSize][i][j] = ary[i * n + j];
            }
            retAry[*returnSize][i][n] = '\0';
        }
        returnColumnSizes[*returnSize] = n;

        if (ISDBG) printf("Found:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (ISDBG) printf("%c ", retAry[*returnSize][i][j]);
            }
            if (ISDBG) printf("\n");
        }
        if (ISDBG) printf("\n");

        (*returnSize)++;
        ret = true;
    } else {
        for (int nextii = ii + 1; nextii < n; nextii++) {
            for (int nextjj = 0; nextjj < n; nextjj++) {
                if (ary[nextii * n + nextjj] == '.' &&
                    sloveNQueensHelper(ary, n, retAry, nextii, nextjj, returnSize, returnColumnSizes, queens - 1)) {
                    ret = true;
                }
            }
        }
    }

    ary[ii * n + jj] = '.';
    if (ISDBG) printf("%d: Unput Q on %d,%d\n", queens, ii, jj);

    return ret;
}

char*** solveNQueens(int n, int* returnSize, int** returnColumnSizes) {
    char*** retAry = (char***)malloc(GMAXSOLU * sizeof(char**));
    *returnSize = 0;
    *returnColumnSizes = (int*)malloc(GMAXSOLU * sizeof(int));

    char* tmpAry = (char*)malloc(n * n * sizeof(char));
    for (int i = 0; i < n * n; i++) {
        tmpAry[i] = '.';
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sloveNQueensHelper(tmpAry, n, retAry, i, j, returnSize, *returnColumnSizes, n);
        }
    }

    free(tmpAry);
    return retAry;
}
