//
//  leetcode69.c
//  myleetcodetest
//
//  Created by jason on 2024-06-13.
//

#include "leetcode69.h"

int mySqrt(int x) {
    if (x == 0 || x == 1) {
        return x;
    }
    long i = x;
    while (i * i >= x) {
        i /= 2;
    }
    //printf("xx i: %d\n", i);
    for (; i < x; i++) {
        if (i * i > x) {
            break;
        }
    }

    //printf("yy i: %d\n", i);
    return (int)(i - 1);
}
