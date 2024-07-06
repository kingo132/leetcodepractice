//
//  leetcode41.c
//  myleetcodetest
//
//  Created by jason on 2024-07-04.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode41.h"

void swapLT41(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int firstMissingPositive(int* nums, int numsSize) {
    int missing = -1;
    for (int i = 0; i < numsSize; i++) {
        while (nums[i] != i + 1 && nums[i] > 0 && nums[i] <= numsSize && nums[i] != nums[nums[i] - 1]) {
            swapLT41(&nums[i], &nums[nums[i] - 1]);
        }
    }
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] != i + 1) {
            missing = i + 1;
            break;
        }
    }
    return missing == -1 ? nums[numsSize - 1] + 1 : missing;
}
