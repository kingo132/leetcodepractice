#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

void swapLT442(int*a, int* b) {
    if (a == b) {
        return;
    }
    int t = *a;
    *a = *b;
    *b = t;
}

int* findDuplicates(int* nums, int numsSize, int* returnSize) {
    int* retAry = (int*)malloc(100000 * sizeof(int));
    *returnSize = 0;

    for (int i = 0; i < numsSize; i++) {
        while (nums[i] != i + 1) {
            if (nums[i] == nums[nums[i] - 1]) {
                int j = 0;
                for (; j < *returnSize; j++) {
                    if (retAry[j] == nums[i]) {
                        break;
                    }
                }
                if (j == *returnSize) {
                    retAry[(*returnSize)++] = nums[i];
                }
                break;
            }
            swapLT442(&nums[i], &nums[nums[i] - 1]);
        }
    }

    return retAry;
}