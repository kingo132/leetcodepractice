//
//  leetcode93.c
//  myleetcodetest
//
//  Created by jason on 2024-06-30.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#include "leetcode93.h"

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

bool isDebug = false;

bool isValidIP(char* s, int dot1, int dot2, int dot3, int sLen) {
    if (isDebug) printf("Test: %d,%d,%d,%d: ", dot1, dot2, dot3, sLen);
    int n1 = 0, n2 = 0, n3 = 0, n4 = 0;
    for (int i = 0; i <= dot1; i++) {
        if (n1 != 0) {
            n1 *= 10;
        } else if (s[i] == '0' && dot1 > 0) {
            if (isDebug) printf(", invalid\n");
            return false;
        }
        n1 += s[i] - '0';
    }
    if (n1 > 255) {
        if (isDebug) printf(", invalid n1: %d\n", n1);
        return false;
    }
    
    for (int i = dot1 + 1; i <= dot2; i++) {
        if (n2 != 0) {
            n2 *= 10;
        } else if (s[i] == '0' && dot2 - dot1 > 1) {
            if (isDebug) printf(", invalid\n");
            return false;
        }
        n2 += s[i] - '0';
    }
    if (n2 > 255) {
        if (isDebug) printf(", invalid n2: %d\n", n2);
        return false;
    }

    for (int i = dot2 + 1; i <= dot3; i++) {
        if (n3 != 0) {
            n3 *= 10;
        } else if (s[i] == '0' && dot3 - dot2 > 1) {
            if (isDebug) printf(", invalid\n");
            return false;
        }
        n3 += s[i] - '0';
    }
    if (n3 > 255) {
        if (isDebug) printf(", invalid n3: %d\n", n3);
        return false;
    }

    for (int i = dot3 + 1; i < sLen; i++) {
        if (n4 != 0) {
            n4 *= 10;
        } else if (s[i] == '0' && sLen - dot3 - 1 > 1) {
            if (isDebug) printf(", invalid\n");
            return false;
        }
        n4 += s[i] - '0';
    }
    if (n4 > 255) {
        if (isDebug) printf(", invalid n4: %d\n", n4);
        return false;
    }

    if (isDebug) printf(", valid\n");
    return true;
}
char** restoreIpAddresses(char* s, int* returnSize) {
    int sLen = 0;
    char* p = s;
    while (*p) {
        sLen++;
        p++;
    }

    char** retAry = (char**)malloc(1000 * sizeof(char*));
    *returnSize = 0;

    for (int dot1 = 0; dot1 < 3; dot1++) {
        for (int dot2 = dot1 + 1; dot2 < dot1 + 4; dot2++) {
            for (int dot3 = dot2 + 1; dot3 < dot2 + 4; dot3++) {
                if (sLen - dot3 - 1 > 3 || sLen - dot3 - 1 <= 0) {
                    continue;
                }
                if (isValidIP(s, dot1, dot2, dot3, sLen)) {
                    if (isDebug) printf("Valid: %d,%d,%d\n", dot1, dot2, dot3);
                    char* str = (char*)malloc((sLen + 4) * sizeof(char));
                    int strIdx = 0;
                    for (int i = 0; i < sLen; i++) {
                        str[strIdx++] = s[i];
                        if (i == dot1 || i == dot2 || i == dot3) {
                            str[strIdx++] = '.';
                        }
                    }
                    str[strIdx] = '\0';
                    retAry[(*returnSize)++] = str;
                }
            }
        }
    }

    return retAry;
}
