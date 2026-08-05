#include <stdio.h>
#include "pieces.h"

void GotHere(){
    printf("Got here!\n");
}

void printc(coords_t c){
    printf("x: %d, y: %d; ", c.x, c.y);
}