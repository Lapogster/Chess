#include "myMath.h"

int absDiff(int n1, int n2);

differences_t coordsAbs(coords_t c1, coords_t c2){
    differences_t returnVal;

    int x1 = c1.x;
    int x2 = c2.x;
    int y1 = c1.y;
    int y2 = c2.y;

    returnVal.xDiff = absDiff(x1, x2);
    returnVal.yDiff = absDiff(y1, y2);

    return returnVal;
}

int absDiff(int n1, int n2){
    if (n1 > n2) return (n1 - n2);
    return (n2 - n1);
}