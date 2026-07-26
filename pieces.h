#ifndef PIECES_H
#define PIECES_H

#include <raylib.h>

#define FALSE 0
#define TRUE 1

#define TILE_SIZE 100.0
#define NUM_TILES 8
#define NUM_PIECES 6

typedef enum {
    None,
    Pawn,
    King,
    Queen,
    Bishop,
    Rook,
    Knight
} piece_type_t;

typedef enum {
    No_colour,
    White,
    Black
} colour_t;

// Pieces
typedef struct{
    piece_type_t type;
    colour_t colour;
    int selected;
} piece_t;

typedef struct{
    Texture2D blackSprite;
    Texture2D whiteSprite;
} texture_t;

#endif