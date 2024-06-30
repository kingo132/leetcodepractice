//
//  leetcode400.c
//  myleetcodetest
//
//  Created by jason on 2024-06-20.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include "leetcode400.h"


// 1~9, 10~99, 100~999, 1000~9999 ...
// Si = ((9 * i - 1) * 10 ^ i + 1) / 9
// S1 = 9, S2 = 9 + 90 * 2 = 189
// ...

unsigned long long powLT400(unsigned long long n, int p) {
    unsigned long long po = 1;
    while (p > 0) {
        po *= n;
        p --;
    }
    return po;
}

double siLT400(int i) {
    return ((9 * i - 1) * powLT400(10, i) + 1) / (double)9.0;
}

int findNthDigit(int n) {
    int i = 1;
    unsigned long long si_1 = siLT400(i - 1);
    unsigned long long si = siLT400(i);
    while (si < n) {
        i ++;
        si_1 = si;
        si = siLT400(i);
    }
    unsigned long long delta = n - si_1 - 1;
    unsigned long long a = delta / i;
    unsigned long long b = delta % i;
    unsigned long long num = powLT400(10, i - 1) + a;
    unsigned long long dig = (num / powLT400(10, i - b - 1)) % 10;
    printf("i: %d, si_1: %d, si: %d, delta: %d, a: %d, b: %d, num: %d, dig: %d\n", i, si_1, si, delta, a, b, num, dig);
    return dig;
}
