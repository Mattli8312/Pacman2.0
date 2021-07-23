#include "TextureManager.h"

TextureManager::TextureManager()
{
    //ctor
}

TextureManager::~TextureManager()
{
    //dtor
}
SDL_Texture* TextureManager::LoadTexture(const char* filename)
{
    if(!IMG_Load(filename))
        std::cout<<"Error with loading: "<<std::endl;
    SDL_Surface * tempSurface = IMG_Load(filename);
    SDL_Texture * tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return tex;
}
