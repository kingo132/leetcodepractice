//
//  leetcode450.c
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

#include "leetcode450.h"


// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};


void swapNode(struct TreeNode *a, struct TreeNode *b) {
    printf("Swap %d <-> %d\n", a ? a->val : -1, b ? b->val : -1);
    int t = a->val;
    a->val = b->val;
    b->val = t;
}

void downBSTify(struct TreeNode* root, struct TreeNode* prev) {
    printf("downBSTify %d, prev: %d\n", root->val, prev ? prev->val : -1);
    if (!root->left && !root->right) {
        if (prev) {
            if (prev->left == root) {
                prev->left = NULL;
            } else if (prev->right == root) {
                prev->right = NULL;
            } else {
                printf("Error deleting %d,%d,%d,%d\n",
                    prev ? prev->val : -1, prev->left ? prev->left->val : -1, prev->right ? prev->right->val : -1,
                    root ? root->val : -1);
            }
            free(root);
        } else {
            printf("Null prev while deleting %d\n", root->val);
        }
        
        return;
    }

    if (root->left && root->val < root->left->val) {
        swapNode(root->left, root);
        prev = root;
        downBSTify(root->left, prev);
    } else if (root->right && root->val > root->right->val) {
        swapNode(root->right, root);
        prev = root;
        downBSTify(root->right, prev);
    } else {
        // 随便选一个
        if (root->left) {
            swapNode(root->left, root);
            prev = root;
            downBSTify(root->left, prev);
        } else if (root->right) {
            swapNode(root->right, root);
            prev = root;
            downBSTify(root->right, prev);
        } else {
            printf("Cannot happen.\n");
        }
    }
}

void deleteNodeHelper(struct TreeNode* root, int key, struct TreeNode** pPrev, struct TreeNode** pPrevPrev, bool* deleted) {
    if (!root) {
        return;
    }

    if (root->left) {
        deleteNodeHelper(root->left, key, pPrev, pPrevPrev, deleted);
    }
    if (*deleted) {
        return;
    }
    printf("Traverse %d, prev: %d, prevPrev: %d\n", root ? root->val : -1, (*pPrev) ? (*pPrev)->val : -1, (*pPrevPrev) ? (*pPrevPrev)->val : -1);
    if (root->val == key) {
        // delete
        if ((*pPrev) != NULL) {
            // use prev
            printf("Preswap1 %d <-> %d\n", root->val, (*pPrev)->val);
            swapNode(root, (*pPrev));
            if (root->left == (*pPrev) || root->right == (*pPrev)) {
                downBSTify((*pPrev), root);
            } else {
                downBSTify((*pPrev), (*pPrevPrev));
            }
            *deleted = true;
            return;
        }
    }
    if ((*pPrev) && (*pPrev)->val == key) {
        // delete prev, use this
        printf("Preswap2 %d <-> %d\n", root->val, (*pPrev)->val);
        swapNode(root, (*pPrev));
        downBSTify(root, (*pPrev));
        *deleted = true;
        return;
    }
    *pPrevPrev = *pPrev;
    *pPrev = root;
    if (root->right) {
        deleteNodeHelper(root->right, key, pPrev, pPrevPrev, deleted);
    }
}

struct TreeNode* deleteNodeOldBad(struct TreeNode* root, int key) {
    if (!root) {
        return NULL;
    }

    if (!root->left && !root->right) {
        if (root->val == key) {
            free(root);
            return NULL;
        }
        return root;
    }

    struct TreeNode* prev = NULL, *prevPrev = NULL;
    bool deleted = false;
    deleteNodeHelper(root, key, &prev, &prevPrev, &deleted);

    return root;
}

// 对于一看都会，一写就废的算法：背下来
// 1. 任何遍历方法找到节点
// 2. 无子或独子，直接删
// 3. 中序前一个或后一个，交换以后递归删除
// 注意要返回删除以后的根节点，递归上面的函数可以接住，
struct TreeNode* findMin(struct TreeNode* root) {
    while (root && root->left) {
        root = root->left;
    }
    return root;
}

struct TreeNode* deleteNode(struct TreeNode* root, int key) {
    if (!root) {
        return NULL;
    }

    if (root->val == key) {
        // delete this
        if (!root->left && !root->right) {
            free(root);
            return NULL;
        }

        if (!root->left) {
            struct TreeNode* t = root->right;
            free(root);
            return t;
        }

        if (!root->right) {
            struct TreeNode* t = root->left;
            free(root);
            return t;
        }

        struct TreeNode* t = findMin(root->right);
        root->val = t->val;
        root->right = deleteNode(root->right, t->val);

        return root;
    }
    
    if (root->left && key < root->val) {
        root->left = deleteNode(root->left, key);
    }
    if (root->right && key > root->val) {
        root->right = deleteNode(root->right, key);
    }
    return root;
}
