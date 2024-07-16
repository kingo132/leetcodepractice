#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    struct ListNode* head = NULL, *p = NULL;
    while (1) {
        int min = INT_MAX;
        int minIdx = -1;
        for (int i = 0; i < listsSize; i++) {
            if (lists[i] && lists[i]->val < min) {
                min = lists[i]->val;
                minIdx = i;
            }
        }
        if (minIdx == -1) {
            break;
        }
        if (head == NULL) {
            head = lists[minIdx];
        }
        if (p != NULL) {
            p->next = lists[minIdx];
        }
        p = lists[minIdx];
        lists[minIdx] = lists[minIdx]->next;
    }
    return head;
}