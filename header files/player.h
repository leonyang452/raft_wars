#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include <raylib.h>
#include "character.h"

class Player : public Character {
    public:
        Player(int healthPointsIn, int xPositionIn, int yPositionIn, Texture2D characterImg)
            : Character(healthPointsIn, xPositionIn, yPositionIn, characterImg) {}

        // Implementation of abstract methods

        /**
         * @brief draws a line starting from a players character when the cursor enters the shooting area, showing the trajectory of what the weapon could take
         * 
         * @param xPos: The x coordinate of the player (Type: int)
         * @param yPos: The y coordinate of the player (Type: int)
         * @param mouse_xPos: The x coordinate of the cursor (Type: int)
         * @param mouse_yPos: The y coordinate of the cursor (Type: int)
         * 
         * @return none
         */
        void drawShootArea(int xPos, int yPos, int mouse_xPos, int mouse_yPos){
            if (isCursorInShootingArea(xPos, yPos, mouse_xPos, mouse_yPos)){
                int num_points = 5;
                double change_x = mouse_xPos - xPos;
                double change_y = mouse_yPos - yPos;

                int point_x = xPos + 10;
                int point_y = yPos + 10;
                for (int i = 0; i < num_points; i++){
                    DrawPixel(point_x, point_y, WHITE);
                    point_x += (int)(change_x/num_points);
                    point_y += (int)(change_y/num_points);
                }
            }
        }

 

        /**
         * @brief checks if a player is trying to shoot there weapon
         * 
         * checks if a players cursor is within the shooting area and if the mouse is clicked
         * 
         * @param xPos: The x coordinate of the player
         * @param yPos: The y coordinate of the player 
         * @param mouse_xPos: The x coordinate of the cursor
         * @param mouse_yPos: The y coordinate of the cursor
         * 
         * @return true/false
         */
        bool isShooting(int xPos, int yPos, int mouse_xPos, int mouse_yPos, bool isPlayerTurn) override{
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isCursorInShootingArea(xPos, yPos, mouse_xPos, mouse_yPos)){
                return true;
            }
            return false;
        }
    
    private:
        /**
         * @brief checks if a players cursor is within the shooting area
         * 
         * this method is private because it is only used within character.h
         * 
         * @param xPos: The x coordinate of the player 
         * @param yPos: The y coordinate of the player 
         * @param mouse_xPos: The x coordinate of the cursor 
         * @param mouse_yPos: The y coordinate of the cursor 
         * 
         * @return true/false
         */
        bool isCursorInShootingArea(int xPos, int yPos, int mouse_xPos, int mouse_yPos){
            int xUpperBound = getUpperBoundShootArea_x();
            int yLowerBound = getLowerBoundShootArea_y();
            int yUpperBound = getUpperBoundShootArea_y();
            if ((xPos <= mouse_xPos) && (mouse_xPos <= xUpperBound) && (yLowerBound <= mouse_yPos) && (mouse_yPos <= yUpperBound)){
                return true;
            }
            return false;
        }
};

#endif