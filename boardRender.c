#include "boardRender.h"
#include <raylib.h>
#include "pieces.h"

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
                if (boardState[i][j].selected) {
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