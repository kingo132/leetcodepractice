#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>

int compareVersion(char* version1, char* version2) {
    char* p1 = version1, *p2 = version2;
    while (1) {
        int n1 = 0;
        while (*p1 && *p1 != '.') {
            if (*p1 >= '0' && *p1 <= '9') {
                //printf("%d\n", *p1 - '0');
                n1 = n1 * 10 + (*p1 - '0');
            }
            p1++;
        }
        if (*p1 == '.') {
            p1++;
        }
        int n2 = 0;
        while (*p2 && *p2 != '.') {
            if (*p2 >= '0' && *p2 <= '9') {
                //printf("%d\n", *p1 - '0');
                n2 = n2 * 10 + (*p2 - '0');
            }
            p2++;
        }
        if (*p2 == '.') {
            p2++;
        }
        if (n1 > n2) {
            return 1;
        } else if (n1 < n2) {
            return -1;
        }
        //printf("Check: %c <-> %c\n", *p1, *p2);
        if (*p1 == '\0' && *p2 == '\0') {
            break;
        }
    }
    return 0;
}