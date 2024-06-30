//
//  leetcode12.c
//  myleetcodetest
//
//  Created by jason on 2024-06-12.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "leetcode12.h"

char* intToRoman(int num) {
    int symBase[4] = {'I', 'X', 'C', 'M'};
    int fiveBase[3] = {'V', 'L', 'D'};
    int idx = 3;
    int modBase = 1000;
    int numCopy = num;
    char* result = (char*)malloc(32 * sizeof(char));
    int rstIdx = 0;
    while (modBase > 0) {
        int digit = numCopy / modBase;
        if (digit >= 1 && digit <= 3) {
            printf("(%d x %c) ", digit, symBase[idx]);
            for (int i = 0; i < digit; i++) {
                result[rstIdx++] = symBase[idx];
            }
        } else if (digit >= 6 && digit <= 8) {
            printf("(%c %d x %c) ", fiveBase[idx], digit - 5, symBase[idx]);
            result[rstIdx++] = fiveBase[idx];
            for (int i = 0; i < digit - 5; i++) {
                result[rstIdx++] = symBase[idx];
            }
        } else if (digit == 4) {
            printf("(%c%c) ", symBase[idx], fiveBase[idx]);
            result[rstIdx++] = symBase[idx];
            result[rstIdx++] = fiveBase[idx];
        } else if (digit == 9) {
            printf("(%c%c) ", symBase[idx], symBase[idx + 1]);
            result[rstIdx++] = symBase[idx];
            result[rstIdx++] = symBase[idx + 1];
        } else if (digit == 5) {
            printf("(%c) ", fiveBase[idx]);
            result[rstIdx++] = fiveBase[idx];
        } else {
            // digit == 0
        }

        numCopy %= modBase;
        modBase /= 10;
        idx --;
    }

    result[rstIdx] = '\0';
    printf("\nGet result: %s\n", result);
    return result;
}
