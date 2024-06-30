//
//  leetcode2.c
//  myleetcodetest
//
//  Created by jason on 2024-06-17.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "leetcode2.h"

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* addTwoNumbersLT2(struct ListNode* l1, struct ListNode* l2) {
    int carryOn = 0;
    struct ListNode* p1 = l1, * p2 = l2;
    struct ListNode* pPrev = NULL;
    struct ListNode* pHead = NULL;
    while (p1 && p2) {
        int v = p1->val + p2->val;
        struct ListNode* p = (struct ListNode*)malloc(sizeof(struct ListNode));
        p->val = (v + carryOn) % 10;
        p->next = NULL;
        carryOn = (v + carryOn) / 10;

        if (pPrev != NULL) {
            pPrev->next = p;
        } else {
            pHead = p;
        }
        pPrev = p;
        p1 = p1->next;
        p2 = p2->next;
    }
    while (p1) {
        int v = p1->val;
        struct ListNode* p = (struct ListNode*)malloc(sizeof(struct ListNode));
        p->val = (v + carryOn) % 10;
        p->next = NULL;
        carryOn = (v + carryOn) / 10;

        if (pPrev != NULL) {
            pPrev->next = p;
        } else {
            pHead = p;
        }
        pPrev = p;
        p1 = p1->next;
    }
    while (p2) {
        int v = p2->val;
        struct ListNode* p = (struct ListNode*)malloc(sizeof(struct ListNode));
        p->val = (v + carryOn) % 10;
        p->next = NULL;
        carryOn = (v + carryOn) / 10;

        if (pPrev != NULL) {
            pPrev->next = p;
        } else {
            pHead = p;
        }
        pPrev = p;
        p2 = p2->next;
    }

    if (carryOn > 0) {
        struct ListNode* p = (struct ListNode*)malloc(sizeof(struct ListNode));
        p->val = carryOn;
        p->next = NULL;
        
        if (pPrev != NULL) {
            pPrev->next = p;
        }
        pPrev = p;
    }

    return pHead;
}
