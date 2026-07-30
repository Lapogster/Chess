#include <raylib.h>
#include "pieces.h"
#include "boardRender.h"
#include "playerLogic.h"

#include <stdio.h>

#define WINDOW_H 800
#define WINDOW_V 800

void InvalidateOldMoves(piece_t (*boardState)[NUM_TILES]);
void NextTurn(colour_t *turn);

int main(void){

    // Initialise App
    InitWindow(WINDOW_H, WINDOW_V, "Chess");

    piece_t boardState[NUM_TILES][NUM_TILES] = {0};

    texture_t textures[NUM_PIECES + 1] = {0};

    colour_t turn = White;
    coords_t currentTile;
    coords_t lastClick = {0,0};
    coords_t lastTile = {0,0};
    input_return_t frameInput = {0};

    // Load Textures
    Texture2D dark_tile = LoadTexture("assets/textures/Dark_Tile.png");

    Texture2D white_pawn = LoadTexture("assets/textures/White_Pawn.png");
    Texture2D black_pawn = LoadTexture("assets/textures/Black_Pawn.png");
    textures[Pawn].whiteSprite = white_pawn;
    textures[Pawn].blackSprite = black_pawn;

    // Spawning Board
    boardState[0][6] = (piece_t){Pawn, White, FALSE, FALSE, FALSE};
    boardState[1][6] = (piece_t){Pawn, White, FALSE, FALSE, FALSE};
    boardState[2][6] = (piece_t){Pawn, White, FALSE, FALSE, FALSE};
    boardState[3][6] = (piece_t){Pawn, White, FALSE, FALSE, FALSE};
    boardState[4][6] = (piece_t){Pawn, White, FALSE, FALSE, FALSE};
    boardState[5][6] = (piece_t){Pawn, White, FALSE, FALSE, FALSE};
    boardState[6][6] = (piece_t){Pawn, White, FALSE, FALSE, FALSE};
    boardState[7][6] = (piece_t){Pawn, White, FALSE, FALSE, FALSE};

    boardState[0][1] = (piece_t){Pawn, Black, FALSE, FALSE, FALSE};
    boardState[1][1] = (piece_t){Pawn, Black, FALSE, FALSE, FALSE};
    boardState[2][1] = (piece_t){Pawn, Black, FALSE, FALSE, FALSE};
    boardState[3][1] = (piece_t){Pawn, Black, FALSE, FALSE, FALSE};
    boardState[4][1] = (piece_t){Pawn, Black, FALSE, FALSE, FALSE};
    boardState[5][1] = (piece_t){Pawn, Black, FALSE, FALSE, FALSE};
    boardState[6][1] = (piece_t){Pawn, Black, FALSE, FALSE, FALSE};
    boardState[7][1] = (piece_t){Pawn, Black, FALSE, FALSE, FALSE};

    boardState[3][5] = (piece_t){Pawn, White, FALSE, FALSE, FALSE};
    boardState[5][2] = (piece_t){Pawn, Black, FALSE, FALSE, FALSE};

    // Run App
    // Game Loop
    while (!WindowShouldClose()){
        BeginDrawing();

        ClearBackground(LIGHTGRAY);

        // Draw Board
        DrawBoard(&dark_tile);

        frameInput = getPlayerInput(turn);
        currentTile = frameInput.currentTile;
        //printf("(%d, %d)", currentTile.x, currentTile.y);
        boardState[lastTile.x][lastTile.y].selected = FALSE;
        if ((currentTile.x != NOT_VALID) && (currentTile.y != NOT_VALID)){
            boardState[currentTile.x][currentTile.y].selected = TRUE;
            if ((frameInput.click && boardState[currentTile.x][currentTile.y].colour == turn) && boardState[currentTile.x][currentTile.y].type != None){
                boardState[lastClick.x][lastClick.y].clicked = FALSE;
                boardState[currentTile.x][currentTile.y].clicked = TRUE;
                lastClick = currentTile;
                InvalidateOldMoves(boardState);
            }
            else if (frameInput.click){
                if  (boardState[currentTile.x][currentTile.y].valid == TRUE){
                    MovePiece(lastClick, currentTile, boardState);
                    NextTurn(&turn);
                    boardState[currentTile.x][currentTile.y].selected = FALSE;
                    boardState[currentTile.x][currentTile.y].clicked = FALSE;
                }
            }
            lastTile = currentTile;
        }

        DrawPieces(boardState, textures);

        HighlightValidMoves(boardState[lastClick.x][lastClick.y], lastClick, boardState, &dark_tile);

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

void InvalidateOldMoves(piece_t (*boardState)[NUM_TILES]){
    for (int i = 0; i < NUM_TILES; i++){
        for (int j = 0; j < NUM_TILES; j++){
            boardState[i][j].valid = FALSE;
        }
    }
    for (int i = 0; i < NUM_TILES; i++){
        for (int j = 0; j < NUM_TILES; j++){
            if(boardState[i][j].type == None){
                boardState[i][j].colour = No_colour;
            }
        }
    }
}

void NextTurn(colour_t *turn){
    if (*turn == White){
        *turn = Black;
    }
    else if (*turn == Black){
        *turn = White;
    }
}