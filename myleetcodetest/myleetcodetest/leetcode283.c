#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

void moveZeroes(int* nums, int numsSize) {
    int slow = 0, fast = 0;
    while (fast < numsSize) {
        if (nums[fast] == 0) {
            fast++;
        } else {
            if (slow != fast) {
                nums[slow] = nums[fast];
            }
            slow++;
            fast++;
        }
    }
    for (int i = slow; i < numsSize; i++) {
        nums[i] = 0;
    }
}