//
//  leetcode767.c
//  myleetcodetest
//
//  Created by jason on 2024-06-17.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include "leetcode767.h"

#define SWAPCHAR(p,q) {char c = *(p); *(p) = *(q); *(q) = c; }

int compareLT767(const void* a, const void* b) {
    char ia = *(char*)a;
    char ib = *(char*)b;
    return ia - ib;
}

char* reorganizeStringTwoWay(char* s) {
    /*int strlen = 0;
    char* p = s;
    while (*p) {
        strlen ++;
        p ++;
    }

    qsort(s, strlen, sizeof(char), compareLT767);*/

    int impos = 0;
    char* p = s + 1;
    while (*p) {
        printf("Dump: %s\n", s);
        if (*p == *(p - 1)) {
            char* q = p + 1;
            while (*q) {
                if (*q != *p) {
                    break;
                }
                q ++;
            }
            if (! *q) {
                //printf("Impossible 1\n");
                //return "";
                impos = 1;
                break;
            }
            SWAPCHAR(p, q);
        }
        p ++;
    }

    if (impos) {
        while (*p) {
            p ++;
        }
        p -= 2;
        while (p >= s) {
            printf("Dump %c: %s\n", *p, s);
            if (*p == *(p + 1)) {
                char* q = p - 1;
                while (q >= s) {
                    if (*q != *p) {
                        break;
                    }
                    q --;
                }
                if (q < s) {
                    //printf("Impossible 1\n");
                    return "";
                }
                printf("Found q: %c\n", *q);
                SWAPCHAR(p, q);
            }
            p --;
        }
    }

    return s;
}

int findMaxI(int* ary, int n, int exclude) {
    int maxI = -1;
    for (int i = 0; i < n; i++) {
        if (ary[i] > 0) {
            if (exclude != -1 && i == exclude) {
                continue;
            }
            if (maxI == -1) {
                maxI = i;
            } else {
                if (ary[i] > ary[maxI]) {
                    maxI = i;
                }
            }
        }
    }
    printf("Get max: %d(%c)\n", maxI, maxI == -1 ? '.' : 'a' + maxI);
    return maxI;
}

char* reorganizeStringSimone(char* s) {
    int freqAry[26] = {0};

    int strlen = 0;
    char* p = s;
    while (*p) {
        freqAry[*p - 'a'] ++;
        strlen ++;
        p ++;
    }

    char* newS = (char*)malloc((strlen + 1) * sizeof(char));
    char* pNew = newS;

    int maxI = findMaxI(freqAry, 26, -1);
    while (maxI != -1) {
        *pNew = 'a' + maxI;
        pNew ++;
        freqAry[maxI] --;
        maxI = findMaxI(freqAry, 26, maxI);
    }
    *pNew = '\0';
    if (pNew - newS < strlen) {
        printf("Not enough: %s\n", newS);
        free(newS);
        return "";
    }

    return newS;
}

typedef struct {
    char ch;
    int freq;
} CharFreq;

int compareChatGPTLT767(const void *a, const void *b) {
    return ((CharFreq *)b)->freq - ((CharFreq *)a)->freq;
}

char* reorganizeStringCharGPT(char* s) {
    int len = strlen(s);
    if (len <= 1) return s;

    CharFreq count[26] = {0};
    for (int i = 0; i < 26; i++) {
        count[i].ch = 'a' + i;
        count[i].freq = 0;
    }

    for (int i = 0; i < len; i++) {
        count[s[i] - 'a'].freq++;
    }

    qsort(count, 26, sizeof(CharFreq), compareChatGPTLT767);

    if (count[0].freq > (len + 1) / 2) {
        return "";
    }

    char *result = (char *)malloc(len + 1);
    if (!result) return "";

    int idx = 0;
    for (int i = 0; i < 26; i++) {
        while (count[i].freq > 0) {
            if (idx >= len) {
                idx = 1;
            }
            result[idx] = count[i].ch;
            idx += 2;
            count[i].freq--;
        }
    }

    result[len] = '\0';
    return result;
}
