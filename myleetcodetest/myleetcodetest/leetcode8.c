//
//  leetcode8.c
//  myleetcodetest
//
//  Created by jason on 2024-06-30.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#include "leetcode8.h"

int myAtoi(char* s) {
    int sign = 0;
    long ret = 0;
    char* p = s;
    while (*p) {
        if (*p == ' ') {
            if (sign != 0) {
                break;
            }
        } else if (*p == '-') {
            if (sign != 0) {
                break;
            }
            sign = -1;
        } else if (*p == '+') {
            if (sign != 0) {
                break;
            }
            sign = 1;
        } else if (*p >= '0' && *p <= '9') {
            if (sign == 0) {
                sign = 1;
            }

            ret = ret * 10 + (*p - '0');
            if (sign == -1 && -ret <= INT_MIN) {
                sign = 1;
                ret = INT_MIN;
                break;
            } else if (ret > INT_MAX) {
                ret = INT_MAX;
                break;
            }
        } else {
            break;
        }
        p++;
    }

    return (int)(sign * ret);
}
