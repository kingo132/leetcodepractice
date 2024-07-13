//
//  leetcode17.c
//  myleetcodetest
//
//  Created by jason on 2024-07-11.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode17.h"

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

typedef struct {
    int dictIdx;
    int dictStrIdx;
    char* retStr;
    int retStrIdx;
} QueNode;

char** letterCombinations(char* digits, int* returnSize) {
    *returnSize = 0;
    if (*digits == '\0') {
        return NULL;
    }

    int len = 0;
    char* p = digits;
    while (*p) {
        len++;
        p++;
    }

    char* dict[] = {
        "abc", // 0 - 2
        "def", // 1 - 3
        "ghi", // 2 - 4
        "jkl", // 3 - 5
        "mno", // 4 - 6
        "pqrs", // 5 - 7
        "tuv", // 6 - 8
        "wxyz" // 7 - 9
        };
    
    int totalCnt = 1;
    for (int i = 0; i < len; i++) {
        if (digits[i] == '7' || digits[i] == '9') {
            totalCnt *= 4;
        } else {
            totalCnt *= 3;
        }
    }
    printf("totalCnt: %d, len: %d\n", totalCnt, len);
    char** ret = (char**)malloc(totalCnt * sizeof(char*));
    //for (int i = 0; i < totalLCnt; i++) {
    //    ret[i] = (char*)malloc((len + 1) * sizeof(char));
    //}

    QueNode* que = (QueNode*)malloc(totalCnt * sizeof(QueNode));
    int front = 0, tail = 0, queSize = 0;
    for (int i = 0; i < totalCnt; i++) {
        que[i].retStr = (char*)malloc((len + 1) * sizeof(char));
        que[i].retStrIdx = 0;
    }

    int l = 3;
    if (digits[0] == '7' || digits[0] == '9') {
        l = 4;
    }
    for (int i = 0; i < l; i++) {
        que[tail].dictIdx = digits[0] - '2';
        que[tail].dictStrIdx = i;
        que[tail].retStr[que[tail].retStrIdx++] = dict[que[tail].dictIdx][que[tail].dictStrIdx];
        tail = (tail + 1) % totalCnt;
        queSize++;
    }

    while (queSize > 0) {
        int dictIdx = que[front].dictIdx;
        int dictStrIdx = que[front].dictStrIdx;
        char* retStr = que[front].retStr;
        int retStrIdx = que[front].retStrIdx;
        queSize--;
        front = (front + 1) % totalCnt;

        if (retStrIdx >= len) {
            retStr[retStrIdx] = '\0';
            //printf("Found: %s\n", retStr);
            ret[*returnSize] = (char*)malloc((len + 1) * sizeof(char));
            for (int i = 0; i < len; i++) {
                ret[*returnSize][i] = retStr[i];
            }
            ret[*returnSize][len] = '\0';
            (*returnSize)++;
            continue;
        }

        l = 3;
        if (digits[retStrIdx] == '7' || digits[retStrIdx] == '9') {
            l = 4;
        }
        for (int i = 0; i < l; i++) {
            que[tail].dictIdx = digits[retStrIdx] - '2';
            que[tail].dictStrIdx = i;
            for (int j = 0; j < retStrIdx; j++) {
                que[tail].retStr[j] = retStr[j];
            }
            que[tail].retStrIdx = retStrIdx;
            que[tail].retStr[que[tail].retStrIdx++] = dict[que[tail].dictIdx][que[tail].dictStrIdx];
            tail = (tail + 1) % totalCnt;
            queSize++;
        }
    }

    return ret;
}
