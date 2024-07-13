//
//  leetcode138.c
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

#include "leetcode138.h"


// Definition for a Node.
struct Node {
    int val;
    struct Node *next;
    struct Node *random;
};

struct Node* copyRandomListOldNotGood(struct Node* head) {
    if (!head) {
        return NULL;
    }

    int len = 0;
    struct Node* pold = head;
    while (pold) {
        len++;
        pold = pold->next;
    }

    struct Node** ary = (struct Node*)malloc((len + 1) * 2 * sizeof(struct Node*));
    pold = head;
    len = 0;
    while (pold) {
        ary[len * 2] = pold;
        len++;
        pold = pold->next;
    }

    struct Node* newHead = (struct Node*)malloc(sizeof(struct Node));
    newHead->val = head->val;

    ary[2 * len] = NULL;
    ary[2 * len + 1] = NULL;

    pold = head;
    struct Node* pnew = newHead;
    int idx = 0;
    while (pold) {
        if (pold->next) {
            pnew->next = (struct Node*)malloc(sizeof(struct Node));
            pnew->next->val = pold->next->val;
        } else {
            pnew->next = NULL;
        }

        // find idx by old pointer
        int newIdx = -1;
        for (int i = 0; i < len; i++) {
            if (ary[i * 2] == pold->random) {
                newIdx = i * 2 + 1;
                break;
            }
        }
        if (newIdx == -1) {
            pnew->random = (struct Node*)(2 * len + 1);
        } else {
            pnew->random = (struct Node*)(newIdx);
        }

        ary[idx + 1] = pnew;
        
        pold = pold->next;
        pnew = pnew->next;
        idx+=2;
    }

    pnew = newHead;
    while (pnew) {
        int idx = (int)(pnew->random);
        pnew->random = ary[idx];
        pnew = pnew->next;
    }

    free(ary);
    return newHead;
}

struct Node* copyRandomList(struct Node* head) {
    if (!head) {
        return NULL;
    }
    struct Node* p = head;
    while (p) {
        struct Node* n = (struct Node*)malloc(sizeof(struct Node));
        n->val = p->val;
        n->next = p->next;
        n->random = NULL;
        p->next = n;
        p = p->next->next;
    }
    p = head;
    while (p && p->next) {
        if (p->random) {
            p->next->random = p->random->next;
        }
        p = p->next->next;
    }
    struct Node* newHead = head->next;
    p = head;
    while (p && p->next) {
        struct Node* t = p->next->next;
        if (t) {
            p->next->next = t->next;
        }
        p->next = t;
        
        p = t;
    }
    return newHead;
}
