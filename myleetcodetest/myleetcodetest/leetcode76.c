#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

long getVal(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a';
    } else if (c >= 'A' && c <= 'Z') {
        return 26 + c - 'A';
    }
    return 0;
}

int isMissing(int* arys, int* aryt) {
    for (int i = 0; i < 52; i++) {
        if (arys[i] < aryt[i]) {
            return 1;
        }
    }
    return 0;
}

char* minWindow(char* s, char* t) {
    int arys[52], aryt[52];
    for (int i = 0; i < 52; i++) {
        arys[i] = aryt[i] = 0;
    }

    char* p = t;
    while (*p) {
        aryt[getVal(*p)]++;
        p++;
    }

    char* pl = s, * pr = s;
    int min = INT_MAX;
    char* minl = NULL, * minr = NULL;
    while (*pl) {
        if (isMissing(arys, aryt) > 0) {
            if (*pr == '\0') {
                break;
            }
            arys[getVal(*pr)]++;
            pr++;
        } else { // v <= 0
            //printf("Found %c <-> %c, len: %d\n", *pl, *pr, pr - pl);
            if (pr - pl < min) {
                min = pr - pl;
                minl = pl;
                minr = pr;
            }
            arys[getVal(*pl)]--;
            pl++;
        }
    }

    if (min == INT_MAX) {
        return "";
    }

    char* ret = (char*)malloc((min + 1) * sizeof(char));
    pl = ret;
    while (minl < minr) {
        *pl = *minl;
        minl++;
        pl++;
    }
    *pl = '\0';

    return ret;
}