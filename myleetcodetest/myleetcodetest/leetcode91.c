//
//  leetcode91.c
//  myleetcodetest
//
//  Created by jason on 2024-06-18.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include "leetcode91.h"

typedef struct {
    int key;
    int val;
    int isOccupied;
} HASHNODE;

void insertHashLT91(HASHNODE* hashAry, int maxHashSize, char* s, int val) {
    int key = 0;
    char* p = s;
    while (*p) {
        key = (key + *p) % maxHashSize;
        p ++;
    }

    int i = 0;
    for (; i < maxHashSize; i++) {
        if (hashAry[key].isOccupied == 0) {
            hashAry[key].key = key;
            hashAry[key].val = val;
            hashAry[key].isOccupied = 1;
            break;
        }
        key = (key + 1) % maxHashSize;
    }
    
    if (i == maxHashSize) {
        printf("Hash is full");
    }
}

int getFromHash(HASHNODE* hashAry, int maxHashSize, char* s) {
    int key = 0;
    char* p = s;
    while (*p) {
        key = (key + *p) % maxHashSize;
        p ++;
    }

    for (int i = 0; i < maxHashSize; i++) {
        if (hashAry[key].isOccupied) {
            if (hashAry[key].key == key) {
                return hashAry[key].val;
            }
        } else {
            break;
        }
        key = (key + 1) % maxHashSize;
    }
    
    return -1;
}

int numDecodingsHelper(HASHNODE* hashAry, int maxHashSize, char* s) {
    if (! s || ! *s) {
        return 1;
    }

    int fromHash = getFromHash(hashAry, maxHashSize, s);
    if (fromHash != -1) {
        return fromHash;
    }

    // 2 more char
    int sum = 0;
    if (*s && *s >= '1' && *s <= '9') {
        sum += numDecodingsHelper(hashAry, maxHashSize, s + 1);
    }
    if (*(s + 1) && (*s == '1' || (*s == '2' && *(s + 1) <= '6'))) {
        sum += numDecodingsHelper(hashAry, maxHashSize, s + 2);
    }
    insertHashLT91(hashAry, maxHashSize, s, sum);
    //printf("Str: %s, cnt: %d\n", s, sum);
    return sum;
}

int numDecodings(char* s) {
    int maxHashSize = 10000;
    HASHNODE* hashAry = (HASHNODE*)malloc(maxHashSize * sizeof(HASHNODE));
    for (int i = 0; i < maxHashSize; i++) {
        hashAry[i].isOccupied = 0;
    }

    int ret = numDecodingsHelper(hashAry, maxHashSize, s);

    free(hashAry);
    return ret;
}
