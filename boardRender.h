// Functions used for rendering

#ifndef BOARDRENDER_H
#define BOARDRENDER_H

#include "pieces.h"

void DrawBoard(Texture2D* dark_tile);
void DrawPieces(piece_t (*boardState)[NUM_TILES], texture_t *textures);

void HighlightValidMoves(piece_t piece, coords_t location, piece_t (*boardState)[NUM_TILES], Texture2D* dark_tile);

void MovePiece(coords_t initial, coords_t target, piece_t (*boardState)[NUM_TILES]);

#endif