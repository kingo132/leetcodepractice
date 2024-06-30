//
//  leetcode120.c
//  myleetcodetest
//
//  Created by jason on 2024-06-11.
//

#include "leetcode120.h"

#define MIN(a,b) ((a)<(b)?(a):(b))

int minimumTotal(int** triangle, int triangleSize, int* triangleColSize) {
    for (int row = triangleSize - 2; row >= 0; row --) {
        for (int i = 0; i < triangleColSize[row]; i++) {
            triangle[row][i] += MIN(triangle[row + 1][i], triangle[row + 1][i + 1]);
        }
    }
    return triangle[0][0];
}
