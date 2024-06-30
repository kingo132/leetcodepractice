//
//  leetcode42.c
//  myleetcodetest
//
//  Created by jason on 2024-06-28.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#include "leetcode42.h"

void dumpAryLT42(const char* prefix, int* ary, int n) {
    printf("%s: ", prefix);
    for (int i = 0; i < n; i++) {
        printf("%d ", ary[i]);
    }
    printf("\n");
}

int trap(int* height, int heightSize) {
    int* tmpAry = (int*)malloc(heightSize * sizeof(int));
    int maxHeight = 0;
    for (int i = 0; i < heightSize; i++) {
        tmpAry[i] = maxHeight;
        if (height[i] > maxHeight) {
            maxHeight = height[i];
        }
    }
    //dumpAryLT42("First", tmpAry, heightSize);
    maxHeight = 0;
    for (int i = heightSize - 1; i >= 0; i--) {
        int min = tmpAry[i];
        if (maxHeight < tmpAry[i]) {
            min = maxHeight;
        }
        if (min - height[i] > 0) {
            tmpAry[i] = min - height[i];
        } else {
            tmpAry[i] = 0;
        }

        if (height[i] > maxHeight) {
            maxHeight = height[i];
        }
    }
    //dumpAryLT42("Result", tmpAry, heightSize);

    int sum = 0;
    for (int i = 0; i < heightSize; i++) {
        sum += tmpAry[i];
    }
    return sum;
}
