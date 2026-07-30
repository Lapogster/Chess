// Definitions of structs and enums, all definitions for use across the program

#ifndef PIECES_H
#define PIECES_H

#include <raylib.h>

#define FALSE 0
#define TRUE 1

#define NOT_VALID -1

#define TILE_SIZE 100.0
#define NUM_TILES 8
#define NUM_PIECES 6

typedef enum Type {
    None,
    Pawn,
    King,
    Queen,
    Bishop,
    Rook,
    Knight
} piece_type_t;

int static piece_value[NUM_PIECES + 1] = {0,1,0,9,3,5,3};

typedef enum Colour {
    No_colour,
    White,
    Black
} colour_t;

// Pieces
typedef struct{
    piece_type_t type;
    colour_t colour;
    int selected;
    int clicked;
    int valid;
    int enPessantAble;
} piece_t;

typedef struct{
    Texture2D blackSprite;
    Texture2D whiteSprite;
} texture_t;

typedef struct{
    int x;
    int y;
} coords_t;

typedef struct{
    coords_t currentTile;
    int click;
} input_return_t;

#define GLOW     CLITERAL(Color){ 253, 249, 0, 100 }
#define VALID     CLITERAL(Color){ 253, 255, 0, 80 }

#endif