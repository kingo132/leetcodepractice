//
//  leetcode863.c
//  myleetcodetest
//
//  Created by jason on 2024-07-02.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode863.h"


// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};



/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

void buildGraph(struct TreeNode* root, int** graph, int* gn) {
    printf("Visit tree: %d\n", root->val);
    if (root->val > *gn) {
        *gn = root->val;
    }
    
    if (root->left) {
        graph[root->val][root->left->val] = 1;
        graph[root->left->val][root->val] = 1;
        printf("set %d <-> %d\n", root->val, root->left->val);
        buildGraph(root->left, graph, gn);
    }
    if (root->right) {
        graph[root->val][root->right->val] = 1;
        graph[root->right->val][root->val] = 1;
        printf("set %d <-> %d\n", root->val, root->right->val);
        buildGraph(root->right, graph, gn);
    }
}

#define MAXLEN 1000

int* distanceK(struct TreeNode* root, struct TreeNode* target, int k, int* returnSize) {
    *returnSize = 0;
    if (! root) {
        return NULL;
    }
    if (k < 0) {
        return NULL;
    }
    int* retAry = (int*)malloc(MAXLEN * sizeof(int));
    if (k == 0) {
        retAry[(*returnSize)++] = target->val;
        return retAry;
    }

    int** graph = (int**)malloc(MAXLEN * sizeof(int*));
    for (int i = 0; i < MAXLEN; i++) {
        graph[i] = (int*)malloc(MAXLEN * sizeof(int));
        for (int j = 0; j < MAXLEN; j++) {
            graph[i][j] = 0;
        }
    }
    int gn = 0;

    buildGraph(root, graph, &gn);
    gn ++; // Include 0

    int* que = (int*)malloc(gn * sizeof(int));
    int* step = (int*)malloc(gn * sizeof(int));
    int* visited = (int*)malloc(gn * sizeof(int));
    int front = 0, tail = 0, queSize = 0;
    for (int i = 0; i < gn; i++) {
        visited[i] = 0;
        step[i] = 0;
    }

    printf("Got gn: %d\n", gn);

    que[tail++] = target->val;
    queSize++;
    while (queSize > 0) {
        int v = que[front++];
        queSize--;
        printf("Visit: %d\n", v);
        visited[v] = 1;
        int s = step[v];

        for (int i = 0; i <= gn; i++) {
            if (graph[v][i] && visited[i] == 0) {
                step[i] = s + 1;
                que[tail++] = i;
                queSize++;
            }
        }
    }

    for (int i = 0; i < gn; i++) {
        if (step[i] == k) {
            retAry[(*returnSize)++] = i;
        }
    }
    
    free(que);
    free(step);
    free(visited);
    for (int i = 0; i < MAXLEN; i++) {
        free(graph[i]);
    }
    free(graph);
    return retAry;
}
