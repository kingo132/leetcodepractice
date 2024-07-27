#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MYDBG false

int writeNum(char* p, int cnt) {
    int base = 10, ret = 0;
    while (base <= cnt) {
        base *= 10;
    }
    while (base > 1) {
        if (MYDBG) printf("cnt: %d, base: %d, p: %c\n", cnt, base, '0' + (cnt * 10) / base);
        *p = '0' + (cnt * 10) / base;
        p++;
        ret++;
        cnt = ((cnt * 10) % base) / 10;
        base /= 10;
    }
    return ret;
}

int compress(char* chars, int charsSize) {
    if (charsSize == 1) return 1;

    int len = 0, cnt = 1;
    int w = 1, s = 0, f = 1;
    while (s < charsSize && f < charsSize) {
        if (MYDBG) printf("str: %s, w: %d,%c, s: %d,%c, f: %d,%c, cnt: %d, len: %d\n", chars, w, *(chars + w), s, *(chars + s), f, *(chars + f), cnt, len);
        if (s == f) {
            if (w != f) {
                *(chars + w) = *(chars + f);
            }
            f++;
            w++;
            len++;
        } else {
            if (*(chars + s) == *(chars + f)) {
                cnt++;
                f++;
            } else {
                if (cnt > 1) {
                    int wc = writeNum(chars + w, cnt);
                    w += wc;
                    s = f;
                    len += wc;
                    cnt = 1;
                } else {
                    *(chars + w) = *(chars + f);
                    w++;
                    s++;
                    f++;
                    len++;
                }
            }
        }
        if (MYDBG) printf("str: %s, w: %d, s: %d, f: %d, cnt: %d, len: %d\n", chars, w, s, f, cnt, len);
    }
    if (cnt > 1) {
        len += writeNum(chars + w, cnt);
    }
    //chars[len] = '\0';
    return len + 1;
}