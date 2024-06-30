//
//  leetcode1004.c
//  myleetcodetest
//
//  Created by jason on 2024-06-29.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#include "leetcode1004.h"

int longestOnesALittleBitMess(int* nums, int numsSize, int k) {
    int maxCnt = 0, curCnt = 0, kTmp = k, kStart = -1, oneCntBeforekStart = 0;
    for (int i = 0; i < numsSize; i++) {
        //printf("i: %d, maxCnt: %d, curCnt: %d, kTmp: %d, kStart: %d, one: %d\n",
        //       i, maxCnt, curCnt, kTmp, kStart, oneCntBeforekStart);
        if (nums[i] == 1) {
            curCnt ++;
            if (curCnt > maxCnt) {
                maxCnt = curCnt;
            }
        } else {
            if (kTmp > 0) {
                curCnt ++;
                kTmp --;
                if (kStart == -1) {
                    kStart = i;
                    for (int j = kStart - 1; j >= 0; j--) {
                        oneCntBeforekStart ++;
                        if (nums[j] == 0) {
                            break;
                        }
                    }
                }
                if (curCnt > maxCnt) {
                    maxCnt = curCnt;
                }
            } else {
                //if (curCnt > maxCnt) {
                //    maxCnt = curCnt;
                //}
                //curCnt = k - 1;
                //kTmp = k;

                // Check the left of kStart
                if (kStart < 0) {
                    curCnt = 0;
                    continue;
                } else if (kStart == 0) {
                    // left is like 0
                    oneCntBeforekStart = 0;
                } else { // kStart > 0
                    // check if left is 0 or 1
                    if (nums[kStart - 1] == 1) {
                        curCnt -= oneCntBeforekStart;
                        oneCntBeforekStart = 0;
                    } else {
                        oneCntBeforekStart = 0;
                    }
                }

                // Increase kStart
                kStart ++;
                while (nums[kStart] == 1 && kStart < numsSize) {
                    kStart ++; // goto the right most of a continues 1 list
                    oneCntBeforekStart ++;
                }
            }
        }
    }
    if (curCnt > maxCnt) {
        maxCnt = curCnt;
    }
    return maxCnt;
}

int longestOnes(int* nums, int numsSize, int k) {
    int l = 0, r = 0, kt = k, maxLen = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == 1) {
            r ++;
        } else {
            if (kt > 0) {
                kt--;
                r ++;
            } else {
                if (r - l > maxLen) {
                    maxLen = r - l;
                }
                if (k <= 0) {
                    l = r = i;
                } else {
                    if (nums[l] == 1) {
                        // no k left, move l to the first k
                        while (nums[l] == 1 && l < r) {
                            l++;
                        }
                        if (l < r) {
                            l ++;
                            r ++;
                        }
                    } else {
                        // move 1 k right
                        l++;
                        r++;
                    }
                }
            }
        }
    }

    if (r - l > maxLen) {
        maxLen = r - l;
    }
    return maxLen;
}
