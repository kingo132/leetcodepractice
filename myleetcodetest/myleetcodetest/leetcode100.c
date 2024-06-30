//
//  leetcode100.c
//  myleetcodetest
//
//  Created by jason on 2024-06-19.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include "leetcode100.h"


struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool isSameTree(struct TreeNode* p, struct TreeNode* q) {
    if (p == NULL) {
        if (q == NULL) {
            return true;
        } else {
            return false;
        }
    } else {
        if (q == NULL) {
            return false;
        } else {
            // continue
        }
    }
    if (p->val != q->val) {
        return false;
    }
    if (! isSameTree(p->left, q->left)) {
        return false;
    }
    return isSameTree(p->right, q->right);
}
