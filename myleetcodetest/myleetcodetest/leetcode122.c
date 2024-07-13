//
//  leetcode122.c
//  myleetcodetest
//
//  Created by jason on 2024-07-10.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode122.h"

int maxProfitMy(int* prices, int pricesSize) {
    if (pricesSize <= 1) {
        return 0;
    }
    int* dp = (int*)malloc(pricesSize * sizeof(int));
    dp[pricesSize - 1] = 0;
    for (int i = pricesSize - 2; i >= 0; i--) {
        int max = INT_MIN;
        for (int j = i + 1; j < pricesSize; j++) {
            int profit = (prices[j] - prices[i] > 0 ? prices[j] - prices[i] : 0) + (dp[j] > 0 ? dp[j] : 0);
            //printf("Check profit %d on %d,%d\n", profit, prices[i], prices[j]);
            if (profit > max) {
                max = profit;
            }
        }
        dp[i] = max;
    }
    //for (int i = 0; i < pricesSize; i++) {
    //    printf("%d ", dp[i]);
    //}
    //printf("\n");
    return dp[0];
}

int maxProfitLT122(int* prices, int pricesSize) {
    int sum = 0;
    for (int i = 1; i < pricesSize; i++) {
        int v = prices[i] - prices[i - 1];
        if (v > 0) {
            sum += v;
        }
    }
    return sum;
}
