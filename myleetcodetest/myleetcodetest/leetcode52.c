#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

bool canPosition(char** board, int n, int ii, int jj) {
    for (int i = 0; i < n; i++) {
        if (board[i][jj] == 'Q') {
            return false;
        }
    }

    for (int j = 0; j < n; j++) {
        if (board[ii][j] == 'Q') {
            return false;
        }
    }

    int i = ii - 1, j = jj - 1;
    while (i >= 0 && j >= 0) {
        if (board[i][j] == 'Q') {
            return false;
        }
        i--;
        j--;
    }
    i = ii + 1, j = jj + 1;
    while (i < n && j < n) {
        if (board[i][j] == 'Q') {
            return false;
        }
        i++;
        j++;
    }

    i = ii - 1, j = jj - 1;
    while (i >= 0 && j >= 0) {
        if (board[i][j] == 'Q') {
            return false;
        }
        i--;
        j--;
    }

    i = ii - 1, j = jj + 1;
    while (i >= 0 && j < n) {
        if (board[i][j] == 'Q') {
            return false;
        }
        i--;
        j++;
    }

    i = ii + 1, j = jj - 1;
    while (i < n && j >= 0) {
        if (board[i][j] == 'Q') {
            return false;
        }
        i++;
        j--;
    }

    return true;
}

void dumpMat(const char* prefix, char** board, int n) {
    printf("%s\n", prefix);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

int totalNQueensHelper(char** board, int n, int i) {
    if (i == n) {
        dumpMat("Found:", board, n);
        return 1;
    }
    int cnt = 0;
    for (int j = 0; j < n; j++) {
        if (canPosition(board, n, i, j)) {
            board[i][j] = 'Q';
            cnt += totalNQueensHelper(board, n, i + 1);
            board[i][j] = '.';
        }
    }
    return cnt;
}

int totalNQueens(int n) {
    char** board = (char**)malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++) {
        board[i] = (char*)malloc(n * sizeof(char));
        for (int j = 0; j < n; j++) {
            board[i][j] = '.';
        }
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        board[0][i] = 'Q';
        cnt += totalNQueensHelper(board, n, 1);
        board[0][i] = '.';
    }
    for (int i = 0; i < n; i++) {
        free(board[i]);
    }
    free(board);
    return cnt;
}