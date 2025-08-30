#ifndef BUTTON_H
#define BUTTON_H
#include <raylib.h>

class Button{
    private:
        Texture2D texture;
        Vector2 position;

    public:
        Button(const char* imagePath, Vector2 imagePosition, float scale){
            Image image = LoadImage(imagePath);
            int originalWidth = image.width;
            int originalHeight = image.height;

            int newWidth = static_cast<int>(originalWidth * scale);
            int newHeight = static_cast<int>(originalHeight * scale);

            ImageResize(&image, newWidth, newHeight);
            texture = LoadTextureFromImage(image);
            UnloadImage(image);
            position = imagePosition;
        }

        void Draw(){
            DrawTextureV(texture, position, WHITE);
        }

        bool isPressed(Vector2 mousePos, bool mousePressed){
            Rectangle rect = {position.x, position.y, static_cast<float>(texture.width), static_cast<float>(texture.height)};

            if(CheckCollisionPointRec(mousePos,rect) && mousePressed)
            {
                return true;
            }
            return false;
        }

};

#endif