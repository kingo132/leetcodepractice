//
//  leetcode445.c
//  myleetcodetest
//
//  Created by jason on 2024-06-14.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "leetcode445.h"


struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode** stack1 = malloc(100 * sizeof(struct ListNode*));
    struct ListNode** stack2 = malloc(100 * sizeof(struct ListNode*));
    int* stack3 = malloc(100 * sizeof(int));
    int top1 = 0, top2 = 0, top3 = 0;

    struct ListNode* p = l1;
    while (p) {
        stack1[top1++] = p;
        p = p->next;
    }
    p = l2;
    while (p) {
        stack2[top2++] = p;
        p = p->next;
    }

    int carryOn = 0;
    while (top1 > 0 && top2 > 0) {
        int v = stack1[--top1]->val + stack2[--top2]->val;
        stack3[top3++] = (v + carryOn) % 10;
        carryOn = (v + carryOn) / 10;
    }
    while (top1 > 0) {
        int v = stack1[--top1]->val;
        stack3[top3++] = (v + carryOn) % 10;
        carryOn = (v + carryOn) / 10;

    }
    while (top2 > 0) {
        int v = stack2[--top2]->val;
        stack3[top3++] = (v + carryOn) % 10;
        carryOn = (v + carryOn) / 10;
    }
    if (carryOn > 0) {
        stack3[top3++] = carryOn;
        carryOn = 0;
    }

    struct ListNode* retHead = malloc(sizeof(struct ListNode));
    retHead->val = stack3[--top3];
    struct ListNode* prev = retHead;
    while (top3 > 0) {
        struct ListNode* node = malloc(sizeof(struct ListNode));
        node->val = stack3[--top3];
        prev->next = node;
        prev = node;
    }
    prev->next = NULL;

    free(stack1);
    free(stack2);
    free(stack3);

    return retHead;
}
