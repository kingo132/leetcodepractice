#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* grayCode(int n, int* returnSize) {
    int sz = 1;
    for (int i = 0; i < n; i++) {
        sz *= 2;
    }
    int* retAry = (int*)malloc(sz * sizeof(int));
    *returnSize = sz;

    retAry[0] = 0;
    retAry[1] = 1;
    int len = 2;
    for (int i = 1; i < n; i++) {
        int off = (1 << i);
        for (int j = len - 1; j >= 0; j--) {
            if (2 * len - j - 1 >= sz || 2 * len - j - 1 < 0) {
                printf("Invalid %d, len: %d, i: %d, j: %d, sz: %d\n", 2 * len - j - 1, len, i, j, sz);
                break;
            }
            retAry[2 * len - j - 1] = retAry[j] | off;
        }
        len *= 2;
    }

    return retAry;
}
