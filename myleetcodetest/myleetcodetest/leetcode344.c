//
//  leetcode344.c
//  myleetcodetest
//
//  Created by jason on 2024-06-29.
//

#include "leetcode344.h"

void reverseString(char* s, int sSize) {
    for (int i = 0; i < sSize / 2; i++) {
        char t = s[i];
        s[i] = s[sSize - i - 1];
        s[sSize - i - 1] = t;
    }
}
