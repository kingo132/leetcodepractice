//
//  leetcode1143.c
//  myleetcodetest
//
//  Created by jason on 2024-07-05.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode1143.h"

int longestCommonSubsequence(char* text1, char* text2) {
    int len1 = 0, len2 = 0;
    char* p = text1;
    while (*p) {
        len1++;
        p++;
    }
    p = text2;
    while (*p) {
        len2++;
        p++;
    }
    int** dpm = (int**)malloc(len1 * sizeof(int*));
    for (int i = 0; i < len1; i++) {
        dpm[i] = (int*)malloc(len2 * sizeof(int));
        for (int j = 0; j < len2; j++) {
            dpm[i][j] = 0;
        }
    }

    for (int i = len1 - 1; i >= 0; i--) {
        for (int j = len2 - 1; j >= 0; j--) {
            int right = 0, down = 0, diag = 0;
            if (i != len1 - 1) {
                down = dpm[i+1][j];
            }
            if (j != len2 - 1) {
                right = dpm[i][j+1];
            }
            if (i != len1 - 1 && j != len2 - 1) {
                diag = dpm[i+1][j+1];
            }
            int max = down > right ? down : right;
            max = diag > max ? diag : max;
            int min = down < right ? down : right;
            min = diag < min ? diag : min;

            /*
            if (text1[i] == text2[j]) {
                dpm[i][j] = 1 + diag;
            } else {
                dpm[i][j] = max;
            }
            */
            // 下面是正确答案
            if (text1[i] == text2[j]) {
                // 相等则同时去掉一个字符
                dpm[i][j] = 1 + diag;
            } else {
                // 不相等则各自去掉一个字符，看下剩下的长度
                dpm[i][j] = right > down ? right : down;
            }
        }
    }

    /*
    printf("  ");
    for (int i = 0; i < len2; i++) {
        printf("%c ", text2[i]);
    }
    printf("\n");
    for (int i = 0; i < len1; i++) {
        printf("%c ", text1[i]);
        for (int j = 0; j < len2; j++) {
            printf("%d ", dpm[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    */

    return dpm[0][0];
}
