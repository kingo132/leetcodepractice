//
//  leetcode59.c
//  myleetcodetest
//
//  Created by jason on 2024-07-07.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode59.h"

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

void dumpMatric(const char* prefix, int** m, int n) {
    printf("%s", prefix);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}
int** generateMatrixMy(int n, int* returnSize, int** returnColumnSizes) {
    int** retMat = (int**)malloc(n * sizeof(int*));
    *returnSize = n;
    *returnColumnSizes = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        retMat[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            retMat[i][j] = 0;
        }
        (*returnColumnSizes)[i] = n;
    }

    int i = 0, j = 0, step = n - 1, curStep = 0, cur = 1, direction = 1;
    for (; j < n; j++) {
        retMat[i][j] = cur++;
    }
    j = n - 1;
    while (1) {
        if (direction == 0) { // 0 right
            j++;
        } else if (direction == 1) { // 1 down
            i++;
        } else if (direction == 2) { // 2 left
            j--;
        } else if (direction == 3) { // 3 up
            i--;
        }
        printf("Set %d,%d = %d, curStep: %d, step: %d, direct: %d\n", i, j, cur, curStep, step, direction);
        if (i < 0 || i >= n || j < 0 || j >= n) {
            printf("Invalid %d,%d\n", i, j);
            break;
        }
        if (retMat[i][j] != 0) {
            break;
        }
        retMat[i][j] = cur++;

        curStep++;
        if (curStep >= step) {
            if (direction == 0 || direction == 2) {
                step--;
            }
            direction = (direction + 1) % 4;
            curStep = 0;
        }
    }

    return retMat;
}

// Function to generate a spiral matrix.
int** generateMatrixChatGPT(int n, int* returnSize, int** returnColumnSizes) {
    // Allocate memory for the matrix.
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }

    // Allocate memory for returnColumnSizes.
    *returnColumnSizes = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        (*returnColumnSizes)[i] = n;
    }
    
    // Set the returnSize.
    *returnSize = n;

    int left = 0, right = n - 1;
    int top = 0, bottom = n - 1;
    int num = 1;

    while (left <= right && top <= bottom) {
        // Traverse from left to right.
        for (int i = left; i <= right; i++) {
            matrix[top][i] = num++;
        }
        top++;

        // Traverse from top to bottom.
        for (int i = top; i <= bottom; i++) {
            matrix[i][right] = num++;
        }
        right--;

        // Traverse from right to left.
        if (top <= bottom) {
            for (int i = right; i >= left; i--) {
                matrix[bottom][i] = num++;
            }
            bottom--;
        }

        // Traverse from bottom to top.
        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                matrix[i][left] = num++;
            }
            left++;
        }
    }

    return matrix;
}
