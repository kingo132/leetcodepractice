//
//  leetcode111.c
//  myleetcodetest
//
//  Created by jason on 2024-06-20.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include "leetcode111.h"


struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};


void minDepthHelper(struct TreeNode* root, int depth, int* minDepth) {
    if (! root->left && ! root->right) {
        if (depth < *minDepth) {
            *minDepth = depth;
        }
    }
    if (root->left) {
        minDepthHelper(root->left, depth + 1, minDepth);
    }
    if (root->right) {
        minDepthHelper(root->right, depth + 1, minDepth);
    }
}

int minDepth(struct TreeNode* root) {
    if (! root) {
        return 0;
    }
    int minDepth = INT_MAX;
    minDepthHelper(root, 1, &minDepth);
    return minDepth;
}
