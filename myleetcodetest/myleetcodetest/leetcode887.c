#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

int maxLT887(int a, int b) {
    return (a > b) ? a : b;
}

int minLT887(int a, int b) {
    return (a < b) ? a : b;
}

int superEggDrop(int k, int n) {
    // Create a table to store results of subproblems
    int dp[k + 1][n + 1];
    
    // Initialize base cases:
    // If we have 0 floors, 0 trials are needed
    // If we have 1 floor, 1 trial is needed
    for (int i = 1; i <= k; i++) {
        dp[i][0] = 0;
        dp[i][1] = 1;
    }

    // If we have 1 egg, we need j trials for j floors
    for (int j = 1; j <= n; j++) {
        dp[1][j] = j;
    }

    // Fill the rest of the entries in the table using binary search for optimal substructure property
    for (int i = 2; i <= k; i++) {
        for (int j = 2; j <= n; j++) {
            dp[i][j] = INT_MAX;
            int low = 1, high = j, mid;
            while (low <= high) {
                mid = (low + high) / 2;
                int break_case = dp[i - 1][mid - 1];
                int not_break_case = dp[i][j - mid];
                // 下面取的是最差情况
                int res = 1 + maxLT887(break_case, not_break_case);

                // 注意，这里加一减一是二分法暂停的关键
                if (break_case > not_break_case) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }

                // 找到最优的次数
                dp[i][j] = minLT887(dp[i][j], res);
            }
        }
    }

    // dp[k][n] holds the result
    return dp[k][n];
}