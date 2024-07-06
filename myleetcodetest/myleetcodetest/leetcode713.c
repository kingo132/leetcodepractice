//
//  leetcode713.c
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

#include "leetcode713.h"

// 这种方法是错误的，因为中间计算乘积的时候可能会溢出。要确保乘积的大小不超过k，这样去循环搜索。
int numSubarrayProductLessThanKERROR(int* nums, int numsSize, int k) {
    int cnt = 0;
    for (int i = 1; i <= numsSize; i++) {
        unsigned long long mul = 1;
        for (int j = 0; j < numsSize; j++) {
            if (j < i) {
                mul *= nums[j];
            } else {
                mul = mul * nums[j] / nums[j - i];
            }
            if (j >= i - 1 && mul < k) {
                //printf("Found: "); for (int m = j - i + 1; m <= j; m++) { printf("%d ", nums[m]); } printf("\n");
                cnt++;
            }
        }
    }
    return cnt;
}

void printSubArray(int* nums, int left, int right) {
    printf("All sub: ");
    for (int i = left; i < right; i++) {
        printf("[");
        for (int j = left; j <= i; j++) {
            if (j == i) {
                printf("%d", nums[j]);
            } else {
                printf("%d,", nums[j]);
            }
        }
        printf("], ");
    }
    printf("\n");
}

int numSubarrayProductLessThanKWrongAgain(int* nums, int numsSize, int k) {
    int left = 0, right = 0, mul = 1, cnt = 0;
    while (left < numsSize) {
        if (mul < k) {
            if (right < numsSize) {
                mul *= nums[right];
                if (mul >= k) {
                    cnt += right - left;
                    printf("Add %d(%d) - %d(%d): %d\n", left, nums[left], right, right >= numsSize ? -1 : nums[right], cnt);
                    printSubArray(nums, left, right);
                }
                right++;
            } else {
                cnt += right - left;
                printf("Add %d(%d) - %d(%d): %d\n", left, nums[left], right, right >= numsSize ? -1 : nums[right], cnt);
                printSubArray(nums, left, right);
                left++;
            }
        } else {
            mul /= nums[left];
            left++;
        }
    }
    return cnt;
}

// 1. 子数组应该从右往左找
// 2. 找到一个有效窗口以后，窗口的长度就是应该加上的字序列个数，这个应该死记硬背住
// ChatGPT的答案
int numSubarrayProductLessThanK(int* nums, int numsSize, int k) {
    if (k <= 1) return 0;

    int product = 1;
    int left = 0;
    int count = 0;

    for (int right = 0; right < numsSize; right++) {
        product *= nums[right];

        while (product >= k && left <= right) {
            product /= nums[left++];
        }

        count += right - left + 1;
        //printf("Add %d(%d) - %d(%d) - %d\n", left, nums[left], right, right >= numsSize ? -1 : nums[right], count);
    }

    return count;
}
