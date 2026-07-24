#include <raylib.h>

int main(void){

    // Initialise App
    InitWindow(800, 800, "Game Window");

    // Load Textures
    Texture2D dark_tile = LoadTexture("assets/textures/Dark_Tile.png");
    Texture2D white_pawn = LoadTexture("assets/textures/White_Pawn.png");
    Texture2D black_pawn = LoadTexture("assets/textures/Black_Pawn.png");

    // Run App
    // Game Loop
    int i;
    int j;
    while (!WindowShouldClose()){
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Draw Board
        for (i = 0; i < 8; i++){
            for (j = 0; j < 4; j++){
                if (i % 2 != 0){
                    DrawTexture(dark_tile, i*100.0, j*200.0, RAYWHITE);
                }
                else{
                    DrawTexture(dark_tile, i*100.0, 100.0 + j*200.0, RAYWHITE);
                }

                
            }
        }

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