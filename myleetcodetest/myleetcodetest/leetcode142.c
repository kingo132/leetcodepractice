//
//  leetcode142.c
//  myleetcodetest
//
//  Created by jason on 2024-06-11.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "leetcode142.h"


struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *detectCycleMy(struct ListNode *head) {
    struct ListNode *p1 = head, *p2 = head;
    while (p1 && p2 && p2->next) {
        if (p2->next == p1 || p2->next->next == p1) {
            printf("Found circle, p1 %d, p2 %d, p2->next: %d\n", p1->val, p2->val, p2->next->val);
            break; // Found circle
        }
        p1 = p1->next;
        p2 = p2->next->next;
    }

    if (p2 && p2->next) {
        // Try to search the circle head
        struct ListNode *cycleHead = head;
        do {
            //printf("Try circle head: %d\n", cycleHead->val);
            struct ListNode *p = p1;
            do {
                if (p == cycleHead) {
                    //printf("Found circle head: %d\n", p->val);
                    return cycleHead;
                }
                p = p->next;
            } while (p != p1);
            cycleHead = cycleHead->next;
        } while (true);
    }

    return NULL;
}

// 1. 两个节点肯定会相遇，不会跳过去。（为啥？）
// 2. 从头开始找到相遇点，肯定是循环起始节点。（？？？）
struct ListNode *detectCycle(struct ListNode *head) {
    struct ListNode *p1 = head, *p2 = head;
    while (p2 && p2->next) {
        p1 = p1->next;
        p2 = p2->next->next;
        if (p2 == p1) {
            printf("Found circle, p1 %d, p2 %d, p2->next: %d\n", p1->val, p2->val, p2->next->val);
            break; // Found circle
        }
    }

    if (p2 && p2->next) {
        // Try to search the circle head
        struct ListNode *cycleHead = head;
        while (cycleHead != p1) {
            printf("Try circle: %d %d\n", cycleHead->val, p1->val);
            cycleHead = cycleHead->next;
            p1 = p1->next;
        }
        return cycleHead;
    }

    return NULL;
}

struct ListNode *detectCycleChatGPT(struct ListNode *head) {
    if (!head || !head->next) {
        return NULL;
    }

    struct ListNode *slow = head;
    struct ListNode *fast = head;

    // Detect cycle using Floyd's Tortoise and Hare algorithm
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            break;
        }
    }

    // If there's no cycle
    if (!fast || !fast->next) {
        return NULL;
    }

    printf("Found circle, p1 %d, p2 %d, p2->next: %d\n", slow->val, fast->val, fast->next->val);

    // Find the start of the cycle
    slow = head;
    while (slow != fast) {
        printf("Try circle: %d %d\n", fast->val, slow->val);
        slow = slow->next;
        fast = fast->next;
    }

    return slow;
}
