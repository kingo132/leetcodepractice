//
//  leetcode171.c
//  myleetcodetest
//
//  Created by jason on 2024-06-13.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "leetcode171.h"

int titleToNumber(char* columnTitle) {
    char* pEnd = columnTitle;
    while (*pEnd) {
        pEnd ++;
    }
    char* p = pEnd - 1;
    int ret = 0;
    while (p >= columnTitle) {
        int v = *p - 'A' + 1;

        int base = 1;
        for (int i = 0; i < pEnd - p - 1; i++) {
            base *= 26;
        }
        
        ret += v * base;
        
        p --;
    }
    return ret;
}
