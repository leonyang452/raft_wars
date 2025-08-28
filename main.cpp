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
    int GAME_HEIGHT = 900;
    int PLAYER_POS_Y = 700;
    Color green = {20, 160, 133, 255};
    InitWindow(GAME_WIDTH, GAME_HEIGHT, "Raft Wars");
    Texture2D owletImage = loadImage("assets/Owlet_Monster.png");
    Texture2D pinkMonsterImg = loadImage("assets/Pink_Monster.png");
    Character owl(100, 100, PLAYER_POS_Y, owletImage);
    Weapon w1(5);
    int u_x = 0; // initial velocity in the x direction
    int u_y = 0; // initial velocity in the y direction
    double a_y = -9.8; // gravity on earth
    int s_x = 0; // displacement in the x direction
    double s_y = 0; // displacement in the y direction
    double t = 0.25;
    //cout << owletImage.width * 0.5 << "\n";



    SetTargetFPS(60); // 60 times per second

    // Game Loop
    while(WindowShouldClose() == false){
        // 1. Event Handling

        // 2. Updating Positions


        // 3. Drawing
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(owletImage, 100, PLAYER_POS_Y, WHITE);
        DrawTexture(pinkMonsterImg, 1000, PLAYER_POS_Y, WHITE);
        owl.drawShootArea(owl.get_xPosition(), owl.get_yPosition(), GetMouseX(), GetMouseY());

        if (owl.isShooting(owl.get_xPosition(), owl.get_yPosition(), GetMouseX(), GetMouseY())){
            u_x = w1.calculate_initial_velocity_x(GetMouseX(), owl.get_xPosition()); 
            u_y = w1.calculate_initial_velocity_y(GetMouseY(), owl.get_yPosition()); 

            s_x = w1.calculate_displacement_x(u_x, t);
            s_y = w1.calculate_displacement_y(u_y, a_y, t);
            
            w1.set_shotInProgress(true);

        }

        if (w1.get_shotInProgress() && (owl.get_yPosition() - s_y < owl.get_yPosition())){
            w1.set_xPos(owl.get_xPosition() + s_x);
            w1.set_yPos(owl.get_yPosition() - s_y);
            DrawCircle(w1.get_xPos(), w1.get_yPos(), 2.0f, RED);
            t += 0.25;
            s_x = w1.calculate_displacement_x(u_x, t);
            s_y = w1.calculate_displacement_y(u_y, a_y, t);
        }else{
            w1.set_shotInProgress(false);
            s_x = 0;
            s_y = 0;
            t = 0.25;
        }

        // need to do collision detection
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
