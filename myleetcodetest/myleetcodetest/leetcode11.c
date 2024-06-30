//
//  leetcode11.c
//  myleetcodetest
//
//  Created by jason on 2024-06-17.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "leetcode11.h"

#define MIN(a,b) ((a)>(b)?(b):(a))

int maxAreaBruteForce(int* height, int heightSize) {
    int maxWater = INT_MIN;
    for (int i = 0; i < heightSize; i++) {
        for (int j = i + 1; j < heightSize; j++) {
            int v = MIN(height[i], height[j]) * (j - i);
            if (v > maxWater) {
                maxWater = v;
            }
        }
    }
    return maxWater;
}

int maxArea(int* height, int heightSize) {
    int left = 0, right = heightSize - 1;
    int maxWater = INT_MIN;
    while (left < right) {
        int v = MIN(height[left], height[right]) * (right - left);
        if (v > maxWater) {
            maxWater = v;
        }
        if (height[left] < height[right]) {
            left ++;
        } else {
            right --;
        }
    }
    return maxWater;
}
