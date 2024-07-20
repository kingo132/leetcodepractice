#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* nextGreaterElementsBruteForce(int* nums, int numsSize, int* returnSize) {
    int* retAry = (int*)malloc(numsSize * sizeof(int));
    memset(retAry, 0, numsSize * sizeof(int));
    *returnSize = numsSize;

    for (int i = numsSize - 1; i >= 0; i--) {
        int prev = i - 1;
        if (prev < 0) {
            prev = numsSize - 1;
        }
        if (nums[i] > nums[prev]) {
            retAry[prev] = nums[i]; 
        } else {
            int foundVal = -1;
            for (int j = 0; j < numsSize - 1; j++) {
                int idx = (j + i) % numsSize;
                if (nums[idx] > nums[prev]) {
                    foundVal = nums[idx];
                    break;
                }
            }
            retAry[prev] = foundVal;
        }
    }

    return retAry;
}

int* nextGreaterElements(int* nums, int numsSize, int* returnSize) {
    int* retAry = (int*)malloc(numsSize * sizeof(int));
    memset(retAry, -1, numsSize * sizeof(int));
    *returnSize = numsSize;

    int* stack = (int*)malloc(numsSize * 2 * sizeof(int));
    int top = 0;

    for (int i = 2 * (numsSize - 1); i >= 0; i--) {
        while (top > 0 && stack[top - 1] <= nums[i % numsSize]) {
            top--;
        }
        if (top > 0) {
            retAry[i % numsSize] = stack[top - 1];
        }
        stack[top++] = nums[i % numsSize];
    }

    free(stack);
    return retAry;
}