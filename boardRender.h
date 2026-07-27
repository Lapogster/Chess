// Functions used for rendering

#ifndef BOARDRENDER_H
#define BOARDRENDER_H

#include "pieces.h"

void DrawBoard(Texture2D* dark_tile);
void DrawPieces(piece_t (*boardState)[NUM_TILES], texture_t *textures);

#endif