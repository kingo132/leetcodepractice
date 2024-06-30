//
//  leetcode112.c
//  myleetcodetest
//
//  Created by jason on 2024-06-13.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "leetcode112.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool hasPathSum(struct TreeNode* root, int targetSum) {
    if (!root) {
        return false;
    }
    int rst = -1;
    if (root->left) {
        rst = hasPathSum(root->left, targetSum - root->val);
    }
    if (rst != 1 && root->right) {
        rst = hasPathSum(root->right, targetSum - root->val);
    }

    if (!root->left && !root->right) {
        //printf("Check leaf %d, target: %d\n", root->val, targetSum);
        if (targetSum == root->val) {
            rst = true;
        }
    }

    return rst == 1 ? true : false;
}
