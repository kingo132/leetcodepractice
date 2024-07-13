//
//  leetcode154.c
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

#include "leetcode154.h"

int findMinMy(int* nums, int numsSize) {
    if (nums[numsSize - 1] <= nums[0]) {
        // rotated
        int l = 0, r = numsSize - 1, lastMid = -1;
        while (l < r) {
            int mid = (l + r) / 2;
            //printf("Try %d,%d,%d\n", l, mid, r);
            if (lastMid != -1 && lastMid == mid) {
                break;
            }
            lastMid = mid;
            if (nums[mid] > nums[r]) {
                l = mid;
            } else if (nums[mid] < nums[r]) {
                r = mid;
            } else {
                for (int i = mid; i >= l; i--) {
                    if (nums[i] < nums[r]) {
                        //printf("a\n");
                        r = i;
                        continue;
                    } else if (nums[i] > nums[r]) {
                        //printf("b\n");
                        l = i;
                        continue;
                    }
                }
                for (int i = mid; i < r; i++) {
                    if (nums[i] < nums[r]) {
                        //printf("c\n");
                        r = i;
                        continue;
                    } else if (nums[i] > nums[r]) {
                        //printf("d\n");
                        l = i;
                        continue;
                    }
                }
                //printf("Cannot happen: %d,%d,%d.\n", l, mid, r);
            }
        }
        return nums[r];
    } else {
        return nums[0];
    }
}

int findMinChatGPT(int* nums, int numsSize) {
    int left = 0, right = numsSize - 1;

    while (left < right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] < nums[right]) {
            right = mid;
        } else if (nums[mid] > nums[right]) {
            left = mid + 1;
        } else {
            // nums[mid] == nums[right], reduce the search space
            right--;
        }
    }
    return nums[left];
}
