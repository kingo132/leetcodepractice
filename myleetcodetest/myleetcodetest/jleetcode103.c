#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>

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
    struct TreeNode* node;
    int level;
} QueNode;

// 其实可以一次遍历以后，反转奇数层的数组

int** zigzagLevelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    if (!root) {
        return NULL;
    }

    int** retAry = (int**)malloc(1000 * sizeof(int*));
    for (int i = 0; i < 1000; i++) {
        retAry[i] = (int*)malloc(1000 * sizeof(int));
    }
    *returnColumnSizes = (int*)malloc(1000 * sizeof(int));
    memset(*returnColumnSizes, 0, 1000 * sizeof(int));

    int maxQueSize = 1000;
    QueNode* que = (QueNode*)malloc(maxQueSize * sizeof(QueNode));
    int front = 0, tail = 0, queSize = 0;

    que[tail].node = root;
    que[tail].level = 1;
    tail++;
    queSize++;

    while (queSize > 0) {
        struct TreeNode* node = que[front].node;
        int level = que[front].level;
        front = (front + 1) % maxQueSize;
        queSize--;

        if (level % 2 != 0) {
            //printf("Visit: %d\n", node->val);
            if (level > *returnSize) {
                *returnSize = level;
            }
            retAry[level - 1][(*returnColumnSizes)[level - 1]++] = node->val;
        }

        // left to right
        if (node->left) {
            que[tail].node = node->left;
            que[tail].level = level + 1;
            tail = (tail + 1) % maxQueSize;
            queSize++;
        }
        if (node->right) {
            que[tail].node = node->right;
            que[tail].level = level + 1;
            tail = (tail + 1) % maxQueSize;
            queSize++;
        }
    }

    front = 0, tail = 0, queSize = 0;

    que[tail].node = root;
    que[tail].level = 1;
    tail++;
    queSize++;
    
    while (queSize > 0) {
        struct TreeNode* node = que[front].node;
        int level = que[front].level;
        front = (front + 1) % maxQueSize;
        queSize--;

        if (level % 2 == 0) {
            //printf("Visit: %d\n", node->val);
            if (level > *returnSize) {
                *returnSize = level;
            }
            retAry[level - 1][(*returnColumnSizes)[level - 1]++] = node->val;
        }

        // right to left
        if (node->right) {
            que[tail].node = node->right;
            que[tail].level = level + 1;
            tail = (tail + 1) % maxQueSize;
            queSize++;
        }
        if (node->left) {
            que[tail].node = node->left;
            que[tail].level = level + 1;
            tail = (tail + 1) % maxQueSize;
            queSize++;
        }
    }

    free(que);
    return retAry;
}