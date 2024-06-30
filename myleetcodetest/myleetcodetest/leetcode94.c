//
//  leetcode94.c
//  myleetcodetest
//
//  Created by jason on 2024-06-29.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#include "leetcode94.h"


//Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

void inorderTraversalHelper(struct TreeNode* root, int* retAry, int* returnSize) {
    if (!root) {
        return;
    }
    if (root->left) {
        inorderTraversalHelper(root->left, retAry, returnSize);
    }
    retAry[(*returnSize)++] = root->val;
    if (root->right) {
        inorderTraversalHelper(root->right, retAry, returnSize);
    }
}

int* inorderTraversalLT94(struct TreeNode* root, int* returnSize) {
    int* retAry = (int*)malloc(100 * sizeof(int));
    *returnSize = 0;

    inorderTraversalHelper(root, retAry, returnSize);

    return retAry;
}
