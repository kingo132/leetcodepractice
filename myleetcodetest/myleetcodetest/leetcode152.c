#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

int maxProductMyMy(int* nums, int numsSize) {
    int* newAry = (int*)malloc(numsSize * sizeof(int));
    int* negCnt = (int*)malloc(numsSize * sizeof(int));
    int* lastNeg = (int*)malloc(numsSize * sizeof(int));
    int cnt = 0, last = -1;
    for (int i = numsSize - 1; i >= 0; i--) {
        if (nums[i] == 0) {
            cnt = 0;
            last = -1;
        } else if (nums[i] < 0) {
            cnt++;
            negCnt[i] = cnt;
            if (last == -1) {
                last = i;
            }
            lastNeg[i] = last;
        }
    }
    int newIdx = 0;
    int curMul = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] < 0) {
            if (negCnt[i] == 1) {
                if (curMul != 0) {
                    newAry[newIdx++] = curMul;
                    curMul = 0;
                }
                newAry[newIdx++] = nums[i];
            } else if (negCnt[i] % 2 == 0) {
                int tmp = 0;
                if (curMul != 0) {
                    tmp = curMul;
                    curMul = 0;
                }
                while (i < numsSize && nums[i] != 0) {
                    if (tmp == 0) {
                        tmp = nums[i];
                    } else {
                        tmp *= nums[i];
                    }
                    i++;
                }
                newAry[newIdx++] = tmp;
                if (i < numsSize) { // encounter 0
                    newAry[newIdx++] = 0;
                }
            } else {
                int n1 = 0, n2 = 0, n3 = 0;
                if (curMul != 0) {
                    n1 = curMul;
                    curMul = 0;
                }
                for (int j = i + 1; j <= lastNeg[i] - 1; j++) {
                    if (n2 == 0) {
                        n2 = nums[j];
                    } else {
                        n2 *= nums[j];
                    }
                }
                int k = lastNeg[i] + 1;
                while (k < numsSize && nums[k] != 0) {
                    if (n3 == 0) {
                        n3 = nums[k];
                    } else {
                        n3 *= nums[k];
                    }
                    k++;
                }
                //printf("%d,%d,%d,%d,%d,%d\n", i, n1, nums[i], n2, nums[lastNeg[i]], n3);
                int a = nums[i] * n2;
                if (n1 != 0) {
                    a *= n1;
                }
                int b = n2 * nums[lastNeg[i]];
                if (n3 != 0) {
                    b *= n3;
                }
                if (a > b) {
                    newAry[newIdx++] = a;
                    newAry[newIdx++] = nums[lastNeg[i]];
                    if (n3 != 0) {  
                        newAry[newIdx++] = n3;
                    }
                } else {
                    if (n1 != 0) {
                        newAry[newIdx++] = n1;
                    }
                    newAry[newIdx++] = nums[i];
                    newAry[newIdx++] = b;
                }
                i = k;
            }
        } else if (nums[i] == 0) {
            // Just output
            if (curMul != 0) {
                newAry[newIdx++] = curMul;
                curMul = 0;
            }
            newAry[newIdx++] = 0;
        } else { // > 0
            // Multiple
            if (curMul == 0) {
                curMul = nums[i];
            } else {
                curMul *= nums[i];
            }
        }
    }
    if (curMul != 0) {
        newAry[newIdx++] = curMul;
        curMul = 0;
    }

    int max = INT_MIN;
    for (int i = 0; i < newIdx; i++) {
        if (newAry[i] > max) {
            max = newAry[i];
        }
        printf("%d ", newAry[i]);
    }
    printf("\n");
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", negCnt[i]);
    }
    printf("\n");
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", lastNeg[i]);
    }
    printf("\n");
    return max;
}

// This solution will integer overflow
int maxProductChatGPT(int* nums, int numsSize) {
    if (numsSize == 0) return 0;
    
    int maxProduct = nums[0];
    int minProduct = nums[0];
    int result = nums[0];
    
    for (int i = 1; i < numsSize; i++) {
        int currentNum = nums[i];
        
        if (currentNum < 0) {
            int temp = maxProduct;
            maxProduct = minProduct;
            minProduct = temp;
        }
        
        maxProduct = currentNum > currentNum * maxProduct ? currentNum : currentNum * maxProduct;
        minProduct = currentNum < currentNum * minProduct ? currentNum : currentNum * minProduct;
        
        if (maxProduct > result) {
            result = maxProduct;
        }

        printf("max: %d, min: %d, res: %d\n", maxProduct, minProduct, result);
    }
    
    return result;
}

int maxProductError(int* nums, int numsSize) {
    int maxPdtSoFar = INT_MIN, maxEndingHere = 0;
    for (int i = 0; i < numsSize; i++) {
        if (maxEndingHere == 0) {
            maxEndingHere = nums[i];
        } else {
            maxEndingHere *= nums[i];
        }

        if (maxEndingHere > maxPdtSoFar) {
            maxPdtSoFar = maxEndingHere;
        }

        //if (maxEndingHere < 0) {
        //    maxEndingHere = 0;
        //}
        printf("i: %d, maxPdt: %d, maxEnding: %d\n", i, maxPdtSoFar, maxEndingHere);
    }
    return maxPdtSoFar;
}