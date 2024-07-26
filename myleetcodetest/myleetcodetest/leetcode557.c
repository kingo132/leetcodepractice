#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>

void reverseHelper(char* s, char* e) {
    while (*s && *e && s < e) {
        char t = *s;
        *s = *e;
        *e = t;

        s++;
        e--;
    }
}

char* reverseWordsLT557(char* s) {
    char* ps = s, *pe = s;
    while(*pe) {
        if (*pe == ' ') {
            reverseHelper(ps, pe - 1);
            ps = pe + 1;
        }
        pe++;
    }
    reverseHelper(ps, pe - 1);
    return s;
}
