#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

double myPow(double x, int n) {
    if (x == 1) {
        return x;
    }

    if (x == -1) {
        if (n % 2 == 0) {
            return 1.0;
        } else {
            return -1.0;
        }
    }

    long nn = n;
    if (nn < 0) {
        nn = -nn;
    }

    double ret = 1;
    for (long i = 0; i < nn; i++) {
        if (n < 0) {
            ret *= 1.0 / x;
            if (ret > -1e-10 && ret < 1e-10) {
                return 0.0;
            }
        } else {
            ret *= x;
        }
    }
    return ret;
}