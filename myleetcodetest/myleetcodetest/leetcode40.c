#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

// 回溯/动态规划对于：取还是不去的选择，要用for循环来做。就像这一题，必须要用for循环才比较方便。

void dumpAryLT40(int* ary, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", ary[i]);
    }
    printf("\n");
}

void combHelper(int* ary, int n, int ii, int t, int* path, int pathIdx, int** retAry, int* returnSize, int** returnColumnSizes) {
    if (ii > n || t < 0) {
        return;
    }

    if (t == 0) {
        //dumpAryLT40(path, pathIdx);

        (*returnColumnSizes)[*returnSize] = pathIdx;
        for (int j = 0; j < pathIdx; j++) {
            retAry[*returnSize][j] = path[j];
        }
        (*returnSize)++;

        return;
    }

    //printf("ii: %d, t: %d, path: ", ii, t);
    //for (int i = 0; i < pathIdx; i++) {
    //    printf("%d ", path[i]);
    //}
    //printf("\n");
    for (int i = ii; i < n; i++) {
        //printf("ii: %d, ary[%d] = %d, t: %d\n", ii, i, ary[i], t);
        if (ary[i] > t) {
            continue;
        } else { // ary[i] <= t
            if (i > ii && ary[i] == ary[i - 1]) {
                continue;
            }
            path[pathIdx] = ary[i];
            combHelper(ary, n, i + 1, t - ary[i], path, pathIdx + 1, retAry, returnSize, returnColumnSizes);
        }
    }
}

int compareLT40(void* a, void* b) {
    int ia = *(int*)a;
    int ib = *(int*)b;
    return ia - ib;
}

int** combinationSum2(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes) {
    qsort(candidates, candidatesSize, sizeof(int), compareLT40);

    int* path = (int*)malloc(candidatesSize * sizeof(int));

    int** retAry = (int**)malloc(1000 * sizeof(int*));
    *returnColumnSizes = (int*)malloc(1000 * sizeof(int));
    *returnSize = 0;
    for (int i = 0; i < 1000; i++) {
        (*returnColumnSizes)[i] = 0;
        retAry[i] = (int*)malloc(candidatesSize * sizeof(int));
    }

    combHelper(candidates, candidatesSize, 0, target, path, 0, retAry, returnSize, returnColumnSizes);
    free(path);
    return retAry;
}