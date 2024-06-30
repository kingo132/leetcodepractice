//
//  leetcode848.c
//  myleetcodetest
//
//  Created by jason on 2024-06-11.
//

#include "leetcode848.h"

char* shiftingLetters(char* s, int* shifts, int shiftsSize) {
    long shift = 0;
    for (int i = shiftsSize - 1; i >= 0; i--) {
        shift += shifts[i];

        int v = s[i] - 'a';
        v = (v + shift) % 26;
        s[i] = 'a' + v;
    }

    return s;
}
