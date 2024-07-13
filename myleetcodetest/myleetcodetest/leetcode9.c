//
//  leetcode9.c
//  myleetcodetest
//
//  Created by jason on 2024-07-10.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode9.h"

bool isPalindromeLT9(int x) {
    if (x < 0) {
        return false;
    } else if (x == 0) {
        return true;
    }
    char numAry[12];
    int numLen = 0;
    while (x > 0) {
        numAry[numLen++] = x % 10;
        x /= 10;
    }

    int l = 0, r = numLen - 1;
    while (l <= r) {
        if (numAry[l] != numAry[r]) {
            return false;
        }
        l++;
        r--;
    }

    return true;
}
