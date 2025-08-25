#include <iostream>
#include <string>
#include <raylib.h>
using namespace std;

int main(){
    int GAME_WIDTH = 1500;
    int GAME_HEIGHT = 500;
    InitWindow(GAME_WIDTH, GAME_HEIGHT, "Raft Wars");

    SetTargetFPS(60); // 60 times per second

    // Game Loop
    while(WindowShouldClose() == false){
        // 1. Event Handling

        // 2. Updating Positions


        // 3. Drawing
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
