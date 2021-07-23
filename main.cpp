#include <iostream>
#include "Game.h"

int main(int argc, char *argv[])
{
    const float FPS = 60;
    const float frame_delay = 1000.0/FPS;
    Game game;
    game.Init();
    std::cout<<"Game Initialized"<<std::endl;
    std::cout<<"frame delay:"<<frame_delay<<std::endl;
    while(game.IsRunning()){
        game.EventListener();
        game.Update();
        game.Render();
        SDL_Delay(frame_delay);
    }
    std::cout<<"Clearing"<<std::endl;
    game.Clear();
    std::cout<<"Terminated"<<std::endl;
    return 0;
}
