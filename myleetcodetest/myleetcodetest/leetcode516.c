//
//  leetcode516.c
//  myleetcodetest
//
//  Created by jason on 2024-06-27.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#include "leetcode516.h"

void dumpString(char* sOrig, char* eOrig, int n, int n1, int n2) {
    return;
    if (sOrig) {
        char tmp = *(eOrig + 1);
        *(eOrig + 1) = '\0';
        printf("Found: %s, maxSeq: %d, eqLen: %d, maxLenSub: %d\n", sOrig, n, n1, n2);
        *(eOrig + 1) = tmp;
    }
}

char* gSOrig = NULL;
char* gEOrig = NULL;

bool isPlainSubOld(char* s, char* e, int* maxSeq, int* dp, int sLen) {
    char* sOrig = s, * eOrig = e;
    int eqLen = 0;
    while (s <= e) {
        if (*s != *e) {
            bool found = false;
            if (dp[(s + 1 - gSOrig) * sLen + gEOrig - e] > 0) {
                if (eqLen + dp[(s + 1 - gSOrig) * sLen + gEOrig - e] > *maxSeq) {
                    *maxSeq = eqLen + dp[(s + 1 - gSOrig) * sLen + gEOrig - e];
                }
                found = true;
            } else {
                int maxLenSub = 0;
                if (isPlainSubOld(s + 1, e, &maxLenSub, dp, sLen)) {
                    if (eqLen + maxLenSub > *maxSeq) {
                        *maxSeq = eqLen + maxLenSub;
                    }
                    dumpString(sOrig, eOrig, *maxSeq, eqLen, maxLenSub);
                    dp[(s + 1 - gSOrig) * sLen + gEOrig - e] = maxLenSub;
                    found = true;
                }
            }
            if (dp[(s - gSOrig) * sLen + gEOrig - e + 1] > 0) {
                if (eqLen + dp[(s - gSOrig) * sLen + gEOrig - e + 1] > *maxSeq) {
                    *maxSeq = eqLen + dp[(s - gSOrig) * sLen + gEOrig - e + 1];
                }
                found = true;
            } else {
                int maxLenSub = 0;
                if (isPlainSubOld(s, e - 1, &maxLenSub, dp, sLen)) {
                    if (eqLen + maxLenSub > *maxSeq) {
                        *maxSeq = eqLen + maxLenSub;
                    }
                    dumpString(sOrig, eOrig, *maxSeq, eqLen, maxLenSub);
                    dp[(s - gSOrig) * sLen + gEOrig - e + 1] = maxLenSub;
                    found = true;
                }
            }
            return found;
        } else {
            if (s != e) {
                eqLen += 2;
            } else {
                eqLen += 1;
            }
            s++;
            e--;
        }
    }
    if (eqLen > *maxSeq) {
        *maxSeq = eqLen;
    }
    dumpString(sOrig, eOrig, *maxSeq, eqLen, -1);
    return true;
}

int longestPalindromeSubseq(char* s) {
    char* pEnd = s;
    while (*(pEnd + 1)) {
        pEnd++;
    }

    gSOrig = s;
    gEOrig = pEnd;

    int sLen = pEnd - s + 1;
    int* dp = (int*)malloc(sLen * sLen * sizeof(int));
    for (int i = 0; i < sLen * sLen; i++) {
        dp[i] = 0;
    }

    int maxLen = INT_MIN;
    for (char* p1 = s; p1 <= pEnd; p1++) {
        for (char* p2 = pEnd; p2 >= s; p2--) {
            int maxSeq = 0;
            if (p2 - p1 + 1 > maxLen && isPlainSubOld(p1, p2, &maxSeq, dp, sLen) && maxSeq > maxLen) {
                maxLen = maxSeq;
            }
        }
    }

    //for (int i = 0; i < sLen * sLen; i++) {
    //    if (i % sLen == 0) {
    //        printf("\n");
    //    }
    //    printf("%d ", dp[i]);
    //}

    return maxLen;
}
