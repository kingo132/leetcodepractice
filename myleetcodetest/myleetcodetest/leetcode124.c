//
//  leetcode124.c
//  myleetcodetest
//
//  Created by jason on 2024-06-27.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#include "leetcode124.h"


// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int maxPathSumHelper(struct TreeNode* root, int* globalMaxSum) {
    int maxSumLeft = 0;
    if (root->left) {
        maxSumLeft = maxPathSumHelper(root->left, globalMaxSum);
    }
    int maxSumRight = 0;
    if (root->right) {
        maxSumRight = maxPathSumHelper(root->right, globalMaxSum);
    }
    int maxSum = maxSumLeft + root->val;
    if (maxSumRight + root->val > maxSum) {
        maxSum = maxSumRight + root->val;
    }
    if (root->val > maxSum) {
        maxSum = root->val;
    }
    if (maxSum > *globalMaxSum) {
        *globalMaxSum = maxSum;
    }
    if (maxSumLeft + maxSumRight + root->val > *globalMaxSum) {
        *globalMaxSum = maxSumLeft + maxSumRight + root->val;
    }
    printf("Node: %d, maxSum: %d, global: %d\n", root->val, maxSum, *globalMaxSum);
    return maxSum;
    /*if (root->val <= 0) {
        if (maxSumLeft > maxSumRight) {
            maxSum = maxSumLeft;
        } else {
            maxSum = maxSumRight;
        }
        if (maxSum > *globalMaxSum) {
            *globalMaxSum = maxSum;
        }
        return 0;
    } else {
        maxSum = maxSumLeft + maxSumRight + root->val;
        if (maxSum > *globalMaxSum) {
            *globalMaxSum = maxSum;
        }
        return maxSum;
    }*/
}

int maxPathSum(struct TreeNode* root) {
    int maxSum = INT_MIN;
    maxPathSumHelper(root, &maxSum);
    return maxSum;
}
