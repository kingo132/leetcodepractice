//
//  leetcode459.c
//  myleetcodetest
//
//  Created by jason on 2024-06-11.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "leetcode459.h"

bool repeatedSubstringPattern(char* s) {
    int strlen = 0;
    char* p = s;
    while (*p) {
        strlen ++;
        p++;
    }
    
    char* dupS = (char*)malloc((2 * strlen - 1) * sizeof(char));
    p = s + 1;
    int i = 0;
    while (*p) {
        dupS[i++] = *p;
        p++;
    }
    p = s;
    while (*(p + 1)) {
        dupS[i++] = *p;
        p++;
    }
    dupS[i] = '\0';
    printf("Got dup: %s\n", dupS);

    p = dupS;
    while (*p) {
        if (*p == s[0]) {
            int found = 1;
            for (int i = 1; i < strlen; i++) {
                if (*(p + i) != s[i]) {
                    found = 0;
                    break;
                }
            }
            if (found) {
                return true;
            }
        }

        if (p - dupS >= strlen - 2) {
            break;
        }

        p++;
    }

    return false;
}
