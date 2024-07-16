#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* flattenHelper(struct TreeNode* root, struct TreeNode** prev) {
    if (*prev) {
        //printf("Prev %d ->right = %d\n", (*prev)->val, root->val);
        (*prev)->right = root;
    }
    *prev = root;

    struct TreeNode* tmpRight = root->right;
    if (root->left) {
        flattenHelper(root->left, prev);
    }
    //printf("Set %d ->left = NULL, tmpRight: %d\n", root->val, tmpRight ? tmpRight->val : -1);
    root->left = NULL;
    if (tmpRight) {
        flattenHelper(tmpRight, prev);
    }
    return root;
}

void flatten(struct TreeNode* root) {
    if (!root) {
        return;
    }
    struct TreeNode* prev = NULL;
    flattenHelper(root, &prev);
}