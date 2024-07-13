//
//  leetcode572.c
//  myleetcodetest
//
//  Created by jason on 2024-07-12.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode572.h"


// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};


bool isDistinct(struct TreeNode* r1, struct TreeNode* r2) {
    if (r1 == NULL && r2 == NULL) {
        return true;
    } else if (r1 == NULL) {
        return false;
    } else if (r2 == NULL) {
        return false;
    }
    if (r1->val != r2->val) {
        return false;
    }
    if (r1->left || r2->left) {
        if (!isDistinct(r1->left, r2->left)) {
            return false;
        }
    }
    if (r1->right || r2->right) {
        if (!isDistinct(r1->right, r2->right)) {
            return false;
        }
    }
    return true;
}

bool isSubtree(struct TreeNode* root, struct TreeNode* subRoot) {
    if (root->val == subRoot->val) {
        if (isDistinct(root, subRoot)) {
            return true;
        }
    }
    if (root->left) {
        if (isSubtree(root->left, subRoot)) {
            return true;
        }
    }
    if (root->right) {
        if (isSubtree(root->right, subRoot)) {
            return true;
        }
    }
    return false;
}
