#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
#include <string>
#include <raylib.h>

int SHOOTING_AREA_RANGE = 100;

class Character{
    private:
        int healthPoints;
        int xPosition;
        int yPosition;
        int xShootArea[2];
        int yShootArea[2];
        // need to add a hitbox
        int xHitBox[2];
        int yHitBox[2];

    public:
        // Constructors
        Character(int healthPointsIn, int xPositionIn, int yPositionIn, Texture2D characterImg){
            healthPoints = healthPointsIn;
            xPosition = xPositionIn;
            yPosition = yPositionIn;
            xShootArea[0] = xPositionIn - SHOOTING_AREA_RANGE; // left
            xShootArea[1] = xPositionIn + SHOOTING_AREA_RANGE; // right
            yShootArea[0] = yPositionIn - SHOOTING_AREA_RANGE; // up
            yShootArea[1] = yPositionIn + SHOOTING_AREA_RANGE; // down

            xHitBox[0] = (int)(xPosition - (characterImg.width/2)); // lower bound in x direction
            xHitBox[1] = (int)(xPosition + (characterImg.width/2)); // upper bound in x direction

            yHitBox[0] = yPosition; // lower bound in y direction
            yHitBox[1] = (int)(yPosition - (characterImg.height/2)); // upper bound in y direction

        }

        virtual ~Character() {}

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

        int getLowerBoundShootArea_x(){
            return xShootArea[0];
        }

        int getUpperBoundShootArea_x(){
            return xShootArea[1];
        }

        int getLowerBoundShootArea_y(){
            return yShootArea[0];
        }

        int getUpperBoundShootArea_y(){
            return yShootArea[1];
        }
        // Methods

        virtual bool isShooting(int xPos, int yPos, int mouse_xPos, int mouse_yPos, bool isPlayerTurn) = 0;

        bool isHit(int weaponPosX, int weaponPosY){
            if ((xHitBox[0] <= weaponPosX && weaponPosX <= xHitBox[1]) && (yHitBox[1] <= weaponPosY && weaponPosY <= yHitBox[0])){
                return true;
            }
            return false;
        }


};






#endif