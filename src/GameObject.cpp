#include "GameObject.h"

GameObject::~GameObject()
{
    //dtor
}
GameObject::GameObject(const char* texturesheet, int x, int y, int w, int h)
{
    renderer = Game::renderer;
    objTexture = TextureManager::LoadTexture(texturesheet);

    xpos = x;
    ypos = y;
    width = w;
    height = h;
    desRect.h = height;
    desRect.w = width;
}
void GameObject::Update(int x, int y)
{
    xpos = x;
    ypos = y;
    desRect.x = xpos;
    desRect.y = ypos;
}

void GameObject::Render()
{
    SDL_RenderCopy(renderer, objTexture, nullptr, &desRect);
}

/**
* Getters
**/
int GameObject::getXpos()
{
    return xpos;
}

int GameObject::getYpos()
{
    return ypos;
}

int GameObject::getWidth()
{
    return width;
}

int GameObject::getHeight()
{
    return height;
}

