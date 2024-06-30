//
//  leetcode13.c
//  myleetcodetest
//
//  Created by jason on 2024-06-29.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "leetcode13.h"

int romanToInt(char* s) {
    int result = 0;
    
    char* p = s;
    while (*p) {
        switch (*p) {
            case 'I': //
                if (*(p + 1) == 'V') {
                    result += 4;
                    p += 2;
                } else if (*(p + 1) == 'X') {
                    result += 9;
                    p += 2;
                } else {
                    result += 1;
                    p += 1;
                }
                break;
            case 'V':
                result += 5;
                p += 1;
                break;
            case 'X': //
                if (*(p + 1) == 'L') {
                    result += 40;
                    p += 2;
                } else if (*(p + 1) == 'C') {
                    result += 90;
                    p += 2;
                } else {
                    result += 10;
                    p += 1;
                }
                break;
            case 'L':
                result += 50;
                p += 1;
                break;
            case 'C': //
                if (*(p + 1) == 'D') {
                    result += 400;
                    p += 2;
                } else if (*(p + 1) == 'M') {
                    result += 900;
                    p += 2;
                } else {
                    result += 100;
                    p += 1;
                }
                break;
            case 'D':
                result += 500;
                p += 1;
                break;
            case 'M':
                result += 1000;
                p += 1;
                break;
            default:
                return -1;
        }
    }

    return result;
}
