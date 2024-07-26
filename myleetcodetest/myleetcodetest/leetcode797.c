#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

typedef struct {
    int v;
    int* visited;
    int* path;
    int pathIdx;
} QUENODE;

void copyArray(int* a1, int* a2, int n) {
    for (int i = 0; i < n; i++) {
        a2[i] = a1[i];
    }
}

void dumpArrayLT797(const char* prefix, int* a, int n) {
    printf("%s: ", prefix);
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int** allPathsSourceTargetMy(int** graph, int graphSize, int* graphColSize, int* returnSize, int** returnColumnSizes) {
    int** retAry = (int**)malloc(100000 * sizeof(int*));
    *returnSize = 0;
    *returnColumnSizes = (int*)malloc(100000 * sizeof(int));

    int maxQueSize = 10000;
    QUENODE* que = (QUENODE*)malloc(maxQueSize * sizeof(QUENODE));
    int front = 0, tail = 0, queSize = 0;
    for (int i = 0; i < maxQueSize; i++) {
        que[i].visited = (int*)malloc(graphSize * sizeof(int));
        que[i].path = (int*)malloc(graphSize * sizeof(int));
        for (int j = 0; j < graphSize; j++) {
            que[i].visited[j] = 0;
            que[i].path[j] = 0;
        }
        que[i].pathIdx = 0;
    }

    que[tail++].v = 0;
    queSize++;
    while (queSize > 0) {
        int v = que[front].v;
        int* visited = que[front].visited;
        int* path = que[front].path;
        int pathIdx = que[front].pathIdx;
        front = (front + 1) % maxQueSize;
        queSize--;

        visited[v] = 1;
        //if (pathIdx >= graphSize) {
        //    printf("Invalid pathIdx: %d\n", pathIdx);
        //    dumpArray("Invalid path", path, graphSize);
        //    break;
        //}
        path[pathIdx++] = v;

        //printf("Process %d\n", v);
        //dumpArray("Path", path, pathIdx);

        if (v == graphSize - 1) {
            dumpArrayLT797("Found path", path, pathIdx);
            retAry[*returnSize] = (int*)malloc(pathIdx * sizeof(int));
            copyArray(path, retAry[*returnSize], pathIdx);
            (*returnColumnSizes)[*returnSize] = pathIdx;
            (*returnSize)++;
            continue;
        }

        //printf("%d col %d\n", v, graphColSize[v]);
        for (int i = 0; i < graphColSize[v]; i++) {
            //printf("%d,%d\n", graph[v][i], visited[graph[v][i]]);
            if (visited[graph[v][i]] == 0) {
                que[tail].v = graph[v][i];
                copyArray(visited, que[tail].visited, graphSize);
                copyArray(path, que[tail].path, graphSize);
                //printf("Add %d\n", graph[v][i]);
                //dumpArray("path", path, pathIdx);
                que[tail].pathIdx = pathIdx;
                tail = (tail + 1) % maxQueSize;
                queSize++;
            }
        }
    }

    for (int i = 0; i < graphSize; i++) {
        free(que[i].visited);
        free(que[i].path);
    }
    free(que);
    return retAry;
}

// Helper function to perform DFS
void dfsLT797(int** graph, int graphSize, int* graphColSize, int node, int* path, int pathLen, int** result, int* returnSize, int** returnColumnSizes) {
    path[pathLen] = node;
    pathLen++;
    
    if (node == graphSize - 1) {
        // We reached the target node, save the path
        result[*returnSize] = (int*)malloc(pathLen * sizeof(int));
        for (int i = 0; i < pathLen; i++) {
            result[*returnSize][i] = path[i];
        }
        returnColumnSizes[0][*returnSize] = pathLen;
        (*returnSize)++;
    } else {
        // Continue DFS on adjacent nodes
        for (int i = 0; i < graphColSize[node]; i++) {
            dfsLT797(graph, graphSize, graphColSize, graph[node][i], path, pathLen, result, returnSize, returnColumnSizes);
        }
    }
}

// Main function
int** allPathsSourceTargetChatGPT(int** graph, int graphSize, int* graphColSize, int* returnSize, int** returnColumnSizes) {
    int maxPaths = 10000; // Assuming a maximum of 100 paths for simplicity
    int** result = (int**)malloc(maxPaths * sizeof(int*));
    *returnColumnSizes = (int*)malloc(maxPaths * sizeof(int));
    *returnSize = 0;
    
    int* path = (int*)malloc(graphSize * sizeof(int));
    int pathLen = 0;
    
    dfsLT797(graph, graphSize, graphColSize, 0, path, pathLen, result, returnSize, returnColumnSizes);
    
    free(path);
    return result;
}
