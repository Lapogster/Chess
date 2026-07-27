#include <raylib.h>
#include "pieces.h"
#include "boardRender.h"
#include "playerLogic.h"

#include <stdio.h>

#define WINDOW_H 800
#define WINDOW_V 800

int main(void){

    // Initialise App
    InitWindow(WINDOW_H, WINDOW_V, "Chess");

    piece_t boardState[NUM_TILES][NUM_TILES] = {0};

    texture_t textures[NUM_PIECES + 1] = {0};

    colour_t turn = White;
    coords_t currentTile;
    coords_t lastTile = {0,0};

    // Load Textures
    Texture2D dark_tile = LoadTexture("assets/textures/Dark_Tile.png");

    Texture2D white_pawn = LoadTexture("assets/textures/White_Pawn.png");
    Texture2D black_pawn = LoadTexture("assets/textures/Black_Pawn.png");
    textures[Pawn].whiteSprite = white_pawn;
    textures[Pawn].blackSprite = black_pawn;

    // Spawning Board
    boardState[0][6] = (piece_t){Pawn, White, FALSE, FALSE};
    boardState[1][6] = (piece_t){Pawn, White, FALSE, FALSE};
    boardState[2][6] = (piece_t){Pawn, White, FALSE, FALSE};
    boardState[3][6] = (piece_t){Pawn, White, FALSE, FALSE};
    boardState[4][6] = (piece_t){Pawn, White, FALSE, FALSE};
    boardState[5][6] = (piece_t){Pawn, White, FALSE, FALSE};
    boardState[6][6] = (piece_t){Pawn, White, FALSE, FALSE};
    boardState[7][6] = (piece_t){Pawn, White, FALSE, FALSE};

    boardState[0][1] = (piece_t){Pawn, Black, FALSE, FALSE};
    boardState[1][1] = (piece_t){Pawn, Black, FALSE, FALSE};
    boardState[2][1] = (piece_t){Pawn, Black, FALSE, FALSE};
    boardState[3][1] = (piece_t){Pawn, Black, FALSE, FALSE};
    boardState[4][1] = (piece_t){Pawn, Black, FALSE, FALSE};
    boardState[5][1] = (piece_t){Pawn, Black, FALSE, FALSE};
    boardState[6][1] = (piece_t){Pawn, Black, FALSE, FALSE};
    boardState[7][1] = (piece_t){Pawn, Black, FALSE, FALSE};

    // Run App
    // Game Loop
    while (!WindowShouldClose()){
        BeginDrawing();

        ClearBackground(LIGHTGRAY);

        // Draw Board
        DrawBoard(&dark_tile);

        currentTile = getPlayerInput(turn);
        //printf("(%d, %d)", currentTile.x, currentTile.y);
        boardState[lastTile.x][lastTile.y].selected = FALSE;
        if ((currentTile.x != NOT_VALID) && (currentTile.y != NOT_VALID)){
            boardState[currentTile.x][currentTile.y].selected = TRUE;
            lastTile = currentTile;
        }

        DrawPieces(boardState, textures);

        if (turn == White) SetWindowTitle("Chess - White turn");
        else SetWindowTitle("Chess - Black turn");

        EndDrawing();
    }

    // Unloading Textures from Memory
    UnloadTexture(dark_tile);
    UnloadTexture(white_pawn);
    UnloadTexture(black_pawn);

    // Close App
    CloseWindow();

    return 0;
}