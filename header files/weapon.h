#ifndef WEAPON_H
#define WEAPON_H
#include <iostream>
#include <string>
#include <raylib.h>
#include <cmath>
class Weapon{
    // attributes
    private:
        int xPos = 0;
        int yPos = 0;
        int massOfWeapon; //const

    // constructor
    public:
        Weapon(int massOfWeaponIn){
            massOfWeapon = massOfWeaponIn;
        }

    // Setters
    void set_xPos(int xPosIn){
        xPos = xPosIn;
    }

    void set_yPos(int yPosIn){
        yPos = yPosIn;
    }

    void set_massOfWeapon(int massOfWeaponIn){
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
    void calculateTrajectoryPosition(int xPosOfcharacter, int yPosOfcharacter, int mouse_xPos, int mouse_yPos){
        int u_x = mouse_xPos - xPosOfcharacter; // initial velocity in the x direction
        int u_y = yPosOfcharacter - mouse_yPos; // initial velocity in the y direction
        double a_y = -9.8; // gravity on earth
        int s_x = 0; // displacement in the x direction
        double s_y = 0; // displacement in the y direction
        double t = 0.25;

        s_y = (u_y * t) + (0.5) * (a_y) * (t * t);

        while (yPosOfcharacter - s_y < yPosOfcharacter){
            //ClearBackground(BLACK);
            s_y = (u_y * t) + (0.5) * (a_y) * (t * t);
            s_x = (int)(u_x * t);
            //std::cout << yPosOfcharacter - s_y << "\n";

            DrawCircle(xPosOfcharacter + s_x, yPosOfcharacter - s_y, 5.0f, RED);
            t += 0.01;
        }
        
    }

};

#endif