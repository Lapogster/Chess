#include "playerLogic.h"
#include <raylib.h>
#include "pieces.h"

coords_t getPlayerInput(colour_t turn){
    coords_t currentTile = {NOT_VALID, NOT_VALID};

    Vector2 mousePos = GetMousePosition();
    int x = mousePos.x / TILE_SIZE;
    int y = mousePos.y / TILE_SIZE;

    // Check if mouse within bounds
    if ((x >= 0 && x < NUM_TILES) && (y >= 0 && y < NUM_TILES)){
        currentTile.x = x;
        currentTile.y = y;
    }

    return currentTile;
}