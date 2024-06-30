//
//  leetcode191.c
//  myleetcodetest
//
//  Created by jason on 2024-06-20.
//

#include "leetcode191.h"

int hammingWeight(int n) {
    int cnt = 0;
    while (n > 0) {
        if ((n & 0x1) != 0) {
            cnt ++;
        }

        n >>= 1;
    }
    return cnt;
}
