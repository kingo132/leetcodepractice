#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
    int* retAry = (int*)malloc(2 * sizeof(int));
    retAry[0] = retAry[1] = -1;
    int idx = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == target) {
            if (idx == 0) {
                retAry[0] = i;
                retAry[1] = i;
                idx++;
            } else if (idx == 1) {
                retAry[1] = i;
            }
        }
        if (idx == 1 && nums[i] > nums[retAry[1]]) {
            break;
        }
    }
    *returnSize = 2;
    return retAry;
}