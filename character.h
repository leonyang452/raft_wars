#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
#include <string>
#include <raylib.h>

int SHOOTING_AREA_RANGE = 150;

class Character{
    private:
        int healthPoints;
        int xPosition;
        int yPosition;
        int xShootArea[2];
        int yShootArea[2];

    public:
        // Constructors
        Character(int healthPointsIn, int xPositionIn, int yPositionIn){
            healthPoints = healthPointsIn;
            xPosition = xPositionIn;
            yPosition = yPositionIn;
            xShootArea[0] = xPositionIn - SHOOTING_AREA_RANGE; // left
            xShootArea[1] = xPositionIn + SHOOTING_AREA_RANGE; // right
            yShootArea[0] = yPositionIn - SHOOTING_AREA_RANGE; // up
            yShootArea[1] = yPositionIn + SHOOTING_AREA_RANGE; // down

        }

        // Setters
        void setHealthPoints(int healthPointsIn){
            healthPoints = healthPointsIn;
        }

        void set_xPosition(int xPositionIn){
            xPosition = xPositionIn;
        }

        void set_yPosition(int yPositionIn){
            yPosition = yPositionIn;
        }

        //Getters
        int getHealthPoints(){
            return healthPoints;
        }

        int get_xPosition(){
            return xPosition;
        }

        int get_yPosition(){
            return yPosition;
        }

        // Methods

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

        bool isShooting(int xPos, int yPos, int mouse_xPos, int mouse_yPos){
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && (xPos <= mouse_xPos) && (mouse_xPos <= xShootArea[1]) && (yShootArea[0] <= mouse_yPos) && (mouse_yPos <= yShootArea[1])){
                return true;
            }
            return false;
        }

    private:
        bool isCursorInShootingArea(int xPos, int yPos, int mouse_xPos, int mouse_yPos){
            if ((xPos <= mouse_xPos) && (mouse_xPos <= xShootArea[1]) && (yShootArea[0] <= mouse_yPos) && (mouse_yPos <= yShootArea[1])){
                return true;
            }
            return false;
        }


};

#endif