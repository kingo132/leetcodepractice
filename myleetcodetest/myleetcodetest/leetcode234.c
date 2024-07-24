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

bool isPalindrome(struct ListNode* head) {
    if (!head || !head->next) {
        return true;
    }

    struct ListNode* slow = head, * prevSlow = NULL, * fast = head;
    while (fast && fast->next) {
        fast = fast->next->next;

        struct ListNode* t = slow->next;
        slow->next = prevSlow;
        prevSlow = slow;
        slow = t;
    }

    printf("slow: %d, fast: %d\n", slow ? slow->val : -1, fast ? fast->val : -1);
    if (fast) {
        fast = slow->next;
        slow = prevSlow;
    } else {
        fast = slow;
        slow = prevSlow;
    }
    printf("slow: %d, fast: %d\n", slow ? slow->val : -1, fast ? fast->val : -1);

    while (slow && fast) {
        if (slow->val != fast->val) {
            return false;
        }
        slow = slow->next;
        fast = fast->next;
    }

    return true;
}