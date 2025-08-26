#include <iostream>
#include <string>
#include <raylib.h>
#include "header files\character.h"
#include "header files\weapon.h"

using namespace std;

/**
 * @brief Takes the relative file path of an image and loads it into the game window
 * 
 * 
 * @param filePath The relative file path of where the image is stored -> Type: const char*
 * 
 * 
 * @return texture of the image -> Type: Texture2D
 */
Texture2D loadImage(const char* filePath){
    Image p1 = LoadImage(filePath);
    Texture2D texture = LoadTextureFromImage(p1);
    UnloadImage(p1);
    return texture;
}

int main(){
    int ballX = 400;
    int ballY = 400;
    int GAME_WIDTH = 1500;
    int GAME_HEIGHT = 500;
    Color green = {20, 160, 133, 255};
    InitWindow(GAME_WIDTH, GAME_HEIGHT, "Raft Wars");
    Texture2D owletImage = loadImage("assets/Owlet_Monster.png");
    Character owl(4, 100, 234);
    //cout << GAME_HEIGHT/2 - owletImage.height/2;



    SetTargetFPS(60); // 60 times per second

    // Game Loop
    while(WindowShouldClose() == false){
        // 1. Event Handling

        // 2. Updating Positions


        // 3. Drawing
        BeginDrawing();
        ClearBackground(green);
        DrawTexture(owletImage, 100, 234, WHITE);
        //cout << GetMouseX() << "\n";
        owl.drawShootArea(owl.get_xPosition(), owl.get_yPosition(), GetMouseX(), GetMouseY());
        //cout << owl.isShooting();
        if (owl.isShooting(owl.get_xPosition(), owl.get_yPosition(), GetMouseX(), GetMouseY())){
            DrawCircle(50, 50, 5.0f, WHITE);
            Weapon w1(5);
            w1.calculateTrajectoryPosition(owl.get_xPosition(), owl.get_yPosition(), GetMouseX(), GetMouseY());
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
