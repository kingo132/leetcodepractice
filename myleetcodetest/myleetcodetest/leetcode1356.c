//
//  leetcode1356.c
//  myleetcodetest
//
//  Created by jason on 2024-06-13.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "leetcode1356.h"

int bitCnt(int n) {
    int cnt = 0;
    int origN = n;
    while (n > 0) {
        if (n & 1) {
            cnt++;
        }
        n >>= 1;
    }
    //printf("%d has %d bits\n", origN, cnt);
    return cnt;
}

int compareBit(const void* a, const void* b) {
    int ca = bitCnt(*((int*)a));
    int cb = bitCnt(*((int*)b));
    if (ca == cb) {
        return *((int*)a) - *((int*)b);
    }
    return ca - cb;
}

int compareQS(int a, int b) {
    int ca = bitCnt(a);
    int cb = bitCnt(b);
    if (ca == cb) {
        return a - b;
    }
    return ca - cb;
}

void swapLT1356(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partitionQS(int* arr, int arrSize, int low, int high) {
    int pivot = arr[high];

    int i = low - 1;
    for (int j = low; j <= high; j++) {
        if (compareQS(arr[j], pivot) < 0) {
            i++;
            swapLT1356(&arr[i], &arr[j]);
        }
    }
    swapLT1356(&arr[i+1], &arr[high]);
    return i + 1;
}

void qsortMy(int* arr, int arrSize, int low, int high) {
    if (low < high) {
        int pi = partitionQS(arr, arrSize, low, high);
        qsortMy(arr, arrSize, low, pi - 1);
        qsortMy(arr, arrSize, pi + 1, high);
    }
}

int* sortByBits(int* arr, int arrSize, int* returnSize) {
    int* retAry = (int*)malloc(arrSize * sizeof(int));
    for (int i = 0; i < arrSize; i++) {
        retAry[i] = arr[i];
    }
    *returnSize = arrSize;

    qsortMy(retAry, arrSize, 0, arrSize - 1);
    return retAry;
}
