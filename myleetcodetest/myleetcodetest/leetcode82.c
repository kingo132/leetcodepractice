//
//  leetcode82.c
//  myleetcodetest
//
//  Created by jason on 2024-06-11.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "leetcode82.h"

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* deleteDuplicates(struct ListNode* head) {
    struct ListNode dummyNode;
    dummyNode.val = -1;
    dummyNode.next = head;

    struct ListNode* p = &dummyNode;
    while (p && p->next && p->next->next) {
        if (p->next->val == p->next->next->val) {
            int val = p->next->val;
            while (p->next && p->next->val == val) {
                struct ListNode* tmp = p->next;
                p->next = tmp->next;
                //free(tmp);
            }
        } else {
            p = p->next;
        }
    }

    return dummyNode.next;
}
