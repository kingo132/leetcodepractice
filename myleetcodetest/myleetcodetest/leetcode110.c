//
//  leetcode110.c
//  myleetcodetest
//
//  Created by jason on 2024-06-29.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#include "leetcode110.h"


// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};


int heightOfNode(struct TreeNode* root) {
    if(!root->left && !root->right) {
        return 1;
    }

    int heightLeft = 0;
    if (root->left) {
        heightLeft = heightOfNode(root->left);
    }
    int heightRight = 0;
    if (root ->right) {
        heightRight = heightOfNode(root->right);
    }

    //printf("Node: %d, l: %d, r: %d\n", root->val, heightLeft, heightRight);
    if (heightLeft == -1 || heightRight == -1) {
        return -1;
    }

    if (heightLeft > heightRight) {
        if (heightLeft - heightRight > 1) {
            return -1;
        }

        return heightLeft + 1;
    } else {
        if (heightRight - heightLeft > 1) {
            return -1;
        }

        return heightRight + 1;
    }
}

bool isBalanced(struct TreeNode* root) {
    if (!root) {
        return true;
    }
    return heightOfNode(root) != -1;
}
