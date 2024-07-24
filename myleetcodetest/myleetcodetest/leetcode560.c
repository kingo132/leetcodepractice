#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

int subarraySumOld(int* nums, int numsSize, int k) {
    int* dpMin = (int*)malloc(numsSize * sizeof(int));
    int* dpMax = (int*)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        dpMin[i] = INT_MAX;
        dpMax[i] = INT_MIN;
    }

    int cnt = 0;
    for (int i = 0; i < numsSize; i++) {
        int max = numsSize - i;
        if (dpMax[i] != INT_MIN) {
            max = dpMax[i];
        }
        int min = 1;
        if (dpMin[i] != INT_MAX) {
            min = dpMin[i];
        }

        int sum = 0;
        for (int wnd = min; wnd <= max; wnd++) {
            //printf("%d,%d,%d,%d,%d\n", i, wnd, i + wnd - 1, min, max);
            if (wnd == min) {
                for (int j = i; j < i + wnd; j++) {
                    sum += nums[j];
                }
            } else {
                sum += nums[i + wnd - 1];
            }
            
            if (sum == k) {
                printf("Found %d,%d\n", i, wnd);
                cnt++;
                dpMin[i] = dpMax[i] = wnd;
                //break;
            } /*else if (sum > k) {
                dpMax[i] = wnd;
                break;
            } else { // sum < k
                dpMin[i] = wnd;
            }*/
        }
    }

    for (int i = 0; i < numsSize; i++) {
        printf("%d ", dpMin[i]);
    }
    printf("\n");
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", dpMax[i]);
    }
    printf("\n");

    free(dpMin);
    free(dpMax);
    return cnt;
}

int subarraySumOld2(int* nums, int numsSize, int k) {
    int cnt = 0;
    int* prefixSum = (int*)malloc((numsSize + 1) * sizeof(int));
    prefixSum[0] = 0;
    for (int i = 0; i < numsSize; i++) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    for (int i = 0; i < numsSize; i++) {
        for (int j = i; j < numsSize; j++) {
            if (prefixSum[j + 1] - prefixSum[i] == k) {
                cnt++;
            }
        }
    }

    for (int i = 0; i < numsSize + 1; i++) {
        printf("%d ", prefixSum[i]);
    }
    printf("\n");

    free(prefixSum);
    return cnt;
}

typedef struct {
    int k;
    int v;
    int isOcc;
} HashNode;

#define MAXHASHSIZE 100000

void addHash(HashNode* hs, int key, int val) {
    int k = (key < 0 ? -key : key) % MAXHASHSIZE;
    for (int i = 0; i < MAXHASHSIZE; i++) {
        if (hs[k].isOcc == 0) {
            hs[k].k = key;
            hs[k].v = val;
            hs[k].isOcc = 1;
            return;
        } else if (hs[k].isOcc == 1 && hs[k].k == key) {
            hs[k].v = val;
            return;
        }
        k = (k + 1) % MAXHASHSIZE;
    }
}

int getHash(HashNode* hs, int key) {
    int k = (key < 0 ? -key : key) % MAXHASHSIZE;
    for (int i = 0; i < MAXHASHSIZE; i++) {
        if (hs[k].isOcc == 0) {
            return -1;
        }
        if (hs[k].k == key) {
            return hs[k].v;
        }
        k = (k + 1) % MAXHASHSIZE;
    }
    return -1;
}

int subarraySum(int* nums, int numsSize, int k) {
    HashNode* hs = (HashNode*)malloc(MAXHASHSIZE * sizeof(HashNode));
    memset(hs, 0, MAXHASHSIZE * sizeof(HashNode));

    addHash(hs, 0, 1);

    int cnt = 0, sum = 0;
    for (int i = 0; i < numsSize; i++) {
        sum += nums[i];
        int v1 = getHash(hs, sum - k);
        if (v1 != -1) {
            cnt += v1;
        }
        int v2 = getHash(hs, sum);
        if (v2 == -1) {
            addHash(hs, sum, 1);
        } else {
            addHash(hs, sum, v2 + 1);
        }
        //printf("i: %d, sum: %d, v1: %d, v2: %d, cnt: %d\n", i, sum, v1, v2, cnt);
    }

    free(hs);
    return cnt;
}