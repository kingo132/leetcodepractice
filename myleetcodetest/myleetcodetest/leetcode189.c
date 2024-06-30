//
//  leetcode189.c
//  myleetcodetest
//
//  Created by jason on 2024-06-14.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "leetcode189.h"

void dumpAryLT189(int* nums, int numsSize) {
    printf("Dump: ");
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

void reverse(int* nums, int numsSize, int start, int end) {
    while (start < end) {
        int t = nums[start];
        nums[start] = nums[end];
        nums[end] = t;

        start ++;
        end --;
    }
}

void rotate(int* nums, int numsSize, int k) {
    if (numsSize < k) {
        k %= numsSize;
    }
    if (k <= 0) {
        return;
    }
    reverse(nums, numsSize, 0, numsSize - 1);
    reverse(nums, numsSize, 0, k - 1);
    reverse(nums, numsSize, k, numsSize - 1);
}
