//
//  leetcode113.c
//  myleetcodetest
//
//  Created by jason on 2024-06-11.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "leetcode113.h"

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

typedef struct {
    int sum;
    struct TreeNode* n;
} PreorderStackNode;

void dumpStackLT113(PreorderStackNode* stack, int top) {
    printf("Dump stack: ");
    for (int i = 0; i < top; i++) {
        printf("%d,%d ", stack[i].n->val, stack[i].sum);
    }
    printf("\n");
}

int** pathSumPreorder(struct TreeNode* root, int targetSum, int* returnSize, int** returnColumnSizes) {
    int** retAry = (int**)malloc(5000 * sizeof(int*));
    *returnColumnSizes = (int*)malloc(5000 * sizeof(int));
    int retCnt = 0;
    PreorderStackNode* stack = (PreorderStackNode*)malloc(5000 * sizeof(PreorderStackNode));
    int top = 0;

    stack[top].sum = root->val;
    stack[top].n = root;
    top++;
    while (top > 0) {
        struct TreeNode* n = stack[top - 1].n;
        int sum = stack[top - 1].sum;
        top--;
        printf("Visiting %d, sum: %d\n", n->val, sum);
        if (!n->left && !n->right) {
            // leaf
            printf("Found leaf %d, sum: %d\n", n->val, sum);
            //dumpStackLT113(stack, top);
            if (false) {
                int* foundAry = (int*)malloc(top * sizeof(int));
                for (int i = 0; i < top; i++) {
                    foundAry[i] = stack[i].n->val;
                }
                retAry[retCnt] = foundAry;
                (*returnColumnSizes)[retCnt] = top;
                retCnt++;
            }
        }

        if (n->right) {
            stack[top].n = n->right;
            stack[top].sum = sum + n->right->val;
            top++;
        }
        if (n->left) {
            stack[top].n = n->left;
            stack[top].sum = sum + n->left->val;
            top++;
        }
    }

    return retAry;
}

int** pathSumInorder(struct TreeNode* root, int targetSum, int* returnSize, int** returnColumnSizes) {
    int** retAry = (int**)malloc(5000 * sizeof(int*));
    *returnColumnSizes = (int*)malloc(5000 * sizeof(int));
    int retCnt = 0;
    PreorderStackNode* stack = (PreorderStackNode*)malloc(5000 * sizeof(PreorderStackNode));
    int top = 0;

    struct TreeNode* current = root;
    int currentSum = 0;
    while (top > 0 || current) {
        while (current) {
            stack[top].n = current;
            stack[top].sum = currentSum + current->val;
            top++;

            currentSum += current->val;
            current = current->left;
        }
        
        current = stack[top - 1].n;
        currentSum = stack[top - 1].sum;
        top--;
        printf("Visiting %d, sum: %d\n", current->val, currentSum);
        if (!current->left && !current->right) {
            // leaf
            printf("Found leaf %d, sum: %d\n", current->val, currentSum);
            dumpStackLT113(stack, top);
        }

        if (current->right) {
            //currentSum += current->right->val;
        }
        current = current->right;
    }

    return retAry;
}

// 注意：只有二叉树的后序遍历，堆栈里正好是路径，其它叉的不是这样的
int** pathSum(struct TreeNode* root, int targetSum, int* returnSize, int** returnColumnSizes) {
    int** retAry = (int**)malloc(5000 * sizeof(int*));
    *returnColumnSizes = (int*)malloc(5000 * sizeof(int));
    *returnSize = 0;
    PreorderStackNode* stack = (PreorderStackNode*)malloc(5000 * sizeof(PreorderStackNode));
    int top = 0;

    struct TreeNode* current = root;
    int previousSum = 0;
    struct TreeNode* lastVisited = NULL;
    while (top > 0 || current) {
        if (current) {
            stack[top].n = current;
            stack[top].sum = previousSum + current->val;
            top++;

            previousSum = stack[top - 1].sum;
            current = current->left;
        } else {
            if (stack[top - 1].n->right != NULL && lastVisited != stack[top - 1].n->right) {
                current = stack[top - 1].n->right;
                previousSum = stack[top - 1].sum;
            } else {
                struct TreeNode* p = stack[top - 1].n;
                int sum = stack[top - 1].sum;
                top--;
                printf("Visiting %d, sum: %d\n", p->val, sum);
                if (!p->left && !p->right) {
                    // leaf
                    printf("Found leaf %d, sum: %d\n", p->val, sum);
                    dumpStackLT113(stack, top);
                    if (sum == targetSum) {
                        int* foundAry = (int*)malloc((top + 1) * sizeof(int));
                        int i = 0;
                        for (; i < top; i++) {
                            foundAry[i] = stack[i].n->val;
                        }
                        foundAry[i] = p->val;
                        retAry[*returnSize] = foundAry;
                        (*returnColumnSizes)[*returnSize] = top + 1;
                        (*returnSize)++;
                        printf("Add ary %d\n", *returnSize);
                    }
                }
                lastVisited = p;
            }
        }
    }

    return retAry;
}
