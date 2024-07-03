//
//  leetcode104.c
//  myleetcodetest
//
//  Created by jason on 2024-07-02.
//

#include "leetcode104.h"


// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};


int maxDepth(struct TreeNode* root) {
    if (! root) {
        return 0;
    }

    if (! root->left && ! root->right) {
        return 1;
    }

    int dl = 0;
    if (root->left) {
        dl = 1 + maxDepth(root->left);
    }

    int dr = 0;
    if (root->right) {
        dr = 1 + maxDepth(root->right);
    }

    return dl > dr ? dl : dr;
}
