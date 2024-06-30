//
//  leetcode221.c
//  myleetcodetest
//
//  Created by jason on 2024-06-14.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "leetcode221.h"

int maximalSquareBruteForce(char** matrix, int matrixSize, int* matrixColSize) {
    int minEdge = matrixSize > matrixColSize[0] ? matrixColSize[0] : matrixSize;
    int largestSQ = minEdge;
    while (largestSQ > 0) {
        for (int i = 0; i <= matrixSize - largestSQ; i++) {
            for (int j = 0; j <= matrixColSize[0] - largestSQ; j++) {
                int found = 1;
                for (int l = i; l < i + largestSQ; l++) {
                    for (int m = j; m < j + largestSQ; m++) {
                        if (matrix[l][m] == '0') {
                            //printf("Zero %d,%d\n", l, m);
                            found = 0;
                            break;
                        }
                    }
                    if (found == 0) {
                        break;
                    }
                }
                if (found) {
                    printf("Found i:%d,j:%d,sq:%d\n", i, j, largestSQ);
                    return largestSQ * largestSQ;
                }
            }
        }
        
        largestSQ --;
    }

    return largestSQ * largestSQ;
}

int minthree(int a, int b, int c) {
    if (a < b) {
        if (a < c) {
            return a;
        } else {
            return c;
        }
    } else {
        if (b < c) {
            return b;
        } else {
            return c;
        }
    }

    return -1;
}

int maximalSquare(char** matrix, int matrixSize, int* matrixColSize) {
    int dpSize = matrixSize * matrixColSize[0];
    int* dp = (int*)malloc(dpSize * sizeof(int));
    for (int i = 0; i < dpSize; i++) {
        dp[i] = 0;
    }
    int max = 0;
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixColSize[0]; j++) {
            if (i == 0 || j == 0) {
                dp[i * matrixColSize[0] + j] = matrix[i][j] == '1' ? 1 : 0;
            } else if (matrix[i][j] == '1') {
                dp[i * matrixColSize[0] + j] = minthree(dp[i * matrixColSize[0] + j - 1], dp[(i - 1) * matrixColSize[0] + j], dp[(i - 1) * matrixColSize[0] + j - 1]) + 1;
            }
            if (dp[i * matrixColSize[0] + j] > max) {
                max = dp[i * matrixColSize[0] + j];
            }
        }
    }

    free(dp);
    return max * max;
}
