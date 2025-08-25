#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
#include <string>


class Character{
    private:
        int healthPoints;
        int xPosition;
        int yPosition;
        int xShootArea;
        int yShootArea;

    public:
        // Constructors
        Character(int healthPointsIn, int xPositionIn, int yPositionIn){
            healthPoints = healthPointsIn;
            xPosition = xPositionIn;
            yPosition = yPositionIn;
            xShootArea = xPositionIn + 75;
            yShootArea = yPositionIn - 75;

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
        int drawShootArea(int xPos, int yPos, int mouse_xPos, int mouse_yPos){
            if ((xPos <= mouse_xPos) && (mouse_xPos <= xShootArea)){
                //std::cout << "hey";
                return 1;

            } 
            return 0;
        }


};

#endif