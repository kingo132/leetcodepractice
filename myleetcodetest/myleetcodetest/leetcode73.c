//
//  leetcode73.c
//  myleetcodetest
//
//  Created by jason on 2024-07-06.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode73.h"

void dumpMatrixLT73(int** matrix, int m, int n) {
    return;
    printf("dump matrix ->\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void setZeroes(int** matrix, int matrixSize, int* matrixColSize) {
    bool firstRowZero = false, firstColZero = false;
    for (int i = 0; i < matrixSize; i++) {
        if (matrix[i][0] == 0) {
            firstColZero = true;
            break;
        }
    }
    for (int i = 0; i < matrixColSize[0]; i++) {
        if (matrix[0][i] == 0) {
            firstRowZero = true;
            break;
        }
    }
    dumpMatrixLT73(matrix, matrixSize, matrixColSize[0]);
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixColSize[0]; j++) {
            if (matrix[i][j] == 0) {
                matrix[i][0] = 0;
                matrix[0][j] = 0;
            }
        }
    }
    dumpMatrixLT73(matrix, matrixSize, matrixColSize[0]);
    for (int i = 1; i < matrixSize; i++) {
        if (matrix[i][0] == 0) {
            for (int j = 1; j < matrixColSize[0]; j++) {
                matrix[i][j] = 0;
            }
        }
    }
    dumpMatrixLT73(matrix, matrixSize, matrixColSize[0]);
    for (int i = 1; i < matrixColSize[0]; i++) {
        if (matrix[0][i] == 0) {
            for (int j = 1; j < matrixSize; j++) {
                matrix[j][i] = 0;
            }
        }
    }
    dumpMatrixLT73(matrix, matrixSize, matrixColSize[0]);
    if (firstRowZero) {
        for (int i = 0; i < matrixColSize[0]; i++) {
            matrix[0][i] = 0;
        }
    }
    dumpMatrixLT73(matrix, matrixSize, matrixColSize[0]);
    if (firstColZero) {
        for (int i = 0; i < matrixSize; i++) {
            matrix[i][0] = 0;
        }
    }
    dumpMatrixLT73(matrix, matrixSize, matrixColSize[0]);
}
