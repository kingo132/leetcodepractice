//
//  leetcode206.c
//  myleetcodetest
//
//  Created by jason on 2024-06-29.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#include "leetcode206.h"


// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* p = head;
    struct ListNode* newHead = NULL;
    while (p) {
        struct ListNode* tmp = p->next;
        p->next = newHead;
        newHead = p;
        p = tmp;
    }
    return newHead;
}
