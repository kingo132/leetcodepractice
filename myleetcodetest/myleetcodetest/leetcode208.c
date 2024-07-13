//
//  leetcode208.c
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

#include "leetcode208.h"


typedef struct {
    struct TreeNode** childs;
    int cnt;
} TreeNode;

typedef struct {
    TreeNode* root;
} Trie;

TreeNode* createTreeNode() {
    TreeNode* tr = (TreeNode*)malloc(sizeof(TreeNode));
    tr->childs = (TreeNode**)malloc(26 * sizeof(TreeNode*));
    memset(tr->childs, 0, 26 * sizeof(TreeNode*));
    tr->cnt = 0;
    return tr;
}

Trie* trieCreate() {
    Trie* t = (Trie*)malloc(sizeof(Trie));
    t->root = createTreeNode();
    return t;
}

void trieInsert(Trie* obj, char* word) {
    char* p = word;
    TreeNode* root = obj->root;
    while (*p) {
        if (root->childs[*p - 'a'] == NULL) {
            root->childs[*p - 'a'] = createTreeNode();
        }
        root = root->childs[*p - 'a'];
        p++;
    }
    root->cnt++;
}

bool trieSearch(Trie* obj, char* word) {
    char* p = word;
    TreeNode* root = obj->root;
    while (*p) {
        if (root->childs[*p - 'a'] == NULL) {
            return false;
        }
        root = root->childs[*p - 'a'];
        p++;
    }
    if (root->cnt > 0) {
        return true;
    }
    return false;
}

bool trieStartsWith(Trie* obj, char* prefix) {
    char* p = prefix;
    TreeNode* root = obj->root;
    while (*p) {
        if (root->childs[*p - 'a'] == NULL) {
            return false;
        }
        root = root->childs[*p - 'a'];
        p++;
    }
    return true;
}

void freeTree(TreeNode* root) {
    for (int i = 0; i < 26; i++) {
        if (root->childs[i] != NULL) {
            freeTree(root->childs[i]);
        }
    }
    free(root);
}

void trieFree(Trie* obj) {
    freeTree(obj->root);
    free(obj);
}

/**
 * Your Trie struct will be instantiated and called as such:
 * Trie* obj = trieCreate();
 * trieInsert(obj, word);
 
 * bool param_2 = trieSearch(obj, word);
 
 * bool param_3 = trieStartsWith(obj, prefix);
 
 * trieFree(obj);
*/
