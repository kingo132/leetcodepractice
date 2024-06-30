//
//  leetcode44.c
//  myleetcodetest
//
//  Created by jason on 2024-06-21.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

#include "leetcode44.h"

typedef struct {
    char* s;
    char* p;
} STACKNODE;

#define PUSH_STACK(st, t, ss, pp) {/*printf("Push %c,%c\n", *(ss), *(pp));*/ st[t].s = (ss); st[t].p = (pp); t++;}
#define POP_STACK(st, t, ss, pp) {t--; (ss) = st[t].s; (pp) = st[t].p; /*printf("Pop %c,%c\n", *(ss), *(pp));*/}

bool isMatchHelper(char* s, char* p, unsigned char* memo, int mn, char* sStart, char* pStart) {
    STACKNODE* stack = malloc(10000 * sizeof(STACKNODE));
    int top = 0;

    PUSH_STACK(stack, top, s, p)

//label_retry:
    while (top > 0) {
        POP_STACK(stack, top, s, p)

        if (memo[(s - sStart) * mn + (p - pStart)] != 0) {
            return memo[(s - sStart) * mn + (p - pStart)] == 1 ? true : false;
        }

        while (*s && *p) {
            if (*p == '?') {
                s ++;
                p ++;
            } else if (*p == '*') {
                if (*(p + 1) == '\0') {
                    return true;
                } else if (*(p + 1) == '*') {
                    p ++;
                } else if (*(p + 1) == '?') {
                    while (*s) {
                        PUSH_STACK(stack, top, s, p + 1)
                        s ++;
                    }
                    break;
                } else {
                    while (*s) {
                        if (*s == *(p + 1)) {
                            PUSH_STACK(stack, top, s, p + 1)
                        }
                        s ++;
                    }
                    break;
                }
            } else {
                if (*s != *p) {
                    memo[(s - sStart) * mn + (p - pStart)] = 2;
                    break;
                }
                s ++;
                p ++;
            }
        }
        while (*p && *p == '*') {
            p ++;
        }
        if (*s == '\0' && *p == '\0') {
            return true;
        }
    }
    
    return false;
}

bool isMatchHelperRecursiveMy(char* s, char* p, unsigned char* memo, int mn, char* sStart, char* pStart) {
    // 注意！这个memoIdx必须提前计算，后面实时计算的会超时
    int memoIdx = (s - sStart) * mn + (p - pStart);
    if (memo[memoIdx] != 0) {
        return memo[memoIdx] == 1 ? true : false;
    }
    while (*s && *p) {
        if (*p == '?') {
            s ++;
            p ++;
        } else if (*p == '*') {
            if (*(p + 1) == '\0') {
                memo[memoIdx] = 1;
                return true;
            } else if (*(p + 1) == '*') {
                p ++;
            } else if (*(p + 1) == '?') {
                while (*s) {
                    if (isMatchHelperRecursiveMy(s, p + 1, memo, mn, sStart, pStart)) {
                        memo[memoIdx] = 1;
                        return true;
                    }
                    s ++;
                }
                memo[(s - sStart) * mn + (p - pStart)] = 2;
                return false;
            } else {
                while (*s) {
                    if (*s == *(p + 1)) {
                        if (isMatchHelperRecursiveMy(s, p + 1, memo, mn, sStart, pStart)) {
                            memo[memoIdx] = 1;
                            return true;
                        }
                    }
                    s ++;
                }
                memo[memoIdx] = 2;
                return false;
            }
        } else {
            if (*s != *p) {
                memo[memoIdx] = 2;
                return false;
            }
            s ++;
            p ++;
        }
    }
    while (*p && *p == '*') {
        p ++;
    }
    if (*s != '\0' || *p != '\0') {
        memo[memoIdx] = 2;
        return false;
    }
    memo[memoIdx] = 1;
    return true;
}

bool isMatchMy(char* s, char* p) {
    int sLen = 0, pLen = 0;
    char* t = s;
    while (*t) {
        sLen ++;
        t ++;
    }
    t = p;
    while (*t) {
        pLen ++;
        t ++;
    }
    unsigned char* memo = (unsigned char*)malloc((sLen + 1) * (pLen + 1) * sizeof(unsigned char));
    for (int i = 0; i < (sLen + 1) * (pLen + 1); i++) {
        memo[i] = 0;
    }
    return isMatchHelperRecursiveMy(s, p, memo, pLen + 1, s, p);
}

bool isMatchHelperRecursive(char* s, char* p, unsigned char* memo, int mn, char* sStart, char* pStart) {
    int sOffset = s - sStart;
    int pOffset = p - pStart;
    int memoIndex = sOffset * mn + pOffset;
    
    if (memo[memoIndex] != 0) {
        return memo[memoIndex] == 1;
    }
    
    while (*s && *p) {
        if (*p == '?') {
            s++;
            p++;
        } else if (*p == '*') {
            if (*(p + 1) == '\0') {
                memo[memoIndex] = 1;
                return true;
            } else if (*(p + 1) == '*') {
                p++;
            } else {
                while (*s) {
                    if (isMatchHelperRecursive(s, p + 1, memo, mn, sStart, pStart)) {
                        memo[memoIndex] = 1;
                        return true;
                    }
                    s++;
                }
                memo[memoIndex] = 2;
                return false;
            }
        } else {
            if (*s != *p) {
                memo[memoIndex] = 2;
                return false;
            }
            s++;
            p++;
        }
    }
    
    while (*p == '*') {
        p++;
    }
    
    bool result = (*s == '\0' && *p == '\0');
    memo[memoIndex] = result ? 1 : 2;
    return result;
}

bool isMatch(char* s, char* p) {
    int sLen = strlen(s);
    int pLen = strlen(p);
    
    unsigned char* memo = (unsigned char*)malloc((sLen + 1) * (pLen + 1) * sizeof(unsigned char));
    memset(memo, 0, (sLen + 1) * (pLen + 1) * sizeof(unsigned char));
    
    bool result = isMatchHelperRecursiveMy(s, p, memo, pLen + 1, s, p);
    free(memo);
    return result;
}

void leetcode44Main(void) {
    printf("%s\n", isMatch("adceb", "*a*b") ? "true" : "false");
}
