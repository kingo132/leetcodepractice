#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

int largestRectangleAreaOld(int* heights, int heightsSize) {
    if (heightsSize == 1) {
        return heights[0];
    }
    int* widthDP = (int*)malloc(heightsSize * sizeof(int));
    int* heightDP = (int*)malloc(heightsSize * sizeof(int));
    //memset(widthDP, 1, heightsSize * sizeof(int));
    //memset(heightDP, 0, heightsSize * sizeof(int));
    widthDP[heightsSize - 1] = 1;
    heightDP[heightsSize - 1] = heights[heightsSize - 1];
    for (int i = heightsSize - 2; i >= 0; i--) {
        if (heights[i] < heightDP[i + 1]) {
            heightDP[i] = heights[i];
            widthDP[i] = widthDP[i + 1] + 1;
        } else {
            if (heights[i] >= heightDP[i + 1] * (widthDP[i + 1] + 1)) {
                heightDP[i] = heights[i];
                widthDP[i] = 1;
            } else {
                heightDP[i] = heightDP[i + 1];
                widthDP[i] = widthDP[i + 1] + 1;
            }
        }
    }
    int max = 0;
    for (int i = 0; i < heightsSize; i++) {
        printf("(%d,%d) ", widthDP[i], heightDP[i]);
        if (widthDP[i] * heightDP[i] > max) {
            max = widthDP[i] * heightDP[i];
        }
    }
    printf("\n");
    free(widthDP);
    free(heightDP);
    return max;
}

int largestRectangleAreaBruteForce(int* heights, int heightsSize) {
    if (heightsSize == 1) {
        return heights[0];
    }
    int max = INT_MIN;
    for (int i = 0; i < heightsSize; i++) {
        int min = heights[i];
        for (int j = i; j < heightsSize; j++) {
            if (heights[j] < min) {
                min = heights[j];
            }
            if ((j - i + 1) * min > max) {
                //printf("i: %d, j: %d, min: %d, max: %d\n", i, j, min, max);
                max = (j - i + 1) * min;
            }
        }
    }
    return max;
}

int largestRectangleArea(int* heights, int heightsSize) {
    int* stack = (int*)malloc(heightsSize * sizeof(int));
    int top = 0;

    int max = INT_MIN;
    for (int i = 0; i < heightsSize; i++) {
        if (top == 0) {
            stack[top++] = i;
        } else {
            if (heights[i] >= heights[stack[top - 1]]) {
                stack[top++] = i;
            } else {
                while (top > 0 && heights[i] < heights[stack[top - 1]]) {
                    int h = heights[stack[--top]];
                    int l = top == 0 ? i : i - 1 - stack[top - 1];
                    if (l * h > max) {
                        max = l * h;
                    }
                    //printf("i: %d, h: %d, w: %d, max: %d\n", i, h, l, max);
                }
                stack[top++] = i;
            }
        }
        //printf("Stack: ");
        //for (int j = 0; j < top; j++) {
        //    printf("(%d:%d) ", stack[j], heights[stack[j]]);
        //}
        //printf("\n");
    }
    while (top > 0) {
        int h = heights[stack[--top]];
        int l = top == 0 ? heightsSize : heightsSize - 1 - stack[top - 1];
        if (l * h > max) {
            max = l * h;
        }
        //printf("i: %d, h: %d, w: %d, max: %d\n", heightsSize, h, l, max);
    }
    free(stack);
    return max;
}

// Function to find the maximum of two integers
int maxLT84(int a, int b) {
    return (a > b) ? a : b;
}

// Function to return the area of the largest rectangle in the histogram
int largestRectangleAreaChatGPT(int* heights, int heightsSize) {
    // Create an empty stack. The stack holds indexes of heights array.
    // The bars stored in stack are always in increasing order of their heights.
    int* stack = (int*)malloc(heightsSize * sizeof(int));
    int top = -1;  // Initialize top of stack
    int maxArea = 0;  // Initialize max area
    int index = 0;  // Initialize current index in heights array

    while (index < heightsSize) {
        // If this bar is higher than the bar at stack top, push it to stack
        if (top == -1 || heights[index] >= heights[stack[top]]) {
            stack[++top] = index++;
        } else {
            // Pop the top
            int height = heights[stack[top--]];
            // Calculate the area with heights[stack[top]] as the smallest (or minimum height) bar 'h'
            int width = (top == -1) ? index : index - stack[top] - 1;
            maxArea = maxLT84(maxArea, height * width);
            printf("index: %d, height: %d, width: %d, max: %d\n", index, height, width, maxArea);
        }
        printf("Stack: ");
        for (int j = 0; j <= top; j++) {
            printf("(%d:%d) ", stack[j], heights[stack[j]]);
        }
        printf("\n");
    }

    // Now, pop the remaining bars from stack and calculate area with every popped bar as the smallest bar
    while (top != -1) {
        int height = heights[stack[top--]];
        int width = (top == -1) ? index : index - stack[top] - 1;
        maxArea = maxLT84(maxArea, height * width);
        printf("index: %d, height: %d, width: %d, max: %d\n", index, height, width, maxArea);
    }

    // Free the allocated memory
    free(stack);

    return maxArea;
}
