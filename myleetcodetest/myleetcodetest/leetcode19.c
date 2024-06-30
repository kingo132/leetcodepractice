//
//  leetcode19.c
//  myleetcodetest
//
//  Created by jason on 2024-06-22.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include "leetcode19.h"

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    struct ListNode dummyHead;
    dummyHead.next = head;
    struct ListNode* slow = &dummyHead, * fast = &dummyHead;
    while (n > 0) {
        if (fast == NULL) {
            return NULL;
        }
        fast = fast->next;
        n --;
    }

    while (fast->next) {
        slow = slow->next;
        fast = fast->next;
    }

    struct ListNode* tmp = slow->next;
    slow->next = tmp->next;
    free(tmp);
    return dummyHead.next;
}
