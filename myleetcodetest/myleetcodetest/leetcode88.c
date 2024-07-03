//
//  leetcode88.c
//  myleetcodetest
//
//  Created by jason on 2024-07-02.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode88.h"

void swapLT88(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void mergeLT88(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
    for (int i = 0; i < n; i++) {
        nums1[m + i] = nums2[i];
        for (int j = m + i; j >= 1; j--) {
            if (nums1[j] < nums1[j - 1]) {
                swapLT88(&nums1[j], &nums1[j - 1]);
            }
        }
    }
}
