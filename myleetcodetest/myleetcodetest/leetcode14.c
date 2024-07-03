//
//  leetcode14.c
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

#include "leetcode14.h"

char* longestCommonPrefix(char** strs, int strsSize) {
    if (strsSize <= 0) {
        return NULL;
    }
    char* retStr = (char*)malloc(256 * sizeof(char));
    int idx = 0;
    while (1) {
        int c = strs[0][idx];
        int needBreak = 0;
        for (int i = 1; i < strsSize; i++) {
            if (strs[i][idx] != c) {
                needBreak = 1;
                break;
            }
        }

        if (needBreak || c == '\0') {
            break;
        }
        retStr[idx++] = c;
    }
    
    retStr[idx] = '\0';
    return retStr;
}
