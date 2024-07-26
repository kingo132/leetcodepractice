#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

void swapLT48(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void dumpMatrixLT48(int** m, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}

void rotateLT48(int** matrix, int matrixSize, int* matrixColSize) {
    int n = matrixSize;
    if (n <= 1) {
        return;
    }

    int m = n / 2;
    if (n % 2 != 0) {
        m += 1;
    }
    for (int i = 0; i < m; i++) {
        // i,i
        for (int j = i; j < n - i - 1; j++) {
            // i,j        j,n-1-i
            // n-1-j,i    n-1-i,n-1-j
            printf("(%d,%d) -> (%d,%d) -> (%d,%d) -> (%d,%d)\n",
                i, j, j, n-1-i, n-1-i, n-1-j, n-1-j, i);
            //continue;
            int t = matrix[i][j];
            matrix[i][j] = matrix[n-1-j][i];
            matrix[n-1-j][i] = matrix[n-1-i][n-1-j];
            matrix[n-1-i][n-1-j] = matrix[j][n-1-i];
            matrix[j][n-1-i] = t;

            //dumpMatrix(matrix, n);
        }
    }
}
