//
//  leetcode128.c
//  myleetcodetest
//
//  Created by jason on 2024-06-13.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "leetcode128.h"

int compareLT128(const void* a, const void* b) {
    int ia = *((int*)a);
    int ib = *((int*)b);
    return ia - ib;
}

int longestConsecutiveBySort(int* nums, int numsSize) {
    if (numsSize == 0) {
        return 0;
    }

    qsort(nums, numsSize, sizeof(int), compareLT128);

    printf("Sorted: ");
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    int maxlen = 0;
    int seqlen = 1;
    int prev = nums[0];
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] == prev) {
            // prev remain the same
        } else if (nums[i] == prev + 1) {
            prev = nums[i];
            seqlen ++;
        } else {
            prev = nums[i];
            if (seqlen > maxlen) {
                maxlen = seqlen;
            }
            seqlen = 1;
        }
    }

    return maxlen > seqlen ? maxlen : seqlen;
}

typedef struct {
    int key;
    int val;
    int isOccupied;
} HASHNODE;

int hashFunction(int key, int capacity) {
    unsigned int hash = (unsigned int)key;
    hash = (hash * 2654435761) % capacity;
    return hash;
}

void insertHashLT128(HASHNODE* hash, int hashsize, int minVal, int maxVal, int key, int val) {
    //printf("Insert %d\n", key);
    if (key < minVal || key > maxVal) {
        return;
    }
    int k = (key - minVal) % hashsize;
    for (int i = 0; i < hashsize; i++) {
        if (hash[k].isOccupied == 0) {
            //printf("Insert %d in %d\n", key, k);
            hash[k].key = key;
            hash[k].val = val;
            hash[k].isOccupied = 1;
            break;
        }
        //printf("Skip %d insert %d, hashsize %d\n", k, key, hashsize);
        k = (k + 1) % hashsize;
    }
}

int getHash(HASHNODE* hashList, int hashsize, int minVal, int maxVal, int key) {
    if (key < minVal || key > maxVal) {
        return -1;
    }
    int k = (key - minVal) % hashsize;
    //printf("Search by %d, key %d, minVal %d, maxVal %d\n", k, key, minVal, maxVal);
    for (int i = 0; i < hashsize; i++) {
        if (hashList[k].isOccupied == 1 && hashList[k].key == key) {
            //printf("Found %d\n", hashList[k].key);
            return hashList[k].val;
        }
        if (hashList[k].isOccupied == 0) {
            //printf("Cannot find %d\n", key);
            return -1;
        }
        //printf("Conflict %d: %d\n", k, hashList[k].key);
        k = (k + 1) % hashsize;
    }
    return -1;
}

int longestConsecutive(int* nums, int numsSize) {
    int hashsize = numsSize * 10;
    HASHNODE* hashList = (HASHNODE*)malloc(hashsize * sizeof(HASHNODE));
    for (int i = 0; i < hashsize; i++) {
        hashList[i].key = 0;
        hashList[i].val = 0;
        hashList[i].isOccupied = 0;
    }
    int minVal = INT_MAX;
    int maxVal = INT_MIN;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > maxVal) {
            maxVal = nums[i];
        }
        if (nums[i] < minVal) {
            minVal = nums[i];
        }
    }
    for (int i = 0; i < numsSize; i++) {
        insertHashLT128(hashList, hashsize, minVal, maxVal, nums[i], i);
    }
    //printf("Max %d, Min %d\n", maxVal, minVal);
    //for (int i = 0; i < hashsize; i++) {
    //    printf("%d,%d ", hashList[i].key, hashList[i].isOccupied);
    //}
    //printf("\n");

    int ret = 0;
    for (int i = 0; i < numsSize; i++) {
        if (getHash(hashList, hashsize, minVal, maxVal, nums[i] - 1) != -1) {
            //printf("Ignore %d\n", nums[i]);
            continue;
        }

        if (maxVal - nums[i] + 1 <= ret) {
            continue;
        }

        int v = nums[i] + 1;
        int seqlen = 1;
        while (getHash(hashList, hashsize, minVal, maxVal, v) != -1) {
            seqlen ++;
            v ++;
        }
        if (seqlen > ret) {
            ret = seqlen;
        }
    }

    return ret;
}

// Function to find the length of the longest consecutive elements sequence
int longestConsecutiveChatGPT(int* nums, int numsSize) {
    if (numsSize == 0) return 0;

    // Create a hash set (using a simple array)
    int* hashSet = (int*)calloc(numsSize, sizeof(int));
    int* values = (int*)malloc(numsSize * sizeof(int));
    int setSize = 0;

    // Add elements to the hash set
    for (int i = 0; i < numsSize; i++) {
        int found = 0;
        for (int j = 0; j < setSize; j++) {
            if (values[j] == nums[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            values[setSize] = nums[i];
            setSize++;
        }
    }

    int longestStreak = 0;

    // Find the longest consecutive sequence
    for (int i = 0; i < setSize; i++) {
        int currentNum = values[i];
        int found = 0;
        for (int j = 0; j < setSize; j++) {
            if (values[j] == currentNum - 1) {
                found = 1;
                break;
            }
        }
        if (!found) {
            int currentStreak = 1;

            while (1) {
                int foundNext = 0;
                for (int j = 0; j < setSize; j++) {
                    if (values[j] == currentNum + 1) {
                        foundNext = 1;
                        break;
                    }
                }
                if (foundNext) {
                    currentNum += 1;
                    currentStreak += 1;
                } else {
                    break;
                }
            }

            if (currentStreak > longestStreak) {
                longestStreak = currentStreak;
            }
        }
    }

    free(hashSet);
    free(values);

    return longestStreak;
}
