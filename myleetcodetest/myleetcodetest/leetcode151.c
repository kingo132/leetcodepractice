//
//  leetcode151.c
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

#include "leetcode151.h"

char* reverseWords(char* s) {
    int lens = 0;
    char* p = s;
    while (*p) {
        lens ++;
        p++;
    }
    char* newStr = malloc(lens + 1);
    short wordsIdxIdx = 0;
    short* wordsIdx = malloc(lens * 2 * sizeof(short));

    p = s;
    bool inWord = false;
    int i = 0;
    while (*p) {
        if (*p == ' ') {
            if (inWord) {
                // end
                wordsIdx[wordsIdxIdx] = i;
                wordsIdxIdx ++;
                inWord = false;
            } else {
                // dup space, skip
            }
        } else {
            if (! inWord) {
                // start
                wordsIdx[wordsIdxIdx] = i;
                wordsIdxIdx ++;
            } else {
                // in word, skip
            }
            inWord = true;
        }
        p ++;
        i ++;
    }
    if (wordsIdxIdx % 2 != 0) {
        // add last index
        wordsIdx[wordsIdxIdx] = i;
        wordsIdxIdx ++;
    }

    for (int i = 0; i < wordsIdxIdx; i++) {
        printf("%d ", wordsIdx[i]);
    }

    // copy words
    i = 0;
    wordsIdxIdx --;
    while (wordsIdxIdx > 0) {
        short ss = wordsIdx[wordsIdxIdx - 1];
        short se = wordsIdx[wordsIdxIdx];
        do {
            printf("newStr[%d] = %c\n", i, s[ss]);
            newStr[i] = s[ss];
            i ++;

            ss ++;
        } while (ss != se);
        
        printf("newStr[%d] = space\n", i);
        newStr[i] = ' ';
        i ++;
        printf("wordsIdxIdx: %d\n", wordsIdxIdx);
        wordsIdxIdx -= 2;
    }

    newStr[i - 1] = 0;
    return newStr;
}
