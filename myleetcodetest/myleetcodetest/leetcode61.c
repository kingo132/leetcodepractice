//
//  leetcode61.c
//  myleetcodetest
//
//  Created by jason on 2024-06-21.
//

#include "leetcode61.h"


struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* rotateRight(struct ListNode* head, int k) {
    if (! head || ! head->next) {
        return head;
    }
    struct ListNode* p = head;
    struct ListNode* pTail = head;

    int listLen = 0;
    while (p) {
        listLen ++;
        if (p->next == NULL) {
            pTail = p;
        }
        p = p->next;
    }
    k %= listLen;

    p = head;
    for (int i = 0; i < listLen - k - 1; i++) {
        p = p->next;
    }

    if (p->next && p->next != head) {
        pTail->next = head;
        head = p->next;
        p->next = NULL;
    }

    return head;
}
