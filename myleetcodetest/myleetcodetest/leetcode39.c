//
//  leetcode39.c
//  myleetcodetest
//
//  Created by jason on 2024-06-12.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "leetcode39.h"

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

int compare(const void* a, const void* b) {
    return *((const int*)a) - *((const int*)b);
}

void combinationSumHelper(int* candidates, int candidatesSize, int target, int candIdx, int freq, int* path, int** retAry, int* returnSize, int** returnColumnSizes) {
    if (candIdx < candidatesSize - 1 && target > 0) {
        int maxFreq = target / candidates[candIdx + 1];
        for (int i = 0; i <= maxFreq; i++) {
            path[candIdx + 1] = (candidates[candIdx + 1] << 16) + i;
            combinationSumHelper(candidates, candidatesSize, target - candidates[candIdx + 1] * i, candIdx + 1, i, path, retAry, returnSize, returnColumnSizes);
        }
    }

    //printf("Visit %d x %d <-> %d, path: ", candidates[candIdx], freq, target);
    //for (int i = 0; i <= candIdx; i++) {
    //    printf("(%d x %d) ", path[i] >> 16, path[i] & 0xffff);
    //}
    //printf("\n");

    if (target == 0) {
        int* tmpAry = (int*)malloc(10000 * sizeof(int));
        int idx = 0;
        for (int i = 0; i <= candIdx; i++) {
            int c = path[i] >> 16;
            int f = path[i] & 0xffff;
            for (int j = 0; j < f; j++) {
                tmpAry[idx++] = c;
            }
        }
        printf("Add a %d, size: %d\n", idx, *returnSize);
        retAry[*returnSize] = tmpAry;
        (*returnColumnSizes)[*returnSize] = idx;
        (*returnSize) ++;
    }
}

int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes) {
    int** retAry = (int**)malloc(1000 * sizeof(int*));
    *returnColumnSizes = (int*)malloc(1000 * sizeof(int*));
    *returnSize = 0;

    int* path = (int*)malloc(10000 * sizeof(int));

    //qsort(candidates, candidatesSize, sizeof(int), compare);

    int maxFreq = target / candidates[0];
    for (int i = 0; i <= maxFreq; i++) {
        path[0] = (candidates[0] << 16) + i;
        combinationSumHelper(candidates, candidatesSize, target - candidates[0] * i, 0, i, path, retAry, returnSize, returnColumnSizes);
    }

    free(path);
    return retAry;
}
