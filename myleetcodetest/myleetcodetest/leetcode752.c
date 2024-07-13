//
//  leetcode752.c
//  myleetcodetest
//
//  Created by jason on 2024-07-10.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode752.h"

typedef struct {
    char state[5];
    int steps;
} QueNode;

int openLock(char** deadends, int deadendsSize, char* target) {
    int maxQueLen = 100000;
    QueNode* que = (QueNode*)malloc(maxQueLen * sizeof(QueNode));
    int front = 0, tail = 0, queSize = 0;

    int* dpMinStep = (int*)malloc(10000 * sizeof(int));
    for (int i = 0; i < 10000; i++) {
        dpMinStep[i] = INT_MAX;
    }

    int* deadMat = (int*)malloc(10000 * sizeof(int));
    for (int i = 0; i < 10000; i++) {
        deadMat[i] = 0;
    }
    for (int i = 0; i < deadendsSize; i++) {
        deadMat[(deadends[i][0] - '0') * 1000 + (deadends[i][1] - '0') * 100 + (deadends[i][2] - '0') * 10 + (deadends[i][3] - '0')] = 1;
    }

    int minStep = INT_MAX;

    strcpy(que[tail].state, "0000");
    que[tail].steps = 0;
    tail++;
    queSize++;
    while (queSize > 0) {
        char* s = que[front].state;
        int steps = que[front].steps;
        front = (front + 1) % maxQueLen;
        queSize--;

        if (s[0] == target[0] && s[1] == target[1] &&
            s[2] == target[2] && s[3] == target[3]) {
            printf("Found %s, steps: %d\n", s, steps);
            if (steps < minStep) {
                minStep = steps;
            }
            continue;
        }

        if (steps >= minStep) {
            continue;
        }

        if (deadMat[(s[0] - '0') * 1000 + (s[1] - '0') * 100 + (s[2] - '0') * 10 + (s[3] - '0')] != 0) {
            continue;
        }

        if (dpMinStep[(s[0] - '0') * 1000 + (s[1] - '0') * 100 + (s[2] - '0') * 10 + (s[3] - '0')] < minStep) {
            continue;
        }
        dpMinStep[(s[0] - '0') * 1000 + (s[1] - '0') * 100 + (s[2] - '0') * 10 + (s[3] - '0')] = steps;

        //printf("Try %s, steps: %d\n", s, steps);

        for (int i = 0; i < 4; i++) {
            strcpy(que[tail].state, s);
            que[tail].state[i]++;
            if (que[tail].state[i] > '9') {
                que[tail].state[i] = '0';
            }
            que[tail].steps = steps + 1;
            tail = (tail + 1) % maxQueLen;
            queSize++;

            strcpy(que[tail].state, s);
            que[tail].state[i]--;
            if (que[tail].state[i] < '0') {
                que[tail].state[i] = '9';
            }
            que[tail].steps = steps + 1;
            tail = (tail + 1) % maxQueLen;
            queSize++;
        }
    }

    free(que);
    free(dpMinStep);
    free(deadMat);
    return minStep == INT_MAX ? -1 : minStep;
}
