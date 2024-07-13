//
//  leetcode102.c
//  myleetcodetest
//
//  Created by jason on 2024-07-10.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode102.h"


// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

typedef struct {
    struct TreeNode* n;
    int level;
} QueNode;

int heightOfTheTreeLT102(struct TreeNode* root) {
    if (!root->left && !root->right) {
        return 1;
    }
    int hl = 0;
    if (root->left) {
        hl = 1 + heightOfTheTreeLT102(root->left);
    }
    int hr = 0;
    if (root->right) {
        hr = 1 + heightOfTheTreeLT102(root->right);
    }
    return hl > hr ? hl : hr;
}

int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    if (!root) {
        return NULL;
    }
    int maxQueSize = 3000;
    QueNode* que = (QueNode*)malloc(maxQueSize * sizeof(QueNode));
    int front = 0, tail = 0, queSize = 0;

    int height = heightOfTheTreeLT102(root);
    //printf("Get height: %d\n", height);
    *returnSize = height;
    *returnColumnSizes = (int*)malloc(height * sizeof(int));
    int* aryIdx = (int*)malloc(height * sizeof(int));
    for (int i = 0; i < height; i++) {
        (*returnColumnSizes)[i] = 0;
        aryIdx[i] = 0;
    }

    que[tail].n = root;
    que[tail].level = 0;
    tail++;
    queSize++;
    while (queSize > 0) {
        struct TreeNode* n = que[front].n;
        int lvl = que[front].level;
        front = (front + 1) % maxQueSize;
        queSize--;

        //printf("Visit %d, level: %d\n", n->val, lvl);
        (*returnColumnSizes)[lvl]++;

        if (n->left) {
            que[tail].n = n->left;
            que[tail].level = lvl + 1;
            tail = (tail + 1) % maxQueSize;
            queSize++;
        }
        if (n->right) {
            que[tail].n = n->right;
            que[tail].level = lvl + 1;
            tail = (tail + 1) % maxQueSize;
            queSize++;
        }
    }

    int** retAry = (int**)malloc(height * sizeof(int*));
    for (int i = 0; i < height; i++) {
        retAry[i] = (int*)malloc((*returnColumnSizes)[i] * sizeof(int));
    }

    front = 0;
    tail = 0;
    queSize = 0;
    que[tail].n = root;
    que[tail].level = 0;
    tail++;
    queSize++;
    while (queSize > 0) {
        struct TreeNode* n = que[front].n;
        int lvl = que[front].level;
        front = (front + 1) % maxQueSize;
        queSize--;

        //printf("Visit %d, level: %d\n", n->val, lvl);
        //(*returnColumnSizes)[lvl]++;
        retAry[lvl][aryIdx[lvl]++] = n->val;

        if (n->left) {
            que[tail].n = n->left;
            que[tail].level = lvl + 1;
            tail = (tail + 1) % maxQueSize;
            queSize++;
        }
        if (n->right) {
            que[tail].n = n->right;
            que[tail].level = lvl + 1;
            tail = (tail + 1) % maxQueSize;
            queSize++;
        }
    }

    free(aryIdx);
    return retAry;
}
