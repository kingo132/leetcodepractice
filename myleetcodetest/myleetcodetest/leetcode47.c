//
//  leetcode47.c
//  myleetcodetest
//
//  Created by jason on 2024-06-17.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include "leetcode47.h"

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

 void swapLT47(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
 }

 // 两种
 // 1. 通过交换元素的方式全排列
 // 2. 通过枚举坐标的方式全排列。用一个数组记录是否访问过
 // 以上不管用哪种方法，最关键的就是重复元素怎么跳过

void permuteUniqueHelperSwap(int* nums, int numsSize, int i, int** retAry, int* returnSize, int** returnColumnSizes) {
    if (i >= numsSize - 1) {
        int* ret = (int*)malloc(numsSize * sizeof(int));
        printf("Found: ");
        for (int k = 0; k < numsSize; k++) {
            printf("%d ", nums[k]);
            ret[k] = nums[k];
        }
        printf("\n");
        retAry[*returnSize] = ret;
        (*returnColumnSizes)[*returnSize] = numsSize;
        (*returnSize) ++;
        return;
    }

    for (int j = i; j < numsSize; j++) {
        // 这个循环判断，是确保不重复的关键，并且前面需要将数组排序
        // 只要前面有两个相等，后面就不交换。直到从最左边的不相等元素开始交换
        bool shouldSwap = true;
        for (int k = i; k < j; k++) {
            if (nums[k] == nums[j]) {
                shouldSwap = false;
            }
        }
        if (! shouldSwap) {
            continue;
        }
        //printf("Swap %d <-> %d\n", i, j);
        if (j != i) swapLT47(&nums[i], &nums[j]);
        permuteUniqueHelperSwap(nums, numsSize, i + 1, retAry, returnSize, returnColumnSizes);
        if (j != i) swapLT47(&nums[i], &nums[j]);
        //printf("Back %d <-> %d\n", i, j);
    }
}

int compareLT47(const void* a, const void* b) {
    int ia = *(int*)a;
    int ib = *(int*)b;
    return ia - ib;
}

int** permuteUniqueSwap(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int maxSize = 1;
    int tmp = numsSize;
    while (tmp > 0) {
        maxSize *= tmp;
        tmp --;
    }
    printf("Maxsize: %d\n", maxSize);
    int** retAry = (int**)malloc(maxSize * sizeof(int*));
    *returnColumnSizes = (int*)malloc(maxSize * sizeof(int));
    *returnSize = 0;

    qsort(nums, numsSize, sizeof(int), compareLT47);

    permuteUniqueHelperSwap(nums, numsSize, 0, retAry, returnSize, returnColumnSizes);
    return retAry;
}

void backtrack(int* nums, int numsSize, int* temp, bool* used, int pos, int** result, int* returnSize, int** returnColumnSizes) {
    if (pos == numsSize) {
        result[*returnSize] = malloc(numsSize * sizeof(int));
        memcpy(result[*returnSize], temp, numsSize * sizeof(int));
        (*returnColumnSizes)[*returnSize] = numsSize;
        (*returnSize)++;
        return;
    }

    for (int i = 0; i < numsSize; i++) {
        if (used[i] || (i > 0 && nums[i] == nums[i - 1] && !used[i - 1])) {
            continue;
        }
        used[i] = true;
        temp[pos] = nums[i];
        backtrack(nums, numsSize, temp, used, pos + 1, result, returnSize, returnColumnSizes);
        used[i] = false;
    }
}

int** permuteUnique(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    int** result = malloc(1000 * sizeof(int*)); // 假设最大排列数为1000
    *returnColumnSizes = malloc(1000 * sizeof(int));

    int* temp = malloc(numsSize * sizeof(int));
    bool* used = calloc(numsSize, sizeof(bool));

    qsort(nums, numsSize, sizeof(int), compareLT47);

    backtrack(nums, numsSize, temp, used, 0, result, returnSize, returnColumnSizes);

    free(temp);
    free(used);

    return result;
}
