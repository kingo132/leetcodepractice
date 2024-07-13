//
//  leetcode72.c
//  myleetcodetest
//
//  Created by jason on 2024-07-11.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode72.h"

int minDistanceHelper(char* s1, int i, int s1len, char* s2, int j, int s2len, int** dp) {
    int ii = i, jj = j;
    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    while (i < s1len && j < s2len && *(s1 + i) == *(s2 + j)) {
        i++;
        j++;
    }

    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    if (i >= s1len) {
        dp[ii][jj] = s2len - j;
        if (dp[ii][jj] < 0) {
            dp[ii][jj] = 0;
        }
        //printf("Set dp1 %d,%d = %d\n", ii, jj, dp[ii][jj]);
        return dp[ii][jj];
    }
    if (j >= s2len) {
        dp[ii][jj] = s1len - i;
        if (dp[ii][jj] < 0) {
            dp[ii][jj] = 0;
        }
        //printf("Set dp2 %d,%d = %d\n", ii, jj, dp[ii][jj]);
        return dp[ii][jj];
    }

    // inset / delete
    int len1 = 1 + minDistanceHelper(s1, i + 1, s1len, s2, j, s2len, dp);
    int len2 = 1 + minDistanceHelper(s1, i, s1len, s2, j + 1, s2len, dp);
    // replace
    int len3 = 1 + minDistanceHelper(s1, i + 1, s1len, s2, j + 1, s2len, dp);
    dp[ii][jj] = len1 > len2 ? len2 : len1;
    dp[ii][jj] = dp[ii][jj] > len3 ? len3 : dp[ii][jj];
    //printf("Set dp3 %d,%d = %d (%d,%d,%d)\n", ii, jj, dp[ii][jj], len1, len2, len3);
    return dp[ii][jj];
}

int minDistanceLT72(char* word1, char* word2) {
    int len1 = 0;
    char* p1 = word1;
    while (*p1) {
        len1++;
        p1++;
    }
    int len2 = 0;
    p1 = word2;
    while (*p1) {
        len2++;
        p1++;
    }

    int** dp = (int**)malloc((len1 + 1) * sizeof(int*));
    for (int i = 0; i < len1 + 1; i++) {
        dp[i] = (int*)malloc((len2 + 1) * sizeof(int));
        for (int j = 0; j < len2 + 1; j++) {
            dp[i][j] = -1;
        }
    }

    int ret = minDistanceHelper(word1, 0, len1, word2, 0, len2, dp);

    for (int i = 0; i < len1 + 1; i++) {
        for (int j = 0; j < len2 + 1; j++) {
            printf("%d ", dp[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < len1 + 1; i++) {
        free(dp[i]);
    }
    free(dp);

    return ret;
}
