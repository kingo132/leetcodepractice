#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

int maxProfitHelperOld(int* prices, int pricesSize, int idx, int leftCnt, int* dp) {
    if (leftCnt <= 0) {
        return 0;
    }
    if (leftCnt == 1 && dp[idx] != -1) {
        return dp[idx];
    }
    int max = 0;
    int minPrice = prices[idx];
    for (int j = idx + 1; j < pricesSize; j++) {
        if (prices[j] < minPrice) {
            minPrice = prices[j];
        }
        if (prices[j] > minPrice) {
            // two choice, buy or not buy
            int v = prices[j] - minPrice;
            if (leftCnt == 2 && dp[j] != -1) {
                v += dp[j];
            } else if (leftCnt == 2) {
                printf("Try j: %d, v: %d, max: %d\n", j, v, max);
                v += maxProfitHelperOld(prices, pricesSize, j, leftCnt - 1, dp);
            }
            if (v > max) {
                printf("j: %d(%d), v: %d, max: %d, leftCnt: %d\n", j, prices[j], v, max, leftCnt);
                max = v;
            }
        }
    }
    if (leftCnt == 1) {
        dp[idx] = max;
    }
    return max;
}

int maxProfitOld(int* prices, int pricesSize) {
    int* dp;
    dp = (int*)malloc(pricesSize * sizeof(int));
    memset(dp, -1, pricesSize * sizeof(int));
    int ret = maxProfitHelperOld(prices, pricesSize, 0, 2, dp);
    free(dp);
    return ret;
}

int maxProfitChatGPT(int* prices, int pricesSize) {
    if (pricesSize == 0) return 0;

    int* leftProfit = (int*)malloc(pricesSize * sizeof(int));
    int* rightProfit = (int*)malloc(pricesSize * sizeof(int));

    // Calculate leftProfit
    int minPrice = prices[0];
    leftProfit[0] = 0;
    for (int i = 1; i < pricesSize; i++) {
        leftProfit[i] = fmax(leftProfit[i - 1], prices[i] - minPrice);
        minPrice = fmin(minPrice, prices[i]);
    }

    // Calculate rightProfit
    int maxPrice = prices[pricesSize - 1];
    rightProfit[pricesSize - 1] = 0;
    for (int i = pricesSize - 2; i >= 0; i--) {
        rightProfit[i] = fmax(rightProfit[i + 1], maxPrice - prices[i]);
        maxPrice = fmax(maxPrice, prices[i]);
    }

    // Calculate the maximum profit by combining leftProfit and rightProfit
    int maxProfit = 0;
    for (int i = 0; i < pricesSize; i++) {
        maxProfit = fmax(maxProfit, leftProfit[i] + rightProfit[i]);
    }

    free(leftProfit);
    free(rightProfit);

    return maxProfit;
}
