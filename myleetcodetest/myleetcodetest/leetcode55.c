#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

bool canJump(int* nums, int numsSize) {
    int maxReach = nums[0] + 1;
    for (int i = 0; i < maxReach; i++) {
        if (nums[i] + i + 1 > maxReach) {
            maxReach = nums[i] + i + 1;
        }
        if (maxReach >= numsSize) {
            return true;
        }
    }
    return false;
}