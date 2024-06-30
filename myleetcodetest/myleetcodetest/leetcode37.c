//
//  leetcode37.c
//  myleetcodetest
//
//  Created by jason on 2024-06-16.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "leetcode37.h"

int sodukuHelper(char** board, int rowCnt, int colCnt) {
    int ii = 0;
    int jj = 0;
    for (ii = 0; ii < rowCnt; ii++) {
        for (jj = 0; jj < colCnt; jj++) {
            if (board[ii][jj] == '.') {
                break;
            }
        }
        if (jj != colCnt) {
            break;
        }
    }
    if (ii == rowCnt && jj == colCnt) {
        // all set
        return 0;
    }

    int digitAry[10] = {0};
    for (int i = 0; i < rowCnt; i++) {
        if (board[i][jj] != '.') {
            digitAry[board[i][jj] - '0'] = 1;
        }
    }
    for (int i = 0; i < colCnt; i++) {
        if (board[ii][i] != '.') {
            digitAry[board[ii][i] - '0'] = 1;
        }
    }
    int sqStartX = ii - ii % 3;
    int sqStartY = jj - jj % 3;
    for (int i = sqStartX; i < sqStartX + 3; i++) {
        for (int j = sqStartY; j < sqStartY + 3; j++) {
            if (board[i][j] != '.') {
                digitAry[board[i][j] - '0'] = 1;
            }
        }
    }

    for (int i = 1; i < 10; i++) {
        if (digitAry[i] == 0) {
            //printf("Try %d at %d,%d\n", i, ii, jj);
            board[ii][jj] = '0' + i;
            if (sodukuHelper(board, rowCnt, colCnt) == 0) {
                return 0;
            }
        }
    }

    board[ii][jj] = '.';
    return -1;
}

void solveSudoku(char** board, int boardSize, int* boardColSize){
    sodukuHelper(board, boardSize, boardColSize[0]);
}
