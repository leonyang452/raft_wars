#ifndef ENEMY_H
#define ENEMY_H
#include <iostream>
#include <string>
#include <raylib.h>
#include "character.h"

class Enemy: public Character{
    private:
        bool shootingStatus = false;

    public:
        Enemy(int healthPointsIn, int xPositionIn, int yPositionIn, Texture2D characterImg)
            : Character(healthPointsIn, xPositionIn, yPositionIn, characterImg) {}

        // Setter
        void setShootingStatus(bool shootingStatusIn){
            shootingStatus = shootingStatusIn;
        }

        // Getter
        bool getShootingStatus(){
            return shootingStatus;
        }
};

#endif