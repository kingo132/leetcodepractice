//
//  leetcode101.c
//  myleetcodetest
//
//  Created by jason on 2024-06-20.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include "leetcode101.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool isSameCopy(struct TreeNode* root1, struct TreeNode* root2) {
    if (root1 == NULL) {
        if (root2 == NULL) {
            return true;
        } else {
            return false;
        }
    } else {
        if (root2 == NULL) {
            return false;
        } else {
            // continue;
        }
    }

    if (root1->val != root2->val) {
        return false;
    }
    if (! isSameCopy(root1->left, root2->right)) {
        return false;
    }
    return isSameCopy(root1->right, root2->left);
}

bool isSymmetric(struct TreeNode* root) {
    return isSameCopy(root->left, root->right);
}
