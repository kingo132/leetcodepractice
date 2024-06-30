//
//  leetcode692.c
//  myleetcodetest
//
//  Created by jason on 2024-06-18.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include "leetcode692.h"

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int stringcomp(const void* a, const void* b) {
    int ret = strcmp(*((const char**)a), *((const char**)b));
    //printf("%s <-> %s = %d\n", *((const char**)a), *((const char**)b), ret);
    return ret;
}

typedef struct {
    const char* str;
    int freq;
} HEAPNODE;

void swapHeapNodeLT692(HEAPNODE* a, HEAPNODE* b) {
    const char* tStr = a->str;
    int tFreq = a->freq;
    a->str = b->str;
    a->freq = b->freq;
    b->str = tStr;
    b->freq = tFreq;
}

int compareHeapNode(HEAPNODE* a, HEAPNODE* b) {
    if (a->freq != b->freq) {
        return a->freq - b->freq;
    }

    return -strcmp(a->str, b->str);
}

void downHeapifyLT692(HEAPNODE* minHeap, int heapSize, int startIdx) {
    if (heapSize <= 1) {
        return;
    }
    while (startIdx < heapSize - 1) {
        int leftIdx = startIdx * 2 + 1;
        int rightIdx = startIdx * 2 + 2;
        int minIdx = startIdx;
        if (leftIdx < heapSize && compareHeapNode(&minHeap[leftIdx], &minHeap[minIdx]) < 0) {
            minIdx = leftIdx;
        }
        if (rightIdx < heapSize && compareHeapNode(&minHeap[rightIdx], &minHeap[minIdx]) < 0) {
            minIdx = rightIdx;
        }
        if (startIdx != minIdx) {
            //printf("Swap %d <-> %d\n", startIdx, minIdx);
            swapHeapNodeLT692(&minHeap[startIdx], &minHeap[minIdx]);
            startIdx = minIdx;
        } else {
            break;
        }
    }
}

void minHeapInsert(HEAPNODE* minHeap, int* heapSize, int maxHeapSize, char* str, int freq) {
    if (*heapSize < maxHeapSize) {
        minHeap[*heapSize].str = str;
        minHeap[*heapSize].freq = freq;
        (*heapSize) ++;

        if (*heapSize == maxHeapSize) {
            printf("Trigger down heapify.\n");
            // 注意，这里down heapify的顺序，应该是从 size / 2 - 1 (最后一个左右子女非空节点)，开始往前走
            //for (int i = 0; i < maxHeapSize; i++) {
            for (int i = maxHeapSize / 2 - 1; i >= 0; i--) {
                downHeapifyLT692(minHeap, maxHeapSize, i);
            }
            // 注意：这里的heapify不能保证数组有序。要让数组有序，必须不停交换第一个和最后一个元素然后再heapify
        }
    } else {
        HEAPNODE n;
        n.str = str;
        n.freq = freq;
        if (compareHeapNode(&n, &minHeap[0]) > 0) {
            minHeap[0].str = str;
            minHeap[0].freq = freq;
            downHeapifyLT692(minHeap, maxHeapSize, 0);
        }
    }
}

char** topKFrequent(char** words, int wordsSize, int k, int* returnSize) {
    *returnSize = 0;
    qsort(words, wordsSize, sizeof(char*), stringcomp);
    for (int i = 0; i < wordsSize; i++) {
        printf("%s, ", words[i]);
    }
    printf("\n");

    HEAPNODE* minHeap = (HEAPNODE*)malloc(k * sizeof(HEAPNODE));
    int heapSize = 0;
    int freq = 1;
    for (int i = 0; i < wordsSize; i++) {
        //printf("i: %d\n", i);
        if (i == wordsSize - 1 || strcmp(words[i], words[i + 1]) != 0) {
            printf("Insert %s,%d to heap.\n", words[i], freq);
            minHeapInsert(minHeap, &heapSize, k, words[i], freq);
            freq = 1;
        } else {
            freq ++;
        }
    }

    char** retAry = (char**)malloc(k * sizeof(char*));

    printf("Dump heap: ");
    for (int i = 0; i < k; i++) {
        printf("%s,%d ", minHeap[i].str, minHeap[i].freq);
    }
    printf("\n");

    // 执行最小堆排序
    for (int i = 0; i < k; i++) {
        if (i != k - 1) {
            swapHeapNodeLT692(&minHeap[0], &minHeap[k - i - 1]);
            downHeapifyLT692(minHeap, k - i - 1, 0);
        }
    }

    // 反向输出，就是前k大
    printf("Gen result: ");
    for (int i = k - 1; i >= 0; i--) {
        int sl = strlen(minHeap[i].str);
        retAry[i] = (char*)malloc((sl + 1) * sizeof(char));
        memcpy(retAry[i], minHeap[i].str, sl);
        retAry[i][sl] = '\0';
        printf("%s,%d ", retAry[i], minHeap[i].freq);
    }
    printf("\n");

    *returnSize = k;

    return retAry;
}
