//
//  sumsubary.c
//  test
//
//  Created by jason on 2024-05-21.
//

#include "sumsubary.h"

#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

void printAry(const char* prefix, int* arr, int arrSize) {
    printf("%s", prefix);
    for (int i = 0; i < arrSize; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void printStack(const char* prefix, int* stack, int top) {
    printf("%s", prefix);
    for (int i = 0; i <= top; i++) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

int sumSubarrayMins(int* arr, int arrSize) {
    int* ple = (int*)malloc(arrSize * sizeof(int)); // Previous less element
    int* nle = (int*)malloc(arrSize * sizeof(int)); // Next less element
    int* stack = (int*)malloc(arrSize * sizeof(int)); // Stack to hold indices
    int top = -1; // Stack top pointer
    
    // Initialize Previous Less Element array
    for (int i = 0; i < arrSize; i++) {
        while (top >= 0 && arr[stack[top]] >= arr[i]) {
            top--;
        }
        ple[i] = (top == -1) ? -1 : stack[top];
        stack[++top] = i;
        printAry("ple: ", ple, arrSize);
        printStack("stack: ", stack, top);
    }
    
    // Reset stack for Next Less Element computation
    top = -1;
    
    // Initialize Next Less Element array
    for (int i = arrSize - 1; i >= 0; i--) {
        while (top >= 0 && arr[stack[top]] > arr[i]) {
            top--;
        }
        nle[i] = (top == -1) ? arrSize : stack[top];
        stack[++top] = i;
        printAry("nle: ", nle, arrSize);
        printStack("stack: ", stack, top);
    }
    
    // Calculate the sum of subarray minimums
    long long result = 0;
    for (int i = 0; i < arrSize; i++) {
        int leftCount = i - ple[i];
        int rightCount = nle[i] - i;
        result = (result + (long long)arr[i] * leftCount * rightCount) % MOD;
    }
    
    // Free allocated memory
    free(ple);
    free(nle);
    free(stack);
    
    return (int)result;
}

int sumsubary_main() {
    int arr1[] = {3, 1, 2, 4};
    int arrSize1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("Sum of subarray minimums: %d\n", sumSubarrayMins(arr1, arrSize1)); // Output: 17

    int arr2[] = {11, 81, 94, 43, 3};
    int arrSize2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("Sum of subarray minimums: %d\n", sumSubarrayMins(arr2, arrSize2)); // Output: 444

    return 0;
}
