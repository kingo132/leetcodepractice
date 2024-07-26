#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>


#define MAXHEAPSIZE 100000

typedef struct {
    int lowheap[MAXHEAPSIZE];
    int lowheapIdx;
    int higheap[MAXHEAPSIZE];
    int higheapIdx;
} MedianFinder;

#define MYDEBUG false

void dumpAryLT295(const char* prefix, int* ary, int n) {
    printf("%s", prefix);
    for (int i = 0; i < n; i++) {
        printf("%d ", ary[i]);
    }
    printf("\n");
}

MedianFinder* medianFinderCreate() {
    MedianFinder* mf = (MedianFinder*)malloc(sizeof(MedianFinder));
    mf->lowheapIdx = mf->higheapIdx = 0;
    return mf;
}

void swapLT295(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void heapifyDown(int* heap, int heapsize, int ii, int type) {
    int idx = ii;
    while (idx < heapsize) {
        int leftidx = idx * 2 + 1;
        int rightidx = idx * 2 + 2;
        if (MYDEBUG) printf("idx: %d, left: %d, right: %d\n", idx, leftidx, rightidx);
        int minidx = idx;
        if (type == 1) { // min heap
            if (leftidx < heapsize && heap[leftidx] < heap[minidx]) {
                minidx = leftidx;
            }
            if (rightidx < heapsize && heap[rightidx] < heap[minidx]) {
                minidx = rightidx;
            }
        } else {
            if (leftidx < heapsize && heap[leftidx] > heap[minidx]) {
                minidx = leftidx;
            }
            if (rightidx < heapsize && heap[rightidx] > heap[minidx]) {
                minidx = rightidx;
            }
        }
        if (minidx != idx) {
            if (MYDEBUG) printf("Swap %d(%d) <-> %d(%d)\n", minidx, heap[minidx], idx, heap[idx]);
            swapLT295(&heap[minidx], &heap[idx]);
            idx = minidx;
        } else {
            break;
        }
    }
}

void addToHeap(int* heap, int* heapIdx, int num, int type) {
    heap[(*heapIdx)++] = num;
    int idx = *(heapIdx) - 1;
    while (idx >= 0) {
        int parentidx = (idx + 1) / 2 - 1;
        if (type == 1) { // min heap
            if (parentidx >= 0 && heap[parentidx] > heap[idx]) {
                swapLT295(&(heap[parentidx]), &(heap[idx]));
                idx = parentidx;
            } else {
                break;
            }
        } else { // max heap
            if (parentidx >= 0 && heap[parentidx] < heap[idx]) {
                swapLT295(&(heap[parentidx]), &(heap[idx]));
                idx = parentidx;
            } else {
                break;
            }
        }
        
    }
}

int extractHeap(int* heap, int* heapIdx, int type) {
    int ret = heap[0];
    swapLT295(&heap[0], &heap[*heapIdx - 1]);
    heapifyDown(heap, *heapIdx - 1, 0, type);
    (*heapIdx)--;
    return ret;
}

void medianFinderAddNum(MedianFinder* obj, int num) {
    if (obj->lowheapIdx == 0) {
        addToHeap(obj->lowheap, &(obj->lowheapIdx), num, 2);
    } else {
        if (num > obj->lowheap[0]) {
            addToHeap(obj->higheap, &(obj->higheapIdx), num, 1);
        } else {
            addToHeap(obj->lowheap, &(obj->lowheapIdx), num, 2);
        }

        if (obj->lowheapIdx < obj->higheapIdx) {
            int n = extractHeap(obj->higheap, &(obj->higheapIdx), 1);
            addToHeap(obj->lowheap, &(obj->lowheapIdx), n, 2);
        } else if (obj->lowheapIdx > obj->higheapIdx + 1) {
            int n = extractHeap(obj->lowheap, &(obj->lowheapIdx), 2);
            addToHeap(obj->higheap, &(obj->higheapIdx), n, 1);
        }
    }

    if (MYDEBUG) dumpAryLT295("Add low heap: ", obj->lowheap, obj->lowheapIdx);
    if (MYDEBUG) dumpAryLT295("Add high heap: ", obj->higheap, obj->higheapIdx);
}

double medianFinderFindMedian(MedianFinder* obj) {
    if ((obj->lowheapIdx + obj->higheapIdx) % 2 == 0) {
        return (obj->lowheap[0] + obj->higheap[0]) / 2.0;
    } else {
        return obj->lowheap[0];
    }
}

void medianFinderFree(MedianFinder* obj) {
    free(obj);
}

/**
 * Your MedianFinder struct will be instantiated and called as such:
 * MedianFinder* obj = medianFinderCreate();
 * medianFinderAddNum(obj, num);
 
 * double param_2 = medianFinderFindMedian(obj);
 
 * medianFinderFree(obj);
*/
