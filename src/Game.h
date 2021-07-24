#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "MazeGraph.h"
#include "TextureManager.h"

class Game
{
    public:
        Game();
        ~Game();
        void Init();
        void Render();
        void Clear();
        void Update();
        void EventListener();
        bool IsRunning();

        static SDL_Renderer * renderer;

    private:
        //Characters

        //Game states/Parameters
        bool running;
        SDL_Window * window;
        MazeGraph * maze;
};

#endif // GAME_H
