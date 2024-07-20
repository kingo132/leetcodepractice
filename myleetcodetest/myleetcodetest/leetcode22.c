#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

typedef struct {
    char* rst;
    int idx;
    int v;
} QueNode;

void dumpQue(const char* prefix, QueNode* que, int front, int tail, int queSize, int maxQueSize) {
    printf("%s", prefix);
    for (int i = 0; i < queSize; i++) {
        int idx = (front + i) % maxQueSize;
        que[idx].rst[que[idx].idx] = '\0';
        printf("[%s,%d,%d], ", que[idx].rst, que[idx].idx, que[idx].v);
    }
    printf("\n");
}

char** generateParenthesis(int n, int* returnSize) {
    int sz = 1;
    for (int i = 0; i < n; i++) {
        sz *= 2;
    }
    sz = 10000;
    
    char** retAry = (char**)malloc(sz * sizeof(char*));
    for (int i = 0; i < sz; i++) {
        retAry[i] = malloc((n * 2 + 1) * sizeof(char));
    }
    *returnSize = 0;

    int maxQueSize = 10000;
    QueNode* que = (QueNode*)malloc(maxQueSize * sizeof(QueNode));
    int front = 0, tail = 0, queSize = 0;
    for (int i = 0; i < maxQueSize; i++) {
        que[i].rst = malloc((n * 2 + 1) * sizeof(char));
        que[i].idx = 0;
        que[i].v = 0;
    }

    que[tail].v = 0;
    tail++;
    queSize++;
    while (queSize > 0) {
        char* rst = que[front].rst;
        int idx = que[front].idx;
        int v = que[front].v;
        front = (front + 1) % maxQueSize;
        queSize--;

        if (idx >= n * 2) {
            rst[idx] = '\0';
            if (v == 0) {
                // output
                printf("Got: %s\n", rst);
                memcpy(retAry[*returnSize], rst, idx + 1);
                (*returnSize)++;
            } else {
                printf("Ivd: %s, v: %d\n", rst, v);
            }
            continue;
        }

        if (v == 0) {
            // only (
            rst[idx] = '(';
            memcpy(que[tail].rst, rst, idx + 1);
            que[tail].idx = idx + 1;
            que[tail].v = v + 1;
            tail = (tail + 1) % maxQueSize;
            queSize++;
        } else if (v > 0) {
            if (v < n * 2 - idx) {
                // ( or )
                rst[idx] = '(';
                memcpy(que[tail].rst, rst, idx + 1);
                que[tail].idx = idx + 1;
                que[tail].v = v + 1;
                tail = (tail + 1) % maxQueSize;
                queSize++;

                rst[idx] = ')';
                memcpy(que[tail].rst, rst, idx + 1);
                que[tail].idx = idx + 1;
                que[tail].v = v - 1;
                tail = (tail + 1) % maxQueSize;
                queSize++;
            } else {
                // only )
                rst[idx] = ')';
                memcpy(que[tail].rst, rst, idx + 1);
                que[tail].idx = idx + 1;
                que[tail].v = v - 1;
                tail = (tail + 1) % maxQueSize;
                queSize++;
            }
        } else {
            // pass
        }

        //dumpQue("Que: ", que, front, tail, queSize, maxQueSize);
    }

    for (int i = 0; i < sz; i++) {
        free(que[i].rst);
    }
    free(que);

    return retAry;
}