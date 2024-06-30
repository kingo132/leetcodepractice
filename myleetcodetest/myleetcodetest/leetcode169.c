//
//  leetcode169.c
//  myleetcodetest
//
//  Created by jason on 2024-06-17.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "leetcode169.h"

// 博耶-摩尔多数投票算法（英语：Boyer–Moore majority vote algorithm）,中文常作多数投票算法、摩尔投票算法等
int majorityElement(int* nums, int numsSize) {
    int cand = -1;
    int count = 0;
    for (int i = 0; i < numsSize; i++) {
        if (count == 0) {
            cand = i;
        }
        if (nums[i] == nums[cand]) {
            count ++;
        } else {
            count --;
        }
    }
    return nums[cand];
}
