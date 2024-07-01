//
//  leetcode164.c
//  myleetcodetest
//
//  Created by jason on 2024-06-30.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#include "leetcode164.h"

void dumpAryLT164(const char* prefix, int* ary, int n) {
    printf("%s: ", prefix);
    for (int i = 0; i < n; i++) {
        printf("%d ", ary[i]);
    }
    printf("\n");
}

void countSortLT164(int* ary, int* tmpAry, int n, int b) {
    int cntAry[10];
    memset(cntAry, 0, sizeof(cntAry));

    //dumpAryLT164("Before sort", ary, n);
    for (int i = 0; i < n; i++) {
        cntAry[(ary[i] / b) % 10] ++;
    }
    //dumpAryLT164("Cnt ary1", cntAry, 10);
    for (int i = 1; i < 10; i++) {
        cntAry[i] += cntAry[i - 1];
    }
    //dumpAryLT164("Cnt ary2", cntAry, 10);
    // 注意：这里要从n-1到0，反序添加。这样才能保证整个数组有序。
    for (int i = n - 1; i >= 0; i--) {
        tmpAry[cntAry[(ary[i] / b) % 10] - 1] = ary[i];
        cntAry[(ary[i] / b) % 10] --;
    }
    //dumpAryLT164("Tmp ary", tmpAry, n);
    for (int i = 0; i < n; i++) {
        ary[i] = tmpAry[i];
    }
    //dumpAryLT164("After sort", ary, n);
}

int maximumGap(int* nums, int numsSize) {
    if (numsSize <= 1) {
        return 0;
    }
    
    int min = INT_MAX, max = INT_MIN;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] < min) {
            min = nums[i];
        }
        if (nums[i] > max) {
            max = nums[i];
        }
    }

    int* tmpAry = (int*)malloc(numsSize * sizeof(int));

    for (int base = 1; max / base > 0; base *= 10) {
        countSortLT164(nums, tmpAry, numsSize, base);
    }

    int maxgap = 0;
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] - nums[i - 1] > maxgap) {
            maxgap = nums[i] - nums[i - 1];
        }
    }

    free(tmpAry);
    return maxgap;
}
