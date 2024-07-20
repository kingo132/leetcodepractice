#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>

bool isLoopOld(char* s, int len) {
    //printf("s: %s, len: %d\n", s, len);
    //return true;
    char* p1 = s, * p2 = s + len / 3, * p3 = s + len * 2 / 3;
    for (int i = 0; i < len / 3; i++) {
        if (*p1 != *p2) {
            return false;
        }
        if (*p2 != *p3) {
            return false;
        }
    }
    for (int i = 0; i < len / 3; i++) {
        s[i + 1] = s[i + len / 3];
    }
    s[0] = '(';
    s[len / 3 + 1] = ')';
    s[len / 3 + 2] = '\0';
    return true;
}

bool isLoopSub(char* s, int sLen, int subLen, char** loopStart) {
    char* p1 = s + sLen - 2, * p2 = s + sLen - 2 - subLen, * p3 = s + sLen - 2 - 2 * subLen;
    *(p1 + 1) = '\0';
    if (sLen > 145) printf("%d: %s, subLen: %d\n", sLen, s, subLen);
    for (int i = 0; i < subLen; i++) {
        if (sLen > 145) printf("Check: %c - %c - %c\n", *p1, *p2, *p3);
        if (*p1 != *p2) {
            return false;
        }
        if (*p2 != *p3) {
            return false;
        }
        p1--;
        p2--;
        p3--;
    }
    *loopStart = p3 + 1;
    if (sLen > 145) printf("LoopStart: %c\n", **loopStart);
    return true;
}

bool isLoop(char* s, int sLen) {
    int maxSubLen = sLen / 3;
    for (int i = maxSubLen; i > 0; i--) {
        char* loopStart = s;
        if (isLoopSub(s, sLen, i, &loopStart)) {
            for (int j = 0; j < i; j++) {
                *(loopStart + j + 1) = *(loopStart + i + j);
            }
            *loopStart = '(';
            *(loopStart + i + 1) = ')';
            *(loopStart + i + 2) = '\0';
            return true;
        }
    }
    return false;
}

typedef struct {
    int key;
    int val;
    int isOccupied;
} HashNode;

void setHash(int key, int val, HashNode* hashAry, int maxHashLen) {
    int k = key % maxHashLen;
    for (int i = 0; i < maxHashLen; i++) {
        if (hashAry[i].isOccupied == 0) {
            hashAry[i].key = key;
            hashAry[i].val = val;
            hashAry[i].isOccupied = 1;
            return;
        }
        k = (k + 1) % maxHashLen;
    }
}

int getHash(int key, HashNode* hashAry, int maxHashLen) {
    int k = key % maxHashLen;
    for (int i = 0; i < maxHashLen; i++) {
        if (hashAry[i].isOccupied == 0) {
           return -1;
        }
        if (hashAry[i].key == key) {
            return hashAry[i].val;
        }
        k = (k + 1) % maxHashLen;
    }
    return -1;
}

char* fractionToDecimal(int oldNumerator, int denominator) {
    char* retStr = (char*)malloc(10000 * sizeof(char));
    memset(retStr, 0, 10000 * sizeof(char));
    int idx = 0;

    int maxHashLen = 1000;
    HashNode* remHash = (HashNode*)malloc(maxHashLen * sizeof(HashNode));
    memset(remHash, 0, maxHashLen * sizeof(HashNode));

    long newNumerator = oldNumerator;
    if (newNumerator == 0) {
        retStr[idx++] = '0';
    } else {
        if (newNumerator < 0) {
            if (denominator < 0) {
                //numerator = - numerator;
                //denominator = - denominator;
            } else {
                retStr[idx++] = '-';
                newNumerator = - newNumerator;
            }
        } else if (denominator < 0) {
            retStr[idx++] = '-';
            denominator = - denominator;
        }

        if (newNumerator > 0 && denominator > 0) {
            long t = denominator;
            while (newNumerator > t) {
                t *= 10;
            }
            while (t != denominator) {
                t /= 10;
                retStr[idx++] = '0' + (newNumerator / t);
                newNumerator = newNumerator % t;
            }
        } else if (newNumerator < 0 && denominator < 0) {
            long t = denominator;
            while (newNumerator < t) {
                t *= 10;
            }
            while (t != denominator) {
                t /= 10;
                retStr[idx++] = '0' + (newNumerator / t);
                newNumerator = newNumerator % t;
            }
        }

        if (idx == 0) {
            retStr[idx++] = '0';
        }

        if (newNumerator != 0) {
            retStr[idx++] = '.';
            int startIdx = idx;

            int index = 0;
            long remainder = newNumerator % denominator;
            printf("remainder1: %d\n", remainder);
            while (remainder != 0 && getHash(remainder, remHash, maxHashLen) == -1) {
                printf("remainder: %d\n", remainder);
                //rems[remainder] = index++;
                setHash(remainder, index++, remHash, maxHashLen);
                remainder *= 10;
                retStr[idx++] = '0' + remainder / denominator;
                remainder %= denominator;
            }

            if (remainder != 0) {
                printf("remainder2: %d\n", remainder);

                int sTmp = getHash(remainder, remHash, maxHashLen);
                for (int i = index - 1; i >= sTmp; i--) {
                    printf("%c ", retStr[startIdx + i]);
                    retStr[startIdx + i + 1] = retStr[startIdx + i];
                }
                printf("\n");

                retStr[startIdx + sTmp] = '(';
                idx++;
                retStr[idx++] = ')';
            }
            /*if (remainder != 0) {
                char* p = &retStr[idx];
                while (*(p - 1) != '.') {
                    *p = *(p - 1);
                    p--;
                }
                *p = '(';
                idx++;
                retStr[idx++] = ')';
            }*/
            /*
            int firstIdx = idx;

            numerator *= 10;
            while (numerator < denominator) {
                retStr[idx++] = '0';
                numerator *= 10;
            }

            while (numerator != 0) {
                if (idx - firstIdx + 1 >= 10 && isLoop(retStr + firstIdx, idx - firstIdx + 1)) {
                    break;
                }
                retStr[idx++] = '0' + (numerator / denominator);
                numerator = (numerator % denominator) * 10;
            }
            */
        }
    }

    retStr[idx] = '\0';

    return retStr;
}