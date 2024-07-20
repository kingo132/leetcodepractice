#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

double findMaxAverage(int* nums, int numsSize, int k) {
    if (k > numsSize) {
        k = numsSize;
    }

    int sum = 0;
    for (int i = 0; i < k; i++) {
        sum += nums[i];
    }
    double avg = (double)sum / k;
    double maxAvg = avg;
    for (int i = 1; i <= numsSize - k; i++) {
        avg = (avg * k + nums[k + i - 1] - nums[i - 1]) / k;
        //printf("i: %d, k: %d, avg: %f, maxAvg: %f\n", i, k, avg, maxAvg);
        if (avg > maxAvg) {
            maxAvg = avg;
        }
    }
    return maxAvg;
}