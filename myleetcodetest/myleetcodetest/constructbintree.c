//
//  constructbintree.c
//  test
//
//  Created by jason on 2024-05-20.
//

#include <stdlib.h>
#include "constructbintree.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int findIndex(int* arr, int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1;
}

struct TreeNode* buildTreeHelper(int* preorder, int preorderSize, int* inorder, int inorderStart, int inorderEnd, int* preorderIndex) {
    if (inorderStart > inorderEnd || inorderStart < 0 || inorderEnd >= preorderSize) {
        return NULL;
    }
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = preorder[*preorderIndex];
    node->left = node->right = NULL;

    (*preorderIndex) ++;
    if (inorderStart == inorderEnd) {
        return node;
    }
    
    if (*preorderIndex >= preorderSize) {
        return node;
    }

    /* Find index in inorder */
    int i = inorderStart;
    for (; i <= inorderEnd; i++) {
        if (inorder[i] == node->val) {
            break;
        }
    }
    if (i > inorderEnd) {
        /* not found */
        printf("Can not find %d in inorder %d-%d\n", preorder[*preorderIndex], inorderStart, inorderEnd);
        return node;
    }
    
    //i = findIndex(inorder, inorderStart, inorderEnd, node->val);

    node->left = buildTreeHelper(preorder, preorderSize, inorder, inorderStart, i - 1, preorderIndex);
    node->right = buildTreeHelper(preorder, preorderSize, inorder, i + 1, inorderEnd, preorderIndex);
    return node;
}

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    int preorderIndex = 0;
    return buildTreeHelper(preorder, preorderSize, inorder, 0, inorderSize - 1, &preorderIndex);
}

void inorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    inorderTraversal(root->left);
    printf("%d ", root->val);
    inorderTraversal(root->right);
}

// Pre-order traversal
void preorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->val);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void buildTreeMain() {
    int preorder[] = {3,9,20,15,7};
    int inorder[] = {9,3,15,20,7};
    
    struct TreeNode* root = buildTree(preorder, 5, inorder, 5);
    preorderTraversal(root);
    printf("\n");
    inorderTraversal(root);
    printf("\n");
}
