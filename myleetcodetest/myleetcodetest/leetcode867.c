//
//  leetcode867.c
//  myleetcodetest
//
//  Created by jason on 2024-07-02.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode867.h"

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** transpose(int** matrix, int matrixSize, int* matrixColSize, int* returnSize, int** returnColumnSizes) {
    *returnSize = matrixColSize[0];
    int** retMat = (int**)malloc((*returnSize) * sizeof(int*));
    *returnColumnSizes = (int*)malloc((*returnSize) * sizeof(int));
    for (int i = 0; i < (*returnSize); i++) {
        (*returnColumnSizes)[i] = matrixSize;
        retMat[i] = (int*)malloc((*returnColumnSizes)[i] * sizeof(int));
        for (int j = 0; j < (*returnColumnSizes)[i]; j++) {
            retMat[i][j] = matrix[j][i];
        }
    }
    return retMat;
}
