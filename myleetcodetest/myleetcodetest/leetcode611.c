//
//  leetcode611.c
//  myleetcodetest
//
//  Created by jason on 2024-06-29.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#include "leetcode611.h"

bool isValidTriangle(int a, int b, int c) {
    if (a + b > c && a + c > b && b + c > a) {
        return true;
    }
    return false;
}

int compareLT611(const void* a, const void* b) {
    int ia = *(int*)a;
    int ib = *(int*)b;
    return ia - ib;
}

int triangleNumber(int* nums, int numsSize) {
    qsort(nums, numsSize, sizeof(int), compareLT611);
    //for (int i = 0; i < numsSize; i++) {
    //    printf("%d ", nums[i]);
    //}
    //printf("\n");

    int cnt = 0;
    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            //printf("i: %d, j: %d, %d,%d\n", i, j, nums[i], nums[j]);
            int s = nums[i] + nums[j];
            int l = j + 1;
            int r = numsSize - 1;
            int maxIdx = -1;
            while (l <= r) {
                //printf("%d,%d,%d\n", s, l, r);
                int mid = (l + r) / 2;
                if (mid == l || mid == r) {
                    if (s > nums[r]) {
                        maxIdx = r;
                    } else if (s > nums[l]) {
                        maxIdx = l;
                    } else if (s == nums[l]) {
                        for (int k = l - 1; k > j; k--) {
                            if (nums[k] < s) {
                                maxIdx = k;
                                break;
                            }
                        }
                    }
                    break;
                }
                if (nums[mid] > s) {
                    r = mid;
                } else {
                    l = mid;
                }
            }
            if (maxIdx != -1) {
                //printf("Found %d,%d -> %d\n", nums[i], nums[j], nums[maxIdx]);
                cnt += maxIdx - j;
            }
            /*for (int k = j + 1; k < numsSize; k++) {
                if (nums[i] + nums[j] > nums[k]) {
                    if (nums[i] + nums[k] > nums[j]) {
                        if (nums[j] + nums[k] > nums[i]) {
                            cnt ++;
                        }
                    }
                } else {
                    break;
                }
            }*/
        }
    }
    return cnt;
}
