#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
void postorderTraversalHelper(struct TreeNode* root, int* retAry, int* returnSize) {
    if (root->left) {
        postorderTraversalHelper(root->left, retAry, returnSize);
    }
    if (root->right) {
        postorderTraversalHelper(root->right, retAry, returnSize);
    }
    retAry[(*returnSize)++] = root->val;
}

int* postorderTraversal(struct TreeNode* root, int* returnSize) {
    *returnSize = 0;
    if (!root) {
        return NULL;
    }

    int* retAry = (int*)malloc(100 * sizeof(int));
    postorderTraversalHelper(root, retAry, returnSize);
    return retAry;
}