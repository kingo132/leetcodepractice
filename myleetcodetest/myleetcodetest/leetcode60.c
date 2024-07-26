//
//  leetcode60.c
//  myleetcodetest
//
//  Created by jason on 2024-07-25.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode60.h"


void swapLT60(char* a, char* b) {
    if (a == b) {
        return;
    }
    char t = *a;
    *a = *b;
    *b = t;
}

void dumpAryLT60(char* ary, int n) {
    for (int i = 0; i < n; i++) {
        printf("%c ", ary[i]);
    }
    printf("\n");
}

void permuRecursive(char* ary, int s, int e) {
    if (s == e) {
        dumpAryLT60(ary, e + 1);
        return;
    }

    for (int i = s; i <= e; i++) {
        swapLT60(&ary[s], &ary[i]);
        permuRecursive(ary, s + 1, e);
        swapLT60(&ary[s], &ary[i]);
    }
}

void reverseLT60(char* ary, int s, int e) {
    while (s < e) {
        swapLT60(&ary[s], &ary[e]);
        s++;
        e--;
    }
}

bool nextpermu(char* ary, int n) {
    int i = n - 2;
    while (i >= 0 && ary[i] >= ary[i+1]) {
        i--;
    }

    if (i < 0) {
        return false;
    }

    int j = n - 1;
    while (ary[j] <= ary[i]) {
        j--;
    }

    swapLT60(&ary[i], &ary[j]);
    reverseLT60(ary, i + 1, n - 1);
    return true;
}

char* getPermutation(int n, int k) {
    char* ary = (char*)malloc((n + 1) * sizeof(char));
    for (int i = 0; i < n; i++) {
        ary[i] = '0' + i + 1;
    }
    ary[n] = '\0';

    //permuRecursive(ary, 0, n - 1);
    
    do {
        //dumpAry(ary, n);
        k--;
        if (k <= 0) {
            return ary;
        }
    } while (nextpermu(ary, n));

    free(ary);
    return NULL;
}
