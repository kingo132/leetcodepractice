#include <stdio.h>
#include "minmaxsum.h"
#include "constructbintree.h"
#include "wordsearch.h"
#include "candy.h"
#include "sumsubary.h"
#include "leetcode743.h"

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
    leetcode743Main();
    
    return 0;
}
