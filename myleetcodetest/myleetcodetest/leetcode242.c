//
//  leetcode242.c
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

#include "leetcode242.h"

bool isAnagram(char* s, char* t) {
    int cnt[26];
    for (int i = 0; i < 26; i++) {
        cnt[i] = 0;
    }

    char* p = s;
    while (*p) {
        cnt[*p - 'a']++;
        p++;
    }

    p = t;
    while (*p) {
        cnt[*p - 'a']--;
        p++;
    }
    
    for (int i = 0; i < 26; i++) {
        if (cnt[i] != 0) {
            return false;
        }
    }

    return true;
}
