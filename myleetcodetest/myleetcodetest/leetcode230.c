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

int kthSmallestHelper(struct TreeNode* root, int* k) {
    if (root->left) {
        int v = kthSmallestHelper(root->left, k);
        if (v >= 0) {
            return v;
        }
    }

    (*k)--;
    if (*k <= 0) {
        return root->val;
    }

    if (root->right) {
        int v = kthSmallestHelper(root->right, k);
        if (v >= 0) {
            return v;
        }
    }

    return -1;
}
int kthSmallest(struct TreeNode* root, int k) {
    return  kthSmallestHelper(root, &k);
}