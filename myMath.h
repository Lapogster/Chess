#ifndef MYMATH_H
#define MYMATH_H

#include "pieces.h"

typedef struct{
    int xDiff;
    int yDiff;
} differences_t;

differences_t coordsAbs(coords_t c1, coords_t c2);

#endif