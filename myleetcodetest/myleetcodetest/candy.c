//
//  candy.c
//  test
//
//  Created by jason on 2024-05-21.
//

#include "candy.h"
#include <stdbool.h>
#include <stdlib.h>

float mathRound(float v) {
    if (v - (int)v >= 0.5) {
        return ((int)v) + 1;
    }
    return (int)v;
}

void dumpIntList(const char* prefix, int* list, int size) {
    printf("%s", prefix);
    for (int i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

void rightAddCandyList(int* candyList, int* ratings, int size, int i) {
    for (int j = i + 1; j < size; j++) {
        if (ratings[j] > ratings[j - 1] && candyList[j] <= candyList[j - 1]) {
            candyList[j] = candyList[j - 1] + 1;
        }
    }
}

void leftAddCandyList(int* candyList, int* ratings, int size, int i) {
    for (int j = i - 1; j >= 0; j--) {
        if (ratings[j] > ratings[j + 1] && candyList[j] <= candyList[j + 1]) {
            candyList[j] = candyList[j + 1] + 1;
        }
    }
}

int candy(int* ratings, int ratingsSize) {
    int sum = 0;
    for (int i = 0; i < ratingsSize; i++) {
        sum += ratings[i];
    }
    int* candyList = (int *)malloc(ratingsSize * sizeof(int));
    for (int i = 0; i < ratingsSize; i++) {
        int count = mathRound(ratings[i] / (float)sum);
        if (count <= 0) {
            count = 1;
        }
        candyList[i] = count;
    }
    for (int i = 0; i < ratingsSize; i++) {
        if (i > 0) {
            /* Has left neighbor */
            if (ratings[i] > ratings[i - 1] && candyList[i] <= candyList[i - 1]) {
                candyList[i] = candyList[i - 1] + 1;
                rightAddCandyList(candyList, ratings, ratingsSize, i);
            }
        }
        if (i < ratingsSize - 1) {
            /* Has right neighbor */
            if (ratings[i] > ratings[i + 1] && candyList[i] <= candyList[i + 1]) {
                candyList[i] = candyList[i + 1] + 1;
                leftAddCandyList(candyList, ratings, ratingsSize, i);
            }
        }
    }
    dumpIntList("candyList: ", candyList, ratingsSize);
    for (int i = 0; i < ratingsSize; i++) {
        while (candyList[i] > 1) {
            bool canDec = true;
            if (i > 0) {
                /* Has left neighbor */
                if (ratings[i] > ratings[i - 1]) {
                    if (candyList[i] <= candyList[i - 1] + 1) {
                        canDec = false;
                    }
                } else if (ratings[i] < ratings[i - 1]) {
                    /* Can dec in all the way */
                } else {
                    /* = */
                    /* Can dec in all the way */
                }
            }
            if (i < ratingsSize - 1) {
                /* Has right neighbor */
                if (ratings[i] > ratings[i + 1]) {
                    if (candyList[i] <= candyList[i + 1] + 1) {
                        canDec = false;
                    }
                } else if (ratings[i] < ratings[i + 1]) {
                    /* Can dec in all the way */
                } else {
                    /* = */
                    /* Can dec in all the way */
                }
            }
            if (! canDec) {
                break;
            } else {
                candyList[i] --;
                dumpIntList("deced candyList: ", candyList, ratingsSize);
            }
        }
    }
    sum = 0;
    dumpIntList("final candyList: ", candyList, ratingsSize);
    for (int i = 0; i < ratingsSize; i++) {
        sum += candyList[i];
    }
    return sum;
}

void candyMain(void) {
    int ratings[] = {1,2,87,87,87,2,1};
    printf("%d\n", candy(ratings, sizeof(ratings) / sizeof(int)));
}
