//
//  leetcode543.c
//  myleetcodetest
//
//  Created by jason on 2024-07-12.
//

#include "leetcode543.h"


// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int diameterOfBinaryTreeHelper(struct TreeNode* root, int* maxPathLen) {
    if (!root->left && !root->right) {
        if (1 > *maxPathLen) {
            *maxPathLen = 1;
        }
        return 1;
    }

    int hl = 0;
    if (root->left) {
        hl = diameterOfBinaryTreeHelper(root->left, maxPathLen);
    }
    int hr = 0;
    if (root->right) {
        hr = diameterOfBinaryTreeHelper(root->right, maxPathLen);
    }

    if (hl + hr + 1 > *maxPathLen) {
        *maxPathLen = hl + hr + 1;
    }
    return 1 + (hl > hr ? hl : hr);
}

int diameterOfBinaryTree(struct TreeNode* root) {
    int max = 0;
    diameterOfBinaryTreeHelper(root, &max);
    return max - 1;
}
