#include <stdio.h>
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

bool isValidBSTHelper(struct TreeNode* root, int* prev, int* isFirst) {
    if (root->left) {
        if (!isValidBSTHelper(root->left, prev, isFirst)) {
            return false;
        }
    }

    printf("Check %d, prev: %d, isFirst: %d\n", root->val, *prev, *isFirst);
    if (*isFirst == 0 && root->val <= *prev) {
        return false;
    }
    *prev = root->val;
    *isFirst = 0;

    if (root->right) {
        if (!isValidBSTHelper(root->right, prev, isFirst)) {
            return false;
        }
    }

    return true;
}

bool isValidBST(struct TreeNode* root) {
    if (!root) {
        return true;
    }
    int prev = INT_MIN, isFirst = 1;
    return isValidBSTHelper(root, &prev, &isFirst);
}
