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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void serializeHelper(struct TreeNode* root, char* rstr, int* idx) {
    if (!root) {
        return;
    }
    int n = sprintf(rstr + *idx, "%d,", root->val);
    (*idx) += n;
    if (root->left) {
        serializeHelper(root->left, rstr, idx);
    } else {
        rstr[(*idx)++] = ',';
    }
    if (root->right) {
        serializeHelper(root->right, rstr, idx);
    } else {
        rstr[(*idx)++] = ',';
    }
}

/** Encodes a tree to a single string. */
char* serialize(struct TreeNode* root) {
    int idx = 0;
    char* rstr = (char*)malloc(50000 * sizeof(char));
    serializeHelper(root, rstr, &idx);
    //printf("idx: %d\n", idx);
    rstr[idx] = '\0';
    return rstr;
}

int getNextNum(char** s) {
    //printf("Get next: %s\n", *s);
    if (**s == ',') {
        (*s)++;
        return INT_MIN;
    }

    char* p = *s;
    int num = 0, sign = 1;
    if (*p == '-') {
        sign = -1;
        p++;
    }
    while (*p && *p != ',') {
        //printf("%c\n", *p);
        num = num * 10 + (*p - '0');
        p++;
    }
    if (*p) {
        *s = p + 1;
    } else {
        *s = p;
    }
    return num * sign;
}

struct TreeNode* createNode(int v) {
    struct TreeNode* n = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    n->val = v;
    n->left = n->right = NULL;
    return n;
}

struct TreeNode* deserializeHelper(char** s) {
    if (**s == '\0') {
        return NULL;
    }

    int v = getNextNum(s);
    //printf("Visit: %d, s: %s\n", v, *s);
    if (v != INT_MIN) {
        struct TreeNode* n = createNode(v);
        n->left = deserializeHelper(s);
        //if (n->left) printf("%d get left: %d\n", v, n->left->val);
        n->right = deserializeHelper(s);
        //if (n->right) printf("%d get right: %d\n", v, n->right->val);
        return n;
    }
    return NULL;
}

/** Decodes your encoded data to tree. */
struct TreeNode* deserialize(char* data) {
    //printf("s: %s\n", data);
    return deserializeHelper(&data);
}

// Your functions will be called as such:
// char* data = serialize(root);
// deserialize(data);