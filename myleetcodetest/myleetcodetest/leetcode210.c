//
//  leetcode210.c
//  myleetcodetest
//
//  Created by jason on 2024-06-29.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#include "leetcode210.h"

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

bool findAllPrerequisites(int startFrom, unsigned char* visited, int numCourses, int** prerequisites, int prerequisitesSize, int* retAry, int* returnSize) {
    for (int i = 0; i < prerequisitesSize; i++) {
        //printf("%d,%d,%d\n", i, prerequisites[i][0], prerequisites[i][1]);
        if (prerequisites[i][0] == startFrom) {
            if (visited[prerequisites[i][1]] == 2) {
                printf("find loop: %d\n", prerequisites[i][1]);
                return false;
            } else if (visited[prerequisites[i][1]] == 0) {
                //printf("find: %d\n", prerequisites[i][1]);
                visited[prerequisites[i][1]] = 2;
                if (!findAllPrerequisites(prerequisites[i][1], visited, numCourses, prerequisites, prerequisitesSize, retAry, returnSize)) {
                    return false;
                }
            }
        }
    }

    //printf("take course: %d\n", startFrom);
    visited[startFrom] = 1;
    retAry[(*returnSize)++] = startFrom;
    return true;
}

int* findOrder(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize, int* returnSize) {
    unsigned char* visited = (unsigned char*)malloc(numCourses * sizeof(unsigned char));
    for (int i = 0; i < numCourses; i++) {
        visited[i] = 0; // 0 not visited, 1 visited, 2 searching
    }

    *returnSize = 0;
    int* retAry = (int*)malloc(numCourses * sizeof(int));

    for (int i = 0; i < numCourses; i++) {
        if (visited[i] == 1) {
            continue;
        }
        unsigned char hasParent = 0;
        for (int j = 0; j < prerequisitesSize; j++) {
            if (prerequisites[j][1] == i) {
                hasParent = 1;
                break;
            }
        }
        if (! hasParent) {
            printf("Start from: %d\n", i);
            if (! findAllPrerequisites(i, visited, numCourses, prerequisites, prerequisitesSize, retAry, returnSize)) {
                free(retAry);
                *returnSize = 0;
                return NULL;
            }
        }
    }

    for (int i = 0; i < numCourses; i++) {
        for (int j = 0; j < prerequisitesSize; j++) {
            if (visited[prerequisites[j][0]] != 1) {
                free(retAry);
                *returnSize = 0;
                return NULL;
            }
        }
    }

    return retAry;
}
