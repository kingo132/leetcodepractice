//
//  leetcode46.c
//  myleetcodetest
//
//  Created by jason on 2024-06-13.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "leetcode46.h"

typedef struct {
    int val;
    int* rst;
    int rstIdx;
    int* visited;
} DSNODE;

int factorial(int n) {
    int f = 1;
    while (n > 0) {
        f *= n;
        n --;
    }
    return f;
}

void copyNode(DSNODE* a, DSNODE* b, int n) {
    b->val = a->val;
    b->rstIdx = a->rstIdx;
    for (int i = 0; i < n; i++) {
        b->rst[i] = a->rst[i];
        b->visited[i] = a->visited[i];
    }
}

int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int expectedRetCnt = factorial(numsSize);
    DSNODE* stack = (DSNODE*)malloc(expectedRetCnt * sizeof(DSNODE));
    int top = 0;
    for (int i = 0; i < expectedRetCnt; i++) {
        stack[i].rst = (int*)malloc(numsSize * sizeof(int));
        stack[i].rstIdx = 0;
        stack[i].visited = (int*)malloc(numsSize * sizeof(int));
        for (int j = 0; j < numsSize; j++) {
            stack[i].visited[j] = 0;
        }
    }
    
    int** resultAry = (int**)malloc(expectedRetCnt * sizeof(int*));
    *returnColumnSizes = (int*)malloc(expectedRetCnt * sizeof(int));
    *returnSize = 0;

    for (int i = 0; i < numsSize; i++) {
        stack[top].val = nums[i];
        stack[top].rst[stack[top].rstIdx++] = nums[i];
        stack[top].visited[i] = 1;
        top ++;
    }

    while (top > 0) {
        DSNODE n;
        n.rst = (int*)malloc(numsSize * sizeof(int));
        n.visited = (int*)malloc(numsSize * sizeof(int));
        copyNode(&(stack[--top]), &n, numsSize);

        if (n.rstIdx < numsSize) {
            for (int i = 0; i < numsSize; i++) {
                if (n.visited[i] == 0) {
                    copyNode(&n, &(stack[top]), numsSize);
                    stack[top].rst[stack[top].rstIdx++] = nums[i];
                    stack[top].visited[i] = 1;
                    top ++;
                }
            }
        } else {
            printf("Found: ");
            for (int i = 0; i < numsSize; i++) {
                printf("%d ", n.rst[i]);
            }
            printf("\n");
            int* tmpAry = (int*)malloc(numsSize * sizeof(int));
            for (int i = 0; i < numsSize; i++) {
                tmpAry[i] = n.rst[i];
            }
            resultAry[*returnSize] = tmpAry;
            (*returnColumnSizes)[*returnSize] = numsSize;
            (*returnSize) ++;
        }
        free(n.rst);
        free(n.visited);
    }

    for (int i = 0; i < *returnSize; i++) {
        free(stack[i].rst);
        free(stack[i].visited);
    }
    free(stack);

    return resultAry;
}

// From ChatGPT

// Helper function to swap two elements
void swapLT46(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Helper function to generate permutations using backtracking
void backtrackLT46(int *nums, int numsSize, int **result, int *returnSize, int *returnColumnSizes, int start) {
    if (start == numsSize) {
        result[*returnSize] = (int *)malloc(numsSize * sizeof(int));
        for (int i = 0; i < numsSize; i++) {
            result[*returnSize][i] = nums[i];
        }
        returnColumnSizes[*returnSize] = numsSize;
        (*returnSize)++;
        return;
    }
    
    for (int i = start; i < numsSize; i++) {
        swapLT46(&nums[start], &nums[i]);
        backtrackLT46(nums, numsSize, result, returnSize, returnColumnSizes, start + 1);
        swapLT46(&nums[start], &nums[i]); // backtrack
    }
}

int** permuteChatGPT(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int maxPermutations = 1;
    for (int i = 1; i <= numsSize; i++) {
        maxPermutations *= i; // numsSize!
    }
    
    int **result = (int **)malloc(maxPermutations * sizeof(int *));
    *returnColumnSizes = (int *)malloc(maxPermutations * sizeof(int));
    *returnSize = 0;
    
    backtrackLT46(nums, numsSize, result, returnSize, *returnColumnSizes, 0);
    
    return result;
}
