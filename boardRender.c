#include "boardRender.h"
#include <raylib.h>
#include "pieces.h"

void RookCheck(coords_t location, piece_t (*boardState)[NUM_TILES], Texture2D* dark_tile);
void BishopCheck(coords_t location, piece_t (*boardState)[NUM_TILES], Texture2D* dark_tile);

void DrawBoard(Texture2D* dark_tile){
    for (int i = 0; i < NUM_TILES; i++){
        for (int j = 0; j < NUM_TILES/2; j++){
            if (i % 2 != 0){
                DrawTexture(*dark_tile, i*TILE_SIZE, j*TILE_SIZE*2, RAYWHITE);
            }
            else{
                DrawTexture(*dark_tile, i*TILE_SIZE, TILE_SIZE + j*TILE_SIZE*2, RAYWHITE);
            }
            
        }
    }
}

void DrawPieces(piece_t (*boardState)[NUM_TILES], texture_t *textures){
    Color renderTint;
    for (int i = 0; i < NUM_TILES; i++){
        for (int j = 0; j < NUM_TILES; j++){
            if (boardState[i][j].type != None){
                if (boardState[i][j].selected || boardState[i][j].clicked) {
                    renderTint = GLOW;
                }
                else{
                    renderTint = RAYWHITE;
                }
                if (boardState[i][j].colour == White){
                    DrawTexture(textures[boardState[i][j].type].whiteSprite, i*TILE_SIZE, j*TILE_SIZE, renderTint);
                }
                else if (boardState[i][j].colour == Black){
                    DrawTexture(textures[boardState[i][j].type].blackSprite, i*TILE_SIZE, j*TILE_SIZE, renderTint);
                }
            }
        }
    }
}

void HighlightValidMoves(piece_t piece, coords_t location, piece_t (*boardState)[NUM_TILES], Texture2D* dark_tile){
    if (piece.type == None) return;

    // Pawn check
    if (piece.type == Pawn){
        if (piece.colour == White){
            if (location.y == 0) return;
            if (boardState[location.x][location.y - 1].type == None){
                DrawTexture(*dark_tile, location.x * TILE_SIZE, (location.y - 1) * TILE_SIZE, VALID);
                boardState[location.x][location.y - 1].valid = TRUE;
            }
            if ((boardState[location.x - 1][location.y - 1].colour == Black) || boardState[location.x - 1][location.y - 1].enPessantAble){
                if (boardState[location.x - 1][location.y - 1].enPessantAble){
                }
                DrawTexture(*dark_tile, (location.x - 1) * TILE_SIZE, (location.y - 1) * TILE_SIZE, VALID);
                boardState[location.x - 1][location.y - 1].valid = TRUE;
            }
            if ((boardState[location.x + 1][location.y - 1].colour == Black) || boardState[location.x + 1][location.y - 1].enPessantAble){
                if (boardState[location.x + 1][location.y - 1].enPessantAble){
                }
                DrawTexture(*dark_tile, (location.x + 1) * TILE_SIZE, (location.y - 1) * TILE_SIZE, VALID);
                boardState[location.x + 1][location.y - 1].valid = TRUE;
            }
            if (location.y == 1) return;
            if ((boardState[location.x][location.y - 1].type == None) && (boardState[location.x][location.y - 2].type == None) && (location.y == 6)){
                DrawTexture(*dark_tile, location.x * TILE_SIZE, (location.y - 2) * TILE_SIZE, VALID);
                boardState[location.x][location.y - 2].valid = TRUE;
            }
        }
        else{
            if (location.y == 7) return;
            if (boardState[location.x][location.y + 1].type == None){
                DrawTexture(*dark_tile, location.x * TILE_SIZE, (location.y + 1) * TILE_SIZE, VALID);
                boardState[location.x][location.y + 1].valid = TRUE;
            }
            if ((boardState[location.x + 1][location.y + 1].colour == White) || boardState[location.x + 1][location.y + 1].enPessantAble){
                if (boardState[location.x + 1][location.y + 1].enPessantAble){
                }
                DrawTexture(*dark_tile, (location.x + 1) * TILE_SIZE, (location.y + 1) * TILE_SIZE, VALID);
                boardState[location.x + 1][location.y + 1].valid = TRUE;
            }
            if ((boardState[location.x - 1][location.y + 1].colour == White) || boardState[location.x - 1][location.y + 1].enPessantAble){
                if (boardState[location.x - 1][location.y + 1].enPessantAble){
                }
                DrawTexture(*dark_tile, (location.x - 1) * TILE_SIZE, (location.y + 1) * TILE_SIZE, VALID);
                boardState[location.x - 1][location.y + 1].valid = TRUE;
            }
            if (location.y == 6) return;
            if ((boardState[location.x][location.y + 1].type == None) && (boardState[location.x][location.y + 2].type == None) && (location.y == 1)){
                DrawTexture(*dark_tile, location.x * TILE_SIZE, (location.y + 2) * TILE_SIZE, VALID);
                boardState[location.x][location.y + 2].valid = TRUE;
            }
        }
    }

    // Rook Check
    if (piece.type == Rook){
        RookCheck(location, boardState, dark_tile);
    }

    // Bishop Check
    if (piece.type == Bishop){
        BishopCheck(location, boardState, dark_tile);
    }

    // Knight Check
    if (piece.type == Knight){
        
    }

    // Queen Check
    if (piece.type == Queen){
        RookCheck(location, boardState, dark_tile);
        BishopCheck(location, boardState, dark_tile);
    }

    // King Check
    if (piece.type == King){
        
    }
}

void MovePiece(coords_t initial, coords_t target, piece_t (*boardState)[NUM_TILES]){
    // Handle en passant
    if (boardState[target.x][target.y].enPessantAble == TRUE){
        if (boardState[initial.x][initial.y].colour == White){
            boardState[target.x][target.y + 1].type = None;
        }
        else if (boardState[initial.x][initial.y].colour == Black){
            boardState[target.x][target.y - 1].type = None;
        }
    }

    // Make move
    boardState[target.x][target.y] = boardState[initial.x][initial.y];
    boardState[initial.x][initial.y].type = None;
}

void RookCheck(coords_t location, piece_t (*boardState)[NUM_TILES], Texture2D* dark_tile){

}

void BishopCheck(coords_t location, piece_t (*boardState)[NUM_TILES], Texture2D* dark_tile){

}