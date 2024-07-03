//
//  leetcode509.c
//  myleetcodetest
//
//  Created by jason on 2024-07-02.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode509.h"



int fib(int n){
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    
    int n1 = 0, n2 = 1, ret = 0;
    for (int i = 2; i <= n; i++) {
        ret = n1 + n2;
        n1 = n2;
        n2 = ret;
    }
    return ret;
}
