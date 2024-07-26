//
//  leetcode1314.c
//  myleetcodetest
//
//  Created by jason on 2024-07-07.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode1314.h"

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

typedef struct {
    int hori;
    int vert;
} ARYNODE;

void dumpMatLT1314(const char* prefix, ARYNODE** mat, int m, int n) {
    printf("%s\n", prefix);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("(%d,%d) ", mat[i][j].hori, mat[i][j].vert);
        }
        printf("\n");
    }
}

int** matrixBlockSum(int** mat, int matSize, int* matColSize, int k, int* returnSize, int** returnColumnSizes) {
    int** retMat = (int**)malloc(matSize * matColSize[0] * sizeof(int*));
    *returnSize = matSize;
    *returnColumnSizes = (int*)malloc(matSize * sizeof(int));
    ARYNODE** tmpAry = (ARYNODE**)malloc(matSize * matColSize[0] * sizeof(ARYNODE*));
    for (int i = 0; i < matSize; i++) {
        retMat[i] = (int*)malloc(matColSize[0] * sizeof(int));
        tmpAry[i] = (ARYNODE*)malloc(matColSize[0] * sizeof(ARYNODE));
        for (int j = 0; j < matColSize[0]; j++) {
            retMat[i][j] = 0;
            tmpAry[i][j].hori = 0;
            tmpAry[i][j].vert = 0;
        }
        (*returnColumnSizes)[i] = matColSize[0];
    }

    for (int i = 0; i < matSize; i++) {
        for (int j = 0; j < matColSize[0]; j++) {
            //printf("%d,%d\n", i, j);
            if (j == 0) {
                int sum = 0;
                for (int m = j; m <= j + k; m++) {
                    if (m >= 0 && m < matColSize[0]) {
                        sum += mat[i][m];
                    }
                }
                tmpAry[i][j].hori = sum;
            } else {
                tmpAry[i][j].hori = tmpAry[i][j - 1].hori;
                if (j + k < matColSize[0]) {
                    tmpAry[i][j].hori += mat[i][j + k];
                }
                if (j - k - 1 >= 0) {
                    tmpAry[i][j].hori -= mat[i][j - k - 1];
                }
            }
            /*
            if (i = 0) {
                int sum = 0;
                for (int m = i; m <= i + k; m++) {
                    if (m >= 0 && m < matSize) {
                        sum += mat[m][j];
                    }
                }
                tmpAry[i][j].vert = sum;
            } else {
                if (i + k < matSize) {
                    tmpAry[i][j].vert += mat[i + k][j];
                }
                if (i - k - 1 >= 0) {
                    tmpAry[i][j].vert -= mat[i - k - 1][j];
                }
            }
            */
        }
    }

    //dumpMat("Dump: ", tmpAry, matSize, matColSize[0]);

    for (int i = 0; i < matSize; i++) {
        for (int j = 0; j < matColSize[0]; j++) {
            if (i == 0) {
                int sum = 0;
                for (int m = 0; m <= k; m++) {
                    sum += tmpAry[m][j].hori;
                }
                retMat[i][j] = sum;
            } else {
                retMat[i][j] = retMat[i - 1][j];
                if (i + k < matSize) {
                    retMat[i][j] += tmpAry[i + k][j].hori;
                }
                if (i - k - 1 >= 0) {
                    retMat[i][j] -= tmpAry[i - k - 1][j].hori;
                }
            }
        }
    }
    for (int i = 0; i < matSize; i++) {
        free(tmpAry[i]);
    }
    free(tmpAry);
    return retMat;
}
