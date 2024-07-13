//
//  leetcode268.c
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

#include "leetcode268.h"

void swapLT268(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int missingNumber(int* nums, int numsSize) {
    for (int i = 0; i < numsSize; i++) {
        while (nums[i] >= 0 && nums[i] < numsSize && nums[i] != i) {
            swapLT268(&nums[i], &nums[nums[i]]);
        }
    }
    int ret = 0;
    for (; ret < numsSize; ret++) {
        if (nums[ret] >= numsSize) {
            break;
        }
    }
    return ret;
}
