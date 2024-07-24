#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

// 枚举用交换元素；子集用每次增加元素；
int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int** retAry = (int**)malloc(10000 * sizeof(int*));
    *returnColumnSizes = (int*)malloc(10000 * sizeof(int));
    for (int i = 0; i < 10000; i++) {
        retAry[i] = (int*)malloc(numsSize * sizeof(int));
        (*returnColumnSizes)[i] = 0;
    }
    *returnSize = 0;

    (*returnColumnSizes)[(*returnSize)++] = 0;

    for (int i = 0; i < numsSize; i++) {
        int sz = *returnSize;
        for (int j = 0; j < sz; j++) {
            for (int k = 0; k < (*returnColumnSizes)[j]; k++) {
                retAry[sz + j][k] = retAry[j][k];
            }
            (*returnColumnSizes)[sz + j] = (*returnColumnSizes)[j];
            retAry[sz + j][(*returnColumnSizes)[sz + j]] = nums[i];
            (*returnColumnSizes)[sz + j]++;
        }
        *returnSize += sz;
    }
    return retAry;
}