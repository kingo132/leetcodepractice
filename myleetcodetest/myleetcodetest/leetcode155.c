//
//  leetcode155.c
//  myleetcodetest
//
//  Created by jason on 2024-06-16.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "leetcode155.h"

typedef struct {
    int* stack;
    int* minval;
    int top;
} MinStack;


MinStack* minStackCreate() {
    MinStack* s = (MinStack*)malloc(sizeof(MinStack));
    s->stack = (int*)malloc(30000 * sizeof(int));
    s->minval = (int*)malloc(30000 * sizeof(int));
    s->top = 0;
    return s;
}

void dumpStackLT155(MinStack* obj) {
    for (int i = 0; i < obj->top; i++) {
        printf("%d,%d ", obj->stack[i], obj->minval[i]);
    }
    printf("\n");
}

void minStackPush(MinStack* obj, int val) {
    obj->stack[obj->top] = val;
    if (obj->top == 0) {
        obj->minval[obj->top] = val;
    } else {
        if (val < obj->minval[obj->top - 1]) {
            obj->minval[obj->top] = val;
        } else {
            obj->minval[obj->top] = obj->minval[obj->top - 1];
        }
    }
    obj->top ++;
    //dumpStackLT113(obj);
}

void minStackPop(MinStack* obj) {
    obj->top --;
}

int minStackTop(MinStack* obj) {
    return obj->stack[obj->top - 1];
}

int minStackGetMin(MinStack* obj) {
    return obj->minval[obj->top - 1];
}

void minStackFree(MinStack* obj) {
    free(obj->stack);
    free(obj);
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, val);
 
 * minStackPop(obj);
 
 * int param_3 = minStackTop(obj);
 
 * int param_4 = minStackGetMin(obj);
 
 * minStackFree(obj);
*/
