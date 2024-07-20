#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

void swapLT31(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void reverseAry(int* arr, int l, int r) {
    while (l < r) {
        swapLT31(&arr[l], &arr[r]);
        l++;
        r--;
    }
}

void nextPermutation(int* nums, int numsSize) {
    for (int i = numsSize - 1; i > 0; i--) {
        if (nums[i] > nums[i - 1]) {
            int j = numsSize - 1;
            for (; j > i; j--) {
                if (nums[j] > nums[i - 1]) {
                    break;
                }
            }
            swapLT31(&nums[j], &nums[i - 1]);
            reverseAry(nums, i, numsSize - 1);
            return;
        }
    }
    reverseAry(nums, 0, numsSize - 1);
}