#include "playerLogic.h"
#include <raylib.h>
#include "pieces.h"

input_return_t getPlayerInput(colour_t turn){
    coords_t currentTile = {NOT_VALID, NOT_VALID};

    Vector2 mousePos = GetMousePosition();
    int x = mousePos.x / TILE_SIZE;
    int y = mousePos.y / TILE_SIZE;

    // Check if mouse within bounds
    if ((x >= 0 && x < NUM_TILES) && (y >= 0 && y < NUM_TILES)){
        currentTile.x = x;
        currentTile.y = y;
    }

    input_return_t input = {0};
    input.currentTile = currentTile;

    if (((x >= 0 && x < NUM_TILES) && (y >= 0 && y < NUM_TILES)) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        input.click = TRUE;
    }

    return input;
}