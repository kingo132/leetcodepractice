//
//  leetcode958.c
//  myleetcodetest
//
//  Created by jason on 2024-07-25.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode958.h"

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool isCompleteTreeHelper(struct TreeNode* n, int* h, int l, struct TreeNode** last) {
    if (*last != NULL) {
        return false;
    }

    if (!n->left && !n->right) {
        if (*h != -1 && *h != l) {
            if (*last != NULL) {
                return false;
            }
            *last = n;
            return true;
        } else {
            *h = l;
            return true;
        }
    }

    if (!n->left) {
        if (*last != NULL) {
            return false;
        }
        *last = n;
    } else {
        if (!isCompleteTreeHelper(n->left, h, l + 1, last)) {
            return false;
        }
    }

    if (!n->right) {
        if (*last != NULL) {
            return false;
        }
        *last = n;
    } else {
        if (!isCompleteTreeHelper(n->right, h, l + 1, last)) {
            return false;
        }
    }

    return true;
}

int fillary(struct TreeNode* root, int* ary, int idx) {
    if (idx > 10000) {
        return false;
    }
    ary[idx - 1] = root->val;
    int ret = idx;
    if (root->left) {
        int v = fillary(root->left, ary, 2 * idx);
        if (v > ret) {
            ret = v;
        }
    }
    if (root->right) {
        int v = fillary(root->right, ary, 2 * idx + 1);
        if (v > ret) {
            ret = v;
        }
    }
    return ret;
}

bool isCompleteTree(struct TreeNode* root) {
    //int h = -1;
    //struct TreeNode* last = NULL;
    //return isCompleteTreeHelper(root, &h, 1, &last);
    int* ary = (int*)malloc(10000 * sizeof(int));
    memset(ary, 0, 10000 * sizeof(int));

    int len = fillary(root, ary, 1);

    for (int i = 0; i < len; i++) {
        if (ary[i] == 0) {
            free(ary);
            return false;
        }
    }

    free(ary);
    return true;
}
