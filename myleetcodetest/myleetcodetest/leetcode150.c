//
//  leetcode150.c
//  myleetcodetest
//
//  Created by jason on 2024-06-20.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include "leetcode150.h"

int getPrecedence(char c) {
    if (c == '+' || c == '-') {
        return 1;
    } else if (c == '*' || c == '/') {
        return 2;
    }
    return -1;
}

void dumpStackLT150(int* stack, int n) {
    printf("Dump: ");
    for (int i = 0; i < n; i ++) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

int evalRPN(char** tokens, int tokensSize) {
    char* stack1 = (char*)malloc(tokensSize * sizeof(char));
    int* stack2 = (int*)malloc(tokensSize * sizeof(int));
    int top1 = 0, top2 = 0;

    for (int i = 0; i < tokensSize; i++) {
        //dumpStackLT150(stack2, top2);
        if (tokens[i][0] == '+' || (tokens[i][0] == '-' && tokens[i][1] == '\0') || tokens[i][0] == '*' || tokens[i][0] == '/') {
            if (top2 < 2) {
                printf("Not enough operand, top2: %d, op: %c\n", top2, tokens[i][0]);
                return -1;
            }
            int oprand2 = stack2[--top2];
            int oprand1 = stack2[--top2];
            if (tokens[i][0] == '+') {
                stack2[top2++] = oprand1 + oprand2;
            } else if (tokens[i][0] == '-') {
                stack2[top2++] = oprand1 - oprand2;
            } else if (tokens[i][0] == '*') {
                stack2[top2++] = oprand1 * oprand2;
            } else if (tokens[i][0] == '/') {
                stack2[top2++] = oprand1 / oprand2;
            } else {
                printf("Unknown op: %c\n", tokens[i][0]);
            }
        } else {
            stack2[top2++] = atoi(tokens[i]);
        }
    }

    return stack2[0];
}
