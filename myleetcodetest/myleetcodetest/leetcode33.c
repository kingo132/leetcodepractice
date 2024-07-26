#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

int binSearch(int* nums, int numsSize, int l, int r, int t) {
    while (l <= r) {
        int m = (l + r) / 2;
        if (t == nums[m]) {
            return m;
        } else if (t > nums[m]) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return -1;
}

int searchLT33(int* nums, int numsSize, int target) {
    int l = 0, r = numsSize - 1;
    int mid = (l + r) / 2;
    while (l <= r) {
        mid = (l + r) / 2;
        printf("l: %d, r: %d, m: %d\n", l, r, mid);
        if (nums[mid] >= nums[0]) {
            if (mid < numsSize - 1 && nums[mid] > nums[mid + 1]) {
                break;
            }
            l = mid + 1;
        } else {
            r = mid - 1;
        }
        /*if (mid > 0 && nums[mid] > nums[mid - 1]) {
            if (mid < numsSize - 1 && nums[mid] > nums[mid + 1]) {
                break;
            } else {
                l = mid + 1;
            }
        } else {
            if (mid < numsSize - 1 && nums[mid] > nums[mid + 1]) {
                r = mid - 1;
            } else {
                //printf("Impossible, l: %d, r: %d, mid: %d\n", l, r, mid);
                //break;
                r = mid - 1;
            }
        }*/
    }
    printf("mid %d(%d)\n", mid, nums[mid]);

    if (target >= nums[0] && target <= nums[mid]) {
        return binSearch(nums, numsSize, 0, mid, target);
    }

    return binSearch(nums, numsSize, mid + 1, numsSize - 1, target);
}
