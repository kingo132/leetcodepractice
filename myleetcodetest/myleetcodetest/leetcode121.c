//
//  leetcode121.c
//  myleetcodetest
//
//  Created by jason on 2024-06-30.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#include "leetcode121.h"

int maxProfit(int* prices, int pricesSize) {
    int* tmpAry = (int*)malloc(pricesSize * sizeof(int));
    int min = INT_MAX, max = INT_MIN, maxProfit = INT_MIN;
    for (int i = 0; i < pricesSize; i++) {
        if (prices[i] < min) {
            min = prices[i];
        }
        tmpAry[i] = min;
    }
    for (int i = pricesSize - 1; i >= 0; i--) {
        if (prices[i] > max) {
            max = prices[i];
        }
        if (max - tmpAry[i] > maxProfit) {
            maxProfit = max - tmpAry[i];
        }
    }
    return maxProfit;
}
