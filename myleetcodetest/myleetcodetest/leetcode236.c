//
//  leetcode236.c
//  myleetcodetest
//
//  Created by jason on 2024-07-12.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode236.h"


//Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};


void getPathRecursive(struct TreeNode* root, struct TreeNode* p, struct TreeNode* path[], int* lenPath, int i) {
    path[i] = root;
    if (root == p) {
        *lenPath = i + 1;
        return;
    }
    if (*lenPath == 0 && root->left) {
        getPathRecursive(root->left, p, path, lenPath, i + 1);
    }
    if (*lenPath == 0 && root->right) {
        getPathRecursive(root->right, p, path, lenPath, i + 1);
    }
}

typedef struct {
    struct TreeNode* n;
    int lvl;
} StackNode;

void getPath(struct TreeNode* root, struct TreeNode* p, struct TreeNode* path[], int* lenPath, int i) {
    if (!root) {
        return;
    }
    StackNode* stack = (StackNode*)malloc(10000 * sizeof(StackNode));
    int top = 0;

    stack[top].n = root;
    stack[top].lvl = 1;
    top++;

    while (top > 0) {
        struct TreeNode* n = stack[top - 1].n;
        int lvl = stack[top - 1].lvl;
        top--;

        //printf("Trying %d,%d\n", n->val, lvl);

        path[lvl - 1] = n;
        if (n == p) {
            *lenPath = lvl;
            free(stack);
            return;
        }

        if (n->left) {
            stack[top].n = n->left;
            stack[top].lvl = lvl + 1;
            top++;
        }
        if (n->right) {
            stack[top].n = n->right;
            stack[top].lvl = lvl + 1;
            top++;
        }
    }
    free(stack);
}

struct TreeNode* lowestCommonAncestorMyMy(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    struct TreeNode* pathP[20000],* pathQ[20000];
    int lenPathP = 0, lenPathQ = 0;
    getPath(root, p, pathP, &lenPathP, 0);
    getPath(root, q, pathQ, &lenPathQ, 0);
    printf("Path1: %d, Path2: %d\n", lenPathP, lenPathQ);
    for (int i = 0; i < lenPathP; i++) {
        printf("%d ", pathP[i]->val);
    }
    printf("\n");
    for (int i = 0; i < lenPathQ; i++) {
        printf("%d ", pathQ[i]->val);
    }
    printf("\n");
    int idxP = lenPathP - 1, idxQ = lenPathQ - 1;
    if (lenPathP > lenPathQ) {
        idxP -= lenPathP - lenPathQ;
    } else {
        idxQ -= lenPathQ - lenPathP;
    }
    while (idxP >= 0 && idxQ >= 0) {
        printf("Check %d <-> %d\n", idxP, idxQ);
        if (pathP[idxP] == pathQ[idxQ]) {
            return pathP[idxP];
        }
        idxP--;
        idxQ--;
    }
    return NULL;
}

struct TreeNode* lowestCommonAncestorChatGPT(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    if (root == NULL || root == p || root == q) {
        return root;
    }
    
    struct TreeNode* left = lowestCommonAncestorChatGPT(root->left, p, q);
    struct TreeNode* right = lowestCommonAncestorChatGPT(root->right, p, q);
    
    if (left != NULL && right != NULL) {
        return root;
    }
    
    return (left != NULL) ? left : right;
}
