//
//  leetcode440.c
//  myleetcodetest
//
//  Created by jason on 2024-06-26.
//

#include "leetcode440.h"

#include <stdio.h>

// 递归函数，生成以当前前缀为开头的所有数字
void generateNumbers(int prefix, int limit) {
    // 如果前缀超过了上限，就直接返回
    if (prefix > limit) {
        return;
    }

    // 打印当前前缀
    printf("%d\n", prefix);

    // 在当前前缀后面添加一个数字，并递归生成
    for (int i = 0; i <= 9; i++) {
        int next = prefix * 10 + i;
        if (next > limit) {
            break;
        }
        generateNumbers(next, limit);
    }
}

int leetcode440MainOld(void) {
    int limit = 1000;

    // 从1到9作为初始前缀，生成所有数字
    for (int i = 1; i <= 9; i++) {
        generateNumbers(i, limit);
    }

    return 0;
}

int generateLexi(unsigned long long v, int* gk, unsigned long long lim) {
    if (v > lim) {
        return -1;
    }

    (*gk)--;
    if (*gk <= 0) {
        return v;
    }
    //printf("v: %d, gk: %d\n", v, *gk);

    for (int i = 0; i < 10; i++) {
        unsigned long long next = v * 10 + i;
        if (next > lim) {
            break;
        }
        int ret = generateLexi(next, gk, lim);
        if (ret > 0) {
            return ret;
        }
    }

    return -1;
}

int findKthNumberMy(int n, int k) {
    int gk = k;
    for (int i = 1; i < 10; i++) {
        int ret = generateLexi(i, &gk, n);
        if (ret > 0) {
            return ret;
        }
    }
    return -1;
}

int findKthNumberChatGPT(int n, int k) {
    long curr = 1; // Start from the smallest number
    k--; // We are looking for the (k-1)th number in 0-indexed form

    while (k > 0) {
        long steps = 0;
        long first = curr;
        long last = curr + 1;
        // Count steps in the prefix range [curr, curr+1)
        while (first <= n) {
            steps += (last <= n ? last : n + 1) - first;
            first *= 10;
            last *= 10;
        }
        if (steps <= k) {
            // If steps are less than or equal to k, we can skip this entire prefix
            curr++;
            k -= steps;
        } else {
            // Otherwise, go deeper in the current prefix
            curr *= 10;
            k--;
        }
    }
    return curr;
}

long getCount(long prefix, long n) {
    long count = 0;
    long current = prefix;
    long next = prefix + 1;
    while (current <= n) {
        count += (next <= n + 1) ? (next - current) : (n + 1 - current);
        current *= 10; // 前往子树
        next *= 10; // 右边子树的最左节点
    }
    return count;
}

int findKthNumber(int n, int k) {
    long curr = 1;
    k--; // Convert k to zero-based index

    while (k > 0) {
        long count = getCount(curr, n);
        if (count <= k) { // 跳过子树
            k -= count;
            curr++; // 前往右节点只需加1
        } else { // 进入子树
            curr *= 10;
            k--; // 前往子树最左节点，要乘以10
        }
    }
    return (int)curr;
}

int leetcode440Main(void) {
    //int n = 13;
    //int k = 2;
    //printf("The %d-th lexicographically smallest number in range [1, %d] is %d\n", k, n, findKthNumber(n, k));

    int n = 783368691;
    int k = 319151369;
    printf("The %d-th lexicographically smallest number in range [1, %d] is %d\n", k, n, findKthNumber(n, k));
    printf("The %d-th lexicographically smallest number in range [1, %d] is %d\n", k, n, findKthNumberChatGPT(n, k));
    //printf("%d\n", getNodesCntOfASubTree(10, 189));

    return 0;
}
