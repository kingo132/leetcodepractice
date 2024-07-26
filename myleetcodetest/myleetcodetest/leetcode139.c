#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

bool wordBreakHelper(char* s, int ii, char** wordDict, int wordDictSize, int* dp) {
    if (dp[ii] != -1) {
        return dp[ii] == 1;
    }

    bool ret = false;
    for (int i = 0; i < wordDictSize; i++) {
        if (*(s + ii) == wordDict[i][0]) {
            int jj = 0;
            while (*(s + ii + jj) != '\0' && *(s + ii + jj) == wordDict[i][jj]) {
                jj++;
            }
            if (*(s + ii + jj) == '\0') {
                if (wordDict[i][jj] == '\0') {
                    ret = true;
                    break;
                }
            } else if (wordDict[i][jj] == '\0') {
                if (wordBreakHelper(s, ii + jj, wordDict, wordDictSize, dp)) {
                    ret = true;
                    break;
                }
            }
        }
    }
    dp[ii] = ret ? 1 : 0;
    return ret;
}

bool wordBreak(char* s, char** wordDict, int wordDictSize) {
    int len = 0;
    char* p = s;
    while (*p) {
        len++;
        p++;
    }
    int* dp = (int*)malloc((len + 1) * sizeof(int));
    memset(dp, -1, (len + 1) * sizeof(int));
    bool ret = wordBreakHelper(s, 0, wordDict, wordDictSize, dp);
    free(dp);
    return ret;
}