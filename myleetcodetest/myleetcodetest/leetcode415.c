//
//  leetcode415.c
//  myleetcodetest
//
//  Created by jason on 2024-06-22.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include "leetcode415.h"

char* addStrings(char* num1, char* num2) {
    char* num1End = num1, * num2End = num2;
    int len1 = 1, len2 = 1;
    while (*(num1End + 1)) {
        num1End ++;
        len1 ++;
    }
    while (*(num2End + 1)) {
        num2End ++;
        len2 ++;
    }

    int malLen = len1 > len2 ? len1 + 2: len2 + 2;
    char* rst = (char*)malloc(malLen * sizeof(char));
    int rstIdx = malLen - 1;
    rst[rstIdx--] = '\0';

    int carryOn = 0;
    while (num1End >= num1 && num2End >= num2) {
        int n1 = *num1End - '0';
        int n2 = *num2End - '0';
        int n = n1 + n2 + carryOn;
        carryOn = n / 10;
        //printf("%d\n", rstIdx);
        rst[rstIdx--] = '0' + n % 10;

        num1End --;
        num2End --;
    }
    while (num1End >= num1) {
        //printf("%d\n", rstIdx);
        rst[rstIdx--] = '0' + (*num1End - '0' + carryOn) % 10;
        carryOn = (*num1End - '0' + carryOn) / 10;
        num1End --;
    }
    while (num2End >= num2) {
        //printf("%d\n", rstIdx);
        rst[rstIdx--] = '0' + (*num2End - '0' + carryOn) % 10;
        carryOn = (*num2End - '0' + carryOn) / 10;
        num2End --;
    }

    if (carryOn > 0) {
        //printf("%d, %d\n", rstIdx, carryOn);
        rst[rstIdx--] = '0' + carryOn;
    }

    if (rstIdx >= 0) {
        for (int i = rstIdx + 1; i < malLen; i++) {
            rst[i - rstIdx - 1] = rst[i];
        }
    }

    return rst;
}

void leetcode415Main(void) {
    printf("%s\n", addStrings("11", "123"));
}
