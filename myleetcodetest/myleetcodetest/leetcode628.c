//
//  leetcode628.c
//  myleetcodetest
//
//  Created by jason on 2024-06-20.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include "leetcode628.h"

int compareLT628(const void* a, const void* b) {
    int ia = *(int *)a;
    int ib = *(int *)b;
    return ib - ia;
}

int maximumProduct(int* nums, int numsSize) {
    qsort(nums, numsSize, sizeof(int), compareLT628);

    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    /*int max = INT_MIN;
    for (int i = 0; i < numsSize; i++) {
        for (int j= i + 1; j < numsSize; j++) {
            for (int k = j + 1; k < numsSize; k++) {
                int v = nums[i] * nums[j] * nums[k];
                if (v > max) {
                    max = v;
                }
            }
        }
    }*/
    if (nums[numsSize - 1] < 0 && nums[numsSize - 2] < 0 && nums[0] > 0 && nums[numsSize - 1] * nums[numsSize - 2] > nums[1] * nums[2]) {
        return nums[0] * nums[numsSize - 1] * nums[numsSize - 2];
    }

    return nums[0] * nums[1] * nums[2];
}
