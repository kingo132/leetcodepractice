//
//  leetcode673.c
//  myleetcodetest
//
//  Created by jason on 2024-07-11.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode673.h"

int findNumberOfLISHelper(int* nums, int numsSize, int i, int* dp, char* seqStr, int* lenCnt) {
    if (dp[i] != -1) {
        return dp[i];
    }
    //seqStr[steps] = '0' + nums[i];
    if (i >= numsSize - 1) {
        dp[i] = 1;
        lenCnt[i] = 1;
        return dp[i];
    }
    int max = 1;
    for (int j = i + 1; j < numsSize; j++) {
        if (nums[j] > nums[i]) {
            int len = 1 + findNumberOfLISHelper(nums, numsSize, j, dp, seqStr, lenCnt);
            if (len > max) {
                max = len;
                lenCnt[i] = lenCnt[j];
            } else if (len == max) {
                lenCnt[i] += lenCnt[j];
            }
        }
    }
    //seqStr[steps + 1] = '\0';
    //printf("Final: %s, steps: %d\n", seqStr, steps + 1);
    if (lenCnt[i] == 0) {
        lenCnt[i] = 1;
    }
    dp[i] = max;
    return dp[i];
}

int findNumberOfLIS(int* nums, int numsSize) {
    if (numsSize == 1) {
        return 1;
    }
    int* dp = (int*)malloc(numsSize * sizeof(int));
    memset(dp, -1, numsSize * sizeof(int));
    char* seqStr = (char*)malloc(2000 * sizeof(char));
    int maxLen = 0;
    int* lenCnt = (int*)malloc(2000 * sizeof(int));
    int maxCnt = 0;
    memset(lenCnt, 0, 2000 * sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        int v = findNumberOfLISHelper(nums, numsSize, i, dp, seqStr, lenCnt);
        if (v > maxLen) {
            maxLen = v;
            maxCnt = lenCnt[i];
        } else if (v == maxLen) {
            maxCnt += lenCnt[i];
        }
    }
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", dp[i]);
    }
    printf("\n");
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", lenCnt[i]);
    }
    printf("\n");
    //printf("\nmaxLen: %d\n", maxLen);
    free(dp);
    return maxCnt;
}

void leetcode673main(void) {
    //int ary[] = {2,2,2,2,2};
    //int ary[] = {1,2,4,3,5,4,7,2};
    //int ary[] = {1,3,5,4,7};
    int ary[] = {1,2};
    printf("%d\n", findNumberOfLIS(ary, sizeof(ary) / sizeof(int)));
}
