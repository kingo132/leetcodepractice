#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

int robHelper(int* nums, int ii, int n, int* dp, int* robed) {
    if (ii >= n) {
        return 0;
    }

    if (dp[robed[0] * n + ii] != -1) {
        return dp[robed[0] * n + ii];
    }

    //printf("Robed: ");
    //for (int i = 0; i < n; i++) {
    //    printf("%d ", robed[i]);
    //}
    //printf("\n");

    int max = 0;
    for (int i = ii; i < n; i++) {
        int left = i - 1;
        if (left < 0) {
            left = n - 1;
        }
        int right = i + 1;
        if (right >= n) {
            right = 0;
        }
        if (robed[left] == 0 && robed[right] == 0) {
            robed[i] = 1;
            int v = nums[i] + robHelper(nums, i + 1, n, dp, robed);
            //printf("i: %d, v: %d\n", i, v);
            if (v > max) {
                max = v;
            }
            robed[i] = 0;
        }
    }
    
    //printf("ii: %d, max: %d\n", ii, max);
    dp[robed[0] * n + ii] = max;
    return max;
}

int rob(int* nums, int numsSize) {
    int* dp = (int*)malloc(numsSize * 2 * sizeof(int));
    memset(dp, -1, numsSize * 2 * sizeof(int));
    int* robed = (int*)malloc(numsSize * sizeof(int));
    memset(robed, 0, numsSize * sizeof(int));
    int ret = robHelper(nums, 0, numsSize, dp, robed);
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", dp[i]);
    }
    printf("\n");
    free(dp);
    free(robed);
    return ret;
}