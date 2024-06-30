//
//  leetcode1497.c
//  myleetcodetest
//
//  Created by jason on 2024-06-21.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

#include "leetcode1497.h"

void dumpAry(const char* prefix, int* arr, int lvl, bool rst) {
    printf("%s: ", prefix);
    for (int i = 0; i < lvl; i++) {
        printf("(%d,%d) ", arr[i * 2], arr[i * 2 + 1]);
    }
    printf(" = %s\n", rst ? "True" : "False");
}

bool canArrangeHelper(int* arr, int arrSize, int k, unsigned char* visited, int ii, int level, int* aryForDump) {
    //if (level >= 2) {
    //    return false;
    //}
    for (int i = ii; i < arrSize; i++) {
        for (int j = i + 1; j < arrSize; j++) {
            if (visited[i] == 0 && visited[j] == 0 && (arr[i] + arr[j]) % k == 0) {
                aryForDump[level * 2] = arr[i];
                aryForDump[level * 2 + 1] = arr[j];
                if (level + 1 >= arrSize / 2) {
                    dumpAry("Found", aryForDump, level + 1, true);
                    return true;
                }
                visited[i] = 1;
                visited[j] = 1;
                if (canArrangeHelper(arr, arrSize, k, visited, ii + 1, level + 1, aryForDump)) {
                    return true;
                }
                dumpAry("Not found", aryForDump, level + 1, false);
                visited[i] = 0;
                visited[j] = 0;
            }
        }
    }
    return false;
}

bool canArrangeHelper2(int* arr, int arrSize, int* candAry, int candCnt, unsigned char* visited, int ii, int level, int* aryForDump) {
    for (int i = ii; i < candCnt; i++) {
        if (visited[candAry[i * 2]] == 0 && visited[candAry[i * 2 + 1]] == 0) {
            //aryForDump[level * 2] = arr[candAry[i * 2]];
            //aryForDump[level * 2 + 1] = arr[candAry[i * 2 + 1]];
            if (level + 1 >= arrSize / 2) {
                //dumpAry("Found", aryForDump, level + 1, true);
                return true;
            }
            visited[candAry[i * 2]] = 1;
            visited[candAry[i * 2 + 1]] = 1;
            if (canArrangeHelper2(arr, arrSize, candAry, candCnt, visited, ii + 1, level + 1, aryForDump)) {
                return true;
            }
            //dumpAry("Not found", aryForDump, level + 1, false);
            visited[candAry[i * 2]] = 0;
            visited[candAry[i * 2 + 1]] = 0;
        }
    }
    return false;
}

