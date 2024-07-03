//
//  leetcode347.c
//  myleetcodetest
//
//  Created by jason on 2024-07-02.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode347.h"

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

void swapLT347(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Min heap
void heapifyUPLT347(int* heapAry, int n, int k) {
    int parentIdx = ((k + 1) / 2) - 1;
    if (heapAry[parentIdx] > heapAry[k]) {
        swapLT347(&heapAry[parentIdx], &heapAry[k]);
        heapifyUPLT347(heapAry, n, parentIdx);
    }
}

typedef struct {
    int num;
    int freq;
} HEAPNODE;

void swapHNLT347(HEAPNODE* a, HEAPNODE* b) {
    int num = a->num;
    int freq = a->freq;
    a->num = b->num;
    a->freq = b->freq;
    b->num = num;
    b->freq = freq;
}

void healpifyDownLT347(HEAPNODE* heapAry, int n, int k) {
    int leftIdx = (k + 1) * 2 - 1;
    int rightIdx = (k + 1) * 2;
    int maxIdx = k;
    if (leftIdx < n && heapAry[leftIdx].freq < heapAry[maxIdx].freq) {
        maxIdx = leftIdx;
    }
    if (rightIdx < n && heapAry[rightIdx].freq < heapAry[maxIdx].freq) {
        maxIdx = rightIdx;
    }
    if (maxIdx != k) {
        swapHNLT347(&heapAry[k], &heapAry[maxIdx]);
        healpifyDownLT347(heapAry, n, maxIdx);
    }
}

void dumpHeap(HEAPNODE* heapAry, int n) {
    printf("Heap: ");
    for (int i = 0; i < n; i++) {
        printf("(%d,%d) ", heapAry[i].num, heapAry[i].freq);
    }
    printf("\n");
}

int* topKFrequentLT347(int* nums, int numsSize, int k, int* returnSize) {
    int* freqAry = (int*)malloc(20001 * sizeof(int)); // 20001 includes 0
    memset(freqAry, 0, 20001 * sizeof(int));

    int min = INT_MAX, max = INT_MIN;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] + 10000 < min) {
            min = nums[i] + 10000;
        }
        if (nums[i] + 10000 > max) {
            max = nums[i] + 10000;
        }
        freqAry[nums[i] + 10000]++;
    }

    for (int i = 0; i < 20001; i++) {
        if (freqAry[i] > 0) {
            printf("Freq %d: %d\n", i - 10000, freqAry[i]);
        }
    }

    printf("Min: %d, Max: %d\n", min, max);

    HEAPNODE* heapAry = (HEAPNODE*)malloc(k * sizeof(HEAPNODE));
    int heapSize = 0;
    for (int i = min; i <= max; i++) {
        if (freqAry[i] > 0) {
            if (heapSize < k) {
                heapAry[heapSize].num = i - 10000;
                heapAry[heapSize].freq = freqAry[i];
                heapSize++;
                if (heapSize == k) {
                    for (int j = k - 1; j >= 0; j--) {
                        healpifyDownLT347(heapAry, k, j);
                    }
                    //dumpHeap(heapAry, k);
                }
            } else {
                if (freqAry[i] > heapAry[0].freq) {
                    heapAry[0].num = i - 10000;
                    heapAry[0].freq = freqAry[i];
                    healpifyDownLT347(heapAry, k, 0);
                }
            }
        }
    }

    //dumpHeap(heapAry, k);

    int* retAry = (int*)malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) {
        retAry[i] = heapAry[k - 1 - i].num;
    }

    free(freqAry);
    free(heapAry);

    *returnSize = k;
    return retAry;
}
