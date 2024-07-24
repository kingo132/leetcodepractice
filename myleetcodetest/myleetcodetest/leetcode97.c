#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

// 注意：动态规划每一个函数内不需要考虑其他数组元素的值存储，只需要考虑自己的就可以了，但是return前必须要把自己的值存下来
bool isInterleaveHelper(char* s1, int idx1, char* s2, int idx2, char* s3, int idx3, int*** dp) {
    if (s1[idx1] == '\0' && s2[idx2] == '\0' && s3[idx3] == '\0') {
        dp[idx1][idx2][idx3] = 1;
        return true;
    }

    if (dp[idx1][idx2][idx3] != -1) {
        return dp[idx1][idx2][idx3] == 1;
    }

    bool ret = false;
    if (s1[idx1] != '\0' && s3[idx3] != '\0' && s3[idx3] == s1[idx1]) {
        ret = isInterleaveHelper(s1, idx1 + 1, s2, idx2, s3, idx3 + 1, dp);
    }

    if (!ret && s2[idx2] != '\0' && s3[idx3] != '\0' && s3[idx3] == s2[idx2]) {
        ret = isInterleaveHelper(s1, idx1, s2, idx2 + 1, s3, idx3 + 1, dp);
    }

    dp[idx1][idx2][idx3] = ret ? 1 : 0;
    return ret;
}

int strlenLT97(char* s) {
    int len = 0;
    while (*s != '\0') {
        len++;
        s++;
    }
    return len;
}

bool isInterleave(char* s1, char* s2, char* s3) {
    int len1 = strlenLT97(s1) + 1;
    int len2 = strlenLT97(s2) + 1;
    int len3 = strlenLT97(s3) + 1;
    int*** dp = (int***)malloc(len1 * sizeof(int**));
    for (int i = 0; i < len1; i++) {
        dp[i] = (int**)malloc(len2 * sizeof(int*));
        for (int j = 0; j < len2; j++) {
            dp[i][j] = (int*)malloc(len3 * sizeof(int));
            memset(dp[i][j], -1, len3 * sizeof(int));
        }
    }
    bool ret = isInterleaveHelper(s1, 0, s2, 0, s3, 0, dp);
    for (int i = 0; i < len1; i++) {
        for (int j = 0; j < len2; j++) {
            free(dp[i][j]);
        }
        free(dp[i]);
    }
    free(dp);
    return ret;
}