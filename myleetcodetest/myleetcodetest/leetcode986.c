#include <stdio.h>
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
#define MYDBG false
// 等于的情况，可以包括在各个分支判断里面
int** intervalIntersection(int** firstList, int firstListSize, int* firstListColSize, int** secondList, int secondListSize, int* secondListColSize, int* returnSize, int** returnColumnSizes) {
    int idx1 = 0, idx2 = 0;

    int** retAry = (int**)malloc(1000 * sizeof(int*));
    *returnColumnSizes = (int*)malloc(1000 * sizeof(int));
    for (int i = 0; i < 1000; i++) {
        retAry[i] = (int*)malloc(2 * sizeof(int));
        (*returnColumnSizes)[i] = 2;
    }
    *returnSize = 0;

    while (idx1 < firstListSize && idx2 < secondListSize) {
        int s1 = firstList[idx1][0], e1 = firstList[idx1][1];
        int s2 = secondList[idx2][0], e2 = secondList[idx2][1];

        if (MYDBG) printf("Check, s1: %d, e1: %d, s2: %d, e2: %d\n", s1, e1, s2, e2);
        if (s1 <= s2 && e1 <= e2 && s2 <= e1) {
            // 1212
            if (MYDBG) printf("1:(%d - %d), ", s2, e1);
            retAry[*returnSize][0] = s2;
            retAry[*returnSize][1] = e1;
            (*returnSize)++;
            idx1++;
        } else if (s1 >= s2 && e1 >= e2 && s1 <= e2) {
            // 2121
            if (MYDBG) printf("2:(%d - %d), ", s1, e2);
            retAry[*returnSize][0] = s1;
            retAry[*returnSize][1] = e2;
            (*returnSize)++;
            idx2++;
        } else if (s1 >= s2 && e1 <= e2) {
            // 2112
            if (MYDBG) printf("3:(%d - %d), ", s1, e1);
            retAry[*returnSize][0] = s1;
            retAry[*returnSize][1] = e1;
            (*returnSize)++;
            idx1++;
        } else if (s1 <= s2 && e1 >= e2) {
            // 1221
            if (MYDBG) printf("4:(%d - %d), ", s2, e2);
            retAry[*returnSize][0] = s2;
            retAry[*returnSize][1] = e2;
            (*returnSize)++;
            idx2++;
        } else if (e1 < s2) {
            // 1122
            idx1++;
        } else if (s1 > e2) {
            // 2211
            idx2++;
        } else {
            if (MYDBG) printf("Unresolved\n");
        }
    }

    //*returnSize = 0;
    return retAry;
}
