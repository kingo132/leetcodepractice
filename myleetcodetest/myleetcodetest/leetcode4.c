//
//  leetcode4.c
//  myleetcodetest
//
//  Created by jason on 2024-06-10.
//
#include <stdlib.h>
#include "leetcode4.h"

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int medianPos = (nums1Size + nums2Size) / 2;
    printf("Get medianPos: %d\n", medianPos);
    int* mergedAry = (int*)malloc((medianPos + 1) * sizeof(int));
    int nums1Idx = 0, nums2Idx = 0;
    for (int i = 0; i <= medianPos; i++) {
        if (nums1Idx < nums1Size) {
            if (nums2Idx < nums2Size) {
                // Compare 1 & 2
                if (nums1[nums1Idx] < nums2[nums2Idx]) {
                    printf("%d comp %d from nums1 %d\n", i, nums1[nums1Idx], nums1Idx);
                    mergedAry[i] = nums1[nums1Idx];
                    nums1Idx++;
                } else {
                    printf("%d comp %d from nums2 %d\n", i, nums2[nums2Idx], nums2Idx);
                    mergedAry[i] = nums2[nums2Idx];
                    nums2Idx++;
                }
            } else {
                // From 1
                printf("%d get %d from nums1 %d\n", i, nums1[nums1Idx], nums1Idx);
                mergedAry[i] = nums1[nums1Idx];
                nums1Idx++;
            }
        } else {
            if (nums2Idx < nums2Size) {
                // From 2
                printf("%d get %d from nums2 %d\n", i, nums2[nums2Idx], nums2Idx);
                mergedAry[i] = nums2[nums2Idx];
                nums2Idx++;
            } else {
                // Empty retrival
                printf("Empty retrival: %d,%d,%d\n", i, nums1Idx, nums2Idx);
                break;
            }
        }
    }

    double ret = 0.0;
    if ((nums1Size + nums2Size) % 2 != 0) { // odd
        ret = mergedAry[medianPos];
        printf("Calculate from %d: %f\n", medianPos, ret);
    } else { // even
        ret = (double)(mergedAry[medianPos] + mergedAry[medianPos - 1]) / 2.0;
        printf("Calculate from (%d+%d)/2: %f\n", mergedAry[medianPos], mergedAry[medianPos - 1], ret);
    }
    free(mergedAry);
    return ret;
}

int leetcode4Main(void) {
    
    return 0;
}
