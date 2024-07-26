#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>

// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* createNode(int* ary, int l, int r) {
    if (l > r) {
        return NULL;
    }

    int mid = (l + r) / 2;
    struct TreeNode* n = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    n->val = ary[mid];
    n->left = createNode(ary, l, mid - 1);
    n->right = createNode(ary, mid + 1, r);
    return n;
}

struct TreeNode* sortedListToBST(struct ListNode* head) {
    int* ary = (int*)malloc(100000 * sizeof(int));
    int len = 0;

    struct ListNode* p = head;
    while (p) {
        ary[len++] = p->val;
        p = p->next;
    }

    return createNode(ary, 0, len - 1);
}