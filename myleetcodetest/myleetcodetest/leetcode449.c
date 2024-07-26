#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int nodesCnt(struct TreeNode* root) {
    if (!root->left && !root->right) {
        return 1;
    }
    int cl = 0;
    if (root->left) {
        cl = nodesCnt(root->left);
    }
    int cr = 0;
    if (root->right) {
        cr = nodesCnt(root->right);
    }
    return 1 + cl + cr;
}

void serializeHelperLT449(struct TreeNode* root, char* buf, int* bufIdx) {
    if (!root) {
        return;
    }
    int cnt = sprintf(buf + (*bufIdx), "%d,", root->val);
    *bufIdx += cnt;
    if (root->left) {
        serializeHelperLT449(root->left, buf, bufIdx);
    } else {
        *(buf + (*bufIdx)) = ',';
        (*bufIdx)++;
    }
    if (root->right) {
        serializeHelperLT449(root->right, buf, bufIdx);
    } else {
        *(buf + (*bufIdx)) = ',';
        (*bufIdx)++;
    }
}

/** Encodes a tree to a single string. */
char* serializeLT449(struct TreeNode* root) {
    if (!root) {
        return NULL;
    }
    int nodeCnt = nodesCnt(root);
    char* buf = (char*)malloc(nodeCnt * 10 * sizeof(char));
    int bufIdx = 0;
    serializeHelperLT449(root, buf, &bufIdx);
    buf[bufIdx] = '\0';
    printf("Ser: %s\n", buf);
    return buf;
}

int getNextInt(char** str) {
    char* p = *str;
    while (*p) {
        if (*p >= '0' && *p <= '9') {
            p++;
        } else {
            break;
        }
    }
    if (p == *str) {
        (*str)++;
        return -1;
    }
    *p = '\0';
    int ret = atoi(*str);
    *str = p + 1;
    return ret;
}

struct TreeNode* createNewNode(int v, struct TreeNode* l, struct TreeNode* r) {
    struct TreeNode* n = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    n->val = v;
    n->left = l;
    n->right = r;
    //printf("Create node: %d, l: %d, r: %d\n", n->val, l?l->val:-1, r?r->val:-1);
    return n;
}

struct TreeNode* deserializeHelperLT449(char** data) {
    struct TreeNode* root = NULL;
    int v = getNextInt(data);
    if (v != -1) {
        root = createNewNode(v, NULL, NULL);
        //printf("After root: %s\n", *data);
        root->left = deserializeHelperLT449(data);
        //printf("After left: %s\n", *data);
        root->right = deserializeHelperLT449(data);
        //printf("After right: %s\n", *data);
    }
    return root;
}

/** Decodes your encoded data to tree. */
struct TreeNode* deserializeLT449(char* data) {
    if (!data) {
        return NULL;
    }

    return deserializeHelperLT449(&data);
}

// Your functions will be called as such:
// char* data = serialize(root);
// deserialize(data);
