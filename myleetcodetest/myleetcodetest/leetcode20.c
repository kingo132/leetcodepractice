#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

bool isValid(char* s) {
    char* stack = (char*)malloc(10000 * sizeof(char));
    int top = 0;

    stack[top++] = *(s++);
    while (*s != '\0') {
        if (*s == '(') {
            stack[top++] = *(s++);
        } else if (*s == '[') {
            stack[top++] = *(s++);
        } else if (*s == '{') {
            stack[top++] = *(s++);
        } else if (*s == ')') {
            if (top <= 0 || stack[top - 1] != '(') {
                //printf("%c expect %c but got %c\n", *s, '(', stack[top - 1]);
                free(stack);
                return false;
            }
            top--;
            s++;
        } else if (*s == ']') {
            if (top <= 0 || stack[top - 1] != '[') {
                //printf("%c expect %c but got %c\n", *s, '[', stack[top - 1]);
                free(stack);
                return false;
            }
            top--;
            s++;
        } else if (*s == '}') {
            if (top <= 0 || stack[top - 1] != '{') {
                //printf("%c expect %c but got %c\n", *s, '{', stack[top - 1]);
                free(stack);
                return false;
            }
            top--;
            s++;
        } 
    }

    //printf("Final, top: %d, s: %c\n", top, *s);
    free(stack);
    if (*s == '\0' && top == 0) {
        return true;
    }
    return false;
}