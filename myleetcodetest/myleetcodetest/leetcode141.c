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

bool hasCycle(struct ListNode *head) {
    struct ListNode * slow = head, * fast = head;
    while (slow && fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }

    return false;
}