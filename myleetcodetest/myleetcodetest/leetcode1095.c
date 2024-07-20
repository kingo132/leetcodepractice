#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

/**
 * *********************************************************************
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * *********************************************************************
 *
 * int get(MountainArray *, int index);
 * int length(MountainArray *);

int mountainTopIdx(MountainArray* arr, int len, int l, int r) {
    if (l > r) {
        return -1;
    }

    int mid = (l + r) / 2;
    int midv = get(arr, mid);
    if (mid > 0 && get(arr, mid - 1) > midv) {
        // should be on the left of mid
        return mountainTopIdx(arr, len, l, mid - 1);
    } else {
        // should be on the right of mid
        if (mid < len - 1 && get(arr, mid + 1) > midv) {
            return mountainTopIdx(arr, len, mid + 1, r);
        } else {
            return mid;
        }
    }

    return -1;
}

int binSearch(MountainArray* arr, int len, int l, int lv, int r, int rv, int target, bool isasc) {
    if (l > r) {
        return -1;
    }

    int mid = (l + r) / 2;
    int midv = get(arr, mid);
    if (target == midv) {
        return mid;
    }
    
    if (target > midv) {
        if (isasc) {
            return binSearch(arr, len, mid + 1, mid + 1 < len ? get(arr, mid + 1) : -1, r, rv, target, isasc);
        } else {
            return binSearch(arr, len, l, lv, mid - 1, mid - 1 >= 0 ? get(arr, mid - 1) : -1, target, isasc);
        }
    } else {
        if (isasc) {
            return binSearch(arr, len, l, lv, mid - 1, mid - 1 >= 0 ? get(arr, mid - 1) : -1, target, isasc);
        } else {
            return binSearch(arr, len, mid + 1, mid + 1 < len ? get(arr, mid + 1) : -1, r, rv, target, isasc);
        }
    }

    return -1;
}

int findInMountainArray(int target, MountainArray* mountainArr) {
	int len = length(mountainArr);
    int topIdx = mountainTopIdx(mountainArr, len, 0, len - 1);
    printf("topIdx: %d\n", topIdx);
    int idx = binSearch(mountainArr, len, 0, get(mountainArr, 0), topIdx, get(mountainArr, topIdx), target, true);
    if (idx != -1) {
        return idx;
    }
    idx = binSearch(mountainArr, len, topIdx, get(mountainArr, topIdx), len - 1, get(mountainArr, len - 1), target, false);
    if (idx != -1) {
        return idx;
    }
    return -1;
}
*/