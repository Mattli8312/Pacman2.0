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
        enum GameState{GAME, FINISH, DEATH, RESET, INIT, MAIN};

        void Init();
        void Render(bool completed = false);
        void Clear();
        void Update();
        void EventListener();
        void RenderText();
        void RunApplication();

        void ResetPlayers();
        void InitializePlayers();
        bool IsRunning();

        /**Game Logic**/
        void HandleCollision();

        static SDL_Renderer * renderer;

    private:
        int fps = 0;
        int ghost_points = 100;
        GameState state_;
        //Game states/Parameters
        bool running;
        SDL_Window * window;
        MazeGraph * maze;
};

#endif // GAME_H
