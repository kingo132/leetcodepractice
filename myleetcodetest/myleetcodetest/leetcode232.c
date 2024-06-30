//
//  leetcode232.c
//  myleetcodetest
//
//  Created by jason on 2024-06-16.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "leetcode232.h"

typedef struct {
    int* stack;
    int top1;
    int top2;
    int size;
} MyQueue;


MyQueue* myQueueCreate() {
    MyQueue* mq = (MyQueue*)malloc(sizeof(MyQueue));
    mq->stack = (int*)malloc(100 * sizeof(int));
    mq->top1 = mq->top2 = mq->size = 0;
    return mq;
}

void myQueuePush(MyQueue* obj, int x) {
    obj->stack[obj->top1++] = x;
    obj->size ++;
}

int myQueuePop(MyQueue* obj) {
    obj->size --;
    return obj->stack[obj->top2++];
}

int myQueuePeek(MyQueue* obj) {
    return obj->stack[obj->top2];
}

bool myQueueEmpty(MyQueue* obj) {
    return obj->size == 0;
}

void myQueueFree(MyQueue* obj) {
    free(obj->stack);
    free(obj);
}

/**
 * Your MyQueue struct will be instantiated and called as such:
 * MyQueue* obj = myQueueCreate();
 * myQueuePush(obj, x);
 
 * int param_2 = myQueuePop(obj);
 
 * int param_3 = myQueuePeek(obj);
 
 * bool param_4 = myQueueEmpty(obj);
 
 * myQueueFree(obj);
*/
