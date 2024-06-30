//
//  leetcode3.c
//  myleetcodetest
//
//  Created by jason on 2024-06-22.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

#include "leetcode3.h"

int lengthOfLongestSubstring(char* s) {
    if (! s || *s == 0) {
        return 0;
    }

    char* pSubStart = s, * pSubEnd = s;
    char* p = s;

    char* ocrIdx[512];
    memset(&ocrIdx, 0, 512 * sizeof(char*));

    int maxLen = 0;
    while (*p) {
        if (ocrIdx[(unsigned char)(*p)] != NULL) {
            if (pSubEnd - pSubStart > maxLen) {
                printf("Max (%d-%d)=%d at %d, occr: %d\n", pSubEnd - s, pSubStart - s, pSubEnd - pSubStart, p - s, ocrIdx[(unsigned char)(*p)] - s);
                maxLen = pSubEnd - pSubStart;
            }
            
            p = ocrIdx[(unsigned char)(*p)] + 1;
            pSubStart = p;
            pSubEnd = p;

            memset(&ocrIdx, 0, 512 * sizeof(char*));
        } else {
            ocrIdx[(unsigned char)(*p)] = p;
            pSubEnd ++;
            p ++;
        }
    }

    printf("Final (%d-%d)=%d\n", pSubEnd - s, pSubStart - s, pSubEnd - pSubStart);
    return pSubEnd - pSubStart > maxLen ? pSubEnd - pSubStart : maxLen;
}

void leetcode3Main(void) {
    printf("%d\n", lengthOfLongestSubstring("ohomm"));
}
