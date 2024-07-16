#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize) {
    // 关键在于用surplus和deficit记录当前累积的正负值
    int sum = 0, startIdx = 0, surplus = 0, deficit = 0;
    for (int i = 0; i < gasSize; i++) {
        int v = gas[i] - cost[i];
        surplus += v;
        if (surplus < 0) {
            startIdx = i + 1;
            deficit = surplus;
            surplus = 0;
        }
        sum += v;
    }
    if (sum < 0) {
        return -1;
    }
    if (surplus + deficit >= 0) {
        return startIdx;
    }
    
    /*
    for (; startIdx < gasSize; startIdx++) {
        //printf("Start from: %d\n", startIdx);
        int curGas = 0, cst = 0, i = 0;
        for (; i < gasSize + 1; i++) {
            int idx = (startIdx + i) % gasSize;
            //printf("%d: %d - %d + %d = %d\n", idx, curGas, cst, gas[idx], curGas + gas[idx] - cst);
            if (curGas - cst < 0) {
                //printf("Failed: %d\n", curGas);
                break;
            }
            curGas = curGas - cst + gas[idx];
            cst = cost[idx];
        }
        if (i == gasSize + 1) {
            return startIdx;
        }
    }*/
    return -1;
}