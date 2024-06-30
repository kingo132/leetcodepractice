//
//  leetcode617.c
//  myleetcodetest
//
//  Created by jason on 2024-06-16.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "leetcode617.h"


struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* mergeTrees(struct TreeNode* root1, struct TreeNode* root2) {
    if (root1 == NULL && root2 == NULL) {
        return NULL;
    }

    if (root1 == NULL && root2 != NULL) {
        root1 = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        root1->val = 0;
        root1->left = NULL;
        root1->right = NULL;
    }

    if (root2 != NULL) {
        root1->val += root2->val;
    }

    if (root1->left == NULL && root2 && root2->left != NULL) {
        root1->left = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        root1->left->val = 0;
        root1->left->left = NULL;
        root1->left->right = NULL;
    }
    if (root1->right == NULL && root2 && root2->right != NULL) {
        root1->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        root1->right->val = 0;
        root1->right->left = NULL;
        root1->right->right = NULL;
    }

    mergeTrees(root1->left, root2 ? root2->left : NULL);
    mergeTrees(root1->right, root2 ? root2->right : NULL);

    return root1;
}
