#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef struct {
    int iorj, d; // d: 1 hori, 2 verti
    int l, r;
} QueNode;

bool isDbg = false;

bool searchMatrixMy(int** matrix, int matrixSize, int* matrixColSize, int target) {
    int m = matrixSize, n = matrixColSize[0];
    int maxQueSize = m * n;
    if (maxQueSize < 10) {
        maxQueSize = 10;
    }
    QueNode* que = (QueNode*)malloc(maxQueSize * sizeof(QueNode));
    int front = 0, tail = 0, queSize = 0;

    int* visitedI = (int*)malloc(m * sizeof(int));
    memset(visitedI, 0, m * sizeof(int));
    int* visitedJ = (int*)malloc(n * sizeof(int));
    memset(visitedJ, 0, n * sizeof(int));

    que[tail].iorj = 0;
    que[tail].d = 1;
    que[tail].l = 0;
    que[tail].r = n - 1;
    visitedI[que[tail].iorj] = 1;
    tail++;
    que[tail].iorj = 0;
    que[tail].d = 2;
    que[tail].l = 0;
    que[tail].r = m - 1;
    visitedJ[que[tail].iorj] = 1;
    tail++;
    queSize += 2;
    while (queSize > 0) {
        int iorj = que[front].iorj;
        int d = que[front].d;
        int l = que[front].l;
        int r = que[front].r;
        front = (front + 1) % maxQueSize;
        queSize--;

        if (isDbg) printf("Check iorj: %d, d: %d, l: %d, r: %d\n", iorj, d, l, r);
        //if (i < 0 || i >= m || j < 0 || j >= n) {
        //    printf("Invalid %d,%d\n", i, j);
        //    break;
        //}

        if (d == 1) { // hori, iorj is i
            if (l <= r) {
                int mid = (l + r) / 2;
                if (target == matrix[iorj][mid]) {
                    free(que);
                    free(visitedI);
                    free(visitedJ);
                    return true;
                } else if (target > matrix[iorj][mid]) {
                    que[tail].iorj = iorj;
                    que[tail].d = d;
                    que[tail].l = mid + 1;
                    que[tail].r = r;
                    if (isDbg) printf("1Add iorj: %d, d: %d, l: %d, r: %d\n", iorj, d, l, r);
                    tail = (tail + 1) % maxQueSize;
                    queSize++;
                    if (visitedJ[mid] == 0) {
                        que[tail].iorj = mid;
                        que[tail].d = 2;
                        que[tail].l = iorj + 1;
                        que[tail].r = m - 1;
                        if (isDbg) printf("2Add iorj: %d, d: %d, l: %d, r: %d\n", iorj, d, l, r);
                        tail = (tail + 1) % maxQueSize;
                        queSize++;
                        visitedJ[mid] = 1;
                    }
                } else { // target < matrix[iorj][mid]
                    que[tail].iorj = iorj;
                    que[tail].d = d;
                    que[tail].l = l;
                    que[tail].r = mid - 1;
                    if (isDbg) printf("3Add iorj: %d, d: %d, l: %d, r: %d\n", iorj, d, l, r);
                    tail = (tail + 1) % maxQueSize;
                    queSize++;
                    if (visitedJ[mid] == 0) {
                        que[tail].iorj = mid;
                        que[tail].d = 2;
                        que[tail].l = 0;
                        que[tail].r = iorj - 1;
                        if (isDbg) printf("4Add iorj: %d, d: %d, l: %d, r: %d\n", iorj, d, l, r);
                        tail = (tail + 1) % maxQueSize;
                        queSize++;
                        visitedJ[mid] = 1;
                    }
                }

                
            }
        } else { // verti, iorj is j
            if (l <= r) {
                int mid = (l + r) / 2;
                if (target == matrix[mid][iorj]) {
                    free(que);
                    free(visitedI);
                    free(visitedJ);
                    return true;
                } else if (target > matrix[mid][iorj]) {
                    que[tail].iorj = iorj;
                    que[tail].d = d;
                    que[tail].l = mid + 1;
                    que[tail].r = r;
                    if (isDbg) printf("5Add iorj: %d, d: %d, l: %d, r: %d\n", iorj, d, l, r);
                    tail = (tail + 1) % maxQueSize;
                    queSize++;
                    if (visitedI[mid] == 0) {
                        que[tail].iorj = mid;
                        que[tail].d = 1;
                        que[tail].l = iorj + 1;
                        que[tail].r = n - 1;
                        if (isDbg) printf("6Add iorj: %d, d: %d, l: %d, r: %d\n", iorj, d, l, r);
                        tail = (tail + 1) % maxQueSize;
                        queSize++;
                        visitedI[mid] = 1;
                    }
                } else { // target < matrix[mid][iorj]
                    que[tail].iorj = iorj;
                    que[tail].d = d;
                    que[tail].l = l;
                    que[tail].r = mid - 1;
                    if (isDbg) printf("7Add iorj: %d, d: %d, l: %d, r: %d\n", iorj, d, l, r);
                    tail = (tail + 1) % maxQueSize;
                    queSize++;
                    if (visitedI[mid] == 0) {
                        que[tail].iorj = mid;
                        que[tail].d = 1;
                        que[tail].l = 0;
                        que[tail].r = iorj - 1;
                        if (isDbg) printf("8Add iorj: %d, d: %d, l: %d, r: %d\n", iorj, d, l, r);
                        tail = (tail + 1) % maxQueSize;
                        queSize++;
                        visitedI[mid] = 1;
                    }
                }
            }
        }
    }

    free(que);
    free(visitedI);
    free(visitedJ);
    return false;
}

bool searchMatrixLT240(int** matrix, int matrixSize, int* matrixColSize, int target) {
    int row = 0;
    int col = *matrixColSize - 1;

    while (row < matrixSize && col >= 0) {
        if (matrix[row][col] == target) {
            return true; // 找到目标值
        } else if (matrix[row][col] > target) {
            col--; // 当前值大于目标值，左移
        } else {
            row++; // 当前值小于目标值，下移
        }
    }
    return false; // 未找到目标值
}
