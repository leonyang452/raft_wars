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
    bool test = false;
    int u_x = 0; // initial velocity in the x direction
    int u_y = 0; // initial velocity in the y direction
    double a_y = -9.8; // gravity on earth
    int s_x = 0; // displacement in the x direction
    double s_y = 0; // displacement in the y direction
    double t = 0.25;
    //cout << GAME_HEIGHT/2 - owletImage.height/2;



    SetTargetFPS(60); // 60 times per second

    // Game Loop
    while(WindowShouldClose() == false){
        // 1. Event Handling

        // 2. Updating Positions


        // 3. Drawing
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(owletImage, 100, 234, WHITE);
        //cout << GetMouseX() << "\n";
        owl.drawShootArea(owl.get_xPosition(), owl.get_yPosition(), GetMouseX(), GetMouseY());
        //cout << owl.isShooting();
        if (owl.isShooting(owl.get_xPosition(), owl.get_yPosition(), GetMouseX(), GetMouseY())){
            //DrawCircle(50, 50, 5.0f, WHITE);
            Weapon w1(5);
            //w1.calculateTrajectoryPosition(owl.get_xPosition(), owl.get_yPosition(), GetMouseX(), GetMouseY());
            u_x = GetMouseX() - owl.get_xPosition(); // initial velocity in the x direction
            u_y = owl.get_yPosition() - GetMouseY(); // initial velocity in the y direction
            s_y = (u_y * t) + (0.5) * (a_y) * (t * t);
            s_x = (int)(u_x * t);
            test = true;

        }
        cout << "owl position = " << owl.get_yPosition() << " and ball position = " << owl.get_yPosition() - s_y <<"\n";
        //cout << "ball position = " << owl.get_yPosition() - s_y << "\n";
        if (test && (owl.get_yPosition() - s_y < owl.get_yPosition())){
            //std::cout << yPosOfcharacter - s_y << "\n";
            DrawCircle(owl.get_xPosition() + s_x, owl.get_yPosition() - s_y, 5.0f, RED);
            t += 0.25;
            s_y = (u_y * t) + (0.5) * (a_y) * (t * t);
            s_x = (int)(u_x * t);
        }else{
            test = false;
            s_y = 0;
            s_x = 0;
            t = 0.25;
        }
        cout << test;
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
