//
//  leetcode168.c
//  myleetcodetest
//
//  Created by jason on 2024-06-30.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode168.h"

char* convertToTitle(int columnNumber) {
    char* sAry = (char*)malloc(10000 * sizeof(char));
    int sLen = 0;
    int n = columnNumber;
    while (n > 0) {
        //printf("%c(%d,%d) ", 'A' + ((n - 1) % 26), n, ((n - 1) % 26));
        sAry[sLen++] = 'A' + ((n - 1) % 26);
        n = (n - 1) / 26;
    }
    sAry[sLen] = '\0';
    for (int i = 0; i < sLen / 2; i++) {
        char t = sAry[i];
        sAry[i] = sAry[sLen - 1 - i];
        sAry[sLen - 1 - i] = t;
    }
    return sAry;
}
