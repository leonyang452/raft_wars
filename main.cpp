#include <iostream>
#include <string>
#include <raylib.h>
#include "header files\character.h"
#include "header files\weapon.h"
#include <cstdlib>
#include <ctime>

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
    Player owl(500, 100, PLAYER_POS_Y, owletImage);
    Player enemy(500, 1000, PLAYER_POS_Y, pinkMonsterImg);
    Weapon w1(5);
    Weapon enemyWeapon(1);
    int u_x = 0; // initial velocity in the x direction
    int u_y = 0; // initial velocity in the y direction
    double a_y = -9.8; // gravity on earth
    int s_x = 0; // displacement in the x direction
    double s_y = 0; // displacement in the y direction
    double t = 0.25;
    bool isPlayerTurn = true;
    bool enemyShooting = false;
    //cout << owletImage.width * 0.5 << "\n";
    srand(time(0));
    //cout << rand() % 101 << "\n";



    SetTargetFPS(60); // 60 times per second

    // Game Loop
    while(WindowShouldClose() == false){
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(owletImage, 100, PLAYER_POS_Y, WHITE);
        DrawTexture(pinkMonsterImg, 1000, PLAYER_POS_Y, WHITE);
        owl.drawShootArea(owl.get_xPosition(), owl.get_yPosition(), GetMouseX(), GetMouseY());
        DrawText(TextFormat("player turn"), 200, 80, 20, RED);

        // player shooting
        if (owl.isShooting(owl.get_xPosition(), owl.get_yPosition(), GetMouseX(), GetMouseY(), isPlayerTurn) && isPlayerTurn){
            u_x = w1.calculate_initial_velocity_x(GetMouseX(), owl.get_xPosition()); 
            u_y = w1.calculate_initial_velocity_y(GetMouseY(), owl.get_yPosition()); 

            s_x = w1.calculate_displacement_x(u_x, t);
            s_y = w1.calculate_displacement_y(u_y, a_y, t);
            
            w1.set_shotInProgress(true);

        }

        if (w1.get_shotInProgress() && (owl.get_yPosition() - s_y < owl.get_yPosition()) && isPlayerTurn){
            w1.set_xPos(owl.get_xPosition() + s_x);
            w1.set_yPos(owl.get_yPosition() - s_y);
            DrawCircle(w1.get_xPos(), w1.get_yPos(), 2.0f, RED);
            t += 0.25;
            s_x = w1.calculate_displacement_x(u_x, t);
            s_y = w1.calculate_displacement_y(u_y, a_y, t);

            if (enemy.isHit(w1.get_xPos(), w1.get_yPos())){
                cout << "hitttt" << "\n";
                enemy.setHealthPoints(enemy.getHealthPoints() - w1.calculateDamage(u_x, u_y));
                isPlayerTurn = false;
                enemyShooting = true;
                s_x = 0;
                s_y = 0;
                t = 0.25;

            }

        }else if(!enemy.isHit(w1.get_xPos(), w1.get_yPos()) && w1.get_shotInProgress()){
            w1.set_shotInProgress(false);
            s_x = 0;
            s_y = 0;
            t = 0.25;
            isPlayerTurn = false;
            enemyShooting = true;

        }

        // enemy shooting
        if(!isPlayerTurn && enemyShooting){
            cout << "shoot" << "\n";
            u_x = enemyWeapon.calculate_initial_velocity_x(enemyWeapon.randomiseVelocityX(enemy.get_xPosition()), enemy.get_xPosition()); 
            u_y = enemyWeapon.calculate_initial_velocity_y(enemyWeapon.randomiseVelocityY(enemy.get_yPosition()), enemy.get_yPosition()); 

            s_x = enemyWeapon.calculate_displacement_x(u_x, t);
            s_y = enemyWeapon.calculate_displacement_y(u_y, a_y, t);

            cout << "u_x = " << u_x << "\n";
            cout << "s_x = " << s_x << "\n";
            cout << "s_y = " << s_y << "\n";
            
            enemyWeapon.set_shotInProgress(true);
            enemyShooting = false;
        }

        if(enemyWeapon.get_shotInProgress() && (enemy.get_yPosition() - s_y < enemy.get_yPosition()) && !isPlayerTurn){
            enemyWeapon.set_xPos(enemy.get_xPosition() + s_x);
            enemyWeapon.set_yPos(enemy.get_yPosition() - s_y);
            DrawCircle(enemyWeapon.get_xPos(), enemyWeapon.get_yPos(), 2.0f, BLUE);
            t += 0.25;
            s_x = enemyWeapon.calculate_displacement_x(u_x, t);
            s_y = enemyWeapon.calculate_displacement_y(u_y, a_y, t);

        }else if(!owl.isHit(enemyWeapon.get_xPos(), enemyWeapon.get_yPos()) && enemyWeapon.get_shotInProgress()){
            enemyWeapon.set_shotInProgress(false);
            s_x = 0;
            s_y = 0;
            t = 0.25;
            isPlayerTurn = true;
            //enemyShooting = false;
            
        }



        EndDrawing();
    }
    CloseWindow();
    return 0;
}
