//
//  leetcode6.c
//  myleetcodetest
//
//  Created by jason on 2024-06-29.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#include "leetcode6.h"

// 在草稿纸上列出一些序列，然后可以发现取字母的规律
char* convert(char* s, int numRows) {
    if (numRows == 1) {
        return s;
    }
    char* rst = (char*)malloc(1000 * sizeof(char));
    int rstIdx = 0;

    int n = (numRows - 1) * 2;
    int sLen = 0;
    char* sEnd = s;
    while (*sEnd) {
        sLen ++;
        sEnd ++;
    }

    //printf("%d,%d, %p, %p, %d, %p\n", n, sLen, s, sEnd, rstIdx, rst);//return NULL;
    char* p = s;
    while (p < sEnd) {
        if (rstIdx >= 1000) {
            printf("memory overflow.\n");
            return NULL;
        }
        rst[rstIdx++] = *p;
        p += n;
    }

    for (int i = 0; i < numRows - 2; i++) {
        int itv = n - 2 * (i + 1);
        p = s + i + 1;
        int j = 0;
        while (p < sEnd) {
            if (rstIdx >= 1000) {
                printf("memory overflow.\n");
                return NULL;
            }
            rst[rstIdx++] = *p;
            if (j % 2 == 0) {
                p += itv;
            } else {
                p += n - itv;
            }
            j++;
        }
    }

    p = s + numRows - 1;
    while (p < sEnd) {
        if (rstIdx >= 1000) {
            printf("memory overflow.\n");
            return NULL;
        }
        rst[rstIdx++] = *p;
        p += n;
    }

    rst[rstIdx] = '\0';
    return rst;
}

void leetcode6Main(void) {
    printf("%s\n", convert("PAYPALISHIRING", 4));
}
