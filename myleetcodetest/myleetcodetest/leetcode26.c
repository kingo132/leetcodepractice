//
//  leetcode26.c
//  myleetcodetest
//
//  Created by jason on 2024-06-22.
//

#include "leetcode26.h"

int removeDuplicates(int* nums, int numsSize) {
    int slow = 0, fast = 0;
    while (fast < numsSize) {
        if (fast < numsSize - 1 && nums[fast] == nums[fast + 1]) {
            fast ++;
        } else {
            int t = nums[slow];
            nums[slow] = nums[fast];
            nums[fast] = t;
            slow ++;
            fast ++;
        }
    }
    return slow;
}
