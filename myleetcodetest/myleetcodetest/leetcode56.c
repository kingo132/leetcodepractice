//
//  leetcode56.c
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

#include "leetcode56.h"

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

int compareLT56(const void* a, const void* b) {
    int ia = (*((int**)a)[0]);
    int ib = (*((int**)b)[0]);
    //printf("sort %d <-> %d\n", ia, ib);
    return ia - ib;
}

int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes) {
    qsort(intervals, intervalsSize, sizeof(int**), compareLT56);

    int** retAry = (int**)malloc(intervalsSize * sizeof(int*));
    *returnColumnSizes = (int*)malloc(intervalsSize * sizeof(int));
    *returnSize = 0;
    for (int i = 0; i < intervalsSize; i++) {
        if (*returnSize == 0 || intervals[i][0] > retAry[(*returnSize) - 1][1]) {
            retAry[*returnSize] = (int*)malloc(intervalsColSize[0] * sizeof(int));
            retAry[*returnSize][0] = intervals[i][0];
            retAry[*returnSize][1] = intervals[i][1];
            (*returnColumnSizes)[*returnSize] = intervalsColSize[0];
            (*returnSize)++;
        }
        if (*returnSize > 0 && intervals[i][0] <= retAry[(*returnSize) - 1][1] && intervals[i][1] > retAry[(*returnSize) - 1][1]) {
            retAry[(*returnSize) - 1][1] = intervals[i][1];
        }
    }

    return retAry;
}
