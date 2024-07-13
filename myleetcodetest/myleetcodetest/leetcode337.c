//
//  leetcode337.c
//  myleetcodetest
//
//  Created by jason on 2024-07-09.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode337.h"



// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};


int robHelperOld(struct TreeNode* root, bool parentRobed) {
    printf("Cal %d\n", root->val);
    if (!root->left && !root->right) {
        if (parentRobed) {
            return 0;
        }
        return root->val;
    }

    int max = INT_MIN;
    if (! parentRobed) {
        int l = 0, r = 0;
        if (root->left) {
            // rob this, try left
            l = robHelperOld(root->left, true);
        }
        if (root->right) {
            // rob this, try right
            r = robHelperOld(root->right, true);
        }
        if (l + r + root->val > max) {
            max = l + r + root->val;
        }
    }
    
    int l = 0, r = 0;
    if (root->left) {
        // not rob this, try left
        l = robHelperOld(root->left, false);
    }
    if (root->right) {
        // not rob this, try right
        r = robHelperOld(root->right, false);
    }
    if (l + r > max) {
        max = l + r;
    }

    return max;
}

void robHelperLT337(struct TreeNode* root, int* rob, int* notrob) {
    //printf("Cal %d\n", root->val);
    if (!root->left && !root->right) {
        *rob = root->val;
        *notrob = 0;
        return;
    }

    int leftrob = 0, leftnotrob = 0, rightrob = 0, rightnotrob = 0;
    if (root->left) {
        robHelperLT337(root->left, &leftrob, &leftnotrob);
    }
    if (root->right) {
        robHelperLT337(root->right, &rightrob, &rightnotrob);
    }

    // rob
    *rob = root->val + leftnotrob + rightnotrob;
    // not rob
    int max = leftrob + rightrob;
    if (leftrob + rightnotrob > max) {
        max = leftrob + rightnotrob;
    }
    if (leftnotrob + rightnotrob > max) {
        max = leftnotrob + rightnotrob;
    }
    if (leftnotrob + rightrob > max) {
        max = leftnotrob + rightrob;
    }
    *notrob = max;

    return;
}

int robLT337(struct TreeNode* root) {
    int rob = 0, notrob = 0;
    robHelperLT337(root, &rob, &notrob);
    return rob > notrob ? rob : notrob;
}

// A helper function to find the maximum of two integers.
int maxLT337(int a, int b) {
    return (a > b) ? a : b;
}

// A helper function to perform DFS and calculate the maximum money.
void dfs(struct TreeNode* node, int* rob, int* not_rob) {
    if (node == NULL) {
        *rob = 0;
        *not_rob = 0;
        return;
    }
    
    int left_rob = 0, left_not_rob = 0;
    int right_rob = 0, right_not_rob = 0;
    
    // Recursively calculate for left and right children.
    dfs(node->left, &left_rob, &left_not_rob);
    dfs(node->right, &right_rob, &right_not_rob);
    
    // If we rob this node, we cannot rob its children.
    *rob = node->val + left_not_rob + right_not_rob;
    
    // If we do not rob this node, we take the maximum value possible from robbing or not robbing its children.
    *not_rob = maxLT337(left_rob, left_not_rob) + maxLT337(right_rob, right_not_rob);
}

// The main function to calculate the maximum money the thief can rob.
int robChatGPT(struct TreeNode* root) {
    int rob = 0, not_rob = 0;
    dfs(root, &rob, &not_rob);
    return maxLT337(rob, not_rob);
}
