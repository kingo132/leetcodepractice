//
//  leetcode207.c
//  myleetcodetest
//
//  Created by jason on 2024-06-30.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#include "leetcode207.h"

bool canFinish(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize) {
    int* inDeg = (int*)malloc(numCourses * sizeof(int));
    memset(inDeg, 0, numCourses * sizeof(int));

    for (int i = 0; i < prerequisitesSize; i++) {
        inDeg[prerequisites[i][0]] ++;
    }

    while (1) {
        int i = 0;
        for (; i < numCourses; i++) {
            if (inDeg[i] == 0) {
                break;
            }
        }
        if (i != numCourses) {
            // take course i
            inDeg[i] = -1;
            //printf("take course %d\n", i);
            for (int j = 0; j < prerequisitesSize; j++) {
                if (prerequisites[j][1] == i) {
                    inDeg[prerequisites[j][0]] --;
                }
            }
        } else {
            break;
        }
    }

    for (int i = 0; i < numCourses; i++) {
        if (inDeg[i] > 0) {
            free(inDeg);
            return false;
        }
    }

    return true;
}
