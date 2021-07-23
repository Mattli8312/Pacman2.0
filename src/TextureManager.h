#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "Game.h"
class TextureManager
{
    public:
        TextureManager();
        ~TextureManager();
        static SDL_Texture * LoadTexture(const char* filename);
};

#endif // TEXTUREMANAGER_H
