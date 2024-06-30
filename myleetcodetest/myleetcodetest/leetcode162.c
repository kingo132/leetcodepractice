//
//  leetcode162.c
//  myleetcodetest
//
//  Created by jason on 2024-06-14.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "leetcode162.h"

int findPeakElementLinear(int* nums, int numsSize) {
    int shouldCompareLeft = 1;
    for (int i = 0; i < numsSize; i++) {
        int left = INT_MIN;
        if (i > 0) {
            left = nums[i - 1];
        }
        int right = INT_MIN;
        if (i < numsSize - 1) {
            right = nums[i + 1];
        }
        if (shouldCompareLeft) {
            if (nums[i] > left || (nums[i] == left && nums[i] == INT_MIN)) {
                if (nums[i] > right || (nums[i] == right && nums[i] == INT_MIN)) {
                    return i;
                } else {
                    // i += 1, no need to compare left
                    shouldCompareLeft = 0;
                }
            } else {
                if (nums[i] > right || (nums[i] == right && nums[i] == INT_MIN)) {
                    // i += 2
                    i ++;
                    shouldCompareLeft = 1;
                } else {
                    // i += 1, no need to compare left
                    shouldCompareLeft = 0;
                }
            }
        } else {
            if (nums[i] > right || (nums[i] == right && nums[i] == INT_MIN)) {
                return i;
            } else {
                // i += 1, no need to compare left
                shouldCompareLeft = 0;
            }
        }
    }

    return -1;
}

int findPeakElement(int* nums, int numsSize) {
    if (numsSize == 1) {
        return 0;
    }
    int left = 0, right = numsSize - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        printf("Check %d,%d /2-> %d\n", left, right, mid);

        int leftVal = INT_MIN;
        if (mid > 0) {
            leftVal = nums[mid - 1];
        }
        int rightVal = INT_MIN;
        if (mid < numsSize - 1) {
            rightVal = nums[mid + 1];
        }
        
        printf("Left %d, right %d\n", leftVal, rightVal);
        if (((nums[mid] > leftVal) || (nums[mid] == leftVal && nums[mid] == INT_MIN)) &&
            ((nums[mid] > rightVal) || (nums[mid] == rightVal && nums[mid] == INT_MIN))) {
            return mid;
        }

        if (rightVal > leftVal) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
        //printf("New %d,%d\n", left, right);
    }

    return -1;
}
