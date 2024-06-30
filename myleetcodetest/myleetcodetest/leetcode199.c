//
//  leetcode199.c
//  myleetcodetest
//
//  Created by jason on 2024-06-29.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#include "leetcode199.h"


// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

void rightSideViewHelper(struct TreeNode* root, int** retAry, int* returnSize, struct TreeNode* rightMostNode, int rightHeight) {
    if (root->left) {
        rightSideViewHelper(root->left, retAry, returnSize, rightMostNode, rightHeight);
    }
    if (root->right) {
        rightSideViewHelper(root->right, retAry, returnSize, rightMostNode, rightHeight);
    }

    if (root == rightMostNode) {
        *returnSize = 0;
        *retAry = (int*)malloc(100 * sizeof(int));
        (*retAry)[(*returnSize)++] = root->val;
    } else if (*returnSize > 0) {
        (*retAry)[(*returnSize)++] = root->val;
    }
}

void rightSideViewHelper2(struct TreeNode* root, int* retAry, int* returnSize, int height) {
    if (height + 1 > *returnSize) {
        *returnSize = height + 1;
    }
    retAry[height] = root->val;
    
    if (root->left) {
        rightSideViewHelper2(root->left, retAry, returnSize, height + 1);
    }
    if (root->right) {
        rightSideViewHelper2(root->right, retAry, returnSize, height + 1);
    }
}

int* rightSideView(struct TreeNode* root, int* returnSize) {
    *returnSize = 0;
    if (! root) {
        return NULL;
    }

    int* retAry = (int*)malloc(100 * sizeof(int));

    rightSideViewHelper2(root, retAry, returnSize, 0);

    /*
    struct TreeNode* pNode = root;
    int rightHeight = 1;
    while (1) {
        retAry[(*returnSize)++] = pNode->val;
        if (pNode->right) {
            pNode = pNode->right;
        } else if (pNode->left) {
            pNode = pNode->left;
        } else {
            break;
        }
        rightHeight ++;
    }

    //printf("Right most: %d, height: %d\n", pNode->val, rightHeight);

    pNode = root->left;
    int leftHeight = 2;
    while (pNode) {
        if (leftHeight > rightHeight) {
            retAry[(*returnSize)++] = pNode->val;
        }
        if (pNode->right) {
            pNode = pNode->right;
        } else if (pNode->left) {
            pNode = pNode->left;
        } else {
            break;
        }
        leftHeight ++;
    }
    */

    /*
    int* retAry = NULL;
    rightSideViewHelper(root, &retAry, returnSize, rightMostNode, rightHeight);

    for (int i = 0; i < (*returnSize) / 2; i++) {
        int t = retAry[i];
        retAry[i] = retAry[(*returnSize) - i - 1];
        retAry[(*returnSize) - i - 1] = t;
    }
    */

    return retAry;
}
