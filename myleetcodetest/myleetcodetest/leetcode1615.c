//
//  leetcode1615.c
//  myleetcodetest
//
//  Created by jason on 2024-07-10.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode1615.h"

int maximalNetworkRank(int n, int** roads, int roadsSize, int* roadsColSize) {
    int* roadCnt = (int*)malloc(n * sizeof(int));
    int* connectMat = (int*)malloc(n * n * sizeof(int));
    memset(roadCnt, 0, n * sizeof(int));
    for (int i = 0; i < n * n; i++) {
        connectMat[i] = 0;
    }

    for (int i = 0; i < roadsSize; i++) {
        roadCnt[roads[i][0]]++;
        roadCnt[roads[i][1]]++;
        connectMat[roads[i][0] * n + roads[i][1]] = 1;
        connectMat[roads[i][1] * n + roads[i][0]] = 1;
    }

    int max = INT_MIN;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int rank = roadCnt[i] + roadCnt[j];
            if (connectMat[i * n + j] != 0) {
                rank -= 1;
            }
            if (rank > max) {
                max = rank;
            }
        }
    }
    
    free(connectMat);
    free(roadCnt);
    return max;
}
