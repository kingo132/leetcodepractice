//
//  leetcode470.c
//  myleetcodetest
//
//  Created by jason on 2024-06-28.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#include "leetcode470.h"

int rand7() {
    return rand() % 7;
}

// The rand7() API is already defined for you.
// int rand7();
// @return a random integer in the range 1 to 7

int rand10Simone() {
    static long b = 0;
    int r = (rand7() * rand7()+rand7() * rand7()* rand7()+rand7()+rand7() * rand7()* rand7()*rand7())*1.5;
    //b = b ^ ((long)1 << r);
    int ret = 1 + (r % 10);
    //printf("%d, %ld, %ld = %d\n", r, ((long)1 << r), b, ret);
    //printf("%d = %d\n", r, ret);
    return ret;
}

int rand10() {
    static int i = 0;
    return 1 + ((i++) * 7 + rand7()) % 10;
}

int rand10ChatGPT() {
    int num;
    do {
        num = (rand7() - 1) * 7 + rand7(); // Generate numbers from 1 to 49
    } while (num > 40); // Discard numbers greater than 40

    return (num - 1) % 10 + 1; // Map to 1-10
}
