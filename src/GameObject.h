#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>

#include "Game.h"
#include "TextureManager.h"
class GameObject
{
    public:
        GameObject(const char* texturesheet, int x, int y, int w, int h);
        ~GameObject();

        void Update(int x, int y);
        void Render();
        int getXpos();
        int getYpos();
        int getWidth();
        int getHeight();

    private:

        int xpos;
        int ypos;
        int width;
        int height;

        SDL_Texture* objTexture;
        SDL_Rect desRect;
        SDL_Renderer* renderer;

};

#endif // GAMEOBJECT_H
