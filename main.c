#include <raylib.h>
#include "pieces.h"
#include "boardRender.h"
#include "playerLogic.h"
#include "myMath.h"
#include "gameInfo.h"

#include <stdio.h>

void InvalidateOldMoves(piece_t (*boardState)[NUM_TILES]);
void NextTurn(colour_t *turn);
void ClearEnPassant(piece_t (*boardState)[NUM_TILES]);
void PromotePiece(coords_t tile, piece_t (*boardState)[NUM_TILES], Texture2D* dark_tile);

int main(void){

    // Initialise App
    InitWindow(WINDOW_H, WINDOW_V, "Chess");
    SetWindowIcon(LoadImage("assets/textures/White_Pawn.png"));

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
    boardState[0][6] = (piece_t){Pawn, White, FALSE, FALSE, FALSE, FALSE};
    boardState[1][6] = (piece_t){Pawn, White, FALSE, FALSE, FALSE, FALSE};
    boardState[2][6] = (piece_t){Pawn, White, FALSE, FALSE, FALSE, FALSE};
    boardState[3][6] = (piece_t){Pawn, White, FALSE, FALSE, FALSE, FALSE};
    boardState[4][6] = (piece_t){Pawn, White, FALSE, FALSE, FALSE, FALSE};
    boardState[5][6] = (piece_t){Pawn, White, FALSE, FALSE, FALSE, FALSE};
    boardState[6][6] = (piece_t){Pawn, White, FALSE, FALSE, FALSE, FALSE};
    boardState[7][6] = (piece_t){Pawn, White, FALSE, FALSE, FALSE, FALSE};

    boardState[0][1] = (piece_t){Pawn, Black, FALSE, FALSE, FALSE, FALSE};
    boardState[1][1] = (piece_t){Pawn, Black, FALSE, FALSE, FALSE, FALSE};
    boardState[2][1] = (piece_t){Pawn, Black, FALSE, FALSE, FALSE, FALSE};
    boardState[3][1] = (piece_t){Pawn, Black, FALSE, FALSE, FALSE, FALSE};
    boardState[4][1] = (piece_t){Pawn, Black, FALSE, FALSE, FALSE, FALSE};
    boardState[5][1] = (piece_t){Pawn, Black, FALSE, FALSE, FALSE, FALSE};
    boardState[6][1] = (piece_t){Pawn, Black, FALSE, FALSE, FALSE, FALSE};
    boardState[7][1] = (piece_t){Pawn, Black, FALSE, FALSE, FALSE, FALSE};

    boardState[3][5] = (piece_t){Pawn, White, FALSE, FALSE, FALSE, FALSE};
    boardState[5][2] = (piece_t){Pawn, Black, FALSE, FALSE, FALSE, FALSE};

    int thisTurnEP = FALSE;

    // Run App
    // Game Loop
    while (!WindowShouldClose()){
        BeginDrawing();

        ClearBackground(LIGHTGRAY);

        // Draw Board
        DrawBoard(&dark_tile);
        DrawPieces(boardState, textures); // Moved for now

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
                    if (boardState[currentTile.x][currentTile.y].enPessantAble) thisTurnEP = TRUE;

                    ClearEnPassant(boardState);
                    
                    if ((boardState[lastClick.x][lastClick.y].type == Pawn) && coordsAbs(lastClick, currentTile).yDiff == 2){
                        if (turn == White){
                            boardState[lastClick.x][lastClick.y - 1].enPessantAble = TRUE;
                        }
                        else{
                            boardState[lastClick.x][lastClick.y + 1].enPessantAble = TRUE;
                        }
                    }

                    MovePiece(lastClick, currentTile, boardState);

                    if (turn == White){
                        if ((currentTile.y == 0) && (boardState[currentTile.x][currentTile.y].type == Pawn)){
                            PromotePiece(currentTile, boardState, &dark_tile);
                        }
                    }
                    else if (turn == Black){
                        if ((currentTile.y == 7) && (boardState[currentTile.x][currentTile.y].type == Pawn)){
                            PromotePiece(currentTile, boardState, &dark_tile);
                        }
                    }

                    if (thisTurnEP){
                        if (boardState[currentTile.x][currentTile.y].colour == White){
                            boardState[currentTile.x][currentTile.y + 1].type = None;
                        }
                        else if (boardState[currentTile.x][currentTile.y].colour == Black) {
                            boardState[currentTile.x][currentTile.y - 1].type = None;
                        }
                    }
                    thisTurnEP = FALSE;

                    NextTurn(&turn);
                    boardState[currentTile.x][currentTile.y].selected = FALSE;
                    boardState[currentTile.x][currentTile.y].clicked = FALSE;
                }
            }
            lastTile = currentTile;
        }

        //DrawPieces(boardState, textures);

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

void ClearEnPassant(piece_t (*boardState)[NUM_TILES]){
    for (int i = 0; i < NUM_TILES; i++){
        for (int j = 0; j < NUM_TILES; j++){
            boardState[i][j].enPessantAble = FALSE;
        }
    }
}

void PromotePiece(coords_t tile, piece_t (*boardState)[NUM_TILES], Texture2D* dark_tile){
    //printf("Promoting at x:%d y%d\n", tile.x, tile.y);
    PromoteBox(dark_tile);
    EndDrawing();
    while (TRUE);
    }