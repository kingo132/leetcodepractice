//
//  leetcode1013.c
//  myleetcodetest
//
//  Created by jason on 2024-06-20.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include "leetcode1013.h"

typedef struct {
    int k;
    short v;
    unsigned char isOccupied;
} HASHNODE;

int getSum(int* arr, int m, int n, HASHNODE* hashTable, int hashSize) {
    /*int key = (m << 16) + n;
    int k = key % hashSize;
    int savedSum = 0;
    for (int i = 0; i < hashSize; i++) {
        if (hashTable[k].isOccupied == 0) {
            break;
        } else {
            if (hashTable[k].k == key) {
                savedSum = hashTable[k].v;
                break;
            }
        }
        k = (k + 1) % hashSize;
    }

    if (hashTable[k].k == key) {
        return savedSum;
    }*/

    int sum = 0;
    for (int i = m; i <= n; i++) {
        sum += arr[i];
    }

    /*k = key % hashSize;
    int i = 0;
    for (; i < hashSize; i++) {
        if (hashTable[k].isOccupied == 0) {
            hashTable[k].k = key;
            hashTable[k].v = sum;
            hashTable[k].isOccupied = 1;
            break;
        }
        k = (k + 1) % hashSize;
    }

    if (i == hashSize) {
        printf("Hash table overflow.\n");
    }*/

    return sum;
}

bool canThreePartsEqualSum(int* arr, int arrSize) {
    int totalSum = 0;
    for (int i = 0; i < arrSize; i++) {
        totalSum += arr[i];
    }

    if (totalSum % 3 != 0) {
        return false;
    }

    totalSum /= 3;

    int x = 0, y = arrSize - 1;
    int sum1 = arr[x], sum2 = 0, sum3 = arr[y];
    for (int i = x + 1; i < y; i++) {
        sum2 += arr[i];
    }

    while (x < y - 1) {
        if (sum1 != totalSum) {
            x ++;
            sum1 += arr[x];
            sum2 -= arr[x];
        } else if (sum3 != totalSum) {
            y --;
            sum3 += arr[y];
            sum2 -= arr[y];
        } else if (sum2 == totalSum) {
            return true;
        }
    }

    return false;

    //int hashSize = 500000;
    //HASHNODE* hashTable = (HASHNODE*)malloc(hashSize * sizeof(HASHNODE));
    //for (int i = 0; i < hashSize; i++) {
    //    hashTable[i].isOccupied = 0;
    //}
    
    /*
    int sum1 = 0;
    for (int i = 0; i < arrSize - 2; i ++) {
        sum1 += arr[i];
        if (sum1 == totalSum / 3) {
            int sum2 = arr[i + 1];
            for (int j = i + 2; j < arrSize; j ++) {
                sum2 += arr[j];
                if (sum2 == totalSum / 3) {
                    int sum3 = 0;

                }
            }
        }
        */
        /*for (int j = i + 2; j < arrSize; j ++) {
            sum2 += arr[j];
            sum3 -= arr[j];
            if (getSum(arr, 0, i, hashTable, hashSize) == totalSum / 3) {
                if (getSum(arr, i + 1, j - 1, hashTable, hashSize) == totalSum / 3) {
                    if (getSum(arr, j, arrSize - 1, hashTable, hashSize) == totalSum / 3) {
                        return true;
                    }
                }
            }
        }
    }*/
    //return false;
}
