//
//  leetcode384.c
//  myleetcodetest
//
//  Created by jason on 2024-06-30.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode384.h"




typedef struct {
    //int** numsAry;
    int* nums;
    int numsSize;
    //int numsArySize;
} Solution;

int factorialLT384(int n) {
    int ret = 1;
    while (n > 0) {
        ret *= n;
        n = n - 1;
    }
    return ret;
}

void swapLT384(int* a, int * b) {
    int t = *a;
    *a = *b;
    *b = t;
}

/*
void permutationLT384(int* nums, int numsSize, int idx, int** numsAry, int* numsArySize) {
    if (idx == numsSize - 1) {
        //printf("%d: ", *numsArySize);
        numsAry[*numsArySize] = (int*)malloc(numsSize * sizeof(int));
        for (int i = 0; i < numsSize; i++) {
            numsAry[*numsArySize][i] = nums[i];
            //printf("%d ", numsAry[*numsArySize][i]);
        }
        //printf("\n");
        (*numsArySize) ++;
        return;
    }
    for (int i = idx; i < numsSize; i++) {
        if (i != idx) {
            swapLT384(&nums[idx], &nums[i]);
        }
        //printf("%d,%d\n", idx, i);
        permutationLT384(nums, numsSize, idx + 1, numsAry, numsArySize);
        if (i != idx) {
            swapLT384(&nums[idx], &nums[i]);
        }
    }
}
*/
void permutationLT384Rand(int* nums, int numsSize, int idx, int* retAry) {
    if (idx == numsSize - 1) {
        //printf("rand: ");
        for (int i = 0; i < numsSize; i++) {
            retAry[i] = nums[i];
            //printf("%d ", retAry[i]);
        }
        //printf("\n");
        return;
    }
    int i = rand() % (numsSize - idx) + idx;
    if (i != idx) {
        swapLT384(&nums[idx], &nums[i]);
    }
    //printf("%d,%d\n", idx, i);
    permutationLT384Rand(nums, numsSize, idx + 1, retAry);
    if (i != idx) {
        swapLT384(&nums[idx], &nums[i]);
    }
}

Solution* solutionCreate(int* nums, int numsSize) {
    Solution* s = (Solution*)malloc(sizeof(Solution));
    //s->numsArySize = 0;
    //s->numsAry = (int**)malloc(factorialLT384(numsSize) * sizeof(int*));
    s->numsSize = numsSize;
    s->nums = (int*)malloc(s->numsSize * sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        s->nums[i] = nums[i];
    }

    srand(time(NULL));
    return s;
}

int* solutionReset(Solution* obj, int* retSize) {
    *retSize = obj->numsSize;
    return obj->nums;
}

int* solutionShuffle(Solution* obj, int* retSize) {
    *retSize = obj->numsSize;
    int* shuff = (int*)malloc(obj->numsSize * sizeof(int));
    permutationLT384Rand(obj->nums, obj->numsSize, 0, shuff);
    return shuff;
}

void solutionFree(Solution* obj) {
    //for (int i = 0; i < obj->numsArySize; i++) {
    //    free(obj->numsAry[i]);
    //}
    free(obj->nums);
    free(obj);
}

/**
 * Your Solution struct will be instantiated and called as such:
 * Solution* obj = solutionCreate(nums, numsSize);
 * int* param_1 = solutionReset(obj, retSize);
 
 * int* param_2 = solutionShuffle(obj, retSize);
 
 * solutionFree(obj);
*/
