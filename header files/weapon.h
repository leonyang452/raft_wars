#ifndef WEAPON_H
#define WEAPON_H
#include <iostream>
#include <string>
#include <raylib.h>
class Weapon{
    // attributes
    private:
        int xPos;
        int yPos;
        int massOfWeapon; //const

    // constructor
    public:
        Weapon(int massOfWeaponIn){
            massOfWeapon = massOfWeaponIn;
        }

    // Setters
    int set_xPos(int xPosIn){
        xPos = xPosIn;
    }

    int yPos(int yPosIn){
        yPos = yPosIn;
    }

    int set_massOfWeapon(int massOfWeaponIn){
        massOfWeapon = massOfWeaponIn;
    }

    // Getters
    int get_xPos(){
        return xPos;
    }

    int get_yPos(){
        return yPos;
    }

    // Methods

};

#endif