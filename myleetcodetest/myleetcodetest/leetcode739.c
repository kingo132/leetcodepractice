//
//  leetcode739.c
//  myleetcodetest
//
//  Created by jason on 2024-06-19.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include "leetcode739.h"

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* dailyTemperaturesBruteForce(int* temperatures, int temperaturesSize, int* returnSize) {
    int* retAry = (int*)malloc(temperaturesSize * sizeof(int));
    *returnSize = temperaturesSize;

    for (int i = 0; i < temperaturesSize; i++) {
        int days = 0;
        for (int j = i + 1; j < temperaturesSize; j++) {
            if (temperatures[j] > temperatures[i]) {
                days = j - i;
                break;
            }
        }
        retAry[i] = days;
    }

    return retAry;
}

void dumpAryLT739(const char* prefix, int* ary, int n) {
    printf("%s: ", prefix);
    for (int i = 0; i < n; i++) {
        printf("%d ", ary[i]);
    }
    printf("\n");
}

int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize) {
    int* retAry = (int*)malloc(temperaturesSize * sizeof(int));
    *returnSize = temperaturesSize;

    int auxAry[71];
    for (int i = 0; i < 71; i++) {
        auxAry[i] = -1;
    }

    int maxVal = temperatures[temperaturesSize - 1];
    int minVal = temperatures[temperaturesSize - 1];
    retAry[temperaturesSize - 1] = 0;
    auxAry[temperatures[temperaturesSize - 1] - 30] = temperaturesSize - 1;
    for (int i = temperaturesSize - 2; i >= 0; i--) {
        auxAry[temperatures[i] - 30] = i;
        //printf("%d: %d, min %d(%d), max %d(%d)\n", i, temperatures[i], minVal, auxAry[minVal-30], maxVal, auxAry[maxVal-30]);
        //dumpAry("auxAry", auxAry, 70);
        if (temperatures[i] >= maxVal) {
            retAry[i] = 0;
            maxVal = temperatures[i];
        } else {
            if (temperatures[i] < minVal) {
                minVal = temperatures[i];
            }
            int minIdx = INT_MAX;
            for (int j = minVal; j <= maxVal; j++) {
                if (j > temperatures[i] && auxAry[j - 30] != -1 && auxAry[j - 30] < minIdx) {
                    minIdx = auxAry[j - 30];
                }
            }
            //printf("Get minIdx: %d\n", minIdx);
            if (minIdx != INT_MAX) {
                retAry[i] = minIdx - i;
            } else {
                retAry[i] = 0;
            }
        }
    }

    return retAry;
}
