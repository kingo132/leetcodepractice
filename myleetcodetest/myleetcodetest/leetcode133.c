//
//  leetcode133.c
//  myleetcodetest
//
//  Created by jason on 2024-06-13.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "leetcode133.h"


struct Node {
    int val;
    int numNeighbors;
    struct Node** neighbors;
};

struct Node *cloneGraphHelper(struct Node *n, struct Node **valToNode) {
    if (n == NULL) {
        printf("Null n\n");
        return NULL;
    }
    struct Node *clone = NULL;
    if (valToNode[n->val] != NULL) {
        printf("Clone %d from saved\n", n->val);
        clone = valToNode[n->val];
    } else {
        printf("Clone %d from new\n", n->val);
        clone = (struct Node *)malloc(sizeof(struct Node));
        clone->val = n->val;
        clone->numNeighbors = n->numNeighbors;
        clone->neighbors = (struct Node**)malloc(n->numNeighbors * sizeof(struct Node*));
        valToNode[n->val] = clone;
        for (int i = 0; i < n->numNeighbors; i++) {
            clone->neighbors[i] = cloneGraphHelper(n->neighbors[i], valToNode);
        }
    }

    return clone;
}

struct Node *cloneGraphRecursive(struct Node *s) {
    struct Node *valToNode[100] = {NULL};

    return cloneGraphHelper(s, valToNode);
}

struct Node *cloneGraph(struct Node *s) {
    if (s == NULL) {
        return NULL;
    }
    struct Node *valToNode[101] = {NULL};

    struct Node *stack[1000] = {NULL};
    int top = 0;

    stack[top++] = s;
    while (top > 0) {
        struct Node *n = stack[--top];
        if (n == NULL) {
            printf("Null n, top %d\n", top);
            break;
        }

        if (valToNode[n->val] == NULL) {
            //printf("Clone %d from new\n", n->val);
            struct Node *clone = (struct Node *)malloc(sizeof(struct Node));
            clone->val = n->val;
            clone->numNeighbors = n->numNeighbors;
            clone->neighbors = (struct Node**)malloc(n->numNeighbors * sizeof(struct Node*));
            valToNode[n->val] = clone;
        }

        for (int i = 0; i < n->numNeighbors; i++) {
            if (n->neighbors[i] == NULL) {
                valToNode[n->val]->neighbors[i] = NULL;
            } else {
                if (valToNode[n->neighbors[i]->val] == NULL) {
                    valToNode[n->neighbors[i]->val] = (struct Node *)malloc(sizeof(struct Node));
                    valToNode[n->neighbors[i]->val]->val = n->neighbors[i]->val;
                    valToNode[n->neighbors[i]->val]->numNeighbors = n->neighbors[i]->numNeighbors;
                    valToNode[n->neighbors[i]->val]->neighbors = (struct Node**)malloc(n->neighbors[i]->numNeighbors * sizeof(struct Node*));
                    stack[top++] = n->neighbors[i];
                }
                valToNode[n->val]->neighbors[i] = valToNode[n->neighbors[i]->val];
            }
        }
    }

    return valToNode[s->val];
}
