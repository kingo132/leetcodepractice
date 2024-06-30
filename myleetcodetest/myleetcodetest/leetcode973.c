//
//  leetcode973.c
//  myleetcodetest
//
//  Created by jason on 2024-06-15.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "leetcode973.h"

// 1: 最大堆求最小前k个，最小堆求最大前k个
// 2: 堆的向下堆化才能保证数组的元素有序排列，向上堆化无法保证

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
 // O(n * k)
int** kClosestSelection(int** points, int pointsSize, int* pointsColSize, int k, int* returnSize, int** returnColumnSizes) {
    int* distAry = (int*)malloc(pointsSize * sizeof(int));
    for (int i = 0; i < pointsSize; i++) {
        distAry[i] = points[i][0] * points[i][0] + points[i][1] * points[i][1];
    }

    int** retAry = (int**)malloc(k * sizeof(int*));
    *returnSize = 0;
    *returnColumnSizes = (int*)malloc(k * sizeof(int));
    
    if (k > pointsSize / 2) {
        // search by eliminate
        for (int i = 0; i < pointsSize - k; i++) {
            int curMaxIdx = -1;
            for (int j = 0; j < pointsSize; j++) {
                if (curMaxIdx == -1 || (distAry[j] != INT_MIN && distAry[j] > distAry[curMaxIdx])) {
                    curMaxIdx = j;
                }
            }
            if (curMaxIdx == -1) {
                break;
            }
            distAry[curMaxIdx] = INT_MIN;
        }
        for (int i = 0; i < pointsSize; i++) {
            if (distAry[i] != INT_MIN) {
                retAry[*returnSize] = malloc(2 * sizeof(int));
                retAry[*returnSize][0] = points[i][0];
                retAry[*returnSize][1] = points[i][1];
                (*returnColumnSizes)[*returnSize] = 2;
                (*returnSize) ++;
            }
        }
    } else {
        // search by add
        for (int i = 0; i < k; i++) {
            int curMinIdx = -1;
            for (int j = 0; j < pointsSize; j++) {
                if (curMinIdx == -1 || (distAry[j] != INT_MAX && distAry[j] < distAry[curMinIdx])) {
                    curMinIdx = j;
                }
            }
            if (curMinIdx == -1) {
                break;
            }
            retAry[*returnSize] = malloc(2 * sizeof(int));
            retAry[*returnSize][0] = points[curMinIdx][0];
            retAry[*returnSize][1] = points[curMinIdx][1];
            (*returnColumnSizes)[*returnSize] = 2;
            (*returnSize) ++;
            distAry[curMinIdx] = INT_MAX;
        }
    }

    return retAry;
}

typedef struct {
    int dist;
    int x;
    int y;
} HEAPNODE;

void swapHeapNodeLT973(HEAPNODE* a, HEAPNODE* b) {
    printf("swap %d,%d <-> %d,%d\n", a->x, a->y, b->x, b->y);
    HEAPNODE t;
    t.dist = a->dist;
    t.x = a->x;
    t.y = a->y;
    a->dist = b->dist;
    a->x = b->x;
    a->y = b->y;
    b->dist = t.dist;
    b->x = t.x;
    b->y = t.y;
}

void downHeapifyLT973(HEAPNODE* heap, int heapSize, int idx) {
    while (idx < heapSize) {
        int leftChild = (idx + 1) * 2 - 1;
        int largest = idx;
        if (leftChild < heapSize && heap[leftChild].dist > heap[idx].dist) {
            largest = leftChild;
        }
        int rightChild = (idx + 1) * 2;
        if (rightChild < heapSize && heap[rightChild].dist > heap[largest].dist) {
            largest = rightChild;
        }
        if (largest != idx) {
            swapHeapNodeLT973(&heap[largest], &heap[idx]);
        } else {
            break;
        }
        idx = largest;
    }
}

// Heap, O(n * log(n))
int** kClosest(int** points, int pointsSize, int* pointsColSize, int k, int* returnSize, int** returnColumnSizes) {
    HEAPNODE* heap = malloc(k * sizeof(HEAPNODE));

    for (int i = 0; i < k; i++) {
        heap[i].dist = points[i][0] * points[i][0] + points[i][1] * points[i][1];
        heap[i].x = points[i][0];
        heap[i].y = points[i][1];
    }
    for (int i = k / 2; i >= 0; i--) {
        downHeapifyLT973(heap, k, i);
    }
    for (int i = k; i < pointsSize; i++) {
        int dist = points[i][0] * points[i][0] + points[i][1] * points[i][1];
        if (dist < heap[0].dist) {
            heap[0].dist = dist;
            heap[0].x = points[i][0];
            heap[0].y = points[i][1];
            downHeapifyLT973(heap, k, 0);
        }
    }

    int** retAry = (int**)malloc(k * sizeof(int*));
    *returnSize = 0;
    *returnColumnSizes = (int*)malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) {
        retAry[*returnSize] = malloc(2 * sizeof(int));
        retAry[*returnSize][0] = heap[i].x;
        retAry[*returnSize][1] = heap[i].y;
        (*returnColumnSizes)[*returnSize] = 2;
        (*returnSize) ++;
    }

    free(heap);
    return retAry;
}

// Quick Select, O(n)
void dumpArr(const char* prefix, int* arr, int n) {
    printf("%s: ", prefix);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
void swapKClosest(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}
int partitionKClosest(int* arr, int n, int l, int r) {
    int pivot = arr[r];

    int i = l;
    for (int j = l; j <= r; j++) {
        if (arr[j] < pivot) {
            //printf("Swap %d <-> %d\n", i, j);
            swapKClosest(&arr[i], &arr[j]);
            i ++;
        }
    }
    //printf("Swap %d <-> %d\n", i + 1, r);
    swapKClosest(&arr[i], &arr[r]);
    return i;
}

int kClosestQSHelper(int* arr, int n, int l, int r, int k) {
    //printf("n: %d, l: %d, r: %d, k: %d\n", n, l, r, k);
    //dumpArr("Before partition: ", arr, n);
    int pivot = partitionKClosest(arr, n, l, r);
    //dumpArr("After partition: ", arr, n);
    //printf("pivot: %d\n", pivot);
    if (pivot == k - 1) {
        return pivot;
    }
    if (pivot > k - 1) {
        return kClosestQSHelper(arr, n, l, pivot - 1, k);
    }

    return kClosestQSHelper(arr, n, pivot + 1, r, k);
}

int** kClosestQuickSelect(int** points, int pointsSize, int* pointsColSize, int k, int* returnSize, int** returnColumnSizes) {
    int* distAry = (int*)malloc(pointsSize * sizeof(int));
    for (int i = 0; i < pointsSize; i++) {
        distAry[i] = points[i][0] * points[i][0] + points[i][1] * points[i][1];
    }

    int** retAry = (int**)malloc(k * sizeof(int*));
    *returnSize = 0;
    *returnColumnSizes = (int*)malloc(k * sizeof(int));

    int kth = kClosestQSHelper(distAry, pointsSize, 0, pointsSize - 1, k);
    printf("Kth is %d (%d,%d) %d\n", kth, points[kth][0], points[kth][1], distAry[kth]);
    for (int i = 0; i < pointsSize; i++) {
        if (points[i][0] * points[i][0] + points[i][1] * points[i][1] <= distAry[kth]) {
            retAry[*returnSize] = malloc(2 * sizeof(int));
            retAry[*returnSize][0] = points[i][0];
            retAry[*returnSize][1] = points[i][1];
            (*returnColumnSizes)[*returnSize] = 2;
            (*returnSize) ++;
        }
    }

    return retAry;
}
