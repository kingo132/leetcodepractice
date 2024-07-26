#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>

int reverseLT7(int x){
    if (x == INT_MIN) {
        return 0;
    }

    int sign = 1;
    if (x < 0) {
        x = -x;
        sign = -1;
    }

    char intAry[10];
    int intAryIdx = 0;
    for (int i = 0; i < 10; i++) {
        intAry[i] = 0;
    }

    int t = x;
    while (t > 0) {
        intAry[intAryIdx++] = t % 10;
        t /= 10;
    }

    // ret * 10 + ia > INT_MAX
    int ret = 0;
    for (int i = 0; i < intAryIdx; i++) {
        if (sign > 0) {
            if (ret > (INT_MAX - intAry[i]) / 10.0) {
                return 0;
            }
        } else {
            if (ret > (-(INT_MIN + 1) - intAry[i]) / 10.0) {
                return 0;
            }
        }
        ret *= 10;
        ret += intAry[i];
    }

    return sign * ret;
}
