#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

int numTimesAllBlue(int* flips, int flipsSize) {
    unsigned long long sum = 0, cnt = 0;
    for (int i = 0; i < flipsSize; i++) {
        sum += flips[i];
        unsigned long long f = (unsigned long long)(i + 2) * (i + 1) / 2;
        if (sum == f) {
            cnt++;
        }
    }
    return cnt;
}