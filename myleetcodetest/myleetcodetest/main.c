#include <stdio.h>
#include "minmaxsum.h"
#include "constructbintree.h"
#include "wordsearch.h"
#include "candy.h"
#include "sumsubary.h"
#include "leetcode743.h"
#include "leetcode4.h"
#include "leetcode46.h"
#include "leetcode912.h"
#include "leetcode1497.h"
#include "leetcode44.h"
#include "leetcode3.h"
#include "leetcode415.h"
#include "leetcode440.h"
#include "leetcode6.h"

void printBinary(int num) {
    int i;
    // Assuming we're dealing with a standard 32-bit integer
    for (i = 31; i >= 0; i--) {
        int k = num >> i;
        if (k & 1)
            printf("1");
        else
            printf("0");
    }
    printf("\n");
}

void testComplementRepresentation(void) {
    int a = (1 << 31);
    int b = ~(1 << 31);
    printf("%d %d\n", a, b);
    printBinary(a);
    printBinary(b);
}

int main(int argc, char** argv) {
    //testComplementRepresentation();
    //minmaxsum_main();
    //buildTreeMain();
    //wordsearchMain();
    //candyMain();
    //sumsubary_main();
    //leetcode743Main();
    //leetcode4Main();
    //leetcode912Main();
    //leetcode1497Main();
    //leetcode3Main();
    //leetcode415Main();
    //leetcode440Main();
    
    //int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes);
    //int nums[3] = {1, 2, 3};
    //int returnSize = 0;
    //int* returnColumnSizes;
    //permute(nums, 3, &returnSize, &returnColumnSizes);
    
    leetcode6Main();
    
    return 0;
}
