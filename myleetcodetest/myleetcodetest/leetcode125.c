//
//  leetcode125.c
//  myleetcodetest
//
//  Created by jason on 2024-06-14.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "leetcode125.h"

char lowerAlpha(char c) {
    if (c >= 'A' && c <= 'Z') {
        return 'a' + (c - 'A');
    } else if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
        return c;
    }

    return 0;
}

bool isPalindrome(char* s) {
    char* pRight = s;
    while (*(pRight + 1)) {
        pRight ++;
    }

    char* pLeft = s;
    while (pLeft < pRight) {
        char l = lowerAlpha(*pLeft);
        if (l == 0) {
            pLeft ++;
            continue;
        }
        char r = lowerAlpha(*pRight);
        if (r == 0) {
            pRight --;
            continue;
        }
        if (l != r) {
            return false;
        }
        pLeft ++;
        pRight --;
    }

    return true;
}
