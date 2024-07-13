//
//  leetcode173.c
//  myleetcodetest
//
//  Created by jason on 2024-07-07.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode173.h"


//Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};




typedef struct {
    struct TreeNode** stack;
    int top;
} BSTIterator;

int heightOfTheTree(struct TreeNode* root) {
    if (!root->left && !root->right) {
        return 1;
    }
    int hl = 0;
    if (root->left) {
        hl = 1 + heightOfTheTree(root->left);
    }
    int hr = 0;
    if (root->right) {
        hr = 1 + heightOfTheTree(root->right);
    }
    return hl > hr ? hl : hr;
}

BSTIterator* bSTIteratorCreate(struct TreeNode* root) {
    int h = heightOfTheTree(root);
    BSTIterator* bi = (BSTIterator*)malloc(sizeof(BSTIterator));
    bi->stack = (struct TreeNode**)malloc(h * sizeof(struct TreeNode*));
    bi->top = 0;

    while (root) {
        bi->stack[bi->top++] = root;
        root = root->left;
    }

    return bi;
}

int bSTIteratorNext(BSTIterator* obj) {
    if (obj->top > 0) {
        struct TreeNode* ret = obj->stack[--obj->top];
        struct TreeNode* p = ret->right;
        while (p) {
            obj->stack[obj->top++] = p;
            p = p->left;
        }
        return ret->val;
    }
    return -1;
}

bool bSTIteratorHasNext(BSTIterator* obj) {
    return obj->top != 0;
}

void bSTIteratorFree(BSTIterator* obj) {
    free(obj->stack);
    free(obj);
}

/**
 * Your BSTIterator struct will be instantiated and called as such:
 * BSTIterator* obj = bSTIteratorCreate(root);
 * int param_1 = bSTIteratorNext(obj);
 
 * bool param_2 = bSTIteratorHasNext(obj);
 
 * bSTIteratorFree(obj);
*/
