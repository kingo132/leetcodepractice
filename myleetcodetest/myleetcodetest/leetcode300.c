#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

void dumpStack(const char* prefix, int* stack, int top) {
    printf("%s", prefix);
    for (int i = 0; i < top; i++) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

int lengthOfLISHelper(int* nums, int numsSize, int ii, int* stack, int top) {
    while ((ii < numsSize) && (top == 0 || nums[ii] > nums[stack[top - 1]])) {
        stack[top++] = ii;
        ii++;
    }

    if (ii >= numsSize) {
        //dumpStack("Final: ", stack, top);
        return top;
    }

    //dumpStack("A1: ", stack, top);
    int len1 = lengthOfLISHelper(nums, numsSize, ii + 1, stack, top);

    //dumpStack("A2: ", stack, top);
    while (top > 0 && (nums[ii] <= nums[stack[top - 1]] || ii <= stack[top - 1])) {
        top--;
    }
    stack[top++] = ii;
    //printf("ii1: %d\n", ii);
    //dumpStack("A3: ", stack, top);
    int len2 = lengthOfLISHelper(nums, numsSize, ii + 1, stack, top);
    //printf("ii2: %d\n", ii);
    //dumpStack("A4: ", stack, top);

    return len1 > len2 ? len1 : len2;
}

int compareLT300(void* a, void* b) {
    int ia = *(int*)a;
    int ib = *(int*)b;
    return ia - ib;
}

int lengthOfLIS(int* nums, int numsSize) {
    //int* stack = (int*)malloc(3000 * sizeof(int));
    //int top = 0;
    //return lengthOfLISHelper(nums, numsSize, 0, stack, top);
    int* tmpAry = (int*)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        tmpAry[i] = 0;
    }
    int globalMax = INT_MIN;
    for (int i = numsSize - 1; i >= 0; i--) {
        int max = 1;
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[j] > nums[i] && tmpAry[j] + 1 > max) {
                max = tmpAry[j] + 1;
            }
        }
        tmpAry[i] = max;
        if (max > globalMax) {
            globalMax = max;
        }
    }
    dumpStack("tmpAry: ", tmpAry, numsSize);
    free(tmpAry);
    return globalMax;
}