//
//  wordsearch.c
//  test
//
//  Created by jason on 2024-05-21.
//

#include <stdbool.h>
#include <stdlib.h>
#include "wordsearch.h"

char getUnusedNeighbor(char** board, int boardSize, int* boardColSize, char* boardMark, int i, int j, int direction) {
    /* Direction: 1 left, 2 right, 3 up, 4 down */
    if (i < 0 || i >= boardSize || j < 0 || j >= *boardColSize) {
        return -1;
    }
    if (direction == 1) {
        j --;
        if (j >= 0 && boardMark[i * (*boardColSize) + j] == 0) {
            boardMark[i * (*boardColSize) + j] = 1;
            return board[i][j];
        }
    } else if (direction == 2) {
        j ++;
        if (j <= (*boardColSize) - 1 && boardMark[i * (*boardColSize) + j] == 0) {
            boardMark[i * (*boardColSize) + j] = 1;
            return board[i][j];
        }
    } else if (direction == 3) {
        i --;
        if (i >= 0 && boardMark[i * (*boardColSize) + j] == 0) {
            boardMark[i * (*boardColSize) + j] = 1;
            return board[i][j];
        }
    } else if (direction == 4) {
        i ++;
        if (i <= boardSize - 1 && boardMark[i * (*boardColSize) + j] == 0) {
            boardMark[i * (*boardColSize) + j] = 1;
            return board[i][j];
        }
    }

    return -1;
}

bool existHelper(char** board, int boardSize, int* boardColSize, char* word, char* boardMark, int i, int j) {
    if ((*word) == 0) {
        /* Found */
        return true;
    }
    if (i < 0 || i >= boardSize || j < 0 || j >= *boardColSize) {
        return false;
    }
    
    //printf("Search in %d,%d for %c\n", i, j, *word);
    
    bool found = false;
    if (boardMark[i * (*boardColSize) + j] == 0 && board[i][j] == *word) {
        boardMark[i * (*boardColSize) + j] = 1;
        found = existHelper(board, boardSize, boardColSize, word + 1, boardMark, i, j - 1);
        if (! found) {
            found = existHelper(board, boardSize, boardColSize, word + 1, boardMark, i, j + 1);
        }
        if (! found) {
            found = existHelper(board, boardSize, boardColSize, word + 1, boardMark, i - 1, j);
        }
        if (! found) {
            found = existHelper(board, boardSize, boardColSize, word + 1, boardMark, i + 1, j);
        }
        boardMark[i * (*boardColSize) + j] = 0;
    }

    return found;
}

bool exist(char** board, int boardSize, int* boardColSize, char* word) {
    char* boardMark = (char *)malloc(boardSize * (*boardColSize));
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < *boardColSize; j++) {
            for (int k = 0; k < boardSize * (*boardColSize); k ++) {
                boardMark[k] = 0;
            }
            if (existHelper(board, boardSize, boardColSize, word, boardMark, i, j)) {
                return true;
            }
        }
    }

    return false;
}

void wordsearchMain(void) {
    int m = 3, n = 4;
    char** board = (char**)malloc(m * sizeof(char**));
    int* boardColSize = (int*)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        char* row = (char*)malloc(n * sizeof(char));
        boardColSize[i] = n;
        board[i] = row;
    }
    board[0][0] = 'A';
    board[0][1] = 'B';
    board[0][2] = 'C';
    board[0][3] = 'E';
    board[1][0] = 'S';
    board[1][1] = 'F';
    board[1][2] = 'C';
    board[1][3] = 'S';
    board[2][0] = 'A';
    board[2][1] = 'D';
    board[2][2] = 'E';
    board[2][3] = 'E';
    
    const char* word = "ABCCED";
    if (exist(board, m, boardColSize, word)) {
        printf("Exist\n");
    } else {
        printf("Not exist\n");
    }
}
