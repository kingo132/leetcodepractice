//
//  leetcode1358.c
//  myleetcodetest
//
//  Created by jason on 2024-07-07.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode1358.h"

int numberOfSubstrings(char* s) {
    int sLen = 0;
    char* p = s;
    while (*p) {
        sLen++;
        p++;
    }
    /*int cnt = 0;
    int ary[3];
    for (int i = 0; i < sLen - 2; i++) {
        ary[0] = ary[1] = ary[2] = 0;
        ary[s[i] - 'a']++;
        ary[s[i + 1] - 'a']++;
        for (int j = i + 2; j < sLen; j++) {
            ary[s[j] - 'a']++;
            if (ary[0] > 0 && ary[1] > 0 && ary[2] > 0) {
                //char t = s[j + 1];
                //s[j + 1] = '\0';
                //printf("Found: %s\n", &s[i]);
                //s[j + 1] = t;
                cnt += sLen - j;
                break;
            }
        }
    }
    return cnt;*/
    int* ary = (unsigned int*)malloc(sLen * sizeof(unsigned int));
    int aPos = INT_MAX, bPos = INT_MAX, cPos = INT_MAX;
    for (int i = sLen; i >= 0; i--) {
        if (s[i] == 'a') {
            aPos = i;
            ary[i] = bPos > cPos ? bPos : cPos;
        } else if (s[i] == 'b') {
            bPos = i;
            ary[i] = aPos > cPos ? aPos : cPos;
        } else if (s[i] == 'c') {
            cPos = i;
            ary[i] = aPos > bPos ? aPos : bPos;
        }
    }
    //for (int i = 0; i < sLen; i++) {
    //    printf("%d ", ary[i]);
    //}
    //printf("\n");
    int cnt = 0;
    for (int i = 0; i < sLen; i++) {
        if (ary[i] == INT_MAX) {
            continue;
        }
        cnt += sLen - ary[i];
    }
    return cnt;
}
