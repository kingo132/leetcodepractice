#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    struct ListNode* p1 = list1, * p2 = list2, * head = NULL, * ph = NULL;

    while (p1 && p2) {
        //printf("%d <-> %d, ph: %d, head: %d\n", p1->val, p2->val, ph ? ph->val : -1, head ? head->val : -1);
        if (p1->val > p2->val) {
            if (ph == NULL) {
                ph = p2;
                head = p2;
            } else {
                ph->next = p2;
                ph = p2;
            }
            p2 = p2->next;
        } else {
            if (ph == NULL) {
                ph = p1;
                head = p1;
            } else {
                ph->next = p1;
                ph = p1;
            }
            p1 = p1->next;
        }
    }

    //printf("ph: %d, head: %d\n", ph ? ph->val : -1, head ? head->val : -1);
    if (p1 != NULL) {
        if (ph) {
            ph->next = p1;
        } else {
            head = p1;
        }
    } else if (p2 != NULL) {
        if (ph) {
            ph->next = p2;
        } else {
            head = p2;
        }
    }

    return head;
}