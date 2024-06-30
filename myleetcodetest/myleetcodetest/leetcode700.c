//
//  leetcode700.c
//  myleetcodetest
//
//  Created by jason on 2024-06-13.
//

#include "leetcode700.h"

 struct TreeNode {
     int val;
     struct TreeNode *left;
     struct TreeNode *right;
 };
 
struct TreeNode* searchBST(struct TreeNode* root, int val) {
    //printf("Searching %d\n", root ? root->val : -1);
    if (root && root->val == val) {
        return root;
    }

    struct TreeNode* n = NULL;
    if (root->left) {
        n = searchBST(root->left, val);
    }
    if (!n && root->right) {
        n = searchBST(root->right, val);
    }

    return n;
}
