//
//  leetcode74.c
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

#include "leetcode74.h"

bool searchMatrixLT74(int** matrix, int matrixSize, int* matrixColSize, int target) {
    int l = 0, r = matrixSize;
    while (l < r) {
        int mid = (l + r) / 2;
        if (matrix[mid][0] < target) {
            if (l == mid) { // 注意：要加上这个以防死循环
                break;
            }
            l = mid;
        } else if (matrix[mid][0] > target) {
            if (r == mid) { // 注意：要加上这个以防死循环
                break;
            }
            r = mid;
        } else {
            return true;
        }
    }

    //printf("Found in: %d\n", l);

    int rowIdx = l;
    l = 0, r = matrixColSize[0];
    while (l < r) {
        int mid = (l + r) / 2;
        if (matrix[rowIdx][mid] < target) {
            if (l == mid) { // 注意：要加上这个以防死循环
                break;
            }
            l = mid;
        } else if (matrix[rowIdx][mid] > target) {
            if (r == mid) { // 注意：要加上这个以防死循环
                break;
            }
            r = mid;
        } else {
            return true;
        }
    }

    return false;
}