bool canArrangeMy(int* arr, int arrSize, int k) {
    unsigned char* visited = (unsigned char*)malloc(arrSize * sizeof(char));
    for (int i = 0; i < arrSize; i++) {
        visited[i] = 0;
    }

    int maxCandCnt = 10000;
    int* candAry = (int*)malloc(maxCandCnt * sizeof(int));
    int candCnt = 0;

    for (int i = 0; i < arrSize; i++) {
        for (int j = i + 1; j < arrSize; j++) {
            if ((arr[i] + arr[j]) % k == 0) {
                if (candCnt * 2 >= maxCandCnt) {
                    printf("Max cand exceed.\n");
                    return false;
                }
                printf("(%d,%d) ", arr[i], arr[j]);
                candAry[candCnt * 2] = i;
                candAry[candCnt * 2 + 1] = j;
                candCnt ++;
            }
        }
    }
    printf("\n");
    
    if (candCnt * 2 < arrSize) {
        return false;
    }

    int* aryForDump = (int*)malloc(arrSize * sizeof(int));
    return canArrangeHelper2(arr, arrSize, candAry, candCnt, visited, 0, 0, aryForDump);

    int* idxAry = (int*)malloc((arrSize / 2) * sizeof(int));
    idxAry[0] = 0;
    for (int i = 1; i < (arrSize / 2); i++) {
        idxAry[i] = idxAry[i - 1] + 1;
    }
    while (1) {
        //for (int i = 0; i < (arrSize / 2); i++) {
        //    printf("%d, ", idxAry[i]);
        //}
        for (int i = 0; i < arrSize; i++) {
            visited[i] = 0;
        }
        int i = 0;
        for (; i < (arrSize / 2); i++) {
            //printf("Invalid idx: %d.\n", candAry[idxAry[i] * 2]);
            if (idxAry[i] * 2 + 1 > maxCandCnt - 1 || candAry[idxAry[i] * 2] > arrSize - 1 || candAry[idxAry[i] * 2 + 1] > arrSize - 1) {
                printf("Invalid idx: %d.\n", idxAry[i] * 2 + 1);
                return false;
            }
            if (visited[candAry[idxAry[i] * 2]] || visited[candAry[idxAry[i] * 2 + 1]]) {
                break;
            }
            visited[candAry[idxAry[i] * 2]] = 1;
            visited[candAry[idxAry[i] * 2 + 1]] = 1;
        }
        if (i == (arrSize / 2)) {
            //printf(", True.\n");
            return true;
        }
        //printf(", False.\n");

        if (idxAry[(arrSize / 2) - 1] >= candCnt - 1) {
            int j = (arrSize / 2) - 2;
            for (; j >= 0; j--) {
                int maxIdxVal = candCnt - (arrSize / 2) + j;
                if (idxAry[j] < maxIdxVal) {
                    idxAry[j] ++;
                    for (int l = j + 1; l < (arrSize / 2); l++) {
                        idxAry[l] = idxAry[l - 1] + 1;
                    }
                    break;
                }
            }
            if (j < 0) {
                break;
            }
        } else {
            idxAry[(arrSize / 2) - 1] ++;
        }
    }

    return false;

    int startCand = 0;
    while (startCand <= candCnt - k) {
        for (int i = 0; i < arrSize; i++) {
            visited[i] = 0;
        }
        visited[candAry[startCand * 2]] = 1;
        visited[candAry[startCand * 2 + 1]] = 1;
        printf("(%d,%d) ", arr[candAry[startCand * 2]], arr[candAry[startCand * 2 + 1]]);
        int prevCand = startCand;
        int i = 0;
        for (; i < k; i++) { // Pick k times
            int j = prevCand + 1;
            for (; j < candCnt; j++) {
                if (visited[candAry[j * 2]] == 0 && visited[candAry[j * 2 + 1]] == 0) {
                    printf("(%d,%d) ", arr[candAry[j * 2]], arr[candAry[j * 2 + 1]]);
                    visited[candAry[j * 2]] = 1;
                    visited[candAry[j * 2 + 1]] = 1;
                    prevCand = j;
                    break;
                }
            }
            if (j == candCnt) {
                // Not found
                break;
            }
        }
        if (i == k) {
            printf(", True.\n");
            return true;
        }
        printf(", False.\n");
        startCand ++;
    }
    
    return false;

    //int* aryForDump = (int*)malloc(arrSize * sizeof(int));
    //return canArrangeHelper(arr, arrSize, k, visited, 0, 0, aryForDump);
}

// ChatGPT 的答案
bool canArrange(int* arr, int arrSize, int k) {
    // Array to count occurrences of each remainder
    int remainderCount[k];
    for (int i = 0; i < k; i++) {
        remainderCount[i] = 0;
    }

    // Count occurrences of each remainder
    for (int i = 0; i < arrSize; i++) {
        int remainder = arr[i] % k;
        if (remainder < 0) {
            remainder += k; // Ensure remainder is non-negative
        }
        remainderCount[remainder]++;
    }

    // Check if pairs can be formed
    // 整除k的必须要偶数个
    if (remainderCount[0] % 2 != 0) {
        return false; // Pairs with sum of zero remainder must be even
    }

    // 其余的必须要成对
    for (int i = 1; i <= k / 2; i++) {
        if (remainderCount[i] != remainderCount[k - i]) {
            return false;
        }
    }

    return true;
}

void leetcode1497Main(void) {
    int arr[] = {1,2,3,4,5,6};
    canArrange(arr, sizeof(arr) / sizeof(int), 10);
}
