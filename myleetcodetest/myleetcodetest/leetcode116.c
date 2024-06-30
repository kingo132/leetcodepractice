//
//  leetcode116.c
//  myleetcodetest
//
//  Created by jason on 2024-06-11.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "leetcode116.h"

struct Node {
    int val;
    struct Node *left;
    struct Node *right;
    struct Node *next;
};

typedef struct {
    struct Node* n;
    int h;
} QUENODE;

#define QUE_MAX_SIZE 4096
struct Node* connectTree(struct Node* root) {
    QUENODE que[QUE_MAX_SIZE];
    int front = 0, tail = 0;
    int queSize = 0;

    que[tail].n = root;
    que[tail].h = 0;
    tail++;
    queSize++;

    struct Node* prevN = NULL;
    int prevH = 0;
    while (queSize > 0) {
        struct Node* n = que[front].n;
        int h = que[front].h;
        front = (front + 1) % QUE_MAX_SIZE;
        queSize--;

        if (!n) {
            printf("Null n\n");
            break;
        }
        //printf("Visiting %d: %d\n", front, n->val);

        if (prevN != NULL && prevH == h) {
            prevN->next = n;
        }
        prevN = n;
        prevH = h;

        if (n->left) {
            que[tail].n = n->left;
            que[tail].h = h + 1;
            tail = (tail + 1) % QUE_MAX_SIZE;
            queSize++;
        }
        if (n->right) {
            que[tail].n = n->right;
            que[tail].h = h + 1;
            tail = (tail + 1) % QUE_MAX_SIZE;
            queSize++;
        }
    }

    return root;
}
