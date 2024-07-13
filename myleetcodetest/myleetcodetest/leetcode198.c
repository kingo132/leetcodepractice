//
//  leetcode198.c
//  myleetcodetest
//
//  Created by jason on 2024-06-11.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "leetcode198.h"

int robGreedy(int* nums, int numsSize) {
    int* isRobbed = (int*)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        isRobbed[i] = 0;
    }

    int sum = 0;
    while (true) {
        int max = -1, maxI = -1;
        for (int i = 0; i < numsSize; i++) {
            int isLeftRobbed = 1;
            if (i == 0 || isRobbed[i - 1] == 0) {
                isLeftRobbed = 0;
            }
            int isRightRobbed = 1;
            if (i == numsSize - 1 || isRobbed[i + 1] == 0) {
                isRightRobbed = 0;
            }
            if (isRobbed[i] == 0 && isLeftRobbed == 0 && isRightRobbed == 0 && nums[i] > max) {
                max = nums[i];
                maxI = i;
            }
        }
        printf("Found max %d,%d\n", maxI, max);
        if (maxI == -1) {
            // No one left
            break;
        }
        sum += max;
        isRobbed[maxI] = 1;
    }

    free(isRobbed);
    return sum;
}

int robHelperLT198(int* nums, int numsSize, int idx) {
    int max = 0;
    if (idx < numsSize) {
        int sum = nums[idx] + robHelperLT198(nums, numsSize, idx + 2);
        if (sum > max) {
            max = sum;
        }
        if (idx + 1 < numsSize) {
            sum = nums[idx + 1] + robHelperLT198(nums, numsSize, idx + 3);
            if (sum > max) {
                max = sum;
            }
        }
    }
        
    return max;
}

int robRecursive(int* nums, int numsSize) {
    return robHelperLT198(nums, numsSize, 0);
}

int robA(int* nums, int numsSize) {
    int* stack = (int*)malloc(numsSize * sizeof(int));
    int top = 0;

    stack[top++] = 1;
    stack[top++] = 0;
    int sum = 0, max = 0;
    while (top > 0) {
        int idx = stack[--top];
        sum += nums[idx];
        printf("Visit %d:%d, sum: %d\n", idx, nums[idx], sum);
        if (idx + 3 < numsSize) {
            stack[top++] = idx + 3;
        }
        if (idx + 2 < numsSize) {
            stack[top++] = idx + 2;
        }
        sum -= nums[idx];
    }

    return max;
}

int robNonRecursive(int* nums, int numsSize) {
    if (numsSize == 0) return 0;
    if (numsSize == 1) return nums[0];

    int* dp = (int*)malloc((numsSize + 1) * sizeof(int));
    dp[0] = 0;
    dp[1] = nums[0];

    for (int i = 1; i < numsSize; i++) {
        dp[i + 1] = (dp[i] > (dp[i - 1] + nums[i])) ? dp[i] : (dp[i - 1] + nums[i]);
    }

    int result = dp[numsSize];
    free(dp);
    return result;
}

int robMyMy(int* nums, int numsSize) {
    return robNonRecursive(nums, numsSize);
}

int robLT198(int* nums, int numsSize) {
    int* dp = (int*)malloc((numsSize + 1) * sizeof(int));
    
    dp[0] = 0;
    dp[1] = nums[0];

    for (int i = 1; i < numsSize; i++) {
        dp[i + 1] = dp[i] > dp[i - 1] + nums[i] ? dp[i] : dp[i - 1] + nums[i];
    }

    int ret = dp[numsSize];
    free(dp);
    return ret;
}
