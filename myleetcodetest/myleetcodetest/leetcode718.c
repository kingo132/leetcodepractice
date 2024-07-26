#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

int findLengthHelper(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int wl1 = 0, wr1 = 0, wl2 = 0, wr2 = 0, max = 0;
    while (wl2 < nums2Size) {
        if (wl1 >= nums1Size) {
            printf("wl1 exceed\n");
            break;
        }
        if (wr1 >= nums1Size) {
            printf("wr1 exceed\n");
            break;
        }
        if (wr2 >= nums2Size) {
            printf("wr2 exceed\n");
            break;
        }
        if (max > nums2Size - wl2) {
            return max; // 这一步可以减少很多无用的运算
        }
        if (nums1[wr1] != nums2[wr2]) {
            // find next start position
            while (wl2 < nums2Size) {
                wl1++;
                while (wl1 < nums1Size && nums1[wl1] != nums2[wl2]) {
                    wl1++;
                }
                if (wl1 == nums1Size) {
                    wl2++;
                    wl1 = 0;
                } else {
                    break;
                }
            }

            if (wl2 == nums2Size) {
                break;
            }
                
            wr1 = wl1;
            wr2 = wl2;
            //printf("%d,%d\n", wr1, wr2);
        } else {
            wr1++;
            wr2++;
            if (wr1 - wl1 > max) {
                //printf("max %d,%d - %d,%d\n", wl1, wr1, wl2, wr2);
                max = wr1 - wl1;
            }

            if (wr1 >= nums1Size || wr2 >= nums2Size) {
                wl2++;
                wr2 = wl2;
                wl1 = wr1 = 0;
            }
        }
    }

    return max;
}

int findLength(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    //printf("A: \n");
    int max1 = findLengthHelper(nums1, nums1Size, nums2, nums2Size);
    //printf("B: \n");
    int max2 = findLengthHelper(nums2, nums2Size, nums1, nums1Size);
    return max1 > max2 ? max1 : max2;
}
