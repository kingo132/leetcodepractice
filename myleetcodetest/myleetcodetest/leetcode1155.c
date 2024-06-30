//
//  leetcode1155.c
//  myleetcodetest
//
//  Created by jason on 2024-06-18.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "leetcode1155.h"

int numRollsToTargetHelper(int n, int k, int target, int* auxMatrix, int origTgt, int origK) {
    if (n <= 0) {
        printf("Invalid n: %d\n", n);
        return 0;
    }
    int sum = 0;
    int minK = target - (n - 1) * k;
    if (minK < 1) {
        minK = 1;
    }
    int maxK = target - (n - 1);
    if (maxK > k) {
        maxK = k;
    }
    //printf("minK: %d, maxK: %d\n", minK, maxK);
    for (int i = minK; i <= maxK; i++) {
        int cur = 0;
        if (auxMatrix[(n - 1) * (origTgt * origK) + (target - 1) * origK + (i - 1)] != -1) {
            cur = auxMatrix[(n - 1) * (origTgt * origK) + (target - 1) * origK + (i - 1)];
        } else {
            if (target - i >= 0) {
                if (n <= 2) {
                    if (target - i <= k) {
                        cur = 1;
                    }
                } else {
                    cur = numRollsToTargetHelper(n - 1, k, target - i, auxMatrix, origTgt, origK);
                }
            }
            //printf("Pos %d target %d choose %d, has %d cand\n", n, target, i, cur);
            auxMatrix[(n - 1) * (origTgt * origK) + (target - 1) * origK + (i - 1)] = cur;
        }
        sum = (sum + cur) % 1000000007;
    }
    return sum;
}

int numRollsToTarget(int n, int k, int target) {
    int* auxMatrix = (int*)malloc(n * k * target * sizeof(int));
    for (int i = 0; i < n * k * target; i++) {
        auxMatrix[i] = -1;
    }

    int ret = numRollsToTargetHelper(n, k, target, auxMatrix, target, k);

    free(auxMatrix);
    return ret;
}
