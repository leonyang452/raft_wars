#include <iostream>
#include <string>
#include <raylib.h>
#include "header files\character.h"
#include "header files\weapon.h"
#include "header files\player.h"
#include "header files\enemy.h"
#include "header files\button.h"
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
    int u_x = 0; // initial velocity in the x direction
    int u_y = 0; // initial velocity in the y direction
    double a_y = -9.8; // gravity on earth
    int s_x = 0; // displacement in the x direction
    double s_y = 0; // displacement in the y direction
    double t = 0.25;
    bool isPlayerTurn = true;
    int MAX_HEALTH = 250;

    InitWindow(GAME_WIDTH, GAME_HEIGHT, "Raft Wars");
    Texture2D owletImage = loadImage("../assets/Owlet_Monster.png");
    Texture2D pinkMonsterImg = loadImage("../assets/Pink_Monster.png");
    Player owl(MAX_HEALTH, 100, PLAYER_POS_Y, owletImage);
    Enemy enemy(MAX_HEALTH, 1000, PLAYER_POS_Y, pinkMonsterImg);
    Weapon w1(5);
    Weapon enemyWeapon(1);
    Button startButton{"../assets/start_button.png", {300, 150}, 0.65};
    srand(time(0));
    SetTargetFPS(60); 

    // Game Loop
    while(WindowShouldClose() == false){
        BeginDrawing();
        ClearBackground(BLACK);


        // checking if both characters are still alive
        if (enemy.getIsAlive() && owl.getIsAlive()){ 
            DrawTexture(owletImage, 100, PLAYER_POS_Y, WHITE);
            DrawTexture(pinkMonsterImg, 1000, PLAYER_POS_Y, WHITE);
            owl.drawShootArea(owl.get_xPosition(), owl.get_yPosition(), GetMouseX(), GetMouseY());
            enemy.displayHealthBar(100, 200, MAX_HEALTH);
            enemy.updateHealthBar(100, 200, enemy.getHealthPoints());

            owl.displayHealthBar(1000, 200, MAX_HEALTH);
            owl.updateHealthBar(1000, 200, owl.getHealthPoints());

        } 

        // checking if enemy is dead
        if (!enemy.getIsAlive()){
            DrawText(TextFormat("You Win"), 750, 500, 100, GREEN);
            s_x = 0;
            s_y = 0;
            t = 0.25;
            Vector2 mousePosition = GetMousePosition();
            bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

            if(startButton.isPressed(mousePosition, mousePressed)){
                ClearBackground(BLACK);
                enemy.set_isAlive(true);
                enemy.setHealthPoints(MAX_HEALTH);
                owl.setHealthPoints(MAX_HEALTH);
                isPlayerTurn = true;
                s_x = 0;
                s_y = 0;
                t = 0.25;
            }
            startButton.Draw();
        }

        // checking if the player is dead
        if (!owl.getIsAlive()){
            DrawText(TextFormat("You lose"), 750, 500, 100, RED);
            s_x = 0;
            s_y = 0;
            t = 0.25;
            Vector2 mousePosition = GetMousePosition();
            bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

            if(startButton.isPressed(mousePosition, mousePressed)){
                ClearBackground(BLACK);
                owl.set_isAlive(true);
                enemy.setHealthPoints(MAX_HEALTH);
                owl.setHealthPoints(MAX_HEALTH);
                isPlayerTurn = true;
                s_x = 0;
                s_y = 0;
                t = 0.25;
            }
            startButton.Draw();
        }


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
                cout << "hit" << "\n";
                enemy.setHealthPoints(enemy.getHealthPoints() - w1.calculateDamage(u_x, u_y));
                isPlayerTurn = false;
                enemy.setShootingStatus(true);
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
            enemy.setShootingStatus(true);

        }

        // enemy shooting
        if(enemy.getShootingStatus() && !isPlayerTurn){
            u_x = enemyWeapon.calculate_initial_velocity_x(enemyWeapon.randomiseVelocityX(enemy.get_xPosition()), enemy.get_xPosition()); 
            u_y = enemyWeapon.calculate_initial_velocity_y(enemyWeapon.randomiseVelocityY(enemy.get_yPosition()), enemy.get_yPosition()); 

            s_x = enemyWeapon.calculate_displacement_x(u_x, t);
            s_y = enemyWeapon.calculate_displacement_y(u_y, a_y, t);
            
            enemyWeapon.set_shotInProgress(true);
            enemy.setShootingStatus(false);
        }

        if(enemyWeapon.get_shotInProgress() && (enemy.get_yPosition() - s_y < enemy.get_yPosition()) && !isPlayerTurn){
            enemyWeapon.set_xPos(enemy.get_xPosition() + s_x);
            enemyWeapon.set_yPos(enemy.get_yPosition() - s_y);
            DrawCircle(enemyWeapon.get_xPos(), enemyWeapon.get_yPos(), 2.0f, BLUE);
            t += 0.25;
            s_x = enemyWeapon.calculate_displacement_x(u_x, t);
            s_y = enemyWeapon.calculate_displacement_y(u_y, a_y, t);

            if (owl.isHit(enemyWeapon.get_xPos(), enemyWeapon.get_yPos())){
                cout << "hitttt" << "\n";
                owl.setHealthPoints(owl.getHealthPoints() - enemyWeapon.calculateDamage(u_x, u_y));
                isPlayerTurn = true;
                enemy.setShootingStatus(false);
                s_x = 0;
                s_y = 0;
                t = 0.25;

            }

        }else if(!owl.isHit(enemyWeapon.get_xPos(), enemyWeapon.get_yPos()) && enemyWeapon.get_shotInProgress()){
            enemyWeapon.set_shotInProgress(false);
            s_x = 0;
            s_y = 0;
            t = 0.25;
            isPlayerTurn = true;
            enemy.setShootingStatus(false);
            
        }

        if (enemy.getHealthPoints() < 0){
            enemy.set_isAlive(false);
        }

        if (owl.getHealthPoints() < 0){
            owl.set_isAlive(false);
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
