#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

int maxSubArray(int* nums, int numsSize) {
    int maxSoFar = INT_MIN, maxEnding = 0;
    for (int i = 0; i < numsSize; i++) {
        maxEnding += nums[i];

        if (maxEnding > maxSoFar) {
            maxSoFar = maxEnding;
        }

        if (maxEnding < 0) {
            maxEnding = 0;
        }
    }
    return maxSoFar;
}